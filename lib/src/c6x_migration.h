/*****************************************************************************/
/*  C6X_MIGRATION.H                                                          */
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
#ifndef __C6X_MIGRATION_H
#define __C6X_MIGRATION_H

#include <stdint.h>
#include <c7x.h>

#define __BUILTIN   __attribute__((builtin))
#define __BUILTIN_M __BUILTIN __attribute__((impure))

#define __PRAGMA(x) _Pragma(#x)
#ifdef __cplusplus
#  define __INLINE_FUNC(x) __PRAGMA(FUNC_ALWAYS_INLINE)
#else
#  define __INLINE_FUNC(x) __PRAGMA(FUNC_ALWAYS_INLINE(x))
#endif

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*****************************************************************************/
/* How to use this file                                                      */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* This header file provides definitions for C6000 specific macros and       */
/* intrinsics.  The implementations of these intrinsics may be as routines   */
/* that will be inlined.                                                     */
/*                                                                           */
/* It is meant as a reference that can be modified and included in           */
/* projects in place of the c6x.h header file provided with the Texas        */
/* Instruments C6000 C/C++ Compiler installation package.                    */
/*                                                                           */
/* The three sections of this file are as follows:                           */
/*   1. Predefined macros                                                    */
/*     Macros and keywords that would have been defined internally by the    */
/*     C6000 compiler, but do not exist within the C7000 compiler.           */
/*   2. Legacy types                                                         */
/*     Definitions and explanations of types that exist in the C6000         */
/*     programming model, but not in the C7000 programming model. Also       */
/*     contains examples of how to migrate current projects to use the C7000 */
/*     OpenCL vector type programming model.                                 */
/*   3. Legacy intrinsics                                                    */
/*     Declarations of builtin functions defined for the C6000 programming   */
/*     model that are no longer supported for C7000.                         */
/*                                                                           */
/*     Some of the builtin functions have a C7000 instruction that provides  */
/*     identical functionality. These functions are marked with a comment    */
/*     that contains the equivalent C7000 mnemonic to use. This mnemonic is  */
/*     a key that can be used to search through the c7x.h header file to     */
/*     find an equivalent C/C++ idiom using the C7000 programming model.     */
/*                                                                           */
/*     Instructions which do not contain a mapping to a C7000 mnemonic must  */
/*     be emulated by a different instruction or instructions.               */
/*---------------------------------------------------------------------------*/

/*****************************************************************************/
/* Predefined Macros for Legacy Types                                        */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* Target and subtarget macros                                               */
/* These macros allow for the compilation of code that has been specialized  */
/* for C6000, but is being compiled as-is for C7000. The specific subtarget  */
/* being emulated by this list of macros is C6600.                           */
/*                                                                           */
/* For C7000-specialized code, use the C7000-specific target macros          */
/* __C7000__ or __C7100__.                                                   */
/*---------------------------------------------------------------------------*/
#define _TMS320C6X        1
#define __TMS320C6X__     1
#define _TMS320C6600      1
#define _TMS320C6740      1
#define _TMS320C6700_PLUS 1
#define _TMS320C67_PLUS   1
#define _TMS320C6700      1
#define _TMS320C64_PLUS   1
#define _TMS320C6400_PLUS 1
#define _TMS320C6400      1
#define __C6X_MIGRATION__ 1

/*---------------------------------------------------------------------------*/
/* __TI_ELFABI__                                                             */
/* This macro is deprecated. Use __TI_EABI__ in its place                    */
/*---------------------------------------------------------------------------*/
#define __TI_ELFABI__ __TI_EABI__

/*---------------------------------------------------------------------------*/
/* _LITTLE_ENDIAN and _BIG_ENDIAN                                            */
/* These macros are deprecated. Use __little_endian__ and __big_endian__.    */
/*---------------------------------------------------------------------------*/
#if __little_endian__
    #define _LITTLE_ENDIAN 1
#elif __big_endian__
    #define _BIG_ENDIAN    1
#endif

/*---------------------------------------------------------------------------*/
/* The near and far keywords are not supported on C7000, but are defined     */
/* as empty macros for legacy code support.                                  */
/*---------------------------------------------------------------------------*/
#define near
#define _near
#define __near
#define far
#define _far
#define __far

/*---------------------------------------------------------------------------*/
/* C6000's delayed move is not supported on C7000 as a delayed move.         */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_mvd)
static inline int _mvd(int s1)
{
    return s1;
}

/*****************************************************************************/
/* __x128_t                                                                  */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* The __x128_t type is a legacy type used for representing vectors.         */
/*                                                                           */
/* It is defined as an opaque container, meaning that only intrinsics may    */
/* use or modify its contents. Therefore, direct accesses to its contents    */
/* through C are undefined behavior.                                         */
/*                                                                           */
/* When migrating code from C6000 to C7000, replace uses of __x128_t with    */
/* OpenCL native vector types.                                               */
/*---------------------------------------------------------------------------*/
typedef struct
{
    int32_t _v[4];
} __attribute__((aligned(16))) __attribute__((vector_type)) __x128_t;

/*---------------------------------------------------------------------------*/
/* __x128_t Generators                                                       */
/*                                                                           */
/* Replace with OpenCL initializations, e.g.:                                */
/* double2 = (double2)(1.0, 2.0); // Instead of _dto128(1.0, 2.0);           */
/* int4 = (int4)(x, y, z, h);     // Instead of _llto128(itoll(h, z),        */
/*                                //                     itoll(y, x));       */
/*---------------------------------------------------------------------------*/
__x128_t __BUILTIN _dup32_128(unsigned);
__x128_t __BUILTIN _fto128(float, float, float, float);
__x128_t __BUILTIN _ito128(unsigned, unsigned, unsigned, unsigned);
__x128_t __BUILTIN _dto128(double, double);
__x128_t __BUILTIN _llto128(long long, long long);

/*---------------------------------------------------------------------------*/
/* __x128_t Accessors                                                        */
/*                                                                           */
/* Replace with OpenCL accessors, e.g.:                                      */
/* int4 a = (int4)(1, 2, 3, 4);                                              */
/* a.s3   // Instead of _get32_128(a, 3);                                    */
/* a.even // Instead of _itoll(_get32_128(a, 0), _get32_128(a, 2));          */
/* a.hi   // Instead of _hi128(a);                                           */
/* a.lo   // Instead of _lo128(a);                                           */
/*---------------------------------------------------------------------------*/
long long __BUILTIN _hi128(__x128_t);
long long __BUILTIN _lo128(__x128_t);
double __BUILTIN _hid128(__x128_t);
double __BUILTIN _lod128(__x128_t);

unsigned __BUILTIN _get32_128(__x128_t, __attribute__((constrange(0,3))) unsigned);
float __BUILTIN _get32f_128(__x128_t, __attribute__((constrange(0,3))) unsigned);

/*****************************************************************************/
/* __float2_t                                                                */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* __float2_t is a legacy type that replaced the use of 'double' for packed  */
/* 32-bit float data.                                                        */
/*                                                                           */
/* Replace uses of this type with the OpenCL native vector type 'float2'.    */
/*---------------------------------------------------------------------------*/
typedef double __float2_t;

/*---------------------------------------------------------------------------*/
/* __as_float2_t provided for compatibility between host emulation and cl7x  */
/* where the type of __float2_t differs. For cl7x, this is __as_double(),    */
/* for host emulation, this is an initialization of the struct.              */
/*---------------------------------------------------------------------------*/
#define __as_float2_t __as_double

/*---------------------------------------------------------------------------*/
/* Conversions from 16-bit precision ints to __float2_t                      */
/*                                                                           */
/* C7000 ISA:                                                                */
/*   VINTHSPL                                                                */
/*   VINTHSPUL                                                               */
/*   VINTHSPH                                                                */
/*   VINTHSPUH                                                               */
/*                                                                           */
/* However, in some situations, converting 16-bit integers to 32-bit         */
/* integers first may yield superior performance.  For example, VUNPKW       */
/* followed by VINTSP or VINTSPU.                                            */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_dinthsp)
static inline __float2_t _dinthsp(unsigned s1)
{
    return __as_float2_t(__convert_float2(__as_short2(s1)));
}

__INLINE_FUNC(_dinthspu)
static inline __float2_t _dinthspu(unsigned s1)
{
    return __as_float2_t(__convert_float2(__as_ushort2(s1)));
}

/*---------------------------------------------------------------------------*/
/* Conversion from 32-bit precision ints to __float2_t                       */
/*                                                                           */
/* C7000 ISA:                                                                */
/*   VINTSP                                                                  */
/*   VINTSPU                                                                 */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_dintsp)
static inline __float2_t _dintsp(long long s1)
{
    return __as_float2_t(__int_to_float(__as_int2(s1)));
}

__INLINE_FUNC(_dintspu)
static inline __float2_t _dintspu(long long s1)
{
    return __as_float2_t(__int_to_float(__as_uint2(s1)));
}

/*---------------------------------------------------------------------------*/
/* Conversion from __float2_t to 16-bit precision ints                       */
/*                                                                           */
/* C7000 ISA:                                                                */
/*   VSPINTHPK                                                               */
/*                                                                           */
/* See Also:                                                                 */
/*   VSPINTH                                                                 */
/*                                                                           */
/* However, in some situations, converting to 32-bit integers first may      */
/* yield superior performance due to data layout.  For example, VSPINT       */
/* followed by VHPACKL.                                                      */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_dspinth)
static inline unsigned _dspinth(__float2_t s1)
{
    return __as_uint(__convert_short2(__float_to_int(__as_float2(s1))));
}

