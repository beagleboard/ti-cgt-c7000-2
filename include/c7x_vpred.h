/*****************************************************************************/
/*  C7X_VPRED.H                                                              */
/*                                                                           */
/* Copyright (c) 2015 Texas Instruments Incorporated                         */
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
#ifndef __C7X_H_INCLUDE__
#error "This file can only be included by parent header c7x.h"
#endif

#ifndef __C7X_VPRED_H
#define __C7X_VPRED_H

/*****************************************************************************/
/* CONVERT TO/FROM A VECTOR PREDICATE FROM/TO A BOOLEAN VECTOR               */
/*                                                                           */
/* Note: Because boolean vectors are always intepreted as vectors of single  */
/* 1-bit values, the corresponding "__vpred" must be interpreted as "char"   */
/* format.  This means that the bits are scaled for halfword, word, or long. */
/*****************************************************************************/
__bool2  __OVBIF __create_bool2(__vpred);
__bool3  __OVBIF __create_bool3(__vpred);
__bool4  __OVBIF __create_bool4(__vpred);
__bool8  __OVBIF __create_bool8(__vpred);
__bool16 __OVBIF __create_bool16(__vpred);
__bool32 __OVBIF __create_bool32(__vpred);
__bool64 __OVBIF __create_bool64(__vpred);

__vpred __OVBIF __create_vpred(__bool2);
__vpred __OVBIF __create_vpred(__bool3);
__vpred __OVBIF __create_vpred(__bool4);
__vpred __OVBIF __create_vpred(__bool8);
__vpred __OVBIF __create_vpred(__bool16);
__vpred __OVBIF __create_vpred(__bool32);
__vpred __OVBIF __create_vpred(__bool64);
__vpred __OVBIF __create_vpred(__ulong);

#define __create_vpred(a)  __overload("__create_vpred",(a))((a))

__ulong __OVBIF __create_scalar(__vpred);

/*****************************************************************************/
/* VECTOR PREDICATE TO REGISTER INTERFACE                                    */
/*****************************************************************************/
__vpred  __BIF _mvrp       (long);
long     __BIF _mvpb       (__vpred);
long     __BIF _mvph       (__vpred);
long     __BIF _mvpw       (__vpred);
long     __BIF _mvpd       (__vpred);

/*****************************************************************************/
/* VECTOR LOADS AND PREDICATED VECTOR LOADS                                  */
/*                                                                           */
/* On C7120 and later devices, implicit predication occurs on loads that use */
/* streaming address generator (SA) operands. If an SA may be used as an     */
/* operand to a load AND that SA may generate predicates with one or more    */
/* predicate bits off, then a predicated load must be used to avoid          */
/* unexpected behavior. Use the following idiom with implicitly predicated   */
/* SA loads:                                                                 */
/*                                                                           */
/* __vpred pred = __SA0_VPRED(char2);                                        */
/* char2 *ptr = __SA0ADV(char2, base_ptr);                                   */
/* char2 data = __vload_pred(pred, ptr);                                     */
/*                                                                           */
/* If implicit predication is not available (C7100), the idiom is malformed, */
/* or the compiler fails to optimize the idiom, an equivalent series of      */
/* instructions will instead be generated to load and then predicate.        */
/*****************************************************************************/
/* VLD2B, VLD4B, VLD8B, VLD16B, VLD32B, VLD64B */
__char2   __OVBIF __vload_pred(__vpred, __RD __const_char2_ptr);
__char4   __OVBIF __vload_pred(__vpred, __RD __const_char4_ptr);
__char8   __OVBIF __vload_pred(__vpred, __RD __const_char8_ptr);
__char16  __OVBIF __vload_pred(__vpred, __RD __const_char16_ptr);
__char32  __OVBIF __vload_pred(__vpred, __RD __const_char32_ptr);
__char64  __OVBIF __vload_pred(__vpred, __RD __const_char64_ptr);
__uchar2  __OVBIF __vload_pred(__vpred, __RD __const_uchar2_ptr);
__uchar4  __OVBIF __vload_pred(__vpred, __RD __const_uchar4_ptr);
__uchar8  __OVBIF __vload_pred(__vpred, __RD __const_uchar8_ptr);
__uchar16 __OVBIF __vload_pred(__vpred, __RD __const_uchar16_ptr);
__uchar32 __OVBIF __vload_pred(__vpred, __RD __const_uchar32_ptr);
__uchar64 __OVBIF __vload_pred(__vpred, __RD __const_uchar64_ptr);

/* VLD2H, VLD4H, VLD8H, VLD16H, VLD32H */
__short2   __OVBIF __vload_pred(__vpred, __RD __const_short2_ptr);
__short4   __OVBIF __vload_pred(__vpred, __RD __const_short4_ptr);
__short8   __OVBIF __vload_pred(__vpred, __RD __const_short8_ptr);
__short16  __OVBIF __vload_pred(__vpred, __RD __const_short16_ptr);
__short32  __OVBIF __vload_pred(__vpred, __RD __const_short32_ptr);
__ushort2  __OVBIF __vload_pred(__vpred, __RD __const_ushort2_ptr);
__ushort4  __OVBIF __vload_pred(__vpred, __RD __const_ushort4_ptr);
__ushort8  __OVBIF __vload_pred(__vpred, __RD __const_ushort8_ptr);
__ushort16 __OVBIF __vload_pred(__vpred, __RD __const_ushort16_ptr);
__ushort32 __OVBIF __vload_pred(__vpred, __RD __const_ushort32_ptr);

/* VLDHSWAPB */
__cchar   __OVBIF __vload_pred(__vpred, __RD __const_cchar_ptr);
__cchar2   __OVBIF __vload_pred(__vpred, __RD __const_cchar2_ptr);
__cchar4   __OVBIF __vload_pred(__vpred, __RD __const_cchar4_ptr);
__cchar8   __OVBIF __vload_pred(__vpred, __RD __const_cchar8_ptr);
__cchar16  __OVBIF __vload_pred(__vpred, __RD __const_cchar16_ptr);
__cchar32  __OVBIF __vload_pred(__vpred, __RD __const_cchar32_ptr);

/* VLD2W, VLD4W, VLD8W, VLD16W */
__int2   __OVBIF __vload_pred(__vpred, __RD __const_int2_ptr);
__int4   __OVBIF __vload_pred(__vpred, __RD __const_int4_ptr);
__int8   __OVBIF __vload_pred(__vpred, __RD __const_int8_ptr);
__int16  __OVBIF __vload_pred(__vpred, __RD __const_int16_ptr);
__uint2  __OVBIF __vload_pred(__vpred, __RD __const_uint2_ptr);
__uint4  __OVBIF __vload_pred(__vpred, __RD __const_uint4_ptr);
__uint8  __OVBIF __vload_pred(__vpred, __RD __const_uint8_ptr);
__uint16 __OVBIF __vload_pred(__vpred, __RD __const_uint16_ptr);
__float2   __OVBIF __vload_pred(__vpred, __RD __const_float2_ptr);
__float4   __OVBIF __vload_pred(__vpred, __RD __const_float4_ptr);
__float8   __OVBIF __vload_pred(__vpred, __RD __const_float8_ptr);
__float16  __OVBIF __vload_pred(__vpred, __RD __const_float16_ptr);

/* VLDWSWAPH */
__cshort   __OVBIF __vload_pred(__vpred, __RD __const_cshort_ptr);
__cshort2   __OVBIF __vload_pred(__vpred, __RD __const_cshort2_ptr);
__cshort4   __OVBIF __vload_pred(__vpred, __RD __const_cshort4_ptr);
__cshort8   __OVBIF __vload_pred(__vpred, __RD __const_cshort8_ptr);
__cshort16  __OVBIF __vload_pred(__vpred, __RD __const_cshort16_ptr);

/* VLD1D, VLD2D, VLD4D, VLD8D */
long    __OVBIF __vload_pred(__vpred, __RD const long*);
__long2   __OVBIF __vload_pred(__vpred, __RD __const_long2_ptr);
__long4   __OVBIF __vload_pred(__vpred, __RD __const_long4_ptr);
__long8   __OVBIF __vload_pred(__vpred, __RD __const_long8_ptr);
__ulong   __OVBIF __vload_pred(__vpred, __RD const __ulong*);
__ulong2  __OVBIF __vload_pred(__vpred, __RD __const_ulong2_ptr);
__ulong4  __OVBIF __vload_pred(__vpred, __RD __const_ulong4_ptr);
__ulong8  __OVBIF __vload_pred(__vpred, __RD __const_ulong8_ptr);
double   __OVBIF __vload_pred(__vpred, __RD const double*);
__double2   __OVBIF __vload_pred(__vpred, __RD __const_double2_ptr);
__double4   __OVBIF __vload_pred(__vpred, __RD __const_double4_ptr);
__double8   __OVBIF __vload_pred(__vpred, __RD __const_double8_ptr);

/* VLDDSWAPW */
__cint   __OVBIF __vload_pred(__vpred, __RD __const_cint_ptr);
__cint2   __OVBIF __vload_pred(__vpred, __RD __const_cint2_ptr);
__cint4   __OVBIF __vload_pred(__vpred, __RD __const_cint4_ptr);
__cint8   __OVBIF __vload_pred(__vpred, __RD __const_cint8_ptr);
__cfloat   __OVBIF __vload_pred(__vpred, __RD __const_cfloat_ptr);
__cfloat2   __OVBIF __vload_pred(__vpred, __RD __const_cfloat2_ptr);
__cfloat4   __OVBIF __vload_pred(__vpred, __RD __const_cfloat4_ptr);
__cfloat8   __OVBIF __vload_pred(__vpred, __RD __const_cfloat8_ptr);

/* VLDDUP2B, VLDDUP4B, VLDDUP8B, VLDDUP16B, VLDDUP32B, VLDDUP64B */
__char64      __OVBIF __vload_pred_dup(__vpred, __RD __const_char32_ptr);
__char64      __OVBIF __vload_pred_dup(__vpred, __RD __const_char16_ptr);
__char64      __OVBIF __vload_pred_dup(__vpred, __RD __const_char8_ptr);
__char64      __OVBIF __vload_pred_dup(__vpred, __RD __const_char4_ptr);
__char64      __OVBIF __vload_pred_dup(__vpred, __RD __const_char2_ptr);
__char64      __OVBIF __vload_pred_dup(__vpred, __RD const char*);
__uchar64     __OVBIF __vload_pred_dup(__vpred, __RD __const_uchar32_ptr);
__uchar64     __OVBIF __vload_pred_dup(__vpred, __RD __const_uchar16_ptr);
__uchar64     __OVBIF __vload_pred_dup(__vpred, __RD __const_uchar8_ptr);
__uchar64     __OVBIF __vload_pred_dup(__vpred, __RD __const_uchar4_ptr);
__uchar64     __OVBIF __vload_pred_dup(__vpred, __RD __const_uchar2_ptr);
__uchar64     __OVBIF __vload_pred_dup(__vpred, __RD __const_uchar_ptr);

