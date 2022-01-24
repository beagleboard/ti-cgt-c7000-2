/*****************************************************************************/
/* VCOP_STORE.H                                                              */
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
/*    VCOP Virtual Machine - Store operations                                */
/*****************************************************************************/
/*                                                                           */
/* TRANSLATION LAYERS                                                        */
/*                                                                           */
/*-   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -   -  */
/* TOP                                                                       */
/* LEVEL                        +----------vcop_store--------+               */
/* INTERFACE                    |                            |               */
/* LAYER                 +-----store()-----+            store_pred()----+    */
/*-   -   -   -   -   -  |-   -   -   -   -|  -   -   -   -  |-   -   - | -  */
/* STORE OP ISA          v                 v                 v          |    */
/* ABSTRACTION   vstore_interleave      vstore           vstore_pred    |    */
/* LAYER                 |                 |                 |          |    */
/*-   -   -   -   -   -  |-   -   -   -   -|  -   -   -   -  |-   -   - | -  */
/* MEMORY                |                 v                 |          |    */
/* ACCESS                +-------------->SAptr<--------------+          |    */
/* LAYER                 |                 |                 |          |    */
/*-   -   -   -   -   -  |-   -   -   -   -|  -   -   -   -  |-   -   - | -  */
/* INTRINSIC/            v                 v                 v          v    */
/* HARDWARE                          INTRINSICS                              */
/* LAYER                                                                     */
/*****************************************************************************/