/*---------------------------------------------------------------------------*/
/* Conversion from __float2_t to 2 32-bit precision ints                     */
/*                                                                           */
/* C7000 ISA:                                                                */
/*   VSPINT                                                                  */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_dspint)
static inline long long _dspint(__float2_t s1)
{
    return __as_long(__float_to_int(__as_float2(s1)));
}

/*---------------------------------------------------------------------------*/
/* Reinterpretation between 64-bit integers and __float2_t                   */
/*                                                                           */
/* Replace the __float2_t type with the OpenCL float2 type, then use         */
/* OpenCL-styled reinterpret casts (as_double, as_float2)                    */
/*---------------------------------------------------------------------------*/
#define _lltof2  __as_float2_t
#define _f2toll(x)  ((long long)__as_long(x))

/*---------------------------------------------------------------------------*/
/* Replace __float2_t with the OpenCL float2 type, and use OpenCL vector     */
/* initialization, e.g.: (float2)(float, float)                              */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_ftof2)
static inline __float2_t _ftof2(float s1, float s2)
{
    return __as_float2_t((__float2)(s2, s1));
}

/*---------------------------------------------------------------------------*/
/* Replace __float2_t with the OpenCL float2 type, then use OpenCL accessors */
/* e.g.: float2.hi, float2.lo                                                */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_hif2)
static inline float _hif2(__float2_t s1)
{
    return __as_float2(s1).s1;
}
__INLINE_FUNC(_lof2)
static inline float _lof2(__float2_t s1)
{
    return __as_float2(s1).s0;
}

/*---------------------------------------------------------------------------*/
/* There is no difference between _amem and _mem for C7000, as all loads     */
/* and stores have unaligned capability. Replace these intrinsics with basic */
/* C dereference operators on a pointer to an OpenCL vector.                 */
/*---------------------------------------------------------------------------*/
#define _amem8_f2(p)       (*(__float2_t*)(char*)(p))
#define _amem8_f2_const(p) (*(__float2_t*)(char*)(p))
#define _mem8_f2(p)        (*(__float2_t*)(char*)(p))
#define _mem8_f2_const(p)  (*(__float2_t*)(char*)(p))

/*---------------------------------------------------------------------------*/
/* Use the PACKW or PACKWDLY4 instruction, reinterpret casting each source   */
/* to int if needed, and then casting the result to an OpenCL float2.        */
/*---------------------------------------------------------------------------*/
/* No delay for instructions with just a pack (same for _dmvd) */
#define _fdmv_f2   _ftof2
#define _fdmvd_f2  _ftof2

/*---------------------------------------------------------------------------*/
/* After changing references to __x128_t to use OpenCL vectors, replace      */
/* these two operations with OpenCL-style vector accessors.                  */
/*                                                                           */
/* e.g.:                                                                     */
/* float2 _hif2_128(float4 src) { return src.hi; }                           */
/*---------------------------------------------------------------------------*/
#define _hif2_128(x)  (__as_float2_t(_hi128(x)))
#define _lof2_128(x)  (__as_float2_t(_lo128(x)))

/*---------------------------------------------------------------------------*/
/* After changing references to __x128_t to use OpenCL vectors, replace      */
/* this intrinsic with an OpenCL initialization.                             */
/*---------------------------------------------------------------------------*/
#define _f2to128(x,y) (_llto128(__as_long(x),__as_long(y)))

/*---------------------------------------------------------------------------*/
/* Accessing the SAT bit or Floating Point status bits                       */
/*                                                                           */
/* These bits are set in the C7x FSR control register.  Access to the FSR is */
/* provided by the following API that can be used in legacy C6x source code. */
/* An 8bit value is returned containing the following fields:                */
/*                                                                           */
/* Bit 7: SAT   - Result is saturated Fixed Point Flag (C6X OPERATIONS ONLY) */
/* Bit 6: UNORD - Compare result is unordered Floating Point Flag            */
/* Bit 5: DEN   - Source is a Denorm Floating Point Flag                     */
/* Bit 4: INEX  - Result is inexact Floating Point Flag                      */
/* Bit 3: UNDER - Result is underflow Floating Point Flag                    */
/* Bit 2: OVER  - Result is overflow Floating Point Flag                     */
/* Bit 1: DIV0  - Divide by zero Floating Point Flag                         */
/* Bit 0: INVAL - Invalid Operations Floating Point Flag                     */
/*                                                                           */
/*    e.g.: uint8_t fsr_val = __get_C7X_FSR();                               */
/*                                                                           */
/* Please refer to the CPU micro architecture guide for more information on  */
/* how to interpret the FSR bits layout.                                     */
/*                                                                           */
/* NOTE: Accessing the SAT bit of the FSR is applicable only when migrating  */
/* C6000 supported operations using the legacy C6000 intrinsics defined in   */
/* this file. Accessing the SAT bit is NOT SUPPORTED for C7000 operations.   */
/*---------------------------------------------------------------------------*/
#define __get_C7X_FSR() __get_fsr_double(sizeof(double))

/*****************************************************************************/
/* __int40_t                                                                 */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* __int40_t is a legacy type that provided extended precision integer       */
/* arithmetic that was natively supported by C6000 subtargets. The 40-bit    */
/* type is not supported on C7000, and the following intrinsics must be      */
/* migrated manually to 64-bit arithmetic.                                   */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* Conversions between double-precision floating point and __int40_t         */
/*---------------------------------------------------------------------------*/
/* __int40_t __BUILTIN _dtol(double);                   */
/* double __BUILTIN _ltod(__int40_t);                   */

/*---------------------------------------------------------------------------*/
/* 40-bit intrinsics                                                         */
/*---------------------------------------------------------------------------*/
/* __int40_t __BUILTIN _labs(__int40_t);       VABSD    */
/* __int40_t __BUILTIN _ldotp2(int, int);      VDOTP2HD */
/* unsigned __BUILTIN _lnorm(__int40_t);       VNORMD   */
/* __int40_t __BUILTIN _lsadd(int, __int40_t); ADDD     */
/* __int40_t __BUILTIN _lssub(int, __int40_t); SUBD     */
/* int __BUILTIN _sat(__int40_t);              VSATLW   */

/*---------------------------------------------------------------------------*/
/* C7x int40 saturating conversions                                          */
/*---------------------------------------------------------------------------*/
/* long = __long_to_int40_sat(long);           VSATDL   */
/* int2 = __int40_to_int_sat(long);            VSATLW   */

/*****************************************************************************/
/* Legacy OpenCL vector types                                                */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* OpenCL v1.2 defines the long type as a 64-bit integer value, while C6000  */
/* defined it as either 32 or 40 bits, depending on certain configurations.  */
/* Because of this, C6000 could not use the OpenCL vector types based off of */
/* the 64-bit OpenCL long, instead supporting a new type as an extension     */
/* named 'longlong'.                                                         */
/*                                                                           */
/* The long type on C7000 is 64 bits, matching the OpenCL specification.     */
/*                                                                           */
/* The extension vector types are defined here for migration, but code       */
/* leveraging the 'longlong' type should be migrated to using the standard   */
/* long type specifier.                                                      */
/*---------------------------------------------------------------------------*/
#if !__TI_STRICT_ANSI_MODE__
typedef long     longlong;
typedef __long2  longlong2;
typedef __long3  longlong3;
typedef __long4  longlong4;
typedef __long8  longlong8;
typedef __long16 longlong16;

typedef __ulong   ulonglong;
typedef __ulong2  ulonglong2;
typedef __ulong3  ulonglong3;
typedef __ulong4  ulonglong4;
typedef __ulong8  ulonglong8;
typedef __ulong16 ulonglong16;
#endif
typedef long     __longlong;
typedef __long2  __longlong2;
typedef __long3  __longlong3;
typedef __long4  __longlong4;
typedef __long8  __longlong8;
typedef __long16 __longlong16;

typedef __ulong   __ulonglong;
typedef __ulong2  __ulonglong2;
typedef __ulong3  __ulonglong3;
typedef __ulong4  __ulonglong4;
typedef __ulong8  __ulonglong8;
typedef __ulong16 __ulonglong16;

/*****************************************************************************/
/* Legacy C6X Intrinsics                                                     */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* The following intrinsics were defined on C6000 to separate aligned and    */
/* unaligned loads and stores of 2, 4, and 8 byte data.                      */
/*                                                                           */
/* On C7000, all loads and stores are unaligned, so the intrinsics may be    */
/* broken down into native C dereferences.                                   */
/*---------------------------------------------------------------------------*/
#define _amem2(p)         (*(unsigned short*)(char*)(p))
#define _amem2_const(p)   (*(unsigned short*)(char*)(p))
#define _amem4(p)         (*(unsigned int*)(char*)(p))
#define _amem4_const(p)   (*(unsigned int*)(char*)(p))
#define _amem8(p)         (*(unsigned long*)(char*)(p))
#define _amem8_const(p)   (*(unsigned long*)(char*)(p))
#define _amemd8(p)        (*(double*)(char*)(p))
#define _amemd8_const(p)  (*(double*)(char*)(p))
#define _mem2(p)          (*(unsigned short*)(char*)(p))
#define _mem2_const(p)    (*(unsigned short*)(char*)(p))
#define _mem4(p)          (*(unsigned int*)(char*)(p))
#define _mem4_const(p)    (*(unsigned int*)(char*)(p))
#define _mem8(p)          (*(unsigned long*)(char*)(p))
#define _mem8_const(p)    (*(unsigned long*)(char*)(p))
#define _memd8(p)         (*(double*)(char*)(p))
#define _memd8_const(p)   (*(double*)(char*)(p))

