/*****************************************************************************/
/* VCOP_LOAD.H                                                               */
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
/*    VCOP Virtual Machine - Load operations                                 */
/*****************************************************************************/
namespace VCOP_VM
{

/******************************************************************************
* Load operation ISA abstractions
*   ISA abstrations provide an interface that allows the client to express
*   load operations generically. The abstraction handles unpacking (type
*   promotion) and selects the proper instruction. 
******************************************************************************/
/*-----------------------------------------------------------------------------
* load_unpack
*    Basic load operation to load __int16 vector from memory, unpacking if
*    needed.  Ptr is either a regular or "smart" SAptr pointer to a 16-element 
*    vector.
*----------------------------------------------------------------------------*/
template <typename Ptr> struct load_unpack
{
   static inline __int16 load(Ptr p)
      { return __as_int16(__vload_unpack_int(p.addr())); } 
};

template <typename Stag> struct load_unpack<SAptr<__int16, Stag> >
{
   typedef SAptr<__int16, Stag> Ptr; 
   static inline __int16 load(Ptr p)
      { return __as_int16(*p); } 
};

template <typename Stag> struct load_unpack<SAptr<__uint16, Stag> >
{
   typedef SAptr<__uint16, Stag> Ptr; 
   static inline __int16 load(Ptr p)
      { return __as_int16(*p); } 
};

/*-----------------------------------------------------------------------------
* extend_to_int()
*    generic overload for in-place sign/zero extend instrinsics 
*----------------------------------------------------------------------------*/
inline __int16 extend_to_int(__short32 src)
   { return __low_short_to_int(src); } 
inline __int16 extend_to_int(__ushort32 src)
   { return __as_int16(__low_ushort_to_uint(src)); } 

/*-----------------------------------------------------------------------------
* unpack_to_int()
*    generic overload for expanding sign/zero extend ("unpacking") instrinsics 
*----------------------------------------------------------------------------*/
inline __int16 unpack_to_int(__char16 src)
   { return __convert_int16(src); } 
inline __int16 unpack_to_int(__uchar16 src)
   { return __as_int16(__convert_uint16(src)); } 

/******************************************************************************
* vcop_load
*   This class provides C7x code sequences for each combination of data
*   type and distribution mode, using both normal addressing and the
*   Streaming Engine.  Each specialization specifies a translation sequence
*   and SE setup for one combination. The API is:
*
*   vcop_load<type, Stag, dist>::load(__vector& Vdst, void* ptr)
*        Load vector 'Vdst' from address 'ptr'
*        Stag specifies either SA or normal indirect addressing
*
*   vcop_load<type, Stag, dist>::SE_load(__vector& Vdst)
*        Load vector 'Vdst' using streaming engine
*        Stag specifies SE-based addressing
*
*   The class has specializations for ecah type/dist combination which
*   implement the distribution mode.
******************************************************************************/
template<typename memtype, 
         class    dist, 
         typename Stag=nosa,
         int      simd=VCOP_SIMD_WIDTH> 
struct vcop_load;

class npt;
class onept;
class circ2;
class ds2;
class us2;
class custom;
class deinterleave;
class expand;
class nbits;
class transpose;

/*-----------------------------------------------------------------------------
* npt
*----------------------------------------------------------------------------*/
template <typename type, typename Stag, int simd>
struct vcop_load<type, npt, Stag, simd> : public SE_defaults
{
   typedef typename vector<type, 16>::type memtype;   // [u]<type>16

   static void load(__int16& Vdst, void* p)
   {
      typedef SAptr<memtype, Stag> Ptr; 
      Vdst = load_unpack<Ptr>::load(Ptr(p)); 
   }

   static const __SE_ELETYPE SE_element_type = SE_element_type_flag<type>::val;
   static const __SE_PROMOTE SE_promote      = SE_promote_flag<type,int32_t>::val; 
   static const __SE_VECLEN SE_veclen       = SE_veclen_flag<simd>::val; 