namespace VCOP_VM
{

/******************************************************************************
* Store operation ISA abstractions
* ISA abstrations provide an interface that allows the client to express store
* operations generically in terms of element types and number of elements for
* both the register source and the memory destination. The layer handles 
* packing and lane masking, abstracts the differences between SA-based 
* addressing and regular indirection, and selects the proper instruction.
******************************************************************************/
/*-----------------------------------------------------------------------------
* vstore - generic vector store
*     Parameterized by type and SA mode
*        srctype - type of register source vector (typically __int16)
*        memtype - type of memory vector (typically {char|short|int}8 ) 
*        Stag    - nosa for regular indirect, or SA mode 
*----------------------------------------------------------------------------*/
template<typename srctype, typename memtype, typename Stag> struct vstore;

/*-----------------------------------------------------------------------------
* Non-packing vector stores
*----------------------------------------------------------------------------*/
// <type>M --> <type>N (full or partial vector)
// partial vector masked by store instr
// VST<N><type>
template<typename type, int M, int N, typename Stag>
struct vstore<vector<type, M>, vector<type,N>, Stag>
{
   typedef typename vector<type, M>::type regtype; 
   typedef typename vector<type, N>::type memtype; 
   static void apply(regtype Vsrc, void* p)
   {
      memtype Vsub = subvec<regtype, memtype>::apply(Vsrc); 
      memtype* ptr = SAptr<memtype, Stag>(p).addr(); 
      *ptr = Vsub;
   }
};

/*-----------------------------------------------------------------------------
* Packing vector stores 
*----------------------------------------------------------------------------*/
// int<M> --> short<M>  (full vector)
// VSTHPACKL
template<int M, typename Stag>
struct vstore<vector<int32_t,M>, vector<int16_t,M>, Stag>
{
   typedef typename vector<int32_t, M>::type regtype; 
   typedef typename vector<int16_t, M>::type memtype; 
   static void apply(regtype Vsrc, void* p)
   {
      memtype* ptr = SAptr<memtype, Stag>(p).addr(); 
      __vstore_packl(ptr, Vsrc);
   }
};

// int<M> --> char<M>  (full vector)
// VSTWPACKB
template<int M, typename Stag>
struct vstore<vector<int32_t,M>, vector<int8_t,M>, Stag>
{
   typedef typename vector<int32_t, M>::type regtype; 
   typedef typename vector<int8_t, M>::type memtype; 
   static void apply(regtype Vsrc, void* p)
   {
      memtype* ptr = SAptr<memtype, Stag>(p).addr(); 
      __vstore_pack_byte(ptr, Vsrc);
   }
};

// int<M> --> short<N>, N<16  (partial vector (via predication))
// MASKH, VSTPHPACKL
template<int M, int N, typename Stag> 
struct vstore<vector<int32_t,M>, vector<int16_t,N>, Stag>
{
   typedef typename vector<int32_t, M>::type regtype; 
   typedef typename vector<int16_t, M>::type memtype; 
   static void apply(regtype Vsrc, void* p)
   {
      vpred pred = SAmask<4, Stag>::get_mask(N);
      memtype* ptr = SAptr<memtype, Stag>(p).addr(); 
      __vstore_pred_packl(pred, ptr, Vsrc);
   }
};

// int<M> --> char<N>, N<16  (partial vector (via predication))
// VSTWPACKB
template<int M, int N, typename Stag>
struct vstore<vector<int32_t,M>, vector<int8_t,N>, Stag>
{
   typedef typename vector<int32_t, M>::type regtype; 
   typedef typename vector<int8_t, M>::type memtype; 
   static void apply(regtype Vsrc, void* p)
   {
      vpred pred = SAmask<4, Stag>::get_mask(N);
      memtype* ptr = SAptr<memtype, Stag>(p).addr(); 
      __vstore_pred_pack_byte(pred, ptr, Vsrc);
   }
};

/*-----------------------------------------------------------------------------
* Scalar stores 
*----------------------------------------------------------------------------*/
// vector --> type (scalar store)
// ST<type>
template<typename srctype, typename type, typename Stag>
struct vstore<srctype, scalar<type>, Stag>
{
   typedef typename srctype::type regtype; 
   static void apply(regtype Vsrc, void* p)
   {
      type* ptr = SAptr<type, Stag>(p).addr(); 
      *ptr = (type)Vsrc.s0; 
   }
};

/*-----------------------------------------------------------------------------
* Interleaved stores
*----------------------------------------------------------------------------*/
template<typename srctype, typename memtype, typename Stag> 
struct vstore_interleave;

// short<M> --> short<M>  (full vector)
// VSTINTLH
template<int M, typename Stag>
struct vstore_interleave<vector<int16_t,M>, vector<int16_t,M>, Stag>
{
   typedef typename vector<int16_t, M>::type regtype; 
   typedef typename vector<int16_t, M>::type memtype; 
   static void apply(regtype Vsrc0, regtype Vsrc1, void* p)
   {
      memtype* ptr = SAptr<memtype, Stag>(p).addr(); 
      __vstore_interleave(ptr, Vsrc0, Vsrc1); 
   }
};

// short<M> --> short<N>  (partial vector (via predication))
// VSTPINTLH
template<int M, int N, typename Stag>
struct vstore_interleave<vector<int16_t,M>, vector<int16_t,N>, Stag>
{
   typedef typename vector<int16_t, M>::type regtype; 
   typedef typename vector<int16_t, M>::type memtype;
   static void apply(regtype Vsrc0, regtype Vsrc1, void* p)
   {
      vpred pred = SAmask<2, Stag>::get_mask(N);
      memtype* ptr = SAptr<memtype, Stag>(p).addr(); 
      __vstore_pred_interleave(pred, ptr, Vsrc0, Vsrc1); 
   }
};

// char<M> --> char<M>  (full vector)
// VSTINTLB4
template<int M, typename Stag>
struct vstore_interleave<vector<int8_t,M>, vector<int8_t,M>, Stag>
{
   typedef typename vector<int8_t, M>::type regtype; 
   typedef typename vector<int8_t, M/2>::type memtype; 
   static void apply(regtype Vsrc0, regtype Vsrc1, void* p)
   {
      memtype* ptr = SAptr<memtype, Stag>(p).addr(); 
      __vstore_interleave(ptr, Vsrc0, Vsrc1); 
   }
};

// char<M> --> char<N>  (partial vector (via predication))
// VSTPINTLB4
template<int M, int N, typename Stag>
struct vstore_interleave<vector<int8_t,M>, vector<int8_t,N>, Stag>
{
   typedef typename vector<int8_t, M>::type regtype; 
   typedef typename vector<int8_t, M/2>::type memtype;
   static void apply(regtype Vsrc0, regtype Vsrc1, void* p)
   {
      vpred pred = SAmask<1, Stag>::get_mask(N);
      memtype* ptr = SAptr<memtype, Stag>(p).addr(); 
      __vstore_pred_interleave4(pred, ptr, Vsrc0, Vsrc1); 
   }
};

/******************************************************************************
* zcompare() - 
*   Helper function for generating store predicate from VCOP vector
******************************************************************************/
inline vpred zcompare(__int16 Vpred)
{
   // Compare __int16 predicate != 0. 
   // No compare NEQ, and no way to negate predicate from C, so use 
   // unsigned GT
   __uint16 Vpredu = __as_uint16(Vpred);

   vpred pred = __cmp_gt_pred(Vpredu, (__uint16)(0)); 
   return pred; 
}

/*-----------------------------------------------------------------------------
* vstore_pred - predicated vector store
*     Parameterized by type and SA mode
*        srctype - type of register source vector (typically __int16)
*        memtype - type of memory vector (typically {char|short|int}8 ) 
*        Stag    - nosa for regular indirect, or SA mode 
*----------------------------------------------------------------------------*/
template<typename srctype, typename memtype, typename Stag> struct vstore_pred;

/*-----------------------------------------------------------------------------
* Non-packing predicated vector stores
*----------------------------------------------------------------------------*/
// <type>M --> <type>N (full or partial vector)
// partial vector masked by store instr
// VSTP<N><type>
template<typename type, int M, int N, typename Stag>
struct vstore_pred<vector<type, M>, vector<type,N>, Stag>
{
   typedef typename vector<type, M>::type regtype; 
   typedef typename vector<type, N>::type memtype; 
   static void apply(regtype Vsrc, void* p, vpred pred)
   {
      SAptr<memtype, Stag> ptr(p); 
      memtype Vsub = subvec<regtype,memtype>::apply(Vsrc);
      __vstore_pred(pred, (ptr.addr()), Vsub);
   }
};

template <int M, int N, typename Stag>
struct vstore_pred<vector<int32_t, M>, vector<uint32_t, N>, Stag> : 
   public vstore_pred<vector<int32_t, M>, vector<int32_t, N>, Stag> {};

/*-----------------------------------------------------------------------------
* Packing predicated vector stores 
*----------------------------------------------------------------------------*/
// long<N> --> int<N>, N<16  (full vector)
// VSTPWPACKL
template<int N, typename Stag> 
struct vstore_pred<vector<int64_t,N>, vector<int32_t,N>, Stag>
{
   typedef typename vector<int64_t, N>::type regtype; 
   typedef typename vector<int32_t, N>::type memtype; 
   static void apply(regtype Vsrc, void* p, vpred pred)
   {
      SAptr<memtype, Stag> ptr(p); 
      __vstore_pred_packl(pred, (ptr.addr()), Vsrc); 
   }
};

// long<M> --> int<N>, N<16  (partial vector (via predication))
// MASKH, VSTPWPACKL
template<int M, int N, typename Stag> 
struct vstore_pred<vector<int64_t,M>, vector<int32_t,N>, Stag>
{
   typedef typename vector<int64_t, M>::type regtype; 
   typedef typename vector<int32_t, M>::type memtype; 
   static void apply(regtype Vsrc, void* p, vpred pred)
   {
      /* nosa to enable hoisting of the MASK/AND sequence */
      vpred pmask = SAmask<8, nosa>::get_mask(N);
      pred = __and(pred, pmask); 
      SAptr<memtype, Stag> ptr(p); 
      __vstore_pred_packl(pred, (ptr.addr()), Vsrc); 
   }
};

template <int M, int N, typename Stag>
struct vstore_pred<vector<int64_t, M>, vector<uint32_t, N>, Stag> : 
   public vstore_pred<vector<int64_t, M>, vector<int32_t, N>, Stag> {};

// int<N> --> short<N>, N<16  (full vector)
// VSTPHPACKL
template<int N, typename Stag> 
struct vstore_pred<vector<int32_t,N>, vector<int16_t,N>, Stag>
{
   typedef typename vector<int32_t, N>::type regtype; 
   typedef typename vector<int16_t, N>::type memtype; 
   static void apply(regtype Vsrc, void* p, vpred pred)
   {
      SAptr<memtype, Stag> ptr(p); 
      __vstore_pred_packl(pred, (ptr.addr()), Vsrc);
   }
};

// int<M> --> short<N>, N<16  (partial vector (via predication))
// MASKH, VSTPHPACKL
template<int M, int N, typename Stag> 
struct vstore_pred<vector<int32_t,M>, vector<int16_t,N>, Stag>
{
   typedef typename vector<int32_t, M>::type regtype; 
   typedef typename vector<int16_t, M>::type memtype; 
   static void apply(regtype Vsrc, void* p, vpred pred)
   {
      /* nosa to enable hoisting of the MASK/AND sequence */
      vpred pmask  = SAmask<4, nosa>::get_mask(N);
      pred = __and(pred, pmask); 
      SAptr<memtype, Stag> ptr(p); 
      __vstore_pred_packl(pred, (ptr.addr()), Vsrc);
   }
};

template <int M, int N, typename Stag>
struct vstore_pred<vector<int32_t, M>, vector<uint16_t, N>, Stag> : 
   public vstore_pred<vector<int32_t, M>, vector<int16_t, N>, Stag> {};

// int<N> --> char<N>, N<16  (full vector)
// VSTWPACKB
template<int N, typename Stag>
struct vstore_pred<vector<int32_t,N>, vector<int8_t,N>, Stag>
{
   typedef typename vector<int32_t, N>::type regtype; 
   typedef typename vector<int8_t, N>::type memtype; 
   static void apply(regtype Vsrc, void* p, vpred pred)
   {
      memtype* ptr = SAptr<memtype, Stag>(p).addr(); 
      __vstore_pred_pack_byte(pred, ptr, Vsrc);
   }
};

// int<M> --> char<N>, N<16  (partial vector (via predication))
// VSTWPACKB
template<int M, int N, typename Stag>
struct vstore_pred<vector<int32_t,M>, vector<int8_t,N>, Stag>
{
   typedef typename vector<int32_t, M>::type regtype; 
   typedef typename vector<int8_t, M>::type memtype; 
   static void apply(regtype Vsrc, void* p, vpred pred)
   {
      /* nosa to enable hoisting of the MASK/AND sequence */
      vpred pmask  = SAmask<4, nosa>::get_mask(N);
      pred = __and(pred, pmask); 
      memtype* ptr = SAptr<memtype, Stag>(p).addr(); 
      __vstore_pred_pack_byte(pred, ptr, Vsrc);
   }
};

template <int M, int N, typename Stag>
struct vstore_pred<vector<int32_t, M>, vector<uint8_t, N>, Stag> : 
   public vstore_pred<vector<int32_t, M>, vector<int8_t, N>, Stag> {};

// short<N> --> char<N>, N<16  (full vector)
// VSTPBPACKL
template<int N, typename Stag> 
struct vstore_pred<vector<int16_t,N>, vector<int8_t,N>, Stag>
{
   typedef typename vector<int16_t, N>::type regtype; 
   typedef typename vector<int8_t, N>::type memtype; 
   static void apply(regtype Vsrc, void* p, vpred pred)
   {
      SAptr<memtype, Stag> ptr(p); 
      __vstore_pred_packl(pred, (ptr.addr()), Vsrc);
   }
};

// short<M> --> char<N>, N<16  (partial vector (via predication))
// MASKH, VSTPBPACKL
template<int M, int N, typename Stag> 
struct vstore_pred<vector<int16_t,M>, vector<int8_t,N>, Stag>
{
   typedef typename vector<int16_t, M>::type regtype; 
   typedef typename vector<int8_t, M>::type memtype; 
   static void apply(regtype Vsrc, void* p, vpred pred)
   {
      /* nosa to enable hoisting of the MASK/AND sequence */
      vpred pmask  = SAmask<4, nosa>::get_mask(N); 
      pred = __and(pred, pmask); 
      SAptr<memtype, Stag> ptr(p); 
      __vstore_pred_packl(pred, (ptr.addr()), Vsrc);
   }
};

template <int M, int N, typename Stag>
struct vstore_pred<vector<int16_t, M>, vector<uint8_t, N>, Stag> : 
   public vstore_pred<vector<int16_t, M>, vector<int8_t, N>, Stag> {};

/******************************************************************************
* vcop_store         
*   This class provides C7x code sequences for each combination of data
*   type and  VCOP distribution mode. The API is:
*
*   vcop_store<type, dist, Stag, simd>
*       :: store(__vector Vsrc, void* p)
*          Store vector 'Vsrc' to address 'p'
* 
*       :: store_pred(__vector Vsrc, void* p, __int16 pred)
*          Predicated store
*
*   Each specialization implements a type/dist combination.
******************************************************************************/
template<typename type, 
         class    dist, 
         typename Stag=nosa, 
         int      simd=VCOP_SIMD_WIDTH> 
   struct vcop_store;

class npt;
class table_npt;
class onept;
class ds2;
class offset_np1;
class s_scatter;
class p_scatter;
class skip;
class collate_;
class interleave;
class transpose;

/*-----------------------------------------------------------------------------
* npt
*----------------------------------------------------------------------------*/
template <typename type, typename Stag, int simd>
struct vcop_store<type, npt, Stag, simd>
{
   static void store(__int16 Vsrc, void* p)
   {
      vstore<vector<int32_t,16>, vector<type,simd>, Stag>::apply(Vsrc, p); 
   }
   static void store_pred(__int16 Vsrc, void* p, __int16 pred)
   {
      vpred Vpredw = zcompare(pred);
      vstore_pred<vector<int32_t,16>, vector<type,simd>, Stag>
                                                       ::apply(Vsrc, p, Vpredw);
   }
};

template <typename Stag, int simd>
struct vcop_store<uint8_t, npt, Stag, simd> : 
   public vcop_store<int8_t, npt, Stag, simd> {};

template <typename Stag, int simd>
struct vcop_store<uint16_t, npt, Stag, simd> :
   public vcop_store<int16_t, npt, Stag, simd> {};

template <typename Stag, int simd>
struct vcop_store<uint32_t, npt, Stag, simd> : 
   public vcop_store<int32_t, npt, Stag, simd> {};

/*-----------------------------------------------------------------------------
* onept
*----------------------------------------------------------------------------*/
template <typename type, typename Stag, int simd>
struct vcop_store<type, onept, Stag, simd>
{
   typedef typename traits<type>::signed_type stype;
   static void store(__int16 Vsrc, void* p)
   {
      vstore<vector<int32_t,16>, scalar<stype>, Stag>::apply(Vsrc, p); 
   }
   static void store_pred(__int16 Vsrc, void* p, __int16 pred)
   {
      type* ptr = (type*)SAptr<stype, Stag>(p).addr(); 
      if (pred.s0)
         *ptr = (stype)Vsrc.s0;
   }
}; 

/*-----------------------------------------------------------------------------
* ds2
*----------------------------------------------------------------------------*/
// ds2, 8-bit
template<typename Stag, int simd> struct vcop_store<int8_t, ds2, Stag, simd>
{
   static void store(__int16 Vsrc, void* p)
   {
      // select every 8th byte                           
      __char64 svals = vperm_ds8_8(Vsrc); 
      vstore<vector<int8_t,64>, vector<int8_t,simd/2>, Stag>::apply(svals, p); 
   }
   static void store_pred(__int16 Vsrc, void* p, __int16 pred)
   {
      vpred Vpredw = zcompare(pred); 
       
      // decimate predicate by words for ds2
      Vpredw  = __decimate_int(Vpredw, Vpredw); 

      // decimate src vector by 2
      __int16 svals = vperm_ds2_32(Vsrc); 

      vstore_pred<vector<int32_t,16>, vector<int8_t,simd/2>, Stag>
                                                      ::apply(svals, p, Vpredw);
   }
};

template<typename Stag,int simd> struct vcop_store<uint8_t, ds2, Stag, simd> :
   public vcop_store<int8_t, ds2, Stag, simd> {};

// ds2, 16-bit
template<typename Stag, int simd> struct vcop_store<int16_t, ds2, Stag, simd>
{
   static void store(__int16 Vsrc, void* p)
   {
      // select every 4th halfword
      __short32 svals = vperm_ds4_16(Vsrc); 
      vstore<vector<int16_t,32>,vector<int16_t,simd/2>,Stag>::apply(svals, p);
   }
   static void store_pred(__int16 Vsrc, void* p, __int16 pred)
   {
      vpred Vpredw = zcompare(pred); 

      // decimate predicate by words for ds2
      Vpredw  = __decimate_int(Vpredw, Vpredw); 

      // decimate src vector by 2
      __int16 svals = vperm_ds2_32(Vsrc); 

      vstore_pred<vector<int32_t,16>, vector<int16_t,simd/2>, Stag>
                                                      ::apply(svals, p, Vpredw);
   }
};

template<typename Stag,int simd> struct vcop_store<uint16_t,ds2,Stag,simd> :
   public vcop_store<int16_t, ds2, Stag, simd> {};

// ds2, 32-bit
template<typename Stag, int simd> struct vcop_store<int32_t, ds2, Stag, simd>
{
   static void store(__int16 Vsrc, void* p)
   {
      vpred pmask = SAmask<8, Stag>::get_mask(simd/2);
      __int8* ptr = SAptr<__int8, Stag>(p).addr(); 
      __vstore_pred_packl(pmask, ptr, __as_long8(Vsrc)); 
   }
   static void store_pred(__int16 Vsrc, void* p, __int16 pred)
   {
      vpred Vpredw = zcompare(pred); 

      vstore_pred<vector<int64_t,8>, vector<int32_t,simd/2>, Stag>
                                           ::apply(__as_long8(Vsrc), p, Vpredw);
   }
};

// u32 ds2 - same as s32
template<typename Stag,int simd> struct vcop_store<uint32_t,ds2,Stag,simd> :
   public vcop_store<int32_t, ds2, Stag, simd> {};

/*-----------------------------------------------------------------------------
* skip
*    VCOP has 8 and 16-bit only
*----------------------------------------------------------------------------*/
// skip, 8-bit
template<typename Stag> struct vcop_store<int8_t, skip, Stag, 16>
{
   static void store(__int16 Vsrc, void* p)
   {
      vpred Vpred = _mvrp(0x3333333333333333);    // every other byte
      vstore_pred<vector<int16_t, 32>, vector<int8_t, 32>, Stag>
                                          ::apply(__as_short32(Vsrc), p, Vpred);
   }
   static void store_pred(__int16 Vsrc, void* p, __int16 pred)
   {
      vpred Vpredw = zcompare(pred); 

      // mask to enable every other halfword
      vpred Vmask  = _mvrp(0x3333333333333333);
            Vpredw = __and(Vpredw, Vmask); 

      vstore_pred<vector<int16_t, 32>, vector<int8_t, 32>, Stag>
                                         ::apply(__as_short32(Vsrc), p, Vpredw);
   }
};

template<typename Stag> struct vcop_store<int8_t, skip, Stag, 8>
{
   static void store(__int16 Vsrc, void* p)
   {
      vpred Vpred = _mvrp(0x33333333);    // every other byte
      vstore_pred<vector<int16_t, 32>, vector<int8_t, 32>, Stag>
                                          ::apply(__as_short32(Vsrc), p, Vpred);
   }
   static void store_pred(__int16 Vsrc, void* p, __int16 pred)
   {
      vpred Vpredw = zcompare(pred); 

      // mask to enable every other halfword
      vpred Vmask  = _mvrp(0x33333333);
            Vpredw = __and(Vpredw, Vmask); 

      vstore_pred<vector<int16_t, 32>, vector<int8_t, 32>, Stag>
                                         ::apply(__as_short32(Vsrc), p, Vpredw);
   }
};

template<typename Stag,int simd> struct vcop_store<uint8_t,skip,Stag,simd> :
   public vcop_store<int8_t, skip, Stag, simd> {};

// skip, 16-bit
template<typename Stag> struct vcop_store<int16_t, skip, Stag, 16>
{
   static void store(__int16 Vsrc, void* p)
   {
      vpred Vpred = _mvrp(0x3333333333333333);    // every other short
      vstore_pred<vector<int16_t, 32>, vector<int16_t, 32>, Stag>
                                          ::apply(__as_short32(Vsrc), p, Vpred);
   }
   static void store_pred(__int16 Vsrc, void* p, __int16 pred)
   {
      vpred Vpred = zcompare(pred); 

      // mask to enable every other short
      vpred Vmask = _mvrp(0x3333333333333333);
            Vpred = __and(Vpred, Vmask); 

      // predicated store
      vstore_pred<vector<int16_t, 32>, vector<int16_t, 32>, Stag>
                                          ::apply(__as_short32(Vsrc), p, Vpred);
   }
};

template<typename Stag> struct vcop_store<int16_t, skip, Stag, 8>
{
   static void store(__int16 Vsrc, void* p)
   {
      vpred Vpred = _mvrp(0x33333333);    // every other short
      vstore_pred<vector<int16_t, 32>, vector<int16_t, 32>, Stag>
                                          ::apply(__as_short32(Vsrc), p, Vpred);
   }
   static void store_pred(__int16 Vsrc, void* p, __int16 pred)
   {
      vpred Vpred = zcompare(pred); 

      // mask to enable every other short
      vpred Vmask = _mvrp(0x33333333);
            Vpred = __and(Vpred, Vmask); 

      // predicated store
      vstore_pred<vector<int16_t, 32>, vector<int16_t, 32>, Stag>
                                          ::apply(__as_short32(Vsrc), p, Vpred);
   }
};

template<typename Stag,int simd> struct vcop_store<uint16_t,skip,Stag,simd> :
   public vcop_store<int16_t, skip, Stag, simd> {};

/*-----------------------------------------------------------------------------
* interleave
*    VCOP has 8 and 16-bit only
*----------------------------------------------------------------------------*/
// interleave, 8-bit
template<typename Stag, int simd>
struct vcop_store<int8_t, interleave, Stag, simd>
{
   static void store(__int16 Vsrc0, __int16 Vsrc1, void* p)
   {
      // interleaving store takes every 4th byte from src vectors and 
      // interleaves them. (16 byte from each --> 32 bytes, mask to 16 bytes)
      __char64 Vsrc0b = __as_char64(Vsrc0); 
      __char64 Vsrc1b = __as_char64(Vsrc1); 
      // VSTINTLB4
      vstore_interleave<vector<int8_t,64>, vector<int8_t,simd * 2>, Stag>
         ::apply(Vsrc0b, Vsrc1b, p); 
   }
   // no predication for interleave mode
};

template<typename Stag, int simd>
struct vcop_store<uint8_t, interleave, Stag, simd> :
   public vcop_store<int8_t, interleave, Stag, simd> {};

// interleave, 16-bit
template<typename Stag,
int simd> struct vcop_store<int16_t, interleave, Stag, simd>
{
   static void store(__int16 Vsrc0, __int16 Vsrc1, void* p)
   {
      // interleaving store takes every other hword from src vectors and 
      // interleaves them. (16 hw from each --> 32 hw, mask to 16 hw)
      __short32 Vsrc0h = __as_short32(Vsrc0); 
      __short32 Vsrc1h = __as_short32(Vsrc1); 

      vstore_interleave<vector<int16_t,32>, vector<int16_t,simd * 2>, Stag>
         ::apply(Vsrc0h, Vsrc1h, p); 
   }
   // no predication for interleave mode
};

template<typename Stag, int simd>
struct vcop_store<uint16_t, interleave, Stag, simd> :
   public vcop_store<int16_t, interleave, Stag, simd> {};

/*-----------------------------------------------------------------------------
* s_scatter
*    This implementation of scatter uses full vector shifts to extract the
*    elements of the input vectors more efficiently.  Using a naive "vector.s7"
*    style of extraction requires 1 SHRD (LS) and 6 VGETW (C) per vector of 8.
*    Using the full vector shift style of extraction requires 3 VSHRU (LS) and
*    4 SHRD (LS).
*----------------------------------------------------------------------------*/
template<typename type, typename Stag>
struct vcop_store<type, s_scatter, Stag, 8>
{
   static void store(__int16 Vsrc, void* p, __int16 Vindex)
   {
      // capture address (and advance if SA)
      char* ptr = (char*)(SAptr<type, Stag>(p).addr()); 

      *(type*)(ptr + Vindex.s0) = Vsrc.s0;
      *(type*)(ptr + Vindex.s1) = Vsrc.s1;
      {
         int2 Tsrc   = Vsrc.s23;
         int2 Tindex = Vindex.s23;
         *(type*)(ptr + Tindex.s0) = Tsrc.s0;
         *(type*)(ptr + Tindex.s1) = Tsrc.s1;
      }
      {
         int2 Tsrc   = Vsrc.s45;
         int2 Tindex = Vindex.s45;
         *(type*)(ptr + Tindex.s0) = Tsrc.s0;
         *(type*)(ptr + Tindex.s1) = Tsrc.s1;
      }
      {
         int2 Tsrc   = Vsrc.s67;
         int2 Tindex = Vindex.s67;
         *(type*)(ptr + Tindex.s0) = Tsrc.s0;
         *(type*)(ptr + Tindex.s1) = Tsrc.s1;
      }
      #if 0
      // Naive form
      *(type*)(ptr + Vindex.s0) = Vsrc.s0;
      *(type*)(ptr + Vindex.s1) = Vsrc.s1;
      *(type*)(ptr + Vindex.s2) = Vsrc.s2;
      *(type*)(ptr + Vindex.s3) = Vsrc.s3;
      *(type*)(ptr + Vindex.s4) = Vsrc.s4;
      *(type*)(ptr + Vindex.s5) = Vsrc.s5;
      *(type*)(ptr + Vindex.s6) = Vsrc.s6;
      *(type*)(ptr + Vindex.s7) = Vsrc.s7;
      #endif
   }
   static void store_pred(__int16 Vsrc, void* p, __int16 Vindex, __int16 pred)
   {
      // capture address (and advance if SA)
      char* ptr = (char*)(SAptr<type, Stag>(p).addr()); 

      if (pred.s0) *(type*)(ptr + Vindex.s0) = Vsrc.s0;
      if (pred.s1) *(type*)(ptr + Vindex.s1) = Vsrc.s1;
      {
         int2 Tsrc   = Vsrc.s23;
         int2 Tpred  = pred.s23;
         int2 Tindex = Vindex.s23;
         if (Tpred.s0) *(type*)(ptr + Tindex.s0) = Tsrc.s0;
         if (Tpred.s1) *(type*)(ptr + Tindex.s1) = Tsrc.s1;
      }
      {
         int2 Tsrc   = Vsrc.s45;
         int2 Tpred  = pred.s45;
         int2 Tindex = Vindex.s45;
         if (Tpred.s0) *(type*)(ptr + Tindex.s0) = Tsrc.s0;
         if (Tpred.s1) *(type*)(ptr + Tindex.s1) = Tsrc.s1;
      }
      {
         int2 Tsrc   = Vsrc.s67;
         int2 Tpred  = pred.s67;
         int2 Tindex = Vindex.s67;
         if (Tpred.s0) *(type*)(ptr + Tindex.s0) = Tsrc.s0;
         if (Tpred.s1) *(type*)(ptr + Tindex.s1) = Tsrc.s1;
      }
      #if 0
      // Naive form
      if (pred.s0) *(type*)(ptr + Vindex.s0) = Vsrc.s0;
      if (pred.s1) *(type*)(ptr + Vindex.s1) = Vsrc.s1;
      if (pred.s2) *(type*)(ptr + Vindex.s2) = Vsrc.s2;
      if (pred.s3) *(type*)(ptr + Vindex.s3) = Vsrc.s3;
      if (pred.s4) *(type*)(ptr + Vindex.s4) = Vsrc.s4;
      if (pred.s5) *(type*)(ptr + Vindex.s5) = Vsrc.s5;
      if (pred.s6) *(type*)(ptr + Vindex.s6) = Vsrc.s6;
      if (pred.s7) *(type*)(ptr + Vindex.s7) = Vsrc.s7;
      #endif
   }
};

template<typename type, typename Stag>
struct vcop_store<type, s_scatter, Stag, 16>
{
   static void store(__int16 Vsrc, void* p, __int16 Vindex)
   {
      // capture address (and advance if SA)
      char* ptr = (char*)(SAptr<type, Stag>(p).addr()); 

      *(type*)(ptr + Vindex.s0) = Vsrc.s0;
      *(type*)(ptr + Vindex.s1) = Vsrc.s1;
      {
         int2 Tsrc   = Vsrc.s23;
         int2 Tindex = Vindex.s23;
         *(type*)(ptr + Tindex.s0) = Tsrc.s0;
         *(type*)(ptr + Tindex.s1) = Tsrc.s1;
      }
      {
         int2 Tsrc   = Vsrc.s45;
         int2 Tindex = Vindex.s45;
         *(type*)(ptr + Tindex.s0) = Tsrc.s0;
         *(type*)(ptr + Tindex.s1) = Tsrc.s1;
      }
      {
         int2 Tsrc   = Vsrc.s67;
         int2 Tindex = Vindex.s67;
         *(type*)(ptr + Tindex.s0) = Tsrc.s0;
         *(type*)(ptr + Tindex.s1) = Tsrc.s1;
      }
      {
         int2 Tsrc   = Vsrc.s89;
         int2 Tindex = Vindex.s89;
         *(type*)(ptr + Tindex.s0) = Tsrc.s0;
         *(type*)(ptr + Tindex.s1) = Tsrc.s1;
      }
      {
         int2 Tsrc   = Vsrc.sab;
         int2 Tindex = Vindex.sab;
         *(type*)(ptr + Tindex.s0) = Tsrc.s0;
         *(type*)(ptr + Tindex.s1) = Tsrc.s1;
      }
      {
         int2 Tsrc   = Vsrc.scd;
         int2 Tindex = Vindex.scd;
         *(type*)(ptr + Tindex.s0) = Tsrc.s0;
         *(type*)(ptr + Tindex.s1) = Tsrc.s1;
      }
      {
         int2 Tsrc   = Vsrc.sef;
         int2 Tindex = Vindex.sef;
         *(type*)(ptr + Tindex.s0) = Tsrc.s0;
         *(type*)(ptr + Tindex.s1) = Tsrc.s1;
      }
      #if 0
      // Naive form
      *(type*)(ptr + Vindex.s0) = Vsrc.s0;
      *(type*)(ptr + Vindex.s1) = Vsrc.s1;
      *(type*)(ptr + Vindex.s2) = Vsrc.s2;
      *(type*)(ptr + Vindex.s3) = Vsrc.s3;
      *(type*)(ptr + Vindex.s4) = Vsrc.s4;
      *(type*)(ptr + Vindex.s5) = Vsrc.s5;
      *(type*)(ptr + Vindex.s6) = Vsrc.s6;
      *(type*)(ptr + Vindex.s7) = Vsrc.s7;
      *(type*)(ptr + Vindex.s8) = Vsrc.s8;
      *(type*)(ptr + Vindex.s9) = Vsrc.s9;
      *(type*)(ptr + Vindex.sa) = Vsrc.sa;
      *(type*)(ptr + Vindex.sb) = Vsrc.sb;
      *(type*)(ptr + Vindex.sc) = Vsrc.sc;
      *(type*)(ptr + Vindex.sd) = Vsrc.sd;
      *(type*)(ptr + Vindex.se) = Vsrc.se;
      *(type*)(ptr + Vindex.sf) = Vsrc.sf;
      #endif
   }
   static void store_pred(__int16 Vsrc, void* p, __int16 Vindex, __int16 pred)
   {
      // capture address (and advance if SA)
      char* ptr = (char*)(SAptr<type, Stag>(p).addr()); 

      if (pred.s0) *(type*)(ptr + Vindex.s0) = Vsrc.s0;
      if (pred.s1) *(type*)(ptr + Vindex.s1) = Vsrc.s1;
      {
         int2 Tsrc   = Vsrc.s23;
         int2 Tpred  = pred.s23;
         int2 Tindex = Vindex.s23;
         if (Tpred.s0) *(type*)(ptr + Tindex.s0) = Tsrc.s0;
         if (Tpred.s1) *(type*)(ptr + Tindex.s1) = Tsrc.s1;
      }
      {
         int2 Tsrc   = Vsrc.s45;
         int2 Tpred  = pred.s45;
         int2 Tindex = Vindex.s45;
         if (Tpred.s0) *(type*)(ptr + Tindex.s0) = Tsrc.s0;
         if (Tpred.s1) *(type*)(ptr + Tindex.s1) = Tsrc.s1;
      }
      {
         int2 Tsrc   = Vsrc.s67;
         int2 Tpred  = pred.s67;
         int2 Tindex = Vindex.s67;
         if (Tpred.s0) *(type*)(ptr + Tindex.s0) = Tsrc.s0;
         if (Tpred.s1) *(type*)(ptr + Tindex.s1) = Tsrc.s1;
      }
      {
         int2 Tsrc   = Vsrc.s89;
         int2 Tpred  = pred.s89;
         int2 Tindex = Vindex.s89;
         if (Tpred.s0) *(type*)(ptr + Tindex.s0) = Tsrc.s0;
         if (Tpred.s1) *(type*)(ptr + Tindex.s1) = Tsrc.s1;
      }
      {
         int2 Tsrc   = Vsrc.sab;
         int2 Tpred  = pred.sab;
         int2 Tindex = Vindex.sab;
         if (Tpred.s0) *(type*)(ptr + Tindex.s0) = Tsrc.s0;
         if (Tpred.s1) *(type*)(ptr + Tindex.s1) = Tsrc.s1;
      }
      {
         int2 Tsrc   = Vsrc.scd;
         int2 Tpred  = pred.scd;
         int2 Tindex = Vindex.scd;
         if (Tpred.s0) *(type*)(ptr + Tindex.s0) = Tsrc.s0;
         if (Tpred.s1) *(type*)(ptr + Tindex.s1) = Tsrc.s1;
      }
      {
         int2 Tsrc   = Vsrc.sef;
         int2 Tpred  = pred.sef;
         int2 Tindex = Vindex.sef;
         if (Tpred.s0) *(type*)(ptr + Tindex.s0) = Tsrc.s0;
         if (Tpred.s1) *(type*)(ptr + Tindex.s1) = Tsrc.s1;
      }
      #if 0
      // Naive form
      if (pred.s0) *(type*)(ptr + Vindex.s0) = Vsrc.s0;
      if (pred.s1) *(type*)(ptr + Vindex.s1) = Vsrc.s1;
      if (pred.s2) *(type*)(ptr + Vindex.s2) = Vsrc.s2;
      if (pred.s3) *(type*)(ptr + Vindex.s3) = Vsrc.s3;
      if (pred.s4) *(type*)(ptr + Vindex.s4) = Vsrc.s4;
      if (pred.s5) *(type*)(ptr + Vindex.s5) = Vsrc.s5;
      if (pred.s6) *(type*)(ptr + Vindex.s6) = Vsrc.s6;
      if (pred.s7) *(type*)(ptr + Vindex.s7) = Vsrc.s7;
      if (pred.s0) *(type*)(ptr + Vindex.s8) = Vsrc.s8;
      if (pred.s1) *(type*)(ptr + Vindex.s9) = Vsrc.s9;
      if (pred.s2) *(type*)(ptr + Vindex.sa) = Vsrc.sa;
      if (pred.s3) *(type*)(ptr + Vindex.sb) = Vsrc.sb;
      if (pred.s4) *(type*)(ptr + Vindex.sc) = Vsrc.sc;
      if (pred.s5) *(type*)(ptr + Vindex.sd) = Vsrc.sd;
      if (pred.s6) *(type*)(ptr + Vindex.se) = Vsrc.se;
      if (pred.s7) *(type*)(ptr + Vindex.sf) = Vsrc.sf;
      #endif
   }
};

/*-----------------------------------------------------------------------------
* p_scatter
*    currently implemented as s_scatter
*----------------------------------------------------------------------------*/
// TODO: optimize
template<typename type, typename Stag, int simd> 
struct vcop_store<type, p_scatter, Stag, simd> : 
   public vcop_store<type, s_scatter, Stag, simd> {};

/*-----------------------------------------------------------------------------
* offset_npt1
*----------------------------------------------------------------------------*/
template<typename type, typename Stag> 
struct vcop_store<type, offset_np1, Stag, 8>
{
   // each element is offset by 9 32-bit words
   static inline void* np1_addr(char *ptr, int n)
   { 
      return (void*)(ptr + 9*n*4);
   }

