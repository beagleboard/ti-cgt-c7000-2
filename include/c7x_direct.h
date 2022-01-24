/*****************************************************************************/
/*  C7X_DIRECT.H                                                             */
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

#ifndef __C7X_DIRECT_H
#define __C7X_DIRECT_H

/*****************************************************************************/
/* Deprecated API names                                                      */
/*       OLD                 NEW                                             */
/*****************************************************************************/
#define  __vdsortdd16h_vv    __vdsortddh_vv
#define  __vdsortddu16h_vv   __vdsortdduh_vv
#define  __vdsortdi16h_vv    __vdsortdih_vv
#define  __vdsortdiu16h_vv   __vdsortdiuh_vv
#define  __vdsortid16h_vv    __vdsortidh_vv
#define  __vdsortidu16h_vv   __vdsortiduh_vv
#define  __vdsortii16h_vv    __vdsortiih_vv
#define  __vdsortiiu16h_vv   __vdsortiiuh_vv
#define  __vdsortpdd16h_vv   __vdsortpddh_vv
#define  __vdsortpddu16h_vv  __vdsortpdduh_vv
#define  __vdsortpdi16h_vv   __vdsortpdih_vv
#define  __vdsortpdiu16h_vv  __vdsortpdiuh_vv
#define  __vdsortpid16h_vv   __vdsortpidh_vv
#define  __vdsortpidu16h_vv  __vdsortpiduh_vv
#define  __vdsortpii16h_vv   __vdsortpiih_vv
#define  __vdsortpiiu16h_vv  __vdsortpiiuh_vv
#define  __vhadd16w1d_vd     __vhaddw1d_vd
#define  __vhadd32h1d_vd     __vhaddh1d_vd
#define  __vhadd64b1d_vd     __vhaddb1d_vd
#define  __vhadd8d1d_vd      __vhaddd1d_vd
#define  __vhaddeo16h2w_vd   __vhaddeoh2w_vd
#define  __vhaddeo8w2d_vv    __vhaddeow2d_vv
#define  __vhaddeo8w4d_vvv   __vhaddeow4d_vvv
#define  __vhaddu16w1d_vd    __vhadduw1d_vd
#define  __vhaddu32h1d_vd    __vhadduh1d_vd
#define  __vhaddu64b1d_vd    __vhaddub1d_vd
#define  __vhaddu8d1d_vd     __vhaddud1d_vd
#define  __vhaddueo16h2w_vd  __vhaddueoh2w_vd
#define  __vhaddueo8w2d_vv   __vhaddueow2d_vv
#define  __vhaddueo8w4d_vvv  __vhaddueow4d_vvv
#define  __vhxor16w1w_vr     __vhxorw1w_vr
#define  __vhxor32h1h_vr     __vhxorh1h_vr
#define  __vhxor64b1b_vr     __vhxorb1b_vr
#define  __vhxor8d1d_vd      __vhxord1d_vd
#define  __vsortd16sp_vv     __vsortdsp_vv
#define  __vsortd16w_vv      __vsortdw_vv
#define  __vsortdu16w_vv     __vsortduw_vv
#define  __vsorti16sp_vv     __vsortisp_vv
#define  __vsorti16w_vv      __vsortiw_vv
#define  __vsortiu16w_vv     __vsortiuw_vv
#define  __vsortpd16sp_vv    __vsortpdsp_vv
#define  __vsortpd16w_vv     __vsortpdw_vv
#define  __vsortpdu16w_vv    __vsortpduw_vv
#define  __vsortpi16sp_vv    __vsortpisp_vv
#define  __vsortpi16w_vv     __vsortpiw_vv
#define  __vsortpiu16w_vv    __vsortpiuw_vv
#define  __vshfl4d_vv        __vdeal2d_vv

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/******************************************************************************/
/* Direct Instruction Mapping                                                 */
/*                                                                            */
/* The following is a list of intrinsics that map directly to instructions.   */
/* Although they aren't OpenCL-style, overloaded intrinsics, they are still   */
/* abstracted from the hardware.  The primary purpose of these intrinsics is  */
/* to ensure that no other instructions are generated other than those        */
/* desired by the programmer.  This is particularly useful for operations     */
/* that require operand interleaving on input or operand deinterleaving on    */
/* output.  As such, they should only be used by advanced programmers.        */
/*                                                                            */
/* There are a handful of complicated instructions listed here that do not    */
/* have an OpenCL-style counterpart in c7x.h or cannot be access using a      */
/* specific C idiom.  They can only be accessed using intrinsics listed in    */
/* this file:                                                                 */
/*                                                                            */
/*  'EXTV'                                                                    */
/*  'EXTUV'                                                                   */
/*  'REPLACEV'                                                                */
/*  'VFIR8HD'                                                                 */
/*  'VFIR8HW'                                                                 */
/*  'VFIR8SUHD'                                                               */
/*  'VFIR8SUHW'                                                               */
/*  'VFIR8UHD'                                                                */
/*  'VFIR8UHW'                                                                */
/*  'VMATMPYHD'                                                               */
/*  'VMATMPYSP'                                                               */
/*  'VMATMPYSUHD'                                                             */
/*  'VMATMPYSUHW'                                                             */
/*  'VMATMPYUHD'                                                              */
/*  'VMATMPYUHW'                                                              */
/*  'VMATMPYUSHD'                                                             */
/*  'VSAD16OU16H16W'                                                          */
/*  'VSAD16OU8H16W'                                                           */
/*  'VSAD8OU16B32H'                                                           */
/*  'VSADM16OU16H16W'                                                         */
/*  'VSADM16OU8H16W'                                                          */
/*  'VSADM8OU16B32H'                                                          */
/*  'VDSAD16OU8H8W'                                                           */
/*  'VDSAD8OU16B16H'                                                          */
/*  'VDSADM16OU8H8W'                                                          */
/*  'VDSADM8OU16B16H'                                                         */
/*  'VCDOTPM2OPN16B32H'                                                       */
/*  'VCDOTPM2OPN1H32H'                                                        */
/*  'VCDOTPM2OPN8H16W'                                                        */
/*  'VCDOTPM2OPN8W16W'                                                        */
/*  'VCDOTPM32OPN16B32H'                                                      */
/*                                                                            */
/******************************************************************************/


/******************************************************************************/
/* __SE_REG and __SE_REG_PAIR Streaming Engine Operands                       */
/*                                                                            */
/* Some instructions can only take streaming engine operands (VFIR, VMATMPY). */
/* The intrinsics for these instructions take an immediate representing which */
/* streaming engine, as well as the advance option.                           */
/*----------------------------------------------------------------------------*/
/* Use the following for __SE_REG operands.                                   */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* typedef enum                                                               */
/* {                                                                          */
/*     __SE_REG_0     = 0,                                                    */
/*     __SE_REG_0_ADV = 1,                                                    */
/*     __SE_REG_1     = 2,                                                    */
/*     __SE_REG_1_ADV = 3                                                     */
/* } __SE_REG;                                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* Use the following for __SE_REG_PAIR operands.                              */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* typedef enum                                                               */
/* {                                                                          */
/*     __SE_REG_PAIR_0     = 0,                                               */
/*     __SE_REG_PAIR_0_ADV = 1                                                */
/* } __SE_REG_PAIR;                                                           */
/*                                                                            */
/* All other values are invalid and will produce an error.                    */
/******************************************************************************/

/*-----------------------------------------------------------------------------
* ID: __addd_ddd
*----------------------------------------------------------------------------*/
/*

ADDD
long = __addd_ddd(long, long);
ulong = __addd_ddd(ulong, ulong);

*/

#define __addd_ddd(a,b) __overload("__addd_ddd",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __addd_dkd
*----------------------------------------------------------------------------*/
/*

ADDD
long = __addd_dkd(long, (int)(k));
ulong = __addd_dkd(ulong, (uint)(k={0-0x7fffffff}));

*/

#define __addd_dkd(a,b) __overload("__addd_dkd",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __adddp_ddd
*----------------------------------------------------------------------------*/
/*

ADDDP
double = __adddp_ddd(double, double);

*/


/*-----------------------------------------------------------------------------
* ID: __addsp_rrr
*----------------------------------------------------------------------------*/
/*

ADDSP
float = __addsp_rrr(float, float);

*/


/*-----------------------------------------------------------------------------
* ID: __addw_rkr
*----------------------------------------------------------------------------*/
/*

ADDW
int = __addw_rkr(int, (int)(k));
uint = __addw_rkr(uint, (uint)(k));

*/

#define __addw_rkr(a,b) __overload("__addw_rkr",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __addw_rrr
*----------------------------------------------------------------------------*/
/*

ADDW
int = __addw_rrr(int, int);
uint = __addw_rrr(uint, uint);

*/

#define __addw_rrr(a,b) __overload("__addw_rrr",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __and_ppp
*----------------------------------------------------------------------------*/
/*

AND
__vpred = __and_ppp(__vpred, __vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __andd_ddd
*----------------------------------------------------------------------------*/
/*

ANDD
char8 = __andd_ddd(char8, char8);
short4 = __andd_ddd(short4, short4);
int2 = __andd_ddd(int2, int2);
long = __andd_ddd(long, long);
uchar8 = __andd_ddd(uchar8, uchar8);
ushort4 = __andd_ddd(ushort4, ushort4);
uint2 = __andd_ddd(uint2, uint2);
ulong = __andd_ddd(ulong, ulong);

*/

#define __andd_ddd(a,b) __overload("__andd_ddd",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __andd_dkd
*----------------------------------------------------------------------------*/
/*

ANDD
long = __andd_dkd(long, (int)(k));
ulong = __andd_dkd(ulong, (uint)(k={0-0x7fffffff}));

*/

#define __andd_dkd(a,b) __overload("__andd_dkd",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __andn_ppp
*----------------------------------------------------------------------------*/
/*

ANDN
__vpred = __andn_ppp(__vpred, __vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __andnd_ddd
*----------------------------------------------------------------------------*/
/*

ANDND
char8 = __andnd_ddd(char8, char8);
short4 = __andnd_ddd(short4, short4);
int2 = __andnd_ddd(int2, int2);
long = __andnd_ddd(long, long);
uchar8 = __andnd_ddd(uchar8, uchar8);
ushort4 = __andnd_ddd(ushort4, ushort4);
uint2 = __andnd_ddd(uint2, uint2);
ulong = __andnd_ddd(ulong, ulong);

*/

#define __andnd_ddd(a,b) __overload("__andnd_ddd",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __andnd_dkd
*----------------------------------------------------------------------------*/
/*

ANDND
long = __andnd_dkd(long, (int)(k));
ulong = __andnd_dkd(ulong, (uint)(k={0-0x7fffffff}));

*/

#define __andnd_dkd(a,b) __overload("__andnd_dkd",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __andnw_rkr
*----------------------------------------------------------------------------*/
/*

ANDNW
char4 = __andnw_rkr(char4, (char4)(k));
short2 = __andnw_rkr(short2, (short2)(k));
int = __andnw_rkr(int, (int)(k));
uchar4 = __andnw_rkr(uchar4, (uchar4)(k));
ushort2 = __andnw_rkr(ushort2, (ushort2)(k));
uint = __andnw_rkr(uint, (uint)(k));

*/

#define __andnw_rkr(a,b) __overload("__andnw_rkr",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __andnw_rrr
*----------------------------------------------------------------------------*/
/*

ANDNW
char4 = __andnw_rrr(char4, char4);
short2 = __andnw_rrr(short2, short2);
int = __andnw_rrr(int, int);
uchar4 = __andnw_rrr(uchar4, uchar4);
ushort2 = __andnw_rrr(ushort2, ushort2);
uint = __andnw_rrr(uint, uint);

*/

#define __andnw_rrr(a,b) __overload("__andnw_rrr",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __andw_rkr
*----------------------------------------------------------------------------*/
/*

ANDW
char4 = __andw_rkr(char4, (char4)(k));
short2 = __andw_rkr(short2, (short2)(k));
int = __andw_rkr(int, (int)(k));
uchar4 = __andw_rkr(uchar4, (uchar4)(k));
ushort2 = __andw_rkr(ushort2, (ushort2)(k));
uint = __andw_rkr(uint, (uint)(k));

*/

#define __andw_rkr(a,b) __overload("__andw_rkr",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __andw_rrr
*----------------------------------------------------------------------------*/
/*

ANDW
char4 = __andw_rrr(char4, char4);
short2 = __andw_rrr(short2, short2);
int = __andw_rrr(int, int);
uchar4 = __andw_rrr(uchar4, uchar4);
ushort2 = __andw_rrr(ushort2, ushort2);
uint = __andw_rrr(uint, uint);

*/

#define __andw_rrr(a,b) __overload("__andw_rrr",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __bitr_pp
*----------------------------------------------------------------------------*/
/*

BITR
__vpred = __bitr_pp(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __c6dcmpeqb_ddr
*----------------------------------------------------------------------------*/
/*

C6DCMPEQB
uchar = __c6dcmpeqb_ddr(char8, char8);

*/


/*-----------------------------------------------------------------------------
* ID: __c6dcmpeqh_ddr
*----------------------------------------------------------------------------*/
/*

C6DCMPEQH
uchar = __c6dcmpeqh_ddr(short4, short4);

*/


/*-----------------------------------------------------------------------------
* ID: __c6dcmpgth_ddr
*----------------------------------------------------------------------------*/
/*

C6DCMPGTH
uchar = __c6dcmpgth_ddr(short4, short4);

*/


/*-----------------------------------------------------------------------------
* ID: __c6dcmpgtub_ddr
*----------------------------------------------------------------------------*/
/*

C6DCMPGTUB
uchar = __c6dcmpgtub_ddr(uchar8, uchar8);

*/


/*-----------------------------------------------------------------------------
* ID: __c6ddotp2hhw_drd
*----------------------------------------------------------------------------*/
/*

C6DDOTP2HHW
int2 = __c6ddotp2hhw_drd(short4, short2);

*/


/*-----------------------------------------------------------------------------
* ID: __c6ddotp2hrhh_drr
*----------------------------------------------------------------------------*/
/*

C6DDOTP2HRHH
short2 = __c6ddotp2hrhh_drr(short4, short2);

*/


/*-----------------------------------------------------------------------------
* ID: __c6ddotp2lhw_drd
*----------------------------------------------------------------------------*/
/*

C6DDOTP2LHW
int2 = __c6ddotp2lhw_drd(short4, short2);

*/


/*-----------------------------------------------------------------------------
* ID: __c6ddotp2lrhh_drr
*----------------------------------------------------------------------------*/
/*

C6DDOTP2LRHH
short2 = __c6ddotp2lrhh_drr(short4, short2);

*/


/*-----------------------------------------------------------------------------
* ID: __c6dmpyhw_vvw
*----------------------------------------------------------------------------*/
/*

C6DMPYHW
__c6dmpyhw_vvw(short32, short32, int16&, int16&);

*/


/*-----------------------------------------------------------------------------
* ID: __c6dmpysubh_vvw
*----------------------------------------------------------------------------*/
/*

C6DMPYSUBH
__c6dmpysubh_vvw(char64, uchar64, short32&, short32&);

*/


/*-----------------------------------------------------------------------------
* ID: __c6dmpyubh_vvw
*----------------------------------------------------------------------------*/
/*

C6DMPYUBH
__c6dmpyubh_vvw(uchar64, uchar64, ushort32&, ushort32&);

*/


/*-----------------------------------------------------------------------------
* ID: __c6dmpyuhw_vvw
*----------------------------------------------------------------------------*/
/*

C6DMPYUHW
__c6dmpyuhw_vvw(ushort32, ushort32, uint16&, uint16&);

*/


/*-----------------------------------------------------------------------------
* ID: __c6dotp2rsuhw_rrr
*----------------------------------------------------------------------------*/
/*

C6DOTP2RSUHW
int = __c6dotp2rsuhw_rrr(short2, ushort2);

*/


/*-----------------------------------------------------------------------------
* ID: __c6dotpn2hw_rrr
*----------------------------------------------------------------------------*/
/*

C6DOTPN2HW
int = __c6dotpn2hw_rrr(short2, short2);

*/


/*-----------------------------------------------------------------------------
* ID: __c6dotpn2rsuhh_rrr
*----------------------------------------------------------------------------*/
/*

C6DOTPN2RSUHH
int = __c6dotpn2rsuhh_rrr(short2, ushort2);

*/


/*-----------------------------------------------------------------------------
* ID: __c6dsmpyhw_vvw
*----------------------------------------------------------------------------*/
/*

C6DSMPYHW
__c6dsmpyhw_vvw(short32, short32, int16&, int16&);

*/


/*-----------------------------------------------------------------------------
* ID: __c6dspacku4_ddd
*----------------------------------------------------------------------------*/
/*

C6DSPACKU4
uchar8 = __c6dspacku4_ddd(short4, short4);

*/


/*-----------------------------------------------------------------------------
* ID: __c6mpy2ir_rrd
*----------------------------------------------------------------------------*/
/*

C6MPY2IR
int2 = __c6mpy2ir_rrd(short2, int);

*/


/*-----------------------------------------------------------------------------
* ID: __c6mpyhir_rrr
*----------------------------------------------------------------------------*/
/*

C6MPYHIR
int = __c6mpyhir_rrr(short2, int);

*/


/*-----------------------------------------------------------------------------
* ID: __c6mpylir_rrr
*----------------------------------------------------------------------------*/
/*

C6MPYLIR
int = __c6mpylir_rrr(short2, int);

*/


/*-----------------------------------------------------------------------------
* ID: __clr_rrr
*----------------------------------------------------------------------------*/
/*

CLR
uint = __clr_rrr(uint, uint);

*/


/*-----------------------------------------------------------------------------
* ID: __cmpeqd_ddr
*----------------------------------------------------------------------------*/
/*

CMPEQD
int = __cmpeqd_ddr(long, long);

*/


/*-----------------------------------------------------------------------------
* ID: __cmpeqd_dkr
*----------------------------------------------------------------------------*/
/*

CMPEQD
int = __cmpeqd_dkr(long, (int)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __cmpeqdp_ddr
*----------------------------------------------------------------------------*/
/*

CMPEQDP
int = __cmpeqdp_ddr(double, double);

*/


/*-----------------------------------------------------------------------------
* ID: __cmpeqsp_rrr
*----------------------------------------------------------------------------*/
/*

CMPEQSP
int = __cmpeqsp_rrr(float, float);

*/


/*-----------------------------------------------------------------------------
* ID: __cmpeqw_rkr
*----------------------------------------------------------------------------*/
/*

CMPEQW
int = __cmpeqw_rkr(int, (int)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __cmpeqw_rrr
*----------------------------------------------------------------------------*/
/*

CMPEQW
int = __cmpeqw_rrr(int, int);

*/


/*-----------------------------------------------------------------------------
* ID: __cmpged_ddr
*----------------------------------------------------------------------------*/
/*

CMPGED
int = __cmpged_ddr(long, long);

*/


/*-----------------------------------------------------------------------------
* ID: __cmpged_dkr
*----------------------------------------------------------------------------*/
/*

CMPGED
int = __cmpged_dkr(long, (int)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __cmpgeud_ddr
*----------------------------------------------------------------------------*/
/*

CMPGEUD
int = __cmpgeud_ddr(ulong, ulong);

*/


/*-----------------------------------------------------------------------------
* ID: __cmpgeud_dkr
*----------------------------------------------------------------------------*/
/*

CMPGEUD
int = __cmpgeud_dkr(ulong, (uint)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __cmpgeuw_rkr
*----------------------------------------------------------------------------*/
/*

CMPGEUW
int = __cmpgeuw_rkr(uint, (uint)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __cmpgeuw_rrr
*----------------------------------------------------------------------------*/
/*

CMPGEUW
int = __cmpgeuw_rrr(uint, uint);

*/


/*-----------------------------------------------------------------------------
* ID: __cmpgew_rkr
*----------------------------------------------------------------------------*/
/*

CMPGEW
int = __cmpgew_rkr(int, (int)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __cmpgew_rrr
*----------------------------------------------------------------------------*/
/*

CMPGEW
int = __cmpgew_rrr(int, int);

*/


/*-----------------------------------------------------------------------------
* ID: __cmpgtd_ddr
*----------------------------------------------------------------------------*/
/*

CMPGTD
int = __cmpgtd_ddr(long, long);

*/


/*-----------------------------------------------------------------------------
* ID: __cmpgtd_dkr
*----------------------------------------------------------------------------*/
/*

CMPGTD
int = __cmpgtd_dkr(long, (int)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __cmpgtud_ddr
*----------------------------------------------------------------------------*/
/*

CMPGTUD
int = __cmpgtud_ddr(ulong, ulong);

*/


/*-----------------------------------------------------------------------------
* ID: __cmpgtud_dkr
*----------------------------------------------------------------------------*/
/*

CMPGTUD
int = __cmpgtud_dkr(ulong, (uint)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __cmpgtuw_rkr
*----------------------------------------------------------------------------*/
/*

CMPGTUW
int = __cmpgtuw_rkr(uint, (uint)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __cmpgtuw_rrr
*----------------------------------------------------------------------------*/
/*

CMPGTUW
int = __cmpgtuw_rrr(uint, uint);

*/


/*-----------------------------------------------------------------------------
* ID: __cmpgtw_rkr
*----------------------------------------------------------------------------*/
/*

CMPGTW
int = __cmpgtw_rkr(int, (int)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __cmpgtw_rrr
*----------------------------------------------------------------------------*/
/*

CMPGTW
int = __cmpgtw_rrr(int, int);

*/


/*-----------------------------------------------------------------------------
* ID: __cmpledp_ddr
*----------------------------------------------------------------------------*/
/*

CMPLEDP
int = __cmpledp_ddr(double, double);

*/


/*-----------------------------------------------------------------------------
* ID: __cmplesp_rrr
*----------------------------------------------------------------------------*/
/*

CMPLESP
int = __cmplesp_rrr(float, float);

*/


/*-----------------------------------------------------------------------------
* ID: __cmpltdp_ddr
*----------------------------------------------------------------------------*/
/*

CMPLTDP
int = __cmpltdp_ddr(double, double);

*/


/*-----------------------------------------------------------------------------
* ID: __cmpltsp_rrr
*----------------------------------------------------------------------------*/
/*

CMPLTSP
int = __cmpltsp_rrr(float, float);

*/


/*-----------------------------------------------------------------------------
* ID: __compressl_pp
*----------------------------------------------------------------------------*/
/*

COMPRESSL
__vpred = __compressl_pp(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __compressr_pp
*----------------------------------------------------------------------------*/
/*

COMPRESSR
__vpred = __compressr_pp(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __decimateb_ppp
*----------------------------------------------------------------------------*/
/*

DECIMATEB
__vpred = __decimateb_ppp(__vpred, __vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __decimated_ppp
*----------------------------------------------------------------------------*/
/*

DECIMATED
__vpred = __decimated_ppp(__vpred, __vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __decimateh_ppp
*----------------------------------------------------------------------------*/
/*

DECIMATEH
__vpred = __decimateh_ppp(__vpred, __vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __decimatew_ppp
*----------------------------------------------------------------------------*/
/*

DECIMATEW
__vpred = __decimatew_ppp(__vpred, __vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __divdw_drd
*----------------------------------------------------------------------------*/
/*

DIVDW
long = __divdw_drd(long, int);

*/


/*-----------------------------------------------------------------------------
* ID: __divudw_drd
*----------------------------------------------------------------------------*/
/*

DIVUDW
ulong = __divudw_drd(ulong, uint);

*/


/*-----------------------------------------------------------------------------
* ID: __divuw_rrr
*----------------------------------------------------------------------------*/
/*

DIVUW
uint = __divuw_rrr(uint, uint);

*/


/*-----------------------------------------------------------------------------
* ID: __divw_rrr
*----------------------------------------------------------------------------*/
/*

DIVW
int = __divw_rrr(int, int);

*/


/*-----------------------------------------------------------------------------
* ID: __ext_dkkd
*----------------------------------------------------------------------------*/
/*

EXT
long = __ext_dkkd(char8, (uchar)(k={0-63}), (uchar)(k={0-63}));
long = __ext_dkkd(short4, (uchar)(k={0-63}), (uchar)(k={0-63}));
long = __ext_dkkd(int2, (uchar)(k={0-63}), (uchar)(k={0-63}));
long = __ext_dkkd(long, (uchar)(k={0-63}), (uchar)(k={0-63}));

*/