/*---------------------------------------------------------------------------*/
/* The following declarations are C6000 intrinsics which are supported       */
/* by the C7000 ISA. A C7000 instruction mnemonic preceding the declaration  */
/* denotes that there is a direct translation available for migration.       */
/*                                                                           */
/* Operand types and C idioms for the C7000 instructions are described in    */
/* c7x.h, and can be searched through using the mnemonic as a key.           */
/*---------------------------------------------------------------------------*/
/* VADDSP */
__INLINE_FUNC(_daddsp)
static inline __float2_t _daddsp(__float2_t s1, __float2_t s2)
{
    return __as_float2_t(__as_float2(s1) + __as_float2(s2));
}
/* VSUBSP */
__INLINE_FUNC(_dsubsp)
static inline __float2_t _dsubsp(__float2_t s1, __float2_t s2)
{
    return __as_float2_t(__as_float2(s1) - __as_float2(s2));
}
/* VMPYSP */
__INLINE_FUNC(_dmpysp)
static inline __float2_t _dmpysp(__float2_t s1, __float2_t s2)
{
    return __as_float2_t(__as_float2(s1) * __as_float2(s2));
}
/* VCMPYSP */
__x128_t __BUILTIN _cmpysp(__float2_t, __float2_t);

/* VCCMATMPYHW */
__x128_t __BUILTIN _ccmatmpy(long long, __x128_t);
/* VCCMATMPYR1HH */
long long __BUILTIN _ccmatmpyr1(long long, __x128_t);
/* VCMATMPYHW */
__x128_t __BUILTIN _cmatmpy(long long, __x128_t);
/* VCMATMPYR1HH */
long long __BUILTIN _cmatmpyr1(long long, __x128_t);
/* VCMPYR1WW */
__INLINE_FUNC(_cmpy32r1)
static inline long long _cmpy32r1(long long s1, long long s2)
{
    return __as_long(__cmpy_fx(__as_cint(s1), __as_cint(s2)));
}
/* VCMPYHW */
__INLINE_FUNC(_cmpy)
static inline long long _cmpy(unsigned s1, unsigned s2)
{
    return __as_long(__cmpy_ext(__as_cshort(s1), __as_cshort(s2)));
}
/* VCMPYHW */
__x128_t __BUILTIN _dcmpy(long long, long long);
/* VCMPYRHH */
__INLINE_FUNC(_cmpyr)
static inline unsigned _cmpyr(unsigned s1, unsigned s2)
{
    return __as_uint(__cmpyr_fx(__as_cshort(s1), __as_cshort(s2)));
}
/* VCCMPYR1HH */
__INLINE_FUNC(_dccmpyr1)
static inline long long _dccmpyr1(long long s1, long long s2)
{
    return __as_long(__cmpy_conj_fx(__as_cshort2(s1), __as_cshort2(s2)));
}
/* VCMPYR1HH */
__INLINE_FUNC(_cmpyr1)
static inline unsigned _cmpyr1(unsigned s1, unsigned s2)
{
    return __as_uint(__cmpy_fx(__as_cshort(s1), __as_cshort(s2)));
}
/* VCMPYR1HH */
__INLINE_FUNC(_dcmpyr1)
static inline long long _dcmpyr1(long long s1, long long s2)
{
    return __as_long(__cmpy_fx(__as_cshort2(s1), __as_cshort2(s2)));
}
/* VCCMPYHW */
__x128_t __BUILTIN _dccmpy(long long, long long);
/* VCCMPYR1WW */
__INLINE_FUNC(_ccmpy32r1)
static inline long long _ccmpy32r1(long long s1, long long s2)
{
    return __as_long(__cmpy_conj_fx(__as_cint(s1), __as_cint(s2)));
}
/* VDOTP4HW */
long long __BUILTIN _ddotp4h(__x128_t, __x128_t);
/* VDOTP4SUHW */
long long __BUILTIN _ddotpsu4h(__x128_t, __x128_t);
/* C6DMPYHW */
__x128_t __BUILTIN _dmpy2(long long, long long);
/* C6DMPYSUBH */
__x128_t __BUILTIN _dmpysu4(long long, long long);
/* C6DMPYUHW */
__x128_t __BUILTIN _dmpyu2(long long, long long);
/* C6DMPYUBH */
__x128_t __BUILTIN _dmpyu4(long long, long long);
/* C6DSMPYHW */
__x128_t __BUILTIN _dsmpy2(long long, long long);
/* VMPYWW */
__x128_t __BUILTIN _qmpy32(__x128_t, __x128_t);
/* VMPYSP */
__x128_t __BUILTIN _qmpysp(__x128_t, __x128_t);
/* VSMPYR1WW */
__x128_t __BUILTIN _qsmpy32r1(__x128_t, __x128_t);