   static void SE_load(__int16& Vdst)
   {
      Vdst = se_ref<__int16, Stag>::ref(); 
   }
};

/*-----------------------------------------------------------------------------
* transpose
*----------------------------------------------------------------------------*/
template <typename type, typename Stag, int simd>
struct transpose_base : public SE_defaults
{
   typedef typename vector<type, 16>::type memtype;   // [u]<type>16

   static const __SE_ELETYPE SE_element_type = SE_element_type_flag<type>::val;
   static const __SE_PROMOTE SE_promote      = SE_promote_flag<type,int32_t>::val; 
   static const __SE_VECLEN SE_veclen       = SE_veclen_flag<simd>::val; 

   static void SE_load(__int16& Vdst)
   {
      Vdst = se_ref<__int16, Stag>::ref(); 
   }
};

template <typename Stag, int simd>
struct vcop_load<int32_t, transpose, Stag, simd> :
   public transpose_base<int32_t, Stag, simd>
{
   static const __SE_TRANSPOSE SE_transpose    = __SE_TRANSPOSE_32BIT;
};

template <typename Stag, int simd>
struct vcop_load<uint32_t, transpose, Stag, simd> :
   public transpose_base<uint32_t, Stag, simd>
{
   static const __SE_TRANSPOSE SE_transpose    = __SE_TRANSPOSE_32BIT;
};

template <typename Stag, int simd>
struct vcop_load<int16_t, transpose, Stag, simd> :
   public transpose_base<int16_t, Stag, simd>
{
   static const __SE_DECIM SE_decimate     = __SE_DECIM_2;
   static const __SE_TRANSPOSE SE_transpose    = __SE_TRANSPOSE_16BIT;
};

template <typename Stag, int simd>
struct vcop_load<uint16_t, transpose, Stag, simd> :
   public transpose_base<uint16_t, Stag, simd>
{
   static const __SE_DECIM SE_decimate     = __SE_DECIM_2;
   static const __SE_TRANSPOSE SE_transpose    = __SE_TRANSPOSE_16BIT;
};

template <typename Stag, int simd>
struct vcop_load<int8_t, transpose, Stag, simd> :
   public transpose_base<int8_t, Stag, simd>
{
   static const __SE_DECIM SE_decimate     = __SE_DECIM_4;
   static const __SE_TRANSPOSE SE_transpose    = __SE_TRANSPOSE_8BIT;
};

template <typename Stag, int simd>
struct vcop_load<uint8_t, transpose, Stag, simd> :
   public transpose_base<uint8_t, Stag, simd>
{
   static const __SE_DECIM SE_decimate     = __SE_DECIM_4;
   static const __SE_TRANSPOSE SE_transpose    = __SE_TRANSPOSE_8BIT;
};


/*-----------------------------------------------------------------------------
* onept
*----------------------------------------------------------------------------*/
template <typename type, typename Stag, int simd> 
struct vcop_load<type, onept, Stag, simd> : public SE_defaults
{
   // scalar load, then duplicate
   static void load(__int16& Vdst, void* p)
   {
      typedef SAptr<type, Stag> Ptr; 
      int32_t val = *Ptr(p); 
      Vdst = (__int16)(val); 
   }

   // SE setup: use Nx element duplication, N = simd
   static const __SE_ELEDUP SE_element_dup  = SE_element_dup_flag<simd>::val;
   static const __SE_ELETYPE SE_element_type = SE_element_type_flag<type>::val;
   static const __SE_PROMOTE SE_promote      = SE_promote_flag<type,int32_t>::val; 
   static const __SE_VECLEN SE_veclen       = SE_veclen_flag<simd>::val; 

   static void SE_load(__int16& Vdst)
   {
      Vdst = se_ref<__int16, Stag>::ref(); 
   }
};

/*-----------------------------------------------------------------------------
* circ2
*----------------------------------------------------------------------------*/
template <typename type, typename Stag, int simd> 
struct vcop_load<type, circ2, Stag, simd> : public SE_defaults
{
   typedef typename vector<type, 16>::type memtype;   // [u]<type>16

   static void load(__int16& Vdst, void* p)
   {
      typedef SAptr<memtype, Stag> Ptr; 
      Vdst = load_unpack<Ptr>::load(Ptr(p)); 
      __int2 vals = Vdst.s01;
      Vdst = __as_int16(__vdupd_dv(__as_longlong(vals)));
   }