#define __ext_dkkd(a,b,c) __overload("__ext_dkkd",(a),(b),(c))((a),(b),(c))


/*-----------------------------------------------------------------------------
* ID: __extu_dkkd
*----------------------------------------------------------------------------*/
/*

EXTU
ulong = __extu_dkkd(uchar8, (uchar)(k={0-63}), (uchar)(k={0-63}));
ulong = __extu_dkkd(ushort4, (uchar)(k={0-63}), (uchar)(k={0-63}));
ulong = __extu_dkkd(uint2, (uchar)(k={0-63}), (uchar)(k={0-63}));
ulong = __extu_dkkd(ulong, (uchar)(k={0-63}), (uchar)(k={0-63}));

*/

#define __extu_dkkd(a,b,c) __overload("__extu_dkkd",(a),(b),(c))((a),(b),(c))


/*-----------------------------------------------------------------------------
* ID: __extuv_vkkkd
*----------------------------------------------------------------------------*/
/*

EXTUV
ulong = __extuv_vkkkd(ulong8, (uchar)(k={0-7}), (uchar)(k={0-63}), (uchar)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __extv_vkkkd
*----------------------------------------------------------------------------*/
/*

EXTV
long = __extv_vkkkd(long8, (uchar)(k={0-7}), (uchar)(k={0-63}), (uchar)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __landd_ddr
*----------------------------------------------------------------------------*/
/*

LANDD
int = __landd_ddr(long, long);

*/


/*-----------------------------------------------------------------------------
* ID: __landnd_ddr
*----------------------------------------------------------------------------*/
/*

LANDND
int = __landnd_ddr(long, long);

*/


/*-----------------------------------------------------------------------------
* ID: __lord_ddr
*----------------------------------------------------------------------------*/
/*

LORD
int = __lord_ddr(long, long);

*/


/*-----------------------------------------------------------------------------
* ID: __maskb_kp
*----------------------------------------------------------------------------*/
/*

MASKB
__vpred = __maskb_kp((uchar)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __maskb_rp
*----------------------------------------------------------------------------*/
/*

MASKB
__vpred = __maskb_rp(uint);

*/


/*-----------------------------------------------------------------------------
* ID: __maskd_kp
*----------------------------------------------------------------------------*/
/*

MASKD
__vpred = __maskd_kp((uchar)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __maskd_rp
*----------------------------------------------------------------------------*/
/*

MASKD
__vpred = __maskd_rp(uint);

*/


/*-----------------------------------------------------------------------------
* ID: __maskh_kp
*----------------------------------------------------------------------------*/
/*

MASKH
__vpred = __maskh_kp((uchar)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __maskh_rp
*----------------------------------------------------------------------------*/
/*

MASKH
__vpred = __maskh_rp(uint);

*/


/*-----------------------------------------------------------------------------
* ID: __maskw_kp
*----------------------------------------------------------------------------*/
/*

MASKW
__vpred = __maskw_kp((uchar)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __maskw_rp
*----------------------------------------------------------------------------*/
/*

MASKW
__vpred = __maskw_rp(uint);

*/


/*-----------------------------------------------------------------------------
* ID: __moddw_drd
*----------------------------------------------------------------------------*/
/*

MODDW
long = __moddw_drd(long, int);

*/


/*-----------------------------------------------------------------------------
* ID: __modudw_drd
*----------------------------------------------------------------------------*/
/*

MODUDW
ulong = __modudw_drd(ulong, uint);

*/


/*-----------------------------------------------------------------------------
* ID: __moduw_rrr
*----------------------------------------------------------------------------*/
/*

MODUW
uint = __moduw_rrr(uint, uint);

*/


/*-----------------------------------------------------------------------------
* ID: __modw_rrr
*----------------------------------------------------------------------------*/
/*

MODW
int = __modw_rrr(int, int);

*/


/*-----------------------------------------------------------------------------
* ID: __mpydd_ddd
*----------------------------------------------------------------------------*/
/*

MPYDD
long = __mpydd_ddd(long, long);
ulong = __mpydd_ddd(ulong, ulong);

*/

#define __mpydd_ddd(a,b) __overload("__mpydd_ddd",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __mpydp_ddd
*----------------------------------------------------------------------------*/
/*

MPYDP
double = __mpydp_ddd(double, double);

*/


/*-----------------------------------------------------------------------------
* ID: __mpyhw_rrr
*----------------------------------------------------------------------------*/
/*

MPYHW
int = __mpyhw_rrr(short, short);

*/


/*-----------------------------------------------------------------------------
* ID: __mpysp_rrr
*----------------------------------------------------------------------------*/
/*

MPYSP
float = __mpysp_rrr(float, float);

*/


/*-----------------------------------------------------------------------------
* ID: __mpysuhw_rrr
*----------------------------------------------------------------------------*/
/*

MPYSUHW
int = __mpysuhw_rrr(short, ushort);

*/


/*-----------------------------------------------------------------------------
* ID: __mpyuhw_rrr
*----------------------------------------------------------------------------*/
/*

MPYUHW
uint = __mpyuhw_rrr(ushort, ushort);

*/


/*-----------------------------------------------------------------------------
* ID: __mpyww_rrr
*----------------------------------------------------------------------------*/
/*

MPYWW
int = __mpyww_rrr(int, int);
uint = __mpyww_rrr(uint, uint);

*/

#define __mpyww_rrr(a,b) __overload("__mpyww_rrr",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __nand_ppp
*----------------------------------------------------------------------------*/
/*

NAND
__vpred = __nand_ppp(__vpred, __vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __nandd_ddd
*----------------------------------------------------------------------------*/
/*

NANDD
char8 = __nandd_ddd(char8, char8);
short4 = __nandd_ddd(short4, short4);
int2 = __nandd_ddd(int2, int2);
long = __nandd_ddd(long, long);
uchar8 = __nandd_ddd(uchar8, uchar8);
ushort4 = __nandd_ddd(ushort4, ushort4);
uint2 = __nandd_ddd(uint2, uint2);
ulong = __nandd_ddd(ulong, ulong);

*/

#define __nandd_ddd(a,b) __overload("__nandd_ddd",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __nandd_dkd
*----------------------------------------------------------------------------*/
/*

NANDD
long = __nandd_dkd(long, (int)(k));
ulong = __nandd_dkd(ulong, (uint)(k={0-0x7fffffff}));

*/

#define __nandd_dkd(a,b) __overload("__nandd_dkd",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __nandw_rrr
*----------------------------------------------------------------------------*/
/*

NANDW
char4 = __nandw_rrr(char4, char4);
short2 = __nandw_rrr(short2, short2);
int = __nandw_rrr(int, int);
uchar4 = __nandw_rrr(uchar4, uchar4);
ushort2 = __nandw_rrr(ushort2, ushort2);
uint = __nandw_rrr(uint, uint);

*/

#define __nandw_rrr(a,b) __overload("__nandw_rrr",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __nor_ppp
*----------------------------------------------------------------------------*/
/*

NOR
__vpred = __nor_ppp(__vpred, __vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __nord_ddd
*----------------------------------------------------------------------------*/
/*

NORD
char8 = __nord_ddd(char8, char8);
short4 = __nord_ddd(short4, short4);
int2 = __nord_ddd(int2, int2);
long = __nord_ddd(long, long);
uchar8 = __nord_ddd(uchar8, uchar8);
ushort4 = __nord_ddd(ushort4, ushort4);
uint2 = __nord_ddd(uint2, uint2);
ulong = __nord_ddd(ulong, ulong);

*/

#define __nord_ddd(a,b) __overload("__nord_ddd",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __nord_dkd
*----------------------------------------------------------------------------*/
/*

NORD
long = __nord_dkd(long, (int)(k));
ulong = __nord_dkd(ulong, (uint)(k={0-0x7fffffff}));

*/

#define __nord_dkd(a,b) __overload("__nord_dkd",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __norw_rrr
*----------------------------------------------------------------------------*/
/*

NORW
char4 = __norw_rrr(char4, char4);
short2 = __norw_rrr(short2, short2);
int = __norw_rrr(int, int);
uchar4 = __norw_rrr(uchar4, uchar4);
ushort2 = __norw_rrr(ushort2, ushort2);
uint = __norw_rrr(uint, uint);

*/

#define __norw_rrr(a,b) __overload("__norw_rrr",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __not_pp
*----------------------------------------------------------------------------*/
/*

NOT
__vpred = __not_pp(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __or_ppp
*----------------------------------------------------------------------------*/
/*

OR
__vpred = __or_ppp(__vpred, __vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __ord_ddd
*----------------------------------------------------------------------------*/
/*

ORD
char8 = __ord_ddd(char8, char8);
short4 = __ord_ddd(short4, short4);
int2 = __ord_ddd(int2, int2);
long = __ord_ddd(long, long);
uchar8 = __ord_ddd(uchar8, uchar8);
ushort4 = __ord_ddd(ushort4, ushort4);
uint2 = __ord_ddd(uint2, uint2);
ulong = __ord_ddd(ulong, ulong);

*/

#define __ord_ddd(a,b) __overload("__ord_ddd",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __ord_dkd
*----------------------------------------------------------------------------*/
/*

ORD
long = __ord_dkd(long, (int)(k));
ulong = __ord_dkd(ulong, (uint)(k={0-0x7fffffff}));

*/

#define __ord_dkd(a,b) __overload("__ord_dkd",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __orn_ppp
*----------------------------------------------------------------------------*/
/*

ORN
__vpred = __orn_ppp(__vpred, __vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __ornd_ddd
*----------------------------------------------------------------------------*/
/*

ORND
char8 = __ornd_ddd(char8, char8);
short4 = __ornd_ddd(short4, short4);
int2 = __ornd_ddd(int2, int2);
long = __ornd_ddd(long, long);
uchar8 = __ornd_ddd(uchar8, uchar8);
ushort4 = __ornd_ddd(ushort4, ushort4);
uint2 = __ornd_ddd(uint2, uint2);
ulong = __ornd_ddd(ulong, ulong);

*/

#define __ornd_ddd(a,b) __overload("__ornd_ddd",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __ornd_dkd
*----------------------------------------------------------------------------*/
/*

ORND
long = __ornd_dkd(long, (int)(k));
ulong = __ornd_dkd(ulong, (uint)(k={0-0x7fffffff}));

*/

#define __ornd_dkd(a,b) __overload("__ornd_dkd",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __ornw_rkr
*----------------------------------------------------------------------------*/
/*

ORNW
char4 = __ornw_rkr(char4, (char4)(k));
short2 = __ornw_rkr(short2, (short2)(k));
int = __ornw_rkr(int, (int)(k));
uchar4 = __ornw_rkr(uchar4, (uchar4)(k));
ushort2 = __ornw_rkr(ushort2, (ushort2)(k));
uint = __ornw_rkr(uint, (uint)(k));

*/

#define __ornw_rkr(a,b) __overload("__ornw_rkr",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __ornw_rrr
*----------------------------------------------------------------------------*/
/*

ORNW
char4 = __ornw_rrr(char4, char4);
short2 = __ornw_rrr(short2, short2);
int = __ornw_rrr(int, int);
uchar4 = __ornw_rrr(uchar4, uchar4);
ushort2 = __ornw_rrr(ushort2, ushort2);
uint = __ornw_rrr(uint, uint);

*/

#define __ornw_rrr(a,b) __overload("__ornw_rrr",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __orw_rkr
*----------------------------------------------------------------------------*/
/*

ORW
char4 = __orw_rkr(char4, (char4)(k));
short2 = __orw_rkr(short2, (short2)(k));
int = __orw_rkr(int, (int)(k));
uchar4 = __orw_rkr(uchar4, (uchar4)(k));
ushort2 = __orw_rkr(ushort2, (ushort2)(k));
uint = __orw_rkr(uint, (uint)(k));

*/

#define __orw_rkr(a,b) __overload("__orw_rkr",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __orw_rrr
*----------------------------------------------------------------------------*/
/*

ORW
char4 = __orw_rrr(char4, char4);
short2 = __orw_rrr(short2, short2);
int = __orw_rrr(int, int);
uchar4 = __orw_rrr(uchar4, uchar4);
ushort2 = __orw_rrr(ushort2, ushort2);
uint = __orw_rrr(uint, uint);

*/

#define __orw_rrr(a,b) __overload("__orw_rrr",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __packw_rrd
*----------------------------------------------------------------------------*/
/*

PACKW
int2 = __packw_rrd(int, int);
float2 = __packw_rrd(float, float);
uint2 = __packw_rrd(uint, uint);
cshort2 = __packw_rrd(cshort, cshort);

*/

#define __packw_rrd(a,b) __overload("__packw_rrd",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __packwdly4_rrd
*----------------------------------------------------------------------------*/
/*

PACKWDLY4
long = __packwdly4_rrd(int, int);
ulong = __packwdly4_rrd(uint, uint);

*/

#define __packwdly4_rrd(a,b) __overload("__packwdly4_rrd",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __packx2_rrd
*----------------------------------------------------------------------------*/
/*

PACKX2
short4 = __packx2_rrd(short2, short2);
ushort4 = __packx2_rrd(ushort2, ushort2);
cchar4 = __packx2_rrd(cchar2, cchar2);

*/

#define __packx2_rrd(a,b) __overload("__packx2_rrd",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __pbitcntb_pr
*----------------------------------------------------------------------------*/
/*

PBITCNTB
uint = __pbitcntb_pr(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __pbitcntd_pr
*----------------------------------------------------------------------------*/
/*

PBITCNTD
uint = __pbitcntd_pr(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __pbitcnth_pr
*----------------------------------------------------------------------------*/
/*

PBITCNTH
uint = __pbitcnth_pr(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __pbitcntw_pr
*----------------------------------------------------------------------------*/
/*

PBITCNTW
uint = __pbitcntw_pr(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __pcntgatherb_prp
*----------------------------------------------------------------------------*/
/*

PCNTGATHERB
__pcntgatherb_prp(__vpred, uint&, __vpred&);

*/


/*-----------------------------------------------------------------------------
* ID: __pcntgatherd_prp
*----------------------------------------------------------------------------*/
/*

PCNTGATHERD
__pcntgatherd_prp(__vpred, uint&, __vpred&);

*/


/*-----------------------------------------------------------------------------
* ID: __pcntgatherh_prp
*----------------------------------------------------------------------------*/
/*

PCNTGATHERH
__pcntgatherh_prp(__vpred, uint&, __vpred&);

*/


/*-----------------------------------------------------------------------------
* ID: __pcntgatherw_prp
*----------------------------------------------------------------------------*/
/*

PCNTGATHERW
__pcntgatherw_prp(__vpred, uint&, __vpred&);

*/


/*-----------------------------------------------------------------------------
* ID: __pduph2b_pp
*----------------------------------------------------------------------------*/
/*

PDUPH2B
__vpred = __pduph2b_pp(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __pduph2d_pp
*----------------------------------------------------------------------------*/
/*

PDUPH2D
__vpred = __pduph2d_pp(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __pduph2h_pp
*----------------------------------------------------------------------------*/
/*

PDUPH2H
__vpred = __pduph2h_pp(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __pduph2w_pp
*----------------------------------------------------------------------------*/
/*

PDUPH2W
__vpred = __pduph2w_pp(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __pdupl2b_pp
*----------------------------------------------------------------------------*/
/*

PDUPL2B
__vpred = __pdupl2b_pp(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __pdupl2d_pp
*----------------------------------------------------------------------------*/
/*

PDUPL2D
__vpred = __pdupl2d_pp(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __pdupl2h_pp
*----------------------------------------------------------------------------*/
/*

PDUPL2H
__vpred = __pdupl2h_pp(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __pdupl2w_pp
*----------------------------------------------------------------------------*/
/*

PDUPL2W
__vpred = __pdupl2w_pp(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __prmbdb_pr
*----------------------------------------------------------------------------*/
/*

PRMBDB
uint = __prmbdb_pr(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __prmbdd_pr
*----------------------------------------------------------------------------*/
/*

PRMBDD
uint = __prmbdd_pr(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __prmbdh_pr
*----------------------------------------------------------------------------*/
/*

PRMBDH
uint = __prmbdh_pr(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __prmbdw_pr
*----------------------------------------------------------------------------*/
/*

PRMBDW
uint = __prmbdw_pr(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __replace_dkkd
*----------------------------------------------------------------------------*/
/*

REPLACE
ulong = __replace_dkkd(ulong, (uchar)(k={0-63}), (uchar)(k={0-63}), ulong);
long = __replace_dkkd(long, (char)(k={0-63}), (char)(k={0-63}), long);

*/

#define __replace_dkkd(a,b,c,d) __overload("__replace_dkkd",(a),(b),(c),(d))((a),(b),(c),(d))


/*-----------------------------------------------------------------------------
* ID: __replacev_dkkkv
*----------------------------------------------------------------------------*/
/*

REPLACEV
ulong8 = __replacev_dkkkv(ulong, (uchar)(k={0-7}), (uchar)(k={0-63}), (uchar)(k={0-63}), ulong8);
long8 = __replacev_dkkkv(long, (char)(k={0-7}), (char)(k={0-63}), (char)(k={0-63}), long8);

*/

#define __replacev_dkkkv(a,b,c,d,e) __overload("__replacev_dkkkv",(a),(b),(c),(d),(e))((a),(b),(c),(d),(e))


/*-----------------------------------------------------------------------------
* ID: __set_rrr
*----------------------------------------------------------------------------*/
/*

SET
int = __set_rrr(int, int);

*/


/*-----------------------------------------------------------------------------
* ID: __shld_dkd
*----------------------------------------------------------------------------*/
/*

SHLD
long = __shld_dkd(long, (uchar)(k={0-63}));
ulong = __shld_dkd(ulong, (uchar)(k={0-63}));

*/

#define __shld_dkd(a,b) __overload("__shld_dkd",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __shld_drd
*----------------------------------------------------------------------------*/
/*

SHLD
long = __shld_drd(long, int);
ulong = __shld_drd(ulong, uint);

*/

#define __shld_drd(a,b) __overload("__shld_drd",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __shlw_rkr
*----------------------------------------------------------------------------*/
/*

SHLW
int = __shlw_rkr(int, (uchar)(k={0-63}));
uint = __shlw_rkr(uint, (uchar)(k={0-63}));

*/

#define __shlw_rkr(a,b) __overload("__shlw_rkr",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __shlw_rrr
*----------------------------------------------------------------------------*/
/*

SHLW
int = __shlw_rrr(int, int);
uint = __shlw_rrr(uint, uint);

*/

#define __shlw_rrr(a,b) __overload("__shlw_rrr",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __shrd_dkd
*----------------------------------------------------------------------------*/
/*

SHRD
long = __shrd_dkd(long, (uchar)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __shrd_drd
*----------------------------------------------------------------------------*/
/*

SHRD
long = __shrd_drd(long, int);

*/


/*-----------------------------------------------------------------------------
* ID: __shrud_dkd
*----------------------------------------------------------------------------*/
/*

SHRUD
ulong = __shrud_dkd(ulong, (uchar)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __shrud_drd
*----------------------------------------------------------------------------*/
/*

SHRUD
ulong = __shrud_drd(ulong, uint);

*/


/*-----------------------------------------------------------------------------
* ID: __shruw_rkr
*----------------------------------------------------------------------------*/
/*

SHRUW
uint = __shruw_rkr(uint, (uchar)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __shruw_rrr
*----------------------------------------------------------------------------*/
/*

SHRUW
uint = __shruw_rrr(uint, uint);

*/


/*-----------------------------------------------------------------------------
* ID: __shrw_rkr
*----------------------------------------------------------------------------*/
/*

SHRW
int = __shrw_rkr(int, (uchar)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __shrw_rrr
*----------------------------------------------------------------------------*/
/*

SHRW
int = __shrw_rrr(int, int);

*/


/*-----------------------------------------------------------------------------
* ID: __smpyhw_rrr
*----------------------------------------------------------------------------*/
/*

SMPYHW
int = __smpyhw_rrr(short, short);

*/


/*-----------------------------------------------------------------------------
* ID: __subd_ddd
*----------------------------------------------------------------------------*/
/*

SUBD
long = __subd_ddd(long, long);
ulong = __subd_ddd(ulong, ulong);

*/

#define __subd_ddd(a,b) __overload("__subd_ddd",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __subdp_ddd
*----------------------------------------------------------------------------*/
/*

SUBDP
double = __subdp_ddd(double, double);

*/


/*-----------------------------------------------------------------------------
* ID: __subrd_ddd
*----------------------------------------------------------------------------*/
/*

SUBRD
long = __subrd_ddd(long, long);
ulong = __subrd_ddd(ulong, ulong);

*/

#define __subrd_ddd(a,b) __overload("__subrd_ddd",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __subrd_dkd
*----------------------------------------------------------------------------*/
/*

SUBRD
long = __subrd_dkd(long, (int)(k));
ulong = __subrd_dkd(ulong, (uint)(k={0-0x7fffffff}));

*/

#define __subrd_dkd(a,b) __overload("__subrd_dkd",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __subrw_rkr
*----------------------------------------------------------------------------*/
/*

SUBRW
int = __subrw_rkr(int, (int)(k));
uint = __subrw_rkr(uint, (uint)(k));

*/

#define __subrw_rkr(a,b) __overload("__subrw_rkr",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __subrw_rrr
*----------------------------------------------------------------------------*/
/*

SUBRW
int = __subrw_rrr(int, int);
uint = __subrw_rrr(uint, uint);

*/

#define __subrw_rrr(a,b) __overload("__subrw_rrr",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __subsp_rrr
*----------------------------------------------------------------------------*/
/*

SUBSP
float = __subsp_rrr(float, float);

*/


/*-----------------------------------------------------------------------------
* ID: __subw_rrr
*----------------------------------------------------------------------------*/
/*

SUBW
int = __subw_rrr(int, int);
uint = __subw_rrr(uint, uint);

*/

#define __subw_rrr(a,b) __overload("__subw_rrr",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vabsb_vv
*----------------------------------------------------------------------------*/
/*

VABSB
char64 = __vabsb_vv(char64);

*/


/*-----------------------------------------------------------------------------
* ID: __vabsd_vv
*----------------------------------------------------------------------------*/
/*

VABSD
long8 = __vabsd_vv(long8);

*/


/*-----------------------------------------------------------------------------
* ID: __vabsdp_vv
*----------------------------------------------------------------------------*/
/*

VABSDP
double8 = __vabsdp_vv(double8);

*/


/*-----------------------------------------------------------------------------
* ID: __vabsh_vv
*----------------------------------------------------------------------------*/
/*

VABSH
short32 = __vabsh_vv(short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vabssp_vv
*----------------------------------------------------------------------------*/
/*

VABSSP
float16 = __vabssp_vv(float16);

*/


/*-----------------------------------------------------------------------------
* ID: __vabsw_vv
*----------------------------------------------------------------------------*/
/*

VABSW
int16 = __vabsw_vv(int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vaddb_vkv
*----------------------------------------------------------------------------*/
/*

VADDB
char64 = __vaddb_vkv(char64, (char64)(k));
uchar64 = __vaddb_vkv(uchar64, (uchar64)(k));

*/

#define __vaddb_vkv(a,b) __overload("__vaddb_vkv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vaddb_vvv
*----------------------------------------------------------------------------*/
/*

VADDB
char64 = __vaddb_vvv(char64, char64);
uchar64 = __vaddb_vvv(uchar64, uchar64);

*/

#define __vaddb_vvv(a,b) __overload("__vaddb_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vaddcb_pvv
*----------------------------------------------------------------------------*/
/*

VADDCB
char64 = __vaddcb_pvv(__vpred, char64, char64);
uchar64 = __vaddcb_pvv(__vpred, uchar64, uchar64);

*/

#define __vaddcb_pvv(a,b,c) __overload("__vaddcb_pvv",(a),(b),(c))((a),(b),(c))


/*-----------------------------------------------------------------------------
* ID: __vaddcd_pvv
*----------------------------------------------------------------------------*/
/*

VADDCD
long8 = __vaddcd_pvv(__vpred, long8, long8);
ulong8 = __vaddcd_pvv(__vpred, ulong8, ulong8);

*/

#define __vaddcd_pvv(a,b,c) __overload("__vaddcd_pvv",(a),(b),(c))((a),(b),(c))


/*-----------------------------------------------------------------------------
* ID: __vaddch_pvv
*----------------------------------------------------------------------------*/
/*

VADDCH
short32 = __vaddch_pvv(__vpred, short32, short32);
ushort32 = __vaddch_pvv(__vpred, ushort32, ushort32);

*/

