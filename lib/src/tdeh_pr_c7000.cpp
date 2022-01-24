/*****************************************************************************/
/*  tdeh_pr_c7000.cpp                                                        */
/*  Copyright (c) 2016       Texas Instruments Incorporated                  */
/*                                                                           */
/*  Contains the target-dependent routines of the Personality Routine (PR)   */
/*  implementation (PR entry points pr0 - pr3, unwind processing)            */
/*  required by Table-Driven Exception Handling                              */
/*                                                                           */
/*****************************************************************************/
#if __EXCEPTIONS && defined(__TI_TABLE_DRIVEN_EXCEPTIONS)

#include <stdlib.h>
#include "tdeh_common.h"
#include "tdeh_c7000.h"

#if defined(DEBUG_UNWINDER)
#include <vcop/vcop.h>
#include <stdio.h>
#include <ctype.h>
typedef __int16 __vector;
template <typename type, int n = sizeof(__vector)/sizeof(type)> struct vector;
template<> struct vector<int64_t,8> { typedef __long8 type; };
template<> struct vector<int64_t,4> { typedef __long4 type; };
template<> struct vector<int64_t,2> { typedef __long2 type; };

/******************************************************************************
* print - Vector print operation for kernel debugging 
*    Invoked by translator for Kernel C "print" statements, as
*        print<type,simd>(Vec, "tag%N");
*    where
*        'tag' is an optional prefix label
*        N gives the number of bits in each element
*    for example 
*        print<int32_t,16>::apply(v, "myvec:%16")
*    might print
*        myvec: 1122 3344 5566 7788 99aa bbcc ddee ff00 
******************************************************************************/
template <typename elem_type, int simd=sizeof(__vector)/sizeof(elem_type)>
struct print
{
   typedef typename vector<elem_type, simd>::type vtype; 

   static void apply(vtype v, const char* fmt=NULL)
   {
      elem_type vbuf[simd];
      *(vtype*)vbuf = v;

      // copy format string up to '%' to output
      const char *cp = fmt;
      while (cp && *cp && *cp != '%')
	 putchar(*cp++); 
      if (cp != fmt) printf(": "); 

      // parse number of bits, following '%'
      int bits = 40; 
      if (cp && *cp == '%' && isdigit(*(cp+1)))
	 bits = atoi(cp+1); 
      if (bits > 64) bits = 64;     // saturate to 64 for sanity
      uint64_t mask = (((uint64_t)1 << bits) - 1);

      // sign extend each value according to the element type,
      // mask to user's specified size, and print
      // only print up to VCOP_SIMD_WIDTH
      int length = simd < VCOP_SIMD_WIDTH ? simd : VCOP_SIMD_WIDTH;
      for (int i = 0; i < length; ++i) 
      {
	 uint64_t val = vbuf[i] & mask; 
	 printf("%0*lx", (bits/4), val); 
	 printf(" "); 
      }
      printf("\n"); 
   }
};
#endif

extern "C" {

/*****************************************************************************/
/* EXTERNS - C++ EH Compiler Helper Functions                                */
/*****************************************************************************/
void __cxa_call_unexpected(_Unwind_Exception *);

/*****************************************************************************/
/* EXTERNS - ASM Routine to copy register buffer regs into machine regs      */
/*****************************************************************************/
void  __TI_Install_CoreRegs(void *core_regs);

_Unwind_Reason_Code __TI_Unwind_RaiseException(_Unwind_Exception *uexcep, 
                                               _Unwind_Context  *ph2_context);

_Unwind_Reason_Code __TI_Unwind_RaiseException2(_Unwind_Exception *uexcep, 
                                                _Unwind_Context  *ph1_context,
                                                _Unwind_Context  *ph2_context);

/*****************************************************************************/
/* EXTERNS - printf, used only by debug                                      */
/*****************************************************************************/
#if defined(DEBUG_PR) || defined(DEBUG_UW_INSTRS)
#include <stdio.h>
#endif

#include <string.h>

}

/*****************************************************************************/
/* Functions used to access the Register Buffer                              */
/*****************************************************************************/
typedef enum { _URB_Failure=0, _URB_Success } _URB_Status;
static _URB_Status regb_core_get(_Unwind_Context *, _Unwind_Reg_Id, unsigned long *);
static _URB_Status regb_core_set(_Unwind_Context *, _Unwind_Reg_Id, unsigned long);

/*****************************************************************************/
/* Unwind Instr Handle  - Used to keep track of unwind instructions when a   */
/*                        frame is unwound. The function next_uw_byte uses   */
/*                        this struct to return the next unwind instr byte   */
/*****************************************************************************/
typedef struct
{
    _UINT32 *curr_pos;
    _UINT32  curr_word;

    _UINT32  words_remaining;
    _UINT32  bytes_remaining;
} _Unwind_Instr_Handle;

       static _UINT8  next_uw_byte(_Unwind_Instr_Handle *);
INLINE static _UINT32 read_uleb128(_Unwind_Instr_Handle *);

/*****************************************************************************/
/* Personality Routine  - main entry                                         */
/*****************************************************************************/
static _Unwind_Reason_Code __TI_unwind_cpp_pr(_Unwind_Phase      phase,
					      _Unwind_Exception *uexcep,
					      _Unwind_Context   *context,
					      _Unwind_PR_Kind    pr_kind);


extern bool __TI_process_descriptors(_Unwind_Phase        phase,
				_Unwind_Exception   *uexcep,
				_Unwind_Context     *context,
				_Unwind_PR_Kind      pr_kind,
				_UINT32             *descr_ptr,
				_Unwind_Reason_Code *reason,
				bool                *ph2_call_unexpected);