   // SE setup: use 2x group duplication
   static const __SE_ELETYPE SE_element_type = SE_element_type_flag<type>::val;
   static const __SE_PROMOTE SE_promote      = SE_promote_flag<type,int32_t>::val; 
   static const __SE_GRPDUP SE_group_dup    = __SE_GRPDUP_ON;
   static const __SE_VECLEN SE_veclen       = SE_veclen_flag<2>::val ;

   static void SE_load(__int16& Vdst)
   {
      Vdst = se_ref<__int16, Stag>::ref(); 
   }
};

/*-----------------------------------------------------------------------------
* ds2
*    8-and 16-bit only (VCOP does not support ds2 for 32-bit)
*----------------------------------------------------------------------------*/
// shared SE setup for all types: use 2x decimation
template <typename type, typename Stag, int simd> 
struct load_ds2_base : public SE_defaults
{
   static const __SE_ELETYPE SE_element_type = SE_element_type_flag<type>::val;
   static const __SE_PROMOTE SE_promote      = SE_promote_flag<type,int32_t>::val; 
   static const __SE_DECIM SE_decimate     = __SE_DECIM_2;
   static const __SE_VECLEN SE_veclen       = SE_veclen_flag<simd>::val;
   static void SE_load(__int16& Vdst)
   {
      Vdst = se_ref<__int16, Stag>::ref(); 
   }
};

// ds2, 8-bit
template <typename type, typename Stag, int simd> struct load_ds2_char : 
   public load_ds2_base<type, Stag, simd> 
{
   typedef typename vector<type, 32>::type memtype;         // [u]char32
   typedef typename traits<type>::short_type short_type;    // [u]short
   typedef typename vector<short_type, 32>::type vectype;   // [u]short32

   static void load(__int16& Vdst, void* p)
   {
      typedef SAptr<memtype, Stag> Ptr; 
      // VLDBUNPKH:    ... sD sC sB sA
      vectype  vals = __vload_unpack_short(Ptr(p).addr()); 
      // VUNPKLH:      ... ss sC ss sA
      Vdst = extend_to_int(vals); 
   }
};

template<typename Stag, int simd> 
struct vcop_load<int8_t, ds2, Stag, simd> : 
   public load_ds2_char<int8_t, Stag, simd> {}; 
template<typename Stag, int simd> 
struct vcop_load<uint8_t, ds2, Stag, simd> : 
   public load_ds2_char<uint8_t, Stag, simd> {}; 

// ds2, 16-bit
template <typename type, typename Stag, int simd> struct load_ds2_short : 
   public load_ds2_base<type, Stag, simd> 
{
   typedef typename vector<type, 32>::type memtype;       // [u]short32   
   typedef typename vector<type, 32>::type vectype;       // [u]short32

   static void load(__int16& Vdst, void* p)
   {
      typedef SAptr<memtype, Stag> Ptr; 
      // VLDH:     ... DD CC BB AA
      vectype  vals = *Ptr(p);
      // VUNPKLH:  ... ss CC ss AA
      Vdst = extend_to_int(vals); 
   }
};

template<typename Stag, int simd> 
struct vcop_load<int16_t, ds2, Stag, simd> : 
   public load_ds2_short<int16_t, Stag, simd> {}; 
template<typename Stag, int simd> 
struct vcop_load<uint16_t, ds2, Stag, simd> : 
   public load_ds2_short<uint16_t, Stag, simd> {}; 

/*-----------------------------------------------------------------------------
* us2
*----------------------------------------------------------------------------*/
// shared SE setup for all types: use 2x element duplication
template <typename type, typename Stag, int simd>
struct load_us2_base : public SE_defaults
{
   static const __SE_ELETYPE SE_element_type = SE_element_type_flag<type>::val;
   static const __SE_PROMOTE SE_promote      = SE_promote_flag<type,int32_t>::val; 
   static const __SE_VECLEN SE_veclen       = SE_veclen_flag<simd>::val ;
   static const __SE_ELEDUP SE_element_dup  = __SE_ELEDUP_2X;