   static void store(__int16 Vsrc, void* p)
   {
      type* tptr = (SAptr<type, Stag>(p).addr()); 
      char* ptr = (char *)tptr;
      *(type*)np1_addr(ptr, 0) = Vsrc.s0;
      *(type*)np1_addr(ptr, 1) = Vsrc.s1;
      *(type*)np1_addr(ptr, 2) = Vsrc.s2;
      *(type*)np1_addr(ptr, 3) = Vsrc.s3;
      *(type*)np1_addr(ptr, 4) = Vsrc.s4;
      *(type*)np1_addr(ptr, 5) = Vsrc.s5;
      *(type*)np1_addr(ptr, 6) = Vsrc.s6;
      *(type*)np1_addr(ptr, 7) = Vsrc.s7;
   }
   static void store_pred(__int16 Vsrc, void* p, __int16 pred)
   {
      type* tptr = (SAptr<type, Stag>(p).addr()); 
      char* ptr = (char *)tptr;
      if (pred.s0) *(type*)np1_addr(ptr, 0) = Vsrc.s0;
      if (pred.s1) *(type*)np1_addr(ptr, 1) = Vsrc.s1;
      if (pred.s2) *(type*)np1_addr(ptr, 2) = Vsrc.s2;
      if (pred.s3) *(type*)np1_addr(ptr, 3) = Vsrc.s3;
      if (pred.s4) *(type*)np1_addr(ptr, 4) = Vsrc.s4;
      if (pred.s5) *(type*)np1_addr(ptr, 5) = Vsrc.s5;
      if (pred.s6) *(type*)np1_addr(ptr, 6) = Vsrc.s6;
      if (pred.s7) *(type*)np1_addr(ptr, 7) = Vsrc.s7;
   }
};

template<typename type, typename Stag> 
struct vcop_store<type, offset_np1, Stag, 16>
{
   // each element is offset by 17 32-bit words
   static inline void* np1_addr(char *ptr, int n)
   { 
      return (void*)(ptr + 17*n*4);
   }