/* VABSW */
__INLINE_FUNC(_abs)
static inline int _abs(int s1)
{
    return __abs(s1);
}
/* VABSH */
__INLINE_FUNC(_abs2)
static inline int _abs2(int s1)
{
    return __as_int(__abs(__as_short2(s1)));
}
/* VADDH */
__INLINE_FUNC(_add2)
static inline int _add2(int s1, int s2)
{
    return __as_int(__as_short2(s1) + __as_short2(s2));
}
/* VADDB */
__INLINE_FUNC(_add4)
static inline int _add4(int s1, int s2)
{
    return __as_int(__as_char4(s1) + __as_char4(s2));
}
/* VAVGH */
__INLINE_FUNC(_avg2)
static inline int _avg2(int s1, int s2)
{
    return __as_int(__rhadd(__as_short2(s1), __as_short2(s2)));
}
/* VAVGUB */
__INLINE_FUNC(_avgu4)
static inline unsigned _avgu4(unsigned s1, unsigned s2)
{
    return __as_uint(__rhadd(__as_uchar4(s1), __as_uchar4(s2)));
}
/* VBITCNTB */
__INLINE_FUNC(_bitc4)
static inline unsigned _bitc4(unsigned s1)
{
    return __as_uint(__popcount(__as_char4(s1)));
}
/* VBITRW */
__INLINE_FUNC(_bitr)
static inline unsigned _bitr(unsigned s1)
{
    return __as_uint(__bit_reverse(__as_int(s1)));
}
/* CLR */
__INLINE_FUNC(_clr)
static inline unsigned _clr(unsigned s1, unsigned s2, unsigned s3)
{
    unsigned long e_s2 = (((unsigned long) s2) << 59) >> 54;
    unsigned long e_s3 = (((unsigned long) s3) << 59) >> 59;
    unsigned long tmp  = e_s2 | e_s3;
    return __as_uint(__clear(s1, (unsigned) tmp));
}
/* CLR */
__INLINE_FUNC(_clrr)
static inline unsigned _clrr(unsigned s1, int s2)
{
    return __as_uint(__clear(s1, __as_uint(s2)));
}
/* VCROT270H */
__INLINE_FUNC(_crot270)
static inline int _crot270(int s1)
{
    return __as_int(__crot270(__as_cshort(s1)));
}
/* VCROT90H */
__INLINE_FUNC(_crot90)
static inline int _crot90(int s1)
{
    return __as_int(__crot90(__as_cshort(s1)));
}
/* VADDW */
__INLINE_FUNC(_dadd)
static inline long long _dadd(long long s1, long long s2)
{
    return __as_long(__as_int2(s1) + __as_int2(s2));
}
/* VADDH */
__INLINE_FUNC(_dadd2)
static inline long long _dadd2(long long s1, long long s2)
{
    return __as_long(__as_short4(s1) + __as_short4(s2));
}
/* VADDW */
long long __BUILTIN _dadd_c(int, long long);
/* VAPYSH */
__INLINE_FUNC(_dapys2)
static inline long long _dapys2(long long s1, long long s2)
{
    return __as_long(__apply_sign(__as_short4(s2), __as_short4(s1)));
}
/* VAVGH */
__INLINE_FUNC(_davg2)
static inline long long _davg2(long long s1, long long s2)
{
    return __as_long(__rhadd(__as_short4(s1), __as_short4(s2)));
}
/* VAVGNRH */
__INLINE_FUNC(_davgnr2)
static inline long long _davgnr2(long long s1, long long s2)
{
    return __as_long(__hadd(__as_short4(s1), __as_short4(s2)));
}
/* VAVGNRUB */
__INLINE_FUNC(_davgnru4)
static inline long long _davgnru4(long long s1, long long s2)
{
    return __as_long(__hadd(__as_uchar8(s1), __as_uchar8(s2)));
}
/* VAVGUB */
__INLINE_FUNC(_davgu4)
static inline long long _davgu4(long long s1, long long s2)
{
    return __as_long(__rhadd(__as_uchar8(s1), __as_uchar8(s2)));
}
/* C6DCMPEQH */
__INLINE_FUNC(_dcmpeq2)
static inline unsigned _dcmpeq2(long long s1, long long s2)
{
    return __as_uchar(__c6dcmpeqh_ddr(__as_short4(s1), __as_short4(s2)));
}
/* C6DCMPEQB */
__INLINE_FUNC(_dcmpeq4)
static inline unsigned _dcmpeq4(long long s1, long long s2)
{
    return __as_uchar(__c6dcmpeqb_ddr(__as_char8(s1), __as_char8(s2)));
}
/* C6DCMPGTH */
__INLINE_FUNC(_dcmpgt2)
static inline unsigned _dcmpgt2(long long s1, long long s2)
{
    return __as_uchar(__c6dcmpgth_ddr(__as_short4(s1), __as_short4(s2)));
}
/* C6DCMPGTUB */
__INLINE_FUNC(_dcmpgtu4)
static inline unsigned _dcmpgtu4(long long s1, long long s2)
{
    return __c6dcmpgtub_ddr(__as_uchar8(s1), __as_uchar8(s2));
}
/* VCROT270H */
__INLINE_FUNC(_dcrot270)
static inline long long _dcrot270(long long s1)
{
    return __as_long(__crot270(__as_cshort2(s1)));
}
/* VCROT90H */
__INLINE_FUNC(_dcrot90)
static inline long long _dcrot90(long long s1)
{
    return __as_long(__crot90(__as_cshort2(s1)));
}
/* C6DDOTP2HHW */
__INLINE_FUNC(_ddotph2)
static inline long long _ddotph2(long long s1, unsigned s2)
{
    return __as_long(__c6ddotp2hhw_drd(__as_short4(s1), __as_short2(s2)));
}
/* C6DDOTP2HRHH */
__INLINE_FUNC(_ddotph2r)
static inline unsigned _ddotph2r(long long s1, unsigned s2)
{
    return __as_uint(__c6ddotp2hrhh_drr(__as_short4(s1), __as_short2(s2)));
}
/* C6DDOTP2LHW */
__INLINE_FUNC(_ddotpl2)
static inline long long _ddotpl2(long long s1, unsigned s2)
{
    return __as_long(__c6ddotp2lhw_drd(__as_short4(s1), __as_short2(s2)));
}
/* C6DDOTP2LRHH */
__INLINE_FUNC(_ddotpl2r)
static inline unsigned _ddotpl2r(long long s1, unsigned s2)
{
    return __as_uint(__c6ddotp2lrhh_drr(__as_short4(s1), __as_short2(s2)));
}
/* VBITDEALW */
__INLINE_FUNC(_deal)
static inline unsigned _deal(unsigned s1)
{
    return __as_uint(__deal_bit(__as_uint(s1)));
}
/* VMAXH */
__INLINE_FUNC(_dmax2)
static inline long long _dmax2(long long s1, long long s2)
{
    return __as_long(__max(__as_short4(s1), __as_short4(s2)));
}
/* VMAXUB */
__INLINE_FUNC(_dmaxu4)
static inline long long _dmaxu4(long long s1, long long s2)
{
    return __as_long(__max(__as_uchar8(s1), __as_uchar8(s2)));
}
/* VMINH */
__INLINE_FUNC(_dmin2)
static inline long long _dmin2(long long s1, long long s2)
{
    return __as_long(__min(__as_short4(s1), __as_short4(s2)));
}
/* VMINUB */
__INLINE_FUNC(_dminu4)
static inline long long _dminu4(long long s1, long long s2)
{
    return __as_long(__min(__as_uchar8(s1), __as_uchar8(s2)));
}
/* PACKW */
__INLINE_FUNC(_dmv)
static inline long long _dmv(unsigned s1, unsigned s2)
{
    return __as_long((__uint2)(s2, s1));
}
/* No delay for instructions with just a pack (same for _fdmvd) */
#define _dmvd(s1, s2) _dmv(__as_uint(s1), __as_uint(s2))
/* VDOTP2HW */
__INLINE_FUNC(_dotp2)
static inline int _dotp2(int s1, int s2)
{
    return __dotp2(__as_short2(s1), __as_short2(s2));
}
/*---------------------------------------------------------------------------*/
/* Although VDOTP4HW may be used to emulate _dotp4h, it may be beneficial to */
/* instead use VDOTP4HD to avoid the need for double vector inputs.          */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_dotp4h)
static inline int _dotp4h(long long s1, long long s2)
{
    return __saturate(__dotp4_ext(__as_short4(s1), __as_short4(s2)), (unsigned char)(32));
}
/* VDOTP4HD */
__INLINE_FUNC(_dotp4hll)
static inline long long _dotp4hll(long long s1, long long s2)
{
    return __dotp4_ext(__as_short4(s1), __as_short4(s2));
}
/*---------------------------------------------------------------------------*/
/* Although C6DOTPN2HW may be used to emulate _dotpn2, it may be beneficial  */
/* to instead use VDOTP2NWD to allow for vectorization.                      */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_dotpn2)
static inline int _dotpn2(int s1, int s2)
{
    return __dotp2_negate(__as_short2(s1), __as_short2(s2));
}
/*---------------------------------------------------------------------------*/
/* Although C6DOTPN2RSUHH may be used to emulate _dotpnrsu2, it may be       */
/* beneficial to instead use VDOTP2NWD to allow for vectorization.           */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_dotpnrsu2)
static inline int _dotpnrsu2(int s1, unsigned s2)
{
    return __dotp2_negate(__as_short2(s1), __as_ushort2(s2));
}
#define _dotpnrus2(u, s) _dotpnrsu2((s), (u))
/*---------------------------------------------------------------------------*/
/* Although C6DOTP2RSUHW may be used to emulate _dotprsu2, it may be         */
/* beneficial to instead use VDOTP2SUHW to allow for vectorization.          */
/*---------------------------------------------------------------------------*/
/* C6DOTP2RSUHW */
__INLINE_FUNC(_dotprsu2)
static inline int _dotprsu2(int s1, unsigned s2)
{
    return __dotp2_fx_ext(__as_short2(s1), __as_ushort2(s2));
}
/* VDOTP4SUBW */
__INLINE_FUNC(_dotpsu4)
static inline int _dotpsu4(int s1, unsigned s2)
{
    return __as_int(__dotp4_ext(__as_char4(s1), __as_uchar4(s2)));
}
#define _dotpus4(u, s) _dotpsu4((s), (u))
/* VDOTP4SUHW */
__INLINE_FUNC(_dotpsu4h)
static inline int _dotpsu4h(long long s1, long long s2)
{
#pragma diag_push
/* Use before set diagnostic */
#pragma diag_suppress 551
    __long8 v1, v2, v3, v4;
    v1.s0 = s1;
    v3.s0 = s2;
    return __vdotp4suhw_wwv(__as_short32(v1),  __as_short32(v2),
                            __as_ushort32(v3), __as_ushort32(v4)).s0;
#pragma diag_pop
}
/* VDOTP4SUHD */
__INLINE_FUNC(_dotpsu4hll)
static inline long long _dotpsu4hll(long long s1, long long s2)
{
    return __dotp4_ext(__as_short4(s1), __as_ushort4(s2));
}
/* VDOTP4UBW */
__INLINE_FUNC(_dotpu4)
static inline unsigned _dotpu4(unsigned s1, unsigned s2)
{
    return __dotp4_ext(__as_uchar4(s1), __as_uchar4(s2));
}
/* VPACKP2 */
__INLINE_FUNC(_dpack2)
static inline long long _dpack2(unsigned s1, unsigned s2)
{
    __char8 tmp1 = __as_char8((unsigned long) s1);
    __char8 tmp2 = __as_char8((unsigned long) s2);
    return __as_long(__pack_even(__as_short4(tmp1), __as_short4(tmp2)));
}
/* VPACKH2 */
__INLINE_FUNC(_dpackh2)
static inline long long _dpackh2(long long s1, long long s2)
{
    return __as_long(__pack_high(__as_short4(s1), __as_short4(s2)));
}
/* VPACKH4 */
__INLINE_FUNC(_dpackh4)
static inline long long _dpackh4(long long s1, long long s2)
{
    return __as_long(__pack_high(__as_char8(s1), __as_char8(s2)));
}
/* VPACKHL2 */
__INLINE_FUNC(_dpackhl2)
static inline long long _dpackhl2(long long s1, long long s2)
{
    return __as_long(__pack_high_low(__as_short4(s1), __as_short4(s2)));
}
/* VPACKL2 */
__INLINE_FUNC(_dpackl2)
static inline long long _dpackl2(long long s1, long long s2)
{
    return __as_long(__pack_low(__as_short4(s1), __as_short4(s2)));
}
/* VPACKL4 */
__INLINE_FUNC(_dpackl4)
static inline long long _dpackl4(long long s1, long long s2)
{
    return __as_long(__pack_low(__as_char8(s1), __as_char8(s2)));
}
/* VPACKLH2 */
__INLINE_FUNC(_dpacklh2)
static inline long long _dpacklh2(long long s1, long long s2)
{
    return __as_long(__pack_low_high(__as_short4(s1), __as_short4(s2)));
}
/* VPACKLH4 */
__INLINE_FUNC(_dpacklh4)
static inline long long _dpacklh4(unsigned s1, unsigned s2)
{
    __short4 tmp1 = __as_short4((unsigned long) s1);
    __short4 tmp2 = __as_short4((unsigned long) s2);
    return __as_long(__pack_low_high(__as_char8(tmp1), __as_char8(tmp2)));
}
/* PACKX2 */
__INLINE_FUNC(_dpackx2)
static inline long long _dpackx2(unsigned s1, unsigned s2)
{
    return __as_long(__pack_even_cross(__as_short2(s1), __as_short2(s2)));
}
/* VDPINT */
__INLINE_FUNC(_dpint)
static inline int _dpint(double s1)
{
    return __double_to_int(s1).s0;
}
/* VSADDW */
__INLINE_FUNC(_dsadd)
static inline long long _dsadd(long long s1, long long s2)
{
    return __as_long(__add_sat(__as_int2(s1), __as_int2(s2)));
}
/* VSADDH */
__INLINE_FUNC(_dsadd2)
static inline long long _dsadd2(long long s1, long long s2)
{
    return __as_long(__add_sat(__as_short4(s1), __as_short4(s2)));
}
/* VSHLW */
__INLINE_FUNC(_dshl)
static inline long long _dshl(long long s1, unsigned s2)
{
    return __as_long(__as_int2(s1) << (__int2)(s2));
}
/* VSHLH */
__INLINE_FUNC(_dshl2)
static inline long long _dshl2(long long s1, unsigned s2)
{
    return __as_long(__shift_left(__as_short4(s1), (__int2)(s2)));
}
/* VSHRW */
__INLINE_FUNC(_dshr)
static inline long long _dshr(long long s1, unsigned s2)
{
    return __as_long(__as_int2(s1) >> (__int2)(s2));
}
/* VSHRH */
__INLINE_FUNC(_dshr2)
static inline long long _dshr2(long long s1, unsigned s2)
{
    return __as_long(__shift_right(__as_short4(s1), (__int2)(s2)));
}
/* VSHRUW */
__INLINE_FUNC(_dshru)
static inline long long _dshru(long long s1, unsigned s2)
{
    return __as_long(__as_uint2(s1) >> (__uint2)(s2));
}
/* VSHRUH */
__INLINE_FUNC(_dshru2)
static inline long long _dshru2(long long s1, unsigned s2)
{
    return __as_long(__shift_right(__as_ushort4(s1), (__uint2)(s2)));
}
/* C6DSPACKU4 */
__INLINE_FUNC(_dspacku4)
static inline long long _dspacku4(long long s1, long long s2)
{
    return __as_long(__c6dspacku4_ddd(__as_short4(s1), __as_short4(s2)));
}
/* VSSUBW */
__INLINE_FUNC(_dssub)
static inline long long _dssub(long long s1, long long s2)
{
    return __as_long(__sub_sat(__as_int2(s1), __as_int2(s2)));
}
/* VSSUBH */
__INLINE_FUNC(_dssub2)
static inline long long _dssub2(long long s1, long long s2)
{
    return __as_long(__sub_sat(__as_short4(s1), __as_short4(s2)));
}
/* VSUBW */
__INLINE_FUNC(_dsub)
static inline long long _dsub(long long s1, long long s2)
{
    return __as_long(__as_int2(s1) - __as_int2(s2));
}
/* VSUBH */
__INLINE_FUNC(_dsub2)
static inline long long _dsub2(long long s1, long long s2)
{
    return __as_long(__as_short4(s1) - __as_short4(s2));
}
/* XPND4H */
__INLINE_FUNC(_dxpnd2)
static inline long long _dxpnd2(unsigned s1)
{
    return __as_long(__expand_lsb_pack_short((unsigned char) s1));
}
/* XPND8B */
__INLINE_FUNC(_dxpnd4)
static inline long long _dxpnd4(unsigned s1)
{
    return __as_long(__expand_lsb_pack_char((unsigned char) s1));
}
/* EXT */
__INLINE_FUNC(_ext)
static inline int _ext(int s1, unsigned s2, unsigned s3)
{
    return (s1 << s2) >> s3;
}
/* EXTU */
__INLINE_FUNC(_extu)
static inline unsigned _extu(unsigned s1, unsigned s2, unsigned s3)
{
    return (s1 << s2) >> s3;
}
/* VABSDP */
__INLINE_FUNC(_fabs)
static inline double _fabs(double s1)
{
    return __abs(s1);
}
/* VABSSP */
__INLINE_FUNC(_fabsf)
static inline float _fabsf(float s1)
{
    return __abs(s1);
}
/* PACKW */
__INLINE_FUNC(_fdmv)
static inline double _fdmv(float s1, float s2)
{
    return __as_double((__float2)(s2, s1));
}
/* No delay for instructions with just a pack (same for _dmvd) */
#define _fdmvd(s1, s2) _fdmv(s1, s2)
/* VGMPYW */
__INLINE_FUNC(_gmpy)
static inline unsigned _gmpy(unsigned s1, unsigned s2)
{
    return __gmpy(s1, s2);
}
/* VGMPYB */
__INLINE_FUNC(_gmpy4)
static inline int _gmpy4(int s1, int s2)
{
    return __as_int(__gmpy(__as_uchar4(s1), __as_uchar4(s2)));
}
/* VLMBDW */
__INLINE_FUNC(_lmbd)
static inline unsigned _lmbd(unsigned s1, unsigned s2)
{
    return __leftmost_bit_detect(s2, s1);
}
/* VMAXH */
__INLINE_FUNC(_max2)
static inline int _max2(int s1, int s2)
{
    return __as_int(__max(__as_short2(s1), __as_short2(s2)));
}
/* VMAXUB */
__INLINE_FUNC(_maxu4)
static inline unsigned _maxu4(unsigned s1, unsigned s2)
{
    return __as_uint(__max(__as_uchar4(s1), __as_uchar4(s2)));
}
/* VMINH */
__INLINE_FUNC(_min2)
static inline int _min2(int s1, int s2)
{
    return __as_int(__min(__as_short2(s1), __as_short2(s2)));
}
/* VMINUB */
__INLINE_FUNC(_minu4)
static inline unsigned _minu4(unsigned s1, unsigned s2)
{
    return __as_uint(__min(__as_uchar4(s1), __as_uchar4(s2)));
}
/*---------------------------------------------------------------------------*/
/* Although VMPYHW may be used to emulate _mpy, it may be beneficial to      */
/* instead use VMPYWW to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_mpy)
static inline int _mpy(int s1, int s2)
{
    return ((short)s1)*((short)s2);
}
/* C6MPY2IR */
__INLINE_FUNC(_mpy2ir)
static inline long long _mpy2ir(unsigned s1, int s2)
{
    return __as_long(__mpy_fx(__as_short2(s1), s2));
}
/*---------------------------------------------------------------------------*/
/* Although VMPYHW may be used to emulate _mpy2ll, it may be beneficial to   */
/* instead use VMPYWW to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_mpy2ll)
static inline long long _mpy2ll(int s1, int s2)
{
    return __as_long(__convert_int2(__as_short2(s1)) * __convert_int2(__as_short2(s2)));
}
/* VMPYWW */
__INLINE_FUNC(_mpy32)
static inline int _mpy32(int s1, int s2)
{
    return s1 * s2;
}
/*---------------------------------------------------------------------------*/
/* Although VMPYWD may be used to emulate _mpy32ll it may be beneficial to   */
/* instead use VMPYDD to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_mpy32ll)
static inline long long _mpy32ll(int s1, int s2)
{
    return (long long)s1 * (long long)s2;
}
#define _mpy32l(s1, s2) _mpy32ll((s1), (s2))
/*---------------------------------------------------------------------------*/
/* Although VMPYSUWD may be used to emulate _mpy32su it may be beneficial to */
/* instead use VMPYDD to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_mpy32su)
static inline long long _mpy32su(int s1, unsigned s2)
{
    return (long long)s1 * (long long)s2;
}
#define _mpy32us(u, s) _mpy32su((s), (u))
/*---------------------------------------------------------------------------*/
/* Although VMPYUWD may be used to emulate _mpy32u, it may be beneficial to  */
/* instead use VMPYDD to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
/* VMPYUWD */
__INLINE_FUNC(_mpy32u)
static inline long long _mpy32u(unsigned s1, unsigned s2)
{
    return (long long)s1 * (long long)s2;
}
/* C6MPYHIR */
__INLINE_FUNC(_mpyhir)
static inline int _mpyhir(int s1, int s2)
{
    return __c6mpyhir_rrr(__as_short2(s1), s2);
}
#define _mpyihr(src1, src2) _mpyhir((src2), (src1))
/* VMPYWD */
__INLINE_FUNC(_mpyidll)
static inline long long _mpyidll(int s1, int s2)
{
    return __mpy_ext(s1, s2);
}
/* C6MPYLIR */
__INLINE_FUNC(_mpylir)
static inline int _mpylir(int s1, int s2)
{
    return __c6mpylir_rrr(__as_short2(s1), s2);
}
#define _mpyilr(src1, src2) _mpylir((src2), (src1))
/* VMPYSP2DP */
__INLINE_FUNC(_mpysp2dp)
static inline double _mpysp2dp(float s1, float s2)
{
    return __mpy_ext(s1, s2);
}
/*---------------------------------------------------------------------------*/
/* Although VMPYSUHW may be used to emulate _mpysu, it may be beneficial to  */
/* instead use VMPYWW to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_mpysu)
static inline int _mpysu(int s1, unsigned s2)
{
    return ((int)__as_short2(s1).s0) * ((int)__as_ushort2(s2).s0);
}
#define _mpyus(u, s) _mpysu((s), (u))
/* VMPYSUBH */
__INLINE_FUNC(_mpysu4ll)
static inline long long _mpysu4ll(int s1, unsigned s2)
{
    return __as_long(__convert_short4(__as_char4(s1)) * __convert_short4(__as_uchar4(s2)));
}
#define _mpyus4ll(src1, src2) _mpysu4ll((src2), (src1))
/*---------------------------------------------------------------------------*/
/* Although VMPYUHW may be used to emulate _mpyu, it may be beneficial to    */
/* instead use VMPYWW to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_mpyu)
static inline unsigned _mpyu(unsigned s1, unsigned s2)
{
    return __as_ushort2(s1).s0 * __as_ushort2(s2).s0;
}
/*---------------------------------------------------------------------------*/
/* Although VMPYUHW may be used to emulate _mpyu2, it may be beneficial to   */
/* instead use VMPYWW to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
/* VMPYUHW */
__INLINE_FUNC(_mpyu2)
static inline long long _mpyu2(unsigned s1, unsigned s2)
{
    return __as_long(__convert_uint2(__as_ushort2(s1)) * __convert_uint2(__as_ushort2(s2)));
}
/* VMPYUBH */
__INLINE_FUNC(_mpyu4ll)
static inline long long _mpyu4ll(unsigned s1, unsigned s2)
{
    return __as_long(__mpy_ext(__as_uchar4(s1), __as_uchar4(s2)));
}
/* VNORMW */
__INLINE_FUNC(_norm)
static inline unsigned _norm(int s1)
{
    return __norm(s1);
}
/* VPACKP2 */
__INLINE_FUNC(_pack2)
static inline unsigned _pack2(unsigned s1, unsigned s2)
{
    return __as_uint((__ushort2)(__as_ushort2(s2).s0, __as_ushort2(s1).s0));
}
/* VPACKH2 */
__INLINE_FUNC(_packh2)
static inline unsigned _packh2(unsigned s1, unsigned s2)
{
    return __as_uint(__pack_high(__as_short2(s1), __as_short2(s2)));
}
/* VPACKH4 */
__INLINE_FUNC(_packh4)
static inline unsigned _packh4(unsigned s1, unsigned s2)
{
    return __as_uint(__pack_high(__as_char4(s1), __as_char4(s2)));
}
/* VPACKHL2 */
__INLINE_FUNC(_packhl2)
static inline unsigned _packhl2(unsigned s1, unsigned s2)
{
    return __as_uint(__pack_high_low(__as_short2(s1), __as_short2(s2)));
}
/* VPACKL4 */
__INLINE_FUNC(_packl4)
static inline unsigned _packl4(unsigned s1, unsigned s2)
{
    return __as_uint(__pack_low(__as_char4(s1), __as_char4(s2)));
}
/* VPACKLH2 */
__INLINE_FUNC(_packlh2)
static inline unsigned _packlh2(unsigned s1, unsigned s2)
{
    return __as_uint(__pack_low_high(__as_short2(s1), __as_short2(s2)));
}
#define _swap2(src) _packlh2((src), (src))
/* VRCPDP */
__INLINE_FUNC(_rcpdp)
static inline double _rcpdp(double s1)
{
    return __recip(s1);
}
/* VRCPSP */
__INLINE_FUNC(_rcpsp)
static inline float _rcpsp(float s1)
{
    return __recip(s1);
}
/* VROTLW */
__INLINE_FUNC(_rotl)
static inline unsigned _rotl(unsigned s1, unsigned s2)
{
    return __as_uint(__rotate_left(__as_int(s1), s2));
}
/* VRPACKH */
__INLINE_FUNC(_rpack2)
static inline unsigned _rpack2(unsigned s1, unsigned s2)
{
    return __as_uint(__pack_shift_sat(__as_int(s1), __as_int(s2)));
}
/* VRSQRDP */
__INLINE_FUNC(_rsqrdp)
static inline double _rsqrdp(double s1)
{
    return __recip_sqrt(s1);
}
/* VRSQRSP */
__INLINE_FUNC(_rsqrsp)
static inline float _rsqrsp(float s1)
{
    return __recip_sqrt(s1);
}
/* VSADDW */
__INLINE_FUNC(_sadd)
static inline int _sadd(int s1, int s2)
{
    return __add_sat(s1, s2);
}
/* VSADDH */
__INLINE_FUNC(_sadd2)
static inline int _sadd2(int s1, int s2)
{
    return __as_int(__add_sat(__as_short2(s1), __as_short2(s2)));
}
/* VSADDUB */
__INLINE_FUNC(_saddu4)
static inline unsigned _saddu4(unsigned s1, unsigned s2)
{
    return __as_uint(__add_sat(__as_uchar4(s1), __as_uchar4(s2)));
}
/* VSADDUSH */
__INLINE_FUNC(_saddus2)
static inline int _saddus2(unsigned s1, int s2)
{
    return __as_int(__add_sat(__as_ushort2(s1), __as_short2(s2)));
}
#define _saddsu2(src1, src2) _saddus2((src2), (src1))
/* SET */
__INLINE_FUNC(_set)
static inline unsigned _set(unsigned s1, unsigned s2, unsigned s3)
{
    unsigned long e_s2 = (((unsigned long) s2) << 59) >> 54;
    unsigned long e_s3 = (((unsigned long) s3) << 59) >> 59;
    unsigned long tmp  = e_s2 | e_s3;
    return __as_uint(__set(s1, (unsigned) tmp));
}
/* SET */
__INLINE_FUNC(_setr)
static inline unsigned _setr(unsigned s1, int s2)
{
    return __set(__as_int(s1), s2);
}
/* VBITSHFLW */
__INLINE_FUNC(_shfl)
static inline unsigned _shfl(unsigned s1)
{
    return __shuffle_bit(s1);
}
/* VSHFL3 */
__INLINE_FUNC(_shfl3)
static inline long long _shfl3(unsigned s1, unsigned s2)
{
    return __shuffle_3way(__as_uint2((unsigned long) s1),
                          __as_uint2((unsigned long) s2));
}
/* VSHLH */
__INLINE_FUNC(_shl2)
static inline unsigned _shl2(unsigned s1, unsigned s2)
{
    return __as_uint(__shift_left(__as_short2(s1), (int)s2));
}
/* VSHLMB */
__INLINE_FUNC(_shlmb)
static inline unsigned _shlmb(unsigned s1, unsigned s2)
{
    return __shift_left_merge(__as_int(s1), __as_char4(s2));
}
/* VSHRH */
__INLINE_FUNC(_shr2)
static inline int _shr2(int s1, unsigned s2)
{
    return __as_int(__shift_right(__as_short2(s1), (int)s2));
}
/* VSHRMB */
__INLINE_FUNC(_shrmb)
static inline unsigned _shrmb(unsigned s1, unsigned s2)
{
    return __shift_right_merge(__as_int(s1), __as_char4(s2));
}
/* VSHRUH */
__INLINE_FUNC(_shru2)
static inline unsigned _shru2(unsigned s1, unsigned s2)
{
    return __as_uint(__shift_right(__as_ushort2(s1), s2));
}
/* VSMPYHW */
__INLINE_FUNC(_smpy)
static inline int _smpy(int s1, int s2)
{
    return __mpy_sat_ext(__as_short2(s1).s0, __as_short2(s2).s0);
}
/* VSMPYHW */
__INLINE_FUNC(_smpy2ll)
static inline long long _smpy2ll(int s1, int s2)
{
    return __as_long(__mpy_sat_ext(__as_short2(s1), __as_short2(s2)));
}
/* VSMPYWW */
__INLINE_FUNC(_smpy32)
static inline int _smpy32(int s1, int s2)
{
    return __mpy_sat(s1, s2);
}
/* VSPACKWH */
__INLINE_FUNC(_spack2)
static inline int _spack2(int s1, int s2)
{
    return __as_int(__pack_sat(s1, s2));
}
/* C6DSPACKU4 */
__INLINE_FUNC(_spacku4)
static inline unsigned _spacku4(int s1, int s2)
{
    __short4 tmp = __as_short4((__int2)(s2, s1));
    return __as_uint2(__c6dspacku4_ddd(tmp, tmp)).s0;
}
/* VSPINT */
__INLINE_FUNC(_spint)
static inline int _spint(float s1)
{
    return __float_to_int(s1);
}
/* VSPINTHPK */
__INLINE_FUNC(_spinth)
static inline unsigned _spinth(float s1)
{
    __float16 tmp1;
    tmp1.s0 = s1;
    return __as_uint(__vspinthpk_vv(tmp1).s01);
}
/* VSSHLW */
__INLINE_FUNC(_sshl)
static inline int _sshl(int s1, unsigned s2)
{
    return __shift_left_sat(s1, s2);
}
/* VSSHVLW */
__INLINE_FUNC(_sshvl)
static inline int _sshvl(int s1, int s2)
{
    return __shift_left_var_sat(s1, s2);
}
/* VSSHVRW */
__INLINE_FUNC(_sshvr)
static inline int _sshvr(int s1, int s2)
{
    return __shift_right_var_sat(s1, s2);
}
/* VSSUBW */
__INLINE_FUNC(_ssub)
static inline int _ssub(int s1, int s2)
{
    return __sub_sat(s1, s2);
}
/* VSSUBH */
__INLINE_FUNC(_ssub2)
static inline int _ssub2(int s1, int s2)
{
    return __as_int(__sub_sat(__as_short2(s1), __as_short2(s2)));
}
/* VSUBH */
__INLINE_FUNC(_sub2)
static inline int _sub2(int s1, int s2)
{
    return __as_int(__as_short2(s1) - __as_short2(s2));
}
/* VSUBB */
__INLINE_FUNC(_sub4)
static inline int _sub4(int s1, int s2)
{
    return __as_int(__as_char4(s1) - __as_char4(s2));
}
/* VSUBABSB */
__INLINE_FUNC(_subabs4)
static inline int _subabs4(int s1, int s2)
{
    return __as_int(__abs_diff(__as_uchar4(s1), __as_uchar4(s2)));
}
/* VSUBCW */
__INLINE_FUNC(_subc)
static inline unsigned _subc(unsigned s1, unsigned s2)
{
    return __sub_cond(s1, s2);
}
/* VSWAPB */
__INLINE_FUNC(_swap4)
static inline unsigned _swap4(unsigned s1)
{
    return __as_uint(__swap(__as_char4(s1)));
}
/* VUNPKLH */
__INLINE_FUNC(_unpkh2)
static inline long long _unpkh2(unsigned s1)
{
    __uint2 tmp;
    tmp = __as_uint2((unsigned long) s1);
    return __as_long(__unpack_low(__as_short4(tmp)));
}
/* VUNPKLUH */
__INLINE_FUNC(_unpkhu2)
static inline long long _unpkhu2(unsigned s1)
{
    __uint2 tmp;
    tmp = __as_uint2((unsigned long) s1);
    return __as_long(__unpack_low(__as_ushort4(tmp)));
}
/* VUNPKHUB */
__INLINE_FUNC(_unpkhu4)
static inline unsigned _unpkhu4(unsigned s1)
{
    return __as_uint(__unpack_high(__as_uchar4(s1)));
}
/* VUNPKLUB */
__INLINE_FUNC(_unpklu4)
static inline unsigned _unpklu4(unsigned s1)
{
    return __as_uint(__unpack_low(__as_uchar4(s1)));
}
/* VXORW */
long long __BUILTIN _xorll_c(int, long long);
/* VXORMPYW */
__INLINE_FUNC(_xormpy)
static inline unsigned _xormpy(unsigned s1, unsigned s2)
{
    return __mpy_xor(s1, s2);
}
/* XPND4H */
__INLINE_FUNC(_xpnd2)
static inline unsigned _xpnd2(unsigned s1)
{
    return __as_uint(__expand_lsb_pack_short((unsigned char) s1).s01);
}
/* XPND8B */
__INLINE_FUNC(_xpnd4)
static inline unsigned _xpnd4(unsigned s1)
{
    return __as_uint(__expand_lsb_pack_char((unsigned char) s1).s0123);
}