#define __vaddch_pvv(a,b,c) __overload("__vaddch_pvv",(a),(b),(c))((a),(b),(c))


/*-----------------------------------------------------------------------------
* ID: __vaddcw_pvv
*----------------------------------------------------------------------------*/
/*

VADDCW
int16 = __vaddcw_pvv(__vpred, int16, int16);
uint16 = __vaddcw_pvv(__vpred, uint16, uint16);

*/

#define __vaddcw_pvv(a,b,c) __overload("__vaddcw_pvv",(a),(b),(c))((a),(b),(c))


/*-----------------------------------------------------------------------------
* ID: __vaddd_vkv
*----------------------------------------------------------------------------*/
/*

VADDD
long8 = __vaddd_vkv(long8, (int8)(k));
ulong8 = __vaddd_vkv(ulong8, (uint8)(k={0-0x7fffffff}));

*/

#define __vaddd_vkv(a,b) __overload("__vaddd_vkv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vaddd_vvv
*----------------------------------------------------------------------------*/
/*

VADDD
long8 = __vaddd_vvv(long8, long8);
ulong8 = __vaddd_vvv(ulong8, ulong8);

*/

#define __vaddd_vvv(a,b) __overload("__vaddd_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vadddp_vvv
*----------------------------------------------------------------------------*/
/*

VADDDP
double8 = __vadddp_vvv(double8, double8);

*/


/*-----------------------------------------------------------------------------
* ID: __vaddh_vkv
*----------------------------------------------------------------------------*/
/*

VADDH
short32 = __vaddh_vkv(short32, (short32)(k));
ushort32 = __vaddh_vkv(ushort32, (ushort32)(k));

*/

#define __vaddh_vkv(a,b) __overload("__vaddh_vkv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vaddh_vvv
*----------------------------------------------------------------------------*/
/*

VADDH
short32 = __vaddh_vvv(short32, short32);
ushort32 = __vaddh_vvv(ushort32, ushort32);

*/

#define __vaddh_vvv(a,b) __overload("__vaddh_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vaddsp_vvv
*----------------------------------------------------------------------------*/
/*

VADDSP
float16 = __vaddsp_vvv(float16, float16);

*/


/*-----------------------------------------------------------------------------
* ID: __vaddw_vkv
*----------------------------------------------------------------------------*/
/*

VADDW
int16 = __vaddw_vkv(int16, (int16)(k));
uint16 = __vaddw_vkv(uint16, (uint16)(k));

*/

#define __vaddw_vkv(a,b) __overload("__vaddw_vkv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vaddw_vvv
*----------------------------------------------------------------------------*/
/*

VADDW
int16 = __vaddw_vvv(int16, int16);
uint16 = __vaddw_vvv(uint16, uint16);

*/

#define __vaddw_vvv(a,b) __overload("__vaddw_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vandnw_vkv
*----------------------------------------------------------------------------*/
/*

VANDNW
int16 = __vandnw_vkv(int16, (int16)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __vandnw_vvv
*----------------------------------------------------------------------------*/
/*

VANDNW
char64 = __vandnw_vvv(char64, char64);
short32 = __vandnw_vvv(short32, short32);
int16 = __vandnw_vvv(int16, int16);
long8 = __vandnw_vvv(long8, long8);

*/

#define __vandnw_vvv(a,b) __overload("__vandnw_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vandw_vkv
*----------------------------------------------------------------------------*/
/*

VANDW
int16 = __vandw_vkv(int16, (int16)(k));
uint16 = __vandw_vkv(uint16, (uint16)(k));

*/

#define __vandw_vkv(a,b) __overload("__vandw_vkv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vandw_vvv
*----------------------------------------------------------------------------*/
/*

VANDW
char64 = __vandw_vvv(char64, char64);
short32 = __vandw_vvv(short32, short32);
int16 = __vandw_vvv(int16, int16);
long8 = __vandw_vvv(long8, long8);
uchar64 = __vandw_vvv(uchar64, uchar64);
ushort32 = __vandw_vvv(ushort32, ushort32);
uint16 = __vandw_vvv(uint16, uint16);
ulong8 = __vandw_vvv(ulong8, ulong8);

*/

#define __vandw_vvv(a,b) __overload("__vandw_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vapysb_vvv
*----------------------------------------------------------------------------*/
/*

VAPYSB
char64 = __vapysb_vvv(char64, char64);

*/


/*-----------------------------------------------------------------------------
* ID: __vapysd_vvv
*----------------------------------------------------------------------------*/
/*

VAPYSD
long8 = __vapysd_vvv(long8, long8);

*/


/*-----------------------------------------------------------------------------
* ID: __vapysh_vvv
*----------------------------------------------------------------------------*/
/*

VAPYSH
short32 = __vapysh_vvv(short32, short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vapysw_vvv
*----------------------------------------------------------------------------*/
/*

VAPYSW
int16 = __vapysw_vvv(int16, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vavgb_vvv
*----------------------------------------------------------------------------*/
/*

VAVGB
char64 = __vavgb_vvv(char64, char64);

*/


/*-----------------------------------------------------------------------------
* ID: __vavgd_vvv
*----------------------------------------------------------------------------*/
/*

VAVGD
long8 = __vavgd_vvv(long8, long8);

*/


/*-----------------------------------------------------------------------------
* ID: __vavgh_vvv
*----------------------------------------------------------------------------*/
/*

VAVGH
short32 = __vavgh_vvv(short32, short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vavgnrb_vvv
*----------------------------------------------------------------------------*/
/*

VAVGNRB
char64 = __vavgnrb_vvv(char64, char64);

*/


/*-----------------------------------------------------------------------------
* ID: __vavgnrd_vvv
*----------------------------------------------------------------------------*/
/*

VAVGNRD
long8 = __vavgnrd_vvv(long8, long8);

*/


/*-----------------------------------------------------------------------------
* ID: __vavgnrh_vvv
*----------------------------------------------------------------------------*/
/*

VAVGNRH
short32 = __vavgnrh_vvv(short32, short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vavgnrub_vvv
*----------------------------------------------------------------------------*/
/*

VAVGNRUB
uchar64 = __vavgnrub_vvv(uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vavgnrud_vvv
*----------------------------------------------------------------------------*/
/*

VAVGNRUD
ulong8 = __vavgnrud_vvv(ulong8, ulong8);

*/


/*-----------------------------------------------------------------------------
* ID: __vavgnruh_vvv
*----------------------------------------------------------------------------*/
/*

VAVGNRUH
ushort32 = __vavgnruh_vvv(ushort32, ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vavgnruw_vvv
*----------------------------------------------------------------------------*/
/*

VAVGNRUW
uint16 = __vavgnruw_vvv(uint16, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vavgnrw_vvv
*----------------------------------------------------------------------------*/
/*

VAVGNRW
int16 = __vavgnrw_vvv(int16, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vavgub_vvv
*----------------------------------------------------------------------------*/
/*

VAVGUB
uchar64 = __vavgub_vvv(uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vavgud_vvv
*----------------------------------------------------------------------------*/
/*

VAVGUD
ulong8 = __vavgud_vvv(ulong8, ulong8);

*/


/*-----------------------------------------------------------------------------
* ID: __vavguh_vvv
*----------------------------------------------------------------------------*/
/*

VAVGUH
ushort32 = __vavguh_vvv(ushort32, ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vavguw_vvv
*----------------------------------------------------------------------------*/
/*

VAVGUW
uint16 = __vavguw_vvv(uint16, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vavgw_vvv
*----------------------------------------------------------------------------*/
/*

VAVGW
int16 = __vavgw_vvv(int16, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vbinlogw_vv
*----------------------------------------------------------------------------*/
/*

VBINLOGW
uint16 = __vbinlogw_vv(uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vbitcntb_vv
*----------------------------------------------------------------------------*/
/*

VBITCNTB
char64 = __vbitcntb_vv(char64);
uchar64 = __vbitcntb_vv(uchar64);

*/

#define __vbitcntb_vv(a) __overload("__vbitcntb_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vbitcntd_vv
*----------------------------------------------------------------------------*/
/*

VBITCNTD
long8 = __vbitcntd_vv(long8);
ulong8 = __vbitcntd_vv(ulong8);

*/

#define __vbitcntd_vv(a) __overload("__vbitcntd_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vbitcnth_vv
*----------------------------------------------------------------------------*/
/*

VBITCNTH
short32 = __vbitcnth_vv(short32);
ushort32 = __vbitcnth_vv(ushort32);

*/

#define __vbitcnth_vv(a) __overload("__vbitcnth_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vbitcntw_vv
*----------------------------------------------------------------------------*/
/*

VBITCNTW
int16 = __vbitcntw_vv(int16);
uint16 = __vbitcntw_vv(uint16);

*/

#define __vbitcntw_vv(a) __overload("__vbitcntw_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vbitdeald_vv
*----------------------------------------------------------------------------*/
/*

VBITDEALD
long8 = __vbitdeald_vv(long8);
ulong8 = __vbitdeald_vv(ulong8);

*/

#define __vbitdeald_vv(a) __overload("__vbitdeald_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vbitdealw_vv
*----------------------------------------------------------------------------*/
/*

VBITDEALW
int16 = __vbitdealw_vv(int16);
uint16 = __vbitdealw_vv(uint16);

*/

#define __vbitdealw_vv(a) __overload("__vbitdealw_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vbitrd_vv
*----------------------------------------------------------------------------*/
/*

VBITRD
long8 = __vbitrd_vv(long8);
ulong8 = __vbitrd_vv(ulong8);

*/

#define __vbitrd_vv(a) __overload("__vbitrd_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vbitrw_vv
*----------------------------------------------------------------------------*/
/*

VBITRW
int16 = __vbitrw_vv(int16);
uint16 = __vbitrw_vv(uint16);

*/

#define __vbitrw_vv(a) __overload("__vbitrw_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vbitshfld_vv
*----------------------------------------------------------------------------*/
/*

VBITSHFLD
long8 = __vbitshfld_vv(long8);
ulong8 = __vbitshfld_vv(ulong8);

*/

#define __vbitshfld_vv(a) __overload("__vbitshfld_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vbitshflw_vv
*----------------------------------------------------------------------------*/
/*

VBITSHFLW
int16 = __vbitshflw_vv(int16);
uint16 = __vbitshflw_vv(uint16);

*/

#define __vbitshflw_vv(a) __overload("__vbitshflw_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vbittran8b_vv
*----------------------------------------------------------------------------*/
/*

VBITTRAN8B
uchar64 = __vbittran8b_vv(uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vbpackh_vvv
*----------------------------------------------------------------------------*/
/*

VBPACKH
char64 = __vbpackh_vvv(char64, char64);
uchar64 = __vbpackh_vvv(uchar64, uchar64);

*/

#define __vbpackh_vvv(a,b) __overload("__vbpackh_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vbpackl_vvv
*----------------------------------------------------------------------------*/
/*

VBPACKL
char64 = __vbpackl_vvv(char64, char64);
uchar64 = __vbpackl_vvv(uchar64, uchar64);

*/

#define __vbpackl_vvv(a,b) __overload("__vbpackl_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vbunpkd_vv
*----------------------------------------------------------------------------*/
/*

VBUNPKD
long8 = __vbunpkd_vv(char8);

*/


/*-----------------------------------------------------------------------------
* ID: __vbunpkdu_vv
*----------------------------------------------------------------------------*/
/*

VBUNPKDU
ulong8 = __vbunpkdu_vv(uchar8);

*/


/*-----------------------------------------------------------------------------
* ID: __vbunpkh_vv
*----------------------------------------------------------------------------*/
/*

VBUNPKH
short32 = __vbunpkh_vv(char32);

*/


/*-----------------------------------------------------------------------------
* ID: __vbunpkhh_vv
*----------------------------------------------------------------------------*/
/*

VBUNPKHH
short32 = __vbunpkhh_vv(char64);

*/


/*-----------------------------------------------------------------------------
* ID: __vbunpkhl_vv
*----------------------------------------------------------------------------*/
/*

VBUNPKHL
short32 = __vbunpkhl_vv(char64);

*/


/*-----------------------------------------------------------------------------
* ID: __vbunpkhu_vv
*----------------------------------------------------------------------------*/
/*

VBUNPKHU
ushort32 = __vbunpkhu_vv(uchar32);

*/


/*-----------------------------------------------------------------------------
* ID: __vbunpkuhh_vv
*----------------------------------------------------------------------------*/
/*

VBUNPKUHH
ushort32 = __vbunpkuhh_vv(uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vbunpkuhl_vv
*----------------------------------------------------------------------------*/
/*

VBUNPKUHL
ushort32 = __vbunpkuhl_vv(uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vbunpkw_vv
*----------------------------------------------------------------------------*/
/*

VBUNPKW
int16 = __vbunpkw_vv(char16);

*/


/*-----------------------------------------------------------------------------
* ID: __vbunpkwu_vv
*----------------------------------------------------------------------------*/
/*

VBUNPKWU
uint16 = __vbunpkwu_vv(uchar16);

*/


/*-----------------------------------------------------------------------------
* ID: __vccdotp2hw_vvv
*----------------------------------------------------------------------------*/
/*

VCCDOTP2HW
cint8 = __vccdotp2hw_vvv(cshort16, cshort16);

*/


/*-----------------------------------------------------------------------------
* ID: __vccmatmpyhw{_se}_vww
*----------------------------------------------------------------------------*/
/*

VCCMATMPYHW
__vccmatmpyhw_vww(cshort16, cshort16, cshort16, cint8&, cint8&);

__vccmatmpyhw_se_vww(cshort16, __SE_REG_PAIR, cint8&, cint8&);

*/


/*-----------------------------------------------------------------------------
* ID: __vccmatmpyr1hh{_se}_vwv
*----------------------------------------------------------------------------*/
/*

VCCMATMPYR1HH
cshort16 = __vccmatmpyr1hh_vwv(cshort16, cshort16, cshort16);

cshort16 = __vccmatmpyr1hh_se_vwv(cshort16, __SE_REG_PAIR);

*/


/*-----------------------------------------------------------------------------
* ID: __vccmpyhw_vvw
*----------------------------------------------------------------------------*/
/*

VCCMPYHW
__vccmpyhw_vvw(cshort16, cshort16, cint8&, cint8&);

*/


/*-----------------------------------------------------------------------------
* ID: __vccmpyr1hh_vvv
*----------------------------------------------------------------------------*/
/*

VCCMPYR1HH
cshort16 = __vccmpyr1hh_vvv(cshort16, cshort16);

*/


/*-----------------------------------------------------------------------------
* ID: __vccmpyr1ww_vvv
*----------------------------------------------------------------------------*/
/*

VCCMPYR1WW
cint8 = __vccmpyr1ww_vvv(cint8, cint8);

*/


/*-----------------------------------------------------------------------------
* ID: __vcdotp2hw_vvv
*----------------------------------------------------------------------------*/
/*

VCDOTP2HW
cint8 = __vcdotp2hw_vvv(cshort16, cshort16);

*/


/*-----------------------------------------------------------------------------
* ID: __vcdotpm2opn16b32h_yvvv
*----------------------------------------------------------------------------*/
/*

VCDOTPM2OPN16B32H
cshort16 = __vcdotpm2opn16b32h_yvvv(ushort32, ulong, cchar32);

*/


/*-----------------------------------------------------------------------------
* ID: __vcdotpm2opn1h32h_yvvv
*----------------------------------------------------------------------------*/
/*

VCDOTPM2OPN1H32H
cshort16 = __vcdotpm2opn1h32h_yvvv(ushort32, uint, cshort16);

*/


/*-----------------------------------------------------------------------------
* ID: __vcdotpm2opn8h16w_yvvv
*----------------------------------------------------------------------------*/
/*

VCDOTPM2OPN8H16W
cint8 = __vcdotpm2opn8h16w_yvvv(ulong8, uint4, cshort8);

*/


/*-----------------------------------------------------------------------------
* ID: __vcdotpm2opn8w16w_yvvv
*----------------------------------------------------------------------------*/
/*

VCDOTPM2OPN8W16W
cint8 = __vcdotpm2opn8w16w_yvvv(ulong8, uint4, cint8);

*/


/*-----------------------------------------------------------------------------
* ID: __vcdotpm32opn16b32h_yvvv
*----------------------------------------------------------------------------*/
/*

VCDOTPM32OPN16B32H
cshort16 = __vcdotpm32opn16b32h_yvvv(ushort32, ulong4, cchar32);

*/


/*-----------------------------------------------------------------------------
* ID: __vclassdp_vv
*----------------------------------------------------------------------------*/
/*

VCLASSDP
long8 = __vclassdp_vv(double8);

*/


/*-----------------------------------------------------------------------------
* ID: __vclasssp_vv
*----------------------------------------------------------------------------*/
/*

VCLASSSP
int16 = __vclasssp_vv(float16);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmatmpyhw{_se}_vww
*----------------------------------------------------------------------------*/
/*

VCMATMPYHW
__vcmatmpyhw_vww(cshort16, cshort16, cshort16, cint8&, cint8&);

__vcmatmpyhw_se_vww(cshort16, __SE_REG_PAIR, cint8&, cint8&);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmatmpyr1hh{_se}_vwv
*----------------------------------------------------------------------------*/
/*

VCMATMPYR1HH
cshort16 = __vcmatmpyr1hh_vwv(cshort16, cshort16, cshort16);

cshort16 = __vcmatmpyr1hh_se_vwv(cshort16, __SE_REG_PAIR);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmaxb_vvv
*----------------------------------------------------------------------------*/
/*

VCMAXB
char64 = __vcmaxb_vvv(char64, char64);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmaxh_vvv
*----------------------------------------------------------------------------*/
/*

VCMAXH
short32 = __vcmaxh_vvv(short32, short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmaxpb_vvp
*----------------------------------------------------------------------------*/
/*

VCMAXPB
__vcmaxpb_vvp(char64, char64&, __vpred&);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmaxph_vvp
*----------------------------------------------------------------------------*/
/*

VCMAXPH
__vcmaxph_vvp(short32, short32&, __vpred&);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmpeqb_vvp
*----------------------------------------------------------------------------*/
/*

VCMPEQB
__vpred = __vcmpeqb_vvp(char64, char64);
__vpred = __vcmpeqb_vvp(uchar64, uchar64);

*/

#define __vcmpeqb_vvp(a,b) __overload("__vcmpeqb_vvp",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vcmpeqd_vvp
*----------------------------------------------------------------------------*/
/*

VCMPEQD
__vpred = __vcmpeqd_vvp(long8, long8);
__vpred = __vcmpeqd_vvp(ulong8, ulong8);

*/

#define __vcmpeqd_vvp(a,b) __overload("__vcmpeqd_vvp",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vcmpeqdp_vvp
*----------------------------------------------------------------------------*/
/*

VCMPEQDP
__vpred = __vcmpeqdp_vvp(double8, double8);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmpeqh_vvp
*----------------------------------------------------------------------------*/
/*

VCMPEQH
__vpred = __vcmpeqh_vvp(short32, short32);
__vpred = __vcmpeqh_vvp(ushort32, ushort32);

*/

#define __vcmpeqh_vvp(a,b) __overload("__vcmpeqh_vvp",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vcmpeqsp_vvp
*----------------------------------------------------------------------------*/
/*

VCMPEQSP
__vpred = __vcmpeqsp_vvp(float16, float16);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmpeqw_vvp
*----------------------------------------------------------------------------*/
/*

VCMPEQW
__vpred = __vcmpeqw_vvp(int16, int16);
__vpred = __vcmpeqw_vvp(uint16, uint16);

*/

#define __vcmpeqw_vvp(a,b) __overload("__vcmpeqw_vvp",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vcmpgeb_vvp
*----------------------------------------------------------------------------*/
/*

VCMPGEB
__vpred = __vcmpgeb_vvp(char64, char64);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmpged_vvp
*----------------------------------------------------------------------------*/
/*

VCMPGED
__vpred = __vcmpged_vvp(long8, long8);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmpgeh_vvp
*----------------------------------------------------------------------------*/
/*

VCMPGEH
__vpred = __vcmpgeh_vvp(short32, short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmpgeub_vvp
*----------------------------------------------------------------------------*/
/*

VCMPGEUB
__vpred = __vcmpgeub_vvp(uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmpgeud_vvp
*----------------------------------------------------------------------------*/
/*

VCMPGEUD
__vpred = __vcmpgeud_vvp(ulong8, ulong8);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmpgeuh_vvp
*----------------------------------------------------------------------------*/
/*

VCMPGEUH
__vpred = __vcmpgeuh_vvp(ushort32, ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmpgeuw_vvp
*----------------------------------------------------------------------------*/
/*

VCMPGEUW
__vpred = __vcmpgeuw_vvp(uint16, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmpgew_vvp
*----------------------------------------------------------------------------*/
/*

VCMPGEW
__vpred = __vcmpgew_vvp(int16, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmpgtb_vvp
*----------------------------------------------------------------------------*/
/*

VCMPGTB
__vpred = __vcmpgtb_vvp(char64, char64);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmpgtd_vvp
*----------------------------------------------------------------------------*/
/*

VCMPGTD
__vpred = __vcmpgtd_vvp(long8, long8);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmpgth_vvp
*----------------------------------------------------------------------------*/
/*

VCMPGTH
__vpred = __vcmpgth_vvp(short32, short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmpgtub_vvp
*----------------------------------------------------------------------------*/
/*

VCMPGTUB
__vpred = __vcmpgtub_vvp(uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmpgtud_vvp
*----------------------------------------------------------------------------*/
/*

VCMPGTUD
__vpred = __vcmpgtud_vvp(ulong8, ulong8);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmpgtuh_vvp
*----------------------------------------------------------------------------*/
/*

VCMPGTUH
__vpred = __vcmpgtuh_vvp(ushort32, ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmpgtuw_vvp
*----------------------------------------------------------------------------*/
/*

VCMPGTUW
__vpred = __vcmpgtuw_vvp(uint16, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmpgtw_vvp
*----------------------------------------------------------------------------*/
/*

VCMPGTW
__vpred = __vcmpgtw_vvp(int16, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmpledp_vvp
*----------------------------------------------------------------------------*/
/*

VCMPLEDP
__vpred = __vcmpledp_vvp(double8, double8);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmplesp_vvp
*----------------------------------------------------------------------------*/
/*

VCMPLESP
__vpred = __vcmplesp_vvp(float16, float16);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmpltdp_vvp
*----------------------------------------------------------------------------*/
/*

VCMPLTDP
__vpred = __vcmpltdp_vvp(double8, double8);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmpltsp_vvp
*----------------------------------------------------------------------------*/
/*

VCMPLTSP
__vpred = __vcmpltsp_vvp(float16, float16);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmpyhw_vvw
*----------------------------------------------------------------------------*/
/*

VCMPYHW
__vcmpyhw_vvw(cshort16, cshort16, cint8&, cint8&);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmpyr1hh_vvv
*----------------------------------------------------------------------------*/
/*

VCMPYR1HH
cshort16 = __vcmpyr1hh_vvv(cshort16, cshort16);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmpyr1ww_vvv
*----------------------------------------------------------------------------*/
/*

VCMPYR1WW
cint8 = __vcmpyr1ww_vvv(cint8, cint8);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmpyrhh_vvv
*----------------------------------------------------------------------------*/
/*

VCMPYRHH
cshort16 = __vcmpyrhh_vvv(cshort16, cshort16);

*/


/*-----------------------------------------------------------------------------
* ID: __vcmpysp_vvw
*----------------------------------------------------------------------------*/
/*

VCMPYSP
__vcmpysp_vvw(cfloat8, cfloat8, float16&, float16&);

*/


/*-----------------------------------------------------------------------------
* ID: __vcrot270h_vv
*----------------------------------------------------------------------------*/
/*

VCROT270H
cshort16 = __vcrot270h_vv(cshort16);

*/


/*-----------------------------------------------------------------------------
* ID: __vcrot270sp_vv
*----------------------------------------------------------------------------*/
/*

VCROT270SP
cfloat8 = __vcrot270sp_vv(cfloat8);

*/


/*-----------------------------------------------------------------------------
* ID: __vcrot270w_vv
*----------------------------------------------------------------------------*/
/*

VCROT270W
cint8 = __vcrot270w_vv(cint8);

*/


