/****************************************************************************/
/*  vcop_memory.c        - VCOP Compiler Assisted Memory Allocation         */
/*                                                                          */
/* Copyright (c) 2011 Texas Instruments Incorporated                        */
/* http://www.ti.com/                                                       */
/*                                                                          */
/*  Redistribution and  use in source  and binary forms, with  or without   */
/*  modification,  are permitted provided  that the  following conditions   */
/*  are met:                                                                */
/*                                                                          */
/*     Redistributions  of source  code must  retain the  above copyright   */
/*     notice, this list of conditions and the following disclaimer.        */
/*                                                                          */
/*     Redistributions in binary form  must reproduce the above copyright   */
/*     notice, this  list of conditions  and the following  disclaimer in   */
/*     the  documentation  and/or   other  materials  provided  with  the   */
/*     distribution.                                                        */
/*                                                                          */
/*     Neither the  name of Texas Instruments Incorporated  nor the names   */
/*     of its  contributors may  be used to  endorse or  promote products   */
/*     derived  from   this  software  without   specific  prior  written   */
/*     permission.                                                          */
/*                                                                          */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS   */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT   */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR   */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT   */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT   */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,   */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY   */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT   */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    */
/*                                                                          */
/****************************************************************************/

#undef _INLINE                          /* DISABLE INLINE EXPANSION         */

#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <_lock.h>
#include <vcop/mempkt.h>
#include <vcop/vcopmem.h>

/*----------------------------------------------------------------------------
* Create the initial entry defining the memory pool for each VCOP heap and
* place them in an individual user section.  The linker will place each user
* section into its corresponding memory region, as defined by the linker
* command file, with a section size also defined by the linker command file.
* Note that this means that the allocatable space is actually (re)allocated in
* the linker to ensure that other data cannot be placed there during linktime.
* The memory pools must also be properly aligned.
*---------------------------------------------------------------------------*/
#pragma DATA_SECTION(_imemla_memory, ".imemla")
#pragma DATA_ALIGN(_imemla_memory, __ALIGNOF__(int));
PACKET _imemla_memory[1];

#pragma DATA_SECTION(_imemha_memory, ".imemha")
#pragma DATA_ALIGN(_imemha_memory, __ALIGNOF__(int));
PACKET _imemha_memory[1];

#pragma DATA_SECTION(_imemlb_memory, ".imemlb")
#pragma DATA_ALIGN(_imemlb_memory, __ALIGNOF__(int));
PACKET _imemlb_memory[1];

#pragma DATA_SECTION(_imemhb_memory, ".imemhb")
#pragma DATA_ALIGN(_imemhb_memory, __ALIGNOF__(int));
PACKET _imemhb_memory[1];

#pragma DATA_SECTION(_wmem_memory, ".wmem")
#pragma DATA_ALIGN(_wmem_memory, __ALIGNOF__(int));
PACKET _wmem_memory[1];

/*----------------------------------------------------------------------------
* IMEML_SIZE, IMEMH_SIZE, WMEM_SIZE are symbols that define the size of the
* VCOP memory heaps.  They need to be defined within a linker command file.
*---------------------------------------------------------------------------*/
extern int IMEML_SIZE[];
extern int IMEMH_SIZE[];
extern int WMEM_SIZE [];

#define INTVAL(sym) ((int)(uint64_t)(&sym))

typedef uint64_t addrtype;    // integral type corresponding to pointer

/*----------------------------------------------------------------------------
* vcop_heap datastructure representing the state of a VCOP memory heap
*---------------------------------------------------------------------------*/
typedef struct vheap
{
    PACKET      *freeblk;  /* Pointer to heap freelist               */
    addrtype     beg;      /* Location of the beginning of the heap  */
    uintptr_t    len;      /* Length of the heap                     */
    int          aliased;  /* Aliased state of the heap              */
    VCOP_MEMHEAP aliasidx; /* Index of aliased heap freelist         */
} vcop_heap;

/*----------------------------------------------------------------------------
* Setup the VCOP memory allocator state, consisting of:
*  - pointer to the freelist for the heap
*  - the location of the heap in VCOP memory
*  - the total size of the heap
*  - whether the heap is aliased by another heap
*  - ID of the aliased heap, if applicable
*---------------------------------------------------------------------------*/
#pragma diag_suppress 70  // "warning: integer conversion resulted in truncation"
                          // SIZE symbols should not exceed 32b