   static void store(__int16 Vsrc, void* p)
   {
      type* tptr = (SAptr<type, Stag>(p).addr()); 
      char* ptr = (char *)tptr;
      *(type*)np1_addr(ptr, 0)  = Vsrc.s0;
      *(type*)np1_addr(ptr, 1)  = Vsrc.s1;
      *(type*)np1_addr(ptr, 2)  = Vsrc.s2;
      *(type*)np1_addr(ptr, 3)  = Vsrc.s3;
      *(type*)np1_addr(ptr, 4)  = Vsrc.s4;
      *(type*)np1_addr(ptr, 5)  = Vsrc.s5;
      *(type*)np1_addr(ptr, 6)  = Vsrc.s6;
      *(type*)np1_addr(ptr, 7)  = Vsrc.s7;
      *(type*)np1_addr(ptr, 8)  = Vsrc.s8;
      *(type*)np1_addr(ptr, 9)  = Vsrc.s9;
      *(type*)np1_addr(ptr, 10) = Vsrc.sa;
      *(type*)np1_addr(ptr, 11) = Vsrc.sb;
      *(type*)np1_addr(ptr, 12) = Vsrc.sc;
      *(type*)np1_addr(ptr, 13) = Vsrc.sd;
      *(type*)np1_addr(ptr, 14) = Vsrc.se;
      *(type*)np1_addr(ptr, 15) = Vsrc.sf;
   }
   static void store_pred(__int16 Vsrc, void* p, __int16 pred)
   {
      type* tptr = (SAptr<type, Stag>(p).addr()); 
      char* ptr = (char *)tptr;
      if (pred.s0) *(type*)np1_addr(ptr, 0)  = Vsrc.s0;
      if (pred.s1) *(type*)np1_addr(ptr, 1)  = Vsrc.s1;
      if (pred.s2) *(type*)np1_addr(ptr, 2)  = Vsrc.s2;
      if (pred.s3) *(type*)np1_addr(ptr, 3)  = Vsrc.s3;
      if (pred.s4) *(type*)np1_addr(ptr, 4)  = Vsrc.s4;
      if (pred.s5) *(type*)np1_addr(ptr, 5)  = Vsrc.s5;
      if (pred.s6) *(type*)np1_addr(ptr, 6)  = Vsrc.s6;
      if (pred.s7) *(type*)np1_addr(ptr, 7)  = Vsrc.s7;
      if (pred.s8) *(type*)np1_addr(ptr, 8)  = Vsrc.s8;
      if (pred.s9) *(type*)np1_addr(ptr, 9)  = Vsrc.s9;
      if (pred.sa) *(type*)np1_addr(ptr, 10) = Vsrc.sa;
      if (pred.sb) *(type*)np1_addr(ptr, 11) = Vsrc.sb;
      if (pred.sc) *(type*)np1_addr(ptr, 12) = Vsrc.sc;
      if (pred.sd) *(type*)np1_addr(ptr, 13) = Vsrc.sd;
      if (pred.se) *(type*)np1_addr(ptr, 14) = Vsrc.se;
      if (pred.sf) *(type*)np1_addr(ptr, 15) = Vsrc.sf;
   }
};

/*-----------------------------------------------------------------------------
* transpose
*----------------------------------------------------------------------------*/
template <typename type, typename Stag, int simd>
struct vcop_store<type, transpose, Stag, simd> :
   public vcop_store<type, npt, Stag, simd> {};

/*-----------------------------------------------------------------------------
* collate_traits
*   helper class to abstract variations due to element sizes
*     collate_traits<type>::vtype 
*        - vector of <type> elements (src of store)
*     collate_traits<type>::pmask  
*        - mask word-wise predicate according to memory data type
*----------------------------------------------------------------------------*/
template<typename type, int simd> struct collate_traits; 

template<> struct collate_traits<int8_t, 8>
{
   typedef __char64 vtype;
   static vpred pmask(vpred Vpredw)
   {
      vpred Vmask;
      Vmask = _mvrp(0x11111111);
      vpred Vpredb = __and_ppp(Vpredw, Vmask); 
      return Vpredb;
   }
};

template<> struct collate_traits<int8_t, 16>
{
   typedef __char64 vtype;
   static vpred pmask(vpred Vpredw)
   {
      vpred Vmask;
      Vmask = _mvrp(0x1111111111111111);
      vpred Vpredb = __and_ppp(Vpredw, Vmask); 
      return Vpredb;
   }
};

template<> struct collate_traits<int16_t, 8>
{
   typedef __short32 vtype; 
   static vpred pmask(vpred Vpredw)
   {
      vpred Vmask;
      Vmask = _mvrp(0x33333333);
      vpred Vpredh = __and_ppp(Vpredw, Vmask); 
      return Vpredh;
   }
};

template<> struct collate_traits<int16_t, 16>
{
   typedef __short32 vtype; 
   static vpred pmask(vpred Vpredw)
   {
      vpred Vmask;
      Vmask = _mvrp(0x3333333333333333);
      vpred Vpredh = __and_ppp(Vpredw, Vmask); 
      return Vpredh;
   }
};

template<> struct collate_traits<int32_t, 8>
{
   typedef __int16 vtype; 
   static vpred pmask(vpred Vpredw)
   {
      vpred Vmask;
      Vmask = _mvrp(0xFFFFFFFF);
      Vpredw = __and_ppp(Vpredw, Vmask); 
      return Vpredw;
   }
};

template<> struct collate_traits<int32_t, 16>
{
   typedef __int16 vtype; 
   static vpred pmask(vpred Vpredw)
   {
      return Vpredw;
   }
};

/*-----------------------------------------------------------------------------
* collate
*----------------------------------------------------------------------------*/
template<typename type, int simd> 
struct vcop_store<type, collate_, nosa, simd>
{
   typedef typename traits<type>::signed_type elem_type;
   typedef          collate_traits<elem_type, simd> my_collate_traits;
   typedef typename my_collate_traits::vtype  my_vtype;