/*-----------------------------------------------------------------------------
* ID: __vcrot90h_vv
*----------------------------------------------------------------------------*/
/*

VCROT90H
cshort16 = __vcrot90h_vv(cshort16);

*/


/*-----------------------------------------------------------------------------
* ID: __vcrot90sp_vv
*----------------------------------------------------------------------------*/
/*

VCROT90SP
cfloat8 = __vcrot90sp_vv(cfloat8);

*/


/*-----------------------------------------------------------------------------
* ID: __vcrot90w_vv
*----------------------------------------------------------------------------*/
/*

VCROT90W
cint8 = __vcrot90w_vv(cint8);

*/


/*-----------------------------------------------------------------------------
* ID: __vdeal2b_vv
*----------------------------------------------------------------------------*/
/*

VDEAL2B
char64 = __vdeal2b_vv(char64);
uchar64 = __vdeal2b_vv(uchar64);

*/

#define __vdeal2b_vv(a) __overload("__vdeal2b_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vdeal2h_vv
*----------------------------------------------------------------------------*/
/*

VDEAL2H
short32 = __vdeal2h_vv(short32);
ushort32 = __vdeal2h_vv(ushort32);
cchar32 = __vdeal2h_vv(cchar32);

*/

#define __vdeal2h_vv(a) __overload("__vdeal2h_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vdeal2w_vv
*----------------------------------------------------------------------------*/
/*

VDEAL2W
int16 = __vdeal2w_vv(int16);
float16 = __vdeal2w_vv(float16);
uint16 = __vdeal2w_vv(uint16);
cshort16 = __vdeal2w_vv(cshort16);

*/

#define __vdeal2w_vv(a) __overload("__vdeal2w_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vdeal2d_vv
*----------------------------------------------------------------------------*/
/*

VDEAL2D
long8 = __vdeal2d_vv(long8);
double8 = __vdeal2d_vv(double8);
cfloat8 = __vdeal2d_vv(cfloat8);
ulong8 = __vdeal2d_vv(ulong8);
cint8 = __vdeal2d_vv(cint8);

*/

#define __vdeal2d_vv(a) __overload("__vdeal2d_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vdeal4b_vv
*----------------------------------------------------------------------------*/
/*

VDEAL4B
char64 = __vdeal4b_vv(char64);
uchar64 = __vdeal4b_vv(uchar64);

*/

#define __vdeal4b_vv(a) __overload("__vdeal4b_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vdeal4h_vv
*----------------------------------------------------------------------------*/
/*

VDEAL4H
short32 = __vdeal4h_vv(short32);
ushort32 = __vdeal4h_vv(ushort32);
cchar32 = __vdeal4h_vv(cchar32);

*/

#define __vdeal4h_vv(a) __overload("__vdeal4h_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vdotp2hd_vvw
*----------------------------------------------------------------------------*/
/*

VDOTP2HD
__vdotp2hd_vvw(short32, short32, long8&, long8&);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotp2hw_vvv
*----------------------------------------------------------------------------*/
/*

VDOTP2HW
int16 = __vdotp2hw_vvv(short32, short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotp2nwd_vvv
*----------------------------------------------------------------------------*/
/*

VDOTP2NWD
long8 = __vdotp2nwd_vvv(int16, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotp2nxwd_vvv
*----------------------------------------------------------------------------*/
/*

VDOTP2NXWD
long8 = __vdotp2nxwd_vvv(int16, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotp2subh_vvv
*----------------------------------------------------------------------------*/
/*

VDOTP2SUBH
short32 = __vdotp2subh_vvv(char64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotp2suhd_vvw
*----------------------------------------------------------------------------*/
/*

VDOTP2SUHD
__vdotp2suhd_vvw(short32, ushort32, long8&, long8&);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotp2suhw_vvv
*----------------------------------------------------------------------------*/
/*

VDOTP2SUHW
int16 = __vdotp2suhw_vvv(short32, ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotp2ubh_vvv
*----------------------------------------------------------------------------*/
/*

VDOTP2UBH
ushort32 = __vdotp2ubh_vvv(uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotp2uhd_vvw
*----------------------------------------------------------------------------*/
/*

VDOTP2UHD
__vdotp2uhd_vvw(ushort32, ushort32, ulong8&, ulong8&);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotp2uhw_vvv
*----------------------------------------------------------------------------*/
/*

VDOTP2UHW
uint16 = __vdotp2uhw_vvv(ushort32, ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotp2wd_vvv
*----------------------------------------------------------------------------*/
/*

VDOTP2WD
long8 = __vdotp2wd_vvv(int16, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotp2xwd_vvv
*----------------------------------------------------------------------------*/
/*

VDOTP2XWD
long8 = __vdotp2xwd_vvv(int16, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotp4hd_vvv
*----------------------------------------------------------------------------*/
/*

VDOTP4HD
long8 = __vdotp4hd_vvv(short32, short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotp4hw{_se1,_se2,_se12}_wwv
*----------------------------------------------------------------------------*/
/*

VDOTP4HW
int16 = __vdotp4hw_wwv(short32, short32, short32, short32);

int16 = __vdotp4hw_se1_wwv(__SE_REG_PAIR, short32, short32);
int16 = __vdotp4hw_se2_wwv(short32, short32, __SE_REG_PAIR);
int16 = __vdotp4hw_se12_wwv(__SE_REG_PAIR, __SE_REG_PAIR);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotp4subw_vvv
*----------------------------------------------------------------------------*/
/*

VDOTP4SUBW
int16 = __vdotp4subw_vvv(char64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotp4suhd_vvv
*----------------------------------------------------------------------------*/
/*

VDOTP4SUHD
long8 = __vdotp4suhd_vvv(short32, ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotp4suhw{_se1,_se2,_se12}_wwv
*----------------------------------------------------------------------------*/
/*

VDOTP4SUHW
int16 = __vdotp4suhw_wwv(short32, short32, ushort32, ushort32);

int16 = __vdotp4suhw_se1_wwv(__SE_REG_PAIR, ushort32, ushort32);
int16 = __vdotp4suhw_se2_wwv(short32, short32, __SE_REG_PAIR);
int16 = __vdotp4suhw_se12_wwv(__SE_REG_PAIR, __SE_REG_PAIR);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotp4ubw_vvv
*----------------------------------------------------------------------------*/
/*

VDOTP4UBW
uint16 = __vdotp4ubw_vvv(uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotp4uhd_vvv
*----------------------------------------------------------------------------*/
/*

VDOTP4UHD
ulong8 = __vdotp4uhd_vvv(ushort32, ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotp8subw_vvv
*----------------------------------------------------------------------------*/
/*

VDOTP8SUBW
int16 = __vdotp8subw_vvv(char64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotpmpn16b32h_yvvv
*----------------------------------------------------------------------------*/
/*

VDOTPMPN16B32H
short32 = __vdotpmpn16b32h_yvvv(ushort32, ushort32, char16);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotpmpn16h16w_yvvv
*----------------------------------------------------------------------------*/
/*

VDOTPMPN16H16W
int16 = __vdotpmpn16h16w_yvvv(ushort32, ushort16, short16);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotpmpn16w8d_yvvv
*----------------------------------------------------------------------------*/
/*

VDOTPMPN16W8D
long8 = __vdotpmpn16w8d_yvvv(ushort32, ushort8, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotpmpn32b16h_yvvv
*----------------------------------------------------------------------------*/
/*

VDOTPMPN32B16H
short16 = __vdotpmpn32b16h_yvvv(uint16, uint16, char32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotpmpn32b16w_yvvv
*----------------------------------------------------------------------------*/
/*

VDOTPMPN32B16W
int16 = __vdotpmpn32b16w_yvvv(uint16, uint16, char32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotpmpn32h8w_yvvv
*----------------------------------------------------------------------------*/
/*

VDOTPMPN32H8W
int8 = __vdotpmpn32h8w_yvvv(uint8, uint8, short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotpmpnu16h16w_yvvv
*----------------------------------------------------------------------------*/
/*

VDOTPMPNU16H16W
uint16 = __vdotpmpnu16h16w_yvvv(ushort32, ushort16, ushort16);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotpmpnu16w8d_yvvv
*----------------------------------------------------------------------------*/
/*

VDOTPMPNU16W8D
ulong8 = __vdotpmpnu16w8d_yvvv(ushort32, ushort8, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotpmpnu32b16h_yvvv
*----------------------------------------------------------------------------*/
/*

VDOTPMPNU32B16H
ushort16 = __vdotpmpnu32b16h_yvvv(uint16, uint16, uchar32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotpmpnu32b16w_yvvv
*----------------------------------------------------------------------------*/
/*

VDOTPMPNU32B16W
uint16 = __vdotpmpnu32b16w_yvvv(uint16, uint16, uchar32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdotpmpnu32h8w_yvvv
*----------------------------------------------------------------------------*/
/*

VDOTPMPNU32H8W
uint8 = __vdotpmpnu32h8w_yvvv(uint8, uint8, ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdpackh_vvv
*----------------------------------------------------------------------------*/
/*

VDPACKH
long8 = __vdpackh_vvv(long8, long8);
double8 = __vdpackh_vvv(double8, double8);
cfloat8 = __vdpackh_vvv(cfloat8, cfloat8);
ulong8 = __vdpackh_vvv(ulong8, ulong8);
cint8 = __vdpackh_vvv(cint8, cint8);

*/

#define __vdpackh_vvv(a,b) __overload("__vdpackh_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vdpackl_vvv
*----------------------------------------------------------------------------*/
/*

VDPACKL
long8 = __vdpackl_vvv(long8, long8);
double8 = __vdpackl_vvv(double8, double8);
cfloat8 = __vdpackl_vvv(cfloat8, cfloat8);
ulong8 = __vdpackl_vvv(ulong8, ulong8);
cint8 = __vdpackl_vvv(cint8, cint8);

*/

#define __vdpackl_vvv(a,b) __overload("__vdpackl_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vdpint_vv
*----------------------------------------------------------------------------*/
/*

VDPINT
int16 = __vdpint_vv(double8);

*/


/*-----------------------------------------------------------------------------
* ID: __vdpsp_vv
*----------------------------------------------------------------------------*/
/*

VDPSP
float16 = __vdpsp_vv(double8);

*/


/*-----------------------------------------------------------------------------
* ID: __vdptrunc_vv
*----------------------------------------------------------------------------*/
/*

VDPTRUNC
int16 = __vdptrunc_vv(double8);

*/


/*-----------------------------------------------------------------------------
* ID: __vdsad16ou8h8w_vvv
*----------------------------------------------------------------------------*/
/*

VDSAD16OU8H8W
uint16 = __vdsad16ou8h8w_vvv(ushort32, ushort16);

*/


/*-----------------------------------------------------------------------------
* ID: __vdsad8ou16b16h_vvv
*----------------------------------------------------------------------------*/
/*

VDSAD8OU16B16H
ushort32 = __vdsad8ou16b16h_vvv(uchar64, uchar32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdsadm16ou8h8w_yvvv
*----------------------------------------------------------------------------*/
/*

VDSADM16OU8H8W
uint16 = __vdsadm16ou8h8w_yvvv(uchar64, ushort32, ushort16);

*/


/*-----------------------------------------------------------------------------
* ID: __vdsadm8ou16b16h_yvvv
*----------------------------------------------------------------------------*/
/*

VDSADM8OU16B16H
ushort32 = __vdsadm8ou16b16h_yvvv(uchar64, uchar64, uchar32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdsortddh_vv
*----------------------------------------------------------------------------*/
/*

VDSORTDDH
short32 = __vdsortddh_vv(short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdsortdduh_vv
*----------------------------------------------------------------------------*/
/*

VDSORTDDUH
ushort32 = __vdsortdduh_vv(ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdsortdih_vv
*----------------------------------------------------------------------------*/
/*

VDSORTDIH
short32 = __vdsortdih_vv(short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdsortdiuh_vv
*----------------------------------------------------------------------------*/
/*

VDSORTDIUH
ushort32 = __vdsortdiuh_vv(ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdsortidh_vv
*----------------------------------------------------------------------------*/
/*

VDSORTIDH
short32 = __vdsortidh_vv(short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdsortiduh_vv
*----------------------------------------------------------------------------*/
/*

VDSORTIDUH
ushort32 = __vdsortiduh_vv(ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdsortiih_vv
*----------------------------------------------------------------------------*/
/*

VDSORTIIH
short32 = __vdsortiih_vv(short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdsortiiuh_vv
*----------------------------------------------------------------------------*/
/*

VDSORTIIUH
ushort32 = __vdsortiiuh_vv(ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdsortpddh_vv
*----------------------------------------------------------------------------*/
/*

VDSORTPDDH
uchar64 = __vdsortpddh_vv(short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdsortpdduh_vv
*----------------------------------------------------------------------------*/
/*

VDSORTPDDUH
uchar64 = __vdsortpdduh_vv(ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdsortpdih_vv
*----------------------------------------------------------------------------*/
/*

VDSORTPDIH
uchar64 = __vdsortpdih_vv(short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdsortpdiuh_vv
*----------------------------------------------------------------------------*/
/*

VDSORTPDIUH
uchar64 = __vdsortpdiuh_vv(ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdsortpidh_vv
*----------------------------------------------------------------------------*/
/*

VDSORTPIDH
uchar64 = __vdsortpidh_vv(short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdsortpiduh_vv
*----------------------------------------------------------------------------*/
/*

VDSORTPIDUH
uchar64 = __vdsortpiduh_vv(ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdsortpiih_vv
*----------------------------------------------------------------------------*/
/*

VDSORTPIIH
uchar64 = __vdsortpiih_vv(short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdsortpiiuh_vv
*----------------------------------------------------------------------------*/
/*

VDSORTPIIUH
uchar64 = __vdsortpiiuh_vv(ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vdup16b_vv
*----------------------------------------------------------------------------*/
/*

VDUP16B
char64 = __vdup16b_vv(char4);
uchar64 = __vdup16b_vv(uchar4);

*/

#define __vdup16b_vv(a) __overload("__vdup16b_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vdup16h_vv
*----------------------------------------------------------------------------*/
/*

VDUP16H
short32 = __vdup16h_vv(short2);
ushort32 = __vdup16h_vv(ushort2);
cchar32 = __vdup16h_vv(cchar2);

*/

#define __vdup16h_vv(a) __overload("__vdup16h_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vdup2b_vv
*----------------------------------------------------------------------------*/
/*

VDUP2B
char64 = __vdup2b_vv(char32);
uchar64 = __vdup2b_vv(uchar32);

*/

#define __vdup2b_vv(a) __overload("__vdup2b_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vdup2d_vv
*----------------------------------------------------------------------------*/
/*

VDUP2D
long8 = __vdup2d_vv(long4);
double8 = __vdup2d_vv(double4);
cfloat8 = __vdup2d_vv(cfloat4);
ulong8 = __vdup2d_vv(ulong4);
cint8 = __vdup2d_vv(cint4);

*/

#define __vdup2d_vv(a) __overload("__vdup2d_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vdup2h_vv
*----------------------------------------------------------------------------*/
/*

VDUP2H
short32 = __vdup2h_vv(short16);
ushort32 = __vdup2h_vv(ushort16);
cchar32 = __vdup2h_vv(cchar16);

*/

#define __vdup2h_vv(a) __overload("__vdup2h_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vdup2w_vv
*----------------------------------------------------------------------------*/
/*

VDUP2W
int16 = __vdup2w_vv(int8);
float16 = __vdup2w_vv(float8);
uint16 = __vdup2w_vv(uint8);
cshort16 = __vdup2w_vv(cshort8);

*/

#define __vdup2w_vv(a) __overload("__vdup2w_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vdup32b_vv
*----------------------------------------------------------------------------*/
/*

VDUP32B
char64 = __vdup32b_vv(char2);
uchar64 = __vdup32b_vv(uchar2);

*/

#define __vdup32b_vv(a) __overload("__vdup32b_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vdup4b_vv
*----------------------------------------------------------------------------*/
/*

VDUP4B
char64 = __vdup4b_vv(char16);
uchar64 = __vdup4b_vv(uchar16);

*/

#define __vdup4b_vv(a) __overload("__vdup4b_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vdup4d_vv
*----------------------------------------------------------------------------*/
/*

VDUP4D
long8 = __vdup4d_vv(long2);
double8 = __vdup4d_vv(double2);
cfloat8 = __vdup4d_vv(cfloat2);
ulong8 = __vdup4d_vv(ulong2);
cint8 = __vdup4d_vv(cint2);

*/

#define __vdup4d_vv(a) __overload("__vdup4d_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vdup4h_vv
*----------------------------------------------------------------------------*/
/*

VDUP4H
short32 = __vdup4h_vv(short8);
ushort32 = __vdup4h_vv(ushort8);
cchar32 = __vdup4h_vv(cchar8);

*/

#define __vdup4h_vv(a) __overload("__vdup4h_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vdup4w_vv
*----------------------------------------------------------------------------*/
/*

VDUP4W
int16 = __vdup4w_vv(int4);
float16 = __vdup4w_vv(float4);
uint16 = __vdup4w_vv(uint4);
cshort16 = __vdup4w_vv(cshort4);

*/

#define __vdup4w_vv(a) __overload("__vdup4w_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vdup8b_vv
*----------------------------------------------------------------------------*/
/*

VDUP8B
char64 = __vdup8b_vv(char8);
uchar64 = __vdup8b_vv(uchar8);

*/

#define __vdup8b_vv(a) __overload("__vdup8b_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vdup8h_vv
*----------------------------------------------------------------------------*/
/*

VDUP8H
short32 = __vdup8h_vv(short4);
ushort32 = __vdup8h_vv(ushort4);
cchar32 = __vdup8h_vv(cchar4);

*/

#define __vdup8h_vv(a) __overload("__vdup8h_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vdup8w_vv
*----------------------------------------------------------------------------*/
/*

VDUP8W
int16 = __vdup8w_vv(int2);
float16 = __vdup8w_vv(float2);
uint16 = __vdup8w_vv(uint2);
cshort16 = __vdup8w_vv(cshort2);

*/

#define __vdup8w_vv(a) __overload("__vdup8w_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vdupb_kv
*----------------------------------------------------------------------------*/
/*

VDUPB
char64 = __vdupb_kv((char)(k));
uchar64 = __vdupb_kv((uchar)(k));

*/

#define __vdupb_kv(a) __overload("__vdupb_kv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vdupb_rv
*----------------------------------------------------------------------------*/
/*

VDUPB
char64 = __vdupb_rv(char);
uchar64 = __vdupb_rv(uchar);

*/

#define __vdupb_rv(a) __overload("__vdupb_rv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vdupd_dv
*----------------------------------------------------------------------------*/
/*

VDUPD
long8 = __vdupd_dv(long);
double8 = __vdupd_dv(double);
cfloat8 = __vdupd_dv(cfloat);
ulong8 = __vdupd_dv(ulong);
cint8 = __vdupd_dv(cint);

*/

#define __vdupd_dv(a) __overload("__vdupd_dv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vduph_kv
*----------------------------------------------------------------------------*/
/*

VDUPH
short32 = __vduph_kv((short)(k));
ushort32 = __vduph_kv((ushort)(k));

*/

#define __vduph_kv(a) __overload("__vduph_kv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vduph_rv
*----------------------------------------------------------------------------*/
/*

VDUPH
short32 = __vduph_rv(short);
ushort32 = __vduph_rv(ushort);
cchar32 = __vduph_rv(cchar);

*/

#define __vduph_rv(a) __overload("__vduph_rv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vdupw_kv
*----------------------------------------------------------------------------*/
/*

VDUPW
int16 = __vdupw_kv((int)(k));
float16 = __vdupw_kv((float)(k));
uint16 = __vdupw_kv((uint)(k));

*/

#define __vdupw_kv(a) __overload("__vdupw_kv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vdupw_rv
*----------------------------------------------------------------------------*/
/*

VDUPW
int16 = __vdupw_rv(int);
float16 = __vdupw_rv(float);
uint16 = __vdupw_rv(uint);
cshort16 = __vdupw_rv(cshort);

*/

#define __vdupw_rv(a) __overload("__vdupw_rv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vfir4hw_vww
*----------------------------------------------------------------------------*/
/*

VFIR4HW
__vfir4hw_vww(short32, __SE_REG_PAIR, int16&, int16&);

*/


/*-----------------------------------------------------------------------------
* ID: __vfir4suhw_vww
*----------------------------------------------------------------------------*/
/*

VFIR4SUHW
__vfir4suhw_vww(short32, __SE_REG_PAIR, int16&, int16&);

*/


/*-----------------------------------------------------------------------------
* ID: __vfir4uhw_vww
*----------------------------------------------------------------------------*/
/*

VFIR4UHW
__vfir4uhw_vww(ushort32, __SE_REG_PAIR, uint16&, uint16&);

*/


/*-----------------------------------------------------------------------------
* ID: __vfir8hd_wvw
*----------------------------------------------------------------------------*/
/*

VFIR8HD
__vfir8hd_wvw(short32, short32, __SE_REG, long8&, long8&);

*/


/*-----------------------------------------------------------------------------
* ID: __vfir8hw_wvv
*----------------------------------------------------------------------------*/
/*

VFIR8HW
int16 = __vfir8hw_wvv(short32, short32, __SE_REG);

*/


/*-----------------------------------------------------------------------------
* ID: __vfir8suhd_wvw
*----------------------------------------------------------------------------*/
/*

VFIR8SUHD
__vfir8suhd_wvw(short32, short32, __SE_REG, long8&, long8&);

*/


/*-----------------------------------------------------------------------------
* ID: __vfir8suhw_wvv
*----------------------------------------------------------------------------*/
/*

VFIR8SUHW
int16 = __vfir8suhw_wvv(short32, short32, __SE_REG);

*/


/*-----------------------------------------------------------------------------
* ID: __vfir8uhd_wvw
*----------------------------------------------------------------------------*/
/*

VFIR8UHD
__vfir8uhd_wvw(ushort32, ushort32, __SE_REG, ulong8&, ulong8&);

*/


/*-----------------------------------------------------------------------------
* ID: __vfir8uhw_wvv
*----------------------------------------------------------------------------*/
/*

VFIR8UHW
uint16 = __vfir8uhw_wvv(ushort32, ushort32, __SE_REG);

*/


/*-----------------------------------------------------------------------------
* ID: __vgatherb_pvv
*----------------------------------------------------------------------------*/
/*

VGATHERB
char64 = __vgatherb_pvv(__vpred, char64);

*/


/*-----------------------------------------------------------------------------
* ID: __vgathernb_pvv
*----------------------------------------------------------------------------*/
/*

VGATHERNB
char64 = __vgathernb_pvv(__vpred, char64);

*/


/*-----------------------------------------------------------------------------
* ID: __vgetb_vkd
*----------------------------------------------------------------------------*/
/*

VGETB
char = __vgetb_vkd(char64, (uint)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vgetb_vrd
*----------------------------------------------------------------------------*/
/*

VGETB
char = __vgetb_vrd(char64, uint);

*/


/*-----------------------------------------------------------------------------
* ID: __vgetd_vkd
*----------------------------------------------------------------------------*/
/*

VGETD
long = __vgetd_vkd(long8, (uint)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __vgetd_vrd
*----------------------------------------------------------------------------*/
/*

VGETD
long = __vgetd_vrd(long8, uint);

*/


/*-----------------------------------------------------------------------------
* ID: __vgetdupb_vrv
*----------------------------------------------------------------------------*/
/*

VGETDUPB
uchar64 = __vgetdupb_vrv(uchar64, uint);
char64 = __vgetdupb_vrv(char64, int);

*/

#define __vgetdupb_vrv(a,b) __overload("__vgetdupb_vrv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vgetdupd_vrv
*----------------------------------------------------------------------------*/
/*

VGETDUPD
ulong8 = __vgetdupd_vrv(ulong8, uint);
long8 = __vgetdupd_vrv(long8, int);

*/

#define __vgetdupd_vrv(a,b) __overload("__vgetdupd_vrv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vgetduph_vrv
*----------------------------------------------------------------------------*/
/*

VGETDUPH
ushort32 = __vgetduph_vrv(ushort32, uint);
short32 = __vgetduph_vrv(short32, int);

*/

#define __vgetduph_vrv(a,b) __overload("__vgetduph_vrv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vgetdupw_vrv
*----------------------------------------------------------------------------*/
/*

VGETDUPW
uint16 = __vgetdupw_vrv(uint16, uint);
int16 = __vgetdupw_vrv(int16, int);

*/