INLINE static _Unwind_Reason_Code process_unwind(_Unwind_Context *context, 
						 _Unwind_PR_Kind pr_kind, 
						 _UINT32 *estart_addr);

/*****************************************************************************/
/*                                                                           */
/* __c7xabi_unwind_cpp_pr0 - PR handling short frame unwinding, 16-bit scope */
/*                                                                           */
/*****************************************************************************/
_Unwind_Reason_Code __c7xabi_unwind_cpp_pr0 (_Unwind_Phase      phase,
					    _Unwind_Exception *uexcep, 
					    _Unwind_Context   *context)
{
    return __TI_unwind_cpp_pr(phase, uexcep, context, _UPK_Su16);
}

/*****************************************************************************/
/*                                                                           */
/* __c7xabi_unwind_cpp_pr1 - PR handling long frame unwinding, 16-bit scope  */
/*                                                                           */
/*****************************************************************************/
_Unwind_Reason_Code __c7xabi_unwind_cpp_pr1 (_Unwind_Phase      phase,
					    _Unwind_Exception *uexcep, 
					    _Unwind_Context   *context)
{
    return __TI_unwind_cpp_pr(phase, uexcep, context, _UPK_Lu16);
}

/*****************************************************************************/
/*                                                                           */
/* __c7xabi_unwind_cpp_pr2 - PR handling long frame unwinding, 32-bit scope  */
/*                                                                           */
/*****************************************************************************/
_Unwind_Reason_Code __c7xabi_unwind_cpp_pr2 (_Unwind_Phase      phase,
					    _Unwind_Exception *uexcep, 
					    _Unwind_Context   *context)
{
    return __TI_unwind_cpp_pr(phase, uexcep, context, _UPK_Lu32);
}

/*****************************************************************************/
/*                                                                           */
/* __c7xabi_unwind_cpp_pr3 - PR handling 24-bit encoding, 16-bit scope       */
/*                                                                           */
/*****************************************************************************/
_Unwind_Reason_Code __c7xabi_unwind_cpp_pr3 (_Unwind_Phase      phase,
					    _Unwind_Exception *uexcep, 
					    _Unwind_Context   *context)
{
    return __TI_unwind_cpp_pr(phase, uexcep, context, _UPK_PR3);
}

/*****************************************************************************/
/*                                                                           */
/* __TI_unwind_cpp_pr - Implements pr0 - pr3.                                */
/*                      The personality routine for a frame is used by the   */
/*                      language-independent unwinder to:                    */
/*                      (1) Detect whether a barrier to exception propagation*/
/*                          exists in a given frame - Phase 1                */
/*                      (2) Set up internal state to perform the actual      */
/*                          unwinding i.e set up registers to invoke         */
/*                          cleanup/catch handlers for the frame, remove the */
/*                          frame from the stack using unwind instructions - */
/*                          Phase 2                                          */
/*                                                                           */
/*****************************************************************************/
static _Unwind_Reason_Code __TI_unwind_cpp_pr(_Unwind_Phase      phase,
					      _Unwind_Exception *uexcep,
					      _Unwind_Context   *context,
					      _Unwind_PR_Kind    pr_kind)
{
    _UINT32 *estart_addr;
    _UINT32 *descr_ptr;

    bool ph2_call_unexpected = false;

    /*-----------------------------------------------------------------------*/
    /* If the phase or pr_kind is not supported, return failure              */
    /*-----------------------------------------------------------------------*/
    if (phase != _UP_Phase1 && phase != _UP_Phase2_Start && 
	phase != _UP_Phase2_Resume)
	return _URC_FAILURE;
    if (pr_kind != _UPK_Su16 && pr_kind != _UPK_Lu16 && pr_kind != _UPK_Lu32 &&
	pr_kind != _UPK_PR3)
	return _URC_FAILURE;

    estart_addr = uexcep->pr_data.eht_start;
    
    #ifdef DEBUG_PR
    printf("PR: U %lx, uw exception object\n", uexcep);
    printf("PR: Kind %d, Phase %d, Fn Start %lx, EHT Start %p\n", 
	    pr_kind, phase, uexcep->pr_data.func_start, estart_addr);
    #endif /* DEBUG_PR */

    /*-----------------------------------------------------------------------*/
    /* Process descriptors if the EHT is not an inline EHT - inline EHTs do  */
    /* not have descriptors, only unwind instructions. Bit 0 of the          */
    /* additional field in pr_data is set to 1 if the EHT is inline          */
    /*-----------------------------------------------------------------------*/
    if ((uexcep->pr_data.additional & 1) != 1)
    {
        #ifdef DEBUG_PR
	printf("PR: Looking for process descriptors\n");
        #endif /* DEBUG_PR */

	/*-------------------------------------------------------------------*/
	/* Compute address to start processing descriptors from, this depends*/
	/* on the phase: Phase1, Phase2 start, compute from start of EHT     */
	/* Phase2 resume, restore saved value                                */
	/*-------------------------------------------------------------------*/
	if (phase == _UP_Phase1 || phase == _UP_Phase2_Start)
	{
	    _UINT8 additional_words = 0;

	    /*---------------------------------------------------------------*/
	    /* If long unwind format, compute additional words to skip over  */
	    /*---------------------------------------------------------------*/
	    if (pr_kind == _UPK_Lu16 || pr_kind == _UPK_Lu32)
		additional_words = (*estart_addr & 0x00ff0000) >> 16;

            #ifdef DEBUG_PR
	    printf("PR: Unwinding uses %d addl words\n", additional_words);
            #endif /* DEBUG_PR */

	    descr_ptr = estart_addr + 1 + additional_words;
	}
	else
	    descr_ptr = (_UINT32*)uexcep->cleanup_data.cleanup_ehtp;

	_Unwind_Reason_Code reason;
	if (__TI_process_descriptors(phase, uexcep, context, pr_kind, 
                                     descr_ptr, &reason, 
                                     &ph2_call_unexpected))
	{
            #ifdef DEBUG_PR
            printf("PR: __TI_unwind_cpp_pr returning because"
                   " a descriptor was found\n");
            #endif /* DEBUG_PR */

	    return reason;
	}
    }

    /*-----------------------------------------------------------------------*/
    /* Process unwind instructions                                           */
    /*-----------------------------------------------------------------------*/
    if (process_unwind(context, pr_kind, estart_addr) == _URC_FAILURE)
    {
	#ifdef DEBUG_PR
	printf("PR: __TI_unwind_cpp_pr returning because"
               " process_unwind returned _URC_FAILURE\n"); 
	#endif /* DEBUG_PR */
        
	return _URC_FAILURE;
    }

    /*-----------------------------------------------------------------------*/
    /* If fespec forms a propagation barrier, and __cxa_call_unexpected has  */
    /* to be called, perform setup required                                  */
    /*-----------------------------------------------------------------------*/
    if (ph2_call_unexpected)
    {
	#ifdef DEBUG_PR
	printf("PR: Phase 2 FEspec barrier, calling __cxa_call_unexpected\n"); 
	#endif /* DEBUG_PR */

        /*-------------------------------------------------------------------*/
        /* Copy this PC value into RETA to set up the return address for the */
        /* call to __cxa_call_unexpected. From Section 8.5.3, any permitted  */
        /* throw out of unexpected() must behave as if unwinding resumes at  */
        /* the call site to the func whose exception spec was violated.      */
        /*-------------------------------------------------------------------*/
        unsigned long pc;
        regb_core_get(context, _UR_PC, &pc);
        regb_core_set(context, _UR_RP, (unsigned long)pc);

	/*-------------------------------------------------------------------*/
	/* Set A4, PC to call __cxa_call_unexpected                          */
	/*-------------------------------------------------------------------*/

	regb_core_set(context, _UR_PC, (unsigned long)&__cxa_call_unexpected);
	regb_core_set(context, _UR_A4, (unsigned long)uexcep);

	return _URC_INSTALL_CONTEXT;
    }

    /*-----------------------------------------------------------------------*/
    /* If we get here, ask the unwinder to process the next frame            */
    /*-----------------------------------------------------------------------*/
    return _URC_CONTINUE_UNWIND;
}