static vcop_heap vcop_mem[5] =
{
   { _imemla_memory, (addrtype)&_imemla_memory, INTVAL(IMEML_SIZE), 0, VCOP_IBUFLB },
   { _imemha_memory, (addrtype)&_imemha_memory, INTVAL(IMEMH_SIZE), 0, VCOP_IBUFHB },
   { _imemlb_memory, (addrtype)&_imemlb_memory, INTVAL(IMEML_SIZE), 1, VCOP_NONE },
   { _imemhb_memory, (addrtype)&_imemhb_memory, INTVAL(IMEMH_SIZE), 1, VCOP_NONE },
   { _wmem_memory,   (addrtype)&_wmem_memory,   INTVAL(WMEM_SIZE),  0, VCOP_NONE }
};
#pragma diag_default 70

/*----------------------------------------------------------------------------
* MINSIZE is the smallest packet we will allocate.  It is required that
* (MINSIZE + OVERHEAD) >= sizeof(PACKET), otherwise the packet will not be
* large enough to store the bookkeeping needed to be placed in the free list.
*---------------------------------------------------------------------------*/
#define MINSIZE 8

/*----------------------------------------------------------------------------
* first_call tells vcop_malloc if the heaps need to be initialized
*---------------------------------------------------------------------------*/
static int first_call = 1;

/*----------------------------------------------------------------------------
* vcop_view represents the vcop memory view state: FLAT (default) or ALIASED
*---------------------------------------------------------------------------*/
static VCOP_MEMVIEW vcop_view = VCOP_MEMFLAT;
#define VCOP_ALIASED (vcop_view == VCOP_MEMALIASED)

/*----------------------------------------------------------------------------
* VCOP_SETVIEW - Set the memory view of the VCOP memory heaps
*---------------------------------------------------------------------------*/
void vcop_setview(VCOP_MEMVIEW view) { vcop_view = view; }

/*----------------------------------------------------------------------------
* VCOP_MINIT - This function performs the initial setup of the heap.
*---------------------------------------------------------------------------*/
void vcop_minit(void)
{
    int heap;
    _lock();

    /*------------------------------------------------------------------------
    * To initialize the memory system, set up the free list in each applicable
    * heap to point to the entire heap and initialize the heap to a single
    * empty packet.
    *-----------------------------------------------------------------------*/
    for (heap = VCOP_IBUFLA; heap <= VCOP_WMEM; heap++)
    {
        memsz_t size = -((vcop_mem[heap].len & ~(MINSIZE-1)) - OVERHEAD);
        vcop_mem[heap].freeblk->packet_size = size;
        vcop_mem[heap].freeblk->next_free   = LIMIT;
#ifdef DEBUG
        vcop_mem[heap].freeblk->guard       = GUARDDWORD;
#endif
    }

    first_call = 0; /* CLEAR THE FLAG */
    _unlock();
}