/*---------------------------------------------------------------------------*/
/* The add-sub operation is not supported on C7000 and must be split into    */
/* its constituent operations.                                               */
/*---------------------------------------------------------------------------*/
/* VADDW/VSUBW */
__INLINE_FUNC(_addsub)
static inline long long _addsub(int s1, int s2)
{
    return __as_long((__int2)(s1 - s2, s1 + s2));
}
/* VADDH/VSUBH */
__INLINE_FUNC(_addsub2)
static inline long long _addsub2(unsigned s1, unsigned s2)
{
    __short2 tmp1 = __as_short2(s1) + __as_short2(s2); 
    __short2 tmp2 = __as_short2(s1) - __as_short2(s2); 
    return __as_long((__int2)(__as_int(tmp2), __as_int(tmp1))); 
}
/* VSADDW/VSSUBW */
__INLINE_FUNC(_saddsub)
static inline long long _saddsub(int s1, int s2)
{
    return __as_long((__int2)(__sub_sat(s1,s2), __add_sat(s1, s2)));
}
/* VSADDH/VSSUBH */
__INLINE_FUNC(_saddsub2)
static inline long long _saddsub2(unsigned s1, unsigned s2)
{
    __short2 tmp1 = __add_sat(__as_short2(s1), __as_short2(s2));
    __short2 tmp2 = __sub_sat(__as_short2(s1), __as_short2(s2));
    return __as_long((__short4)(tmp2, tmp1));
}