/* VLDDUP2H, VLDDUP4H, VLDDUP8H, VLDDUP16H, VLDDUP32H */
__short32     __OVBIF __vload_pred_dup(__vpred, __RD __const_short16_ptr);
__short32     __OVBIF __vload_pred_dup(__vpred, __RD __const_short8_ptr);
__short32     __OVBIF __vload_pred_dup(__vpred, __RD __const_short4_ptr);
__short32     __OVBIF __vload_pred_dup(__vpred, __RD __const_short2_ptr);
__short32     __OVBIF __vload_pred_dup(__vpred, __RD const short*);
__ushort32    __OVBIF __vload_pred_dup(__vpred, __RD __const_ushort16_ptr);
__ushort32    __OVBIF __vload_pred_dup(__vpred, __RD __const_ushort8_ptr);
__ushort32    __OVBIF __vload_pred_dup(__vpred, __RD __const_ushort4_ptr);
__ushort32    __OVBIF __vload_pred_dup(__vpred, __RD __const_ushort2_ptr);
__ushort32    __OVBIF __vload_pred_dup(__vpred, __RD __const_ushort_ptr);

/* VLDDUP2W, VLDDUP4W, VLDDUP8W, VLDDUP16W */
__int16       __OVBIF __vload_pred_dup(__vpred, __RD __const_int8_ptr);
__int16       __OVBIF __vload_pred_dup(__vpred, __RD __const_int4_ptr);
__int16       __OVBIF __vload_pred_dup(__vpred, __RD __const_int2_ptr);
__int16       __OVBIF __vload_pred_dup(__vpred, __RD const int*);
__uint16      __OVBIF __vload_pred_dup(__vpred, __RD __const_uint8_ptr);
__uint16      __OVBIF __vload_pred_dup(__vpred, __RD __const_uint4_ptr);
__uint16      __OVBIF __vload_pred_dup(__vpred, __RD __const_uint2_ptr);
__uint16      __OVBIF __vload_pred_dup(__vpred, __RD __const_uint_ptr);
__float16     __OVBIF __vload_pred_dup(__vpred, __RD __const_float8_ptr);
__float16     __OVBIF __vload_pred_dup(__vpred, __RD __const_float4_ptr);
__float16     __OVBIF __vload_pred_dup(__vpred, __RD __const_float2_ptr);
__float16     __OVBIF __vload_pred_dup(__vpred, __RD const float*);

/* VLDDUP2D, VLDDUP4D, VLDDUP8D */
__long8       __OVBIF __vload_pred_dup(__vpred, __RD __const_long4_ptr);
__long8       __OVBIF __vload_pred_dup(__vpred, __RD __const_long2_ptr);
__long8       __OVBIF __vload_pred_dup(__vpred, __RD const long*);
__ulong8      __OVBIF __vload_pred_dup(__vpred, __RD __const_ulong4_ptr);
__ulong8      __OVBIF __vload_pred_dup(__vpred, __RD __const_ulong2_ptr);
__ulong8      __OVBIF __vload_pred_dup(__vpred, __RD __const_ulong_ptr);
__double8     __OVBIF __vload_pred_dup(__vpred, __RD __const_double4_ptr);
__double8     __OVBIF __vload_pred_dup(__vpred, __RD __const_double2_ptr);
__double8     __OVBIF __vload_pred_dup(__vpred, __RD const double*);

/* VLDDUP4G8H, VLDDUP8G4H */
__short32     __OVBIF __vload_pred_dup_vec(__vpred, __RD __const_short8_ptr);
__ushort32    __OVBIF __vload_pred_dup_vec(__vpred, __RD __const_ushort8_ptr);
__short32     __OVBIF __vload_pred_dup_vec(__vpred, __RD __const_short4_ptr);
__ushort32    __OVBIF __vload_pred_dup_vec(__vpred, __RD __const_ushort4_ptr);

/* VLDBUNPKH, VLDBUNPKHU */
short       __OVBIF __vload_pred_unpack_short(__vpred, __RD const char*);
__short2    __OVBIF __vload_pred_unpack_short(__vpred, __RD __const_char2_ptr);
__short4    __OVBIF __vload_pred_unpack_short(__vpred, __RD __const_char4_ptr);
__short8    __OVBIF __vload_pred_unpack_short(__vpred, __RD __const_char8_ptr);
__short16   __OVBIF __vload_pred_unpack_short(__vpred, __RD __const_char16_ptr);
__short32   __OVBIF __vload_pred_unpack_short(__vpred, __RD __const_char32_ptr);
__ushort    __OVBIF __vload_pred_unpack_short(__vpred, __RD __const_uchar_ptr);
__ushort2   __OVBIF __vload_pred_unpack_short(__vpred, __RD __const_uchar2_ptr);
__ushort4   __OVBIF __vload_pred_unpack_short(__vpred, __RD __const_uchar4_ptr);
__ushort8   __OVBIF __vload_pred_unpack_short(__vpred, __RD __const_uchar8_ptr);
__ushort16  __OVBIF __vload_pred_unpack_short(__vpred, __RD __const_uchar16_ptr);
__ushort32  __OVBIF __vload_pred_unpack_short(__vpred, __RD __const_uchar32_ptr);

/* VLDBUNPKW, VLDBUNPKWU */
int         __OVBIF __vload_pred_unpack_int(__vpred, __RD const char*);
__int2      __OVBIF __vload_pred_unpack_int(__vpred, __RD __const_char2_ptr);
__int4      __OVBIF __vload_pred_unpack_int(__vpred, __RD __const_char4_ptr);
__int8      __OVBIF __vload_pred_unpack_int(__vpred, __RD __const_char8_ptr);
__int16     __OVBIF __vload_pred_unpack_int(__vpred, __RD __const_char16_ptr);
__uint      __OVBIF __vload_pred_unpack_int(__vpred, __RD __const_uchar_ptr);
__uint2     __OVBIF __vload_pred_unpack_int(__vpred, __RD __const_uchar2_ptr);
__uint4     __OVBIF __vload_pred_unpack_int(__vpred, __RD __const_uchar4_ptr);
__uint8     __OVBIF __vload_pred_unpack_int(__vpred, __RD __const_uchar8_ptr);
__uint16    __OVBIF __vload_pred_unpack_int(__vpred, __RD __const_uchar16_ptr);

/* VLDHUNPKW, VLDHUNPKWU */
int         __OVBIF __vload_pred_unpack_int(__vpred, __RD const short*);
__int2      __OVBIF __vload_pred_unpack_int(__vpred, __RD __const_short2_ptr);
__int4      __OVBIF __vload_pred_unpack_int(__vpred, __RD __const_short4_ptr);
__int8      __OVBIF __vload_pred_unpack_int(__vpred, __RD __const_short8_ptr);
__int16     __OVBIF __vload_pred_unpack_int(__vpred, __RD __const_short16_ptr);
__uint      __OVBIF __vload_pred_unpack_int(__vpred, __RD __const_ushort_ptr);
__uint2     __OVBIF __vload_pred_unpack_int(__vpred, __RD __const_ushort2_ptr);
__uint4     __OVBIF __vload_pred_unpack_int(__vpred, __RD __const_ushort4_ptr);
__uint8     __OVBIF __vload_pred_unpack_int(__vpred, __RD __const_ushort8_ptr);
__uint16    __OVBIF __vload_pred_unpack_int(__vpred, __RD __const_ushort16_ptr);

/* VLDBUNPKD, VLDBUNPKDU */
long        __OVBIF __vload_pred_unpack_long(__vpred, __RD const char*);
__long2     __OVBIF __vload_pred_unpack_long(__vpred, __RD __const_char2_ptr);
__long4     __OVBIF __vload_pred_unpack_long(__vpred, __RD __const_char4_ptr);
__long8     __OVBIF __vload_pred_unpack_long(__vpred, __RD __const_char8_ptr);
__ulong     __OVBIF __vload_pred_unpack_long(__vpred, __RD __const_uchar_ptr);
__ulong2    __OVBIF __vload_pred_unpack_long(__vpred, __RD __const_uchar2_ptr);
__ulong4    __OVBIF __vload_pred_unpack_long(__vpred, __RD __const_uchar4_ptr);
__ulong8    __OVBIF __vload_pred_unpack_long(__vpred, __RD __const_uchar8_ptr);

/* VLDHUNPKD, VLDHUNPKDU */
long        __OVBIF __vload_pred_unpack_long(__vpred, __RD const short*);
__long2     __OVBIF __vload_pred_unpack_long(__vpred, __RD __const_short2_ptr);
__long4     __OVBIF __vload_pred_unpack_long(__vpred, __RD __const_short4_ptr);
__long8     __OVBIF __vload_pred_unpack_long(__vpred, __RD __const_short8_ptr);
__ulong     __OVBIF __vload_pred_unpack_long(__vpred, __RD __const_ushort_ptr);
__ulong2    __OVBIF __vload_pred_unpack_long(__vpred, __RD __const_ushort2_ptr);
__ulong4    __OVBIF __vload_pred_unpack_long(__vpred, __RD __const_ushort4_ptr);
__ulong8    __OVBIF __vload_pred_unpack_long(__vpred, __RD __const_ushort8_ptr);

/* VLDWUNPKD, VLDWUNPKDU */
long        __OVBIF __vload_pred_unpack_long(__vpred, __RD const int*);
__long2     __OVBIF __vload_pred_unpack_long(__vpred, __RD __const_int2_ptr);
__long4     __OVBIF __vload_pred_unpack_long(__vpred, __RD __const_int4_ptr);
__long8     __OVBIF __vload_pred_unpack_long(__vpred, __RD __const_int8_ptr);
__ulong     __OVBIF __vload_pred_unpack_long(__vpred, __RD __const_uint_ptr);
__ulong2    __OVBIF __vload_pred_unpack_long(__vpred, __RD __const_uint2_ptr);
__ulong4    __OVBIF __vload_pred_unpack_long(__vpred, __RD __const_uint4_ptr);
__ulong8    __OVBIF __vload_pred_unpack_long(__vpred, __RD __const_uint8_ptr);