#define __vgetdupw_vrv(a,b) __overload("__vgetdupw_vrv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vgeth_vkd
*----------------------------------------------------------------------------*/
/*

VGETH
short = __vgeth_vkd(short32, (uint)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __vgeth_vrd
*----------------------------------------------------------------------------*/
/*

VGETH
short = __vgeth_vrd(short32, uint);

*/


/*-----------------------------------------------------------------------------
* ID: __vgetub_vkd
*----------------------------------------------------------------------------*/
/*

VGETUB
uchar = __vgetub_vkd(uchar64, (uint)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __vgetub_vrd
*----------------------------------------------------------------------------*/
/*

VGETUB
uchar = __vgetub_vrd(uchar64, uint);

*/


/*-----------------------------------------------------------------------------
* ID: __vgetuh_vkd
*----------------------------------------------------------------------------*/
/*

VGETUH
ushort = __vgetuh_vkd(ushort32, (uint)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __vgetuh_vrd
*----------------------------------------------------------------------------*/
/*

VGETUH
ushort = __vgetuh_vrd(ushort32, uint);

*/


/*-----------------------------------------------------------------------------
* ID: __vgetuw_vkd
*----------------------------------------------------------------------------*/
/*

VGETUW
uint = __vgetuw_vkd(uint16, (uint)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __vgetuw_vrd
*----------------------------------------------------------------------------*/
/*

VGETUW
uint = __vgetuw_vrd(uint16, uint);

*/


/*-----------------------------------------------------------------------------
* ID: __vgetw_vkd
*----------------------------------------------------------------------------*/
/*

VGETW
int = __vgetw_vkd(int16, (uint)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vgetw_vrd
*----------------------------------------------------------------------------*/
/*

VGETW
int = __vgetw_vrd(int16, uint);

*/


/*-----------------------------------------------------------------------------
* ID: __vgmpyb_vvv
*----------------------------------------------------------------------------*/
/*

VGMPYB
uchar64 = __vgmpyb_vvv(uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vgmpyw_vvv
*----------------------------------------------------------------------------*/
/*

VGMPYW
uint16 = __vgmpyw_vvv(uint16, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vgsatd_vkv
*----------------------------------------------------------------------------*/
/*

VGSATD
long8 = __vgsatd_vkv(long8, (uchar8)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vgsath_vkv
*----------------------------------------------------------------------------*/
/*

VGSATH
short32 = __vgsath_vkv(short32, (uchar32)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vgsatsud_vkv
*----------------------------------------------------------------------------*/
/*

VGSATSUD
ulong8 = __vgsatsud_vkv(long8, (uchar8)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vgsatsuh_vkv
*----------------------------------------------------------------------------*/
/*

VGSATSUH
ushort32 = __vgsatsuh_vkv(short32, (uchar32)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vgsatsuw_vkv
*----------------------------------------------------------------------------*/
/*

VGSATSUW
uint16 = __vgsatsuw_vkv(int16, (uchar16)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vgsatud_vkv
*----------------------------------------------------------------------------*/
/*

VGSATUD
ulong8 = __vgsatud_vkv(ulong8, (uchar8)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vgsatuh_vkv
*----------------------------------------------------------------------------*/
/*

VGSATUH
ushort32 = __vgsatuh_vkv(ushort32, (uchar32)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vgsatuw_vkv
*----------------------------------------------------------------------------*/
/*

VGSATUW
uint16 = __vgsatuw_vkv(uint16, (uchar16)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vgsatw_vkv
*----------------------------------------------------------------------------*/
/*

VGSATW
int16 = __vgsatw_vkv(int16, (uchar16)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vhaddw1d_vd
*----------------------------------------------------------------------------*/
/*

VHADDW1D
long = __vhaddw1d_vd(int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vhaddh1d_vd
*----------------------------------------------------------------------------*/
/*

VHADDH1D
long = __vhaddh1d_vd(short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vhaddb1d_vd
*----------------------------------------------------------------------------*/
/*

VHADDB1D
long = __vhaddb1d_vd(char64);

*/


/*-----------------------------------------------------------------------------
* ID: __vhaddd1d_vd
*----------------------------------------------------------------------------*/
/*

VHADDD1D
long = __vhaddd1d_vd(long8);

*/


/*-----------------------------------------------------------------------------
* ID: __vhaddeoh2w_vd
*----------------------------------------------------------------------------*/
/*

VHADDEOH2W
int2 = __vhaddeoh2w_vd(short32);
cint = __vhaddeoh2w_vd(cshort16);

*/

#define __vhaddeoh2w_vd(a) __overload("__vhaddeoh2w_vd",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vhaddeow2d_vv
*----------------------------------------------------------------------------*/
/*

VHADDEOW2D
long2 = __vhaddeow2d_vv(int16);
clong = __vhaddeow2d_vv(cint8);

*/

#define __vhaddeow2d_vv(a) __overload("__vhaddeow2d_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vhaddeow4d_vvv
*----------------------------------------------------------------------------*/
/*

VHADDEOW4D
long4 = __vhaddeow4d_vvv(int16, int16);
clong2 = __vhaddeow4d_vvv(cint8, cint8);

*/

#define __vhaddeow4d_vvv(a,b) __overload("__vhaddeow4d_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vhadduw1d_vd
*----------------------------------------------------------------------------*/
/*

VHADDUW1D
ulong = __vhadduw1d_vd(uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vhadduh1d_vd
*----------------------------------------------------------------------------*/
/*

VHADDUH1D
ulong = __vhadduh1d_vd(ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vhaddub1d_vd
*----------------------------------------------------------------------------*/
/*

VHADDUB1D
ulong = __vhaddub1d_vd(uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vhaddud1d_vd
*----------------------------------------------------------------------------*/
/*

VHADDUD1D
ulong = __vhaddud1d_vd(ulong8);

*/


/*-----------------------------------------------------------------------------
* ID: __vhaddueoh2w_vd
*----------------------------------------------------------------------------*/
/*

VHADDUEOH2W
uint2 = __vhaddueoh2w_vd(ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vhaddueow2d_vv
*----------------------------------------------------------------------------*/
/*

VHADDUEOW2D
ulong2 = __vhaddueow2d_vv(uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vhaddueow4d_vvv
*----------------------------------------------------------------------------*/
/*

VHADDUEOW4D
ulong4 = __vhaddueow4d_vvv(uint16, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vhhmv_vvv
*----------------------------------------------------------------------------*/
/*

VHHMV
uchar64 = __vhhmv_vvv(uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vhlmv_vvv
*----------------------------------------------------------------------------*/
/*

VHLMV
uchar64 = __vhlmv_vvv(uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vhpackh_vvv
*----------------------------------------------------------------------------*/
/*

VHPACKH
short32 = __vhpackh_vvv(short32, short32);
ushort32 = __vhpackh_vvv(ushort32, ushort32);
cchar32 = __vhpackh_vvv(cchar32, cchar32);

*/

#define __vhpackh_vvv(a,b) __overload("__vhpackh_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vhpackl_vvv
*----------------------------------------------------------------------------*/
/*

VHPACKL
short32 = __vhpackl_vvv(short32, short32);
ushort32 = __vhpackl_vvv(ushort32, ushort32);
cchar32 = __vhpackl_vvv(cchar32, cchar32);

*/

#define __vhpackl_vvv(a,b) __overload("__vhpackl_vvv",(a),(b))((a),(b))

/*-----------------------------------------------------------------------------
* ID: __vhpint_vv
*----------------------------------------------------------------------------*/
/*

VHPINT
int16 = __vhpint_vv(uint16);

*/

/*-----------------------------------------------------------------------------
* ID: __vhpsp_vv
*----------------------------------------------------------------------------*/
/*

VHPSP
float16 = __vhpsp_vv(uint16);

*/

/*-----------------------------------------------------------------------------
* ID: __vhunpkd_vv
*----------------------------------------------------------------------------*/
/*

VHUNPKD
long8 = __vhunpkd_vv(short8);

*/


/*-----------------------------------------------------------------------------
* ID: __vhunpkdu_vv
*----------------------------------------------------------------------------*/
/*

VHUNPKDU
ulong8 = __vhunpkdu_vv(ushort8);

*/


/*-----------------------------------------------------------------------------
* ID: __vhunpkuwh_vv
*----------------------------------------------------------------------------*/
/*

VHUNPKUWH
uint16 = __vhunpkuwh_vv(ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vhunpkuwl_vv
*----------------------------------------------------------------------------*/
/*

VHUNPKUWL
uint16 = __vhunpkuwl_vv(ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vhunpkw_vv
*----------------------------------------------------------------------------*/
/*

VHUNPKW
int16 = __vhunpkw_vv(short16);

*/


/*-----------------------------------------------------------------------------
* ID: __vhunpkwh_vv
*----------------------------------------------------------------------------*/
/*

VHUNPKWH
int16 = __vhunpkwh_vv(short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vhunpkwl_vv
*----------------------------------------------------------------------------*/
/*

VHUNPKWL
int16 = __vhunpkwl_vv(short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vhunpkwu_vv
*----------------------------------------------------------------------------*/
/*

VHUNPKWU
uint16 = __vhunpkwu_vv(ushort16);

*/


/*-----------------------------------------------------------------------------
* ID: __vhxorw1w_vr
*----------------------------------------------------------------------------*/
/*

VHXORW1W
int = __vhxorw1w_vr(int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vhxorh1h_vr
*----------------------------------------------------------------------------*/
/*

VHXORH1H
short = __vhxorh1h_vr(short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vhxorb1b_vr
*----------------------------------------------------------------------------*/
/*

VHXORB1B
short = __vhxorb1b_vr(char64);

*/


/*-----------------------------------------------------------------------------
* ID: __vhxord1d_vd
*----------------------------------------------------------------------------*/
/*

VHXORD1D
long = __vhxord1d_vd(long8);

*/


/*-----------------------------------------------------------------------------
* ID: __vintdph_vv
*----------------------------------------------------------------------------*/
/*

VINTDPH
double8 = __vintdph_vv(int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vintdpl_vv
*----------------------------------------------------------------------------*/
/*

VINTDPL
double8 = __vintdpl_vv(int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vintdpuh_vv
*----------------------------------------------------------------------------*/
/*

VINTDPUH
double8 = __vintdpuh_vv(uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vintdpul_vv
*----------------------------------------------------------------------------*/
/*

VINTDPUL
double8 = __vintdpul_vv(uint16);

*/

/*-----------------------------------------------------------------------------
* ID: __vinthp_vv
*----------------------------------------------------------------------------*/
/*

VINTHP
uint16 = __vinthp_vv(int16);

*/

/*-----------------------------------------------------------------------------
* ID: __vinthsph_vv
*----------------------------------------------------------------------------*/
/*

VINTHSPH
float16 = __vinthsph_vv(short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vinthspl_vv
*----------------------------------------------------------------------------*/
/*

VINTHSPL
float16 = __vinthspl_vv(short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vinthspuh_vv
*----------------------------------------------------------------------------*/
/*

VINTHSPUH
float16 = __vinthspuh_vv(ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vinthspul_vv
*----------------------------------------------------------------------------*/
/*

VINTHSPUL
float16 = __vinthspul_vv(ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vintsp_vv
*----------------------------------------------------------------------------*/
/*

VINTSP
float16 = __vintsp_vv(int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vintspu_vv
*----------------------------------------------------------------------------*/
/*

VINTSPU
float16 = __vintspu_vv(uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vlhmv_vvv
*----------------------------------------------------------------------------*/
/*

VLHMV
uchar64 = __vlhmv_vvv(uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vllmv_vvv
*----------------------------------------------------------------------------*/
/*

VLLMV
uchar64 = __vllmv_vvv(uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vlmbd0b_vv
*----------------------------------------------------------------------------*/
/*

VLMBD0B
uchar64 = __vlmbd0b_vv(uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vlmbd0d_vv
*----------------------------------------------------------------------------*/
/*

VLMBD0D
ulong8 = __vlmbd0d_vv(ulong8);

*/


/*-----------------------------------------------------------------------------
* ID: __vlmbd0h_vv
*----------------------------------------------------------------------------*/
/*

VLMBD0H
ushort32 = __vlmbd0h_vv(ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vlmbd0w_vv
*----------------------------------------------------------------------------*/
/*

VLMBD0W
uint16 = __vlmbd0w_vv(uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vlmbd1b_vv
*----------------------------------------------------------------------------*/
/*

VLMBD1B
uchar64 = __vlmbd1b_vv(uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vlmbd1d_vv
*----------------------------------------------------------------------------*/
/*

VLMBD1D
ulong8 = __vlmbd1d_vv(ulong8);

*/


/*-----------------------------------------------------------------------------
* ID: __vlmbd1h_vv
*----------------------------------------------------------------------------*/
/*

VLMBD1H
ushort32 = __vlmbd1h_vv(ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vlmbd1w_vv
*----------------------------------------------------------------------------*/
/*

VLMBD1W
uint16 = __vlmbd1w_vv(uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vlmbdb_vvv
*----------------------------------------------------------------------------*/
/*

VLMBDB
uchar64 = __vlmbdb_vvv(uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vlmbdd_vvv
*----------------------------------------------------------------------------*/
/*

VLMBDD
ulong8 = __vlmbdd_vvv(ulong8, ulong8);

*/


/*-----------------------------------------------------------------------------
* ID: __vlmbdh_vvv
*----------------------------------------------------------------------------*/
/*

VLMBDH
ushort32 = __vlmbdh_vvv(ushort32, ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vlmbdw_vvv
*----------------------------------------------------------------------------*/
/*

VLMBDW
uint16 = __vlmbdw_vvv(uint16, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vmatmpyhd_vvw
*----------------------------------------------------------------------------*/
/*

VMATMPYHD
__vmatmpyhd_vvw(__SE_REG, __SE_REG, long8&, long8&);

*/


/*-----------------------------------------------------------------------------
* ID: __vmatmpyhw_vvv
*----------------------------------------------------------------------------*/
/*

VMATMPYHW
int16 = __vmatmpyhw_vvv(__SE_REG, __SE_REG);

*/


/*-----------------------------------------------------------------------------
* ID: __vmatmpysp{_se}_vww
*----------------------------------------------------------------------------*/
/*

VMATMPYSP
__vmatmpysp_vww(float16, float16, float16, float16&, float16&);

__vmatmpysp_se_vww(float16, __SE_REG_PAIR, float16&, float16&);

*/


/*-----------------------------------------------------------------------------
* ID: __vmatmpysuhd_vvw
*----------------------------------------------------------------------------*/
/*

VMATMPYSUHD
__vmatmpysuhd_vvw(__SE_REG, __SE_REG, long8&, long8&);

*/


/*-----------------------------------------------------------------------------
* ID: __vmatmpysuhw_vvv
*----------------------------------------------------------------------------*/
/*

VMATMPYSUHW
int16 = __vmatmpysuhw_vvv(__SE_REG, __SE_REG);

*/


/*-----------------------------------------------------------------------------
* ID: __vmatmpyuhd_vvw
*----------------------------------------------------------------------------*/
/*

VMATMPYUHD
__vmatmpyuhd_vvw(__SE_REG, __SE_REG, ulong8&, ulong8&);

*/


/*-----------------------------------------------------------------------------
* ID: __vmatmpyuhw_vvv
*----------------------------------------------------------------------------*/
/*

VMATMPYUHW
uint16 = __vmatmpyuhw_vvv(__SE_REG, __SE_REG);

*/


/*-----------------------------------------------------------------------------
* ID: __vmatmpyushd_vvw
*----------------------------------------------------------------------------*/
/*

VMATMPYUSHD
__vmatmpyushd_vvw(__SE_REG, __SE_REG, long8&, long8&);

*/


/*-----------------------------------------------------------------------------
* ID: __vmatmpyushw_vvv
*----------------------------------------------------------------------------*/
/*

VMATMPYUSHW
int16 = __vmatmpyushw_vvv(__SE_REG, __SE_REG);

*/


/*-----------------------------------------------------------------------------
* ID: __vmaxb_vvv
*----------------------------------------------------------------------------*/
/*

VMAXB
char64 = __vmaxb_vvv(char64, char64);

*/


/*-----------------------------------------------------------------------------
* ID: __vmaxd_vvv
*----------------------------------------------------------------------------*/
/*

VMAXD
long8 = __vmaxd_vvv(long8, long8);

*/


/*-----------------------------------------------------------------------------
* ID: __vmaxdp_vvv
*----------------------------------------------------------------------------*/
/*

VMAXDP
double8 = __vmaxdp_vvv(double8, double8);

*/


/*-----------------------------------------------------------------------------
* ID: __vmaxh_vvv
*----------------------------------------------------------------------------*/
/*

VMAXH
short32 = __vmaxh_vvv(short32, short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vmaxpb_vvp
*----------------------------------------------------------------------------*/
/*

VMAXPB
__vmaxpb_vvp(char64, char64&, __vpred&);

*/


/*-----------------------------------------------------------------------------
* ID: __vmaxpd_vvp
*----------------------------------------------------------------------------*/
/*

VMAXPD
__vmaxpd_vvp(long8, long8&, __vpred&);

*/


/*-----------------------------------------------------------------------------
* ID: __vmaxph_vvp
*----------------------------------------------------------------------------*/
/*

VMAXPH
__vmaxph_vvp(short32, short32&, __vpred&);

*/


/*-----------------------------------------------------------------------------
* ID: __vmaxpw_vvp
*----------------------------------------------------------------------------*/
/*

VMAXPW
__vmaxpw_vvp(int16, int16&, __vpred&);

*/


/*-----------------------------------------------------------------------------
* ID: __vmaxsp_vvv
*----------------------------------------------------------------------------*/
/*

VMAXSP
float16 = __vmaxsp_vvv(float16, float16);

*/


/*-----------------------------------------------------------------------------
* ID: __vmaxub_vvv
*----------------------------------------------------------------------------*/
/*

VMAXUB
uchar64 = __vmaxub_vvv(uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vmaxud_vvv
*----------------------------------------------------------------------------*/
/*

VMAXUD
ulong8 = __vmaxud_vvv(ulong8, ulong8);

*/


/*-----------------------------------------------------------------------------
* ID: __vmaxuh_vvv
*----------------------------------------------------------------------------*/
/*

VMAXUH
ushort32 = __vmaxuh_vvv(ushort32, ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vmaxupb_vvp
*----------------------------------------------------------------------------*/
/*

VMAXUPB
__vmaxupb_vvp(uchar64, uchar64&, __vpred&);

*/


/*-----------------------------------------------------------------------------
* ID: __vmaxupd_vvp
*----------------------------------------------------------------------------*/
/*

VMAXUPD
__vmaxupd_vvp(ulong8, ulong8&, __vpred&);

*/


/*-----------------------------------------------------------------------------
* ID: __vmaxuph_vvp
*----------------------------------------------------------------------------*/
/*

VMAXUPH
__vmaxuph_vvp(ushort32, ushort32&, __vpred&);

*/


/*-----------------------------------------------------------------------------
* ID: __vmaxupw_vvp
*----------------------------------------------------------------------------*/
/*

VMAXUPW
__vmaxupw_vvp(uint16, uint16&, __vpred&);

*/


/*-----------------------------------------------------------------------------
* ID: __vmaxuw_vvv
*----------------------------------------------------------------------------*/
/*

VMAXUW
uint16 = __vmaxuw_vvv(uint16, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vmaxw_vvv
*----------------------------------------------------------------------------*/
/*

VMAXW
int16 = __vmaxw_vvv(int16, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vminb_vvv
*----------------------------------------------------------------------------*/
/*

VMINB
char64 = __vminb_vvv(char64, char64);

*/


/*-----------------------------------------------------------------------------
* ID: __vmind_vvv
*----------------------------------------------------------------------------*/
/*

VMIND
long8 = __vmind_vvv(long8, long8);

*/


/*-----------------------------------------------------------------------------
* ID: __vmindp_vvv
*----------------------------------------------------------------------------*/
/*

VMINDP
double8 = __vmindp_vvv(double8, double8);

*/


/*-----------------------------------------------------------------------------
* ID: __vminh_vvv
*----------------------------------------------------------------------------*/
/*

VMINH
short32 = __vminh_vvv(short32, short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vminpb_vvp
*----------------------------------------------------------------------------*/
/*

VMINPB
__vminpb_vvp(char64, char64&, __vpred&);

*/


/*-----------------------------------------------------------------------------
* ID: __vminpd_vvp
*----------------------------------------------------------------------------*/
/*

VMINPD
__vminpd_vvp(long8, long8&, __vpred&);

*/


/*-----------------------------------------------------------------------------
* ID: __vminph_vvp
*----------------------------------------------------------------------------*/
/*

VMINPH
__vminph_vvp(short32, short32&, __vpred&);

*/


/*-----------------------------------------------------------------------------
* ID: __vminpw_vvp
*----------------------------------------------------------------------------*/
/*

VMINPW
__vminpw_vvp(int16, int16&, __vpred&);

*/


/*-----------------------------------------------------------------------------
* ID: __vminsp_vvv
*----------------------------------------------------------------------------*/
/*

VMINSP
float16 = __vminsp_vvv(float16, float16);

*/


/*-----------------------------------------------------------------------------
* ID: __vminub_vvv
*----------------------------------------------------------------------------*/
/*

VMINUB
uchar64 = __vminub_vvv(uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vminud_vvv
*----------------------------------------------------------------------------*/
/*

VMINUD
ulong8 = __vminud_vvv(ulong8, ulong8);

*/


/*-----------------------------------------------------------------------------
* ID: __vminuh_vvv
*----------------------------------------------------------------------------*/
/*

VMINUH
ushort32 = __vminuh_vvv(ushort32, ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vminupb_vvp
*----------------------------------------------------------------------------*/
/*

VMINUPB
__vminupb_vvp(uchar64, uchar64&, __vpred&);

*/


/*-----------------------------------------------------------------------------
* ID: __vminupd_vvp
*----------------------------------------------------------------------------*/
/*

VMINUPD
__vminupd_vvp(ulong8, ulong8&, __vpred&);

*/


/*-----------------------------------------------------------------------------
* ID: __vminuph_vvp
*----------------------------------------------------------------------------*/
/*

VMINUPH
__vminuph_vvp(ushort32, ushort32&, __vpred&);

*/


/*-----------------------------------------------------------------------------
* ID: __vminupw_vvp
*----------------------------------------------------------------------------*/
/*

VMINUPW
__vminupw_vvp(uint16, uint16&, __vpred&);

*/


/*-----------------------------------------------------------------------------
* ID: __vminuw_vvv
*----------------------------------------------------------------------------*/
/*

VMINUW
uint16 = __vminuw_vvv(uint16, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vminw_vvv
*----------------------------------------------------------------------------*/
/*

VMINW
int16 = __vminw_vvv(int16, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vmpybb_vvv
*----------------------------------------------------------------------------*/
/*

VMPYBB
char64 = __vmpybb_vvv(char64, char64);
uchar64 = __vmpybb_vvv(uchar64, uchar64);

*/

#define __vmpybb_vvv(a,b) __overload("__vmpybb_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vmpydd_vvv
*----------------------------------------------------------------------------*/
/*

VMPYDD
long8 = __vmpydd_vvv(long8, long8);
ulong8 = __vmpydd_vvv(ulong8, ulong8);

*/

#define __vmpydd_vvv(a,b) __overload("__vmpydd_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vmpydp_vvv
*----------------------------------------------------------------------------*/
/*

VMPYDP
double8 = __vmpydp_vvv(double8, double8);

*/


/*-----------------------------------------------------------------------------
* ID: __vmpyhh_vvv
*----------------------------------------------------------------------------*/
/*

VMPYHH
short32 = __vmpyhh_vvv(short32, short32);
ushort32 = __vmpyhh_vvv(ushort32, ushort32);

*/

#define __vmpyhh_vvv(a,b) __overload("__vmpyhh_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vmpyhw_vvw
*----------------------------------------------------------------------------*/
/*

VMPYHW
__vmpyhw_vvw(short32, short32, int16&, int16&);

*/


/*-----------------------------------------------------------------------------
* ID: __vmpysp2dp_vvw
*----------------------------------------------------------------------------*/
/*

VMPYSP2DP
__vmpysp2dp_vvw(float16, float16, double8&, double8&);

*/


/*-----------------------------------------------------------------------------
* ID: __vmpysp_vvv
*----------------------------------------------------------------------------*/
/*

VMPYSP
float16 = __vmpysp_vvv(float16, float16);

*/