/*****************************************************************************/
/*                                                                           */
/* setup_uh - Set up unwinder instruction handle based on PR kind.           */
/*                                                                           */
/*****************************************************************************/
INLINE static void setup_uh(_Unwind_PR_Kind pr_kind, _UINT32 *estart_addr,
                            _Unwind_Instr_Handle *uh)
{
    /*-----------------------------------------------------------------------*/
    /* For PR3, the lower 24 bits are interpreted as a combined  instrucion. */
    /* For Lu16 and Lu32, bits 16-23 contain a count of the  number of       */
    /* additional 4-byte words.                                              */
    /*-----------------------------------------------------------------------*/
    uh->curr_pos = estart_addr;

    _UINT32 tmp = *estart_addr;

    if (pr_kind == _UPK_PR3)
    {
	uh->words_remaining = 0;
	uh->curr_word       = tmp & 0xffffff;
    }
    else if (pr_kind == _UPK_Su16)
    {
	uh->words_remaining = 0;
	uh->bytes_remaining = 3;
	uh->curr_word       = tmp << 8;
    }
    else
    {
	uh->words_remaining = (tmp & 0x00ff0000) >> 16;
	uh->bytes_remaining = 2;
	uh->curr_word       = tmp << 16;
    }
}

/*---------------------------------------------------------------------------*/
/* Printable names of the registers.                                         */
/*---------------------------------------------------------------------------*/
#ifdef DEBUG_UW_INSTRS
static const char *name_from_id_data[] = 
{ 
    "A8",  "A9",  
    "A10", "A11", "A12", "A13", "A14", "A15",
    "RP",  	
    "VB15", "B15", "VB14", "B14"
};

#define name_from_id(id) name_from_id_data[id]
#endif /* DEBUG_UW_INSTRS */

/*---------------------------------------------------------------------------*/
/* "id_from_F4" tells us how to interpret the 4-bit field in unwinding that  */
/* represent the different registers.  Returns an _Unwind_Reg_Id that        */
/* corresponds to a register in the _Unwind_Register_Buffer.                 */
/*---------------------------------------------------------------------------*/
static _Unwind_Reg_Id id_from_F4[] =
{
    _UR_RP,
    _UR_A15,
    _UR_A14, 
    _UR_A13,
    _UR_A12,
    _UR_A11,
    _UR_A10,
    _UR_A9,
    _UR_A8
};
                    
