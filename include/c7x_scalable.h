/*****************************************************************************/
/*  C7X_SCALABLE.H                                                           */
/*                                                                           */
/* Copyright (c) 2021 Texas Instruments Incorporated                         */
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

/*****************************************************************************/
/*                                                                           */
/* WARNING: The types and APIs presented in this file are not finalized and  */
/*          may change in the future.                                        */
/*                                                                           */
/*****************************************************************************/
/* This file provides types and APIs to program the C7x in a vector width    */
/* agnostic fashion. That is, intead of using types like __char64, using     */
/* types like __c7x_char_vec.                                                */
/*                                                                           */
/* These types will work with typical arithmetic operations as specified in  */
/* c7x.h and c7x_direct.h as long as an operation is available on the        */
/* current C7x target.                                                       */
/*                                                                           */
/* Complex use cases will likely need C++ for greater capability that is     */
/* provided by "type traits" like interfaces. This is recommended for using  */
/* the streaming engine in particular.                                       */
/*****************************************************************************/
#ifndef C7X_SCALABLE_H
#define C7X_SCALABLE_H 

#include <c7x.h>

#if defined(__C7X_UNSTABLE_API)

/*****************************************************************************/
/*                                                                           */
/* C Core Interface                                                          */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/* FULL WIDTH VECTOR TYPES                                                   */
/*****************************************************************************/
typedef  __char64    __c7x_char_vec;
typedef  __uchar64   __c7x_uchar_vec;
typedef  __cchar32   __c7x_cchar_vec;
typedef  __short32   __c7x_short_vec;
typedef  __ushort32  __c7x_ushort_vec;
typedef  __cshort16  __c7x_cshort_vec;
typedef  __int16     __c7x_int_vec;
typedef  __uint16    __c7x_uint_vec;
typedef  __float16   __c7x_float_vec;
typedef  __cint8     __c7x_cint_vec;
typedef  __cfloat8   __c7x_cfloat_vec;
typedef  __long8     __c7x_long_vec;
typedef  __ulong8    __c7x_ulong_vec;
typedef  __double8   __c7x_double_vec;
typedef  __clong4    __c7x_clong_vec;
typedef  __cdouble4  __c7x_cdouble_vec;

/*****************************************************************************/
/* HOST EMULATION COMPATIBLE TYPES                                           */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* CONSTANT VECTOR TYPES                                                     */
/*---------------------------------------------------------------------------*/
typedef  const  __c7x_char_vec     __const_c7x_char_vec;
typedef  const  __c7x_uchar_vec    __const_c7x_uchar_vec;
typedef  const  __c7x_cchar_vec    __const_c7x_cchar_vec;
typedef  const  __c7x_short_vec    __const_c7x_short_vec;
typedef  const  __c7x_ushort_vec   __const_c7x_ushort_vec;
typedef  const  __c7x_cshort_vec   __const_c7x_cshort_vec;
typedef  const  __c7x_int_vec      __const_c7x_int_vec;
typedef  const  __c7x_uint_vec     __const_c7x_uint_vec;
typedef  const  __c7x_float_vec    __const_c7x_float_vec;
typedef  const  __c7x_cint_vec     __const_c7x_cint_vec;
typedef  const  __c7x_cfloat_vec   __const_c7x_cfloat_vec;
typedef  const  __c7x_long_vec     __const_c7x_long_vec;
typedef  const  __c7x_ulong_vec    __const_c7x_ulong_vec;
typedef  const  __c7x_double_vec   __const_c7x_double_vec;
typedef  const  __c7x_clong_vec    __const_c7x_clong_vec;
typedef  const  __c7x_cdouble_vec  __const_c7x_cdouble_vec;