/* VLDEBUNPKW, VLDEHUNPKW */
int         __OVBIF __vload_pred_deinterleave_int(__vpred, __RD __const_char2_ptr);
__int2      __OVBIF __vload_pred_deinterleave_int(__vpred, __RD __const_char4_ptr);
__int4      __OVBIF __vload_pred_deinterleave_int(__vpred, __RD __const_char8_ptr);
__int8      __OVBIF __vload_pred_deinterleave_int(__vpred, __RD __const_char16_ptr);
__int16     __OVBIF __vload_pred_deinterleave_int(__vpred, __RD __const_char32_ptr);
int         __OVBIF __vload_pred_deinterleave_int(__vpred, __RD __const_short2_ptr);
__int2      __OVBIF __vload_pred_deinterleave_int(__vpred, __RD __const_short4_ptr);
__int4      __OVBIF __vload_pred_deinterleave_int(__vpred, __RD __const_short8_ptr);
__int8      __OVBIF __vload_pred_deinterleave_int(__vpred, __RD __const_short16_ptr);
__int16     __OVBIF __vload_pred_deinterleave_int(__vpred, __RD __const_short32_ptr);

/* VLDEBUNPKWU, VLDEHUNPKWU */
__uint       __OVBIF __vload_pred_deinterleave_int(__vpred, __RD __const_uchar2_ptr);
__uint2      __OVBIF __vload_pred_deinterleave_int(__vpred, __RD __const_uchar4_ptr);
__uint4      __OVBIF __vload_pred_deinterleave_int(__vpred, __RD __const_uchar8_ptr);
__uint8      __OVBIF __vload_pred_deinterleave_int(__vpred, __RD __const_uchar16_ptr);
__uint16     __OVBIF __vload_pred_deinterleave_int(__vpred, __RD __const_uchar32_ptr);
__uint       __OVBIF __vload_pred_deinterleave_int(__vpred, __RD __const_ushort2_ptr);
__uint2      __OVBIF __vload_pred_deinterleave_int(__vpred, __RD __const_ushort4_ptr);
__uint4      __OVBIF __vload_pred_deinterleave_int(__vpred, __RD __const_ushort8_ptr);
__uint8      __OVBIF __vload_pred_deinterleave_int(__vpred, __RD __const_ushort16_ptr);
__uint16     __OVBIF __vload_pred_deinterleave_int(__vpred, __RD __const_ushort32_ptr);

/* VLDEBUNPKD, VLDEHUNPKD */
long         __OVBIF __vload_pred_deinterleave_long(__vpred, __RD __const_char2_ptr);
__long2      __OVBIF __vload_pred_deinterleave_long(__vpred, __RD __const_char4_ptr);
__long4      __OVBIF __vload_pred_deinterleave_long(__vpred, __RD __const_char8_ptr);
__long8      __OVBIF __vload_pred_deinterleave_long(__vpred, __RD __const_char16_ptr);
long         __OVBIF __vload_pred_deinterleave_long(__vpred, __RD __const_short2_ptr);
__long2      __OVBIF __vload_pred_deinterleave_long(__vpred, __RD __const_short4_ptr);
__long4      __OVBIF __vload_pred_deinterleave_long(__vpred, __RD __const_short8_ptr);
__long8      __OVBIF __vload_pred_deinterleave_long(__vpred, __RD __const_short16_ptr);

/* VLDEBUNPKDU, VLDEHUNPKDU */
__ulong       __OVBIF __vload_pred_deinterleave_long(__vpred, __RD __const_uchar2_ptr);
__ulong2      __OVBIF __vload_pred_deinterleave_long(__vpred, __RD __const_uchar4_ptr);
__ulong4      __OVBIF __vload_pred_deinterleave_long(__vpred, __RD __const_uchar8_ptr);
__ulong8      __OVBIF __vload_pred_deinterleave_long(__vpred, __RD __const_uchar16_ptr);
__ulong       __OVBIF __vload_pred_deinterleave_long(__vpred, __RD __const_ushort2_ptr);
__ulong2      __OVBIF __vload_pred_deinterleave_long(__vpred, __RD __const_ushort4_ptr);
__ulong4      __OVBIF __vload_pred_deinterleave_long(__vpred, __RD __const_ushort8_ptr);
__ulong8      __OVBIF __vload_pred_deinterleave_long(__vpred, __RD __const_ushort16_ptr);

/*****************************************************************************/
/* VECTOR STORES AND PREDICATED VECTOR STORES                                */
/*                                                                           */
/* On all C7000 devices, implicit predication occurs on stores that use      */
/* streaming address generator (SA) operands. If an SA may be used as an     */
/* operand to a store AND that SA may generate predicates with one or more   */
/* predicate bits off, then a predicated store must be used to avoid         */
/* unexpected behavior. Use the following idiom with implicitly predicated   */
/* SA stores:                                                                */
/*                                                                           */
/* __vpred pred = __SA0_VPRED(char2);                                        */
/* char2 *ptr = __SA0ADV(char2, base_ptr);                                   */
/* __vstore_pred(pred, ptr, data);                                           */
/*                                                                           */
/* If the idiom is malformed or the compiler fails to optimize the idiom, an */
/* equivalent series of instructions will instead be generated to create the */
/* predicate and then store with explicit predication.                       */
/*****************************************************************************/
/* VSTPINTLB, VSTPINTLH, VSTPINTLW, VSTPINLD - STORES EVERY EVEN ELEMENT */
void __OVBIFM __vstore_pred_interleave(__vpred, __WR __char64*,  __char64,  __char64);
void __OVBIFM __vstore_pred_interleave(__vpred, __WR __short32*, __short32, __short32);
void __OVBIFM __vstore_pred_interleave(__vpred, __WR __int16*,   __int16,   __int16);
void __OVBIFM __vstore_pred_interleave(__vpred, __WR __long8*,   __long8,   __long8);
void __OVBIFM __vstore_pred_interleave(__vpred, __WR __uchar64*, __uchar64, __uchar64);
void __OVBIFM __vstore_pred_interleave(__vpred, __WR __ushort32*,__ushort32,__ushort32);
void __OVBIFM __vstore_pred_interleave(__vpred, __WR __uint16*,  __uint16,  __uint16);
void __OVBIFM __vstore_pred_interleave(__vpred, __WR __ulong8*,  __ulong8,  __ulong8);

/* VSTPINTLB4 - STORES EVERY FOURTH ELEMENT */
void __OVBIFM __vstore_pred_interleave4(__vpred, __WR __char32*,  __char64,   __char64);
void __OVBIFM __vstore_pred_interleave4(__vpred, __WR __uchar32*, __uchar64,  __uchar64);

#ifndef __C7100__
/* VSTPINTHB, VSTPINTHH, VSTPINTHW, VSTPINTHD - STORES EVERY EVEN ELEMENT */
void __OVBIFM __vstore_pred_interleave_odd(__vpred, __WR __char64*,  __char64,  __char64);
void __OVBIFM __vstore_pred_interleave_odd(__vpred, __WR __short32*, __short32, __short32);
void __OVBIFM __vstore_pred_interleave_odd(__vpred, __WR __int16*,   __int16,   __int16);
void __OVBIFM __vstore_pred_interleave_odd(__vpred, __WR __long8*,   __long8,   __long8);
void __OVBIFM __vstore_pred_interleave_odd(__vpred, __WR __uchar64*, __uchar64, __uchar64);
void __OVBIFM __vstore_pred_interleave_odd(__vpred, __WR __ushort32*,__ushort32,__ushort32);
void __OVBIFM __vstore_pred_interleave_odd(__vpred, __WR __uint16*,  __uint16,  __uint16);
void __OVBIFM __vstore_pred_interleave_odd(__vpred, __WR __ulong8*,  __ulong8,  __ulong8);

/* VSTPLLINTB, VSTPLLINTH, VSTPLLINTW, VSTPLLINTH - STORES LOW VECTOR HALVES */
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __char64*,  __char64,  __char64);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __short32*, __short32, __short32);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __int16*,   __int16,   __int16);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __long8*,   __long8,   __long8);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __uchar64*, __uchar64, __uchar64);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __ushort32*,__ushort32,__ushort32);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __uint16*,  __uint16,  __uint16);
void __OVBIFM __vstore_pred_interleave_low_low(__vpred, __WR __ulong8*,  __ulong8,  __ulong8);

/* VSTPHHINTB, VSTPHHINTH, VSTPHHINTW, VSTPHHINTH - STORES HIGH VECTOR HALVES */
void __OVBIFM __vstore_pred_interleave_high_high(__vpred, __WR __char64*,  __char64,  __char64);
void __OVBIFM __vstore_pred_interleave_high_high(__vpred, __WR __short32*, __short32, __short32);
void __OVBIFM __vstore_pred_interleave_high_high(__vpred, __WR __int16*,   __int16,   __int16);
void __OVBIFM __vstore_pred_interleave_high_high(__vpred, __WR __long8*,   __long8,   __long8);
void __OVBIFM __vstore_pred_interleave_high_high(__vpred, __WR __uchar64*, __uchar64, __uchar64);
void __OVBIFM __vstore_pred_interleave_high_high(__vpred, __WR __ushort32*,__ushort32,__ushort32);
void __OVBIFM __vstore_pred_interleave_high_high(__vpred, __WR __uint16*,  __uint16,  __uint16);
void __OVBIFM __vstore_pred_interleave_high_high(__vpred, __WR __ulong8*,  __ulong8,  __ulong8);
#endif /* ! __C7100__ */

/* VSTP2B, VSTP4B, VSTP8B, VSTP16B, VSTP32B, VSTP64B */
void __OVBIFM __vstore_pred(__vpred, __WR __char2*,   __char2);
void __OVBIFM __vstore_pred(__vpred, __WR __char4*,   __char4);
void __OVBIFM __vstore_pred(__vpred, __WR __char8*,   __char8);
void __OVBIFM __vstore_pred(__vpred, __WR __char16*,  __char16);
void __OVBIFM __vstore_pred(__vpred, __WR __char32*,  __char32);
void __OVBIFM __vstore_pred(__vpred, __WR __char64*,  __char64);
void __OVBIFM __vstore_pred(__vpred, __WR __uchar2*,  __uchar2);
void __OVBIFM __vstore_pred(__vpred, __WR __uchar4*,  __uchar4);
void __OVBIFM __vstore_pred(__vpred, __WR __uchar8*,  __uchar8);
void __OVBIFM __vstore_pred(__vpred, __WR __uchar16*, __uchar16);
void __OVBIFM __vstore_pred(__vpred, __WR __uchar32*, __uchar32);
void __OVBIFM __vstore_pred(__vpred, __WR __uchar64*, __uchar64);