/*---------------------------------------------------------------------------*/
/* Complex single-precision floating point multiplies are emulated with      */
/* a complex multiply to intermediate results, and then the operation is     */
/* finished by either adding or subtracting the intermediate results.        */
/*---------------------------------------------------------------------------*/
/* VCMPYSP/VSUBSP */
__INLINE_FUNC(_complex_conjugate_mpysp)
static inline __float2_t _complex_conjugate_mpysp(__float2_t s1, __float2_t s2)
{
    return __as_float2_t(__complex_conjugate_multiply(__as_cfloat(s1),
                                                      __as_cfloat(s2)));
}
/* VCMPYSP/VADDSP */
__INLINE_FUNC(_complex_mpysp)
static inline __float2_t _complex_mpysp(__float2_t s1, __float2_t s2)
{
    return __as_float2_t(__as_cfloat(s1) * __as_cfloat(s2));
}

/* C6DCMPEQH */
__INLINE_FUNC(_cmpeq2)
static inline int _cmpeq2(int s1, int s2)
{
    char tmp = __c6dcmpeqh_ddr(__as_short4((unsigned long)s1),
                               __as_short4((unsigned long)s2));
    return tmp & 0x3;
}
/* C6DCMPEQB */
__INLINE_FUNC(_cmpeq4)
static inline int _cmpeq4(int s1, int s2)
{
    char tmp = __c6dcmpeqb_ddr(__as_char8((unsigned long)s1),
                               __as_char8((unsigned long)s2));
    return tmp & 0xF;
}
/* C6DCMPGTH */
__INLINE_FUNC(_cmpgt2)
static inline int _cmpgt2(int s1, int s2)
{
    char tmp = __c6dcmpgth_ddr(__as_short4((unsigned long)s1),
                               __as_short4((unsigned long)s2));
    return tmp & 0x3;
}
#define _cmplt2(src1, src2) _cmpgt2((src2), (src1))
/* C6DCMPGTUB */
__INLINE_FUNC(_cmpgtu4)
static inline unsigned _cmpgtu4(unsigned s1, unsigned s2)
{
    char tmp = __c6dcmpgtub_ddr(__as_uchar8((unsigned long)s1),
                                __as_uchar8((unsigned long)s2));
    return tmp & 0xF;
}
#define _cmpltu4(src1, src2) _cmpgtu4((src2), (src1))