/*-----------------------------------------------------------------------------
* ID: __vmpysubh_vvw
*----------------------------------------------------------------------------*/
/*

VMPYSUBH
__vmpysubh_vvw(char64, uchar64, short32&, short32&);

*/


/*-----------------------------------------------------------------------------
* ID: __vmpysuhw_vvw
*----------------------------------------------------------------------------*/
/*

VMPYSUHW
__vmpysuhw_vvw(short32, ushort32, int16&, int16&);

*/


/*-----------------------------------------------------------------------------
* ID: __vmpysuwd_vvw
*----------------------------------------------------------------------------*/
/*

VMPYSUWD
__vmpysuwd_vvw(int16, uint16, long8&, long8&);

*/


/*-----------------------------------------------------------------------------
* ID: __vmpyubh_vvw
*----------------------------------------------------------------------------*/
/*

VMPYUBH
__vmpyubh_vvw(uchar64, uchar64, ushort32&, ushort32&);

*/


/*-----------------------------------------------------------------------------
* ID: __vmpyudq_vvw
*----------------------------------------------------------------------------*/
/*

VMPYUDQ
__vmpyudq_vvw(ulong8, ulong8, ulong8&, ulong8&);

*/


/*-----------------------------------------------------------------------------
* ID: __vmpyuhw_vvw
*----------------------------------------------------------------------------*/
/*

VMPYUHW
__vmpyuhw_vvw(ushort32, ushort32, uint16&, uint16&);

*/


/*-----------------------------------------------------------------------------
* ID: __vmpyuwd_vvw
*----------------------------------------------------------------------------*/
/*

VMPYUWD
__vmpyuwd_vvw(uint16, uint16, ulong8&, ulong8&);

*/


/*-----------------------------------------------------------------------------
* ID: __vmpywd_vvw
*----------------------------------------------------------------------------*/
/*

VMPYWD
__vmpywd_vvw(int16, int16, long8&, long8&);

*/


/*-----------------------------------------------------------------------------
* ID: __vmpyww_vvv
*----------------------------------------------------------------------------*/
/*

VMPYWW
int16 = __vmpyww_vvv(int16, int16);
uint16 = __vmpyww_vvv(uint16, uint16);

*/

#define __vmpyww_vvv(a,b) __overload("__vmpyww_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vnandw_vvv
*----------------------------------------------------------------------------*/
/*

VNANDW
char64 = __vnandw_vvv(char64, char64);
short32 = __vnandw_vvv(short32, short32);
int16 = __vnandw_vvv(int16, int16);
long8 = __vnandw_vvv(long8, long8);
uchar64 = __vnandw_vvv(uchar64, uchar64);
ushort32 = __vnandw_vvv(ushort32, ushort32);
uint16 = __vnandw_vvv(uint16, uint16);
ulong8 = __vnandw_vvv(ulong8, ulong8);

*/

#define __vnandw_vvv(a,b) __overload("__vnandw_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vnorm2uh_vv
*----------------------------------------------------------------------------*/
/*

VNORM2UH
ushort32 = __vnorm2uh_vv(ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vnorm2uw_vv
*----------------------------------------------------------------------------*/
/*

VNORM2UW
uint16 = __vnorm2uw_vv(uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vnormb_vv
*----------------------------------------------------------------------------*/
/*

VNORMB
char64 = __vnormb_vv(char64);

*/


/*-----------------------------------------------------------------------------
* ID: __vnormd_vv
*----------------------------------------------------------------------------*/
/*

VNORMD
long8 = __vnormd_vv(long8);

*/


/*-----------------------------------------------------------------------------
* ID: __vnormh_vv
*----------------------------------------------------------------------------*/
/*

VNORMH
short32 = __vnormh_vv(short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vnormw_vv
*----------------------------------------------------------------------------*/
/*

VNORMW
int16 = __vnormw_vv(int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vnorw_vvv
*----------------------------------------------------------------------------*/
/*

VNORW
char64 = __vnorw_vvv(char64, char64);
short32 = __vnorw_vvv(short32, short32);
int16 = __vnorw_vvv(int16, int16);
long8 = __vnorw_vvv(long8, long8);

*/

#define __vnorw_vvv(a,b) __overload("__vnorw_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vopmatmpysp_vvw
*----------------------------------------------------------------------------*/
/*

VOPMATMPYSP
__vopmatmpysp_vvw(float16, float16, float16&, float16&);

*/


/*-----------------------------------------------------------------------------
* ID: __vornw_vkv
*----------------------------------------------------------------------------*/
/*

VORNW
int16 = __vornw_vkv(int16, (int16)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __vornw_vvv
*----------------------------------------------------------------------------*/
/*

VORNW
char64 = __vornw_vvv(char64, char64);
short32 = __vornw_vvv(short32, short32);
int16 = __vornw_vvv(int16, int16);
long8 = __vornw_vvv(long8, long8);

*/

#define __vornw_vvv(a,b) __overload("__vornw_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vorw_vkv
*----------------------------------------------------------------------------*/
/*

VORW
int16 = __vorw_vkv(int16, (int16)(k));
uint16 = __vorw_vkv(uint16, (uint16)(k));

*/

#define __vorw_vkv(a,b) __overload("__vorw_vkv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vorw_vvv
*----------------------------------------------------------------------------*/
/*

VORW
char64 = __vorw_vvv(char64, char64);
short32 = __vorw_vvv(short32, short32);
int16 = __vorw_vvv(int16, int16);
long8 = __vorw_vvv(long8, long8);
uchar64 = __vorw_vvv(uchar64, uchar64);
ushort32 = __vorw_vvv(ushort32, ushort32);
uint16 = __vorw_vvv(uint16, uint16);
ulong8 = __vorw_vvv(ulong8, ulong8);

*/

#define __vorw_vvv(a,b) __overload("__vorw_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vpackh2_vvv
*----------------------------------------------------------------------------*/
/*

VPACKH2
short32 = __vpackh2_vvv(short32, short32);
ushort32 = __vpackh2_vvv(ushort32, ushort32);
cchar32 = __vpackh2_vvv(cchar32, cchar32);

*/

#define __vpackh2_vvv(a,b) __overload("__vpackh2_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vpackh4_vvv
*----------------------------------------------------------------------------*/
/*

VPACKH4
char64 = __vpackh4_vvv(char64, char64);
uchar64 = __vpackh4_vvv(uchar64, uchar64);

*/

#define __vpackh4_vvv(a,b) __overload("__vpackh4_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vpackhl2_vvv
*----------------------------------------------------------------------------*/
/*

VPACKHL2
short32 = __vpackhl2_vvv(short32, short32);
ushort32 = __vpackhl2_vvv(ushort32, ushort32);
cchar32 = __vpackhl2_vvv(cchar32, cchar32);

*/

#define __vpackhl2_vvv(a,b) __overload("__vpackhl2_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vpackl2_vvv
*----------------------------------------------------------------------------*/
/*

VPACKL2
short32 = __vpackl2_vvv(short32, short32);
ushort32 = __vpackl2_vvv(ushort32, ushort32);
cchar32 = __vpackl2_vvv(cchar32, cchar32);

*/

#define __vpackl2_vvv(a,b) __overload("__vpackl2_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vpackl4_vvv
*----------------------------------------------------------------------------*/
/*

VPACKL4
char64 = __vpackl4_vvv(char64, char64);
uchar64 = __vpackl4_vvv(uchar64, uchar64);

*/

#define __vpackl4_vvv(a,b) __overload("__vpackl4_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vpacklh2_vvv
*----------------------------------------------------------------------------*/
/*

VPACKLH2
short32 = __vpacklh2_vvv(short32, short32);
ushort32 = __vpacklh2_vvv(ushort32, ushort32);
cchar32 = __vpacklh2_vvv(cchar32, cchar32);

*/

#define __vpacklh2_vvv(a,b) __overload("__vpacklh2_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vpacklh4_vvv
*----------------------------------------------------------------------------*/
/*

VPACKLH4
char64 = __vpacklh4_vvv(char64, char64);
uchar64 = __vpacklh4_vvv(uchar64, uchar64);

*/

#define __vpacklh4_vvv(a,b) __overload("__vpacklh4_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vpackp2_vvv
*----------------------------------------------------------------------------*/
/*

VPACKP2
short32 = __vpackp2_vvv(short32, short32);
ushort32 = __vpackp2_vvv(ushort32, ushort32);
cchar32 = __vpackp2_vvv(cchar32, cchar32);

*/

#define __vpackp2_vvv(a,b) __overload("__vpackp2_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vpackw_vvv
*----------------------------------------------------------------------------*/
/*

VPACKW
int16 = __vpackw_vvv(int16, int16);
float16 = __vpackw_vvv(float16, float16);
uint16 = __vpackw_vvv(uint16, uint16);
cshort16 = __vpackw_vvv(cshort16, cshort16);

*/

#define __vpackw_vvv(a,b) __overload("__vpackw_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vpackx2_vvv
*----------------------------------------------------------------------------*/
/*

VPACKX2
short32 = __vpackx2_vvv(short32, short32);
ushort32 = __vpackx2_vvv(ushort32, ushort32);
cchar32 = __vpackx2_vvv(cchar32, cchar32);

*/

#define __vpackx2_vvv(a,b) __overload("__vpackx2_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vperm_vvv
*----------------------------------------------------------------------------*/
/*

VPERM
uchar64 = __vperm_vvv(uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vperm_yvv
*----------------------------------------------------------------------------*/
/*

VPERM
uchar64 = __vperm_yvv(uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vpermeeb_yvvv
*----------------------------------------------------------------------------*/
/*

VPERMEEB
uchar64 = __vpermeeb_yvvv(uchar64, uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vpermeed_yvvv
*----------------------------------------------------------------------------*/
/*

VPERMEED
uchar64 = __vpermeed_yvvv(uchar64, uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vpermeeh_yvvv
*----------------------------------------------------------------------------*/
/*

VPERMEEH
uchar64 = __vpermeeh_yvvv(uchar64, uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vpermeeq_yvvv
*----------------------------------------------------------------------------*/
/*

VPERMEEQ
uchar64 = __vpermeeq_yvvv(uchar64, uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vpermeew_yvvv
*----------------------------------------------------------------------------*/
/*

VPERMEEW
uchar64 = __vpermeew_yvvv(uchar64, uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vpermeob_yvvv
*----------------------------------------------------------------------------*/
/*

VPERMEOB
uchar64 = __vpermeob_yvvv(uchar64, uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vpermeod_yvvv
*----------------------------------------------------------------------------*/
/*

VPERMEOD
uchar64 = __vpermeod_yvvv(uchar64, uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vpermeoh_yvvv
*----------------------------------------------------------------------------*/
/*

VPERMEOH
uchar64 = __vpermeoh_yvvv(uchar64, uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vpermeoq_yvvv
*----------------------------------------------------------------------------*/
/*

VPERMEOQ
uchar64 = __vpermeoq_yvvv(uchar64, uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vpermeow_yvvv
*----------------------------------------------------------------------------*/
/*

VPERMEOW
uchar64 = __vpermeow_yvvv(uchar64, uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vpermhh_yvvv
*----------------------------------------------------------------------------*/
/*

VPERMHH
uchar64 = __vpermhh_yvvv(uchar64, uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vpermlh_yvvv
*----------------------------------------------------------------------------*/
/*

VPERMLH
uchar64 = __vpermlh_yvvv(uchar64, uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vpermll_yvvv
*----------------------------------------------------------------------------*/
/*

VPERMLL
uchar64 = __vpermll_yvvv(uchar64, uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vpermoob_yvvv
*----------------------------------------------------------------------------*/
/*

VPERMOOB
uchar64 = __vpermoob_yvvv(uchar64, uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vpermood_yvvv
*----------------------------------------------------------------------------*/
/*

VPERMOOD
uchar64 = __vpermood_yvvv(uchar64, uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vpermooh_yvvv
*----------------------------------------------------------------------------*/
/*

VPERMOOH
uchar64 = __vpermooh_yvvv(uchar64, uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vpermooq_yvvv
*----------------------------------------------------------------------------*/
/*

VPERMOOQ
uchar64 = __vpermooq_yvvv(uchar64, uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vpermoow_yvvv
*----------------------------------------------------------------------------*/
/*

VPERMOOW
uchar64 = __vpermoow_yvvv(uchar64, uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vppackdup16w_pv
*----------------------------------------------------------------------------*/
/*

VPPACKDUP16W
uint16 = __vppackdup16w_pv(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __vppackdup8w_pv
*----------------------------------------------------------------------------*/
/*

VPPACKDUP8W
uint16 = __vppackdup8w_pv(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __vputb_rkv
*----------------------------------------------------------------------------*/
/*

VPUTB
uchar64 = __vputb_rkv(uchar, (uchar)(k={0-63}), uchar64);
char64 = __vputb_rkv(char, (char)(k={0-63}), char64);

*/

#define __vputb_rkv(a,b,c) __overload("__vputb_rkv",(a),(b),(c))((a),(b),(c))


/*-----------------------------------------------------------------------------
* ID: __vputd_dkv
*----------------------------------------------------------------------------*/
/*

VPUTD
ulong8 = __vputd_dkv(ulong, (uchar)(k={0-63}), ulong8);
long8 = __vputd_dkv(long, (char)(k={0-63}), long8);

*/

#define __vputd_dkv(a,b,c) __overload("__vputd_dkv",(a),(b),(c))((a),(b),(c))


/*-----------------------------------------------------------------------------
* ID: __vputh_rkv
*----------------------------------------------------------------------------*/
/*

VPUTH
ushort32 = __vputh_rkv(ushort, (uchar)(k={0-63}), ushort32);
short32 = __vputh_rkv(short, (char)(k={0-63}), short32);

*/

#define __vputh_rkv(a,b,c) __overload("__vputh_rkv",(a),(b),(c))((a),(b),(c))


/*-----------------------------------------------------------------------------
* ID: __vputw_rkv
*----------------------------------------------------------------------------*/
/*

VPUTW
uint16 = __vputw_rkv(uint, (uchar)(k={0-63}), uint16);
int16 = __vputw_rkv(int, (char)(k={0-63}), int16);

*/

#define __vputw_rkv(a,b,c) __overload("__vputw_rkv",(a),(b),(c))((a),(b),(c))


/*-----------------------------------------------------------------------------
* ID: __vpxpnd_pv
*----------------------------------------------------------------------------*/
/*

VPXPND
char64 = __vpxpnd_pv(__vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __vrcpdp_vv
*----------------------------------------------------------------------------*/
/*

VRCPDP
double8 = __vrcpdp_vv(double8);

*/


/*-----------------------------------------------------------------------------
* ID: __vrcpsp_vv
*----------------------------------------------------------------------------*/
/*

VRCPSP
float16 = __vrcpsp_vv(float16);

*/


/*-----------------------------------------------------------------------------
* ID: __vreplace_vkkv
*----------------------------------------------------------------------------*/
/*

VREPLACE
ulong8 = __vreplace_vkkv(ulong8, (uchar8)(k={0-63}), (uchar8)(k={0-63}), ulong8);
long8 = __vreplace_vkkv(long8, (char8)(k={0-63}), (char8)(k={0-63}), long8);

*/

#define __vreplace_vkkv(a,b,c,d) __overload("__vreplace_vkkv",(a),(b),(c),(d))((a),(b),(c),(d))


/*-----------------------------------------------------------------------------
* ID: __vreverseb_vv
*----------------------------------------------------------------------------*/
/*

VREVERSEB
char64 = __vreverseb_vv(char64);
uchar64 = __vreverseb_vv(uchar64);

*/

#define __vreverseb_vv(a) __overload("__vreverseb_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vreversed_vv
*----------------------------------------------------------------------------*/
/*

VREVERSED
long8 = __vreversed_vv(long8);
double8 = __vreversed_vv(double8);
cfloat8 = __vreversed_vv(cfloat8);
ulong8 = __vreversed_vv(ulong8);
cint8 = __vreversed_vv(cint8);

*/

#define __vreversed_vv(a) __overload("__vreversed_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vreverseh_vv
*----------------------------------------------------------------------------*/
/*

VREVERSEH
short32 = __vreverseh_vv(short32);
ushort32 = __vreverseh_vv(ushort32);
cchar32 = __vreverseh_vv(cchar32);

*/

#define __vreverseh_vv(a) __overload("__vreverseh_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vreversew_vv
*----------------------------------------------------------------------------*/
/*

VREVERSEW
int16 = __vreversew_vv(int16);
float16 = __vreversew_vv(float16);
uint16 = __vreversew_vv(uint16);
cshort16 = __vreversew_vv(cshort16);

*/

#define __vreversew_vv(a) __overload("__vreversew_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vrotlb_vkv
*----------------------------------------------------------------------------*/
/*

VROTLB
uchar64 = __vrotlb_vkv(uchar64, (uchar64)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vrotlb_vvv
*----------------------------------------------------------------------------*/
/*

VROTLB
uchar64 = __vrotlb_vvv(uchar64, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vrotld_vkv
*----------------------------------------------------------------------------*/
/*

VROTLD
ulong8 = __vrotld_vkv(ulong8, (uchar8)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vrotld_vvv
*----------------------------------------------------------------------------*/
/*

VROTLD
ulong8 = __vrotld_vvv(ulong8, ulong8);

*/


/*-----------------------------------------------------------------------------
* ID: __vrotlh_vkv
*----------------------------------------------------------------------------*/
/*

VROTLH
ushort32 = __vrotlh_vkv(ushort32, (ushort32)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vrotlh_vvv
*----------------------------------------------------------------------------*/
/*

VROTLH
ushort32 = __vrotlh_vvv(ushort32, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vrotlw_vkv
*----------------------------------------------------------------------------*/
/*

VROTLW
int16 = __vrotlw_vkv(int16, (uchar16)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vrotlw_vvv
*----------------------------------------------------------------------------*/
/*

VROTLW
int16 = __vrotlw_vvv(int16, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vrpackh_vvv
*----------------------------------------------------------------------------*/
/*

VRPACKH
short32 = __vrpackh_vvv(int16, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vrsqrdp_vv
*----------------------------------------------------------------------------*/
/*

VRSQRDP
double8 = __vrsqrdp_vv(double8);

*/


/*-----------------------------------------------------------------------------
* ID: __vrsqrsp_vv
*----------------------------------------------------------------------------*/
/*

VRSQRSP
float16 = __vrsqrsp_vv(float16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsad16ou16h16w_vvv
*----------------------------------------------------------------------------*/
/*

VSAD16OU16H16W
uint16 = __vsad16ou16h16w_vvv(ushort32, ushort16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsad16ou8h16w_vvv
*----------------------------------------------------------------------------*/
/*

VSAD16OU8H16W
uint16 = __vsad16ou8h16w_vvv(ushort32, ushort8);

*/


/*-----------------------------------------------------------------------------
* ID: __vsad8ou16b32h_vvv
*----------------------------------------------------------------------------*/
/*

VSAD8OU16B32H
ushort32 = __vsad8ou16b32h_vvv(uchar64, uchar16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsaddb_vkv
*----------------------------------------------------------------------------*/
/*

VSADDB
char64 = __vsaddb_vkv(char64, (char64)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __vsaddb_vvv
*----------------------------------------------------------------------------*/
/*

VSADDB
char64 = __vsaddb_vvv(char64, char64);

*/


/*-----------------------------------------------------------------------------
* ID: __vsaddh_vkv
*----------------------------------------------------------------------------*/
/*

VSADDH
short32 = __vsaddh_vkv(short32, (short32)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __vsaddh_vvv
*----------------------------------------------------------------------------*/
/*

VSADDH
short32 = __vsaddh_vvv(short32, short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vsaddub_vvv
*----------------------------------------------------------------------------*/
/*

VSADDUB
uchar64 = __vsaddub_vvv(uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vsadduh_vvv
*----------------------------------------------------------------------------*/
/*

VSADDUH
ushort32 = __vsadduh_vvv(ushort32, ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vsaddusb_vvv
*----------------------------------------------------------------------------*/
/*

VSADDUSB
uchar64 = __vsaddusb_vvv(uchar64, char64);

*/


/*-----------------------------------------------------------------------------
* ID: __vsaddush_vvv
*----------------------------------------------------------------------------*/
/*

VSADDUSH
ushort32 = __vsaddush_vvv(ushort32, short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vsaddusw_vvv
*----------------------------------------------------------------------------*/
/*

VSADDUSW
uint16 = __vsaddusw_vvv(uint16, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsadduw_vvv
*----------------------------------------------------------------------------*/
/*

VSADDUW
uint16 = __vsadduw_vvv(uint16, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsaddw_vkv
*----------------------------------------------------------------------------*/
/*

VSADDW
int16 = __vsaddw_vkv(int16, (int16)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __vsaddw_vvv
*----------------------------------------------------------------------------*/
/*

VSADDW
int16 = __vsaddw_vvv(int16, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsadm16ou16h16w_yvvv
*----------------------------------------------------------------------------*/
/*

VSADM16OU16H16W
uint16 = __vsadm16ou16h16w_yvvv(uchar64, ushort32, ushort16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsadm16ou8h16w_yvvv
*----------------------------------------------------------------------------*/
/*

VSADM16OU8H16W
uint16 = __vsadm16ou8h16w_yvvv(uchar64, ushort32, ushort8);

*/


/*-----------------------------------------------------------------------------
* ID: __vsadm8ou16b32h_yvvv
*----------------------------------------------------------------------------*/
/*

VSADM8OU16B32H
ushort32 = __vsadm8ou16b32h_yvvv(uchar64, uchar64, uchar16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsatdl_vv
*----------------------------------------------------------------------------*/
/*

VSATDL
long8 = __vsatdl_vv(long8);

*/


/*-----------------------------------------------------------------------------
* ID: __vsatdw_vv
*----------------------------------------------------------------------------*/
/*

VSATDW
long8 = __vsatdw_vv(long8);

*/


/*-----------------------------------------------------------------------------
* ID: __vsathb_vv
*----------------------------------------------------------------------------*/
/*

VSATHB
short32 = __vsathb_vv(short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vsatlw_vv
*----------------------------------------------------------------------------*/
/*

VSATLW
long8 = __vsatlw_vv(long8);

*/


/*-----------------------------------------------------------------------------
* ID: __vsatwh_vv
*----------------------------------------------------------------------------*/
/*

VSATWH
int16 = __vsatwh_vv(int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vscaledp_vvv
*----------------------------------------------------------------------------*/
/*

VSCALEDP
double8 = __vscaledp_vvv(double8, ulong8);

*/


/*-----------------------------------------------------------------------------
* ID: __vscalesp_vvv
*----------------------------------------------------------------------------*/
/*

VSCALESP
float16 = __vscalesp_vvv(float16, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vscatterb_pvv
*----------------------------------------------------------------------------*/
/*

VSCATTERB
char64 = __vscatterb_pvv(__vpred, char64);

*/


/*-----------------------------------------------------------------------------
* ID: __vscatternb_pvv
*----------------------------------------------------------------------------*/
/*

VSCATTERNB
char64 = __vscatternb_pvv(__vpred, char64);

*/


/*-----------------------------------------------------------------------------
* ID: __vsel_pvkv
*----------------------------------------------------------------------------*/
/*

VSEL
int16 = __vsel_pvkv(__vpred, int16, (int16)(k));
float16 = __vsel_pvkv(__vpred, float16, (float16)(k));
uint16 = __vsel_pvkv(__vpred, uint16, (uint16)(k));

*/

#define __vsel_pvkv(a,b,c) __overload("__vsel_pvkv",(a),(b),(c))((a),(b),(c))


/*-----------------------------------------------------------------------------
* ID: __vsel_pvvv
*----------------------------------------------------------------------------*/
/*

VSEL
char64 = __vsel_pvvv(__vpred, char64, char64);
short32 = __vsel_pvvv(__vpred, short32, short32);
int16 = __vsel_pvvv(__vpred, int16, int16);
long8 = __vsel_pvvv(__vpred, long8, long8);
uchar64 = __vsel_pvvv(__vpred, uchar64, uchar64);
ushort32 = __vsel_pvvv(__vpred, ushort32, ushort32);
uint16 = __vsel_pvvv(__vpred, uint16, uint16);
ulong8 = __vsel_pvvv(__vpred, ulong8, ulong8);

*/

#define __vsel_pvvv(a,b,c) __overload("__vsel_pvvv",(a),(b),(c))((a),(b),(c))