/* VSTP2H, VSTP4H, VSTP8H, VSTP16H, VSTP32H */
void __OVBIFM __vstore_pred(__vpred, __WR __short2*, __short2);
void __OVBIFM __vstore_pred(__vpred, __WR __short4*, __short4);
void __OVBIFM __vstore_pred(__vpred, __WR __short8*, __short8);
void __OVBIFM __vstore_pred(__vpred, __WR __short16*, __short16);
void __OVBIFM __vstore_pred(__vpred, __WR __short32*, __short32);
void __OVBIFM __vstore_pred(__vpred, __WR __ushort2*, __ushort2);
void __OVBIFM __vstore_pred(__vpred, __WR __ushort4*, __ushort4);
void __OVBIFM __vstore_pred(__vpred, __WR __ushort8*, __ushort8);
void __OVBIFM __vstore_pred(__vpred, __WR __ushort16*, __ushort16);
void __OVBIFM __vstore_pred(__vpred, __WR __ushort32*, __ushort32);
void __OVBIFM __vstore_pred(__vpred, __WR __cchar2*, __cchar2);
void __OVBIFM __vstore_pred(__vpred, __WR __cchar4*, __cchar4);
void __OVBIFM __vstore_pred(__vpred, __WR __cchar8*, __cchar8);
void __OVBIFM __vstore_pred(__vpred, __WR __cchar16*, __cchar16);
void __OVBIFM __vstore_pred(__vpred, __WR __cchar32*, __cchar32);

/* VSTP2W, VSTP4W, VSTP8W, VSTP16W */
void __OVBIFM __vstore_pred(__vpred, __WR __int2*,     __int2);
void __OVBIFM __vstore_pred(__vpred, __WR __int4*,     __int4);
void __OVBIFM __vstore_pred(__vpred, __WR __int8*,     __int8);
void __OVBIFM __vstore_pred(__vpred, __WR __int16*,    __int16);
void __OVBIFM __vstore_pred(__vpred, __WR __uint2*,    __uint2);
void __OVBIFM __vstore_pred(__vpred, __WR __uint4*,    __uint4);
void __OVBIFM __vstore_pred(__vpred, __WR __uint8*,    __uint8);
void __OVBIFM __vstore_pred(__vpred, __WR __uint16*,   __uint16);
void __OVBIFM __vstore_pred(__vpred, __WR __float2*,   __float2);
void __OVBIFM __vstore_pred(__vpred, __WR __float4*,   __float4);
void __OVBIFM __vstore_pred(__vpred, __WR __float8*,   __float8);
void __OVBIFM __vstore_pred(__vpred, __WR __float16*,  __float16);
void __OVBIFM __vstore_pred(__vpred, __WR __cshort2*,  __cshort2);
void __OVBIFM __vstore_pred(__vpred, __WR __cshort4*,  __cshort4);
void __OVBIFM __vstore_pred(__vpred, __WR __cshort8*,  __cshort8);
void __OVBIFM __vstore_pred(__vpred, __WR __cshort16*, __cshort16);

/* VSTP2D, VSTP4D, VSTP8D */
void __OVBIFM __vstore_pred(__vpred, __WR long*,    long);
void __OVBIFM __vstore_pred(__vpred, __WR __long2*,   __long2);
void __OVBIFM __vstore_pred(__vpred, __WR __long4*,   __long4);
void __OVBIFM __vstore_pred(__vpred, __WR __long8*,   __long8);
void __OVBIFM __vstore_pred(__vpred, __WR __ulong*,   __ulong);
void __OVBIFM __vstore_pred(__vpred, __WR __ulong2*,  __ulong2);
void __OVBIFM __vstore_pred(__vpred, __WR __ulong4*,  __ulong4);
void __OVBIFM __vstore_pred(__vpred, __WR __ulong8*,  __ulong8);
void __OVBIFM __vstore_pred(__vpred, __WR double*,  double);
void __OVBIFM __vstore_pred(__vpred, __WR __double2*, __double2);
void __OVBIFM __vstore_pred(__vpred, __WR __double4*, __double4);
void __OVBIFM __vstore_pred(__vpred, __WR __double8*, __double8);
void __OVBIFM __vstore_pred(__vpred, __WR __cint*,    __cint);
void __OVBIFM __vstore_pred(__vpred, __WR __cint2*,   __cint2);
void __OVBIFM __vstore_pred(__vpred, __WR __cint4*,   __cint4);
void __OVBIFM __vstore_pred(__vpred, __WR __cint8*,   __cint8);
void __OVBIFM __vstore_pred(__vpred, __WR __cfloat*,  __cfloat);
void __OVBIFM __vstore_pred(__vpred, __WR __cfloat2*, __cfloat2);
void __OVBIFM __vstore_pred(__vpred, __WR __cfloat4*, __cfloat4);
void __OVBIFM __vstore_pred(__vpred, __WR __cfloat8*, __cfloat8);

/* VSTPBSVPACKL, VSTPBSVPACKH, VSTPBSVPACKHS1: PRED CORRESPONDS TO SRC DATA */
void __OVBIFM __vstore_pred_packl(__vpred,   __WR __char32*,  __short32);
void __OVBIFM __vstore_pred_packl(__vpred,   __WR __uchar32*, __ushort32);
void __OVBIFM __vstore_pred_packh(__vpred,   __WR __char32*,  __short32);
void __OVBIFM __vstore_pred_packh(__vpred,   __WR __uchar32*, __ushort32);
void __OVBIFM __vstore_pred_packhs1(__vpred, __WR __char32*,  __short32);
void __OVBIFM __vstore_pred_packhs1(__vpred, __WR __uchar32*, __ushort32);

/* VSTPHSVPACKL, VSTPHSVPACKH, VSTPHSVPACKHS1: PRED CORRESPONDS TO SRC DATA */
void __OVBIFM __vstore_pred_packl(__vpred,   __WR __short16*,  __int16);
void __OVBIFM __vstore_pred_packl(__vpred,   __WR __ushort16*, __uint16);
void __OVBIFM __vstore_pred_packh(__vpred,   __WR __short16*,  __int16);
void __OVBIFM __vstore_pred_packh(__vpred,   __WR __ushort16*, __uint16);
void __OVBIFM __vstore_pred_packhs1(__vpred, __WR __short16*,  __int16);
void __OVBIFM __vstore_pred_packhs1(__vpred, __WR __ushort16*, __uint16);

/* VSTPWSVPACKB: PRED CORRESPONDS TO SRC DATA */
void __OVBIFM __vstore_pred_pack_byte(__vpred, __WR __char16*,  __int16);
void __OVBIFM __vstore_pred_pack_byte(__vpred, __WR __uchar16*, __uint16);

/* VSTPWSVPACKL, VSTPWSVPACKH, VSTPWSVPACKHS1: PRED CORRESPONDS TO SRC DATA */
void __OVBIFM __vstore_pred_packl(__vpred,   __WR __int8*,  __long8);
void __OVBIFM __vstore_pred_packl(__vpred,   __WR __uint8*, __ulong8);
void __OVBIFM __vstore_pred_packh(__vpred,   __WR __int8*,  __long8);
void __OVBIFM __vstore_pred_packh(__vpred,   __WR __uint8*, __ulong8);
void __OVBIFM __vstore_pred_packhs1(__vpred, __WR __int8*,  __long8);
void __OVBIFM __vstore_pred_packhs1(__vpred, __WR __uint8*, __ulong8);

/* VSTPDSVPACKL, VSTPDSVPACKH, VSTPDSVPACKHS1: PRED CORRESPONDS TO SRC DATA */
void __OVBIFM __vstore_pred_packl_long(__vpred,   __WR __long4*,  __long8);
void __OVBIFM __vstore_pred_packl_long(__vpred,   __WR __ulong4*, __ulong8);
void __OVBIFM __vstore_pred_packh_long(__vpred,   __WR __long4*,  __long8);
void __OVBIFM __vstore_pred_packh_long(__vpred,   __WR __ulong4*, __ulong8);
void __OVBIFM __vstore_pred_packhs1_long(__vpred, __WR __long4*,  __long8);
void __OVBIFM __vstore_pred_packhs1_long(__vpred, __WR __ulong4*, __ulong8);

#define __vstore_pred_packl_long(a,b,c) __overload("__vstore_pred_packl_long",(a),(b),(c))((a),(b),(c))
#define __vstore_pred_packh_long(a,b,c) __overload("__vstore_pred_packh_long",(a),(b),(c))((a),(b),(c))
#define __vstore_pred_packhs1_long(a,b,c) __overload("__vstore_pred_packhs1_long",(a),(b),(c))((a),(b),(c))

/* VSTPBPACKL, VSTPBPACKH, VSTPBPACKHS1: PRED CORRESPONDS TO PACKED DATA */
void __OVBIFM __vstore_pred_packl_2src(__vpred,   __WR __char64*, __short32,  __short32);
void __OVBIFM __vstore_pred_packl_2src(__vpred,   __WR __uchar64*, __ushort32, __ushort32);
void __OVBIFM __vstore_pred_packh_2src(__vpred,   __WR __char64*, __short32,  __short32);
void __OVBIFM __vstore_pred_packh_2src(__vpred,   __WR __uchar64*, __ushort32, __ushort32);
void __OVBIFM __vstore_pred_packhs1_2src(__vpred, __WR __char64*, __short32,  __short32);
void __OVBIFM __vstore_pred_packhs1_2src(__vpred, __WR __uchar64*, __ushort32, __ushort32);

/* VSTPHPACKL, VSTPHPACKH, VSTPHPACKHS1: PRED CORRESPONDS TO PACKED DATA */
void __OVBIFM __vstore_pred_packl_2src(__vpred,   __WR __short32*, __int16,   __int16);
void __OVBIFM __vstore_pred_packl_2src(__vpred,   __WR __ushort32*, __uint16, __uint16);
void __OVBIFM __vstore_pred_packh_2src(__vpred,   __WR __short32*, __int16,   __int16);
void __OVBIFM __vstore_pred_packh_2src(__vpred,   __WR __ushort32*, __uint16, __uint16);
void __OVBIFM __vstore_pred_packhs1_2src(__vpred, __WR __short32*, __int16,   __int16);
void __OVBIFM __vstore_pred_packhs1_2src(__vpred, __WR __ushort32*, __uint16, __uint16);

/* VSTPWPACKB: PRED CORRESPONDS TO PACKED DATA */
void __OVBIFM __vstore_pred_pack_byte_2src(__vpred, __WR __char32*, __int16,  __int16);
void __OVBIFM __vstore_pred_pack_byte_2src(__vpred, __WR __uchar32*, __uint16, __uint16);