/*----------------------------------------------------------------------------
* VCOP_MEMALIGN - Allocate a packet of a given size from a given heap.  The  
*                 returned pointer is aligned to the specified alignment value.
*---------------------------------------------------------------------------*/
void *vcop_memalign(VCOP_MEMHEAP heap, VCOP_ALIGNSPEC align, int size)
{
    void *mem = 0;
    void *ptr = 0;
    memsz_t allocsize;

    /*------------------------------------------------------------------------
    * SDSCM00049633: Verify that the requested size value will not cause
    * an overflow of the memsz_t type during the allocation process.  This  
    * should never happen here since size is an int, but check anyway.
    * Note: there is no bugslayer test for this functionality in VCOP CAMA.
    *-----------------------------------------------------------------------*/
    if (size > (MEMSZ_MAX - align - OVERHEAD - MINSIZE - sizeof(void *)))
       return 0;

    allocsize = size;

    /*------------------------------------------------------------------------
    * No restrictions are placed in this code on alignment values that may
    * be requested for any particular heap.  If the heap does not contain a
    * free memory region large enough to fulfill an alignment request, then 
    * vcop_memalign() will return 0.
    * For EVE hardware, alignment at 16K can only work for buffer VCOP_WMEM
    * (of size 32K) due to the memory management overhead.
    *-----------------------------------------------------------------------*/

    /*------------------------------------------------------------------------
    * If the memory is "aliased", aliased heaps are off limits to user
    *-----------------------------------------------------------------------*/
    if (VCOP_ALIASED && vcop_mem[heap].aliased) return 0;

    /*------------------------------------------------------------------------
    * If allocsize is zero or if heap is empty, don't attempt to allocate
    *-----------------------------------------------------------------------*/
    if (allocsize == 0 || vcop_mem[heap].len == 0) return 0;

    /*------------------------------------------------------------------------
    * Adjust the size of the allocation request so that the allocated address
    * can be aligned accomodate VCOP usage scenarios.  See allowed alignement
    * values in vcopmem.h.
    * Also include an extra 4-bytes so that the original, unaligned memory
    * address can be stored off to be retrieved later by vcop_free(). 
    * Then, adjust the size of the allocation according to MINSIZE to ensure
    * that the address of the field "next_free" remains strictly aligned in all
    * packets on the free list.
    *
    * Essentially, we need a buffer that looks like this, where OVERHEAD refers
    * to the internal allocator overhead to maintain the allocated size:
    *
    *      ------------------------------------------------------------
    *     | OVERHEAD |  align - OVERHEAD  | sizeof(void*) | allocsize |
    *      ------------------------------------------------------------
    *                ^- unaln addr
    *
    * Note that mem_alloc() adds OVERHEAD to the allocation size requested.
    *
    * This turns into:
    *
    *      ------------------------------------------------------------
    *     | <- 4b -> | <----- 0x1Cb -----> | <--- 4b ----> | allocsize |
    *      ------------------------------------------------------------
    *                ^- unaln addr
    *
    * mem_alloc() will return "unaln addr", and the VCOP allocator needs to
    * return an address aligned as requested by vcop_malloc()/vcop_memalign().
    * vcop_malloc must also allow 4bytes of space to store the "unaln addr"
    * so that it can be found by vcop_free().
    *
    * The reason we need to add both the requested alignment size AND the
    * 4-bytes for the sizeof(void*)  is to handle the case in which 
    * "unaln addr" is already aligned along a 32 byte boundary and we still
    * need 4bytes of space at which to store the value for vcop_free() to know
    * what address it needs to free.  If this is not done, vcop_free() cannot
    * know what address it has to free nor would it know that the address it
    * was given was already aligned.  Thus we waste a total of alignment size
    * plus 4 bytes per allocation.  For the default alignment size, this is
    * 36bytes overhead per allocation, which for VCOP is acceptable.
    *-----------------------------------------------------------------------*/
    allocsize += (align - OVERHEAD + sizeof(void*));
    allocsize = RNDUP((allocsize + OVERHEAD), MINSIZE) - OVERHEAD;

    if (first_call) vcop_minit();

    _lock();

    /*------------------------------------------------------------------------
    * Allocate requested memory from primary heap
    *-----------------------------------------------------------------------*/
    ptr = mem_alloc(&vcop_mem[heap].freeblk, allocsize);

    /*------------------------------------------------------------------------
    * If the memory is "aliased", allocate also from the aliased block.
    * There are two primary reasons for this:
    *
    * 1.) The allocator can guarantee that if it returns an allocated address
    *     from the primary heap, the precise and expected area of memory is also
    *     available in the aliased heap.
    * 2.) The allocator can guarantee that both the primary and aliased heaps
    *     are setup correctly by the user and no other data is placed in them
    *     that would impact heap accessibility or allocatable size.
    *-----------------------------------------------------------------------*/
    if (VCOP_ALIASED && (vcop_mem[heap].aliasidx != VCOP_NONE) && ptr != NULL)
    {
        int aheap  = vcop_mem[heap].aliasidx;
        int pdiff  = vcop_mem[aheap].beg - vcop_mem[heap].beg;
        void *aptr = mem_alloc(&vcop_mem[aheap].freeblk, allocsize);

        /*--------------------------------------------------------------------
        * If allocation of aliased heap fails, free primary heap and return 0.
        * The allocator cannot guarantee that the aliased buffer can be used
        * safely.
        *-------------------------------------------------------------------*/
        if (aptr == NULL)
        {
            mem_free(&vcop_mem[heap].freeblk, ptr);
            _unlock();
            return 0;
        }

        /*--------------------------------------------------------------------
        * If the ptrs are not consistent or in sync, free both and return 0.
        * This means the allocator has determined that something has impacted
        * the accessibilty or allocatable size of either or both of the heaps.
        *-------------------------------------------------------------------*/
        if (((addrtype)aptr - (addrtype)ptr) != pdiff)
        {
            mem_free(&vcop_mem[heap].freeblk,   ptr);
            mem_free(&vcop_mem[aheap].freeblk, aptr);
            _unlock();
            return 0;
        }
    }

    _unlock();

    /*------------------------------------------------------------------------
    * If initial allocation was not successful, just return
    *-----------------------------------------------------------------------*/
    if (ptr == NULL) return 0;

    /*------------------------------------------------------------------------
    * Align the memory pointer by 32 bytes, including space for actual ptr
    *-----------------------------------------------------------------------*/
    mem = (void*) RNDUP((addrtype)((char*)ptr + sizeof(void*)), align);

    /*------------------------------------------------------------------------
    * Record actual, unaligned memory pointer so that it can be freed later
    *-----------------------------------------------------------------------*/
    ((void**)mem)[-1] = ptr;

    return mem;
}

