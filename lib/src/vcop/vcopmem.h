/*****************************************************************************/
/*  VCOPMEM.H                                                                */
/*  VCOP buffer memory allocation API                                        */
/*                                                                           */
/*                                                                           */
/* Copyright (c) 2011 Texas Instruments Incorporated                         */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/
#ifndef _VCOPMEM_H
#define _VCOPMEM_H

/*-----------------------------------------------------------------------------
* VCOP_MEMVIEW - Possible VCOP memory view options (default: VCOP_MEMFLAT)
*                VCOP_MEMFLAT:    Users may allocate memory from any of the
*                                 five VCOP heaps.
*                VCOP_MEMALIASED: Users may only allocate from IBUFLA, IBUFHA,
*                                 and WMEM. IBUFLA and IBUFHA alias IBUFLB and
*                                 IBUFHB, respectively.  Under this mode, the
*                                 VCOP allocator will manage memory for both
*                                 A and B heaps transparently, even though an
*                                 address for the allocated A heap is returned.
*----------------------------------------------------------------------------*/
typedef enum memview
{
    VCOP_MEMFLAT = 0,
    VCOP_MEMALIASED
} VCOP_MEMVIEW;

/*-----------------------------------------------------------------------------
* VCOP_MEMHEAP - Possible VCOP heap id values
*                VCOP_NONE:   Invalid buffer heap
*                VCOP_IBUFLA: IBUFLA Buffer Heap
*                VCOP_IBUFHA: IBUFHA Buffer Heap
*                VCOP_IBUFLB: IBUFLB Buffer Heap
*                VCOP_IBUFHB: IBUFHB Buffer Heap
*                VCOP_WMEM:   WMEM Buffer Heap
*----------------------------------------------------------------------------*/
typedef enum memheap
{
    VCOP_NONE   = -1,
    VCOP_IBUFLA = 0,
    VCOP_IBUFHA,
    VCOP_IBUFLB,
    VCOP_IBUFHB,
    VCOP_WMEM
} VCOP_MEMHEAP;

typedef enum alignspec
{
    VCOP_DEFAULT_ALIGN = 0x20,
    VCOP_1K            = 0x400,
    VCOP_2K            = 0x800,
    VCOP_4K            = 0x1000,
    VCOP_8K            = 0x2000,
    VCOP_16K           = 0x4000
} VCOP_ALIGNSPEC;

/*---------------------------------------------------------------------------*/
/* API functions                                                             */
/*                                                                           */
/* void *vcop_malloc(VCOP_MEMHEAP heap, int size)                            */
/*       - Allocate 'size' bytes from a VCOP heap, using heap id values:     */
/*         VCOP_IBUFLA, VCOP_IBUFHA, VCOP_IBUFLB, VCOP_IBUFHB, VCOP_WMEM     */
/*                                                                           */
/* void *vcop_memalign(VCOP_MEMHEAP heap, VCOP_ALIGNSPEC align, int size)    */
/*       - Allocate 'size' bytes from a VCOP heap, using heap id values as   */
/*         above and alignment specification values:                         */
/*         VCOP_DEFAULT_ALIGN = 0x20 (used by vcop_malloc()),                */
/*         VCOP_1K, VCOP_2K, VCOP_4K, VCOP_8K, VCOP_16K                      */
/*                                                                           */
/* void  vcop_free(void *userptr)                                            */
/*       - Free memory indicated by pointer.  Allocator will automatically   */
/*         determine the corresponding heap                                  */
/*                                                                           */
/* void  vcop_setview(VCOP_MEMVIEW view)                                     */
/*       - Set allocator according to VCOP_MEMFLAT or VCOP_MEMALIASED view.  */
/*         Under aliased view, allocator will also manage memory for aliased */
/*         heaps when memory is allocated from IBUFLA or IBUFHA.             */
/*         views: VCOP_MEMFLAT (default) or VCOP_MEMALIASED                  */
/*                                                                           */
/* void  vcop_minit()                                                        */
/*       - Reset the state of the VCOP memory allocator.  This routine is    */
/*         invoked automatically when vcop_malloc() is called for the very   */
/*         first time.  Note: It does NOT free previously allocated memory.  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

void  vcop_setview  (VCOP_MEMVIEW view);
void *vcop_malloc   (VCOP_MEMHEAP heap, int size);
void *vcop_memalign (VCOP_MEMHEAP heap, VCOP_ALIGNSPEC align, int size);
void  vcop_free     (void *userptr);
void  vcop_minit    (void);

#ifdef __cplusplus
}
#endif

#endif /* VCOPMEM_H */