/*---------------------------------------------------------------------------*/
/* VECTOR POINTER TYPES                                                      */
/*---------------------------------------------------------------------------*/
typedef  __c7x_char_vec     *  __c7x_char_vec_ptr;
typedef  __c7x_uchar_vec    *  __c7x_uchar_vec_ptr;
typedef  __c7x_cchar_vec    *  __c7x_cchar_vec_ptr;
typedef  __c7x_short_vec    *  __c7x_short_vec_ptr;
typedef  __c7x_ushort_vec   *  __c7x_ushort_vec_ptr;
typedef  __c7x_cshort_vec   *  __c7x_cshort_vec_ptr;
typedef  __c7x_int_vec      *  __c7x_int_vec_ptr;
typedef  __c7x_uint_vec     *  __c7x_uint_vec_ptr;
typedef  __c7x_float_vec    *  __c7x_float_vec_ptr;
typedef  __c7x_cint_vec     *  __c7x_cint_vec_ptr;
typedef  __c7x_cfloat_vec   *  __c7x_cfloat_vec_ptr;
typedef  __c7x_long_vec     *  __c7x_long_vec_ptr;
typedef  __c7x_ulong_vec    *  __c7x_ulong_vec_ptr;
typedef  __c7x_double_vec   *  __c7x_double_vec_ptr;
typedef  __c7x_clong_vec    *  __c7x_clong_vec_ptr;
typedef  __c7x_cdouble_vec  *  __c7x_cdouble_vec_ptr;

/*---------------------------------------------------------------------------*/
/* CONST VECTOR POINTER TYPES                                                */
/*---------------------------------------------------------------------------*/
typedef  const  __c7x_char_vec     *  __const_c7x_char_vec_ptr;
typedef  const  __c7x_uchar_vec    *  __const_c7x_uchar_vec_ptr;
typedef  const  __c7x_cchar_vec    *  __const_c7x_cchar_vec_ptr;
typedef  const  __c7x_short_vec    *  __const_c7x_short_vec_ptr;
typedef  const  __c7x_ushort_vec   *  __const_c7x_ushort_vec_ptr;
typedef  const  __c7x_cshort_vec   *  __const_c7x_cshort_vec_ptr;
typedef  const  __c7x_int_vec      *  __const_c7x_int_vec_ptr;
typedef  const  __c7x_uint_vec     *  __const_c7x_uint_vec_ptr;
typedef  const  __c7x_float_vec    *  __const_c7x_float_vec_ptr;
typedef  const  __c7x_cint_vec     *  __const_c7x_cint_vec_ptr;
typedef  const  __c7x_cfloat_vec   *  __const_c7x_cfloat_vec_ptr;
typedef  const  __c7x_long_vec     *  __const_c7x_long_vec_ptr;
typedef  const  __c7x_ulong_vec    *  __const_c7x_ulong_vec_ptr;
typedef  const  __c7x_double_vec   *  __const_c7x_double_vec_ptr;
typedef  const  __c7x_clong_vec    *  __const_c7x_clong_vec_ptr;
typedef  const  __c7x_cdouble_vec  *  __const_c7x_cdouble_vec_ptr;

/*****************************************************************************/
/* REINTERPRETS                                                              */
/*****************************************************************************/
#define  __as_c7x_char_vec     __as_char64
#define  __as_c7x_uchar_vec    __as_uchar64
#define  __as_c7x_cchar_vec    __as_cchar32
#define  __as_c7x_short_vec    __as_short32
#define  __as_c7x_ushort_vec   __as_ushort32
#define  __as_c7x_cshort_vec   __as_cshort16
#define  __as_c7x_int_vec      __as_int16
#define  __as_c7x_uint_vec     __as_uint16
#define  __as_c7x_float_vec    __as_float16
#define  __as_c7x_cint_vec     __as_cint8
#define  __as_c7x_cfloat_vec   __as_cfloat8
#define  __as_c7x_long_vec     __as_long8
#define  __as_c7x_ulong_vec    __as_ulong8
#define  __as_c7x_double_vec   __as_double8
#define  __as_c7x_clong_vec    __as_clong4
#define  __as_c7x_cdouble_vec  __as_cdouble4

/*****************************************************************************/
/* LOOP UTILITY                                                              */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* __VEC_NELEM(type) -- Query the number of instances of type that can fit   */
/*   in a vector. Useful for determining loop bounds.                        */
/*   Example: __VEC_NELEM(char) [yields 64 on C7100]                         */
/*---------------------------------------------------------------------------*/
#define __VEC_NELEM(type) (__C7X_VEC_SIZE_BYTES__/sizeof(type))