/* VSTPWPACKL, VSTPWPACKH, VSTPWPACKHS1: PRED CORRESPONDS TO PACKED DATA */
void __OVBIFM __vstore_pred_packl_2src(__vpred,   __WR __int16*, __long8,  __long8);
void __OVBIFM __vstore_pred_packl_2src(__vpred,   __WR __uint16*, __ulong8, __ulong8);
void __OVBIFM __vstore_pred_packh_2src(__vpred,   __WR __int16*, __long8,   __long8);
void __OVBIFM __vstore_pred_packh_2src(__vpred,   __WR __uint16*, __ulong8, __ulong8);
void __OVBIFM __vstore_pred_packhs1_2src(__vpred, __WR __int16*, __long8,   __long8);
void __OVBIFM __vstore_pred_packhs1_2src(__vpred, __WR __uint16*, __ulong8, __ulong8);

/* VSTPDPACKL, VSTPDPACKH, VSTPDPACKHS1: PRED CORRESPONDS TO PACKED DATA */
void __OVBIFM __vstore_pred_packl_long_2src(__vpred,   __WR __long8*, __long8, __long8);
void __OVBIFM __vstore_pred_packl_long_2src(__vpred,   __WR __ulong8*, __ulong8,__ulong8);
void __OVBIFM __vstore_pred_packh_long_2src(__vpred,   __WR __long8*, __long8, __long8);
void __OVBIFM __vstore_pred_packh_long_2src(__vpred,   __WR __ulong8*, __ulong8,__ulong8);
void __OVBIFM __vstore_pred_packhs1_long_2src(__vpred, __WR __long8*, __long8, __long8);
void __OVBIFM __vstore_pred_packhs1_long_2src(__vpred, __WR __ulong8*, __ulong8,__ulong8);

/* VSTPBITRWH */
void __OVBIFM __vstore_pred_reverse_bit(__vpred, __WR __cshort16*, __cshort16);

/* VSTPBITRDW */
void __OVBIFM __vstore_pred_reverse_bit(__vpred, __WR __cint8*,   __cint8);
void __OVBIFM __vstore_pred_reverse_bit(__vpred, __WR __cfloat8*, __cfloat8);

/* STPREDB  (C syntax):
        __vpred src;
        *(__vpred *)ptr = src;
*/

/* STPREDB - store predicate according to type byte (every bit) */
void __BIFM __store_predicate_char(__WR __ulong*, __vpred);

/* STPREDH - store predicate according to type short (every 2-bits) */
void __BIFM __store_predicate_short(__WR __uint*, __vpred);

/* STPREDW - store predicate according to type int (every 4-bits) */
void __BIFM __store_predicate_int(__WR __ushort*, __vpred);

/* STPREDD - store predicate according to type long (every 8-bits) */
void __BIFM __store_predicate_long(__WR __uchar*, __vpred);

/*-----------------------------------------------------------------------------
* ID: __add
*----------------------------------------------------------------------------*/
/*

VADDCB
char = __add(__vpred, char, char);
char2 = __add(__vpred, char2, char2);
char3 = __add(__vpred, char3, char3);
char4 = __add(__vpred, char4, char4);
char8 = __add(__vpred, char8, char8);
char16 = __add(__vpred, char16, char16);
char32 = __add(__vpred, char32, char32);
char64 = __add(__vpred, char64, char64);
uchar = __add(__vpred, uchar, uchar);
uchar2 = __add(__vpred, uchar2, uchar2);
uchar3 = __add(__vpred, uchar3, uchar3);
uchar4 = __add(__vpred, uchar4, uchar4);
uchar8 = __add(__vpred, uchar8, uchar8);
uchar16 = __add(__vpred, uchar16, uchar16);
uchar32 = __add(__vpred, uchar32, uchar32);
uchar64 = __add(__vpred, uchar64, uchar64);

VADDCD
long = __add(__vpred, long, long);
long2 = __add(__vpred, long2, long2);
long3 = __add(__vpred, long3, long3);
long4 = __add(__vpred, long4, long4);
long8 = __add(__vpred, long8, long8);
ulong = __add(__vpred, ulong, ulong);
ulong2 = __add(__vpred, ulong2, ulong2);
ulong3 = __add(__vpred, ulong3, ulong3);
ulong4 = __add(__vpred, ulong4, ulong4);
ulong8 = __add(__vpred, ulong8, ulong8);

VADDCH
short = __add(__vpred, short, short);
short2 = __add(__vpred, short2, short2);
short3 = __add(__vpred, short3, short3);
short4 = __add(__vpred, short4, short4);
short8 = __add(__vpred, short8, short8);
short16 = __add(__vpred, short16, short16);
short32 = __add(__vpred, short32, short32);
ushort = __add(__vpred, ushort, ushort);
ushort2 = __add(__vpred, ushort2, ushort2);
ushort3 = __add(__vpred, ushort3, ushort3);
ushort4 = __add(__vpred, ushort4, ushort4);
ushort8 = __add(__vpred, ushort8, ushort8);
ushort16 = __add(__vpred, ushort16, ushort16);
ushort32 = __add(__vpred, ushort32, ushort32);

VADDCW
int = __add(__vpred, int, int);
int2 = __add(__vpred, int2, int2);
int3 = __add(__vpred, int3, int3);
int4 = __add(__vpred, int4, int4);
int8 = __add(__vpred, int8, int8);
int16 = __add(__vpred, int16, int16);
uint = __add(__vpred, uint, uint);
uint2 = __add(__vpred, uint2, uint2);
uint3 = __add(__vpred, uint3, uint3);
uint4 = __add(__vpred, uint4, uint4);
uint8 = __add(__vpred, uint8, uint8);
uint16 = __add(__vpred, uint16, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __and
*----------------------------------------------------------------------------*/
/*

AND
__vpred = __and(__vpred, __vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __andn
*----------------------------------------------------------------------------*/
/*

ANDN
__vpred = __andn(__vpred, __vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __expand_vpred
*----------------------------------------------------------------------------*/
/*
BITXPND
*/

__vpred __OVBIF __expand_vpred(__vpred,       __CST(0,4) __uchar);
__vpred __OVBIF __expand_vpred(unsigned long, __CST(0,4) __uchar);

#define __expand_vpred(a,b) __overload("__expand_vpred",(a),(__uchar)(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __pack_vpred
*----------------------------------------------------------------------------*/
/*
BITPACK
*/

__vpred __OVBIF __pack_vpred(__vpred,       __CST(0,4) __uchar);
__vpred __OVBIF __pack_vpred(unsigned long, __CST(0,4) __uchar);

#define __pack_vpred(a,b) __overload("__pack_vpred",(a),(__uchar)(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __bit_reverse
*----------------------------------------------------------------------------*/
/*

BITR
__vpred = __bit_reverse(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __cmp_eq_pred
*----------------------------------------------------------------------------*/
/*

VCMPEQB
__vpred = __cmp_eq_pred(char, char);
__vpred = __cmp_eq_pred(char2, char2);
__vpred = __cmp_eq_pred(char3, char3);
__vpred = __cmp_eq_pred(char4, char4);
__vpred = __cmp_eq_pred(char8, char8);
__vpred = __cmp_eq_pred(char16, char16);
__vpred = __cmp_eq_pred(char32, char32);
__vpred = __cmp_eq_pred(char64, char64);
__vpred = __cmp_eq_pred(uchar, uchar);
__vpred = __cmp_eq_pred(uchar2, uchar2);
__vpred = __cmp_eq_pred(uchar3, uchar3);
__vpred = __cmp_eq_pred(uchar4, uchar4);
__vpred = __cmp_eq_pred(uchar8, uchar8);
__vpred = __cmp_eq_pred(uchar16, uchar16);
__vpred = __cmp_eq_pred(uchar32, uchar32);
__vpred = __cmp_eq_pred(uchar64, uchar64);

VCMPEQD
__vpred = __cmp_eq_pred(long, long);
__vpred = __cmp_eq_pred(long2, long2);
__vpred = __cmp_eq_pred(long3, long3);
__vpred = __cmp_eq_pred(long4, long4);
__vpred = __cmp_eq_pred(long8, long8);
__vpred = __cmp_eq_pred(ulong, ulong);
__vpred = __cmp_eq_pred(ulong2, ulong2);
__vpred = __cmp_eq_pred(ulong3, ulong3);
__vpred = __cmp_eq_pred(ulong4, ulong4);
__vpred = __cmp_eq_pred(ulong8, ulong8);

VCMPEQDP
__vpred = __cmp_eq_pred(double, double);
__vpred = __cmp_eq_pred(double2, double2);
__vpred = __cmp_eq_pred(double3, double3);
__vpred = __cmp_eq_pred(double4, double4);
__vpred = __cmp_eq_pred(double8, double8);

VCMPEQH
__vpred = __cmp_eq_pred(short, short);
__vpred = __cmp_eq_pred(short2, short2);
__vpred = __cmp_eq_pred(short3, short3);
__vpred = __cmp_eq_pred(short4, short4);
__vpred = __cmp_eq_pred(short8, short8);
__vpred = __cmp_eq_pred(short16, short16);
__vpred = __cmp_eq_pred(short32, short32);
__vpred = __cmp_eq_pred(ushort, ushort);
__vpred = __cmp_eq_pred(ushort2, ushort2);
__vpred = __cmp_eq_pred(ushort3, ushort3);
__vpred = __cmp_eq_pred(ushort4, ushort4);
__vpred = __cmp_eq_pred(ushort8, ushort8);
__vpred = __cmp_eq_pred(ushort16, ushort16);
__vpred = __cmp_eq_pred(ushort32, ushort32);

VCMPEQSP
__vpred = __cmp_eq_pred(float, float);
__vpred = __cmp_eq_pred(float2, float2);
__vpred = __cmp_eq_pred(float3, float3);
__vpred = __cmp_eq_pred(float4, float4);
__vpred = __cmp_eq_pred(float8, float8);
__vpred = __cmp_eq_pred(float16, float16);

VCMPEQW
__vpred = __cmp_eq_pred(int, int);
__vpred = __cmp_eq_pred(int2, int2);
__vpred = __cmp_eq_pred(int3, int3);
__vpred = __cmp_eq_pred(int4, int4);
__vpred = __cmp_eq_pred(int8, int8);
__vpred = __cmp_eq_pred(int16, int16);
__vpred = __cmp_eq_pred(uint, uint);
__vpred = __cmp_eq_pred(uint2, uint2);
__vpred = __cmp_eq_pred(uint3, uint3);
__vpred = __cmp_eq_pred(uint4, uint4);
__vpred = __cmp_eq_pred(uint8, uint8);
__vpred = __cmp_eq_pred(uint16, uint16);

*/