   static void SE_load(__int16& Vdst)
   {
      Vdst = se_ref<__int16, Stag>::ref(); 
   }
};

// us2, 8-bit
template <typename type, typename Stag, int simd> struct load_us2_char : 
   public load_us2_base<type, Stag, simd>
{
   typedef typename vector<type,32>::type memtype;    // [u]char32
   typedef typename vector<type,64>::type duptype;    // [u]char64

   static void load(__int16& Vdst, void* p)
   {
      typedef SAptr<memtype, Stag> Ptr; 
      // 2x duplication : ... DDCCBBAA
      duptype vals = __vload_dup(Ptr(p).addr()); 
      // unpack & ext   : ... sssBsssB sssAsssA
      Vdst = unpack_to_int(vals.v16[0]); 
   }
}; 

template<typename Stag, int simd> struct vcop_load<int8_t, us2, Stag, simd> :
   public load_us2_char<int8_t, Stag, simd> {}; 
template<typename Stag, int simd> struct vcop_load<uint8_t, us2, Stag, simd> :
   public load_us2_char<uint8_t, Stag, simd> {}; 

// us2, 16-bit
template <typename type, typename Stag, int simd> struct load_us2_short : 
   public load_us2_base<type, Stag, simd>
{
   typedef typename vector<type,simd>::type memtype;    // [u]short[N]
   typedef typename vector<type,32>::type vectype;   // [u]short32

   static void load(__int16& Vdst, void* p)
   {
      typedef SAptr<memtype, Stag> Ptr; 
      // 4x duplication: ... BB BB BB BB AA AA AA AA 
      vectype vals = __vload_dup(Ptr(p).addr());
      // sign/0 ext    : ... ss BB ss BB ss AA ss AA
      Vdst = __as_int16(__unpack_low(vals));
   }
};

template<typename Stag, int simd> struct vcop_load<int16_t, us2, Stag, simd> :
   public load_us2_short<int16_t, Stag, simd> {}; 
template<typename Stag, int simd> struct vcop_load<uint16_t, us2, Stag, simd> : 
   public load_us2_short<uint16_t, Stag, simd> {}; 

// us2, 32-bit
template <typename type, typename Stag, int simd> struct load_us2_int : 
   public load_us2_base<type, Stag, simd>
{
   typedef typename vector<type,simd>::type memtype;    // [u]int[N]
   typedef typename vector<type,16>::type vectype;   // [u]int16

   static void load(__int16& Vdst, void* ptr)
   {
      typedef SAptr<memtype, Stag> Ptr; 
      // 2x duplication: AA AA AA AA BB BB BB BB ...
      vectype vals = __vload_dup(Ptr(ptr).addr());
      Vdst = __as_int16(vals); 
   }
};

template<typename Stag, int simd> struct vcop_load<int32_t, us2, Stag, simd> :
   public load_us2_int<int32_t, Stag, simd> {}; 
template<typename Stag, int simd> struct vcop_load<uint32_t, us2, Stag, simd> :
   public load_us2_int<uint32_t, Stag, simd> {}; 

/*-----------------------------------------------------------------------------
* custom
*   The permute vector is computed by the init() function, stored
*   in the tvals block, and passed to this load function.
*----------------------------------------------------------------------------*/
template <typename type, typename Stag, int simd> 
struct vcop_load<type, custom, Stag, simd> : public SE_defaults
{
   static void load(__int16& Vdst, void* p, __uchar64 permvec)
   {
      vcop_load<type, npt, Stag, simd>::load(Vdst, p); 
      Vdst = __as_int16(__vperm_vvv(permvec, __as_uchar64(Vdst)));
   }

   static const __SE_ELETYPE SE_element_type = SE_element_type_flag<type>::val;
   static const __SE_PROMOTE SE_promote      = SE_promote_flag<type,int32_t>::val; 
   static const __SE_VECLEN SE_veclen       = SE_veclen_flag<simd>::val;