/*****************************************************************************/
/*                                                                           */
/* process_unwind_pop_bitmask - handle bitmasks for POP unwind instrucions   */
/*                                                                           */
/*****************************************************************************/
static void process_unwind_pop_bitmask(_Unwind_Context *context, 
                                       _Unwind_PR_Kind  pr_kind,
                                       _UINT32          mask,
                                       bool             compact_frame)
{     
    unsigned long rval;

#define BM_BITS 13
#define BM_IS_SAVED(BM, mask) (mask & (1 << ((BM_BITS - 1) - BM)))
#define ID_IS_SCALAR_REG(ID)  ((ID >= _UR_A8 && ID <= _UR_RP) || ID == _UR_B15 || ID == _UR_B14)
#define ID_IS_VECTOR_REG(ID)  ((ID == _UR_VB15 || ID == _UR_VB14))

    /*-----------------------------------------------------------------------*/
    /* First, implicitly increment the stack. For this, we will need to      */
    /* know the size of the SOE save area.                                   */
    /*-----------------------------------------------------------------------*/
    int reg_count = 0;

    for (unsigned int BM = 0; BM < BM_BITS; BM++)
        if (BM_IS_SAVED(BM, mask)) {
           reg_count++;
         }

    #ifdef DEBUG_UW_INSTRS
    printf("PUW: PR%d: POP bitmask %d registers%s\n", 
           pr_kind, reg_count,
           compact_frame ? ", compact frame" : "");
    #endif /* DEBUG_UW_INSTRS */

    _UINT32 addend = 0;

    /*----------------------------------------------------------------------*/
    /* Loop over the bits in the bitmask from right to left. Determine the  */
    /* size of the register and increment SP accordingly. The "implicit" SP */
    /* increment done here sets the SP to SP + SOE_SAVE_SIZE, bringing SP   */
    /* back to the caller's frame.                                          */
    /*                                                                      */
    /* POP Bitmask: 01xx xxxx xxxx xxxx.                                    */
    /* Where 'x' represents whether or not a register needs to be restored. */
    /* The ordering (from left to right) is the TDEH safe order.            */
    /* TDEH safe order: A8-A15,RP,VB15,B15,VB14,B14. Note: we can have      */
    /* either the scalar or vector portion of VB14/15, but not both.        */
    /*----------------------------------------------------------------------*/

    for (unsigned int i = 0; i < BM_BITS; i++)
    {
        unsigned int BM = BM_BITS - i - 1;

        if (BM_IS_SAVED(BM, mask))
        {
            int id = i;

            if(ID_IS_SCALAR_REG(id))
            {
                addend += 8;
            }
            else if (ID_IS_VECTOR_REG(id))
                addend += __C7X_VEC_SIZE_BYTES__;
        }
    }
    
    /*-----------------------------------------------------------------------*/
    /* Update the SP value in the _Unwind_Register_Buffer.                   */
    /*-----------------------------------------------------------------------*/    
    regb_core_get(context, _UR_SP, &rval);
    regb_core_set(context, _UR_SP, rval + addend);
  
    #ifdef DEBUG_UW_INSTRS
     printf("PUW: PR%d: implicit SP += %u [%#lx]\n", 
           pr_kind, addend, rval + addend);
    #endif /* DEBUG_UW_INSTRS */
    
    /*-----------------------------------------------------------------------*/
    /* Now pop each register.                                                */
    /*-----------------------------------------------------------------------*/
    _Unwind_Register_Buffer *reg_buf = (_Unwind_Register_Buffer*)(context); 
 
    /*-----------------------------------------------------------------------*/
    /* Grab a copy of SP. We will need to traverse the stack without         */
    /* changing the value of SP in the unwind register buffer.               */
    /* To begin saving SOEs, VSP must be incremented by 16 bytes as SOEs are */
    /* saved in the open 16 byte block that SP points to at all times.       */
    /*-----------------------------------------------------------------------*/
    unsigned long *vsp = (unsigned long *)reg_buf->SP + 2; 

    /*-----------------------------------------------------------------------*/
    /* Iterate over the bitmask ordering and save the values of the SOE      */
    /* registers into the _Unwind_Register_Buffer.                           */
    /*-----------------------------------------------------------------------*/
    int pos = 0;

     for (int i = 0; i < BM_BITS; i++)
     {
        unsigned int BM = BM_BITS - i - 1;

        if (BM_IS_SAVED(BM, mask))
        {
            if(i >= _UR_A8 && i <= _UR_RP)
            {
                pos++; //increment to grab incoming scalar reg
                reg_buf->core[i] = *(vsp-pos);            
            }
            else if(i == _UR_VB15) 
            { 
                 pos += __C7X_VEC_SIZE_BITS__/64;
                 reg_buf->vec_vb15 = __as_long8(*((uchar64*)(vsp - pos)));
            }
            else if(i == _UR_VB14)
            {
                 pos += __C7X_VEC_SIZE_BITS__/64;
                 reg_buf->vec_vb14 = __as_long8(*((uchar64*)(vsp - pos)));
            }
            else if(i == _UR_B15)
            {
                 pos++;
                 unsigned long scalar_portion = *(vsp - pos); //grab lane 0 which is first 64 bits
                 reg_buf->vec_vb15.s0 = scalar_portion;
            }
            else if(i == _UR_B14)
            {
                  pos++;
                  unsigned long scalar_portion = *(vsp - pos); //grab lane 0 which is first 64 bits
                  reg_buf->vec_vb14.s0 = scalar_portion;
            }
          
             #ifdef DEBUG_UW_INSTRS
                printf("PUW: PR%d: POP: %s = *SP[-%d] (*(%#lx) == %#lx)\n",
                   pr_kind, name_from_id(i), i, vsp - pos, *(vsp - pos));
             #endif  
         }
      }
}