#define __cmp_eq_pred(a,b) __overload("__cmp_eq_pred",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __cmp_ge_pred
*----------------------------------------------------------------------------*/
/*

VCMPGEB
__vpred = __cmp_ge_pred(char, char);
__vpred = __cmp_ge_pred(char2, char2);
__vpred = __cmp_ge_pred(char3, char3);
__vpred = __cmp_ge_pred(char4, char4);
__vpred = __cmp_ge_pred(char8, char8);
__vpred = __cmp_ge_pred(char16, char16);
__vpred = __cmp_ge_pred(char32, char32);
__vpred = __cmp_ge_pred(char64, char64);

VCMPGED
__vpred = __cmp_ge_pred(long, long);
__vpred = __cmp_ge_pred(long2, long2);
__vpred = __cmp_ge_pred(long3, long3);
__vpred = __cmp_ge_pred(long4, long4);
__vpred = __cmp_ge_pred(long8, long8);

VCMPGEH
__vpred = __cmp_ge_pred(short, short);
__vpred = __cmp_ge_pred(short2, short2);
__vpred = __cmp_ge_pred(short3, short3);
__vpred = __cmp_ge_pred(short4, short4);
__vpred = __cmp_ge_pred(short8, short8);
__vpred = __cmp_ge_pred(short16, short16);
__vpred = __cmp_ge_pred(short32, short32);

VCMPGEUB
__vpred = __cmp_ge_pred(uchar, uchar);
__vpred = __cmp_ge_pred(uchar2, uchar2);
__vpred = __cmp_ge_pred(uchar3, uchar3);
__vpred = __cmp_ge_pred(uchar4, uchar4);
__vpred = __cmp_ge_pred(uchar8, uchar8);
__vpred = __cmp_ge_pred(uchar16, uchar16);
__vpred = __cmp_ge_pred(uchar32, uchar32);
__vpred = __cmp_ge_pred(uchar64, uchar64);

VCMPGEUD
__vpred = __cmp_ge_pred(ulong, ulong);
__vpred = __cmp_ge_pred(ulong2, ulong2);
__vpred = __cmp_ge_pred(ulong3, ulong3);
__vpred = __cmp_ge_pred(ulong4, ulong4);
__vpred = __cmp_ge_pred(ulong8, ulong8);

VCMPGEUH
__vpred = __cmp_ge_pred(ushort, ushort);
__vpred = __cmp_ge_pred(ushort2, ushort2);
__vpred = __cmp_ge_pred(ushort3, ushort3);
__vpred = __cmp_ge_pred(ushort4, ushort4);
__vpred = __cmp_ge_pred(ushort8, ushort8);
__vpred = __cmp_ge_pred(ushort16, ushort16);
__vpred = __cmp_ge_pred(ushort32, ushort32);

VCMPGEUW
__vpred = __cmp_ge_pred(uint, uint);
__vpred = __cmp_ge_pred(uint2, uint2);
__vpred = __cmp_ge_pred(uint3, uint3);
__vpred = __cmp_ge_pred(uint4, uint4);
__vpred = __cmp_ge_pred(uint8, uint8);
__vpred = __cmp_ge_pred(uint16, uint16);

VCMPGEW
__vpred = __cmp_ge_pred(int, int);
__vpred = __cmp_ge_pred(int2, int2);
__vpred = __cmp_ge_pred(int3, int3);
__vpred = __cmp_ge_pred(int4, int4);
__vpred = __cmp_ge_pred(int8, int8);
__vpred = __cmp_ge_pred(int16, int16);

*/

#define __cmp_ge_pred(a,b) __overload("__cmp_ge_pred",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __cmp_gt_pred
*----------------------------------------------------------------------------*/
/*

VCMPGTB
__vpred = __cmp_gt_pred(char, char);
__vpred = __cmp_gt_pred(char2, char2);
__vpred = __cmp_gt_pred(char3, char3);
__vpred = __cmp_gt_pred(char4, char4);
__vpred = __cmp_gt_pred(char8, char8);
__vpred = __cmp_gt_pred(char16, char16);
__vpred = __cmp_gt_pred(char32, char32);
__vpred = __cmp_gt_pred(char64, char64);

VCMPGTD
__vpred = __cmp_gt_pred(long, long);
__vpred = __cmp_gt_pred(long2, long2);
__vpred = __cmp_gt_pred(long3, long3);
__vpred = __cmp_gt_pred(long4, long4);
__vpred = __cmp_gt_pred(long8, long8);

VCMPGTH
__vpred = __cmp_gt_pred(short, short);
__vpred = __cmp_gt_pred(short2, short2);
__vpred = __cmp_gt_pred(short3, short3);
__vpred = __cmp_gt_pred(short4, short4);
__vpred = __cmp_gt_pred(short8, short8);
__vpred = __cmp_gt_pred(short16, short16);
__vpred = __cmp_gt_pred(short32, short32);

VCMPGTUB
__vpred = __cmp_gt_pred(uchar, uchar);
__vpred = __cmp_gt_pred(uchar2, uchar2);
__vpred = __cmp_gt_pred(uchar3, uchar3);
__vpred = __cmp_gt_pred(uchar4, uchar4);
__vpred = __cmp_gt_pred(uchar8, uchar8);
__vpred = __cmp_gt_pred(uchar16, uchar16);
__vpred = __cmp_gt_pred(uchar32, uchar32);
__vpred = __cmp_gt_pred(uchar64, uchar64);

VCMPGTUD
__vpred = __cmp_gt_pred(ulong, ulong);
__vpred = __cmp_gt_pred(ulong2, ulong2);
__vpred = __cmp_gt_pred(ulong3, ulong3);
__vpred = __cmp_gt_pred(ulong4, ulong4);
__vpred = __cmp_gt_pred(ulong8, ulong8);

VCMPGTUH
__vpred = __cmp_gt_pred(ushort, ushort);
__vpred = __cmp_gt_pred(ushort2, ushort2);
__vpred = __cmp_gt_pred(ushort3, ushort3);
__vpred = __cmp_gt_pred(ushort4, ushort4);
__vpred = __cmp_gt_pred(ushort8, ushort8);
__vpred = __cmp_gt_pred(ushort16, ushort16);
__vpred = __cmp_gt_pred(ushort32, ushort32);

VCMPGTUW
__vpred = __cmp_gt_pred(uint, uint);
__vpred = __cmp_gt_pred(uint2, uint2);
__vpred = __cmp_gt_pred(uint3, uint3);
__vpred = __cmp_gt_pred(uint4, uint4);
__vpred = __cmp_gt_pred(uint8, uint8);
__vpred = __cmp_gt_pred(uint16, uint16);

VCMPGTW
__vpred = __cmp_gt_pred(int, int);
__vpred = __cmp_gt_pred(int2, int2);
__vpred = __cmp_gt_pred(int3, int3);
__vpred = __cmp_gt_pred(int4, int4);
__vpred = __cmp_gt_pred(int8, int8);
__vpred = __cmp_gt_pred(int16, int16);

*/

#define __cmp_gt_pred(a,b) __overload("__cmp_gt_pred",(a),(b))((a),(b))

/*-----------------------------------------------------------------------------
* ID: __cmp_le_pred
*----------------------------------------------------------------------------*/
/*

VCMPLEDP
__vpred = __cmp_le_pred(double, double);
__vpred = __cmp_le_pred(double2, double2);
__vpred = __cmp_le_pred(double3, double3);
__vpred = __cmp_le_pred(double4, double4);
__vpred = __cmp_le_pred(double8, double8);

VCMPLESP
__vpred = __cmp_le_pred(float, float);
__vpred = __cmp_le_pred(float2, float2);
__vpred = __cmp_le_pred(float3, float3);
__vpred = __cmp_le_pred(float4, float4);
__vpred = __cmp_le_pred(float8, float8);
__vpred = __cmp_le_pred(float16, float16);

*/

#define __cmp_le_pred(a,b) __overload("__cmp_le_pred",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __cmp_lt_pred
*----------------------------------------------------------------------------*/
/*

VCMPLTDP
__vpred = __cmp_lt_pred(double, double);
__vpred = __cmp_lt_pred(double2, double2);
__vpred = __cmp_lt_pred(double3, double3);
__vpred = __cmp_lt_pred(double4, double4);
__vpred = __cmp_lt_pred(double8, double8);

VCMPLTSP
__vpred = __cmp_lt_pred(float, float);
__vpred = __cmp_lt_pred(float2, float2);
__vpred = __cmp_lt_pred(float3, float3);
__vpred = __cmp_lt_pred(float4, float4);
__vpred = __cmp_lt_pred(float8, float8);
__vpred = __cmp_lt_pred(float16, float16);

*/

#define __cmp_lt_pred(a,b) __overload("__cmp_lt_pred",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __compress_set_bits_left
*----------------------------------------------------------------------------*/
/*

COMPRESSL
__vpred = __compress_set_bits_left(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __compress_set_bits_right
*----------------------------------------------------------------------------*/
/*

COMPRESSR
__vpred = __compress_set_bits_right(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __decimate_char
*----------------------------------------------------------------------------*/
/*

DECIMATEB
__vpred = __decimate_char(__vpred, __vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __decimate_int
*----------------------------------------------------------------------------*/
/*

DECIMATEW
__vpred = __decimate_int(__vpred, __vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __decimate_long
*----------------------------------------------------------------------------*/
/*

DECIMATED
__vpred = __decimate_long(__vpred, __vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __decimate_short
*----------------------------------------------------------------------------*/
/*

DECIMATEH
__vpred = __decimate_short(__vpred, __vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __duplicate_pred_high_char
*----------------------------------------------------------------------------*/
/*

PDUPH2B
__vpred = __duplicate_pred_high_char(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __duplicate_pred_high_int
*----------------------------------------------------------------------------*/
/*

PDUPH2W
__vpred = __duplicate_pred_high_int(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __duplicate_pred_high_long
*----------------------------------------------------------------------------*/
/*

PDUPH2D
__vpred = __duplicate_pred_high_long(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __duplicate_pred_high_short
*----------------------------------------------------------------------------*/
/*

PDUPH2H
__vpred = __duplicate_pred_high_short(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __duplicate_pred_low_char
*----------------------------------------------------------------------------*/
/*

PDUPL2B
__vpred = __duplicate_pred_low_char(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __duplicate_pred_low_int
*----------------------------------------------------------------------------*/
/*

PDUPL2W
__vpred = __duplicate_pred_low_int(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __duplicate_pred_low_long
*----------------------------------------------------------------------------*/
/*

PDUPL2D
__vpred = __duplicate_pred_low_long(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __duplicate_pred_low_short
*----------------------------------------------------------------------------*/
/*

PDUPL2H
__vpred = __duplicate_pred_low_short(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __expand
*----------------------------------------------------------------------------*/
/*

VPXPND
char64 = __expand(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __gather_set_bits
*----------------------------------------------------------------------------*/
/*

VGATHERB
char64 = __gather_set_bits(__vpred, char64);

*/