/*-----------------------------------------------------------------------------
* ID: __vshfl2b_vv
*----------------------------------------------------------------------------*/
/*

VSHFL2B
char64 = __vshfl2b_vv(char64);
uchar64 = __vshfl2b_vv(uchar64);

*/

#define __vshfl2b_vv(a) __overload("__vshfl2b_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vshfl2d_vv
*----------------------------------------------------------------------------*/
/*

VSHFL2D
long8 = __vshfl2d_vv(long8);
double8 = __vshfl2d_vv(double8);
cfloat8 = __vshfl2d_vv(cfloat8);
ulong8 = __vshfl2d_vv(ulong8);
cint8 = __vshfl2d_vv(cint8);

*/

#define __vshfl2d_vv(a) __overload("__vshfl2d_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vshfl2dee_vvv
*----------------------------------------------------------------------------*/
/*

VSHFL2DEE
long8 = __vshfl2dee_vvv(long8, long8);
double8 = __vshfl2dee_vvv(double8, double8);
cfloat8 = __vshfl2dee_vvv(cfloat8, cfloat8);
ulong8 = __vshfl2dee_vvv(ulong8, ulong8);
cint8 = __vshfl2dee_vvv(cint8, cint8);

*/

#define __vshfl2dee_vvv(a,b) __overload("__vshfl2dee_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vshfl2deo_vvv
*----------------------------------------------------------------------------*/
/*

VSHFL2DEO
long8 = __vshfl2deo_vvv(long8, long8);
double8 = __vshfl2deo_vvv(double8, double8);
cfloat8 = __vshfl2deo_vvv(cfloat8, cfloat8);
ulong8 = __vshfl2deo_vvv(ulong8, ulong8);
cint8 = __vshfl2deo_vvv(cint8, cint8);

*/

#define __vshfl2deo_vvv(a,b) __overload("__vshfl2deo_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vshfl2dhh_vvv
*----------------------------------------------------------------------------*/
/*

VSHFL2DHH
long8 = __vshfl2dhh_vvv(long8, long8);
double8 = __vshfl2dhh_vvv(double8, double8);
cfloat8 = __vshfl2dhh_vvv(cfloat8, cfloat8);
ulong8 = __vshfl2dhh_vvv(ulong8, ulong8);
cint8 = __vshfl2dhh_vvv(cint8, cint8);

*/

#define __vshfl2dhh_vvv(a,b) __overload("__vshfl2dhh_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vshfl2dlh_vvv
*----------------------------------------------------------------------------*/
/*

VSHFL2DLH
long8 = __vshfl2dlh_vvv(long8, long8);
double8 = __vshfl2dlh_vvv(double8, double8);
cfloat8 = __vshfl2dlh_vvv(cfloat8, cfloat8);
ulong8 = __vshfl2dlh_vvv(ulong8, ulong8);
cint8 = __vshfl2dlh_vvv(cint8, cint8);

*/

#define __vshfl2dlh_vvv(a,b) __overload("__vshfl2dlh_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vshfl2dll_vvv
*----------------------------------------------------------------------------*/
/*

VSHFL2DLL
long8 = __vshfl2dll_vvv(long8, long8);
double8 = __vshfl2dll_vvv(double8, double8);
cfloat8 = __vshfl2dll_vvv(cfloat8, cfloat8);
ulong8 = __vshfl2dll_vvv(ulong8, ulong8);
cint8 = __vshfl2dll_vvv(cint8, cint8);

*/

#define __vshfl2dll_vvv(a,b) __overload("__vshfl2dll_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vshfl2doo_vvv
*----------------------------------------------------------------------------*/
/*

VSHFL2DOO
long8 = __vshfl2doo_vvv(long8, long8);
double8 = __vshfl2doo_vvv(double8, double8);
cfloat8 = __vshfl2doo_vvv(cfloat8, cfloat8);
ulong8 = __vshfl2doo_vvv(ulong8, ulong8);
cint8 = __vshfl2doo_vvv(cint8, cint8);

*/

#define __vshfl2doo_vvv(a,b) __overload("__vshfl2doo_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vshfl2h_vv
*----------------------------------------------------------------------------*/
/*

VSHFL2H
short32 = __vshfl2h_vv(short32);
ushort32 = __vshfl2h_vv(ushort32);
cchar32 = __vshfl2h_vv(cchar32);

*/

#define __vshfl2h_vv(a) __overload("__vshfl2h_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vshfl2hhh_vvv
*----------------------------------------------------------------------------*/
/*

VSHFL2HHH
short32 = __vshfl2hhh_vvv(short32, short32);
ushort32 = __vshfl2hhh_vvv(ushort32, ushort32);
cchar32 = __vshfl2hhh_vvv(cchar32, cchar32);

*/

#define __vshfl2hhh_vvv(a,b) __overload("__vshfl2hhh_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vshfl2hll_vvv
*----------------------------------------------------------------------------*/
/*

VSHFL2HLL
short32 = __vshfl2hll_vvv(short32, short32);
ushort32 = __vshfl2hll_vvv(ushort32, ushort32);
cchar32 = __vshfl2hll_vvv(cchar32, cchar32);

*/

#define __vshfl2hll_vvv(a,b) __overload("__vshfl2hll_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vshfl2w_vv
*----------------------------------------------------------------------------*/
/*

VSHFL2W
int16 = __vshfl2w_vv(int16);
float16 = __vshfl2w_vv(float16);
uint16 = __vshfl2w_vv(uint16);
cshort16 = __vshfl2w_vv(cshort16);

*/

#define __vshfl2w_vv(a) __overload("__vshfl2w_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vshfl2whh_vvv
*----------------------------------------------------------------------------*/
/*

VSHFL2WHH
int16 = __vshfl2whh_vvv(int16, int16);
float16 = __vshfl2whh_vvv(float16, float16);
uint16 = __vshfl2whh_vvv(uint16, uint16);
cshort16 = __vshfl2whh_vvv(cshort16, cshort16);

*/

#define __vshfl2whh_vvv(a,b) __overload("__vshfl2whh_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vshfl2wll_vvv
*----------------------------------------------------------------------------*/
/*

VSHFL2WLL
int16 = __vshfl2wll_vvv(int16, int16);
float16 = __vshfl2wll_vvv(float16, float16);
uint16 = __vshfl2wll_vvv(uint16, uint16);
cshort16 = __vshfl2wll_vvv(cshort16, cshort16);

*/

#define __vshfl2wll_vvv(a,b) __overload("__vshfl2wll_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vshfl3_vvv
*----------------------------------------------------------------------------*/
/*

VSHFL3
ulong8 = __vshfl3_vvv(uint16, uint16);
long8 = __vshfl3_vvv(int16, int16);

*/

#define __vshfl3_vvv(a,b) __overload("__vshfl3_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vshfl4b_vv
*----------------------------------------------------------------------------*/
/*

VSHFL4B
char64 = __vshfl4b_vv(char64);
uchar64 = __vshfl4b_vv(uchar64);

*/

#define __vshfl4b_vv(a) __overload("__vshfl4b_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vshfl4h_vv
*----------------------------------------------------------------------------*/
/*

VSHFL4H
short32 = __vshfl4h_vv(short32);
ushort32 = __vshfl4h_vv(ushort32);
cchar32 = __vshfl4h_vv(cchar32);

*/

#define __vshfl4h_vv(a) __overload("__vshfl4h_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vshfl4w_vv
*----------------------------------------------------------------------------*/
/*

VSHFL4W
int16 = __vshfl4w_vv(int16);
float16 = __vshfl4w_vv(float16);
uint16 = __vshfl4w_vv(uint16);
cshort16 = __vshfl4w_vv(cshort16);

*/

#define __vshfl4w_vv(a) __overload("__vshfl4w_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vshl_vkv
*----------------------------------------------------------------------------*/
/*

VSHL
ulong8 = __vshl_vkv(ulong8, (uchar)(k={1-64}));

*/


/*-----------------------------------------------------------------------------
* ID: __vshl_vvv
*----------------------------------------------------------------------------*/
/*

VSHL
ulong8 = __vshl_vvv(ulong8, ulong8);

*/


/*-----------------------------------------------------------------------------
* ID: __vshlb_vkv
*----------------------------------------------------------------------------*/
/*

VSHLB
char64 = __vshlb_vkv(char64, (char64)(k={0-63}));
uchar64 = __vshlb_vkv(uchar64, (uchar64)(k={0-63}));

*/

#define __vshlb_vkv(a,b) __overload("__vshlb_vkv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vshlb_vvv
*----------------------------------------------------------------------------*/
/*

VSHLB
char64 = __vshlb_vvv(char64, int16);
uchar64 = __vshlb_vvv(uchar64, uint16);

*/

#define __vshlb_vvv(a,b) __overload("__vshlb_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vshlcb_pvv
*----------------------------------------------------------------------------*/
/*

VSHLCB
char64 = __vshlcb_pvv(__vpred, char64, char64);
uchar64 = __vshlcb_pvv(__vpred, uchar64, uchar64);

*/

#define __vshlcb_pvv(a,b,c) __overload("__vshlcb_pvv",(a),(b),(c))((a),(b),(c))


/*-----------------------------------------------------------------------------
* ID: __vshlch_pvv
*----------------------------------------------------------------------------*/
/*

VSHLCH
short32 = __vshlch_pvv(__vpred, short32, short32);
ushort32 = __vshlch_pvv(__vpred, ushort32, ushort32);

*/

#define __vshlch_pvv(a,b,c) __overload("__vshlch_pvv",(a),(b),(c))((a),(b),(c))


/*-----------------------------------------------------------------------------
* ID: __vshlcw_pvv
*----------------------------------------------------------------------------*/
/*

VSHLCW
int16 = __vshlcw_pvv(__vpred, int16, int16);
uint16 = __vshlcw_pvv(__vpred, uint16, uint16);

*/

#define __vshlcw_pvv(a,b,c) __overload("__vshlcw_pvv",(a),(b),(c))((a),(b),(c))


/*-----------------------------------------------------------------------------
* ID: __vshld_vkv
*----------------------------------------------------------------------------*/
/*

VSHLD
long8 = __vshld_vkv(long8, (long8)(k={0-63}));
ulong8 = __vshld_vkv(ulong8, (ulong8)(k={0-63}));

*/

#define __vshld_vkv(a,b) __overload("__vshld_vkv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vshld_vvv
*----------------------------------------------------------------------------*/
/*

VSHLD
long8 = __vshld_vvv(long8, long8);
ulong8 = __vshld_vvv(ulong8, ulong8);

*/

#define __vshld_vvv(a,b) __overload("__vshld_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vshlh_vkv
*----------------------------------------------------------------------------*/
/*

VSHLH
short32 = __vshlh_vkv(short32, (short32)(k={0-63}));
ushort32 = __vshlh_vkv(ushort32, (ushort32)(k={0-63}));

*/

#define __vshlh_vkv(a,b) __overload("__vshlh_vkv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vshlh_vvv
*----------------------------------------------------------------------------*/
/*

VSHLH
short32 = __vshlh_vvv(short32, int16);
ushort32 = __vshlh_vvv(ushort32, uint16);

*/

#define __vshlh_vvv(a,b) __overload("__vshlh_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vshlm16b_vvv
*----------------------------------------------------------------------------*/
/*

VSHLM16B
char64 = __vshlm16b_vvv(char64, char16);

*/


/*-----------------------------------------------------------------------------
* ID: __vshlm1b_vrv
*----------------------------------------------------------------------------*/
/*

VSHLM1B
char64 = __vshlm1b_vrv(char64, char);

*/


/*-----------------------------------------------------------------------------
* ID: __vshlm2b_vrv
*----------------------------------------------------------------------------*/
/*

VSHLM2B
char64 = __vshlm2b_vrv(char64, char2);

*/


/*-----------------------------------------------------------------------------
* ID: __vshlm4b_vrv
*----------------------------------------------------------------------------*/
/*

VSHLM4B
char64 = __vshlm4b_vrv(char64, char4);

*/


/*-----------------------------------------------------------------------------
* ID: __vshlm8b_vdv
*----------------------------------------------------------------------------*/
/*

VSHLM8B
char64 = __vshlm8b_vdv(char64, char8);

*/


/*-----------------------------------------------------------------------------
* ID: __vshlmb_vvv
*----------------------------------------------------------------------------*/
/*

VSHLMB
int16 = __vshlmb_vvv(int16, char64);

*/


/*-----------------------------------------------------------------------------
* ID: __vshlw_vkv
*----------------------------------------------------------------------------*/
/*

VSHLW
int16 = __vshlw_vkv(int16, (int16)(k={0-63}));
uint16 = __vshlw_vkv(uint16, (uint16)(k={0-63}));

*/

#define __vshlw_vkv(a,b) __overload("__vshlw_vkv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vshlw_vvv
*----------------------------------------------------------------------------*/
/*

VSHLW
int16 = __vshlw_vvv(int16, int16);
uint16 = __vshlw_vvv(uint16, uint16);

*/

#define __vshlw_vvv(a,b) __overload("__vshlw_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vshr_vkv
*----------------------------------------------------------------------------*/
/*

VSHR
long8 = __vshr_vkv(long8, (uchar)(k={1-64}));

*/


/*-----------------------------------------------------------------------------
* ID: __vshr_vvv
*----------------------------------------------------------------------------*/
/*

VSHR
long8 = __vshr_vvv(long8, ulong8);

*/


/*-----------------------------------------------------------------------------
* ID: __vshrb_vkv
*----------------------------------------------------------------------------*/
/*

VSHRB
char64 = __vshrb_vkv(char64, (char64)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vshrb_vvv
*----------------------------------------------------------------------------*/
/*

VSHRB
char64 = __vshrb_vvv(char64, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vshrd_vkv
*----------------------------------------------------------------------------*/
/*

VSHRD
long8 = __vshrd_vkv(long8, (long8)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vshrd_vvv
*----------------------------------------------------------------------------*/
/*

VSHRD
long8 = __vshrd_vvv(long8, long8);

*/


/*-----------------------------------------------------------------------------
* ID: __vshrh_vkv
*----------------------------------------------------------------------------*/
/*

VSHRH
short32 = __vshrh_vkv(short32, (short32)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vshrh_vvv
*----------------------------------------------------------------------------*/
/*

VSHRH
short32 = __vshrh_vvv(short32, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vshrm16b_vvv
*----------------------------------------------------------------------------*/
/*

VSHRM16B
char64 = __vshrm16b_vvv(char64, char16);

*/


/*-----------------------------------------------------------------------------
* ID: __vshrm1b_vrv
*----------------------------------------------------------------------------*/
/*

VSHRM1B
char64 = __vshrm1b_vrv(char64, char);

*/


/*-----------------------------------------------------------------------------
* ID: __vshrm2b_vrv
*----------------------------------------------------------------------------*/
/*

VSHRM2B
char64 = __vshrm2b_vrv(char64, char2);

*/


/*-----------------------------------------------------------------------------
* ID: __vshrm4b_vrv
*----------------------------------------------------------------------------*/
/*

VSHRM4B
char64 = __vshrm4b_vrv(char64, char4);

*/


/*-----------------------------------------------------------------------------
* ID: __vshrm8b_vdv
*----------------------------------------------------------------------------*/
/*

VSHRM8B
char64 = __vshrm8b_vdv(char64, char8);

*/


/*-----------------------------------------------------------------------------
* ID: __vshrmb_vvv
*----------------------------------------------------------------------------*/
/*

VSHRMB
int16 = __vshrmb_vvv(int16, char64);

*/


/*-----------------------------------------------------------------------------
* ID: __vshrrb_vkv
*----------------------------------------------------------------------------*/
/*

VSHRRB
char64 = __vshrrb_vkv(char64, (uchar64)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vshrrb_vvv
*----------------------------------------------------------------------------*/
/*

VSHRRB
char64 = __vshrrb_vvv(char64, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vshrrd_vkv
*----------------------------------------------------------------------------*/
/*

VSHRRD
long8 = __vshrrd_vkv(long8, (uchar8)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vshrrd_vvv
*----------------------------------------------------------------------------*/
/*

VSHRRD
long8 = __vshrrd_vvv(long8, ulong8);

*/


/*-----------------------------------------------------------------------------
* ID: __vshrrh_vkv
*----------------------------------------------------------------------------*/
/*

VSHRRH
short32 = __vshrrh_vkv(short32, (uchar32)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vshrrh_vvv
*----------------------------------------------------------------------------*/
/*

VSHRRH
short32 = __vshrrh_vvv(short32, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vshrrw_vkv
*----------------------------------------------------------------------------*/
/*

VSHRRW
int16 = __vshrrw_vkv(int16, (uchar16)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vshrrw_vvv
*----------------------------------------------------------------------------*/
/*

VSHRRW
int16 = __vshrrw_vvv(int16, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vshru_vkv
*----------------------------------------------------------------------------*/
/*

VSHRU
ulong8 = __vshru_vkv(ulong8, (uchar)(k={1-64}));

*/


/*-----------------------------------------------------------------------------
* ID: __vshru_vvv
*----------------------------------------------------------------------------*/
/*

VSHRU
ulong8 = __vshru_vvv(ulong8, ulong8);

*/


/*-----------------------------------------------------------------------------
* ID: __vshrub_vkv
*----------------------------------------------------------------------------*/
/*

VSHRUB
uchar64 = __vshrub_vkv(uchar64, (uchar64)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vshrub_vvv
*----------------------------------------------------------------------------*/
/*

VSHRUB
uchar64 = __vshrub_vvv(uchar64, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vshrud_vkv
*----------------------------------------------------------------------------*/
/*

VSHRUD
ulong8 = __vshrud_vkv(ulong8, (ulong8)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vshrud_vvv
*----------------------------------------------------------------------------*/
/*

VSHRUD
ulong8 = __vshrud_vvv(ulong8, ulong8);

*/


/*-----------------------------------------------------------------------------
* ID: __vshruh_vkv
*----------------------------------------------------------------------------*/
/*

VSHRUH
ushort32 = __vshruh_vkv(ushort32, (ushort32)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vshruh_vvv
*----------------------------------------------------------------------------*/
/*

VSHRUH
ushort32 = __vshruh_vvv(ushort32, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vshrurb_vkv
*----------------------------------------------------------------------------*/
/*

VSHRURB
uchar64 = __vshrurb_vkv(uchar64, (uchar64)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vshrurb_vvv
*----------------------------------------------------------------------------*/
/*

VSHRURB
uchar64 = __vshrurb_vvv(uchar64, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vshrurd_vkv
*----------------------------------------------------------------------------*/
/*

VSHRURD
ulong8 = __vshrurd_vkv(ulong8, (uchar8)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vshrurd_vvv
*----------------------------------------------------------------------------*/
/*

VSHRURD
ulong8 = __vshrurd_vvv(ulong8, ulong8);

*/


/*-----------------------------------------------------------------------------
* ID: __vshrurh_vkv
*----------------------------------------------------------------------------*/
/*

VSHRURH
ushort32 = __vshrurh_vkv(ushort32, (uchar32)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vshrurh_vvv
*----------------------------------------------------------------------------*/
/*

VSHRURH
ushort32 = __vshrurh_vvv(ushort32, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vshrurw_vkv
*----------------------------------------------------------------------------*/
/*

VSHRURW
uint16 = __vshrurw_vkv(uint16, (uchar16)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vshrurw_vvv
*----------------------------------------------------------------------------*/
/*

VSHRURW
uint16 = __vshrurw_vvv(uint16, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vshruw_vkv
*----------------------------------------------------------------------------*/
/*

VSHRUW
uint16 = __vshruw_vkv(uint16, (uint16)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vshruw_vvv
*----------------------------------------------------------------------------*/
/*

VSHRUW
uint16 = __vshruw_vvv(uint16, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vshrw_vkv
*----------------------------------------------------------------------------*/
/*

VSHRW
int16 = __vshrw_vkv(int16, (int16)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vshrw_vvv
*----------------------------------------------------------------------------*/
/*

VSHRW
int16 = __vshrw_vvv(int16, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vshvluw_vvv
*----------------------------------------------------------------------------*/
/*

VSHVLUW
uint16 = __vshvluw_vvv(uint16, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vshvlw_vvv
*----------------------------------------------------------------------------*/
/*

VSHVLW
int16 = __vshvlw_vvv(int16, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vshvruw_vvv
*----------------------------------------------------------------------------*/
/*

VSHVRUW
uint16 = __vshvruw_vvv(uint16, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vshvrw_vvv
*----------------------------------------------------------------------------*/
/*

VSHVRW
int16 = __vshvrw_vvv(int16, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsmpyhw_vvw
*----------------------------------------------------------------------------*/
/*

VSMPYHW
__vsmpyhw_vvw(short32, short32, int16&, int16&);

*/


/*-----------------------------------------------------------------------------
* ID: __vsmpyr17ww_vvv
*----------------------------------------------------------------------------*/
/*

VSMPYR17WW
int16 = __vsmpyr17ww_vvv(int16, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsmpyr1hh_vvv
*----------------------------------------------------------------------------*/
/*

VSMPYR1HH
short32 = __vsmpyr1hh_vvv(short32, short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vsmpyr1ww_vvv
*----------------------------------------------------------------------------*/
/*

VSMPYR1WW
int16 = __vsmpyr1ww_vvv(int16, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsmpyrsuhh_vvv
*----------------------------------------------------------------------------*/
/*

VSMPYRSUHH
short32 = __vsmpyrsuhh_vvv(short32, ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vsmpyruhh_vvv
*----------------------------------------------------------------------------*/
/*

VSMPYRUHH
ushort32 = __vsmpyruhh_vvv(ushort32, ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vsmpyww_vvv
*----------------------------------------------------------------------------*/
/*

VSMPYWW
int16 = __vsmpyww_vvv(int16, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsortdsp_vv
*----------------------------------------------------------------------------*/
/*

VSORTDSP
float16 = __vsortdsp_vv(float16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsortdw_vv
*----------------------------------------------------------------------------*/
/*

VSORTDW
int16 = __vsortdw_vv(int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsortduw_vv
*----------------------------------------------------------------------------*/
/*

VSORTDUW
uint16 = __vsortduw_vv(uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsortisp_vv
*----------------------------------------------------------------------------*/
/*

VSORTISP
float16 = __vsortisp_vv(float16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsortiw_vv
*----------------------------------------------------------------------------*/
/*

VSORTIW
int16 = __vsortiw_vv(int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsortiuw_vv
*----------------------------------------------------------------------------*/
/*

VSORTIUW
uint16 = __vsortiuw_vv(uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsortpdsp_vv
*----------------------------------------------------------------------------*/
/*

VSORTPDSP
uchar64 = __vsortpdsp_vv(float16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsortpdw_vv
*----------------------------------------------------------------------------*/
/*

VSORTPDW
uchar64 = __vsortpdw_vv(int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsortpduw_vv
*----------------------------------------------------------------------------*/
/*

VSORTPDUW
uchar64 = __vsortpduw_vv(uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsortpisp_vv
*----------------------------------------------------------------------------*/
/*

VSORTPISP
uchar64 = __vsortpisp_vv(float16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsortpiw_vv
*----------------------------------------------------------------------------*/
/*

VSORTPIW
uchar64 = __vsortpiw_vv(int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsortpiuw_vv
*----------------------------------------------------------------------------*/
/*

VSORTPIUW
uchar64 = __vsortpiuw_vv(uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vspackdw_vvv
*----------------------------------------------------------------------------*/
/*

VSPACKDW
int16 = __vspackdw_vvv(long8, long8);

*/


/*-----------------------------------------------------------------------------
* ID: __vspackhb_vvv
*----------------------------------------------------------------------------*/
/*

VSPACKHB
char64 = __vspackhb_vvv(short32, short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vspackudw_vvv
*----------------------------------------------------------------------------*/
/*

VSPACKUDW
uint16 = __vspackudw_vvv(long8, long8);

*/


/*-----------------------------------------------------------------------------
* ID: __vspackuhb_vvv
*----------------------------------------------------------------------------*/
/*

VSPACKUHB
uchar64 = __vspackuhb_vvv(short32, short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vspackuwh_vvv
*----------------------------------------------------------------------------*/
/*

VSPACKUWH
ushort32 = __vspackuwh_vvv(int16, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vspackwh_vvv
*----------------------------------------------------------------------------*/
/*

VSPACKWH
short32 = __vspackwh_vvv(int16, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vspdph_vv
*----------------------------------------------------------------------------*/
/*

VSPDPH
double8 = __vspdph_vv(float16);

*/