/*****************************************************************************/
/*                                                                           */
/* process_unwind_pr3 - handle the compact PR3 encoding                      */
/*                                                                           */
/*****************************************************************************/
static void process_unwind_pr3(_Unwind_Context *context, 
                                   _Unwind_PR_Kind  pr_kind, 
                                   _UINT32         *estart_addr)
{
    _Unwind_Instr_Handle uh;

    unsigned long rval;

    setup_uh(pr_kind, estart_addr, &uh);

    /*-----------------------------------------------------------------------*/
    /* PR3 packs three things into 24 bits: an SP increment, a               */
    /* register pop bitmask, and a register which holds the return address.  */
    /*-----------------------------------------------------------------------*/

    /*-----------------------------------------------------------------------*/
    /* If the return address is in an SOE register, move it to RP.  This     */
    /* needs to be done before the SOE register is overwritten.              */
    /*-----------------------------------------------------------------------*/
    _Unwind_Reg_Id reg_id = id_from_F4[uh.curr_word & 0xf];

    if (reg_id != _UR_RP)
    {
        regb_core_get(context, reg_id, &rval);
        regb_core_set(context, _UR_RP, rval);

        #ifdef DEBUG_UW_INSTRS
        printf("PUW: PR%d: MVC %s, RP [%#lx]\n", 
               pr_kind, name_from_id(reg_id), rval);
        #endif /* DEBUG_UW_INSTRS */
    }

    /*-----------------------------------------------------------------------*/
    /* Perform the stack increment.      .                                   */
    /*-----------------------------------------------------------------------*/
    _UINT32 sp_inc_bits = uh.curr_word >> 17;

        _UINT32 addend = sp_inc_bits << 3;
        
        regb_core_get(context, _UR_SP, &rval);
        regb_core_set(context, _UR_SP, rval + addend);

        #ifdef DEBUG_UW_INSTRS
        printf("PUW: PR%d: SP += (%u << 3) [%#lx]\n", 
               pr_kind, sp_inc_bits, rval + addend);
        #endif /* DEBUG_UW_INSTRS */

    /*-----------------------------------------------------------------------*/
    /* POP SOE registers. Bitmask sits in bits 4-16 in PR3.                  */
    /*-----------------------------------------------------------------------*/
    unsigned int mask = (uh.curr_word >> 4) & 0x1fff; 

    /*-----------------------------------------------------------------------*/
    /* The bitmask for PR3 is the same order as the bitmask for the          */
    /* POP BITMASK unwind instruction.                                       */
    /*-----------------------------------------------------------------------*/
    process_unwind_pop_bitmask(context, pr_kind, mask, 
                               pr_kind == _UPK_PR3);

    /*-----------------------------------------------------------------------*/
    /* Return through RETA                                                   */
    /*-----------------------------------------------------------------------*/

    regb_core_get(context, _UR_RP, &rval);
    
    regb_core_set(context, _UR_PC, rval);

    #ifdef DEBUG_UW_INSTRS
    printf("PUW: PR%d: RET [%#lx]\n", pr_kind, rval + addend);
    #endif /* DEBUG_UW_INSTRS */
}