/*----------------------------------------------------------------------------
* VCOP_MALLOC - Allocate a packet of a given size from a given heap and return
*               an aligned (VCOP_DEFAULT_ALIGN = 0x20) memory pointer to it.
*---------------------------------------------------------------------------*/
void *vcop_malloc(VCOP_MEMHEAP heap, int size)
{
    return vcop_memalign(heap, VCOP_DEFAULT_ALIGN, size);
}

/*----------------------------------------------------------------------------
* VCOP_FREE - Return a packet allocated by vcop_malloc to the VCOP free memory
*             pool.  The algorithm will automatically calculate which heap from
*             which to free the memory.
*---------------------------------------------------------------------------*/
#define INHEAP(p,b,l) ((p >= b) && (p < (b + l)))
void vcop_free(void *userptr)
{
    int heap;
    void *ptr;

    /*------------------------------------------------------------------------
    * If pointer is NULL, just return
    *-----------------------------------------------------------------------*/
    if (userptr == 0) return;

    /*------------------------------------------------------------------------
    * Extract actual pointer to be freed
    *-----------------------------------------------------------------------*/
    ptr = ((void**)userptr)[-1];

    for (heap = VCOP_IBUFLA; heap <= VCOP_WMEM; heap++)
    {
        if (INHEAP((addrtype)ptr, vcop_mem[heap].beg, vcop_mem[heap].len))
        {
            _lock();

            /*----------------------------------------------------------------
            * If aliased view, free memory from aliased block
            *---------------------------------------------------------------*/
            if (VCOP_ALIASED && (vcop_mem[heap].aliasidx != VCOP_NONE))
            {
                int aheap = vcop_mem[heap].aliasidx;
                int pdiff = vcop_mem[aheap].beg - vcop_mem[heap].beg;
                mem_free(&vcop_mem[aheap].freeblk, (void*)((addrtype)ptr + pdiff));
            }

            /*----------------------------------------------------------------
            * Free memory from block
            *---------------------------------------------------------------*/
            mem_free(&vcop_mem[heap].freeblk, ptr);
            _unlock();
            return;
        }
    }
}