/*-----------------------------------------------------------------------------
* ID: __vspdpl_vv
*----------------------------------------------------------------------------*/
/*

VSPDPL
double8 = __vspdpl_vv(float16);

*/

/*-----------------------------------------------------------------------------
* ID: __vsphp_vv
*----------------------------------------------------------------------------*/
/*

VSPHP
uint16 = __vsphp_vv(float16);

*/

/*-----------------------------------------------------------------------------
* ID: __vspint_vv
*----------------------------------------------------------------------------*/
/*

VSPINT
int16 = __vspint_vv(float16);

*/


/*-----------------------------------------------------------------------------
* ID: __vspinth_vv
*----------------------------------------------------------------------------*/
/*

VSPINTH
short32 = __vspinth_vv(float16);

*/


/*-----------------------------------------------------------------------------
* ID: __vspinthpk_vv
*----------------------------------------------------------------------------*/
/*

VSPINTHPK
short32 = __vspinthpk_vv(float16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsptrunc_vv
*----------------------------------------------------------------------------*/
/*

VSPTRUNC
int16 = __vsptrunc_vv(float16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsshlh_vkv
*----------------------------------------------------------------------------*/
/*

VSSHLH
short32 = __vsshlh_vkv(short32, (uchar32)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vsshlh_vvv
*----------------------------------------------------------------------------*/
/*

VSSHLH
short32 = __vsshlh_vvv(short32, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsshlrdw_vkv
*----------------------------------------------------------------------------*/
/*

VSSHLRDW
int16 = __vsshlrdw_vkv(long8, (uchar8)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vsshlrdw_vvv
*----------------------------------------------------------------------------*/
/*

VSSHLRDW
int16 = __vsshlrdw_vvv(long8, ulong8);

*/


/*-----------------------------------------------------------------------------
* ID: __vsshlrhb_vkv
*----------------------------------------------------------------------------*/
/*

VSSHLRHB
char64 = __vsshlrhb_vkv(short32, (uchar16)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vsshlrhb_vvv
*----------------------------------------------------------------------------*/
/*

VSSHLRHB
char64 = __vsshlrhb_vvv(short32, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsshlrwh_vkv
*----------------------------------------------------------------------------*/
/*

VSSHLRWH
short32 = __vsshlrwh_vkv(int16, (uchar16)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vsshlrwh_vvv
*----------------------------------------------------------------------------*/
/*

VSSHLRWH
short32 = __vsshlrwh_vvv(int16, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsshlsuh_vkv
*----------------------------------------------------------------------------*/
/*

VSSHLSUH
ushort32 = __vsshlsuh_vkv(short32, (uchar32)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vsshlsuh_vvv
*----------------------------------------------------------------------------*/
/*

VSSHLSUH
ushort32 = __vsshlsuh_vvv(short32, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsshlsurdw_vkv
*----------------------------------------------------------------------------*/
/*

VSSHLSURDW
uint16 = __vsshlsurdw_vkv(long8, (uchar8)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vsshlsurdw_vvv
*----------------------------------------------------------------------------*/
/*

VSSHLSURDW
uint16 = __vsshlsurdw_vvv(long8, ulong8);

*/


/*-----------------------------------------------------------------------------
* ID: __vsshlsurhb_vkv
*----------------------------------------------------------------------------*/
/*

VSSHLSURHB
uchar64 = __vsshlsurhb_vkv(short32, (uchar16)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vsshlsurhb_vvv
*----------------------------------------------------------------------------*/
/*

VSSHLSURHB
uchar64 = __vsshlsurhb_vvv(short32, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsshlsurwh_vkv
*----------------------------------------------------------------------------*/
/*

VSSHLSURWH
ushort32 = __vsshlsurwh_vkv(int16, (uchar16)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vsshlsurwh_vvv
*----------------------------------------------------------------------------*/
/*

VSSHLSURWH
ushort32 = __vsshlsurwh_vvv(int16, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsshlsuw_vkv
*----------------------------------------------------------------------------*/
/*

VSSHLSUW
uint16 = __vsshlsuw_vkv(int16, (uchar16)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vsshlsuw_vvv
*----------------------------------------------------------------------------*/
/*

VSSHLSUW
uint16 = __vsshlsuw_vvv(int16, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsshluh_vkv
*----------------------------------------------------------------------------*/
/*

VSSHLUH
ushort32 = __vsshluh_vkv(ushort32, (uchar32)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vsshluh_vvv
*----------------------------------------------------------------------------*/
/*

VSSHLUH
ushort32 = __vsshluh_vvv(ushort32, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsshlurdw_vkv
*----------------------------------------------------------------------------*/
/*

VSSHLURDW
uint16 = __vsshlurdw_vkv(ulong8, (uchar8)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vsshlurdw_vvv
*----------------------------------------------------------------------------*/
/*

VSSHLURDW
uint16 = __vsshlurdw_vvv(ulong8, ulong8);

*/


/*-----------------------------------------------------------------------------
* ID: __vsshlurhb_vkv
*----------------------------------------------------------------------------*/
/*

VSSHLURHB
uchar64 = __vsshlurhb_vkv(ushort32, (uchar16)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vsshlurhb_vvv
*----------------------------------------------------------------------------*/
/*

VSSHLURHB
uchar64 = __vsshlurhb_vvv(ushort32, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsshlurwh_vkv
*----------------------------------------------------------------------------*/
/*

VSSHLURWH
ushort32 = __vsshlurwh_vkv(uint16, (uchar16)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vsshlurwh_vvv
*----------------------------------------------------------------------------*/
/*

VSSHLURWH
ushort32 = __vsshlurwh_vvv(uint16, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsshluw_vkv
*----------------------------------------------------------------------------*/
/*

VSSHLUW
uint16 = __vsshluw_vkv(uint16, (uchar16)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vsshluw_vvv
*----------------------------------------------------------------------------*/
/*

VSSHLUW
uint16 = __vsshluw_vvv(uint16, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsshlw_vkv
*----------------------------------------------------------------------------*/
/*

VSSHLW
int16 = __vsshlw_vkv(int16, (uchar16)(k={0-63}));

*/


/*-----------------------------------------------------------------------------
* ID: __vsshlw_vvv
*----------------------------------------------------------------------------*/
/*

VSSHLW
int16 = __vsshlw_vvv(int16, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsshvlw_vvv
*----------------------------------------------------------------------------*/
/*

VSSHVLW
int16 = __vsshvlw_vvv(int16, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsshvrw_vvv
*----------------------------------------------------------------------------*/
/*

VSSHVRW
int16 = __vsshvrw_vvv(int16, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vssubb_vkv
*----------------------------------------------------------------------------*/
/*

VSSUBB
char64 = __vssubb_vkv(char64, (char64)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __vssubb_vvv
*----------------------------------------------------------------------------*/
/*

VSSUBB
char64 = __vssubb_vvv(char64, char64);

*/


/*-----------------------------------------------------------------------------
* ID: __vssubh_vkv
*----------------------------------------------------------------------------*/
/*

VSSUBH
short32 = __vssubh_vkv(short32, (short32)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __vssubh_vvv
*----------------------------------------------------------------------------*/
/*

VSSUBH
short32 = __vssubh_vvv(short32, short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vssubw_vkv
*----------------------------------------------------------------------------*/
/*

VSSUBW
int16 = __vssubw_vkv(int16, (int16)(k));

*/


/*-----------------------------------------------------------------------------
* ID: __vssubw_vvv
*----------------------------------------------------------------------------*/
/*

VSSUBW
int16 = __vssubw_vvv(int16, int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsubabsb_vvv
*----------------------------------------------------------------------------*/
/*

VSUBABSB
uchar64 = __vsubabsb_vvv(uchar64, uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vsubabsd_vvv
*----------------------------------------------------------------------------*/
/*

VSUBABSD
ulong8 = __vsubabsd_vvv(ulong8, ulong8);

*/


/*-----------------------------------------------------------------------------
* ID: __vsubabsh_vvv
*----------------------------------------------------------------------------*/
/*

VSUBABSH
ushort32 = __vsubabsh_vvv(ushort32, ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vsubabsw_vvv
*----------------------------------------------------------------------------*/
/*

VSUBABSW
uint16 = __vsubabsw_vvv(uint16, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsubb_vkv
*----------------------------------------------------------------------------*/
/*

VSUBB
char64 = __vsubb_vkv(char64, (char64)(k));
uchar64 = __vsubb_vkv(uchar64, (uchar64)(k));

*/

#define __vsubb_vkv(a,b) __overload("__vsubb_vkv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vsubb_vvv
*----------------------------------------------------------------------------*/
/*

VSUBB
char64 = __vsubb_vvv(char64, char64);
uchar64 = __vsubb_vvv(uchar64, uchar64);

*/

#define __vsubb_vvv(a,b) __overload("__vsubb_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vsubcw_vvv
*----------------------------------------------------------------------------*/
/*

VSUBCW
uint16 = __vsubcw_vvv(uint16, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsubd_vkv
*----------------------------------------------------------------------------*/
/*

VSUBD
long8 = __vsubd_vkv(long8, (int8)(k));
ulong8 = __vsubd_vkv(ulong8, (uint8)(k={0-0x7fffffff}));

*/

#define __vsubd_vkv(a,b) __overload("__vsubd_vkv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vsubd_vvv
*----------------------------------------------------------------------------*/
/*

VSUBD
long8 = __vsubd_vvv(long8, long8);
ulong8 = __vsubd_vvv(ulong8, ulong8);

*/

#define __vsubd_vvv(a,b) __overload("__vsubd_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vsubdp_vvv
*----------------------------------------------------------------------------*/
/*

VSUBDP
double8 = __vsubdp_vvv(double8, double8);

*/


/*-----------------------------------------------------------------------------
* ID: __vsubh_vkv
*----------------------------------------------------------------------------*/
/*

VSUBH
short32 = __vsubh_vkv(short32, (short32)(k));
ushort32 = __vsubh_vkv(ushort32, (ushort32)(k));

*/

#define __vsubh_vkv(a,b) __overload("__vsubh_vkv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vsubh_vvv
*----------------------------------------------------------------------------*/
/*

VSUBH
short32 = __vsubh_vvv(short32, short32);
ushort32 = __vsubh_vvv(ushort32, ushort32);

*/

#define __vsubh_vvv(a,b) __overload("__vsubh_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vsubrb_vkv
*----------------------------------------------------------------------------*/
/*

VSUBRB
char64 = __vsubrb_vkv(char64, (char64)(k));
uchar64 = __vsubrb_vkv(uchar64, (uchar64)(k));

*/

#define __vsubrb_vkv(a,b) __overload("__vsubrb_vkv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vsubrb_vvv
*----------------------------------------------------------------------------*/
/*

VSUBRB
char64 = __vsubrb_vvv(char64, char64);
uchar64 = __vsubrb_vvv(uchar64, uchar64);

*/

#define __vsubrb_vvv(a,b) __overload("__vsubrb_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vsubrd_vkv
*----------------------------------------------------------------------------*/
/*

VSUBRD
long8 = __vsubrd_vkv(long8, (int8)(k));
ulong8 = __vsubrd_vkv(ulong8, (uint8)(k={0-0x7fffffff}));

*/

#define __vsubrd_vkv(a,b) __overload("__vsubrd_vkv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vsubrd_vvv
*----------------------------------------------------------------------------*/
/*

VSUBRD
long8 = __vsubrd_vvv(long8, long8);
ulong8 = __vsubrd_vvv(ulong8, ulong8);

*/

#define __vsubrd_vvv(a,b) __overload("__vsubrd_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vsubrh_vkv
*----------------------------------------------------------------------------*/
/*

VSUBRH
short32 = __vsubrh_vkv(short32, (short32)(k));
ushort32 = __vsubrh_vkv(ushort32, (ushort32)(k));

*/

#define __vsubrh_vkv(a,b) __overload("__vsubrh_vkv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vsubrh_vvv
*----------------------------------------------------------------------------*/
/*

VSUBRH
short32 = __vsubrh_vvv(short32, short32);
ushort32 = __vsubrh_vvv(ushort32, ushort32);

*/

#define __vsubrh_vvv(a,b) __overload("__vsubrh_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vsubrw_vkv
*----------------------------------------------------------------------------*/
/*

VSUBRW
int16 = __vsubrw_vkv(int16, (int16)(k));
uint16 = __vsubrw_vkv(uint16, (uint16)(k));

*/

#define __vsubrw_vkv(a,b) __overload("__vsubrw_vkv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vsubrw_vvv
*----------------------------------------------------------------------------*/
/*

VSUBRW
int16 = __vsubrw_vvv(int16, int16);
uint16 = __vsubrw_vvv(uint16, uint16);

*/

#define __vsubrw_vvv(a,b) __overload("__vsubrw_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vsubsp_vvv
*----------------------------------------------------------------------------*/
/*

VSUBSP
float16 = __vsubsp_vvv(float16, float16);

*/


/*-----------------------------------------------------------------------------
* ID: __vsubw_vkv
*----------------------------------------------------------------------------*/
/*

VSUBW
int16 = __vsubw_vkv(int16, (int16)(k));
uint16 = __vsubw_vkv(uint16, (uint16)(k));

*/

#define __vsubw_vkv(a,b) __overload("__vsubw_vkv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vsubw_vvv
*----------------------------------------------------------------------------*/
/*

VSUBW
int16 = __vsubw_vvv(int16, int16);
uint16 = __vsubw_vvv(uint16, uint16);

*/

#define __vsubw_vvv(a,b) __overload("__vsubw_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vswapb_vv
*----------------------------------------------------------------------------*/
/*

VSWAPB
char64 = __vswapb_vv(char64);
uchar64 = __vswapb_vv(uchar64);

*/

#define __vswapb_vv(a) __overload("__vswapb_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vswapd_vv
*----------------------------------------------------------------------------*/
/*

VSWAPD
long8 = __vswapd_vv(long8);
double8 = __vswapd_vv(double8);
cfloat8 = __vswapd_vv(cfloat8);
ulong8 = __vswapd_vv(ulong8);
cint8 = __vswapd_vv(cint8);

*/

#define __vswapd_vv(a) __overload("__vswapd_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vswaph_vv
*----------------------------------------------------------------------------*/
/*

VSWAPH
short32 = __vswaph_vv(short32);
ushort32 = __vswaph_vv(ushort32);
cchar32 = __vswaph_vv(cchar32);

*/

#define __vswaph_vv(a) __overload("__vswaph_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vswapw_vv
*----------------------------------------------------------------------------*/
/*

VSWAPW
int16 = __vswapw_vv(int16);
float16 = __vswapw_vv(float16);
uint16 = __vswapw_vv(uint16);
cshort16 = __vswapw_vv(cshort16);

*/

#define __vswapw_vv(a) __overload("__vswapw_vv",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __vunpkhb_vv
*----------------------------------------------------------------------------*/
/*

VUNPKHB
short32 = __vunpkhb_vv(char64);

*/


/*-----------------------------------------------------------------------------
* ID: __vunpkhh_vv
*----------------------------------------------------------------------------*/
/*

VUNPKHH
int16 = __vunpkhh_vv(short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vunpkhub_vv
*----------------------------------------------------------------------------*/
/*

VUNPKHUB
ushort32 = __vunpkhub_vv(uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vunpkhuh_vv
*----------------------------------------------------------------------------*/
/*

VUNPKHUH
uint16 = __vunpkhuh_vv(ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vunpklb_vv
*----------------------------------------------------------------------------*/
/*

VUNPKLB
short32 = __vunpklb_vv(char64);

*/


/*-----------------------------------------------------------------------------
* ID: __vunpklh_vv
*----------------------------------------------------------------------------*/
/*

VUNPKLH
int16 = __vunpklh_vv(short32);

*/


/*-----------------------------------------------------------------------------
* ID: __vunpklub_vv
*----------------------------------------------------------------------------*/
/*

VUNPKLUB
ushort32 = __vunpklub_vv(uchar64);

*/


/*-----------------------------------------------------------------------------
* ID: __vunpkluh_vv
*----------------------------------------------------------------------------*/
/*

VUNPKLUH
uint16 = __vunpkluh_vv(ushort32);

*/


/*-----------------------------------------------------------------------------
* ID: __vunpkluw_vv
*----------------------------------------------------------------------------*/
/*

VUNPKLUW
ulong8 = __vunpkluw_vv(uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vunpklw_vv
*----------------------------------------------------------------------------*/
/*

VUNPKLW
long8 = __vunpklw_vv(int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vwpackh_vvv
*----------------------------------------------------------------------------*/
/*

VWPACKH
int16 = __vwpackh_vvv(int16, int16);
float16 = __vwpackh_vvv(float16, float16);
uint16 = __vwpackh_vvv(uint16, uint16);
cshort16 = __vwpackh_vvv(cshort16, cshort16);

*/

#define __vwpackh_vvv(a,b) __overload("__vwpackh_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vwpackl_vvv
*----------------------------------------------------------------------------*/
/*

VWPACKL
int16 = __vwpackl_vvv(int16, int16);
float16 = __vwpackl_vvv(float16, float16);
uint16 = __vwpackl_vvv(uint16, uint16);
cshort16 = __vwpackl_vvv(cshort16, cshort16);

*/

#define __vwpackl_vvv(a,b) __overload("__vwpackl_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vwunpkd_vv
*----------------------------------------------------------------------------*/
/*

VWUNPKD
long8 = __vwunpkd_vv(int8);

*/


/*-----------------------------------------------------------------------------
* ID: __vwunpkdh_vv
*----------------------------------------------------------------------------*/
/*

VWUNPKDH
long8 = __vwunpkdh_vv(int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vwunpkdl_vv
*----------------------------------------------------------------------------*/
/*

VWUNPKDL
long8 = __vwunpkdl_vv(int16);

*/


/*-----------------------------------------------------------------------------
* ID: __vwunpkdu_vv
*----------------------------------------------------------------------------*/
/*

VWUNPKDU
ulong8 = __vwunpkdu_vv(uint8);

*/


/*-----------------------------------------------------------------------------
* ID: __vwunpkudh_vv
*----------------------------------------------------------------------------*/
/*

VWUNPKUDH
ulong8 = __vwunpkudh_vv(uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vwunpkudl_vv
*----------------------------------------------------------------------------*/
/*

VWUNPKUDL
ulong8 = __vwunpkudl_vv(uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vxnorw_vvv
*----------------------------------------------------------------------------*/
/*

VXNORW
char64 = __vxnorw_vvv(char64, char64);
short32 = __vxnorw_vvv(short32, short32);
int16 = __vxnorw_vvv(int16, int16);
long8 = __vxnorw_vvv(long8, long8);
uchar64 = __vxnorw_vvv(uchar64, uchar64);
ushort32 = __vxnorw_vvv(ushort32, ushort32);
uint16 = __vxnorw_vvv(uint16, uint16);
ulong8 = __vxnorw_vvv(ulong8, ulong8);

*/

#define __vxnorw_vvv(a,b) __overload("__vxnorw_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vxormpyw_vvv
*----------------------------------------------------------------------------*/
/*

VXORMPYW
uint16 = __vxormpyw_vvv(uint16, uint16);

*/


/*-----------------------------------------------------------------------------
* ID: __vxorw_vkv
*----------------------------------------------------------------------------*/
/*

VXORW
int16 = __vxorw_vkv(int16, (int16)(k));
uint16 = __vxorw_vkv(uint16, (uint16)(k));

*/

#define __vxorw_vkv(a,b) __overload("__vxorw_vkv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __vxorw_vvv
*----------------------------------------------------------------------------*/
/*

VXORW
char64 = __vxorw_vvv(char64, char64);
short32 = __vxorw_vvv(short32, short32);
int16 = __vxorw_vvv(int16, int16);
long8 = __vxorw_vvv(long8, long8);
uchar64 = __vxorw_vvv(uchar64, uchar64);
ushort32 = __vxorw_vvv(ushort32, ushort32);
uint16 = __vxorw_vvv(uint16, uint16);
ulong8 = __vxorw_vvv(ulong8, ulong8);

*/

#define __vxorw_vvv(a,b) __overload("__vxorw_vvv",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __xnor_ppp
*----------------------------------------------------------------------------*/
/*

XNOR
__vpred = __xnor_ppp(__vpred, __vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __xnord_ddd
*----------------------------------------------------------------------------*/
/*

XNORD
char8 = __xnord_ddd(char8, char8);
short4 = __xnord_ddd(short4, short4);
int2 = __xnord_ddd(int2, int2);
long = __xnord_ddd(long, long);
uchar8 = __xnord_ddd(uchar8, uchar8);
ushort4 = __xnord_ddd(ushort4, ushort4);
uint2 = __xnord_ddd(uint2, uint2);
ulong = __xnord_ddd(ulong, ulong);

*/

#define __xnord_ddd(a,b) __overload("__xnord_ddd",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __xnord_dkd
*----------------------------------------------------------------------------*/
/*

XNORD
long = __xnord_dkd(long, (int)(k));
ulong = __xnord_dkd(ulong, (uint)(k={0-0x7fffffff}));

*/

#define __xnord_dkd(a,b) __overload("__xnord_dkd",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __xnorw_rrr
*----------------------------------------------------------------------------*/
/*

XNORW
char4 = __xnorw_rrr(char4, char4);
short2 = __xnorw_rrr(short2, short2);
int = __xnorw_rrr(int, int);
uchar4 = __xnorw_rrr(uchar4, uchar4);
ushort2 = __xnorw_rrr(ushort2, ushort2);
uint = __xnorw_rrr(uint, uint);

*/

#define __xnorw_rrr(a,b) __overload("__xnorw_rrr",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __xor_ppp
*----------------------------------------------------------------------------*/
/*

XOR
__vpred = __xor_ppp(__vpred, __vpred);

*/


/*-----------------------------------------------------------------------------
* ID: __xord_ddd
*----------------------------------------------------------------------------*/
/*

XORD
char8 = __xord_ddd(char8, char8);
short4 = __xord_ddd(short4, short4);
int2 = __xord_ddd(int2, int2);
long = __xord_ddd(long, long);
uchar8 = __xord_ddd(uchar8, uchar8);
ushort4 = __xord_ddd(ushort4, ushort4);
uint2 = __xord_ddd(uint2, uint2);
ulong = __xord_ddd(ulong, ulong);

*/

#define __xord_ddd(a,b) __overload("__xord_ddd",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __xord_dkd
*----------------------------------------------------------------------------*/
/*

XORD
long = __xord_dkd(long, (int)(k));
ulong = __xord_dkd(ulong, (uint)(k={0-0x7fffffff}));

*/

#define __xord_dkd(a,b) __overload("__xord_dkd",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __xorw_rkr
*----------------------------------------------------------------------------*/
/*

XORW
char4 = __xorw_rkr(char4, (char4)(k));
short2 = __xorw_rkr(short2, (short2)(k));
int = __xorw_rkr(int, (int)(k));
uchar4 = __xorw_rkr(uchar4, (uchar4)(k));
ushort2 = __xorw_rkr(ushort2, (ushort2)(k));
uint = __xorw_rkr(uint, (uint)(k));

*/

#define __xorw_rkr(a,b) __overload("__xorw_rkr",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __xorw_rrr
*----------------------------------------------------------------------------*/
/*

XORW
char4 = __xorw_rrr(char4, char4);
short2 = __xorw_rrr(short2, short2);
int = __xorw_rrr(int, int);
uchar4 = __xorw_rrr(uchar4, uchar4);
ushort2 = __xorw_rrr(ushort2, ushort2);
uint = __xorw_rrr(uint, uint);

*/

#define __xorw_rrr(a,b) __overload("__xorw_rrr",(a),(b))((a),(b))


/*-----------------------------------------------------------------------------
* ID: __xpnd4h_rd
*----------------------------------------------------------------------------*/
/*

XPND4H
ushort4 = __xpnd4h_rd(uchar);
short4 = __xpnd4h_rd(char);

*/

#define __xpnd4h_rd(a) __overload("__xpnd4h_rd",(a))((a))


/*-----------------------------------------------------------------------------
* ID: __xpnd8b_rd
*----------------------------------------------------------------------------*/
/*

XPND8B
uchar8 = __xpnd8b_rd(uchar);
char8 = __xpnd8b_rd(char);

*/

#define __xpnd8b_rd(a) __overload("__xpnd8b_rd",(a))((a))

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __C7X_DIRECT_H */