/*****************************************************************************/
/*                                                                           */
/* process_unwind - decode and simulate frame unwinding instructions.        */
/*                  PR0-2 only.                                              */
/*                                                                           */  
/*****************************************************************************/
INLINE static _Unwind_Reason_Code process_unwind(_Unwind_Context *context, 
						 _Unwind_PR_Kind  pr_kind, 
						 _UINT32         *estart_addr)
{
    #ifdef DEBUG_UW_INSTRS
    printf("PUW: Entering process_unwind\n");
    #endif /* DEBUG_UW_INSTRS */

    _Unwind_Instr_Handle uh;

    _UINT8 uw_byte;
    _UINT8 uw_next_byte;

    setup_uh(pr_kind, estart_addr, &uh);

    unsigned long rval;

    /*-----------------------------------------------------------------------*/
    /* Process unwind instructions                                           */
    /*-----------------------------------------------------------------------*/
    if (pr_kind == _UPK_PR3)
    {
        process_unwind_pr3(context, pr_kind, estart_addr);
    }
    else while (1)
    {
	uw_byte = next_uw_byte(&uh);
          
        /*-------------------------------------------------------------------*/
        /* 0xxx xxxx -> SP = SP + (xxxxxxx << 3) + 8 [0x08-0x400]	     */
        /*-------------------------------------------------------------------*/
	if ((uw_byte & 0x80) == 0x00)
	{
            _UINT32 sp_inc_bits = uw_byte & 0x7f; // 0x7f = ~0x80
            _UINT32 addend = (sp_inc_bits << 3) + 8;
	
            regb_core_get(context, _UR_SP, &rval);
            regb_core_set(context, _UR_SP, rval + addend);

	    #ifdef DEBUG_UW_INSTRS
	    printf("PUW: SP += (%d << 3) + 8, [%#lx]\n", 
                   sp_inc_bits, rval + addend);
	    #endif /* DEBUG_UW_INSTRS */

	    continue;
	}

        /*-------------------------------------------------------------------*/
        /* 1110 xxxx -> RET or MVC SOE, RP                                   */
        /*-------------------------------------------------------------------*/
	else if ((((uw_byte >> 4) & 0xd) == 0xd) || uw_byte == UWINS_FINISH)
	{  
           /*-----------------------------------------------------------*/
           /* A stream of unwinding instructions ends with an explicit  */
           /* or implicit RET.  Implicit RET is always interpreted as   */
           /* "FINISH," which is just "RET."  next_uw_byte() returns    */
           /* "FINISH" when there are no more bytes available. We only  */
           /* need to handle the case where MVC SOE, RP is needed.      */
           /*-----------------------------------------------------------*/

            unsigned int check  = uw_byte & 0xf; //grab lower 4 bits

            _Unwind_Reg_Id id = id_from_F4[check];
	   
            /*-----------------------------------------------------------*/
            /* Check to see if 4 bit encoding is RP's 4 bit encoding.    */
            /* If the encoding is not 0 (RP's encoding), we must move    */
            /* the return address from an SOE into RP before overwriting */
            /* the SOE in the POP Bitmask function. The 4-bit encoding   */
            /* encodes which register to use.                            */
            /*-----------------------------------------------------------*/

            if (id != _UR_RP)
	    {
                /*-----------------------------------------------------------*/
                /* This is "MVC SOE, RP" instruction. Set RP using correct   */
                /* SOE. If lower bits = 0, then RP is already set.           */
                /*-----------------------------------------------------------*/
		 
                regb_core_get(context, id, &rval);
		regb_core_set(context, _UR_RP, rval);

                #ifdef DEBUG_UW_INSTRS
		printf("PUW: MVC %s, RP [%#lx]\n", name_from_id(id), rval);
                #endif /* DEBUG_UW_INSTRS */
	    }
	    else
	    {
                /*-----------------------------------------------------------*/
                /* This is a "RET" instruction. Set PC and return.           */
                /*-----------------------------------------------------------*/
                regb_core_get(context, id, &rval); 
                regb_core_set(context, _UR_PC, rval);

                #ifdef DEBUG_UW_INSTRS
                printf("PUW: RET\n");
                #endif /* DEBUG_UW_INSTRS */

                /*-----------------------------------------------------------*/
                /* Once we've seen a RET, we are done. Exit the loop.        */
                /*-----------------------------------------------------------*/
		break;
	    }
	}

	/*-------------------------------------------------------------------*/
        /* 1110 0001 CANTUNWIND		                  		     */
        /*-------------------------------------------------------------------*/
        else if (uw_byte == 0xe1)
        {
            #ifdef DEBUG_UW_INSTRS
	    printf("PUW: CANTUNWIND\n");
            #endif /* DEBUG_UW_INSTRS */

            return _URC_FAILURE;
        }

        /*-------------------------------------------------------------------*/
        /* 10xx xxxx xxxx xxxx POP bitmask. Order from right to left:        */
        /* A8-A15,RP,VB15,B15,VB14,B15                                       */
	/*-------------------------------------------------------------------*/
	else if ((uw_byte & 0xc0) == 0x80)
	{
            uw_next_byte = next_uw_byte(&uh);
            
            unsigned int mask = (uw_byte << 8) | uw_next_byte;

            process_unwind_pop_bitmask(context, pr_kind, mask, false);
	}

        /*-------------------------------------------------------------------*/
        /* 1010 0000 0000 0000 reserved					     */
        /*-------------------------------------------------------------------*/

        /*-------------------------------------------------------------------*/
        /* 1110 0000 kkkk ... -> SP += (ULEB128 << 3) + 0x408 [0x408-max]    */
        /*-------------------------------------------------------------------*/
	else if (uw_byte == 0xe0)
	{
	    _UINT32 sp_inc_bits = read_uleb128(&uh);
            _UINT32 addend = (sp_inc_bits << 3) + 0x408;

 	    regb_core_get(context, _UR_SP, &rval);
	    regb_core_set(context, _UR_SP, rval + addend);

	    #ifdef DEBUG_UW_INSTRS
	    printf("PUW: SP += (%u << 3) + 0x408, [%#lx]\n", 
		   sp_inc_bits, rval + addend);
	    #endif /* DEBUG_UW_INSTRS */
	}

	/*-------------------------------------------------------------------*/
	/* If we get here, the instruction is spare/invalid                  */
	/*-------------------------------------------------------------------*/
	else
	{
	    #ifdef DEBUG_UW_INSTRS
	    printf("PUW: Instr not supported [%#x]\n", uw_byte);
	    #endif /* DEBUG_UW_INSTRS */
	    return _URC_FAILURE;
        }
    }

    #ifdef DEBUG_UW_INSTRS
    printf("PUW: Leaving process_unwind\n");
    #endif /* DEBUG_UW_INSTRS */

    return _URC_CONTINUE_UNWIND;
}


/*****************************************************************************/
/*                                                                           */
/* next_uw_byte - Returns the next unwind instruction or FINISH (aka RET)    */
/*                if there are no instructions remaining.                    */
/*                                                                           */
/*****************************************************************************/
static _UINT8 next_uw_byte(_Unwind_Instr_Handle *uwh)
{
    _UINT8 uw_byte;

    if (uwh->bytes_remaining == 0)
    {
	if (uwh->words_remaining == 0)
	    return UWINS_FINISH;
	else
	{
	    uwh->curr_word = *(++uwh->curr_pos);
	    uwh->words_remaining--;
	    uwh->bytes_remaining = 4;
	}
    }

    uw_byte = (uwh->curr_word & 0xff000000) >> 24;
    uwh->curr_word <<= 8;
    uwh->bytes_remaining--;

    return uw_byte;
}


/*****************************************************************************/
/*                                                                           */
/* read_uleb128 - Read a ULEB128 encoded offset stored in the unwind area    */
/*                                                                           */
/*****************************************************************************/
INLINE static _UINT32 read_uleb128(_Unwind_Instr_Handle *uh)
{
    _UINT8  uw_byte;
    _UINT32 val       = 0;
    _UINT8  shift_amt = 0;

    while (1)
    {
	uw_byte = next_uw_byte(uh);
	val |= (uw_byte & 0x7f) << shift_amt;
	/*-------------------------------------------------------------------*/
	/* The last group does not have MSB set to 1                         */
	/*-------------------------------------------------------------------*/
	if ((uw_byte & 0x80) == 0) break;
	shift_amt += 7;
    }
    return val;
}


