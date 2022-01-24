/*****************************************************************************/
/* VCOP_LHT.H                                                                */
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
/*    VCOP Virtual Machine - Lookup/Histogram Table (LHT) operations         */
/*****************************************************************************/
namespace VCOP_VM
{
// forward declarations
template <typename type>              struct LHT_signed_flag;
template <typename type>              struct LHT_element_type_flag;
template <typename src, typename dst> struct LHT_promote_flag;
template <int ntables>                struct LHT_ntable_flag;
template <int npts>                   struct LHT_interp_flag;
template <typename type>              struct LHT_wsize_flag;

template <int id, int size>
struct lut_id;

template <typename type, int nways, int npts, typename lut_id>
struct LHT_base;

template<typename lut_id>
struct LHT_copy_in_base;

template <int dup, typename dup_init_helper,
          typename perm_helper, typename lut_id> 
struct LHT_copy_in;

template<typename lut_id>
struct LHT_copy_out_base;

template <typename type, int dup, typename perm_helper, typename lut_id>
struct LHT_copy_out;

struct dup_copy;
struct dup_zinit;

template <int ntables, int dup>
struct LHT_permute;

/******************************************************************************
* lut_id
*   This class is used to identify a specific lookup table in L1.
*******************************************************************************/
template<>
struct lut_id<0, 32768>
{
   static const int op_lut_set   = __LUT_SET0;
   static const int copy_lut_set = __LUT_SET2;
   static const int size         = __LUT_TBL_SIZE_32KBYTES;
   static const int position     = 0;
};

template<>
struct lut_id<0, 16384>
{
   static const int op_lut_set   = __LUT_SET0;
   static const int copy_lut_set = __LUT_SET2;
   static const int size         = __LUT_TBL_SIZE_16KBYTES;
   static const int position     = 0;
};

template<>
struct lut_id<1, 16384>
{
   static const int op_lut_set   = __LUT_SET1;
   static const int copy_lut_set = __LUT_SET3;
   static const int size         = __LUT_TBL_SIZE_16KBYTES;
   static const int position     = 16384;
};

/******************************************************************************
* vcop_lookup
*   This class implements lookup table operations.
*   Helper classes are incorporated via inheritance.
******************************************************************************/
template <typename type, int ntables, int npts, int dup, typename lut_id>
struct vcop_lookup : 
   public LHT_base<type, ntables*dup, npts, lut_id>,
   public LHT_copy_in<dup, dup_copy, LHT_permute<ntables, dup>, lut_id>
{
   /*--------------------------------------------------------------------------
   * lookup() - perform a table lookup operaation 
   *-------------------------------------------------------------------------*/
   static void lookup(__int16& Vdst, __int16 Vindex)
   {
      __uint16 LHTindex = __as_uint16(Vindex);
      Vdst = __lookup_read_int(lut_id::op_lut_set, LHTindex); 
      #ifdef VVM_DEBUG
      print<uint32_t>::apply(LHTindex, "index%32"); 
      print<int32_t> ::apply(Vdst,     "data %32"); 
      #endif
   }
};

/******************************************************************************
* vcop_lookup - specialization for npts=16
*   16 point interpolation is not available on C7000, so this specialization
*   utilizes two tables, each of which will return 8 points.
******************************************************************************/
template <typename type, typename lut_id>
struct vcop_lookup<type, 1, 16, 1, lut_id> : 
   public LHT_base<type, 2, 8, lut_id>,
   public LHT_copy_in<2, dup_copy, LHT_permute<1, 2>, lut_id>
{
   /*--------------------------------------------------------------------------
   * lookup() - perform a table lookup operaation 
   *-------------------------------------------------------------------------*/
   static void lookup(__int16& Vdst, __int16 Vindex)
   {
      // Only 1 real index is expected.  For the second table, the second value
      // needs to be the first index plus 8.  This ensures 16 contiguous points.
      Vindex.s1 = Vindex.s0 + 8;
      __uint16 LHTindex = __as_uint16(Vindex);
      Vdst = __lookup_read_int(lut_id::op_lut_set, LHTindex); 
      #ifdef VVM_DEBUG
      print<uint32_t>::apply(LHTindex, "index%32"); 
      print<int32_t> ::apply(Vdst,     "data %32"); 
      #endif
   }
};

/******************************************************************************
* vcop_hist
*   This class implements histogram operations.              
*   Helper classes are incorporated via inheritance.
******************************************************************************/
template <typename type, int ntables, int npts, int dup, typename lut_id>
struct vcop_hist : 
   public LHT_base<type, ntables*dup, 1, lut_id>,
   public LHT_copy_in<dup, dup_zinit, LHT_permute<ntables, dup>, lut_id>,
   public LHT_copy_out<type, dup, LHT_permute<ntables, dup>, lut_id>
{
   /*--------------------------------------------------------------------------
   * hist_update() - perform a histogram operation
   *-------------------------------------------------------------------------*/
   static void hist_update(__int16& Vdst, __int16 Vindex)
   {
      __uint16 LHTindex = __as_uint16(Vindex);
      #ifdef VVM_DEBUG
      print<uint32_t>::apply(LHTindex, "index%32"); 
      #endif
      __hist(lut_id::op_lut_set, LHTindex); 
      // TODO: should return data vector
   }

   /*--------------------------------------------------------------------------
   * whist_update() - perform a weighted histogram operation
   *-------------------------------------------------------------------------*/
   static void whist_update(__int16& Vdst, __int16 Vindex, __int16 Vweight)
   {
      __uint16 LHTindex = __as_uint16(Vindex);
      #ifdef VVM_DEBUG
      print<uint32_t>::apply(LHTindex, "index %32"); 
      print<int32_t> ::apply(Vweight,  "weight%32"); 
      #endif
      __hist_weighted(lut_id::op_lut_set, Vweight, LHTindex); 
      // TODO: should return data vector
   }
};

/******************************************************************************
* Helper classes for lookup and histogram 
******************************************************************************/

/******************************************************************************
* LHT_base 
*   This class has common functionality to configure and enable the table
*   operations in L1D
******************************************************************************/
template <typename type, int nways, int npts, typename lut_id>
struct LHT_base
{
   /*--------------------------------------------------------------------------
   * enable() - initialization of LHT mechanism
   *-------------------------------------------------------------------------*/
   static void enable()
   {
      static bool enabled = false;
      if (!enabled)
      {
	 __LUT_SET_LTER(__LUT_ENABLE_0 | __LUT_ENABLE_1
                      | __LUT_ENABLE_2 | __LUT_ENABLE_3); 
	 enabled = true;
      }
      // LTBR's 0,1 will be asigned to operations; 2,3 to copying.
      // A maximum of two tables are allowed.  A second table will begin
      // 16K into L1.
      // Configure for table operations
      __LUT_SET_LTBR(lut_id::op_lut_set, lut_id::position); 
      // Configure for copy in/out
      __LUT_SET_LTBR(lut_id::copy_lut_set, lut_id::position); 
   }

