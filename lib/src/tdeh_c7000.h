/*****************************************************************************/
/*  tdeh_c7000.h                                                             */
/*  Copyright (c) 2016  Texas Instruments Incorporated                       */
/*                                                                           */
/*  Target-Specific header for Table-Driven Exception Handling               */
/*                                                                           */
/*****************************************************************************/
#ifndef _TDEH_C7000_H
#define _TDEH_C7000_H

#include <tdeh_common.h>

#ifdef __cplusplus
extern "C" {
#endif
    _Unwind_Reason_Code __c7xabi_unwind_cpp_pr0 (_Unwind_Phase      phase,
						 _Unwind_Exception *uexcep, 
						 _Unwind_Context   *context);
    _Unwind_Reason_Code __c7xabi_unwind_cpp_pr1 (_Unwind_Phase      phase,
						 _Unwind_Exception *uexcep, 
						 _Unwind_Context   *context);
    _Unwind_Reason_Code __c7xabi_unwind_cpp_pr2 (_Unwind_Phase      phase,
						 _Unwind_Exception *uexcep, 
						 _Unwind_Context   *context);
    _Unwind_Reason_Code __c7xabi_unwind_cpp_pr3 (_Unwind_Phase      phase,
						 _Unwind_Exception *uexcep, 
						 _Unwind_Context   *context);
#ifdef __cplusplus
}
#endif

/*---------------------------------------------------------------------------*/
/* UWINS_FINISH = RET (1101 0000 = 0xD0)                                     */
/*---------------------------------------------------------------------------*/
#define UWINS_FINISH	(0xd0)

/*---------------------------------------------------------------------------*/
/* TDEH SAVE ORDER                                                           */
/* A8, A9, A10, A11, A12, A13, A14, A15, RP, VB15/B15, VB14,B14              */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Register Buffer - Used to store copy of the machine regs during unwinding */
/* _Unwind_Context is an opaque handle used to access the register           */
/* buffer. The unwinder passes _Unwind_Context* to the personality routine.  */
/* _Unwind_Register_Buffer models how the registers are stored in memory and */
/* facilitates the access of each memory location.                           */
/*                                                                           */
/* "Core" is an array that represents the scalar registers A8-A15 and RP.    */
/* The first and last elements of core are the values of A8 and RP,          */
/* respectively.                                                             */
/*---------------------------------------------------------------------------*/
typedef struct
{
    unsigned long core[9];  
    __long8 vec_vb15;
    __long8 vec_vb14;
    unsigned long A4;
    unsigned long SP;
    unsigned long PC;
} _Unwind_Register_Buffer;

/*---------------------------------------------------------------------------*/
/* This enum establishes an ordering for the registers in the                */
/* _Unwind_Register_Buffer. This ordering matches the TDEH save order and    */
/* the ordering of the pop register bitmask.                                 */ 
/*---------------------------------------------------------------------------*/
typedef enum
{
  _UR_A8 = 0,
  _UR_A9,
  _UR_A10,
  _UR_A11,
  _UR_A12,
  _UR_A13,
  _UR_A14,
  _UR_A15,
  _UR_RP,   //8
  _UR_VB15, 
  _UR_B15,
  _UR_VB14,
  _UR_B14,
  _UR_A4,
  _UR_SP,
  _UR_PC,

  /*-------------------------------------------------------------------------*/
  /* Define offsets used to reference register locations within the          */
  /* _Unwind_Register_Buffer.                                                */
  /*-------------------------------------------------------------------------*/
  _UR_VB14_Offset = _UR_VB15 + (__C7X_VEC_SIZE_BITS__/64),
  _UR_A4_Offset =   _UR_VB14_Offset + (__C7X_VEC_SIZE_BITS__/64),
  _UR_SP_Offset =   _UR_A4_Offset + 1,
  _UR_PC_Offset =   _UR_SP_Offset + 1
} _Unwind_Reg_Id;

#endif /* _TDEH_C7000_H */