// #include "memory.c"
/*****************************************************************************/
/*									     */
/*  MEM_ALLOC - Generic malloc algorithm, operating on a given freelist ptr  */
/*									     */
/*****************************************************************************/
void *mem_alloc(PACKET **free_mem, size_t allocsize)
{
    PACKET *current, *next, *prev;

    _lock();

    current = *free_mem;
    prev = 0;

    /*-----------------------------------------------------------------------*/
    /* Find the first block large enough to hold the requested allocation    */
    /*-----------------------------------------------------------------------*/
    while (current != LIMIT && -current->packet_size < allocsize)
    {
	prev = current;
	current = current->next_free;
    }

    if (current == LIMIT)
    {
        /*-------------------------------------------------------------------*/
        /* No block large enough was found, so return NULL.		     */
        /*-------------------------------------------------------------------*/
	_unlock();
	return 0;
    }

    if (-current->packet_size > (allocsize + OVERHEAD + MINSIZE))
    {
        /*-------------------------------------------------------------------*/
        /* The packet is larger than needed; split the block and mark the    */
        /* smaller-addressed block as used.  The smaller-addressed block     */
        /* was chosen as a way to ensure that freed blocks get recycled	     */
        /* before allocations are made from the large original free block.   */
        /* However, this may tend to increase the length of the free list    */
        /* search for a large enough block.				     */
        /*-------------------------------------------------------------------*/
        /* Knuth's algorithm 2.5a instead allocates the larger-addressed     */
        /* block to the user.  This tends to leave the largest free blocks   */
        /* at the beginning of the free list.  Knuth's 2.5a' uses a "rover"  */
        /* pointer to prevent small free blocks from being concentrated in   */
        /* any part of the list.					     */
        /*-------------------------------------------------------------------*/
	next = (PACKET *)((char *)current + allocsize + OVERHEAD);
	next->packet_size=current->packet_size+allocsize+OVERHEAD;/*NEG==FREE*/
#ifdef DEBUG
	next->guard = GUARDDWORD;
#endif
	current->packet_size = allocsize; /* POSITIVE==IN USE */

	if (prev) prev->next_free = next;
	else      *free_mem       = next;

	next->next_free = current->next_free;
    }
    else
    {
        /*-------------------------------------------------------------------*/
        /* Allocate the whole block and remove it from the free list.	     */
        /*-------------------------------------------------------------------*/
	if (prev) prev->next_free = current->next_free;
	else      *free_mem       = current->next_free;

	current->packet_size = -current->packet_size; /* POSITIVE==IN USE */
    }

    _unlock();
    return &(current->next_free);
}

/*****************************************************************************/
/*									     */
/*  MEM_FREE - Generic free algorithm, operating on a given freelist ptr     */
/*									     */
/*****************************************************************************/
void mem_free(PACKET **free_mem, void *userptr)
{
    PACKET *sysblock, *next, *prev;

    if (userptr == 0) return; /* HANDLE NULL POINTER */

    _lock();

    next = *free_mem;
    prev = 0;
    sysblock = (PACKET *)((char *)userptr - OVERHEAD);

    /*-----------------------------------------------------------------------*/
    /* Search the free list for the *free* packets physically closest to     */
    /* the packet to be freed.  PREV is the closest free packet with a	     */
    /* smaller address, and NEXT is the closest free packet with a larger    */
    /* address.								     */
    /*-----------------------------------------------------------------------*/
    while (next < sysblock)
    {
	prev = next;
	next = next->next_free;
    }

    /*-----------------------------------------------------------------------*/
    /* Coallesce with next block if possible.				     */
    /*-----------------------------------------------------------------------*/
    if ((char *)sysblock + sysblock->packet_size + OVERHEAD == (char *)next)
    {
	sysblock->next_free = next->next_free;
	sysblock->packet_size += -next->packet_size + OVERHEAD;	/* POS==USED */
#ifdef DEBUG
	next->guard = 0;
#endif
    }
    else sysblock->next_free = next;	/* START TO PUT INTO LIST */

    if (prev)				/* ARE WE THE NEW HEAD OF THE LIST */
    {
        /*-------------------------------------------------------------------*/
        /* sysblock is not the head of the free list; try to coallesce with  */
        /* prev								     */
        /*-------------------------------------------------------------------*/
	if ((char *)prev - prev->packet_size + OVERHEAD == (char *)sysblock)
	{
	    prev->next_free = sysblock->next_free;
	    prev->packet_size += -sysblock->packet_size - OVERHEAD;/*NEG==FREE*/
#ifdef DEBUG
	    sysblock->guard = 0;
#endif
	}
	else
	{
	    prev->next_free = sysblock;
	    sysblock->packet_size = -sysblock->packet_size; /* NEGATIVE==FREE */
	}
    }
    else
    {
	*free_mem = sysblock;
	sysblock->packet_size = -sysblock->packet_size; /* NEGATIVE==FREE */
    }
    _unlock();
}