   /*--------------------------------------------------------------------------
   * config() - configure LHT in L1D for lookup / histogram operation
   *-------------------------------------------------------------------------*/
   static uint32_t config()
   {
      enable(); 

      __sLTCRFlags_t LTCR;

      LTCR.INTERPOLATION = LHT_interp_flag<npts>::val;
      LTCR.SATURATION    = __LUT_SAT_ON;
      LTCR.SIGNUNSIGN    = LHT_signed_flag<type>::val;
      LTCR.WEIGHTSIZE    = LHT_wsize_flag<type>::val;
      LTCR.ELETYPE       = LHT_element_type_flag<type>::val;
      LTCR.PROMOTION     = LHT_promote_flag<type,int32_t>::val;
      LTCR.NUMTBLS       = LHT_ntable_flag<nways>::val;
      LTCR.TBLSIZE       = lut_id::size;

      return __lut_set_param(&LTCR);
   }

   /*--------------------------------------------------------------------------
   * open() - assign LHT config to LTCR
   *-------------------------------------------------------------------------*/
   static void open(int id, uint32_t config)
   {
       #ifdef VVM_DEBUG
       printf("set LTCR%d to %08x\n", id, config); 
       #endif
      __LUT_SET_LTCR(id, config); 
   }
}; 

/******************************************************************************
* LHT_copy_in_base
*   This class contains common operations for the copy-in operation. 
*   The copy-in operation copies source table data, from L2 in VCOP layout,
*   to L1D in 7x table layout. 
******************************************************************************/
template<typename lut_id>
struct LHT_copy_in_base
{
   /*--------------------------------------------------------------------------
   * copy_in_config() - 
   *    Configure LHT for initializing table from external memory to L1D
   *-------------------------------------------------------------------------*/
   static uint32_t copy_in_config()
   {
      __sLTCRFlags_t LTCR;

      LTCR.INTERPOLATION = __LUT_INTERP_OFF;
      LTCR.SATURATION    = __LUT_SAT_OFF;
      LTCR.WEIGHTSIZE    = __LUT_WSIZE_16BIT;
      LTCR.SIGNUNSIGN    = __LUT_UNSIGNED;
      LTCR.ELETYPE       = __LUT_ELETYPE_32BIT;
      LTCR.PROMOTION     = __LUT_PROMOTE_OFF;
      LTCR.NUMTBLS       = __LUT_NUM_TBL_1;
      LTCR.TBLSIZE       = lut_id::size;

      return __lut_set_param(&LTCR); 
   }