   // note: ptr passed by reference and updated by number of bytes stored
   static void store(__int16 Vsrc, void*& ptr, __int16 Vpred)
   {
      // compare to 0
      vpred Vpredw = zcompare(Vpred); 

      // mask predicate according to store element size
      vpred Vpredb = my_collate_traits::pmask(Vpredw); 

      // pack 'true' elements to RHS of store vector
      my_vtype Vcoll = as_type(my_vtype, 
                               __gather_set_bits(Vpredb, __as_char64(Vsrc))); 

      // pack the predicate bits and get the byte count
      uint32_t nbytes;
      __popcount_gather_char(Vpredb, nbytes, Vpredb);

      // do store
      __vstore_pred(Vpredb, (my_vtype*)ptr, Vcoll); 


      // update pointer
      ptr = (void*)((char*)ptr + nbytes);
   }
   #if 0   // "naive" version, for reference
   static void store(__int16 Vsrc, uint8_t*& ptr, __int16 Vpred)
   {
      if (Vpred.s0) { *(type*)ptr = Vsrc.s0; ptr = (char*)ptr + sizeof(type); } 
      if (Vpred.s1) { *(type*)ptr = Vsrc.s1; ptr = (char*)ptr + sizeof(type); } 
      if (Vpred.s2) { *(type*)ptr = Vsrc.s2; ptr = (char*)ptr + sizeof(type); } 
      if (Vpred.s3) { *(type*)ptr = Vsrc.s3; ptr = (char*)ptr + sizeof(type); } 
      if (Vpred.s4) { *(type*)ptr = Vsrc.s4; ptr = (char*)ptr + sizeof(type); } 
      if (Vpred.s5) { *(type*)ptr = Vsrc.s5; ptr = (char*)ptr + sizeof(type); } 
      if (Vpred.s6) { *(type*)ptr = Vsrc.s6; ptr = (char*)ptr + sizeof(type); } 
      if (Vpred.s7) { *(type*)ptr = Vsrc.s7; ptr = (char*)ptr + sizeof(type); } 
   }
   #endif
};


/*-----------------------------------------------------------------------------
*  table_npt
*     Implemented in terms of npt/onept, with simd parameter set to ntables
*----------------------------------------------------------------------------*/
template <typename type, typename Stag, int simd>
struct vcop_store<type, table_npt, Stag, simd> : 
   public vcop_store<typename traits<type>::signed_type, npt, Stag, simd> {};

template <typename type, typename Stag>
struct vcop_store<type, table_npt, Stag, 1> : 
   public vcop_store<typename traits<type>::signed_type, onept, Stag, 1> {};


/******************************************************************************
* Saturation classes
******************************************************************************/
template <typename elem_type, typename dst_type, int width, int simd=8> 
struct saturate_to_width;
template <typename elem_type, int simd=8> 
struct saturate_to_range;

/*-----------------------------------------------------------------------------
* saturate_to_width<elem_type, dst_type, int width>::apply()
*   - saturate a vector to fit the given destination width
*----------------------------------------------------------------------------*/
// A type is already saturated to its own bounds.
template <int simd> 
struct saturate_to_width<int32_t, int32_t, 32, simd>
{
   static void apply(__int16& Vdst) {} 
};

template <int simd> 
struct saturate_to_width<uint32_t, uint32_t, 32, simd>
   : public saturate_to_width<int32_t, int32_t, 32, simd> {};

// Saturation from signed to unsigned
// VGSATSUW
template <int width, int simd> 
struct saturate_to_width<int32_t, uint32_t, width, simd>
{
   static void apply(__int16& Vdst) 
   {
        Vdst = __as_int16(__saturate_s2u(Vdst, (uchar16)width));
   } 
};

template <int width, int simd> 
struct saturate_to_width<int32_t, uint16_t, width, simd> :
   public saturate_to_width<int32_t, uint32_t, width, simd> {};

template <int width, int simd> 
struct saturate_to_width<int32_t, uint8_t, width, simd> :
   public saturate_to_width<int32_t, uint32_t, width, simd> {};

// optimize signed 16-bit form to use dedicated instruction
template <int simd>
struct saturate_to_width<int32_t, int32_t, 16, simd>
{
   static void apply(__int16& Vdst) 
   { 
      // VSATWH
      Vdst = __as_int16(__int_to_short_sat(Vdst));
   }
};

template <int simd>
struct saturate_to_width<int32_t, int16_t, 16, simd> :
   public saturate_to_width<int32_t, int32_t, 16, simd> {};

template <int simd>
struct saturate_to_width<int32_t, int8_t, 16, simd> :
   public saturate_to_width<int32_t, int32_t, 16, simd> {};

// Saturation from signed to signed
// VGSATW
template <int width, int simd> 
struct saturate_to_width<int32_t, int32_t, width, simd>
{
   static void apply(__int16& Vdst) 
   {
        Vdst = __saturate(Vdst, (uchar16)width);
   } 
};

template <int width, int simd> 
struct saturate_to_width<int32_t, int16_t, width, simd> :
   public saturate_to_width<int32_t, int32_t, width, simd> {};

template <int width, int simd> 
struct saturate_to_width<int32_t, int8_t, width, simd> :
   public saturate_to_width<int32_t, int32_t, width, simd> {};

// unsigned 32-bit element type (vectors declared as __vector___uint32)
// VGSATUW
template <int width, int simd> 
struct saturate_to_width<uint32_t, uint32_t, width, simd>
{
   static void apply(__int16& Vdst) 
   {
        Vdst = __as_int16(__saturate(__as_uint16(Vdst), (uchar16)width));
   } 
};

template <int width, int simd> 
struct saturate_to_width<uint32_t, uint16_t, width, simd> :
   public saturate_to_width<uint32_t, uint32_t, width, simd> {};

template <int width, int simd> 
struct saturate_to_width<uint32_t, uint8_t, width, simd> :
   public saturate_to_width<uint32_t, uint32_t, width, simd> {};

/*-----------------------------------------------------------------------------
* saturate_to_range<elem_type>::apply(min, max)
*      - saturate a vector to fit the two bounds
*
* saturate_to_range<elem_type>::apply(min, minset, max, maxset)
*      - VCOP's 4PARAM form
*----------------------------------------------------------------------------*/
// signed elements
template <int simd> 
struct saturate_to_range<int32_t, simd>
{
   static void apply(__int16& Vdst, int min, int max) 
   {
      __int16 minvals = (__int16)min;
      __int16 maxvals = (__int16)max;
      Vdst = __min(Vdst, maxvals);
      Vdst = __max(Vdst, minvals);
   }
   static void apply(__int16& Vdst, int32_t min, int32_t minset, 
                                    int32_t max, int32_t maxset)
   { 
      __int16 Vmin    = (__int16)min;
      __int16 Vmax    = (__int16)max;
      __int16 Vminset = (__int16)minset;
      __int16 Vmaxset = (__int16)maxset;

      vpred Vpred1 = __cmp_gt_pred(Vmin, Vdst);
      Vdst = __select(Vpred1, Vminset, Vdst);

      vpred Vpred2 = __cmp_gt_pred(Vmax, Vdst); 
      Vdst = __select(Vpred2, Vdst, Vmaxset); 
   }
};

// unsigned elements
template <int simd> 
struct saturate_to_range<uint32_t, simd>
{
   static void apply(__int16& Vdst, uint32_t min, uint32_t max)
   {
      __uint16 minvals = (__uint16)min;
      __uint16 maxvals = (__uint16)max;
      __uint16 vals = __as_uint16(Vdst);
      vals = __min(vals, maxvals);
      vals = __max(vals, minvals);
      Vdst = __as_int16(vals); 
   }
   static void apply(__int16& Vdst, uint32_t min, uint32_t minset, 
                                    uint32_t max, uint32_t maxset)
   {
      __uint16 Vmin    = (__uint16)min;
      __uint16 Vmax    = (__uint16)max;
      __uint16 Vminset = (__uint16)minset;
      __uint16 Vmaxset = (__uint16)maxset;
      __uint16 vals    = __as_uint16(Vdst);

      vpred Vpred1 = __cmp_gt_pred(Vmin, vals);
      vals = __select(Vpred1, Vminset, vals);

      vpred Vpred2 = __cmp_gt_pred(Vmax, vals);
      vals = __select(Vpred2, vals, Vmaxset); 
      Vdst = __as_int16(vals); 
   }
};

}  // namespace VCOP_VM