/*-----------------------------------------------------------------------------
* ID: __gather_unset_bits
*----------------------------------------------------------------------------*/
/*

VGATHERNB
char64 = __gather_unset_bits(__vpred, char64);

*/


/*-----------------------------------------------------------------------------
* ID: __mask_char
*----------------------------------------------------------------------------*/
/*

MASKB
__vpred = __mask_char(uint);
__vpred = __mask_char((uchar)(k));

*/

#define __mask_char(a) __overload("__mask_char",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __mask_int
*----------------------------------------------------------------------------*/
/*

MASKW
__vpred = __mask_int(uint);
__vpred = __mask_int((uchar)(k));

*/

#define __mask_int(a) __overload("__mask_int",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __mask_long
*----------------------------------------------------------------------------*/
/*

MASKD
__vpred = __mask_long(uint);
__vpred = __mask_long((uchar)(k));

*/

#define __mask_long(a) __overload("__mask_long",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __mask_short
*----------------------------------------------------------------------------*/
/*

MASKH
__vpred = __mask_short(uint);
__vpred = __mask_short((uchar)(k));

*/

#define __mask_short(a) __overload("__mask_short",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __max_circ_pred
*----------------------------------------------------------------------------*/
/*

VCMAXPB
__max_circ_pred(char, char&, __vpred&);
__max_circ_pred(char2, char2&, __vpred&);
__max_circ_pred(char3, char3&, __vpred&);
__max_circ_pred(char4, char4&, __vpred&);
__max_circ_pred(char8, char8&, __vpred&);
__max_circ_pred(char16, char16&, __vpred&);
__max_circ_pred(char32, char32&, __vpred&);
__max_circ_pred(char64, char64&, __vpred&);

VCMAXPH
__max_circ_pred(short, short&, __vpred&);
__max_circ_pred(short2, short2&, __vpred&);
__max_circ_pred(short3, short3&, __vpred&);
__max_circ_pred(short4, short4&, __vpred&);
__max_circ_pred(short8, short8&, __vpred&);
__max_circ_pred(short16, short16&, __vpred&);
__max_circ_pred(short32, short32&, __vpred&);

*/

#define __max_circ_pred(a,b,c) __overload("__max_circ_pred",(a),(b),(c))((a),(b),(c))

/*-----------------------------------------------------------------------------
* ID: __max_index
*----------------------------------------------------------------------------*/
/*

VMAXPB
__max_index(char, char&, __vpred&);
__max_index(char2, char2&, __vpred&);
__max_index(char3, char3&, __vpred&);
__max_index(char4, char4&, __vpred&);
__max_index(char8, char8&, __vpred&);
__max_index(char16, char16&, __vpred&);
__max_index(char32, char32&, __vpred&);
__max_index(char64, char64&, __vpred&);

VMAXPD
__max_index(long, long&, __vpred&);
__max_index(long2, long2&, __vpred&);
__max_index(long3, long3&, __vpred&);
__max_index(long4, long4&, __vpred&);
__max_index(long8, long8&, __vpred&);

VMAXPH
__max_index(short, short&, __vpred&);
__max_index(short2, short2&, __vpred&);
__max_index(short3, short3&, __vpred&);
__max_index(short4, short4&, __vpred&);
__max_index(short8, short8&, __vpred&);
__max_index(short16, short16&, __vpred&);
__max_index(short32, short32&, __vpred&);

VMAXPW
__max_index(int, int&, __vpred&);
__max_index(int2, int2&, __vpred&);
__max_index(int3, int3&, __vpred&);
__max_index(int4, int4&, __vpred&);
__max_index(int8, int8&, __vpred&);
__max_index(int16, int16&, __vpred&);

VMAXUPB
__max_index(uchar, uchar&, __vpred&);
__max_index(uchar2, uchar2&, __vpred&);
__max_index(uchar3, uchar3&, __vpred&);
__max_index(uchar4, uchar4&, __vpred&);
__max_index(uchar8, uchar8&, __vpred&);
__max_index(uchar16, uchar16&, __vpred&);
__max_index(uchar32, uchar32&, __vpred&);
__max_index(uchar64, uchar64&, __vpred&);

VMAXUPD
__max_index(ulong, ulong&, __vpred&);
__max_index(ulong2, ulong2&, __vpred&);
__max_index(ulong3, ulong3&, __vpred&);
__max_index(ulong4, ulong4&, __vpred&);
__max_index(ulong8, ulong8&, __vpred&);

VMAXUPH
__max_index(ushort, ushort&, __vpred&);
__max_index(ushort2, ushort2&, __vpred&);
__max_index(ushort3, ushort3&, __vpred&);
__max_index(ushort4, ushort4&, __vpred&);
__max_index(ushort8, ushort8&, __vpred&);
__max_index(ushort16, ushort16&, __vpred&);
__max_index(ushort32, ushort32&, __vpred&);

VMAXUPW
__max_index(uint, uint&, __vpred&);
__max_index(uint2, uint2&, __vpred&);
__max_index(uint3, uint3&, __vpred&);
__max_index(uint4, uint4&, __vpred&);
__max_index(uint8, uint8&, __vpred&);
__max_index(uint16, uint16&, __vpred&);

*/

#define __max_index(a,b,c) __overload("__max_index",(a),(b),(c))((a),(b),(c))

/*-----------------------------------------------------------------------------
* ID: __min_index
*----------------------------------------------------------------------------*/
/*

VMINPB
__min_index(char, char&, __vpred&);
__min_index(char2, char2&, __vpred&);
__min_index(char3, char3&, __vpred&);
__min_index(char4, char4&, __vpred&);
__min_index(char8, char8&, __vpred&);
__min_index(char16, char16&, __vpred&);
__min_index(char32, char32&, __vpred&);
__min_index(char64, char64&, __vpred&);

VMINPD
__min_index(long, long&, __vpred&);
__min_index(long2, long2&, __vpred&);
__min_index(long3, long3&, __vpred&);
__min_index(long4, long4&, __vpred&);
__min_index(long8, long8&, __vpred&);

VMINPH
__min_index(short, short&, __vpred&);
__min_index(short2, short2&, __vpred&);
__min_index(short3, short3&, __vpred&);
__min_index(short4, short4&, __vpred&);
__min_index(short8, short8&, __vpred&);
__min_index(short16, short16&, __vpred&);
__min_index(short32, short32&, __vpred&);

VMINPW
__min_index(int, int&, __vpred&);
__min_index(int2, int2&, __vpred&);
__min_index(int3, int3&, __vpred&);
__min_index(int4, int4&, __vpred&);
__min_index(int8, int8&, __vpred&);
__min_index(int16, int16&, __vpred&);

VMINUPB
__min_index(uchar, uchar&, __vpred&);
__min_index(uchar2, uchar2&, __vpred&);
__min_index(uchar3, uchar3&, __vpred&);
__min_index(uchar4, uchar4&, __vpred&);
__min_index(uchar8, uchar8&, __vpred&);
__min_index(uchar16, uchar16&, __vpred&);
__min_index(uchar32, uchar32&, __vpred&);
__min_index(uchar64, uchar64&, __vpred&);

VMINUPD
__min_index(ulong, ulong&, __vpred&);
__min_index(ulong2, ulong2&, __vpred&);
__min_index(ulong3, ulong3&, __vpred&);
__min_index(ulong4, ulong4&, __vpred&);
__min_index(ulong8, ulong8&, __vpred&);

VMINUPH
__min_index(ushort, ushort&, __vpred&);
__min_index(ushort2, ushort2&, __vpred&);
__min_index(ushort3, ushort3&, __vpred&);
__min_index(ushort4, ushort4&, __vpred&);
__min_index(ushort8, ushort8&, __vpred&);
__min_index(ushort16, ushort16&, __vpred&);
__min_index(ushort32, ushort32&, __vpred&);

VMINUPW
__min_index(uint, uint&, __vpred&);
__min_index(uint2, uint2&, __vpred&);
__min_index(uint3, uint3&, __vpred&);
__min_index(uint4, uint4&, __vpred&);
__min_index(uint8, uint8&, __vpred&);
__min_index(uint16, uint16&, __vpred&);

*/

#define __min_index(a,b,c) __overload("__min_index",(a),(b),(c))((a),(b),(c))

/*-----------------------------------------------------------------------------
* ID: __nand
*----------------------------------------------------------------------------*/
/*

NAND
__vpred = __nand(__vpred, __vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __negate
*----------------------------------------------------------------------------*/
/*

NOT
__vpred = __negate(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __nor
*----------------------------------------------------------------------------*/
/*

NOR
__vpred = __nor(__vpred, __vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __or
*----------------------------------------------------------------------------*/
/*

OR
__vpred = __or(__vpred, __vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __orn
*----------------------------------------------------------------------------*/
/*

ORN
__vpred = __orn(__vpred, __vpred);


*/


/*-----------------------------------------------------------------------------
* ID: __parallel_pack_dup_16way
*----------------------------------------------------------------------------*/
/*

VPPACKDUP16W
uint16 = __parallel_pack_dup_16way(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __parallel_pack_dup_8way
*----------------------------------------------------------------------------*/
/*

VPPACKDUP8W
uint16 = __parallel_pack_dup_8way(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __popcount_char
*----------------------------------------------------------------------------*/
/*

PBITCNTB
uint = __popcount_char(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __popcount_gather_char
*----------------------------------------------------------------------------*/
/*

PCNTGATHERB
__popcount_gather_char(__vpred, uint&, __vpred&);

*/


/*-----------------------------------------------------------------------------
* ID: __popcount_gather_int
*----------------------------------------------------------------------------*/
/*

PCNTGATHERW
__popcount_gather_int(__vpred, uint&, __vpred&);

*/


/*-----------------------------------------------------------------------------
* ID: __popcount_gather_long
*----------------------------------------------------------------------------*/
/*

PCNTGATHERD
__popcount_gather_long(__vpred, uint&, __vpred&);

*/


/*-----------------------------------------------------------------------------
* ID: __popcount_gather_short
*----------------------------------------------------------------------------*/
/*

PCNTGATHERH
__popcount_gather_short(__vpred, uint&, __vpred&);

*/