   /*--------------------------------------------------------------------------
   * copy_in_SE_config() 
   *    Configure streaming engine for reading table from external memory 
   *-------------------------------------------------------------------------*/
   static __SE_TEMPLATE_v1 copy_in_SE_config(uint32_t nbytes)
   {
      // round size up to next 128-byte boundary
      uint32_t table_size = ((nbytes + 127) / 128) * 128;
      uint32_t nwords     = table_size / 4;

      // Setup SE to read from VCOP source table. Data is read consecutively 
      // as 32-bit words into vectors, 16 words per read.
      __SE_TEMPLATE_v1 SE_Template = __gen_SE_TEMPLATE_v1();

      SE_Template.ICNT0  = nwords;
      SE_Template.VECLEN = __SE_VECLEN_16ELEMS;
      SE_Template.ELETYPE = __SE_ELETYPE_32BIT;
      return SE_Template;
   }
};

/******************************************************************************
* LHT_copy_in<> - specialization for dup = 1
*    This class implements the copy-in operation for the case of ntables-way
*    lookup, that is, the normal 8-way SIMD mode. 
******************************************************************************/
template <typename dup_init_helper, typename perm_helper, typename lut_id>
struct LHT_copy_in<1, dup_init_helper, perm_helper, lut_id> :
   public LHT_copy_in_base<lut_id>
{
   /*--------------------------------------------------------------------------
   * copy_table_in()
   *    Copy and rearrange table data from VCOP layout in external memory to 
   *    L1D in 7x layout. Nbytes is size of source table in L2. 
   *-------------------------------------------------------------------------*/
   static void copy_table_in(void* src, uint32_t nbytes, uint32_t LHT_setup, 
			     __SE_TEMPLATE_v1 SE_Template)
   {
      if (nbytes == 0) return;

      // setup LHT and SE using precomputed settings
      __LUT_SET_LTCR(lut_id::copy_lut_set, LHT_setup); 
      __SE1_OPEN((void*)src, SE_Template); 

      // round size up to next 128-byte boundary
      uint32_t table_size = ((nbytes + 127) / 128) * 128;
      uint32_t nlines     = table_size / 128;

      // Copy the data in 128-byte chunks. For each chunk:
      //    Use SE to read 2 64-byte vectors
      //    Rearrange according to table format (if needed)
      //    Write to L1D using 1-way LUTINIT (2 writes per line)
      uint32_t LHTindex = 0;
      for (uint32_t i = 0; i < nlines; ++i)
      {
	 // read from src memory
         __uint16 Vsrc0 = __SE1ADV(uint16); 
         __uint16 Vsrc1 = __SE1ADV(uint16); 

	 // rearrange 2x512b vectors into 1024b destination table format
         __uint16 LHTdata0, LHTdata1;
	 perm_helper::copy_in_perm(Vsrc0, Vsrc1, LHTdata0, LHTdata1); 

	 // write to table in L1D
	 __lookup_init(lut_id::copy_lut_set, LHTdata0, LHTindex); 
         LHTindex += 16; 

	 __lookup_init(lut_id::copy_lut_set, LHTdata1, LHTindex); 
         LHTindex += 16; 

	 #ifdef VVM_DEBUG
	 printf("data for index %d\n", LHTindex - 32); 
	 print<uint32_t, 16>::apply(Vsrc0, "src %32"); 
	 print<uint32_t, 16>::apply(LHTdata0, "perm%32"); 
	 printf("data for index %d\n", LHTindex - 16); 
	 print<uint32_t, 16>::apply(Vsrc1, "src %32"); 
	 print<uint32_t, 16>::apply(LHTdata1, "perm%32"); 
	 #endif
      }

      __SE1_CLOSE();
   }

   static void copy_table_in(void* src, uint32_t nbytes, uint32_t LHT_setup)
   {
      __SE_TEMPLATE_v1 SE_Template =LHT_copy_in_base<lut_id>::copy_in_SE_config(nbytes);
      copy_table_in(src, nbytes, LHT_setup, SE_Template);
   }
};

/******************************************************************************
* LHT_copy_in<> - specialization for dup = 2
*    This class implements the copy-in operation for the case of 2*ntables-way
*    lookup, that is, for 16-way SIMD mode.  In this mode, the source table
*    is duplicated by 2x in L1D, for double-wide lookup.  For the histogram
*    case the second table is zero-initialized; this is controlled by the
*    dup_init_helper policy class.
******************************************************************************/
template <typename dup_init_helper, typename perm_helper, typename lut_id>
struct LHT_copy_in<2, dup_init_helper, perm_helper, lut_id> :
   public LHT_copy_in_base<lut_id>
{
   /*--------------------------------------------------------------------------
   * copy_table_in() - 2x duplication
   *    Copy and rearrange table data from VCOP layout in external memory to 
   *    L1D in 7x layout. Nbytes is size of source table in L2. 
   *-------------------------------------------------------------------------*/
   static void copy_table_in(void* src, uint32_t nbytes, uint32_t LHT_setup, 
			     __SE_TEMPLATE_v1 SE_Template)
   {
      if (nbytes == 0) return;

      // setup LHT and SE using precomputed settings
      __LUT_SET_LTCR(lut_id::copy_lut_set, LHT_setup); 
      __SE1_OPEN((void*)src, SE_Template); 

      // round size up to next 64-byte boundary
      uint32_t table_size = ((nbytes + 63) / 64) * 64;
      uint32_t nlines     = table_size / 64;

      // Copy the data in 64-byte chunks. For each chunk:
      //    Use SE to read 1 64-byte vector
      //    Rearrange according to table format (if needed)
      //    Write to L1D using 1-way LUTINIT (2 duplicate writes per line)
      uint32_t LHTindex = 0;
      for (uint32_t i = 0; i < nlines; ++i)
      {
	 // read from src memory
	 __uint16 Vsrc0 = __SE1ADV(uint16); 

	 // rearrange 512b vector into 512b destination table format
	 __uint16 LHTdata0, LHTdata1; 
	 perm_helper::copy_in_perm(Vsrc0, LHTdata0); 

	 // write to 1st duplicate table in L1D
	 __lookup_init(lut_id::copy_lut_set, LHTdata0, LHTindex); 
	 LHTindex += 16; 

	 // data for 2nd duplicate table is either a copy (for lookup),  
	 // or zero (for histogram)
	 dup_init_helper::duplicate_data(LHTdata0, LHTdata1); 
	 __lookup_init(lut_id::copy_lut_set, LHTdata1, LHTindex); 
	 LHTindex += 16; 

 	 #ifdef VVM_DEBUG
	 printf("data for index %d\n", LHTindex - 32); 
	 print<uint32_t, 16>::apply(Vsrc0, "src %32"); 
	 print<uint32_t, 16>::apply(LHTdata0, "perm%32"); 
	 printf("data for index %d\n", LHTindex - 16); 
	 print<uint32_t, 16>::apply(LHTdata1, "perm%32"); 
	 #endif
      }
      __SE1_CLOSE();
   }
};

/******************************************************************************
* LHT_copy_out_base
*   This class contains common operations for the copy-out operation. 
*   The copy-out operation copies histogram result data, from L1D in 7x layout,
*   to L2 in VCOP layout. 
******************************************************************************/
template<typename lut_id>
struct LHT_copy_out_base
{
   /*--------------------------------------------------------------------------
   * copy_out_config()
   *    Configure LHT for writing updated hist table from L1D to external 
   *    memory
   *-------------------------------------------------------------------------*/
   static uint32_t copy_out_config()
   {
      // setup to read as 16 parallel tables
      __sLTCRFlags_t LTCR;

      LTCR.INTERPOLATION = __LUT_INTERP_OFF;
      LTCR.SATURATION    = __LUT_SAT_OFF;
      LTCR.WEIGHTSIZE    = __LUT_WSIZE_16BIT;
      LTCR.SIGNUNSIGN    = __LUT_UNSIGNED;
      LTCR.ELETYPE       = __LUT_ELETYPE_32BIT;
      LTCR.PROMOTION     = __LUT_PROMOTE_OFF;
      LTCR.NUMTBLS       = __LUT_NUM_TBL_16;
      LTCR.TBLSIZE       = lut_id::size;

      return __lut_set_param(&LTCR); 
   }