/*****************************************************************************/
/*                                                                           */
/* C++ Extended Interface                                                    */
/*                                                                           */
/*****************************************************************************/
#ifdef __cplusplus
#include <type_traits> /* std::enable_if_t */
namespace c7x
{
/*****************************************************************************/
/* VECTOR TRAITS                                                             */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* element_count_of -- Query the number of elements in a type.               */
/*   Members: size_t value                                                   */
/*   Example: element_count_of<int16>::value [yields 16]                     */
/*---------------------------------------------------------------------------*/
template<typename T> struct element_count_of {};

/*---------------------------------------------------------------------------*/
/* element_type_of -- Query the element type of a type.                      */
/*   Members: typedef type                                                   */
/*   Example: typename element_type_of<int16>::type [yields int]             */
/*---------------------------------------------------------------------------*/
template<typename T> struct element_type_of {};

/*---------------------------------------------------------------------------*/
/* component_type_of -- Query the compoment type of a type. This type is     */
/*   equivalent to the element type for non-complex types.                   */
/*   Members: typedef type                                                   */
/*   Example: typename component_type_of<cint16>::type [yields int]          */
/*---------------------------------------------------------------------------*/
template<typename T> struct component_type_of {};

/*---------------------------------------------------------------------------*/
/* make_vector -- Create a vector type.                                      */
/*   Members: typedef type                                                   */
/*   Example: typename make_vector<int, 16>::type [yields int16]             */
/*---------------------------------------------------------------------------*/
template<typename T, size_t N> struct make_vector {};

/*---------------------------------------------------------------------------*/
/* make_full_vector -- Create a vector sized to the target width.            */
/*   Members: typedef type                                                   */
/*   Example: make_full_vector<int>::type [yields int16 on C7100]            */
/*---------------------------------------------------------------------------*/
template<typename T> struct make_full_vector
{
    typedef typename make_vector<
                     typename element_type_of<T>::type,
                     __VEC_NELEM(typename element_type_of<T>::type)>::type type;
};

/*---------------------------------------------------------------------------*/
/* make_pointer -- Create a vector pointer. (For HE compatibility.)          */
/*   Members:                                                                */
/*   Example: make_pointer<int16>::type [yields int16*]                      */
/*---------------------------------------------------------------------------*/
template<typename T> struct make_pointer
{ typedef T * type; };

/*---------------------------------------------------------------------------*/
/* make_const -- Create a const vector. (For HE compatibility.)              */
/*   Members: typedef type                                                   */
/*   Example: make_const<int16>::type [yields const int16]                   */
/*---------------------------------------------------------------------------*/
template<typename T> struct make_const
{ typedef const T type; };

/*---------------------------------------------------------------------------*/
/* is_target_vector -- Query whether the vector type fits on the target.     */
/*   Members: bool value                                                     */
/*   Example: is_target_vector<int16>::value [yields true on C7100]          */
/*---------------------------------------------------------------------------*/
template<typename T> struct is_target_vector
{ static constexpr bool value = false; };

/* Implementation details; don't use directly. */
#define _make_template(_T, _E, _C, _N) \
template<> struct element_count_of<_T> { static constexpr size_t value = _N; }; \
template<> struct element_type_of<_T>  { typedef _E type; }; \
template<> struct component_type_of<_T>  { typedef _C type; }; \
template<> struct make_vector<_E, _N>  { typedef _T type; }; \
template<> struct is_target_vector<_T> { static constexpr bool value = sizeof(_T) <= __C7X_VEC_SIZE_BYTES__; };

/* Integral Types */
_make_template(__char64,     signed char, signed char,  64)
_make_template(__char32,     signed char, signed char,  32)
_make_template(__char16,     signed char, signed char,  16)
_make_template(__char8,      signed char, signed char,  8)
_make_template(__char4,      signed char, signed char,  4)
_make_template(__char3,      signed char, signed char,  3)
_make_template(__char2,      signed char, signed char,  2)
_make_template(signed char,  signed char, signed char,  1)

_make_template(__uchar64,      unsigned char, unsigned char,  64)
_make_template(__uchar32,      unsigned char, unsigned char,  32)
_make_template(__uchar16,      unsigned char, unsigned char,  16)
_make_template(__uchar8,       unsigned char, unsigned char,  8)
_make_template(__uchar4,       unsigned char, unsigned char,  4)
_make_template(__uchar3,       unsigned char, unsigned char,  3)
_make_template(__uchar2,       unsigned char, unsigned char,  2)
_make_template(unsigned char,  unsigned char, unsigned char,  1)

_make_template(__short32,  short, short,  32)
_make_template(__short16,  short, short,  16)
_make_template(__short8,   short, short,  8)
_make_template(__short4,   short, short,  4)
_make_template(__short3,   short, short,  3)
_make_template(__short2,   short, short,  2)
_make_template(short,      short, short,  1)

_make_template(__ushort32,      unsigned short, unsigned short,  32)
_make_template(__ushort16,      unsigned short, unsigned short,  16)
_make_template(__ushort8,       unsigned short, unsigned short,  8)
_make_template(__ushort4,       unsigned short, unsigned short,  4)
_make_template(__ushort3,       unsigned short, unsigned short,  3)
_make_template(__ushort2,       unsigned short, unsigned short,  2)
_make_template(unsigned short,  unsigned short, unsigned short,  1)

_make_template(__int16,  int, int,  16)
_make_template(__int8,   int, int,  8)
_make_template(__int4,   int, int,  4)
_make_template(__int3,   int, int,  3)
_make_template(__int2,   int, int,  2)
_make_template(int,      int, int,  1)

_make_template(__uint16,      unsigned int, unsigned int,  16)
_make_template(__uint8,       unsigned int, unsigned int,  8)
_make_template(__uint4,       unsigned int, unsigned int,  4)
_make_template(__uint3,       unsigned int, unsigned int,  3)
_make_template(__uint2,       unsigned int, unsigned int,  2)
_make_template(unsigned int,  unsigned int, unsigned int,  1)

_make_template(__long8,  long, long,  8)
_make_template(__long4,  long, long,  4)
_make_template(__long3,  long, long,  3)
_make_template(__long2,  long, long,  2)
_make_template(long,     long, long,  1)

_make_template(__ulong8,       unsigned long, unsigned long,  8)
_make_template(__ulong4,       unsigned long, unsigned long,  4)
_make_template(__ulong3,       unsigned long, unsigned long,  3)
_make_template(__ulong2,       unsigned long, unsigned long,  2)
_make_template(unsigned long,  unsigned long, unsigned long,  1)

/* Floating-point types */
_make_template(__float16,  float, float,  16)
_make_template(__float8,   float, float,  8)
_make_template(__float4,   float, float,  4)
_make_template(__float3,   float, float,  3)
_make_template(__float2,   float, float,  2)
_make_template(float,      float, float,  1)

_make_template(__double8,  double, double,  8)
_make_template(__double4,  double, double,  4)
_make_template(__double3,  double, double,  3)
_make_template(__double2,  double, double,  2)
_make_template(double,     double, double,  1)

/* Complex integral types */
_make_template(__cchar32,  __cchar, signed char,  32)
_make_template(__cchar16,  __cchar, signed char,  16)
_make_template(__cchar8,   __cchar, signed char,  8)
_make_template(__cchar4,   __cchar, signed char,  4)
_make_template(__cchar2,   __cchar, signed char,  2)
_make_template(__cchar,    __cchar, signed char,  1)

_make_template(__cshort16,  __cshort, short,  16)
_make_template(__cshort8,   __cshort, short,  8)
_make_template(__cshort4,   __cshort, short,  4)
_make_template(__cshort2,   __cshort, short,  2)
_make_template(__cshort,    __cshort, short,  1)

_make_template(__cint8,  __cint, int,  8)
_make_template(__cint4,  __cint, int,  4)
_make_template(__cint2,  __cint, int,  2)
_make_template(__cint,   __cint, int,  1)

_make_template(__clong4,  __clong, long,  4)
_make_template(__clong2,  __clong, long,  2)
_make_template(__clong,   __clong, long,  1)

/* Complex floating-point types */
_make_template(__cfloat8,  __cfloat, float,  8)
_make_template(__cfloat4,  __cfloat, float,  4)
_make_template(__cfloat2,  __cfloat, float,  2)
_make_template(__cfloat,   __cfloat, float,  1)

_make_template(__cdouble4,  __cdouble, double,  4)
_make_template(__cdouble2,  __cdouble, double,  2)
_make_template(__cdouble,   __cdouble, double,  1)

#undef _make_template

/*****************************************************************************/
/* STREAMING ENGINE (SE), STREAMING ADDRESS GENERATOR (SA) TRAITS            */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* se_veclen_from_traits -- Query for a corresponding __SE_VECLEN value      */
/*   given the number of elements in a vector. Generally, use of __se_veclen */
/*   is instead recommended.                                                 */
/*   Members: __SE_VECLEN value                                              */
/*   Example: se_veclen_from_traits<2>::value [yields __SE_VECLEN_2ELEMS]    */
/*---------------------------------------------------------------------------*/
template<size_t S> struct se_veclen_from_traits {};

template<> struct se_veclen_from_traits<1>
{ static constexpr __SE_VECLEN value = __SE_VECLEN_1ELEM; };
template<> struct se_veclen_from_traits<2>
{ static constexpr __SE_VECLEN value = __SE_VECLEN_2ELEMS; };
template<> struct se_veclen_from_traits<4>
{ static constexpr __SE_VECLEN value = __SE_VECLEN_4ELEMS; };
template<> struct se_veclen_from_traits<8>
{ static constexpr __SE_VECLEN value = __SE_VECLEN_8ELEMS; };
template<> struct se_veclen_from_traits<16>
{ static constexpr __SE_VECLEN value = __SE_VECLEN_16ELEMS; };
template<> struct se_veclen_from_traits<32>
{ static constexpr __SE_VECLEN value = __SE_VECLEN_32ELEMS; };
template<> struct se_veclen_from_traits<64>
{ static constexpr __SE_VECLEN value = __SE_VECLEN_64ELEMS; };

/*---------------------------------------------------------------------------*/
/* se_veclen -- Query for a corresponding __SE_VECLEN value for a given type.*/
/*   Members: __SE_VECLEN value                                              */
/*   Example: se_veclen<int16>::value [yields __SE_VECLEN_16ELEMS]           */
/*---------------------------------------------------------------------------*/
template<typename T> struct se_veclen
{
    static constexpr __SE_VECLEN value = se_veclen_from_traits<
                                             element_count_of<T>::value>::value;
};

/*---------------------------------------------------------------------------*/
/* se_eletype_from_traits -- Query for a corresponding __SE_ELETYPE given    */
/*   the size of elements, whether elements are complex, and whether to swap */
/*   complex elements. Generally, use of se_eletype is instead recommended.  */
/*   Members: __SE_ELETYPE value                                             */
/*   Example: se_eletype_from_traits<1, false, false>::value                 */
/*            [yields __SE_ELETYPE_8BIT]                                     */
/*---------------------------------------------------------------------------*/
template<size_t SIZE, bool CMPLX=false, bool SWAP=false>
struct se_eletype_from_traits {};

template<> struct se_eletype_from_traits<1, false, false>
{ static constexpr __SE_ELETYPE value = __SE_ELETYPE_8BIT; };
template<> struct se_eletype_from_traits<2, false, false>
{ static constexpr __SE_ELETYPE value = __SE_ELETYPE_16BIT; };
template<> struct se_eletype_from_traits<4, false, false>
{ static constexpr __SE_ELETYPE value = __SE_ELETYPE_32BIT; };
template<> struct se_eletype_from_traits<8, false, false>
{ static constexpr __SE_ELETYPE value = __SE_ELETYPE_64BIT; };
template<> struct se_eletype_from_traits<2, true, false>
{ static constexpr __SE_ELETYPE value = __SE_ELETYPE_8BIT_CMPLX_NOSWAP; };
template<> struct se_eletype_from_traits<4, true, false>
{ static constexpr __SE_ELETYPE value = __SE_ELETYPE_16BIT_CMPLX_NOSWAP; };
template<> struct se_eletype_from_traits<8, true, false>
{ static constexpr __SE_ELETYPE value = __SE_ELETYPE_32BIT_CMPLX_NOSWAP; };
template<> struct se_eletype_from_traits<16, true, false>
{ static constexpr __SE_ELETYPE value = __SE_ELETYPE_64BIT_CMPLX_NOSWAP; };
template<> struct se_eletype_from_traits<2, true, true>
{ static constexpr __SE_ELETYPE value = __SE_ELETYPE_8BIT_CMPLX_SWAP; };
template<> struct se_eletype_from_traits<4, true, true>
{ static constexpr __SE_ELETYPE value = __SE_ELETYPE_16BIT_CMPLX_SWAP; };
template<> struct se_eletype_from_traits<8, true, true>
{ static constexpr __SE_ELETYPE value = __SE_ELETYPE_32BIT_CMPLX_SWAP; };
template<> struct se_eletype_from_traits<16, true, true>
{ static constexpr __SE_ELETYPE value = __SE_ELETYPE_64BIT_CMPLX_SWAP; };

/*---------------------------------------------------------------------------*/
/* se_eletype -- Query for a corresponding __SE_ELETYPE given a scalar or    */
/*   vector type.                                                            */
/*   Members: __SE_ELETYPE value                                             */
/*   Example: se_eletype<char64>::value [yields __SE_ELETYPE_8BIT]           */
/*---------------------------------------------------------------------------*/
template<typename T>
struct se_eletype
{
    static constexpr size_t _ES = sizeof(typename element_type_of<T>::type);
    static constexpr size_t _CS = sizeof(typename component_type_of<T>::type);