/*****************************************************************************/
/*                                                                           */
/* regb_core_get - Updates "val" with value stored in register "index"       */
/*                 This function cannot grab vector registers as this        */  
/*                 functionality is not needed in this way.                  */
/*                                                                           */
/*****************************************************************************/
static _URB_Status regb_core_get(_Unwind_Context *context, 
			         _Unwind_Reg_Id  index, 
				 unsigned long       *val)
{
    _Unwind_Register_Buffer *reg_buf = (_Unwind_Register_Buffer*)(context);

   //Registers stored in core array: A8-A15, RP
   int num_core = sizeof(reg_buf->core)/sizeof(reg_buf->core[0]);

   if(index < num_core)
       *val = reg_buf->core[index];
   else if(index == _UR_SP)
       *val = reg_buf->SP;
   else if(index == _UR_PC)
       *val = reg_buf->PC;
   else if(index == _UR_A4)
       *val = reg_buf->A4;
   else
       return _URB_Failure;

    return _URB_Success;
}

/*****************************************************************************/
/*                                                                           */
/* regb_core_set - Update value stored in register "index" using val.        */
/*                 This function cannot set a vector registers as this       */  
/*                 functionality is not needed in this way.                  */
/*                                                                           */
/*****************************************************************************/
static _URB_Status regb_core_set(_Unwind_Context *context, 
				 _Unwind_Reg_Id  index, 
				 unsigned long        val)
{
    _Unwind_Register_Buffer *reg_buf = (_Unwind_Register_Buffer*)(context);

   //Registers stored in core array: A8-A15, RP
   int num_core = sizeof(reg_buf->core)/sizeof(reg_buf->core[0]);

   if(index < num_core)
       reg_buf->core[index] = val;
   else if (index == _UR_SP)
       reg_buf->SP = val;
   else if (index == _UR_PC)
       reg_buf->PC = val;
   else if (index == _UR_A4)
       reg_buf->A4 = val;
   else
       return _URB_Failure;

   return _URB_Success;
}

/*****************************************************************************/
/*                                                                           */
/* __TI_targ_set_pr - Compute PR address from the EHT (extab), update UE     */
/*                                                                           */
/*****************************************************************************/
bool __TI_targ_set_pr(_Unwind_Exception *uexcep)
{
    if (uexcep->pr_data.eht_start == (void *)0) return false;

    /*-----------------------------------------------------------------------*/
    /* The first word of the EHT encodes PR variant used to process eht      */
    /*-----------------------------------------------------------------------*/
    _UINT32 eht_first_word = *(uexcep->pr_data.eht_start);
    
    #ifdef DEBUG_UNWINDER
    printf("UW: EHT First Word %08x, PR %d\n", 
	    eht_first_word, (eht_first_word & 0x0f000000) >> 24);
    fflush(stdout);
    #endif /* DEBUG_UNWINDER */

    /*-----------------------------------------------------------------------*/
    /* If MSB==1, Bits 27-24 contain index of PR used                        */
    /*-----------------------------------------------------------------------*/
    if ((eht_first_word & 0x80000000) != 0)
    {
        #ifdef DEBUG_UNWINDER
        printf("UW: (Compact) EHT First Word %08x, PR %d\n", 
               eht_first_word, (eht_first_word & 0x0f000000) >> 24);
        #endif /* DEBUG_UNWINDER */
        
	switch ((eht_first_word & 0x0f000000) >> 24)
	{
           case 0: 
		uexcep->unwinder_data.pr_addr = 
					    (unsigned long)&__c7xabi_unwind_cpp_pr0;
		break;
	    case 1: 
		uexcep->unwinder_data.pr_addr = 
					    (unsigned long)&__c7xabi_unwind_cpp_pr1;
		break;
	    case 2: 
		uexcep->unwinder_data.pr_addr = 
					    (unsigned long)&__c7xabi_unwind_cpp_pr2;
		break;
	    case 3: 
		uexcep->unwinder_data.pr_addr = 
					    (unsigned long)&__c7xabi_unwind_cpp_pr3;
		break;
	    default:
		return false;

	}
    }
    /*-----------------------------------------------------------------------*/
    /* If MSB==0, Bits 30-0 contain the PR offset, conv from segrel to abs   */
    /*-----------------------------------------------------------------------*/
    else
    {
    
    uexcep->unwinder_data.pr_addr =__TI_prel2abs(uexcep->pr_data.eht_start); //pass in address of first word
    #ifdef DEBUG_UNWINDER
    printf("UW: (Generic) EHT First Word %08x, (addr %lx)\n", 
	   eht_first_word, uexcep->unwinder_data.pr_addr);
    #endif /* DEBUG_UNWINDER */

    }

    return true;
}


/*****************************************************************************/
/*                                                                           */
/* __TI_targ_regbuf_get_sp - Return SP from RegBuffer pointed to by context  */
/*                                                                           */
/*****************************************************************************/
REG_SIZE __TI_targ_regbuf_get_sp(_Unwind_Context *context)
{
    _Unwind_Register_Buffer *regbuf = (_Unwind_Register_Buffer*)(context);
    return regbuf->SP;
}


/*****************************************************************************/
/*                                                                           */
/* __TI_targ_regbuf_get_pc - Return PC from RegBuffer pointed to by context  */
/*                                                                           */
/*****************************************************************************/
REG_SIZE __TI_targ_regbuf_get_pc(_Unwind_Context *context)
{
    _Unwind_Register_Buffer *regbuf = (_Unwind_Register_Buffer*)(context);
    return regbuf->PC;
}


/*****************************************************************************/
/*                                                                           */
/* __TI_targ_regbuf_set_pc - Store into RegBuffer PC pointed by context      */
/*                                                                           */
/*****************************************************************************/
void __TI_targ_regbuf_set_pc(_Unwind_Context *context, REG_SIZE val)
{
    _Unwind_Register_Buffer *regbuf = (_Unwind_Register_Buffer*)(context);
    regbuf->PC = val; 
    return;
}