   static void SE_load(__int16& Vdst, __uchar64 permvec)
   {
      __int16 vals = se_ref<__int16, Stag>::ref(); 
      Vdst = __as_int16(__vperm_vvv(permvec, __as_uchar64(vals)));
   }
};

/*-----------------------------------------------------------------------------
* deinterleave
*    8- and 16-bit only (VCOP does not support 32-bit) 
*----------------------------------------------------------------------------*/
template <typename type, typename Stag, int simd>
struct vcop_load<type, deinterleave, Stag, simd> : public SE_defaults
{
   typedef typename vector<type, 32>::type memtype;      // [u]<type>32

   static void load(__int16& Vdst0, __int16& Vdst1, void* p)
   {
      // load evens from p, without advance
      typedef SAptr<memtype, typename Stag::noadv> Ptr_e; 
      Vdst0 = __as_int16(__vload_deinterleave_int(Ptr_e(p).addr())); 

      // load odds from p+1, and advance if specified
      typedef SAptr<memtype, Stag> Ptr_o; 
      void* p1 = (void*)((char*)p + sizeof(type));
      Vdst1 = __as_int16(__vload_deinterleave_int(Ptr_o(p1).addr()));
   }

   //-------------------------------------------------------------------------
   // SE-based interleave mode uses SE decimation and two SE reads.
   // VCC defines the stream as 2 vectors worth of consectutive elements.
   // VCC inserts a loop level at level 1 that iterates twice (icnt1 = 2).
   // First iteration reads even elements, via decimation.
   // Then, advance by one (dim1 = 1); second iteration of loop1 reads odds.
   //-------------------------------------------------------------------------
   static const __SE_ELETYPE SE_element_type = SE_element_type_flag<type>::val;
   static const __SE_PROMOTE SE_promote      = SE_promote_flag<type,int32_t>::val; 
   static const __SE_DECIM SE_decimate     = __SE_DECIM_2;
   static const __SE_VECLEN SE_veclen       = SE_veclen_flag<simd>::val;

   static void SE_load(__int16& Vdst0, __int16& Vdst1)
   {
      Vdst0 = se_ref<__int16, Stag>::ref(); 
      Vdst1 = se_ref<__int16, Stag>::ref(); 
   }
}; 

/*-----------------------------------------------------------------------------
* expand
*    note: Stag must be nosa (SE/SA not supported for expand mode)
*----------------------------------------------------------------------------*/
template <typename type, int simd>
struct vcop_load<type, expand, nosa, simd> : public SE_defaults
{
   typedef typename vector<uint32_t, 16>::type   uregtype;
   typedef typename vector<uint32_t, simd>::type predtype;