/*-----------------------------------------------------------------------------
* ID: __popcount_int
*----------------------------------------------------------------------------*/
/*

PBITCNTW
uint = __popcount_int(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __popcount_long
*----------------------------------------------------------------------------*/
/*

PBITCNTD
uint = __popcount_long(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __popcount_short
*----------------------------------------------------------------------------*/
/*

PBITCNTH
uint = __popcount_short(__vpred);

*/



/*-----------------------------------------------------------------------------
* ID: __rightmost_bit_detect_char
*----------------------------------------------------------------------------*/
/*

PRMBDB
uint = __rightmost_bit_detect_char(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __rightmost_bit_detect_int
*----------------------------------------------------------------------------*/
/*

PRMBDW
uint = __rightmost_bit_detect_int(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __rightmost_bit_detect_long
*----------------------------------------------------------------------------*/
/*

PRMBDD
uint = __rightmost_bit_detect_long(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __rightmost_bit_detect_short
*----------------------------------------------------------------------------*/
/*

PRMBDH
uint = __rightmost_bit_detect_short(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __scatter_set_bits
*----------------------------------------------------------------------------*/
/*

VSCATTERB
char64 = __scatter_set_bits(__vpred, char64);

*/


/*-----------------------------------------------------------------------------
* ID: __scatter_unset_bits
*----------------------------------------------------------------------------*/
/*

VSCATTERNB
char64 = __scatter_unset_bits(__vpred, char64);

*/


/*-----------------------------------------------------------------------------
* ID: __select
*----------------------------------------------------------------------------*/
/*

VSEL
char = __select(__vpred, char, char);
char2 = __select(__vpred, char2, char2);
char3 = __select(__vpred, char3, char3);
char4 = __select(__vpred, char4, char4);
char8 = __select(__vpred, char8, char8);
char16 = __select(__vpred, char16, char16);
char32 = __select(__vpred, char32, char32);
char64 = __select(__vpred, char64, char64);
short = __select(__vpred, short, short);
short2 = __select(__vpred, short2, short2);
short3 = __select(__vpred, short3, short3);
short4 = __select(__vpred, short4, short4);
short8 = __select(__vpred, short8, short8);
short16 = __select(__vpred, short16, short16);
short32 = __select(__vpred, short32, short32);
int = __select(__vpred, int, int);
int2 = __select(__vpred, int2, int2);
int3 = __select(__vpred, int3, int3);
int4 = __select(__vpred, int4, int4);
int8 = __select(__vpred, int8, int8);
int16 = __select(__vpred, int16, int16);
long = __select(__vpred, long, long);
long2 = __select(__vpred, long2, long2);
long3 = __select(__vpred, long3, long3);
long4 = __select(__vpred, long4, long4);
long8 = __select(__vpred, long8, long8);
int = __select(__vpred, int, (int)(k));
int2 = __select(__vpred, int2, (int2)(k));
int3 = __select(__vpred, int3, (int3)(k));
int4 = __select(__vpred, int4, (int4)(k));
int8 = __select(__vpred, int8, (int8)(k));
int16 = __select(__vpred, int16, (int16)(k));
cchar = __select(__vpred, cchar, cchar);
cchar2 = __select(__vpred, cchar2, cchar2);
cchar4 = __select(__vpred, cchar4, cchar4);
cchar8 = __select(__vpred, cchar8, cchar8);
cchar16 = __select(__vpred, cchar16, cchar16);
cchar32 = __select(__vpred, cchar32, cchar32);
uchar = __select(__vpred, uchar, uchar);
uchar2 = __select(__vpred, uchar2, uchar2);
uchar3 = __select(__vpred, uchar3, uchar3);
uchar4 = __select(__vpred, uchar4, uchar4);
uchar8 = __select(__vpred, uchar8, uchar8);
uchar16 = __select(__vpred, uchar16, uchar16);
uchar32 = __select(__vpred, uchar32, uchar32);
uchar64 = __select(__vpred, uchar64, uchar64);
cshort = __select(__vpred, cshort, cshort);
cshort2 = __select(__vpred, cshort2, cshort2);
cshort4 = __select(__vpred, cshort4, cshort4);
cshort8 = __select(__vpred, cshort8, cshort8);
cshort16 = __select(__vpred, cshort16, cshort16);
ushort = __select(__vpred, ushort, ushort);
ushort2 = __select(__vpred, ushort2, ushort2);
ushort3 = __select(__vpred, ushort3, ushort3);
ushort4 = __select(__vpred, ushort4, ushort4);
ushort8 = __select(__vpred, ushort8, ushort8);
ushort16 = __select(__vpred, ushort16, ushort16);
ushort32 = __select(__vpred, ushort32, ushort32);
float = __select(__vpred, float, float);
float2 = __select(__vpred, float2, float2);
float3 = __select(__vpred, float3, float3);
float4 = __select(__vpred, float4, float4);
float8 = __select(__vpred, float8, float8);
float16 = __select(__vpred, float16, float16);
cfloat = __select(__vpred, cfloat, cfloat);
cfloat2 = __select(__vpred, cfloat2, cfloat2);
cfloat4 = __select(__vpred, cfloat4, cfloat4);
cfloat8 = __select(__vpred, cfloat8, cfloat8);
cint = __select(__vpred, cint, cint);
cint2 = __select(__vpred, cint2, cint2);
cint4 = __select(__vpred, cint4, cint4);
cint8 = __select(__vpred, cint8, cint8);
uint = __select(__vpred, uint, uint);
uint2 = __select(__vpred, uint2, uint2);
uint3 = __select(__vpred, uint3, uint3);
uint4 = __select(__vpred, uint4, uint4);
uint8 = __select(__vpred, uint8, uint8);
uint16 = __select(__vpred, uint16, uint16);
double = __select(__vpred, double, double);
double2 = __select(__vpred, double2, double2);
double3 = __select(__vpred, double3, double3);
double4 = __select(__vpred, double4, double4);
double8 = __select(__vpred, double8, double8);
cdouble = __select(__vpred, cdouble, cdouble);
cdouble2 = __select(__vpred, cdouble2, cdouble2);
cdouble4 = __select(__vpred, cdouble4, cdouble4);
clong = __select(__vpred, clong, clong);
clong2 = __select(__vpred, clong2, clong2);
clong4 = __select(__vpred, clong4, clong4);
ulong = __select(__vpred, ulong, ulong);
ulong2 = __select(__vpred, ulong2, ulong2);
ulong3 = __select(__vpred, ulong3, ulong3);
ulong4 = __select(__vpred, ulong4, ulong4);
ulong8 = __select(__vpred, ulong8, ulong8);
float = __select(__vpred, float, (float)(k));
float2 = __select(__vpred, float2, (float2)(k));
float3 = __select(__vpred, float3, (float3)(k));
float4 = __select(__vpred, float4, (float4)(k));
float8 = __select(__vpred, float8, (float8)(k));
float16 = __select(__vpred, float16, (float16)(k));
uint = __select(__vpred, uint, (uint)(k));
uint2 = __select(__vpred, uint2, (uint2)(k));
uint3 = __select(__vpred, uint3, (uint3)(k));
uint4 = __select(__vpred, uint4, (uint4)(k));
uint8 = __select(__vpred, uint8, (uint8)(k));
uint16 = __select(__vpred, uint16, (uint16)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __shift_left_conditional
*----------------------------------------------------------------------------*/
/*

VSHLCB
char = __shift_left_conditional(__vpred, char, char);
char2 = __shift_left_conditional(__vpred, char2, char2);
char3 = __shift_left_conditional(__vpred, char3, char3);
char4 = __shift_left_conditional(__vpred, char4, char4);
char8 = __shift_left_conditional(__vpred, char8, char8);
char16 = __shift_left_conditional(__vpred, char16, char16);
char32 = __shift_left_conditional(__vpred, char32, char32);
char64 = __shift_left_conditional(__vpred, char64, char64);
uchar = __shift_left_conditional(__vpred, uchar, uchar);
uchar2 = __shift_left_conditional(__vpred, uchar2, uchar2);
uchar3 = __shift_left_conditional(__vpred, uchar3, uchar3);
uchar4 = __shift_left_conditional(__vpred, uchar4, uchar4);
uchar8 = __shift_left_conditional(__vpred, uchar8, uchar8);
uchar16 = __shift_left_conditional(__vpred, uchar16, uchar16);
uchar32 = __shift_left_conditional(__vpred, uchar32, uchar32);
uchar64 = __shift_left_conditional(__vpred, uchar64, uchar64);

VSHLCH
short = __shift_left_conditional(__vpred, short, short);
short2 = __shift_left_conditional(__vpred, short2, short2);
short3 = __shift_left_conditional(__vpred, short3, short3);
short4 = __shift_left_conditional(__vpred, short4, short4);
short8 = __shift_left_conditional(__vpred, short8, short8);
short16 = __shift_left_conditional(__vpred, short16, short16);
short32 = __shift_left_conditional(__vpred, short32, short32);
ushort = __shift_left_conditional(__vpred, ushort, ushort);
ushort2 = __shift_left_conditional(__vpred, ushort2, ushort2);
ushort3 = __shift_left_conditional(__vpred, ushort3, ushort3);
ushort4 = __shift_left_conditional(__vpred, ushort4, ushort4);
ushort8 = __shift_left_conditional(__vpred, ushort8, ushort8);
ushort16 = __shift_left_conditional(__vpred, ushort16, ushort16);
ushort32 = __shift_left_conditional(__vpred, ushort32, ushort32);

VSHLCW
int = __shift_left_conditional(__vpred, int, int);
int2 = __shift_left_conditional(__vpred, int2, int2);
int3 = __shift_left_conditional(__vpred, int3, int3);
int4 = __shift_left_conditional(__vpred, int4, int4);
int8 = __shift_left_conditional(__vpred, int8, int8);
int16 = __shift_left_conditional(__vpred, int16, int16);
uint = __shift_left_conditional(__vpred, uint, uint);
uint2 = __shift_left_conditional(__vpred, uint2, uint2);
uint3 = __shift_left_conditional(__vpred, uint3, uint3);
uint4 = __shift_left_conditional(__vpred, uint4, uint4);
uint8 = __shift_left_conditional(__vpred, uint8, uint8);
uint16 = __shift_left_conditional(__vpred, uint16, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __xnor
*----------------------------------------------------------------------------*/
/*

XNOR
__vpred = __xnor(__vpred, __vpred);


*/


/*-----------------------------------------------------------------------------
* ID: __xor
*----------------------------------------------------------------------------*/
/*

XOR
__vpred = __xor(__vpred, __vpred);

*/

#endif /* __C7X_VPRED_H */