/*****************************************************************************/
/* __TI_targ_regbuf_get_sb                                                   */
/*****************************************************************************/
_UINT32 __TI_targ_regbuf_get_sb(_Unwind_Context *context)
{
    //_Unwind_Register_Buffer *regbuf = (_Unwind_Register_Buffer*)context;
    return 0;
}

/*****************************************************************************/
/*                                                                           */
/* __TI_targ_rtti_address - Return address of referenced typeinfo object     */
/*                                                                           */
/*****************************************************************************/
REG_SIZE __TI_targ_rtti_address(_UINT32 *offset, _Unwind_Context *context)
{
    return __TI_prel2abs(offset);
}

/*****************************************************************************/
/*                                                                           */
/* __TI_targ_regbuf_install - Copy RegBuffer into machine registers          */
/*                                                                           */
/*****************************************************************************/
void __TI_targ_regbuf_install(_Unwind_Context *context)
{
    _Unwind_Register_Buffer *regbuf = (_Unwind_Register_Buffer*)context;
    
    __TI_Install_CoreRegs(regbuf);
    /*************************************************************************/
    /* __TI_Install_CoreRegs transfers control out of the unwinder.  Do not  */
    /* add any code after this point.  It will not be executed.              */
    /*************************************************************************/
}


/*****************************************************************************/
/*                                                                           */
/* __TI_targ_setup_call_parm0 - Set up register buffer to make "val" the     */
/*                              first parameter to a function whose address  */
/*                              will be stored in the register buffer PC     */
/*                                                                           */
/*****************************************************************************/
void __TI_targ_setup_call_parm0(_Unwind_Context *context, REG_SIZE val)
{
    _Unwind_Register_Buffer *regbuf = (_Unwind_Register_Buffer*)(context);
    regbuf->A4 = val; 
    return;
}

/*****************************************************************************/
/*                                                                           */
/* __TI_Unwind_RaiseException - This function exists to allocate the         */
/*          register context for __TI_Unwind_RaiseException2, which does     */
/*          all of the work, but doesn't need to know the size of the        */
/*          register context.                                                */
/*                                                                           */
/*****************************************************************************/
_Unwind_Reason_Code __TI_Unwind_RaiseException(_Unwind_Exception *uexcep, 
					       _Unwind_Context   *ph2_context)
{
    #ifdef DEBUG_UNWINDER
    printf("UW: In __TI_Unwind_RaiseException, UE @ %p, ph2_context @ %p\n", 
           uexcep, ph2_context);
    __TI_dump_regbuf_context(ph2_context);
    #endif

    /*-----------------------------------------------------------------------*/
    /* Make a copy of the register context for use by the Phase 1 unwinder.  */
    /* This needs to be a copy because we're going to simulate unwinding by  */
    /* writing to it, and we don't want to scribble on the original yet.     */
    /* Phase 2 will use the original, since at that time we are committed    */
    /* to unwinding the frame.                                               */
    /*-----------------------------------------------------------------------*/
    _Unwind_Register_Buffer ph1_regs;
    _Unwind_Context *ph1_context = (_Unwind_Context *)&ph1_regs;

    memcpy(ph1_context, ph2_context, sizeof(_Unwind_Register_Buffer));

    return __TI_Unwind_RaiseException2(uexcep,
                                      ph1_context,
                                      ph2_context);
}

#ifdef DEBUG_UNWINDER
/*****************************************************************************/
/*                                                                           */
/* __TI_dump_regbuf_context - Helper function for debug                      */
/*                                                                           */
/*****************************************************************************/
void __TI_dump_regbuf_context(_Unwind_Context *context)
{
    _Unwind_Register_Buffer *regbuf = (_Unwind_Register_Buffer*)(context);

#define _SAVED_REG_FMT "lx"

    printf("UW:  A8:   %#" _SAVED_REG_FMT "\n", regbuf->core[_UR_A8]);
    printf("UW:  A9:   %#" _SAVED_REG_FMT "\n", regbuf->core[_UR_A9]);
    printf("UW:  A10:   %#" _SAVED_REG_FMT "\n", regbuf->core[_UR_A10]);
    printf("UW:  A11:   %#" _SAVED_REG_FMT "\n", regbuf->core[_UR_A11]);
    printf("UW:  A12:   %#" _SAVED_REG_FMT "\n", regbuf->core[_UR_A12]);
    printf("UW:  A13:   %#" _SAVED_REG_FMT "\n", regbuf->core[_UR_A13]);
    printf("UW:  A14:  %#" _SAVED_REG_FMT "\n", regbuf->core[_UR_A14]);
    printf("UW:  A15:  %#" _SAVED_REG_FMT "\n", regbuf->core[_UR_A15]);

    printf("UW:  RETA: %#" _SAVED_REG_FMT "\n", regbuf->core[_UR_RP]);

    /*----------------------------------------------------------------------*/
    /* These print functions display the data in the same way regardless of */
    /* endianess.                                                           */
    /*----------------------------------------------------------------------*/
    print<int64_t, __C7X_VEC_SIZE_BITS__/64>::apply(regbuf->vec_vb15, "UW:  VB15%64");
    print<int64_t, __C7X_VEC_SIZE_BITS__/64>::apply(regbuf->vec_vb14, "UW:  VB14%64");

    printf("UW:  SP:   %#" _SAVED_REG_FMT "\n", regbuf->SP);
    printf("UW:  PC:   %#" _SAVED_REG_FMT "\n", regbuf->PC);
    printf("UW:  A4:   %#" _SAVED_REG_FMT "\n", regbuf->A4);

}
#endif /* DEBUG_UNWINDER */



#endif /* __EXCEPTIONS */