   // note: ptr passed by reference and updated
   static void load(__int16& Vdst, void*& ptr, __int16 Vpred)
   {
      // compare predicate to 0
      uregtype uVpred = as_type(uregtype, Vpred);
      predtype pvals_ui = subvec<uregtype,predtype>::apply(uVpred);
      vpred Vpredw = __cmp_gt_pred(pvals_ui, (predtype)(0)); 

      // load and unpack to __int16
      __int16 vals;
      vcop_load<type, npt, nosa, simd>::load(vals, ptr); 

      // select and scatter 'true' elements
      Vdst = __as_int16(__scatter_set_bits(Vpredw, __as_char64(vals))); 

      // count 'true' bytes 
      // (there are 4 predicate bits per element so downscale if needed)
      static const int scale = sizeof(type) == 1 ? 2 :
                               sizeof(type) == 2 ? 1 : 0; 
      __uint nbytes = __popcount_char(Vpredw) >> scale;

      // update pointer 
      ptr = (void*)((char*)ptr + nbytes); 
   }
};

/*-----------------------------------------------------------------------------
* nbits
*    Note: SE addressing not supported
*----------------------------------------------------------------------------*/
// sign-extending
template <typename type, typename Stag, int simd> 
struct load_nbits_signed : public SE_defaults
{
   static void load(__int16& Vdst, void* p)
   {
      typedef SAptr<uint8_t, Stag> Ptr; 
      vpred pred = _mvrp(*Ptr(p));
      // expand each bit to 8 bits
      __char64 bytevals = __vpxpnd_pv(pred);
      // duplicate each byte 4x 
      Vdst = vperm_us4_8(__as_int16(bytevals)); 
   }
};

// zero-extending 
template <typename type, typename Stag, int simd>
struct load_nbits_unsigned : public SE_defaults
{
   // TODO: does this work for simd=16?
   static void load(__int16& Vdst, void* p)
   {
      typedef SAptr<uint8_t, Stag> Ptr; 
      vpred pred = _mvrp(*Ptr(p));
      // expand each bit to 8 bits
      __char64 bytevals = __expand(pred);
      // duplicate each byte 4x 
      Vdst = vperm_us4_8(__as_int16(bytevals)); 
      Vdst = (Vdst & ((__int16)1));
   }
};

// data type of load determines signed or unsigned form
template<typename Stag, int simd>
struct vcop_load<int16_t, nbits, Stag, simd> : 
   public load_nbits_signed<int16_t, Stag, simd> {}; 

template<typename Stag, int simd>
struct vcop_load<uint16_t, nbits, Stag, simd> : 
   public load_nbits_unsigned<uint16_t, Stag, simd> {};

template<typename Stag, int simd> 
struct vcop_load<int8_t, nbits, Stag, simd> : 
   public load_nbits_signed<int8_t, Stag, simd> {}; 

template<typename Stag, int simd> 
struct vcop_load<uint8_t, nbits, Stag, simd> : 
   public load_nbits_unsigned<uint8_t, Stag, simd> {};

template<typename Stag, int simd>
struct vcop_load<int32_t, nbits, Stag, simd> : 
   public load_nbits_signed<int32_t, Stag, simd> {}; 

template<typename Stag, int simd>
struct vcop_load<uint32_t, nbits, Stag, simd> : 
   public load_nbits_unsigned<uint32_t, Stag, simd> {};

/******************************************************************************
* Helper functions for 'custom' load distribution mode.
* Convert 8-element word-wise permute vector into 64-element byte-wise
* permute vector.
*     | 0 | 1 | 5 | ... --> | 0 1 2 3 | 4 5 6 7 | 20 21 22 23 | ...
* This is invoked in init() function for kernel setup. The perm vector
* is stored in the tvals structures and is passed to the 
* vcop_load<custom>::load() function.
******************************************************************************/
inline void perm_wtob(int idx, int pos, __uchar* pv); 

/*-----------------------------------------------------------------------------
* custom_dist_perm() - return a vperm vector given discrete index values
*----------------------------------------------------------------------------*/
inline __uchar64 custom_dist_perm(int i0, int i1, int i2, int i3,
                                  int i4, int i5, int i6, int i7)
{
   // TODO: optimize this for 7x
   __uchar pv[64];

   memset(pv, 0x40, 64);    // fill unused lanes with 0

   perm_wtob(0, i0, pv); 
   perm_wtob(1, i1, pv); 
   perm_wtob(2, i2, pv); 
   perm_wtob(3, i3, pv); 
   perm_wtob(4, i4, pv); 
   perm_wtob(5, i5, pv); 
   perm_wtob(6, i6, pv); 
   perm_wtob(7, i7, pv); 

   __uchar64 perm_b = *(__uchar64*)pv;
   return perm_b;
}

/*-----------------------------------------------------------------------------
* custom_dist_perm() - return a vperm vector given a vector of index values
* TODO: provide overloads for additional index vector types 
*       (type is unspecified in VCOP Kernel-C)
*----------------------------------------------------------------------------*/
inline __uchar64 custom_dist_perm(int vec[])
{ 
   // TODO: this can be optimized for 7x using vector operations
   return custom_dist_perm(vec[0], vec[1], vec[2], vec[3], 
                           vec[4], vec[5], vec[6], vec[7]);
}

/*-----------------------------------------------------------------------------
* perm_wtob() - helper function for custom_dist_perm()
*----------------------------------------------------------------------------*/
inline void perm_wtob(int idx, int pos, __uchar* pv)
{
   pv[(idx*4)  ] = (pos*4); 
   pv[(idx*4)+1] = (pos*4)+1;
   pv[(idx*4)+2] = (pos*4)+2;
   pv[(idx*4)+3] = (pos*4)+3;
}

}  // namespace VCOP_VM