/*---------------------------------------------------------------------------*/
/* _unpkbu4 uses the VUNPKLUB and VUNPKHUB to unpack the low and high 2      */
/* bytes of the argument, and then constructs the result.                    */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_unpkbu4)
static inline long long _unpkbu4(unsigned s1)
{
    return __as_long((__ushort4)(__unpack_low(__as_uchar4(s1)),
                                 __unpack_high(__as_uchar4(s1))));
}

/*---------------------------------------------------------------------------*/
/* The following intrinsics reinterpret values as another type. For C7000,   */
/* the same effect can be achieved by using the OpenCL-style reinterpret     */
/* cast.                                                                     */
/*---------------------------------------------------------------------------*/
/* unsigned __BUILTIN _ftoi(float);    */
#define _ftoi  __as_uint

/* float __BUILTIN _itof(unsigned);    */
#define _itof  __as_float

/* long long __BUILTIN _dtoll(double); */
#define _dtoll(x) ((long long)__as_long(x))

/* double __BUILTIN _lltod(long long); */
#define _lltod __as_double

/*---------------------------------------------------------------------------*/
/* The following intrinsics pack two 32-bit values and then reinterpret the  */
/* value as a 64-bit scalar type. For C7000, OpenCL-style reinterpret casts  */
/* can be used to achieve the same behavior.                                 */
/*                                                                           */
/* Note: Because C7000 cannot individually address the low and high 32-bits  */
/*       of a 64-bit register, these intrinsics will impact performance.     */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_ftod)
static inline double _ftod(float s1, float s2)
{
    return __as_double((__float2)(s2, s1));
}
__INLINE_FUNC(_itod)
static inline double _itod(unsigned s1, unsigned s2)
{
    return __as_double((__uint2)(s2, s1));
}

__INLINE_FUNC(_itoll)
static inline long long _itoll(unsigned s1, unsigned s2)
{
    return __as_long((__uint2)(s2, s1));
}

/*---------------------------------------------------------------------------*/
/* The following two intrinsics are register variants of the EXT/EXTU        */
/* instructions. There are no register versions of these instructions on     */
/* C7000, and so they must be emulated.                                      */
/*                                                                           */
/* When migrating, if the shift values are know to fit into the 6-bit        */
/* boundaries, the shift values can be stored separately and the extractions */
/* can be removed.                                                           */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_extr)
static inline int _extr(int s1, int s2)
{
    /* Performs about the same, may be conditionally optimized in future */
    unsigned tmp1 = (((unsigned)s2) >> 5) & 0x1F;
    unsigned tmp2 = ((unsigned)s2) & 0x1F;
    return (s1 << tmp1) >> tmp2;
}
__INLINE_FUNC(_extur)
static inline unsigned _extur(unsigned s1, int s2)
{
    /* Performs about the same, may be conditionally optimized in future */
    unsigned tmp1 = (((unsigned)s2) >> 5) & 0x1F;
    unsigned tmp2 = ((unsigned)s2) & 0x1F;
    return (s1 << tmp1) >> tmp2;
}

