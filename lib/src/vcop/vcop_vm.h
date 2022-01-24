/*****************************************************************************/
/* VCOP_VM.H                                                                 */
/*                                                                           */
/* Copyright (c) 2016 Texas Instruments Incorporated                         */
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
/*                                                                           */
/*    VCOP Virtual Machine                                                   */
/*                                                                           */
/*    This file supports execution of VCOP Kernels on C7x.                   */
/*                                                                           */
/*    The translator tool (vcc7x) translates VCOP Kernels to C++ programs    */
/*    that invoke methods in this virtual machine.                           */
/*                                                                           */
/*    The methods implement VCOP operations using C7x instructions, through  */
/*    the use of native vector (OpenCL) types and C7x intrinsics.            */
/*****************************************************************************/
#ifndef __VCOP_VM
#define __VCOP_VM

#pragma ALWAYS_INLINE

#include <vcop/vcop.h>
#include <c7x.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// #define VVM_DEBUG       // #define to enable VM debug

namespace VCOP_VM
{
/******************************************************************************
* Basic types to emulate VCOP types
******************************************************************************/
/*-----------------------------------------------------------------------------
* __vector is the type corresponding to a C7x vector. VCOP vectors are
* modeled as full-width vectors on C7x, even if the upper lanes are unused,
* because many of the intrisics expect full width vectors.
*----------------------------------------------------------------------------*/
typedef __int16 __vector;

/*-----------------------------------------------------------------------------
* __agen is just a signed int, representing the address offset
*----------------------------------------------------------------------------*/
typedef int32_t __agen;

/*-----------------------------------------------------------------------------
* 'first' macro for testing first iteration
* 'last' macro for testing last iteration
*----------------------------------------------------------------------------*/
#define __first(lcv)     (lcv == 0)
#define __last(lcv,trip) (lcv == (trip-1))

/*-----------------------------------------------------------------------------
* The kernel API defines the parameter block as an array of unsigned short.
* For 7x translation we use a structure. This macro converts the size
* into unsigned short units.
*----------------------------------------------------------------------------*/
#define __PBLOCK_SIZE(type) ((sizeof(type)+1)/(sizeof(uint16_t)))

/******************************************************************************
* Helper metafunctions
******************************************************************************/
/*-----------------------------------------------------------------------------
* as_type(T,val): a reinterpret cast with paramterizable type
*----------------------------------------------------------------------------*/
#define as_type(T,val) reinterpret<T>(__as_uchar64(val))

/*-----------------------------------------------------------------------------
* reinterpret<T>(__uchar64 V)
*    reinterpret a generic __uchar64  vector as "T"
*----------------------------------------------------------------------------*/
template <typename T> T inline reinterpret(__uchar64 v);

template <> __char64   inline reinterpret<__char64>(__uchar64 v)
   { return __as_char64(v); }
template <> __uchar64  inline reinterpret<__uchar64>(__uchar64 v)
   { return __as_uchar64(v); }
template <> __short32  inline reinterpret<__short32>(__uchar64 v)
   { return __as_short32(v); }
template <> __ushort32 inline reinterpret<__ushort32>(__uchar64 v)
   { return __as_ushort32(v); }
template <> __int16    inline reinterpret<__int16>(__uchar64 v)
   { return __as_int16(v); }
template <> __uint16   inline reinterpret<__uint16>(__uchar64 v)
   { return __as_uint16(v); }

/*-----------------------------------------------------------------------------
* vector<element_type, N>::type
*    Construct an OpenCL vector type from element type and number of elements
*    N defaults to native machine width (e.g. 512 bits on c71x)
*----------------------------------------------------------------------------*/
template <typename type, int n = sizeof(__vector)/sizeof(type)> struct vector;
template<> struct vector<int8_t,1> { typedef int8_t type; };
template<> struct vector<int8_t,2> { typedef __char2 type; };
template<> struct vector<int8_t,4> { typedef __char4 type; };
template<> struct vector<int8_t,8> { typedef __char8 type; };
template<> struct vector<int8_t,16> { typedef __char16 type; };
template<> struct vector<int8_t,32> { typedef __char32 type; };
template<> struct vector<int8_t,64> { typedef __char64 type; };
template<> struct vector<uint8_t,2> { typedef __uchar2 type; };
template<> struct vector<uint8_t,1> { typedef uint8_t type; };
template<> struct vector<uint8_t,4> { typedef __uchar4 type; };
template<> struct vector<uint8_t,8> { typedef __uchar8 type; };
template<> struct vector<uint8_t,16> { typedef __uchar16 type; };
template<> struct vector<uint8_t,32> { typedef __uchar32 type; };
template<> struct vector<uint8_t,64> { typedef __uchar64 type; };
template<> struct vector<int16_t,1> { typedef int16_t type; };
template<> struct vector<int16_t,2> { typedef __short2 type; };
template<> struct vector<int16_t,4> { typedef __short4 type; };
template<> struct vector<int16_t,8> { typedef __short8 type; };
template<> struct vector<int16_t,16> { typedef __short16 type; };
template<> struct vector<int16_t,32> { typedef __short32 type; };
template<> struct vector<uint16_t,1> { typedef uint16_t type; };
template<> struct vector<uint16_t,2> { typedef __ushort2 type; };
template<> struct vector<uint16_t,4> { typedef __ushort4 type; };
template<> struct vector<uint16_t,8> { typedef __ushort8 type; };
template<> struct vector<uint16_t,16> { typedef __ushort16 type; };
template<> struct vector<uint16_t,32> { typedef __ushort32 type; };
template<> struct vector<int32_t,1> { typedef int32_t type; };
template<> struct vector<int32_t,2> { typedef __int2 type; };
template<> struct vector<int32_t,4> { typedef __int4 type; };
template<> struct vector<int32_t,8> { typedef __int8 type; };
template<> struct vector<int32_t,16> { typedef __int16 type; };
template<> struct vector<uint32_t,1> { typedef uint32_t type; };
template<> struct vector<uint32_t,2> { typedef __uint2 type; };
template<> struct vector<uint32_t,4> { typedef __uint4 type; };
template<> struct vector<uint32_t,8> { typedef __uint8 type; };
template<> struct vector<uint32_t,16> { typedef __uint16 type; };
template<> struct vector<int64_t,1> { typedef int64_t type; };
template<> struct vector<int64_t,2> { typedef __long2 type; };
template<> struct vector<int64_t,4> { typedef __long4 type; };
template<> struct vector<int64_t,8> { typedef __long8 type; };
template<> struct vector<uint64_t,1> { typedef uint64_t type; };
template<> struct vector<uint64_t,2> { typedef __ulong2 type; };
template<> struct vector<uint64_t,4> { typedef __ulong4 type; };
template<> struct vector<uint64_t,8> { typedef __ulong8 type; };

/*-----------------------------------------------------------------------------
* scalar<element_type>
*   Class to allow vector templates to specialize on scalar types
*----------------------------------------------------------------------------*/
template <typename type> struct scalar;

/*-----------------------------------------------------------------------------
* subvec<src_type, dst_type>::apply(src_type& T)
*    Return subvector from full-width machine vector.
*    This template facilitates type-independent manipulation of vectors
*    e.g. subvec<__int16, __int4>::apply(V) returns first 4 elements of V
*----------------------------------------------------------------------------*/
template <typename src, typename dst> struct subvec;

template<typename T> struct subvec<T, T>
   { static T& apply(T& src) { return src; } };

template<typename T, typename T2> struct subvec
   { static T2& apply(T& src) { return *(T2*)(&src); } };

/*-----------------------------------------------------------------------------
* traits class - abstracts properties of different element types
*----------------------------------------------------------------------------*/
template <typename t> struct traits;

template <> struct traits<int8_t>
{
   typedef int16_t  short_type;
   typedef int8_t   signed_type;
   typedef uint8_t  unsigned_type;
   typedef __int2 circ2_vectype;
};

template <> struct traits<uint8_t>
{
   typedef uint16_t  short_type;
   typedef int8_t    signed_type;
   typedef uint8_t   unsigned_type;
   typedef __uint2 circ2_vectype;
};

template <> struct traits<int16_t>
{
   typedef int16_t   signed_type;
   typedef uint16_t  unsigned_type;
   typedef __int2 circ2_vectype;
};

template <> struct traits<uint16_t>
{
   typedef int16_t    signed_type;
   typedef uint16_t   unsigned_type;
   typedef __uint2 circ2_vectype;
};

template <> struct traits<int32_t>
{
   typedef __int16 promoted_vectype;
   typedef int32_t   promoted_type;
   typedef int32_t   signed_type;
   typedef uint32_t  unsigned_type;
   typedef __int2 circ2_vectype;
};

template <> struct traits<uint32_t>
{
   typedef __uint16 promoted_vectype;
   typedef uint32_t promoted_type;
   typedef int32_t   signed_type;
   typedef uint32_t  unsigned_type;
   typedef __uint2 circ2_vectype;
};

/******************************************************************************
* Streaming engine (SE) setup
******************************************************************************/
/*-----------------------------------------------------------------------------
* SE_element_type_flag - given element type, return SE element type flag
*----------------------------------------------------------------------------*/
template <typename element_type> struct SE_element_type_flag;
template <> struct SE_element_type_flag<int8_t>
   { static const __SE_ELETYPE val = __SE_ELETYPE_8BIT; };
template <> struct SE_element_type_flag<uint8_t>
   { static const __SE_ELETYPE val = __SE_ELETYPE_8BIT; };
template <> struct SE_element_type_flag<int16_t>
   { static const __SE_ELETYPE val = __SE_ELETYPE_16BIT; };
template <> struct SE_element_type_flag<uint16_t>
   { static const __SE_ELETYPE val = __SE_ELETYPE_16BIT; };
template <> struct SE_element_type_flag<int32_t>
   { static const __SE_ELETYPE val = __SE_ELETYPE_32BIT; };
template <> struct SE_element_type_flag<uint32_t>
   { static const __SE_ELETYPE val = __SE_ELETYPE_32BIT; };

/*-----------------------------------------------------------------------------
* SE_veclen_flag - convert number of bytes to SE vector length flag
*----------------------------------------------------------------------------*/
template <int bytes> struct SE_veclen_flag;
template <> struct SE_veclen_flag<1>
   { static const __SE_VECLEN val = __SE_VECLEN_1ELEM; };
template <> struct SE_veclen_flag<2>
   { static const __SE_VECLEN val = __SE_VECLEN_2ELEMS; };
template <> struct SE_veclen_flag<4>
   { static const __SE_VECLEN val = __SE_VECLEN_4ELEMS; };
template <> struct SE_veclen_flag<8>
   { static const __SE_VECLEN val = __SE_VECLEN_8ELEMS; };
template <> struct SE_veclen_flag<16>
   { static const __SE_VECLEN val = __SE_VECLEN_16ELEMS; };
template <> struct SE_veclen_flag<32>
   { static const __SE_VECLEN val = __SE_VECLEN_32ELEMS; };
template <> struct SE_veclen_flag<64>
   { static const __SE_VECLEN val = __SE_VECLEN_64ELEMS; };

/*-----------------------------------------------------------------------------
* SE_element_dup_flag - convert number of lanes to SE element duplicate flag
*----------------------------------------------------------------------------*/
template <int simd> struct SE_element_dup_flag;
template <> struct SE_element_dup_flag<8>
   { static const __SE_ELEDUP val = __SE_ELEDUP_8X; };
template <> struct SE_element_dup_flag<16>
   { static const __SE_ELEDUP val = __SE_ELEDUP_16X; };

/*-----------------------------------------------------------------------------
* SE_promote_flag - given src and dst type, return SE promote flag
*----------------------------------------------------------------------------*/
template <typename memtype, typename regtype> struct SE_promote_flag;
template <> struct SE_promote_flag<int8_t, int32_t>
   { static const __SE_PROMOTE val = __SE_PROMOTE_4X_SIGNEXT; };
template <> struct SE_promote_flag<uint8_t, int32_t>
   { static const __SE_PROMOTE val = __SE_PROMOTE_4X_ZEROEXT; };
template <> struct SE_promote_flag<int16_t, int32_t>
   { static const __SE_PROMOTE val = __SE_PROMOTE_2X_SIGNEXT; };
template <> struct SE_promote_flag<uint16_t, int32_t>
   { static const __SE_PROMOTE val = __SE_PROMOTE_2X_ZEROEXT; };
template <> struct SE_promote_flag<int32_t, int32_t>
   { static const __SE_PROMOTE val = __SE_PROMOTE_OFF; };
template <> struct SE_promote_flag<uint32_t, int32_t>
   { static const __SE_PROMOTE val = __SE_PROMOTE_OFF; };

/*-----------------------------------------------------------------------------
* SE_defaults
*    Class to provide default SE flag settings for load templates.
*    Specializations can derive from this class, then override specific
*    flags as needed.
*----------------------------------------------------------------------------*/
struct SE_defaults
{
   static const __SE_VECLEN SE_veclen      = __SE_VECLEN_8ELEMS;
   static const __SE_GRPDUP SE_group_dup   = __SE_GRPDUP_OFF;
   static const __SE_ELEDUP SE_element_dup = __SE_ELEDUP_OFF;
   static const __SE_PROMOTE SE_promote     = __SE_PROMOTE_OFF;
   static const __SE_DECIM SE_decimate    = __SE_DECIM_OFF;
   static const __SE_TRANSPOSE SE_transpose   = __SE_TRANSPOSE_OFF;
   static const __SE_DECDIM SE_decdim1     = __SE_DECDIM_DIM0;
   static const __SE_DECDIMSD SE_decdim1sd   = __SE_DECDIMSD_DIM0;
   static const __SE_DECDIM SE_decdim2     = __SE_DECDIM_DIM0;
   static const __SE_DECDIMSD SE_decdim2sd   = __SE_DECDIMSD_DIM0;
   static const __SE_LEZR SE_lezr        = __SE_LEZR_OFF;
};

/*-----------------------------------------------------------------------------
* shift_dims()
*    Given the dims and icnts of a SE/SA configuration, insert another dimension
*    at dimension n by shifting the following dimensions up.
*----------------------------------------------------------------------------*/
inline void shift_dims(int n, int32_t dims[], uint32_t icnts[])
{
   for (int i = 5; i > n; i--)
   {
      dims[i] = dims[i-1];
      icnts[i] = icnts[i-1];
   }
}

/*-----------------------------------------------------------------------------
* max_agen()
*    Given the iteration counts and AGEN coefficients, determine the maximum
*    value that an AGEN may hold.
*----------------------------------------------------------------------------*/
inline int32_t max_agen(int32_t n0 = 1, int32_t k0 = 0,
                        int32_t n1 = 1, int32_t k1 = 0,
                        int32_t n2 = 1, int32_t k2 = 0,
                        int32_t n3 = 1, int32_t k3 = 0,
                        int32_t n4 = 1, int32_t k4 = 0,
                        int32_t n5 = 1, int32_t k5 = 0)
{
   int32_t max = 0;
   if (k0 > 0) max += ((n0-1) * k0);
   if (k1 > 0) max += ((n1-1) * k1);
   if (k2 > 0) max += ((n2-1) * k2);
   if (k3 > 0) max += ((n3-1) * k3);
   if (k4 > 0) max += ((n4-1) * k4);
   if (k5 > 0) max += ((n5-1) * k5);
   return max;
}

/*-----------------------------------------------------------------------------
* max8()
*    Find the maximum of up to 8 values.
*----------------------------------------------------------------------------*/
inline int32_t max8(int32_t n0 = 0, int32_t n1 = 0,
                    int32_t n2 = 0, int32_t n3 = 0,
                    int32_t n4 = 0, int32_t n5 = 0,
                    int32_t n6 = 0, int32_t n7 = 0)
{
   int32_t max = n0;
   if (n1 > max) max = n1;
   if (n2 > max) max = n2;
   if (n3 > max) max = n3;
   if (n4 > max) max = n4;
   if (n5 > max) max = n5;
   if (n6 > max) max = n6;
   if (n7 > max) max = n7;
   return max;
}

#ifdef VVM_DEBUG
/*-----------------------------------------------------------------------------
* SE_dump - Dump the SE flags and parameters
*----------------------------------------------------------------------------*/
static inline void SE_dump(__SE_TEMPLATE_v1 params)
{
    printf("SE setup: eletype=%d promote=%d decim=%d "
            "veclen=%d grpdup=%d eldup=%d transpose=%d decdim1=%d "
            "decdim1sd=%d decdim2=%d, decdim2sd=%d lezr=%d\n",
            params.ELETYPE,
            params.PROMOTE,
            params.DECIM,
            params.VECLEN,
            params.GRPDUP,
            params.ELEDUP,
            params.TRANSPOSE,
            params.DECDIM1,
            params.DECDIM1SD,
            params.DECDIM2,
            params.DECDIM2SD,
            params.LEZR);
    printf("        : icnt0=%d (icnt1,dim1)=(%d,%d) (icnt2,dim2)=(%d,%d) "
            "(icnt3,dim3)=(%d,%d) (icnt4,dim4)=(%d,%d) "
            "(icnt5,dim5)=(%d,%d)\n",
            params.ICNT0,
            params.ICNT1, params.DIM1,
            params.ICNT2, params.DIM2,
            params.ICNT3, params.DIM3,
            params.ICNT4, params.DIM4,
            params.ICNT5, params.DIM5);
}

/*-----------------------------------------------------------------------------
* SA_dump - Dump the SA flags and parameters
*----------------------------------------------------------------------------*/
static inline void SA_dump(__SA_TEMPLATE_v1 params)
{
    printf("SA setup: decdim1=%d decdim1sd=%d decdim2=%d decdim2sd=%d "
            "veclen=%d\n",
            params.DECDIM1,
            params.DECDIM1SD,
            params.DECDIM2,
            params.DECDIMS2SD,
            params.VECLEN);
    printf("        : icnt0=%d (icnt1,dim1)=(%d,%d) (icnt2,dim2)=(%d,%d) "
            "(icnt3,dim3)=(%d,%d) (icnt4,dim4)=(%d,%d) "
            "(icnt5,dim5)=(%d,%d)\n",
            params.ICNT0,
            params.ICNT1, params.DIM1,
            params.ICNT2, params.DIM2,
            params.ICNT3, params.DIM3,
            params.ICNT4, params.DIM4,
            params.ICNT5, params.DIM5);
}
#endif

/*-----------------------------------------------------------------------------
* Transpose tags - transpose mode SE_init/SA_init configuration flags
*----------------------------------------------------------------------------*/
typedef struct {} TRANSPOSE_ON;
typedef struct {} TRANSPOSE_OFF;

/*-----------------------------------------------------------------------------
* SE_init
*    This function is called in the init() function outside the
*    kernel; the generated configuration is passed to the kernel via the
*    tvals structure.  Specializations can provide different values for
*    the SE_* settings variables, or override the whole function.
*----------------------------------------------------------------------------*/
template <typename SEsettings>
struct SE_init_base
{
   static inline __SE_TEMPLATE_v1 configure_SE(       uint32_t icnt0,
                                   int32_t  dim1 = 0, uint32_t icnt1 = 1,
                                   int32_t  dim2 = 0, uint32_t icnt2 = 1,
                                   int32_t  dim3 = 0, uint32_t icnt3 = 1,
                                   int32_t  dim4 = 0, uint32_t icnt4 = 1,
                                   int32_t  dim5 = 0, uint32_t icnt5 = 1)
   {
      __SE_TEMPLATE_v1 params =
      {
#if __little_endian__
         /* ICNT0            = */ icnt0,
         /* ICNT1            = */ icnt1,
         /* ICNT2            = */ icnt2,
         /* ICNT3            = */ icnt3,
         /* ICNT4            = */ icnt4,
         /* ICNT5            = */ icnt5,
         /* DECDIM1_WIDTH    = */ SEsettings::SE_decdim1,
         /* DECDIM2_WIDTH    = */ SEsettings::SE_decdim2,
         /* DIM1             = */ dim1,
         /* DIM2             = */ dim2,
         /* DIM3             = */ dim3,
         /* DIM4             = */ dim4,
         /* DIM5             = */ dim5,
         /* LEZR_CN          = */ SEsettings::SE_lezr,
         /* _reserved1       = */ 0,
         /*** Flags ***/
         /* ELETYPE          = */ SEsettings::SE_element_type,
         /* TRANSPOSE        = */ SEsettings::SE_transpose,
         /* _reserved2       = */ 0,
         /* PROMOTE          = */ SEsettings::SE_promote,
         /* _reserved3       = */ 0,
         /* VECLEN           = */ SEsettings::SE_veclen,
         /* _reserved4       = */ 0,
         /* ELDUP            = */ SEsettings::SE_element_dup,
         /* GRDUP            = */ SEsettings::SE_group_dup,
         /* DECIM            = */ SEsettings::SE_decimate,
         /* FILLVAL          = */ __SE_FILLVAL_ZERO,
         /* DIMFMT           = */ __SE_DIMFMT_6D,
         /* DIR              = */ __SE_DIR_INC,
         /* CBK0             = */ 0,
         /* CBK1             = */ 0,
         /* AM0              = */ __SE_AM_LINEAR,
         /* AM1              = */ __SE_AM_LINEAR,
         /* AM2              = */ __SE_AM_LINEAR,
         /* AM3              = */ __SE_AM_LINEAR,
         /* AM4              = */ __SE_AM_LINEAR,
         /* AM5              = */ __SE_AM_LINEAR,
         /* DECDIM1          = */ SEsettings::SE_decdim1,
         /* DECDIM1SD        = */ SEsettings::SE_decdim1sd,
         /* DECDIM2          = */ SEsettings::SE_decdim2,
         /* DECDIM2SD        = */ SEsettings::SE_decdim2sd,
         /* LEZR             = */ SEsettings::SE_lezr,
         /* TEMPLATE_FMT     = */ __SE_TEMPLATE_FMT_v1
# else
         /* Invert of 64 bit boundaries */
         /* ICNT1            = */ icnt1,
         /* ICNT0            = */ icnt0,

         /* ICNT3            = */ icnt3,
         /* ICNT2            = */ icnt2,

         /* ICNT5            = */ icnt5,
         /* ICNT4            = */ icnt4,

         /* DECDIM2_WIDTH    = */ SEsettings::SE_decdim2,
         /* DECDIM1_WIDTH    = */ SEsettings::SE_decdim1,

         /* DIM2             = */ dim2,
         /* DIM1             = */ dim1,

         /* DIM4             = */ dim4,
         /* DIM3             = */ dim3,

         /* _reserved1       = */ 0,
         /* LEZR_CN          = */ SEsettings::SE_lezr,
         /* DIM5             = */ dim5,

         /*** Flags ***/
         /* TEMPLATE_FMT     = */ __SE_TEMPLATE_FMT_v1
         /* LEZR             = */ SEsettings::SE_lezr,
         /* DECDIM2SD        = */ SEsettings::SE_decdim2sd,
         /* DECDIM2          = */ SEsettings::SE_decdim2,
         /* DECDIM1SD        = */ SEsettings::SE_decdim1sd,
         /* DECDIM1          = */ SEsettings::SE_decdim1,
         /* AM5              = */ __SE_AM_LINEAR,
         /* AM4              = */ __SE_AM_LINEAR,
         /* AM3              = */ __SE_AM_LINEAR,
         /* AM2              = */ __SE_AM_LINEAR,
         /* AM1              = */ __SE_AM_LINEAR,
         /* AM0              = */ __SE_AM_LINEAR,
         /* CBK1             = */ 0,
         /* CBK0             = */ 0,
         /* DIR              = */ __SE_DIR_INC,
         /* DIMFMT           = */ __SE_DIMFMT_6D,
         /* FILLVAL          = */ __SE_FILLVAL_ZERO,
         /* DECIM            = */ SEsettings::SE_decimate,
         /* GRDUP            = */ SEsettings::SE_group_dup,
         /* ELDUP            = */ SEsettings::SE_element_dup,
         /* _reserved4       = */ 0,
         /* VECLEN           = */ SEsettings::SE_veclen,
         /* _reserved3       = */ 0,
         /* PROMOTE          = */ SEsettings::SE_promote,
         /* _reserved2       = */ 0,
         /* TRANSPOSE        = */ SEsettings::SE_transpose,
         /* ELETYPE          = */ SEsettings::SE_element_type,
#endif
      };
      return params;
   }
}; // SE_init_base

template <typename type, typename SEsettings, typename transpose=TRANSPOSE_OFF>
struct SE_init;

template <typename type, typename SEsettings>
struct SE_init <type, SEsettings, TRANSPOSE_OFF> :
   public SE_init_base<SEsettings>
{
   static inline __SE_TEMPLATE_v1 apply(uint32_t icnt0,
                                int32_t  dim1 = 0, uint32_t icnt1 = 1,
                                int32_t  dim2 = 0, uint32_t icnt2 = 1,
                                int32_t  dim3 = 0, uint32_t icnt3 = 1,
                                int32_t  dim4 = 0, uint32_t icnt4 = 1,
                                int32_t  dim5 = 0, uint32_t icnt5 = 1)
   {
      __SE_TEMPLATE_v1 SE_Template =
          SE_init_base<SEsettings>::configure_SE(icnt0,
                                             dim1, icnt1, dim2, icnt2,
                                             dim3, icnt3, dim4, icnt4,
                                             dim5, icnt5);

      #ifdef VVM_DEBUG
      SE_dump(SE_Template);
      #endif

      return SE_Template;
   }
}; // SE_init<SEsettings, false>

template <typename type, typename SEsettings>
struct SE_init <type, SEsettings, TRANSPOSE_ON> :
   public SE_init_base<SEsettings>
{
   static inline __SE_TEMPLATE_v1 apply(uint32_t icnt0,
                                int32_t  dim1 = 0, uint32_t icnt1 = 1,
                                int32_t  dim2 = 0, uint32_t icnt2 = 1,
                                int32_t  dim3 = 0, uint32_t icnt3 = 1,
                                int32_t  dim4 = 0, uint32_t icnt4 = 1,
                                int32_t  dim5 = 0, uint32_t icnt5 = 1)
   {
      // initialize local dim/icnt vectors from passed-in values
      int32_t dim[6];
      uint32_t icnt[6];

      dim[0] = 1;
      icnt[0] = icnt0;
      dim[1] = dim1;
      icnt[1] = icnt1;
      dim[2] = dim2;
      icnt[2] = icnt2;
      dim[3] = dim3;
      icnt[3] = icnt3;
      dim[4] = dim4;
      icnt[4] = icnt4;
      dim[5] = dim5;
      icnt[5] = icnt5;

      // find loop(s) and adjust
      const int ELESZ  = sizeof(type);
      const int ROWSZ  = VCOP_SIMD_WIDTH * 4 / ELESZ;
      const int VECLEN = VCOP_SIMD_WIDTH;
      const int BLKW   = (VCOP_SIMD_WIDTH+1) * 4 / ELESZ;
      const int BLKSZ  = VCOP_SIMD_WIDTH * BLKW;

      // skip vector loop [0]; will adjust below
      for (int i = 1; i < 6; ++i)
      {
         uint32_t absdim = abs(dim[i]);

         // horizontal row loop
         if (absdim >= VECLEN && absdim < ROWSZ)
            dim[i] *= VCOP_SIMD_WIDTH;

         // vertical row loop
         else if (absdim >= BLKW && absdim < BLKSZ)
         {
            dim[i] /= BLKW;
            // if traverses block boundary, split
            if (absdim * icnt[i] > BLKSZ)
            {
               shift_dims(i, dim, icnt);
               uint32_t iters_per_block = BLKSZ/absdim;
               icnt[i] = iters_per_block;

               i++;
              dim[i] = BLKSZ;
              icnt[i] /= iters_per_block;
            }
         }
      }

      // swap vector loop into DIM1 (DIM0/1 interchanged for transpose SE setup)
      icnt[0] = icnt[1];
      dim[0] = dim[1];       // should be 1

      if (dim[0] > 1)
      {
         // We are not striding by the type size.
         // We must insert another dimension.
         shift_dims(2, dim, icnt);
         icnt[2] = icnt[0];
         dim[2] = dim[0];
         icnt[0] = 1;
      }

      dim[1] = VECLEN;
      icnt[1] = VCOP_SIMD_WIDTH;

      __SE_TEMPLATE_v1 SE_Template =
          SE_init_base<SEsettings>::configure_SE(icnt[0],
                                             dim[1], icnt[1], dim[2], icnt[2],
                                             dim[3], icnt[3], dim[4], icnt[4],
                                             dim[5], icnt[5]);

      #ifdef VVM_DEBUG
      SE_dump(SE_Template);
      #endif

      return SE_Template;
   }
}; // SE_init<SEsettings, true>


/******************************************************************************
* Streaming Address Generator (SA) setup
******************************************************************************/
/*-----------------------------------------------------------------------------
* SA_veclen_flag - convert number of elements to SA vector length flag
*----------------------------------------------------------------------------*/
template <int bytes> struct SA_veclen_flag;
template <> struct SA_veclen_flag<1>
   { static const __SA_VECLEN val = __SA_VECLEN_1ELEM; };
template <> struct SA_veclen_flag<2>
   { static const __SA_VECLEN val = __SA_VECLEN_2ELEMS; };
template <> struct SA_veclen_flag<4>
   { static const __SA_VECLEN val = __SA_VECLEN_4ELEMS; };
template <> struct SA_veclen_flag<8>
   { static const __SA_VECLEN val = __SA_VECLEN_8ELEMS; };
template <> struct SA_veclen_flag<16>
   { static const __SA_VECLEN val = __SA_VECLEN_16ELEMS; };
template <> struct SA_veclen_flag<32>
   { static const __SA_VECLEN val = __SA_VECLEN_32ELEMS; };
template <> struct SA_veclen_flag<64>
   { static const __SA_VECLEN val = __SA_VECLEN_64ELEMS; };

/*-----------------------------------------------------------------------------
* SA init function - return setup vector
*----------------------------------------------------------------------------*/
template <int nelem>
struct SA_init_base
{
   static inline __SA_TEMPLATE_v1 configure_SA(       uint32_t icnt0,
                                   int32_t  dim1 = 0, uint32_t icnt1 = 1,
                                   int32_t  dim2 = 0, uint32_t icnt2 = 1,
                                   int32_t  dim3 = 0, uint32_t icnt3 = 1,
                                   int32_t  dim4 = 0, uint32_t icnt4 = 1,
                                   int32_t  dim5 = 0, uint32_t icnt5 = 1)
   {
      __SA_TEMPLATE_v1 params =
      {
#if __little_endian__
         /* ICNT0            = */ icnt0,
         /* ICNT1            = */ icnt1,
         /* ICNT2            = */ icnt2,
         /* ICNT3            = */ icnt3,
         /* ICNT4            = */ icnt4,
         /* ICNT5            = */ icnt5,
         /* DECDIM1_WIDTH    = */ 0,
         /* DECDIM2_WIDTH    = */ 0,
         /* DIM1             = */ dim1,
         /* DIM2             = */ dim2,
         /* DIM3             = */ dim3,
         /* DIM4             = */ dim4,
         /* DIM5             = */ dim5,
         /* DECDIM3_WIDTH    = */ 0,
         /*** Flags ***/
         /* _reserved2       = */ 0,
         /* VECLEN           = */ SA_veclen_flag<nelem>::val,
         /* _reserved3       = */ 0,
         /* INV_DD3          = */ __SA_INV_DD_OFF,
         /* INV_DD1          = */ __SA_INV_DD_OFF,
         /* INV_DD2          = */ __SA_INV_DD_OFF,
         /* DIMFMT           = */ __SA_DIMFMT_6D,
         /* _reserved4       = */ 0,
         /* _reserved5       = */ 0,
         /* DECDIM3          = */ __SA_DECDIM_DIM0,
         /* DECDIM3SD        = */ __SA_DECDIMSD_DIM0,
         /* DECDIM1          = */ __SA_DECDIM_DIM0,
         /* DECDIM1SD        = */ __SA_DECDIMSD_DIM0,
         /* DECDIM2          = */ __SA_DECDIM_DIM0,
         /* DECDIM2SD        = */ __SA_DECDIMSD_DIM0,
         /* _reserved        = */ 0
#else
         /* Invert of 64 bit boundaries */
         /* ICNT1            = */ icnt1,
         /* ICNT0            = */ icnt0,

         /* ICNT3            = */ icnt3,
         /* ICNT2            = */ icnt2,

         /* ICNT5            = */ icnt5,
         /* ICNT4            = */ icnt4,

         /* DECDIM2_WIDTH    = */ 0,
         /* DECDIM1_WIDTH    = */ 0,

         /* DIM2             = */ dim2,
         /* DIM1             = */ dim1,

         /* DIM4             = */ dim4,
         /* DIM3             = */ dim3,

         /* DECDIM3_WIDTH    = */ 0,
         /* DIM5             = */ dim5,

         /*** Flags ***/
         /* _reserved        = */ 0
         /* DECDIM2SD        = */ __SA_DECDIMSD_DIM0,
         /* DECDIM2          = */ __SA_DECDIM_DIM0,
         /* DECDIM1SD        = */ __SA_DECDIMSD_DIM0,
         /* DECDIM1          = */ __SA_DECDIM_DIM0,
         /* DECDIM3SD        = */ __SA_DECDIMSD_DIM0,
         /* DECDIM3          = */ __SA_DECDIM_DIM0,
         /* _reserved5       = */ 0,
         /* _reserved4       = */ 0,
         /* DIMFMT           = */ __SA_DIMFMT_6D,
         /* INV_DD2          = */ __SA_INV_DD_OFF,
         /* INV_DD1          = */ __SA_INV_DD_OFF,
         /* INV_DD3          = */ __SA_INV_DD_OFF,
         /* _reserved3       = */ 0,
         /* VECLEN           = */ SA_veclen_flag<nelem>::val,
         /* _reserved2       = */ 0,
#endif
      };
      return params;
   }
};

template <typename type, int nelem, typename transpose>
struct SA_init;

template <typename type, int nelem>
struct SA_init<type, nelem, TRANSPOSE_OFF> :
   public SA_init_base<VCOP_SIMD_WIDTH>
{
   static inline __SA_TEMPLATE_v1 apply(uint32_t icnt0,
                                int32_t  dim1 = 0, uint32_t icnt1 = 1,
                                int32_t  dim2 = 0, uint32_t icnt2 = 1,
                                int32_t  dim3 = 0, uint32_t icnt3 = 1,
                                int32_t  dim4 = 0, uint32_t icnt4 = 1,
                                int32_t  dim5 = 0, uint32_t icnt5 = 1)
   {
      __SA_TEMPLATE_v1 SA_Template = SA_init_base<nelem>::configure_SA(icnt0,
                                              dim1, icnt1, dim2, icnt2,
                                              dim3, icnt3, dim4, icnt4,
                                              dim5, icnt5);

      #ifdef VVM_DEBUG
      SA_dump(SA_Template);
      #endif

      return SA_Template;
   }
}; // SA_init<type, nelem, false>

template <typename type, int nelem>
struct SA_init<type, nelem, TRANSPOSE_ON> :
   public SA_init_base<nelem>
{
   static inline __SA_TEMPLATE_v1 apply(uint32_t icnt0,
                                int32_t  dim1 = 0, uint32_t icnt1 = 1,
                                int32_t  dim2 = 0, uint32_t icnt2 = 1,
                                int32_t  dim3 = 0, uint32_t icnt3 = 1,
                                int32_t  dim4 = 0, uint32_t icnt4 = 1,
                                int32_t  dim5 = 0, uint32_t icnt5 = 1)
   {
      // initialize local dim/icnt vectors from passed-in values
      int32_t dim[6];
      uint32_t icnt[6];

      dim[0] = 1;
      icnt[0] = icnt0;
      dim[1] = dim1;
      icnt[1] = icnt1;
      dim[2] = dim2;
      icnt[2] = icnt2;
      dim[3] = dim3;
      icnt[3] = icnt3;
      dim[4] = dim4;
      icnt[4] = icnt4;
      dim[5] = dim5;
      icnt[5] = icnt5;

      // insert vector store dim/icnt at [0]
      shift_dims(0, dim, icnt);
      dim[0] = 1;
      icnt[0] = VCOP_SIMD_WIDTH;

      // find column loop(s) and multiply dim by SIMD width
      const int ROWSZ = (VCOP_SIMD_WIDTH+1) * 4 / sizeof(type);
      for (int i = 1; i < 5; ++i)
      {
         if (abs(dim[i]) < ROWSZ)
            dim[i] *= VCOP_SIMD_WIDTH;
      }

      __SA_TEMPLATE_v1 SA_Template =
          SA_init_base<VCOP_SIMD_WIDTH>::configure_SA(icnt[0],
                                              dim[1], icnt[1], dim[2], icnt[2],
                                              dim[3], icnt[3], dim[4], icnt[4],
                                              dim[5], icnt[5]);

      #ifdef VVM_DEBUG
      SA_dump(SA_Template);
      #endif

      return SA_Template;
   }
}; // SA_init<type, nelem, true>

/******************************************************************************
* Stags - control stream-based addressing
*    Each memory-referencing operation has an "Stag" (Stream Tag) that
*    specifies:
*      - whether the reference should use Streaming Engine (SE), Streaming
*        address generator (SA), or neither (plain indirect)
*      - which SA/SE
*      - whether to advance or not
******************************************************************************/
struct nosa { typedef nosa noadv; };
struct adv;
struct noadv;

/*-----------------------------------------------------------------------------
* SE tags - specify Streaming Engine addressing
*----------------------------------------------------------------------------*/
template <int myid, typename myadv=noadv> struct se;

typedef se<0, noadv> se0;
typedef se<0, adv>   se0adv;
typedef se<1, noadv> se1;
typedef se<1, adv>   se1adv;

/*-----------------------------------------------------------------------------
* se_ref
*    generate low-level SE reference intrinsic with parameterized type,
*    id, and adv flag
*----------------------------------------------------------------------------*/
template<typename type, typename Stag> struct se_ref;

#define SE_REF_SPECIALIZATION(type) \
   template<int id> struct se_ref<type, se<id, noadv> > \
   { \
      static type ref() \
         { return __se_ac_##type(id, 0); }  \
   }; \
   template<int id> struct se_ref<type, se<id, adv> > \
   { \
      static type ref() \
         { return (type)__se_ac_##type(id, 1); }\
   };

// specialize se_ref for all types used by the translator
// (currently only one type)
SE_REF_SPECIALIZATION(int16);

#undef SE_REF_SPECIALIZATION

/*-----------------------------------------------------------------------------
* SA tags - specify Streaming Address Generator addressing
*----------------------------------------------------------------------------*/
template <int myid, typename myadv=noadv> struct sa
{
   static const int id = myid;
   typedef myadv advflag;
   // given Tag = sa<id, advflag>, then Tag::noadv is the same SA but w/o adv
   typedef sa<myid, noadv> noadv;
};

typedef sa<0, noadv> sa0;
typedef sa<0, adv>   sa0adv;
typedef sa<1, noadv> sa1;
typedef sa<1, adv>   sa1adv;
typedef sa<2, noadv> sa2;
typedef sa<2, adv>   sa2adv;
typedef sa<3, noadv> sa3;
typedef sa<3, adv>   sa3adv;

/*-----------------------------------------------------------------------------
* sa_ref
*    generate low-level SA reference intrinsic with parameterized type,
*    id, and adv flag
*----------------------------------------------------------------------------*/
template<typename type, typename Stag> struct sa_ref;

#define SA_REF_SPECIALIZATION(ttype) \
   template<int id> struct sa_ref<ttype, sa<id, noadv> > \
   { \
      static ttype* ref(void*p) \
         { return (ttype*)__sa(id, sizeof(ttype)/__numelemof(ttype), p); }  \
   }; \
   template<int id> struct sa_ref<ttype, sa<id, adv> > \
   { \
      static ttype* ref(void*p) \
         { return (ttype*)__sa_adv(id, sizeof(ttype)/__numelemof(ttype), p); }\
   };

// specialize sa_ref for all types used by the translator
SA_REF_SPECIALIZATION(int8_t)
SA_REF_SPECIALIZATION(__char2)
SA_REF_SPECIALIZATION(__char4)
SA_REF_SPECIALIZATION(__char8)
SA_REF_SPECIALIZATION(__char16)
SA_REF_SPECIALIZATION(__char32)
SA_REF_SPECIALIZATION(__char64)

SA_REF_SPECIALIZATION(uint8_t)
SA_REF_SPECIALIZATION(__uchar2)
SA_REF_SPECIALIZATION(__uchar4)
SA_REF_SPECIALIZATION(__uchar8)
SA_REF_SPECIALIZATION(__uchar16)
SA_REF_SPECIALIZATION(__uchar32)
SA_REF_SPECIALIZATION(__uchar64)

SA_REF_SPECIALIZATION(int16_t)
SA_REF_SPECIALIZATION(__short2)
SA_REF_SPECIALIZATION(__short4)
SA_REF_SPECIALIZATION(__short8)
SA_REF_SPECIALIZATION(__short16)
SA_REF_SPECIALIZATION(__short32)

SA_REF_SPECIALIZATION(uint16_t)
SA_REF_SPECIALIZATION(__ushort2)
SA_REF_SPECIALIZATION(__ushort4)
SA_REF_SPECIALIZATION(__ushort8)
SA_REF_SPECIALIZATION(__ushort16)
SA_REF_SPECIALIZATION(__ushort32)

SA_REF_SPECIALIZATION(int32_t)
SA_REF_SPECIALIZATION(__int2)
SA_REF_SPECIALIZATION(__int4)
SA_REF_SPECIALIZATION(__int8)
SA_REF_SPECIALIZATION(__int16)

SA_REF_SPECIALIZATION(uint32_t)
SA_REF_SPECIALIZATION(__uint2)
SA_REF_SPECIALIZATION(__uint4)
SA_REF_SPECIALIZATION(__uint8)
SA_REF_SPECIALIZATION(__uint16)

#undef SA_REF_SPECIALIZATION

/******************************************************************************
* SAptr - "smart pointer" dereferenced using either plain indirect or SA access
******************************************************************************/
/*-----------------------------------------------------------------------------
* Default version - uses regular indirection through pointer
*       SAptr<int, nosa> p(base);     // regular pointer, int* p = base
*       *p                            // indirect through p
*       p.addr()                      // just p itself
*----------------------------------------------------------------------------*/
template <typename type, typename Stag>
struct SAptr
{
   SAptr(void*p) : _ptr(p) {}
   type& operator*()
      { return *(type*)(_ptr); }
   type* addr()
      { return (type*)(_ptr); }

private:
   void* _ptr;
};

/*-----------------------------------------------------------------------------
* Specialization to deref using SA
*       SAptr<int, sa0adv> p(base);     // SA0-based pointer, with advance
*       *p                              // SA0ADV(int, base)
*       p.addr()                        // generated address
*----------------------------------------------------------------------------*/
template <typename type, int id, typename advflag>
struct SAptr<type, sa<id, advflag> >
{
   typedef sa<id, advflag> SAtag;
   SAptr(void*p) : _ptr(p) {}
   type& operator*()
      { return (type&)(*sa_ref<type, SAtag>::ref(_ptr)); }
   type* addr()
      { return (type*)(sa_ref<type, SAtag>::ref(_ptr)); }

private:
   void* _ptr;
};

/******************************************************************************
* SAmask - Abstraction for SAptr to generate vector predicate lane masks for
*          use in stores.
******************************************************************************/
/*-----------------------------------------------------------------------------
* Default version - Generates mask using MASKB/H/W/D instructions and the
*                   number of elements given by the caller.
*----------------------------------------------------------------------------*/
template <size_t lane_width_bytes, typename Stag>
struct SAmask { };

template <>
struct SAmask<1, nosa>
{
    static inline vpred get_mask(__uint nelem) { return __mask_char(nelem); }
};
template <>
struct SAmask<2, nosa>
{
    static inline vpred get_mask(__uint nelem) { return __mask_short(nelem); }
};
template <>
struct SAmask<4, nosa>
{
    static inline vpred get_mask(__uint nelem) { return __mask_int(nelem); }
};
template <>
struct SAmask<8, nosa>
{
    static inline vpred get_mask(__uint nelem) { return __mask_long(nelem); }
};

/*-----------------------------------------------------------------------------
* Specialization for SA-based masks
*   Accesses the special PSA0-PSA3 control registers to extract the masks
*   needed for stores. Does not use the 'nelem' argument, but keeps it to
*   conform to the SAmask API.
*----------------------------------------------------------------------------*/
template <size_t lane_width_bytes, int id, typename advflag>
struct SAmask<lane_width_bytes, sa<id, advflag> >
{
    static inline vpred get_mask(__uint nelem)
    {
        return __sa_vpred(id, lane_width_bytes);
    }
};

/******************************************************************************
* circ() - address computation using circular buffering
*    see vcop spec 3.5.9
******************************************************************************/
inline void* circ(void* base, uint32_t offset, int circ_bits)
{
   size_t mask = ((size_t)0x200 << circ_bits) - 1;
   size_t cbuf = (size_t)base & ~mask;
   return (void*)(cbuf | ((size_t)base + offset) & mask);
}

/******************************************************************************
* vperm_XXX - Vperm operations to reorder vector elements
*   DS<N> - downsample (every Nth element), also used for packing
*   US<N> - upsample (repeat elements)
******************************************************************************/
// vperm pattern to select every other 32-bit word
inline __int16 vperm_ds2_32(__int16 Vsrc)
{
    static const __uchar permstr[] =
      "\x00\x01\x02\x03\x08\x09\x0a\x0b\x10\x11\x12\x13\x18\x19\x1a\x1b"
      "\x20\x21\x22\x23\x28\x29\x2a\x2b\x30\x31\x32\x33\x38\x39\x3a\x3b"
      "\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40"
      "\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40";
    return __as_int16(__vperm_vvv(*(__uchar64*)permstr, __as_uchar64(Vsrc)));
}

// vperm pattern to select every 4th 16-bit word
inline __short32 vperm_ds4_16(__int16 Vsrc)
{
    static const __uchar permstr[] =
      "\x00\x01\x08\x09\x10\x11\x18\x19\x20\x21\x28\x29\x30\x31\x38\x39"
      "\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40"
      "\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40"
      "\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40";
    return __as_short32(__vperm_vvv(*(__uchar64*)permstr, __as_uchar64(Vsrc)));
}

// vperm pattern to select every 8th 8-bit byte
inline __char64 vperm_ds8_8(__int16 Vsrc)
{
    static const __uchar permstr[] =
      "\x00\x08\x10\x18\x20\x28\x30\x38\x40\x40\x40\x40\x40\x40\x40\x40"
      "\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40"
      "\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40"
      "\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40";
    return __as_char64(__vperm_vvv(*(__uchar64*)permstr, __as_uchar64(Vsrc)));
}

// vperm pattern to duplicate each 8-bit byte by 4x
inline __int16 vperm_us4_8(__int16 Vsrc)
{
    static const __uchar permstr[] =
      "\x00\x00\x00\x00\x01\x01\x01\x01\x02\x02\x02\x02\x03\x03\x03\x03"
      "\x04\x04\x04\x04\x05\x05\x05\x05\x06\x06\x06\x06\x07\x07\x07\x07"
      "\x08\x08\x08\x08\x09\x09\x09\x09\x0A\x0A\x0A\x0A\x0B\x0B\x0B\x0B"
      "\x0C\x0C\x0C\x0C\x0D\x0D\x0D\x0D\x0E\x0E\x0E\x0E\x0F\x0F\x0F\x0F";
    return __as_int16(__vperm_vvv(*(__uchar64*)permstr, __as_uchar64(Vsrc)));
}

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

/******************************************************************************
* printp() - print a predicate value
******************************************************************************/
inline void printp(vpred v, const char* tag = NULL)
{
    uint64_t pval = _mvpb(v);
    if (tag) printf("%s:\n", tag);
    printf("0x%016lx\n", pval);
}

}; // namespace VCOP_VM

/******************************************************************************
* Include modules for load, store, and arithmetic ops
******************************************************************************/
#include <vcop/vcop_load.h>
#include <vcop/vcop_store.h>
#include <vcop/vcop_arith.h>
#include <vcop/vcop_lht.h>

#endif