    static constexpr __SE_ELETYPE value = se_eletype_from_traits<
                                                             _ES,
                                                             _CS != _ES,
                                                             _CS != _ES>::value;
};

/*---------------------------------------------------------------------------*/
/* sa_veclen_from_traits -- Query for a corresponding __SA_VECLEN value      */
/*   given the number of elements in a vector. Generally, use of __sa_veclen */
/*   is instead recommended.                                                 */
/*   Members: __SA_VECLEN value                                              */
/*   Example: sa_veclen_from_traits<2>::value [yields __SA_VECLEN_2ELEMS]    */
/*---------------------------------------------------------------------------*/
template<size_t S> struct sa_veclen_from_traits {};

template<> struct sa_veclen_from_traits<1>
{ static constexpr __SA_VECLEN value = __SA_VECLEN_1ELEM; };
template<> struct sa_veclen_from_traits<2>
{ static constexpr __SA_VECLEN value = __SA_VECLEN_2ELEMS; };
template<> struct sa_veclen_from_traits<4>
{ static constexpr __SA_VECLEN value = __SA_VECLEN_4ELEMS; };
template<> struct sa_veclen_from_traits<8>
{ static constexpr __SA_VECLEN value = __SA_VECLEN_8ELEMS; };
template<> struct sa_veclen_from_traits<16>
{ static constexpr __SA_VECLEN value = __SA_VECLEN_16ELEMS; };
template<> struct sa_veclen_from_traits<32>
{ static constexpr __SA_VECLEN value = __SA_VECLEN_32ELEMS; };
template<> struct sa_veclen_from_traits<64>
{ static constexpr __SA_VECLEN value = __SA_VECLEN_64ELEMS; };

/*---------------------------------------------------------------------------*/
/* sa_veclen -- Query for a corresponding __SA_VECLEN value for a given type.*/
/*   Members: __SA_VECLEN value                                              */
/*   Example: sa_veclen<int16>::value [yields __SA_VECLEN_16ELEMS]           */
/*---------------------------------------------------------------------------*/
template<typename T> struct sa_veclen
{
    static constexpr __SA_VECLEN value = sa_veclen_from_traits<
                                             element_count_of<T>::value>::value;
};

/*****************************************************************************/
/* STREAMING ENGINE (SE), STREAMING ADDRESS GENERATOR (SA) ACCESSORS         */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* strm_eng -- Used to access an open streaming engine (SE) instance.        */
/*   Members: T get(): Get the stream value without advancing.               */
/*            T get_adv(): Get the stream value and advance.                 */
/*   Example: strm_eng<0, int16>::get_adv() [yields the next int16]          */
/*---------------------------------------------------------------------------*/
template<unsigned int id, typename T> struct strm_eng {};

/*---------------------------------------------------------------------------*/
/* strm_agen -- Used to access an open streaming address generator (SA)      */
/*   instance.                                                               */
/*   Members: T *get(): Get the stream value without advancing.              */
/*            T *get_adv(): Get the stream value and advance.                */
/*            __vpred get_vpred(): Get the next predicate value.             */
/*   Example: strm_agen<0, int16>::get_adv(ptr) [yields the next int16*]     */
/*---------------------------------------------------------------------------*/
template<unsigned int id, typename T> struct strm_agen {};

/* Implementation details; don't use directly. */
/* Bool not currently supported due to lack of 1 element interface. */
#define _make_template(_T, _t) \
template<unsigned int id> \
struct strm_eng<id, _T> \
{ \
    static _T get() \
    { \
        static_assert(id <= 1, "SE id is out of range."); \
        return __se_ac_ ## _t(id, /* adv= */0); \
    } \
 \
    static _T get_adv() \
    { \
        static_assert(id <= 1, "SE id is out of range."); \
        return __se_ac_ ## _t(id, /* adv= */1); \
    } \
}; \
 \
template<unsigned int id> \
struct strm_agen<id, _T> \
{ \
    static typename make_pointer<_T>::type get(const void *p) \
    { \
        static_assert(id <= 3, "SA id is out of range."); \
        return (typename make_pointer<_T>::type)__sa(id, sizeof(_T)/__numelemof(_T), p); \
    } \
 \
    static typename make_pointer<_T>::type get_adv(const void *p) \
    { \
        static_assert(id <= 3, "SA id is out of range."); \
        return (typename make_pointer<_T>::type)__sa_adv(id, sizeof(_T)/__numelemof(_T), p); \
    } \
 \
    static __vpred get_vpred() \
    { \
        static_assert(id <= 3, "SA id is out of range."); \
        return __sa_vpred(id, sizeof(_T)/__numelemof(_T)); \
    } \
};

/* Integral Types */
_make_template(__char64, char64)
_make_template(__char32, char32)
_make_template(__char16, char16)
_make_template(__char8, char8)
_make_template(__char4, char4)
_make_template(__char2, char2)
_make_template(signed char, char)

_make_template(__uchar64, uchar64)
_make_template(__uchar32, uchar32)
_make_template(__uchar16, uchar16)
_make_template(__uchar8, uchar8)
_make_template(__uchar4, uchar4)
_make_template(__uchar2, uchar2)
_make_template(unsigned char, uchar)

_make_template(__short32, short32)
_make_template(__short16, short16)
_make_template(__short8, short8)
_make_template(__short4, short4)
_make_template(__short2, short2)
_make_template(short, short)

_make_template(__ushort32, ushort32)
_make_template(__ushort16, ushort16)
_make_template(__ushort8, ushort8)
_make_template(__ushort4, ushort4)
_make_template(__ushort2, ushort2)
_make_template(unsigned short, ushort)

_make_template(__int16, int16)
_make_template(__int8, int8)
_make_template(__int4, int4)
_make_template(__int2, int2)
_make_template(int, int)

_make_template(__uint16, uint16)
_make_template(__uint8, uint8)
_make_template(__uint4, uint4)
_make_template(__uint2, uint2)
_make_template(unsigned int, uint)

_make_template(__long8, long8)
_make_template(__long4, long4)
_make_template(__long2, long2)
_make_template(long, long)

_make_template(__ulong8, ulong8)
_make_template(__ulong4, ulong4)
_make_template(__ulong2, ulong2)
_make_template(unsigned long, ulong)

/* Floating-point types */
_make_template(__float16, float16)
_make_template(__float8, float8)
_make_template(__float4, float4)
_make_template(__float2, float2)
_make_template(float, float)

_make_template(__double8, double8)
_make_template(__double4, double4)
_make_template(__double2, double2)
_make_template(double, double)

/* Complex integral types */
_make_template(__cchar32, cchar32)
_make_template(__cchar16, cchar16)
_make_template(__cchar8, cchar8)
_make_template(__cchar4, cchar4)
_make_template(__cchar2, cchar2)
_make_template(__cchar, cchar)

_make_template(__cshort16, cshort16)
_make_template(__cshort8, cshort8)
_make_template(__cshort4, cshort4)
_make_template(__cshort2, cshort2)
_make_template(__cshort, cshort)

_make_template(__cint8, cint8)
_make_template(__cint4, cint4)
_make_template(__cint2, cint2)
_make_template(__cint, cint)

_make_template(__clong4, clong4)
_make_template(__clong2, clong2)
_make_template(__clong, clong)

/* Complex floating-point types */
_make_template(__cfloat8, cfloat8)
_make_template(__cfloat4, cfloat4)
_make_template(__cfloat2, cfloat2)
_make_template(__cfloat, cfloat)

_make_template(__cdouble4, cdouble4)
_make_template(__cdouble2, cdouble2)
_make_template(__cdouble, cdouble)

#undef _make_template

} /* namespace c7x */
#endif /* __cplusplus */

#endif /* __C7X_UNSTABLE_API */

#endif /* C7X_SCALABLE_H */
