/*****************************************************************************/
/* VCOP_ARITH.H                                                              */
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
/*    Arithmetic operations for VCOP virtual machine.                        */
/*****************************************************************************/
namespace VCOP_VM
{
/******************************************************************************
* Arithmetic operations are implemented by template classes of the form:
*   op<type>
* Where op is the VCOP operation and type is the element type.
* 
* Currently only types int32_t and uint32_t are supported. In most cases the
* signed and unsigned forms are the same implementation, but some 
* operations (e.g. right shift, compare) have different specializations. 
*
* The operation itself is invoked via a method called apply(), which 
* takes as arguments source vectors and returns the result vector(s) by 
* reference. For example:
*     shift<int32_t>::apply(Vdst, Vsrc1, Vsrc2);     // bi-directional shift
* 
* VCOP operations that map directly to C operators are not implemented here. 
* The translator simply generates the appropriate C expression and the
* compiler chooses the appropriate instruction.
******************************************************************************/

/*-----------------------------------------------------------------------------
* addh
*----------------------------------------------------------------------------*/
template <typename elem_type> 
struct addh
{
   static inline void apply(__int16& Vdst, __int16 Vsrc1, __int16 Vsrc2)
   {
      __int16 Vsrc1d = Vsrc1 - 1;
      vpred p = __cmp_gt_pred((__int16)0, Vsrc2);
      Vdst = __select(p, Vsrc1d, Vsrc1); 
   }
};

/*-----------------------------------------------------------------------------
* addsub
*----------------------------------------------------------------------------*/
template <typename elem_type> 
struct addsub
{
   static inline void apply(__int16& Vdst1, __int16& Vdst2)
   {
      __int16 Vsrc1 = Vdst1;
      __int16 Vsrc2 = Vdst2;

      Vdst1 = Vsrc1 + Vsrc2;
      Vdst2 = Vsrc1 - Vsrc2;
   }
};

/*-----------------------------------------------------------------------------
* shift
*   (VCOP shift is bi-directional; that is either << or >> depending on
*   sign of RHS.)
*----------------------------------------------------------------------------*/
template <typename elem_type> struct shift;
template <> struct shift <int32_t>
{
   static inline void apply(__int16& Vdst, __int16 Vsrc1, __int16 Vsrc2)
   {
      Vdst = __as_int16(__shift_left_var(Vsrc1, Vsrc2)); 
   } 
};

template <> struct shift <uint32_t>
{
   // C7x bidirectional shift is signed only. An ugly sequence is needed
   // for unsigned. Could improve this translator knows RHS to be constant.
   // TODO: add shift-by-constant forms of unsigned shift
   // 
   static inline void apply(__int16& Vdst, __int16 Vsrc1, __int16 Vsrc2)
   {
      Vdst = __as_int16(__shift_left_var(__as_uint16(Vsrc1), Vsrc2));
   }
};

/*-----------------------------------------------------------------------------
* shift_or
*----------------------------------------------------------------------------*/
template <typename elem_type> 
struct shift_or
{
   static inline void apply(__int16& Vdst, __int16 Vsrc1, __int16 Vsrc2)
   {
      __int16 Vtmp;
      shift<elem_type>::apply(Vtmp, Vsrc1, Vsrc2);
      Vdst = Vdst | Vtmp;
   }
};

/*-----------------------------------------------------------------------------
* sort2
*----------------------------------------------------------------------------*/
template <typename elem_type> 
struct sort2
{
   typedef typename vector<elem_type,16>::type vtype;   // [u]int16
   static inline void apply(__int16& Vdst1, __int16& Vdst2)
   {
      vtype Vsrc1 = as_type(vtype, Vdst1);
      vtype Vsrc2 = as_type(vtype, Vdst2);
      Vdst1 = __as_int16(__min(Vsrc1, Vsrc2));
      Vdst2 = __as_int16(__max(Vsrc1, Vsrc2)); 
   } 
};

/*-----------------------------------------------------------------------------
* swap
*----------------------------------------------------------------------------*/
template <typename elem_type> 
struct swap
{
   static inline void apply(__int16& Vdst1, __int16& Vdst2, __int16 Vcond)
   {
      __int16 Vsrc1 = Vdst1;
      __int16 Vsrc2 = Vdst2;
      Vcond = Vcond & (__int16)1;
      vpred p = __cmp_eq_pred(Vcond, (__int16)0); 
      Vdst1 = __select(p, Vsrc1, Vsrc2);
      Vdst2 = __select(p, Vsrc2, Vsrc1); 
   } 
};

/*-----------------------------------------------------------------------------
* minsetf
*----------------------------------------------------------------------------*/
template <typename elem_type> 
struct minsetf
{
   typedef typename vector<elem_type,16>::type vtype;   // [u]int16
   static inline void apply(__int16& Vdst1, __int16& Vdst2, 
                            __int16  Vsrc1, __int16  Vsrc2)
   {
      vpred p;
      vtype V1 = as_type(vtype, Vsrc1);
      vtype V2 = as_type(vtype, Vsrc2);

      __min_index(V1, V2, p);    // V2 := min(V1,V2)
      Vdst1 = __as_int16(V2);
      Vdst2 = __select(p, (__int16)(1), (__int16)(0));
   }
};

/*-----------------------------------------------------------------------------
* maxsetf
*----------------------------------------------------------------------------*/
template <typename elem_type> 
struct maxsetf
{
   typedef typename vector<elem_type,16>::type vtype;   // [u]int16
   static inline void apply(__int16& Vdst1, __int16& Vdst2, 
                            __int16  Vsrc1, __int16  Vsrc2)
   {
      vpred p;
      vtype V1 = as_type(vtype, Vsrc1);
      vtype V2 = as_type(vtype, Vsrc2);

      __max_index(V1, V2, p);    // V2 := max(V1,V2)
      Vdst1 = __as_int16(V2);
      Vdst2 = __select(p, (__int16)(1), (__int16)(0));
   } 
};

/*-----------------------------------------------------------------------------
* cmpeq
*----------------------------------------------------------------------------*/
template <typename elem_type> 
struct cmpeq
{
   static inline void apply(__int16& Vdst, __int16 Vsrc1, __int16 Vsrc2)
   {
      // CMPEQ does not have an unsigned form; use signed form for both
      vpred p = __cmp_eq_pred(Vsrc1, Vsrc2); 
      Vdst = __select(p, (__int16)(1), (__int16)(0));
   }
};

/*-----------------------------------------------------------------------------
* cmpgt
*----------------------------------------------------------------------------*/
template <typename elem_type> 
struct cmpgt
{
   typedef typename vector<elem_type,16>::type vtype;   // [u]int16
   static inline void apply(__int16& Vdst, __int16 Vsrc1, __int16 Vsrc2)
   {
      vtype V1 = as_type(vtype, Vsrc1); 
      vtype V2 = as_type(vtype, Vsrc2); 
      vpred p = __cmp_gt_pred(V1, V2);
      Vdst = __select(p, (__int16)(1), (__int16)(0));
   } 
};

/*-----------------------------------------------------------------------------
* cmpge
*----------------------------------------------------------------------------*/
template <typename elem_type> 
struct cmpge
{
   typedef typename vector<elem_type,16>::type vtype;   // [u]int16
   static inline void apply(__int16& Vdst, __int16 Vsrc1, __int16 Vsrc2)
   {
      vtype V1 = as_type(vtype, Vsrc1); 
      vtype V2 = as_type(vtype, Vsrc2); 
      vpred p = __cmp_gt_pred(V2, V1);
      Vdst = __select(p, (__int16)(0), (__int16)(1));
   }
};

/*-----------------------------------------------------------------------------
* cmplt
*----------------------------------------------------------------------------*/
template <typename elem_type> 
struct cmplt
{
   typedef typename vector<elem_type,16>::type vtype;   // [u]int16
   static inline void apply(__int16& Vdst, __int16 Vsrc1, __int16 Vsrc2)
   {
      vtype V1 = as_type(vtype, Vsrc1); 
      vtype V2 = as_type(vtype, Vsrc2); 
      vpred p = __cmp_gt_pred(V2, V1);
      Vdst = __select(p, (__int16)(1), (__int16)(0));
   }
};

/*-----------------------------------------------------------------------------
* cmple
*----------------------------------------------------------------------------*/
template <typename elem_type> 
struct cmple
{
   typedef typename vector<elem_type,16>::type vtype;   // [u]int16
   static inline void apply(__int16& Vdst, __int16 Vsrc1, __int16 Vsrc2)
   {
      vtype V1 = as_type(vtype, Vsrc1); 
      vtype V2 = as_type(vtype, Vsrc2); 
      vpred p = __cmp_gt_pred(V1, V2);
      Vdst = __select(p, (__int16)(0), (__int16)(1));
   }
};

/*-----------------------------------------------------------------------------
* select
*----------------------------------------------------------------------------*/
template <typename elem_type> 
struct select
{
   static inline void apply(__int16& Vdst, __int16 Vcond, 
                            __int16 Vsrc2, __int16 Vsrc3)
   {
      vpred p = __cmp_eq_pred(Vcond, (__int16)0); 
      Vdst = __select(p, Vsrc3, Vsrc2); 
   }
};

/*-----------------------------------------------------------------------------
* bit_pack
*----------------------------------------------------------------------------*/
template <typename elem_type, int simd=VCOP_SIMD_WIDTH> 
struct bit_pack;

template <typename elem_type>
struct bit_pack<elem_type, 8>
{
   typedef typename vector<elem_type,16>::type vtype;   // [u]int16
   static inline void apply(__int16& Vdst, __int16 Vsrc1, __int16 Vsrc2)
   {
       // VCOP operation is bit[n] = src1[n] >= src2[n] ? 1 : 0
      vtype V1 = as_type(vtype, Vsrc1); 
      vtype V2 = as_type(vtype, Vsrc2); 
      vpred p = __cmp_ge_pred(V1, V2);
      Vdst = __as_int16(__vppackdup8w_pv(p));
   }
};

template <typename elem_type>
struct bit_pack<elem_type, 16>
{
   typedef typename vector<elem_type,16>::type vtype;   // [u]int16
   static inline void apply(__int16& Vdst, __int16 Vsrc1, __int16 Vsrc2)
   {
       // VCOP operation is bit[n] = src1[n] >= src2[n] ? 1 : 0
      vtype V1 = as_type(vtype, Vsrc1); 
      vtype V2 = as_type(vtype, Vsrc2); 
      vpred p = __cmp_ge_pred(V1, V2);
      Vdst = __as_int16(__vppackdup16w_pv(p));
   }
};

/*-----------------------------------------------------------------------------
* bit_unpack
*----------------------------------------------------------------------------*/
template <typename elem_type> 
struct bit_unpack
{
   static inline void apply(__int16& Vdst, __int16 Vsrc1, __int16 Vsrc2)
   {
      vpred pw = __expand_vpred((unsigned long)Vsrc1.s0, (__uchar)(2));
      Vdst = __select(pw, Vsrc2, (__int16)(0));
   }
};

/*-----------------------------------------------------------------------------
* round
*   This class is used for the standalone round() operation, as well as
*   rounding in combination with stores or multiplies.
*----------------------------------------------------------------------------*/
template <typename elem_type> 
struct round
{
   typedef typename vector<elem_type,16>::type vtype;   // [u]int16
   // vector of bit positions
   static inline void apply(__int16& Vdst, __int16 Vsrc1, __int16 Vsrc2)
   {
      vtype V1 = as_type(vtype, Vsrc1); 
      Vdst = __shift_right_round(V1, __as_uint16(Vsrc2)); 
   }
   // scalar bit position
   static inline void apply(__int16& Vdst, __int16 Vsrc1, int k)
   {
      vtype V1 = as_type(vtype, Vsrc1); 
      Vdst = __as_int16(__shift_right_round(V1, (__uint16)k));
   } 
};

/*-----------------------------------------------------------------------------
* truncate
*    There is no standalone truncate(). This is always part of a store or
*    multiply. Bit position is always a scalar.
*----------------------------------------------------------------------------*/
template <typename elem_type> 
struct truncate
{
   typedef typename vector<elem_type,16>::type vtype;   // [u]int16
   static inline void apply(__int16& Vdst, __int16 Vsrc1, int k)
   {
      vtype V1 = as_type(vtype, Vsrc1); 
      Vdst = __as_int16(V1 >> (elem_type)k); 
   } 
};

/*-----------------------------------------------------------------------------
* apply_sign
*----------------------------------------------------------------------------*/
template <typename elem_type> 
struct apply_sign
{
   static inline void apply(__int16& Vdst, __int16 Vsrc1, __int16 Vsrc2)
   {
      __int16 z = (__int16)0; 
      vpred p = __cmp_gt_pred(Vsrc1, z); 
      __int16 Vsrc2n = -Vsrc2;
      Vdst = __select(p, Vsrc2, Vsrc2n); 
   }
};

/*-----------------------------------------------------------------------------
* bit_count
*----------------------------------------------------------------------------*/
template <typename elem_type> 
struct bit_count
{
   static inline void apply(__int16& Vdst, __int16 Vsrc1)
   {
      Vdst = __popcount(Vsrc1); 
   }
};

/*-----------------------------------------------------------------------------
* bit_reverse
*----------------------------------------------------------------------------*/
template <typename elem_type> 
struct bit_reverse
{
   static inline void apply(__int16& Vdst, __int16 Vsrc1)
   {
      Vdst = __bit_reverse(Vsrc1); 
   }
};

/*-----------------------------------------------------------------------------
* bit_transpose
*----------------------------------------------------------------------------*/
template <typename elem_type> 
struct bit_transpose
{
   static inline void apply(__int16& Vdst, __int16 Vsrc1)
   {
      // unpack 8[8] into 32[8] with upper bits zeroed
      static const __uchar unpack_perm[] = 
         "\x00\x40\x40\x40\x01\x40\x40\x40\x02\x40\x40\x40\x03\x40\x40\x40"
         "\x04\x40\x40\x40\x05\x40\x40\x40\x06\x40\x40\x40\x07\x40\x40\x40"
         "\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40"
         "\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40";

      __int16 Vpack = __as_int16(__vdeal4b_vv(__as_char64(Vsrc1))); 
      Vpack = __as_int16(__vbittran8b_vv(__as_uchar64(Vpack)));   
      Vdst = __as_int16(__vperm_vvv(*(__uchar64*)unpack_perm, 
                                    __as_uchar64(Vpack))); 
   }
};

/*-----------------------------------------------------------------------------
* lmbd
*----------------------------------------------------------------------------*/
template <typename elem_type> 
struct lmbd
{
   static inline void apply(__int16& Vdst, __int16 Vsrc1, __int16 Vsrc2)
   {
      // 7x returns number of bits to the left of the first matching bit, so
      // subtract from 31 to get result
      __uint16 Vleft = __leftmost_bit_detect(__as_uint16(Vsrc1), 
                                             __as_uint16(Vsrc2)); 
      Vdst = (__int16)31 - __as_int16(Vleft);
   }
};

/*-----------------------------------------------------------------------------
* binlog
*----------------------------------------------------------------------------*/
template <typename elem_type> 
struct binlog
{
   static inline void apply(__int16& Vdst, __int16 Vsrc1)
   {
      Vdst = __as_int16(__vbinlogw_vv(__as_uint16(Vsrc1))); 
   }
   #if 0 // "naive" version, left in to illustrate operation
   static inline void apply(__int16& Vdst, __int16 Vsrc1)
   {
      __int16 Vlmbd = __as_int16(__leftmost_bit_detect_one(__as_uint16(Vsrc1))); 

      __int16  Vexp = (__int16)15 - Vlmbd;
      Vexp = __max(Vexp, (__int16)0);       // saturate to [0,15]
      Vexp = Vexp << (__int16)28;

      __int16 Vshift = Vlmbd - (__int16)3;
      Vshift = __min(Vshift, (__int16)11);  // saturate to [-3, 11]

      __int16 Vmant;
      shift<uint32_t>::apply(Vmant, Vsrc1, Vshift);   // 2-way shift (<< or >>)
      Vmant = Vmant & 0x0FFFFFFF;

      Vdst = Vexp | __as_int16(Vmant);
   } // 8 + 5(shift) = 13
   #endif
};

/*-----------------------------------------------------------------------------
* bit_interleave
*----------------------------------------------------------------------------*/
template <typename elem_type> 
struct bit_interleave
{
   static inline void apply(__int16& Vdst, __int16 Vsrc2, __int16 Vsrc1)
   {
      // join lower 16b from each 32b lane 
      static const __uchar permstr[] = 
         "\x00\x01\x20\x21\x02\x03\x22\x23\x04\x05\x24\x25\x06\x07\x26\x27"
         "\x08\x09\x28\x29\x0A\x0B\x2A\x2B\x0C\x0D\x2C\x2D\x0E\x0F\x2E\x2F"
         "\x10\x11\x30\x31\x12\x13\x32\x33\x14\x15\x34\x35\x16\x17\x36\x37"
         "\x18\x19\x38\x39\x1A\x1B\x3A\x3B\x1C\x1D\x3C\x3D\x1E\x1F\x3E\x3F";

      __int16 Vsrc21 = __as_int16(__vpermeeh_yvvv(*(__uchar64*)permstr, 
                                                  __as_uchar64(Vsrc2), 
                                                  __as_uchar64(Vsrc1))); 
      Vdst = __shuffle_bit(Vsrc21); 
   }
};

/*-----------------------------------------------------------------------------
* bit_deinterleave
*----------------------------------------------------------------------------*/
template <typename elem_type> 
struct bit_deinterleave
{
   static inline void apply(__int16& Vdst1, __int16& Vdst2, __int16 Vsrc1)
   {
      __int16 Vdst21 = __vbitdealw_vv(Vsrc1);
      Vdst1 = __as_int16(__vhunpkuwh_vv(__as_ushort32(Vdst21))); 
      Vdst2 = __as_int16(__vhunpkuwl_vv(__as_ushort32(Vdst21))); 
   }
};

/*-----------------------------------------------------------------------------
* vshf16
*----------------------------------------------------------------------------*/
template <typename elem_type> 
struct vshf16
{
   static inline void apply(__int16& Vdst1, __int16& Vdst2, __int16 Vsrc1)
   {
      Vdst1 = Vsrc1 << (__int16)16;
      Vdst2 = __high_short_to_int(__as_short32(Vsrc1));   // VHUNPKWH
   }
};

/*-----------------------------------------------------------------------------
* interleave32
*----------------------------------------------------------------------------*/
struct i_32_perm
{
   static inline __uchar64 perm()
   {
      static const __uchar permstr[] = 
         "\x00\x01\x02\x03\x20\x21\x22\x23\x04\x05\x06\x07\x24\x25\x26\x27"
         "\x08\x09\x0A\x0B\x28\x29\x2A\x2B\x0C\x0D\x0E\x0F\x2C\x2D\x2E\x2F"
         "\x10\x11\x12\x13\x30\x31\x32\x33\x14\x15\x16\x17\x34\x35\x36\x37"
         "\x18\x19\x1A\x1B\x38\x39\x3A\x3B\x1C\x1D\x1E\x1F\x3C\x3D\x3E\x3F";
      return *(__uchar64*)permstr;
   }
};

template <typename elem_type,
          int nelem=VCOP_SIMD_WIDTH>
   struct interleave_32;

template <typename elem_type> 
struct interleave_32 <elem_type, 8>
{
   static inline void apply(__int16& Vdst1, __int16& Vdst2)
   {
      // interleave 2 __int8 vectors
      __uchar64 perm = i_32_perm::perm();
      __int16 Vtmp = __as_int16(__vpermll_yvvv(perm,
                                               __as_uchar64(Vdst2),
                                               __as_uchar64(Vdst1)));
      Vdst1 = Vtmp;
      Vdst2.lo = Vtmp.hi;
   }
};

template <typename elem_type> 
struct interleave_32<elem_type, 16>
{
   static inline void apply(__int16& Vdst1, __int16& Vdst2)
   {
      // interleave 2 __int16 vectors
      __uchar64 perm = i_32_perm::perm();
      __int16 Vtmp1 = __as_int16(__vpermll_yvvv(perm,
                                                __as_uchar64(Vdst2),
                                                __as_uchar64(Vdst1)));
      __int16 Vtmp2 = __as_int16(__vpermhh_yvvv(perm,
                                                __as_uchar64(Vdst2),
                                                __as_uchar64(Vdst1)));
      Vdst1 = Vtmp1;
      Vdst2 = Vtmp2;
   }
};

struct di_32_perm
{
   static inline __uchar64 perm()
   { 
      static const __uchar permstr[] = 
        "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
        "\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F"
        "\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40"
        "\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40";
      return *(__uchar64*)permstr;
   }
};

/*-----------------------------------------------------------------------------
* deinterleave_32
*----------------------------------------------------------------------------*/
template <typename elem_type,
          int nelem=VCOP_SIMD_WIDTH>
   struct deinterleave_32;

template <typename elem_type> 
struct deinterleave_32<elem_type, 8>
{
   static inline void apply(__int16& Vdst1, __int16& Vdst2)
   {
      // deinterleave 2 __int8 vectors 

      __uchar64 perm  = di_32_perm::perm(); 
      __int16 Veven = __as_int16(__vpermeew_yvvv(perm, __as_uchar64(Vdst2),
                                                       __as_uchar64(Vdst1)));
      __int16 Vodd  = __as_int16(__vpermoow_yvvv(perm, __as_uchar64(Vdst2),
                                                       __as_uchar64(Vdst1)));
      Vdst1 = __as_int16(Veven);
      Vdst2 = __as_int16(Vodd);
   }
};

template <typename elem_type> 
struct deinterleave_32<elem_type, 16>
{
   static inline void apply(__int16& Vdst1, __int16& Vdst2)
   {
      // deinterleave 2 __int16 vectors 

      __int16 Veven = __vwpackl_vvv(Vdst2, Vdst1);
      __int16 Vodd  = __vwpackh_vvv(Vdst2, Vdst1);
      Vdst1 = Veven;
      Vdst2 = Vodd;
   }
};

/*-----------------------------------------------------------------------------
* interleave2_32
*----------------------------------------------------------------------------*/
template <typename elem_type,
          int nelem=VCOP_SIMD_WIDTH>
   struct interleave2_32;

template <typename elem_type> 
struct interleave2_32<elem_type, 8>
{
   static inline void apply(__int16& Vdst1, __int16& Vdst2)
   {
      __int16 Vtmp = __as_int16(__vshfl2dll_vvv(__as_long8(Vdst2), 
                                                __as_long8(Vdst1))); 
      Vdst1    = Vtmp;
      Vdst2.lo = Vtmp.hi;
   }
};

template <typename elem_type> 
struct interleave2_32<elem_type, 16>
{
   static inline void apply(__int16& Vdst1, __int16& Vdst2)
   {
      __int16 Vtmp1 = __as_int16(__vshfl2dll_vvv(__as_long8(Vdst2), 
                                                 __as_long8(Vdst1))); 

      __int16 Vtmp2 = __as_int16(__vshfl2dhh_vvv(__as_long8(Vdst2), 
                                                 __as_long8(Vdst1))); 

      Vdst1 = Vtmp1;
      Vdst2 = Vtmp2;
   }
};

/*-----------------------------------------------------------------------------
* deinterleave2_32
*----------------------------------------------------------------------------*/
template <typename elem_type,
          int nelem = VCOP_SIMD_WIDTH> 
   struct deinterleave2_32;

template <typename elem_type>
struct deinterleave2_32<elem_type, 8>
{
   static inline void apply(__int16& Vdst1, __int16& Vdst2)
   {
      __uchar64 perm  = di_32_perm::perm();
      __uchar64 Veven = __vpermeed_yvvv(perm, __as_uchar64(Vdst2),
                                              __as_uchar64(Vdst1));
      __uchar64 Vodd  = __vpermood_yvvv(perm, __as_uchar64(Vdst2),
                                              __as_uchar64(Vdst1));
      Vdst1 = __as_int16(Veven);
      Vdst2 = __as_int16(Vodd);
   }
};

template <typename elem_type>
struct deinterleave2_32<elem_type, 16>
{
   static inline void apply(__int16& Vdst1, __int16& Vdst2)
   {
      __long8 Veven = __vdpackl_vvv(__as_long8(Vdst2),
                                    __as_long8(Vdst1));
      __long8 Vodd  = __vdpackh_vvv(__as_long8(Vdst2),
                                    __as_long8(Vdst1));
      Vdst1 = __as_int16(Veven);
      Vdst2 = __as_int16(Vodd);
   }
};

/*-----------------------------------------------------------------------------
* interleave4_32
*----------------------------------------------------------------------------*/
struct i4_32_perm
{
   static inline __uchar64 perm()
   {
      static const __uchar permstr[] = 
         "\x00\x01\x02\x03\x04\x05\x06\x07\x10\x11\x12\x13\x14\x15\x16\x17"
         "\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F"
         "\x20\x21\x22\x23\x24\x25\x26\x27\x30\x31\x32\x33\x34\x35\x36\x37"
         "\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F";
      return *(__uchar64*)permstr;
   }
};

template <typename elem_type,
          int nelem=VCOP_SIMD_WIDTH>
   struct interleave4_32;

template <typename elem_type> 
struct interleave4_32<elem_type, 8>
{
   static inline void apply(__int16& Vdst1, __int16& Vdst2)
   {
      // interleave 2 __long4 vectors after VSHFL2DLL
      __uchar64 perm = i4_32_perm::perm();
      __int16   Vtmp = __as_int16(__vshfl2dll_vvv(__as_ulong8(Vdst2), 
                                                __as_ulong8(Vdst1))); 
      Vtmp = __as_int16(__vperm_vvv(perm, __as_uchar64(Vtmp))); 
      Vdst1    = Vtmp;
      Vdst2.lo = Vtmp.hi;
   }
};

template <typename elem_type> 
struct interleave4_32<elem_type, 16>
{
   static inline void apply(__int16& Vdst1, __int16& Vdst2)
   {
      // interleave 2 __long8 vectors after 2 VSHFL2DLL's
      __uchar64 perm = i4_32_perm::perm();

      __int16 Vtmp1 = __as_int16(__vshfl2dll_vvv(__as_ulong8(Vdst2), 
                                              __as_ulong8(Vdst1))); 
      Vtmp1 = __as_int16(__vperm_vvv(perm, __as_uchar64(Vtmp1))); 

      __int16 Vtmp2 = __as_int16(__vshfl2dhh_vvv(__as_ulong8(Vdst2), 
                                              __as_ulong8(Vdst1))); 
      Vtmp2 = __as_int16(__vperm_vvv(perm, __as_uchar64(Vtmp2))); 

      Vdst1 = Vtmp1;
      Vdst2 = Vtmp2;
   }
};

}  // namespace VCOP_VM