/*---------------------------------------------------------------------------*/
/* All logical operations on C7000 are 64-bits wide, but even when sign      */
/* extension occurs, the upper 32 bits are just repeats of the sign bit so   */
/* the result doesn't change.                                                */
/*---------------------------------------------------------------------------*/
/* LANDD */
__INLINE_FUNC(_land)
static inline int _land(int s1, int s2)
{
    return __logical_and(s1, s2);
}
/* LANDND */
__INLINE_FUNC(_landn)
static inline int _landn(int s1, int s2)
{
    return __logical_andn(s1, s2);
}
/* LORD */
__INLINE_FUNC(_lor)
static inline int _lor(int s1, int s2)
{
    return __logical_or(s1, s2);
}

/*---------------------------------------------------------------------------*/
/* 2-point dot products between 2 16-bit sources and 4 8-bit sources are not */
/* natively supported on C7000. To emulate this using C7000's instruction    */
/* set, follow these steps:                                                  */
/*   1. Unpack the 4 8-bit source values to 4 16-bit values                  */
/*   2. Duplicate the 2 16-bit source values into 4 16-bit values            */
/*   3. Perform a 2-point 16-bit dot product                                 */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_ddotp4)
static inline long long _ddotp4(unsigned s1, unsigned s2)
{
    __short4 tmp1 = __as_short4((__uint2)(s1, s1));
    __short4 tmp2 = (__short4)(__unpack_low(__as_char4(s2)), __unpack_high(__as_char4(s2)));
    return __as_long(__dotp2(tmp1, tmp2));
}

/*---------------------------------------------------------------------------*/
/* The _lo and _hi intrinsics perform the same operation as OpenCL accessors */
/* on C7000. Behavior can be replicated exactly by using both accessors and  */
/* reinterpret casts.                                                        */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_lo)
static inline unsigned _lo(double s1)
{
    return __as_uint2(s1).s0;
}
__INLINE_FUNC(_lof)
static inline float _lof(double s1)
{
    return __as_float2(s1).s0;
}
__INLINE_FUNC(_loll)
static inline unsigned _loll(long long s1)
{
    return __as_uint2(s1).s0;
}
__INLINE_FUNC(_hi)
static inline unsigned _hi(double s1)
{
    return __as_uint2(s1).s1;
}
__INLINE_FUNC(_hif)
static inline float _hif(double s1)
{
    return __as_float2(s1).s1;
}
__INLINE_FUNC(_hill)
static inline unsigned _hill(long long s1)
{
    return __as_uint2(s1).s1;
}

/*---------------------------------------------------------------------------*/
/* The following intrinsics multiply the high 16 bits of one source with     */
/* the high 16 bits of the other source. The _smpyh variant saturates        */
/* the result if it does not fit into a signed 32-bit container.             */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* Although VMPYHW may be used to emulate _mpyh, it may be beneficial to     */
/* instead use VMPYWW to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_mpyh)
static inline int _mpyh(int s1, int s2)
{
    return ((int)__as_short2(s1).s1) * ((int)__as_short2(s2).s1);
}
/*---------------------------------------------------------------------------*/
/* Although VMPYUHW may be used to emulate _mpyhu, it may be beneficial to   */
/* instead use VMPYWW to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
/* VMPYUHW */
__INLINE_FUNC(_mpyhu)
static inline unsigned _mpyhu(unsigned s1, unsigned s2)
{
    return ((int)__as_ushort2(s1).s1) * ((int)__as_ushort2(s2).s1);
}
/*---------------------------------------------------------------------------*/
/* Although VMPYHSUW may be used to emulate _mpyh, it may be beneficial to   */
/* instead use VMPYWW to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_mpyhsu)
static inline int _mpyhsu(int s1, unsigned s2)
{
    return __as_short2(s1).s1 * __as_ushort2(s2).s1;
}
/* VSMPYHW */
__INLINE_FUNC(_smpyh)
static inline int _smpyh(int s1, int s2)
{
    return __mpy_sat_ext(__as_short2(s1).s1, __as_short2(s2).s1);
}
#define _mpyhus(u, s) _mpyhsu((s), (u))

/*---------------------------------------------------------------------------*/
/* The following intrinsics multiply the high 16 bits of one source with     */
/* the low 16 bits of the other source. The _smpyhl and _smpylh variants     */
/* saturate the result if it does not fit into a signed 32-bit container.    */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* Although VMPYHW may be used to emulate _mpyhl, it may be beneficial to    */
/* instead use VMPYWW to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_mpyhl)
static inline int _mpyhl(int s1, int s2)
{
    return __as_short2(s1).s1 * __as_short2(s2).s0;
}
/*---------------------------------------------------------------------------*/
/* Although VMPYUHW may be used to emulate _mpyhlu, it may be beneficial to  */
/* instead use VMPYWW to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_mpyhlu)
static inline unsigned _mpyhlu(unsigned s1, unsigned s2)
{
    return __as_ushort2(s1).s1 * __as_ushort2(s2).s0;
}
/*---------------------------------------------------------------------------*/
/* Although VMPYSUHW may be used to emulate _mpyhslu, it may be beneficial to*/
/* instead use VMPYWW to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_mpyhslu)
static inline int _mpyhslu(int s1, unsigned s2)
{
    return __as_short2(s1).s1 * __as_ushort2(s2).s0;
}
/*---------------------------------------------------------------------------*/
/* Although VMPYSUHW may be used to emulate _mpyhuls, it may be beneficial to*/
/* instead use VMPYWW to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_mpyhuls)
static inline int _mpyhuls(unsigned s1, int s2)
{
    return __as_ushort2(s1).s1 * __as_short2(s2).s0;
}
/* VSMPYHW */
__INLINE_FUNC(_smpyhl)
static inline int _smpyhl(int s1, int s2)
{
    return __mpy_sat_ext(__as_short2(s1).s1, __as_short2(s2).s0);
}
#define _mpylh(l, h) _mpyhl((h), (l))
#define _mpylhu(l, h) _mpyhlu((h), (l))
#define _mpylshu(ls, hu) _mpyhuls((hu), (ls))
#define _mpyluhs(lu, hs) _mpyhslu((hs), (lu))
#define _smpylh(l, h) _smpyhl((h), (l))

/*---------------------------------------------------------------------------*/
/* The following intrinsics multiply the low or high 16 bits of the first    */
/* source with a signed 32 bit second source to return a signed 64-bit       */
/* value. Because this 16-to-32 bit multiply is not supported natively, the  */
/* 16-bit source must be extended to 32 bits.                                */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* Although VMPYHD may be used to emulate _mpyhill, it may be beneficial to  */
/* instead use VMPYDD to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_mpyhill)
static inline long long _mpyhill(int s1, int s2)
{
    return ((long)__as_short2(s1).s1) * ((long)s2);
}
#define _mpyihll(src1, src2) _mpyhill((src2), (src1))
/*---------------------------------------------------------------------------*/
/* Although VMPYHD may be used to emulate _mpylill, it may be beneficial to  */
/* instead use VMPYDD to avoid the need for double vector outputs.           */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_mpylill)
static inline long long _mpylill(int s1, int s2)
{
    return ((long)__as_short2(s1).s0) * ((long)s2);
}
#define _mpyilll(src1, src2) _mpylill((src2), (src1))

/*---------------------------------------------------------------------------*/
/* The _mpyspdp intrinsic multiplies a float with a double and returns a     */
/* double. This operation is not native on C7000, and must be emulated.      */
/*---------------------------------------------------------------------------*/
__INLINE_FUNC(_mpyspdp)
static inline double _mpyspdp(float s1, double s2)
{
    return (((double)s1) * s2);
}

/*---------------------------------------------------------------------------*/
/* Deprecated intrinsics that use double as a vector container should no     */
/* longer be used.  The following definitions are only provided for          */
/* compatibility with existing code.                                         */
/*---------------------------------------------------------------------------*/
#define _mpy2(x,y)   _lltod(_mpy2ll((x),(y)))
#define _smpy2(x,y)  _lltod(_smpy2ll((x),(y)))
#define _mpyhi(x,y)  _lltod(_mpyhill((x),(y)))
#define _mpyli(x,y)  _lltod(_mpylill((x),(y)))
#define _mpysu4(x,y) _lltod(_mpysu4ll((x),(y)))
#define _mpyu4(x,y)  _lltod(_mpyu4ll((x),(y)))

/*---------------------------------------------------------------------------*/
/* _mfence stalls until the completion of all CPU-triggered memory           */
/* transactions.  The __memory_fence operation on C7x for all colors is the  */
/* equivalent.                                                               */
/*---------------------------------------------------------------------------*/
#define _mfence() __memory_fence(__MFENCE_ALL_COLORS)

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#undef __BUILTIN
#undef __BUILTIN_M
#undef __PRAGMA
#undef __INLINE_FUNC

#endif /* __C6X_MIGRATION_H */