   /*--------------------------------------------------------------------------
   * copy_out_SA_config()
   *    Configure streaming address genererator for writing table from L1D to
   *    external memory
   *-------------------------------------------------------------------------*/
   static __SA_TEMPLATE_v1 copy_out_SA_config(uint32_t nbytes)
   {
      // Setup SA to write back to L2.  Data is written consecutively as bytes.
      __SA_TEMPLATE_v1 SA_Template = __gen_SA_TEMPLATE_v1();

      SA_Template.ICNT0  = nbytes;
      SA_Template.VECLEN = __SA_VECLEN_64ELEMS;
      return SA_Template;
   }
};

/******************************************************************************
* LHT_copy_out<> - specialization for dup = 1
*    This class implements the copy-out operation for the case of ntables-way
*    histogram, that is, the normal 8-way SIMD mode. 
******************************************************************************/
template <typename type, typename perm_helper, typename lut_id>
struct LHT_copy_out<type, 1, perm_helper, lut_id> :
   public LHT_copy_out_base<lut_id>
{
   /*--------------------------------------------------------------------------
   * copy_table_out() - 
   *    Copy histogram table data from L1D to external memory and rearrange
   *    to VCOP layout 
   *-------------------------------------------------------------------------*/
   static void copy_table_out(void* dst, uint32_t nbytes, uint32_t LHT_setup,
                              __SA_TEMPLATE_v1 SA_Template)
   {
      if (nbytes == 0) return;

      // round size up to next 128-byte boundary
      uint32_t table_size = ((nbytes + 127) / 128) * 128;
      uint32_t nlines     = table_size / 128;

      __LUT_SET_LTCR(lut_id::copy_lut_set, LHT_setup); 

      // Copy the data in 128-byte chunks. For each chunk:
      //    Use LUTRD to read 2 64-byte vectors
      //    Rearrange for VCOP table format 
      //    Store to external memory (2 writes per line)
      __uint16* out = (__uint16*)dst;
      __uint16  LHTindex = (__uint16)(0); 

      __SA0_OPEN(SA_Template);

      for (uint32_t i = 0; i < nlines; ++i)
      {
	 __uint16 LHTdata0, LHTdata1;
	 
	 LHTdata0 = __lookup_read_uint(lut_id::copy_lut_set, LHTindex); 
	 ++LHTindex;

	 LHTdata1 = __lookup_read_uint(lut_id::copy_lut_set, LHTindex); 
	 ++LHTindex;

	 // rearrange according to table format
         __uint16 Vdst0, Vdst1; 
	 perm_helper::copy_out_perm(LHTdata0, LHTdata1, Vdst0, Vdst1); 

	 // write to dst memory
         vpred pred = __SA0_VPRED(uchar64);
         __vstore_pred(pred, __SA0ADV(uchar64, out), __as_uchar64(Vdst0));
         pred = __SA0_VPRED(uchar64);
         __vstore_pred(pred, __SA0ADV(uchar64, out), __as_uchar64(Vdst1));

	 #ifdef VVM_DEBUG
	 printf("write data for index %d\n", LHTindex.s0 - 2); 
	 print<uint32_t,16>::apply(LHTdata0, "%32"); 
	 printf("write data for index %d\n", LHTindex.s0 - 1); 
	 print<uint32_t,16>::apply(LHTdata1, "%32"); 
	 #endif
      }

      __SA0_CLOSE();
   }

   static void copy_table_out(void *dst, uint32_t nbytes, uint32_t LHT_setup)
   {
      __SA_TEMPLATE_v1 SA_Template =
                      LHT_copy_out_base<lut_id>::copy_out_SA_config(nbytes);
      return copy_table_out(dst, nbytes, LHT_setup, SA_Template);
   }
};

/******************************************************************************
* LHT_copy_out<> - specialization for dup = 2
*    This class implements the copy-out operation for the case of 2*ntables-way
*    lookup, that is, for 16-way SIMD mode.  In this mode, the table layout 
*    is duplicated by 2x in L1D. The duplicate ways must be combined by
*    adding them together, then rearranged according to VCOP layout and 
*    written to L2. 
******************************************************************************/
template <typename type, typename perm_helper, typename lut_id>
struct LHT_copy_out<type, 2, perm_helper, lut_id> :
   public LHT_copy_out_base<lut_id>
{
   /*--------------------------------------------------------------------------
   * copy_table_out() - 2x duplication
   *    Copy histogram table data from L1D to external memory and rearrange
   *    to VCOP layout 
   *-------------------------------------------------------------------------*/
   static void copy_table_out(void* dst, uint32_t nbytes, uint32_t LHT_setup,
                              __SA_TEMPLATE_v1 SA_Template)
   {
      // vector of original element types
      typedef typename vector<type, 64/sizeof(type)>::type vtype;

      if (nbytes == 0) return;

      // round size up to next 64-byte boundary
      uint32_t table_size = ((nbytes + 63) / 64) * 64;
      uint32_t nlines     = table_size / 64;

      __LUT_SET_LTCR(lut_id::copy_lut_set, LHT_setup); 

      // Copy the data in 64-byte chunks. For each chunk:
      //    Use LUTRD to read 2 64-byte vectors from the duplicated tables
      //    Rearrange for VCOP table format 
      //    Add mirrored elements from duplicated tables together
      //    Store to external memory (1 write per line)
      vtype*   out      = (vtype*)dst;
      __uint16 LHTindex = (__uint16)(0); 

      __SA0_OPEN(SA_Template);

      for (uint32_t i = 0; i < nlines; ++i)
      {
	 // read from table
	 __uint16 LHTdata0, LHTdata1;
	 
	 LHTdata0 = __lookup_read_uint(lut_id::copy_lut_set, LHTindex); 
	 ++LHTindex;

	 LHTdata1 = __lookup_read_uint(lut_id::copy_lut_set, LHTindex); 
	 ++LHTindex;

	 // rearrange so each vector has data from one duplicated table
         __uint16 Vdst0, Vdst1; 
	 perm_helper::copy_out_perm(LHTdata0, LHTdata1, Vdst0, Vdst1); 

	 // add mirrored elements
	 // since values represent hist results, use same saturation as hist
	 vtype Vdata0 = as_type(vtype, Vdst0); 
	 vtype Vdata1 = as_type(vtype, Vdst1); 
	 Vdata0       = __add_sat(Vdata0, Vdata1); 

	 // write to dst memory
         vpred pred = __SA0_VPRED(uchar64);
         __vstore_pred(pred, __SA0ADV(uchar64, out), __as_uchar64(Vdata0));
      }

      __SA0_CLOSE();
   }
   
   static void copy_table_out(void *dst, uint32_t nbytes, uint32_t LHT_setup)
   {
      __SA_TEMPLATE_v1 SA_Template =
                          LHT_copy_out_base<lut_id>::copy_out_SA_config(nbytes);
      copy_table_out(dst, nbytes, LHT_setup, SA_Template);
   }
};

/******************************************************************************
* Policy classes for copy-in duplication
*    For table lookup, the source data is duplicated into the second N ways
*    of the L1D table. 
*    For histogram, the second N ways are initialized to zero (to avoid
*    doubling the initial values when the table is added together). 
******************************************************************************/
struct dup_copy   // for lookup
{ 
   static void duplicate_data(__uint16 src_data, __uint16& dup_data)
      { dup_data = src_data; } 
};

struct dup_zinit  // for hist
{ 
   static void duplicate_data(__uint16 src_data, __uint16& dup_data)
      { dup_data = (__uint16)0; }
};

/******************************************************************************
* LHT_permute class 
*    Implements table layout rearrangement between VCOP and 7x layouts
*    for copy-in and copy-out operations.
*      - VCOP layout: each line contains 8 banks of 4 bytes each
*      - 7x layout: each line contains 16 banks of 8 bytes each
*      - The banks are divided into N tables
*      - Data from the N tables is interleaved into the lines by way
*      - Because the banks (therefore the ways) are different sizes, the 
*        interleaving factor changes 
*      - Layout transformations are detailed in the spreadsheet
* 
*    The API is:
*        LHT_permute<ntables>::copy_in_perm()
*            Vsrc0, Vsrc1: 128bytes of VCOP-format table data (4 lines)
*            Vdst0, Vdst1: 128bytes of 7x-format table data (1 line)
*        LHT_permute<ntables>::copy_out_perm()
*            Vsrc0, Vsrc1: 128bytes of 7x-format table data (1 line)
*            Vdst0, Vdst1: 128bytes of VCOP-format table data (4 lines)
******************************************************************************/
// 1 table, no duplication
template<> struct LHT_permute<1,1>
{
   static void copy_in_perm(__uint16  Vsrc0, __uint16  Vsrc1, 
                            __uint16& Vdst0, __uint16& Vdst1)
   {
      // no permute needed for single linear table
      Vdst0 = Vsrc0; 
      Vdst1 = Vsrc1; 
   }

   static void copy_out_perm(__uint16  Vsrc0, __uint16 Vsrc1, 
                             __uint16& Vdst0, __uint16& Vdst1)
   {
      static const __uchar permstr_out[] =
	 "\x00\x01\x02\x03\x20\x21\x22\x23\x04\x05\x06\x07\x24\x25\x26\x27"
	 "\x08\x09\x0A\x0B\x28\x29\x2A\x2B\x0C\x0D\x0E\x0F\x2C\x2D\x2E\x2F"
	 "\x10\x11\x12\x13\x30\x31\x32\x33\x14\x15\x16\x17\x34\x35\x36\x37"
	 "\x18\x19\x1A\x1B\x38\x39\x3A\x3B\x1C\x1D\x1E\x1F\x3C\x3D\x3E\x3F";

      __uchar64 perm = *(__uchar64*)permstr_out;
      __uchar64 Vdata0 = __as_uchar64(Vsrc0); 
      __uchar64 Vdata1 = __as_uchar64(Vsrc1); 

      Vdst0 = __as_uint16(__vpermll_yvvv(perm, Vdata1, Vdata0)); 
      Vdst1 = __as_uint16(__vpermhh_yvvv(perm, Vdata1, Vdata0)); 
   }
};

// 2 tables, no duplication
template<> struct LHT_permute<2,1>
{
   static void copy_in_perm(__uint16  Vsrc0, __uint16  Vsrc1, 
                            __uint16& Vdst0, __uint16& Vdst1)
   {
      static const __uchar permstr[] = 
	 "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
	 "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F"
	 "\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F"
	 "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F";

      __uchar64 perm   = *(__uchar64*)permstr;
      __uchar64 Vdata0 = __as_uchar64(Vsrc0); 
      __uchar64 Vdata1 = __as_uchar64(Vsrc1); 

      Vdst0 = __as_uint16(__vpermeeq_yvvv(perm, Vdata1, Vdata0)); 
      Vdst1 = __as_uint16(__vpermooq_yvvv(perm, Vdata1, Vdata0)); 
   }

   static void copy_out_perm(__uint16  Vsrc0, __uint16  Vsrc1, 
                             __uint16& Vdst0, __uint16& Vdst1)
   {
      static const __uchar permstr[] = 
	 "\x00\x01\x02\x03\x20\x21\x22\x23\x04\x05\x06\x07\x24\x25\x26\x27"
	 "\x10\x11\x12\x13\x30\x31\x32\x33\x14\x15\x16\x17\x34\x35\x36\x37"
	 "\x08\x09\x0A\x0B\x28\x29\x2A\x2B\x0C\x0D\x0E\x0F\x2C\x2D\x2E\x2F"
	 "\x18\x19\x1A\x1B\x38\x39\x3A\x3B\x1C\x1D\x1E\x1F\x3C\x3D\x3E\x3F";	

      __uchar64 perm   = *(__uchar64*)permstr;
      __uchar64 Vdata0 = __as_uchar64(Vsrc0); 
      __uchar64 Vdata1 = __as_uchar64(Vsrc1); 

      Vdst0 = __as_uint16(__vpermeeq_yvvv(perm, Vdata1, Vdata0)); 
      Vdst1 = __as_uint16(__vpermooq_yvvv(perm, Vdata1, Vdata0)); 
   }
};

// 4 tables, no duplication
template<> struct LHT_permute<4,1>
{
   static void copy_in_perm(__uint16  Vsrc0, __uint16  Vsrc1, 
                            __uint16& Vdst0, __uint16& Vdst1)
   {
      static const __uchar permstr[] = 
	 "\x00\x01\x02\x03\x04\x05\x06\x07\x10\x11\x12\x13\x14\x15\x16\x17"
	 "\x20\x21\x22\x23\x24\x25\x26\x27\x30\x31\x32\x33\x34\x35\x36\x37"
	 "\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F"
	 "\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F";

      __uchar64 perm   = *(__uchar64*)permstr;
      __uchar64 Vdata0 = __as_uchar64(Vsrc0); 
      __uchar64 Vdata1 = __as_uchar64(Vsrc1); 

      Vdst0 = __as_uint16(__vpermeeq_yvvv(perm, Vdata1, Vdata0)); 
      Vdst1 = __as_uint16(__vpermooq_yvvv(perm, Vdata1, Vdata0)); 
   }

   static void copy_out_perm(__uint16  Vsrc0, __uint16  Vsrc1, 
                             __uint16& Vdst0, __uint16& Vdst1)
   {
      static const __uchar permstr[] =
	 "\x00\x01\x02\x03\x20\x21\x22\x23\x08\x09\x0A\x0B\x28\x29\x2A\x2B"
	 "\x10\x11\x12\x13\x30\x31\x32\x33\x18\x19\x1A\x1B\x38\x39\x3A\x3B"
	 "\x04\x05\x06\x07\x24\x25\x26\x27\x0C\x0D\x0E\x0F\x2C\x2D\x2E\x2F"
	 "\x14\x15\x16\x17\x34\x35\x36\x37\x1C\x1D\x1E\x1F\x3C\x3D\x3E\x3F";

      __uchar64 perm   = *(__uchar64*)permstr;
      __uchar64 Vdata0 = __as_uchar64(Vsrc0); 
      __uchar64 Vdata1 = __as_uchar64(Vsrc1); 

      Vdst0 = __as_uint16(__vpermeed_yvvv(perm, Vdata1, Vdata0)); 
      Vdst1 = __as_uint16(__vpermood_yvvv(perm, Vdata1, Vdata0)); 
   }
};

// 8 tables, no duplication
template<> struct LHT_permute<8,1>
{
   static void copy_in_perm(__uint16  Vsrc0, __uint16  Vsrc1, 
                            __uint16& Vdst0, __uint16& Vdst1)
   {
      static const __uchar permstr[] = 
	 "\x00\x01\x02\x03\x10\x11\x12\x13\x20\x21\x22\x23\x30\x31\x32\x33"
	 "\x04\x05\x06\x07\x14\x15\x16\x17\x24\x25\x26\x27\x34\x35\x36\x37"
	 "\x08\x09\x0A\x0B\x18\x19\x1A\x1B\x28\x29\x2A\x2B\x38\x39\x3A\x3B"
	 "\x0C\x0D\x0E\x0F\x1C\x1D\x1E\x1F\x2C\x2D\x2E\x2F\x3C\x3D\x3E\x3F";

      __uchar64 perm   = *(__uchar64*)permstr;
      __uchar64 Vdata0 = __as_uchar64(Vsrc0); 
      __uchar64 Vdata1 = __as_uchar64(Vsrc1); 

      Vdst0 = __as_uint16(__vpermeeq_yvvv(perm, Vdata1, Vdata0)); 
      Vdst1 = __as_uint16(__vpermooq_yvvv(perm, Vdata1, Vdata0)); 
   }
   static void copy_out_perm(__uint16  Vsrc0, __uint16  Vsrc1, 
                             __uint16& Vdst0, __uint16& Vdst1)
   {
      static const __uchar permstr[] = 
	 "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
	 "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F"
	 "\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F"
	 "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F";

      __uchar64 perm   = *(__uchar64*)permstr;
      __uchar64 Vdata0 = __as_uchar64(Vsrc0); 
      __uchar64 Vdata1 = __as_uchar64(Vsrc1); 

      Vdst0 = __as_uint16(__vpermeew_yvvv(perm, Vdata1, Vdata0));
      Vdst1 = __as_uint16(__vpermoow_yvvv(perm, Vdata1, Vdata0));
   }
};

// 16 tables, no duplication
template<> struct LHT_permute<16,1>
{
   static void copy_in_perm(__uint16  Vsrc0, __uint16  Vsrc1, 
                            __uint16& Vdst0, __uint16& Vdst1)
   {
      static const __uchar permstr[] = 
	 "\x00\x01\x02\x03\x20\x21\x22\x23\x04\x05\x06\x07\x24\x25\x26\x27"
	 "\x08\x09\x0A\x0B\x28\x29\x2A\x2B\x0C\x0D\x0E\x0F\x2C\x2D\x2E\x2F"
	 "\x10\x11\x12\x13\x30\x31\x32\x33\x14\x15\x16\x17\x34\x35\x36\x37"
	 "\x18\x19\x1A\x1B\x38\x39\x3A\x3B\x1C\x1D\x1E\x1F\x3C\x3D\x3E\x3F";

      __uchar64 perm   = *(__uchar64*)permstr;
      __uchar64 Vdata0 = __as_uchar64(Vsrc0); 
      __uchar64 Vdata1 = __as_uchar64(Vsrc1); 

      Vdst0 = __as_uint16(__vpermll_yvvv(perm, Vdata1, Vdata0)); 
      Vdst1 = __as_uint16(__vpermhh_yvvv(perm, Vdata1, Vdata0)); 
   }
   static void copy_out_perm(__uint16  Vsrc0, __uint16  Vsrc1, 
                             __uint16& Vdst0, __uint16& Vdst1)
   {
      Vdst0 = Vsrc0;
      Vdst1 = Vsrc1;
   }
};

// 1 table, 2x duplication
template<> struct LHT_permute<1,2>
{
   static void copy_in_perm(__uint16 Vsrc0, __uint16& Vdst0)
   {
      // no permute needed for single linear table
      Vdst0 = Vsrc0; 
   }
   static void copy_out_perm(__uint16  Vsrc0, __uint16  Vsrc1, 
                             __uint16& Vdst0, __uint16& Vdst1)
   {
      static const __uchar permstr[] =
	 "\x00\x01\x02\x03\x20\x21\x22\x23\x04\x05\x06\x07\x24\x25\x26\x27"
	 "\x08\x09\x0A\x0B\x28\x29\x2A\x2B\x0C\x0D\x0E\x0F\x2C\x2D\x2E\x2F"
	 "\x10\x11\x12\x13\x30\x31\x32\x33\x14\x15\x16\x17\x34\x35\x36\x37"
	 "\x18\x19\x1A\x1B\x38\x39\x3A\x3B\x1C\x1D\x1E\x1F\x3C\x3D\x3E\x3F";

      __uchar64 perm   = *(__uchar64*)permstr;
      __uchar64 Vdata0 = __as_uchar64(Vsrc0); 
      __uchar64 Vdata1 = __as_uchar64(Vsrc1); 

      Vdst0 = __as_uint16(__vpermll_yvvv(perm, Vdata1, Vdata0)); 
      Vdst1 = __as_uint16(__vpermhh_yvvv(perm, Vdata1, Vdata0)); 
   }
};

// 2 tables, 2x duplication
template<> struct LHT_permute<2,2>
{
   static void copy_in_perm(__uint16 Vsrc0, __uint16& Vdst0)
   {
      static const __uchar permstr[] = 
	 "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
	 "\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F"
	 "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F"
	 "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F";

      __uchar64 perm   = *(__uchar64*)permstr;
      __uchar64 Vdata0 = __as_uchar64(Vsrc0); 

      Vdst0 = __as_uint16(__vperm_vvv(perm, Vdata0)); 
   }
   static void copy_out_perm(__uint16  Vsrc0, __uint16  Vsrc1,
                             __uint16& Vdst0, __uint16& Vdst1)
   {
      static const __uchar permstr[] = 
	 "\x00\x01\x02\x03\x20\x21\x22\x23\x04\x05\x06\x07\x24\x25\x26\x27"
	 "\x10\x11\x12\x13\x30\x31\x32\x33\x14\x15\x16\x17\x34\x35\x36\x37"
	 "\x08\x09\x0A\x0B\x28\x29\x2A\x2B\x0C\x0D\x0E\x0F\x2C\x2D\x2E\x2F"
	 "\x18\x19\x1A\x1B\x38\x39\x3A\x3B\x1C\x1D\x1E\x1F\x3C\x3D\x3E\x3F";

      __uchar64 perm   = *(__uchar64*)permstr;
      __uchar64 Vdata0 = __as_uchar64(Vsrc0); 
      __uchar64 Vdata1 = __as_uchar64(Vsrc1); 

      Vdst0 = __as_uint16(__vpermll_yvvv(perm, Vdata1, Vdata0)); 
      Vdst1 = __as_uint16(__vpermhh_yvvv(perm, Vdata1, Vdata0)); 
   }
};

// 4 tables, 2x duplication
template<> struct LHT_permute<4,2>
{
   static void copy_in_perm(__uint16 Vsrc0, __uint16& Vdst0)
   {
      static const __uchar permstr[] = 
	 "\x00\x01\x02\x03\x04\x05\x06\x07\x20\x21\x22\x23\x24\x25\x26\x27"
	 "\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F"
	 "\x10\x11\x12\x13\x14\x15\x16\x17\x30\x31\x32\x33\x34\x35\x36\x37"
	 "\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F";

      __uchar64 perm   = *(__uchar64*)permstr;
      __uchar64 Vdata0 = __as_uchar64(Vsrc0); 

      Vdst0 = __as_uint16(__vperm_vvv(perm, Vdata0)); 
   }
   static void copy_out_perm(__uint16  Vsrc0, __uint16  Vsrc1,
                             __uint16& Vdst0, __uint16& Vdst1)
   {
      static const __uchar permstr[] = 
	 "\x00\x01\x02\x03\x20\x21\x22\x23\x08\x09\x0A\x0B\x28\x29\x2A\x2B"
	 "\x10\x11\x12\x13\x30\x31\x32\x33\x18\x19\x1A\x1B\x38\x39\x3A\x3B"
	 "\x04\x05\x06\x07\x24\x25\x26\x27\x0C\x0D\x0E\x0F\x2C\x2D\x2E\x2F"
	 "\x14\x15\x16\x17\x34\x35\x36\x37\x1C\x1D\x1E\x1F\x3C\x3D\x3E\x3F";

      __uchar64 perm   = *(__uchar64*)permstr;
      __uchar64 Vdata0 = __as_uchar64(Vsrc0); 
      __uchar64 Vdata1 = __as_uchar64(Vsrc1); 

      Vdst0 = __as_uint16(__vpermll_yvvv(perm, Vdata1, Vdata0)); 
      Vdst1 = __as_uint16(__vpermhh_yvvv(perm, Vdata1, Vdata0)); 
   }
};

// 8 tables, 2x duplication
template<> struct LHT_permute<8,2>
{
   static void copy_in_perm(__uint16  Vsrc0, __uint16& Vdst0)
   {
      static const __uchar permstr[] =
	 "\x00\x01\x02\x03\x20\x21\x22\x23\x04\x05\x06\x07\x24\x25\x26\x27"
	 "\x08\x09\x0A\x0B\x28\x29\x2A\x2B\x0C\x0D\x0E\x0F\x2C\x2D\x2E\x2F"
	 "\x10\x11\x12\x13\x30\x31\x32\x33\x14\x15\x16\x17\x34\x35\x36\x37"
	 "\x18\x19\x1A\x1B\x38\x39\x3A\x3B\x1C\x1D\x1E\x1F\x3C\x3D\x3E\x3F";

      __uchar64 perm   = *(__uchar64*)permstr;
      __uchar64 Vdata0 = __as_uchar64(Vsrc0); 

      Vdst0 = __as_uint16(__vperm_vvv(perm, Vdata0)); 
   }
   static void copy_out_perm(__uint16  Vsrc0, __uint16  Vsrc1,
                             __uint16& Vdst0, __uint16& Vdst1)
   {
      static const __uchar permstr[] = 
	 "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
	 "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F"
	 "\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F"
	 "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F";

      __uchar64 perm   = *(__uchar64*)permstr;
      __uchar64 Vdata0 = __as_uchar64(Vsrc0); 
      __uchar64 Vdata1 = __as_uchar64(Vsrc1); 

      Vdst0 = __as_uint16(__vpermll_yvvv(perm, Vdata1, Vdata0)); 
      Vdst1 = __as_uint16(__vpermhh_yvvv(perm, Vdata1, Vdata0)); 
   }
};

/*--------------------------------------------------------------------------
* LHT_signed_flag() - given element type, return signed flag
*-------------------------------------------------------------------------*/
template <> struct LHT_signed_flag<int8_t>
   { static const int val = __LUT_SIGNED; };
template <> struct LHT_signed_flag<uint8_t>
   { static const int val = __LUT_UNSIGNED; };
template <> struct LHT_signed_flag<int16_t>
   { static const int val = __LUT_SIGNED; };
template <> struct LHT_signed_flag<uint16_t>
   { static const int val = __LUT_UNSIGNED; };
template <> struct LHT_signed_flag<int32_t>
   { static const int val = __LUT_SIGNED; };
template <> struct LHT_signed_flag<uint32_t>
   { static const int val = __LUT_UNSIGNED; };

/*--------------------------------------------------------------------------
* LHT_element_type_flag() - given element type, return flag
*-------------------------------------------------------------------------*/
template <> struct LHT_element_type_flag<int8_t>
   { static const int val = __LUT_ELETYPE_8BIT; };
template <> struct LHT_element_type_flag<uint8_t>
   { static const int val = __LUT_ELETYPE_8BIT; };
template <> struct LHT_element_type_flag<int16_t>
   { static const int val = __LUT_ELETYPE_16BIT; };
template <> struct LHT_element_type_flag<uint16_t>
   { static const int val = __LUT_ELETYPE_16BIT; };
template <> struct LHT_element_type_flag<int32_t>
   { static const int val = __LUT_ELETYPE_32BIT; };
template <> struct LHT_element_type_flag<uint32_t>
   { static const int val = __LUT_ELETYPE_32BIT; };

/*-----------------------------------------------------------------------------
* LHT_promote_flag - given src and dst type, return LHT promote flag
*----------------------------------------------------------------------------*/
template <typename memtype, typename regtype> struct LHT_promote_flag;
template <> struct LHT_promote_flag<int8_t, int32_t>
   { static const int val = __LUT_PROMOTE_4X; };
template <> struct LHT_promote_flag<uint8_t, int32_t>
   { static const int val = __LUT_PROMOTE_4X; };
template <> struct LHT_promote_flag<int16_t, int32_t>
   { static const int val = __LUT_PROMOTE_2X; };
template <> struct LHT_promote_flag<uint16_t, int32_t>
   { static const int val = __LUT_PROMOTE_2X; };
template <> struct LHT_promote_flag<int32_t, int32_t>
   { static const int val = __LUT_PROMOTE_OFF; };
template <> struct LHT_promote_flag<uint32_t, int32_t>
   { static const int val = __LUT_PROMOTE_OFF; };

/*--------------------------------------------------------------------------
* LHT_ntable_flag() - convert ntables to LTCR flag
*-------------------------------------------------------------------------*/
template <> struct LHT_ntable_flag<1>
   { static const int val = __LUT_NUM_TBL_1; }; 
template <> struct LHT_ntable_flag<2>
   { static const int val = __LUT_NUM_TBL_2; }; 
template <> struct LHT_ntable_flag<4>
   { static const int val = __LUT_NUM_TBL_4; }; 
template <> struct LHT_ntable_flag<8>
   { static const int val = __LUT_NUM_TBL_8; }; 
template <> struct LHT_ntable_flag<16>
   { static const int val = __LUT_NUM_TBL_16; }; 

/*--------------------------------------------------------------------------
* LHT_interp_flag() - convert npts to LTCR INTERP flag
*-------------------------------------------------------------------------*/
template <> struct LHT_interp_flag<1>
   { static const int val = __LUT_INTERP_OFF; }; 
template <> struct LHT_interp_flag<2>
   { static const int val = __LUT_INTERP_2X; }; 
template <> struct LHT_interp_flag<4>
   { static const int val = __LUT_INTERP_4X; }; 
template <> struct LHT_interp_flag<8>
   { static const int val = __LUT_INTERP_8X; }; 

/*--------------------------------------------------------------------------
* LHT_wsize_flag() - given element type, return weight size flag
*-------------------------------------------------------------------------*/
template <> struct LHT_wsize_flag<int8_t>
   { static const int val = __LUT_WSIZE_8BIT; };
template <> struct LHT_wsize_flag<uint8_t>
   { static const int val = __LUT_WSIZE_8BIT; };
template <> struct LHT_wsize_flag<int16_t>
   { static const int val = __LUT_WSIZE_16BIT; };
template <> struct LHT_wsize_flag<uint16_t>
   { static const int val = __LUT_WSIZE_16BIT; };
template <> struct LHT_wsize_flag<int32_t>
   { static const int val = __LUT_WSIZE_16BIT; };
template <> struct LHT_wsize_flag<uint32_t>
   { static const int val = __LUT_WSIZE_16BIT; };

#if 0
/*--------------------------------------------------------------------------
* vcop_offset() - 
*    return offset of an element in a VCOP source table - for serial copy
*-------------------------------------------------------------------------*/
template <typename elem_type, int ntables, int nbanks, int banksz>
uint32_t elem_offset(uint32_t table, uint32_t index);

static uint32_t vcop_offset(uint32_t table, uint32_t index)
{
   static const int VCOP_NBANKS = 8;
   static const int VCOP_BANKSZ = 4;
   return elem_offset<type, ntables, VCOP_NBANKS, VCOP_BANKSZ>(table, index); 
}

/*-----------------------------------------------------------------------------
* elem_offset() - helper function for serial copy
*   For parallel lookup tables interleaved among memory banks, 
*   return offset of single element

*   |<---banksz-->|<---banksz-->|<---banksz-->|<---banksz-->| ...  x nbanks
*   |<------- table 0 --------->|<------ table 1 ---------->| ...  x ntables
*   | t0[0] t0[1] | t0[2] t0[3] | t1[0] t1[1] | t1[2] t1[3] | ...
*   | t0[4] t0[5] | t0[6] t0[7] | t1[4] t1[5] | t1[6] t1[7] | ...
*----------------------------------------------------------------------------*/
template <typename elem_type, int ntables, int nbanks, int banksz>
uint32_t elem_offset(uint32_t table, uint32_t index)
{
   static const uint32_t row_width = nbanks * banksz;
   static const uint32_t table_width = row_width / ntables;
   uint32_t  table_offset = index * sizeof(elem_type); 
   uint32_t  row_index = table_offset / table_width;
   uint32_t  row_offset = table_offset % table_width;

   uint32_t result = (row_index * row_width) 
                   + (table * table_width) + row_offset;

   #ifdef VVM_DEBUG
   printf("elem offset(table=%d, i=%d): "
          "rw=%d tw=%d to=%d ri=%d ro=%d result=%d\n",
          table, index, row_width, table_width, table_offset, 
	  row_index, row_offset, result); 
   #endif

   return result;
}
#endif

}  // namespace VCOP_VM
