/*****************************************************************************/
/*  C7X_STRM_DEPRECATED.H                                                    */
/*                                                                           */
/* Copyright (c) 2017 Texas Instruments Incorporated                         */
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
/* NOTE!!!                                                                   */
/* NOTE!!!                                                                   */
/* NOTE!!!                                                                   */
/* NOTE!!!                                                                   */
/* NOTE!!!                                                                   */
/*                                                                           */
/* DO NOT USE THIS OLD AND DEPRECATED API FOR THE STREAMING ENGINE AND       */
/* STREAMING ADDRESS GENERATOR FEATURES. THIS API HAS BEEN DEPRECATED AND    */
/* WILL BE REMOVED IN A FUTURE VERSION OF THE COMPILER TOOLS. THIS           */
/* DEPRECATED API IS ONLY PROVIDED FOR BACKWARDS COMPATIBILITY WITH OLDER    */
/* SOURCE CODE. Use the API in c7x_strm.h instead.                           */
/*                                                                           */
/* NOTE!!!                                                                   */
/* NOTE!!!                                                                   */
/* NOTE!!!                                                                   */
/* NOTE!!!                                                                   */
/* NOTE!!!                                                                   */
/*                                                                           */
/*****************************************************************************/
#ifndef __C7X_H_INCLUDE__
#error "This file can only be included by parent header c7x.h"
#endif

#ifndef __C7X_STRM_DEPRECATED_H
#define __C7X_STRM_DEPRECATED_H

#include <stdint.h>
#include <linkage.h>

#ifdef __cplusplus
extern "C"
{
#endif

/*-----------------------------------------------------------------------------
* DEFINED STREAMING ENGINE / ADDRESS GENERATOR SETUP ROUTINES:
*------------------------------------------------------------------------------
* __STRM_TEMPLATE __set_ICNT0        (__STRM_TEMPLATE p, uint32_t ICNT);
* __STRM_TEMPLATE __set_ICNT1_DIM1   (__STRM_TEMPLATE p, uint32_t ICNT,
*                                                         int32_t DIM);
* __STRM_TEMPLATE __set_ICNT2_DIM2   (__STRM_TEMPLATE p, uint32_t ICNT,
*                                                         int32_t DIM);
* __STRM_TEMPLATE __set_ICNT3_DIM3   (__STRM_TEMPLATE p, uint32_t ICNT,
*                                                         int32_t DIM);
* __STRM_TEMPLATE __set_ICNT4_DIM4   (__STRM_TEMPLATE p, uint32_t ICNT,
*                                                         int32_t DIM);
* __STRM_TEMPLATE __set_ICNT5_DIM5   (__STRM_TEMPLATE p, uint32_t ICNT,
*                                                         int32_t DIM);
* __STRM_TEMPLATE __set_DECDIM1_WIDTH(__STRM_TEMPLATE p, uint32_t DECDIM_WIDTH);
* __STRM_TEMPLATE __set_DECDIM2_WIDTH(__STRM_TEMPLATE p, uint32_t DECDIM_WIDTH);
* __STRM_TEMPLATE __set_LEZR_CNT     (__STRM_TEMPLATE p,  uint8_t LEZR_CNT);
*
* __STRM_TEMPLATE __set_SE_FLAGS(__STRM_TEMPLATE param,
*                                __SE_FLAGS      *pFlags,
*                                __SE_CIRC_FLAGS *pCFlags);
*
* __STRM_TEMPLATE __set_SA_FLAGS(__STRM_TEMPLATE param,
*                                __SA_FLAGS      *pFlags);
*
*----------------------------------------------------------------------------
* DEFINED STREAMING ENGINE / ADDRESS FLAG DEFAULT INITIALIZATION ROUTINES
*----------------------------------------------------------------------------
* __SE_FLAGS      __SE_FLAGS_default     ();
* __SE_CIRC_FLAGS __SE_CIRC_FLAGS_default();
* __SA_FLAGS      __SA_FLAGS_default     ();
*
*----------------------------------------------------------------------------
* DEFINED STREAMING ENGINE / ADDRESS GENERATOR EXTRACT ROUTINES:
*----------------------------------------------------------------------------
* uint32_t         __get_ICNT0        (__STRM_TEMPLATE param);
* uint32_t         __get_ICNT1        (__STRM_TEMPLATE param);
*  int32_t         __get_DIM1         (__STRM_TEMPLATE param);
* uint32_t         __get_ICNT2        (__STRM_TEMPLATE param);
*  int32_t         __get_DIM2         (__STRM_TEMPLATE param);
* uint32_t         __get_ICNT3        (__STRM_TEMPLATE param);
*  int32_t         __get_DIM3         (__STRM_TEMPLATE param);
* uint32_t         __get_ICNT4        (__STRM_TEMPLATE param);
*  int32_t         __get_DIM4         (__STRM_TEMPLATE param);
* uint32_t         __get_ICNT5        (__STRM_TEMPLATE param);
*  int32_t         __get_DIM5         (__STRM_TEMPLATE param);
* uint32_t         __get_DECDIM1_WIDTH(__STRM_TEMPLATE param);
* uint32_t         __get_DECDIM2_WIDTH(__STRM_TEMPLATE param);
*  uint8_t         __get_LEZR_CNT     (__STRM_TEMPLATE param);
* __SE_FLAGS       __get_SE_FLAGS     (__STRM_TEMPLATE param);
* __SE_CIRC_FLAGS  __get_SE_CIRC_FLAGS(__STRM_TEMPLATE param);
* __SA_FLAGS       __get_SA_FLAGS     (__STRM_TEMPLATE param);
*
*----------------------------------------------------------------------------
* DEFINED STREAMING ENGINE MANAGEMENT MACROS:
*----------------------------------------------------------------------------
* __SE0_OPEN(const void *addr, __STRM_TEMPLATE param)
* __SE1_OPEN(const void *addr, __STRM_TEMPLATE param)
*
* __SE0_CLOSE()
* __SE1_CLOSE()
*
* __SE0(type)      - READ ONLY
* __SE1(type)      - READ ONLY
*
* __SE0ADV(type)   - READ AND ADVANCE
* __SE1ADV(type)   - READ AND ADVANCE
*
*----------------------------------------------------------------------------
* DEFINED STREAM ADDRESS GENERATOR MANAGEMENT MACROS:
*----------------------------------------------------------------------------
* __SA0_OPEN(__STRM_TEMPLATE param)
* __SA1_OPEN(__STRM_TEMPLATE param)
* __SA2_OPEN(__STRM_TEMPLATE param)
* __SA3_OPEN(__STRM_TEMPLATE param)
*
* __SA0_CLOSE()
* __SA1_CLOSE()
* __SA2_CLOSE()
* __SA3_CLOSE()
*
* __SA0(type, baseptr)    - READ ONLY
* __SA1(type, baseptr)    - READ ONLY
* __SA2(type, baseptr)    - READ ONLY
* __SA3(type, baseptr)    - READ ONLY
*
* __SA0ADV(type, baseptr) - READ AND ADVANCE
* __SA1ADV(type, baseptr) - READ AND ADVANCE
* __SA2ADV(type, baseptr) - READ AND ADVANCE
* __SA3ADV(type, baseptr) - READ AND ADVANCE
*
* __SA0_BOOL(type)        - EXTRACT AND SCALE SA VECTOR PREDICATE AS BOOL VECTOR
* __SA1_BOOL(type)        - EXTRACT AND SCALE SA VECTOR PREDICATE AS BOOL VECTOR
* __SA2_BOOL(type)        - EXTRACT AND SCALE SA VECTOR PREDICATE AS BOOL VECTOR
* __SA3_BOOL(type)        - EXTRACT AND SCALE SA VECTOR PREDICATE AS BOOL VECTOR
*
* __SA0_VPRED(type)       - EXTRACT AND SCALE SA VECTOR PREDICATE
* __SA1_VPRED(type)       - EXTRACT AND SCALE SA VECTOR PREDICATE
* __SA2_VPRED(type)       - EXTRACT AND SCALE SA VECTOR PREDICATE
* __SA3_VPRED(type)       - EXTRACT AND SCALE SA VECTOR PREDICATE
*----------------------------------------------------------------------------*/

typedef __uint16     __STRM_TEMPLATE;
typedef __uint16_ptr __STRM_TEMPLATE_ptr;

/*-----------------------------------------------------------------------------
* strmtemplate_ptr(addr): __STRM_TEMPLATE pointer conversion macro
*
* This macro is used to convert between a scalar pointer to an array in memory
* and a __STRM_TEMPLATE_ptr using the host emulation package and is defined
* here for compatiblity when porting programs to the C7000 compiler.
*----------------------------------------------------------------------------*/
#define strmtemplate_ptr(addr) ((__STRM_TEMPLATE_ptr)(addr))

/*----------------------------------------------------------------------------*/
/*                                                                            */
/* NOTE!!!                                                                    */
/* NOTE!!!                                                                    */
/* NOTE!!!                                                                    */
/* NOTE!!!                                                                    */
/* NOTE!!!                                                                    */
/*                                                                            */
/* DO NOT USE THIS OLD AND DEPRECATED API FOR THE STREAMING ENGINE AND        */
/* STREAMING ADDRESS GENERATOR FEATURES. THIS API HAS BEEN DEPRECATED AND     */
/* WILL BE REMOVED IN A FUTURE VERSION OF THE COMPILER TOOLS. THIS            */
/* DEPRECATED API IS ONLY PROVIDED FOR BACKWARDS COMPATIBILITY WITH OLDER     */
/* SOURCE CODE. Use the API in c7x_strm.h instead.                            */
/*                                                                            */
/* NOTE!!!                                                                    */
/* NOTE!!!                                                                    */
/* NOTE!!!                                                                    */
/* NOTE!!!                                                                    */
/* NOTE!!!                                                                    */
/*                                                                            */
/* DEMONSTRATION FOR SETUP AND USAGE OF A STREAMING ENGINE STREAM WITHOUT     */
/* CIRCULAR ADDRESSING:                                                       */
/*                                                                            */
/* #include <c7x.h>                                                           */
/* #include <stddef.h>                                                        */
/* uint8 se_func(uint32_t *startaddr)                                         */
/* {                                                                          */
/*     int I0;                                                                */
/*     uint8 Vresult;                                                         */
/*     __SE_FLAGS      flags;        // SE FLAGS STRUCTURE                    */
/*     __STRM_TEMPLATE params = (0); // SE PARAMETER VECTOR                   */
/*                                                                            */
/*     flags           = __SE_FLAGS_default();                                */
/*                                                                            */
/*     flags.DIMFMT    = __SE_DIMFMT_4D;                                      */
/*     flags.ELETYPE   = __SE_ELETYPE_32BIT;                                  */
/*     flags.VECLEN    = __SE_VECLEN_4ELEMS; // 4 ELEMENTS                    */
/*                                                                            */
/*     // SETUP TEMPLATE VECTOR BASED ON SETTINGS AND OPEN THE STREAM         */
/*     // BASED ON ITERATION COUNTERS AND DIMENSIONS (IN TERMS OF # OF ELEMS) */
/*     params          = __set_ICNT0(params, 4);                              */
/*     params          = __set_ICNT1_DIM1(params, 2,   4);                    */
/*     params          = __set_ICNT2_DIM2(params, 2,   8);                    */
/*     params          = __set_ICNT3_DIM3(params, 4, -16);                    */
/*     params          = __set_SE_FLAGS(params, &flags, NULL);                */
/*                                                                            */
/*     // DECDIM1 WIDTH (0 by default)                                        */
/*     params          = __set_DECDIM1_WIDTH(params, 0);                      */
/*                                                                            */
/*     // DECDIM2 WIDTH (0 by default)                                        */
/*     params          = __set_DECDIM2_WIDTH(params, 0);                      */
/*                                                                            */
/*     // LEZR COUNT (0 by default)                                           */
/*     params          = __set_LEZR_CNT(params, 0);                           */
/*                                                                            */
/*     __SE1_OPEN((const void*)startaddr, params);                            */
/*                                                                            */
/*     // READ THE STREAM AND ADVANCE THE COUNTERS                            */
/*     for (I0 = 0; I0 < 8; I0++)                                             */
/*     {                                                                      */
/*         uint8 Vout;                                                        */
/*         Vout.lo = __SE1ADV(uint4);                                         */
/*         Vout.hi = __SE1ADV(uint4);                                         */
/*                                                                            */
/*         Vresult += Vout;                                                   */
/*     }                                                                      */
/*                                                                            */
/*     // CLOSE THE STREAM                                                    */
/*     __SE1_CLOSE();                                                         */
/*                                                                            */
/*     return Vresult;                                                        */
/* }                                                                          */
/*                                                                            */
/* DEMONSTRATION FOR SETUP AND USAGE OF A STREAMING ENGINE STREAM WITH        */
/* CIRCULAR ADDRESSING:                                                       */
/*                                                                            */
/* #include <c7x.h>                                                           */
/* #include <stddef.h>                                                        */
/* uint16 se_circ_func(uint32_t *startaddr)                                   */
/* {                                                                          */
/*     int I0;                                                                */
/*     uint16 Vresult;                                                        */
/*     __SE_FLAGS       flags;  // SE FLAGS STRUCTURE                         */
/*     __SE_CIRC_FLAGS  cflags; // SE CIRCULAR ADDRESSING FLAGS STRUCTURE     */
/*     __STRM_TEMPLATE  params = (0);   // SE PARAMETER VECTOR                */
/*                                                                            */
/*     flags           = __SE_FLAGS_default();                                */
/*                                                                            */
/*     flags.DIMFMT    = __SE_DIMFMT_3D;                                      */
/*     flags.ELETYPE   = __SE_ELETYPE_32BIT;                                  */
/*     flags.VECLEN    = __SE_VECLEN_16ELEMS; // 16 ELEMENTS                  */
/*                                                                            */
/*     cflags          = __SE_CIRC_FLAGS_default();                           */
/*                                                                            */
/*     // CIRCULAR ADDRESSING BLOCK CONFIGURATION (SEE SPEC FOR DETAILS)      */
/*     cflags.CBK0 = 0;                    // 512BYTE ENCODING                */
/*                                                                            */
/*     // CIRCULAR ADDRESSING ADDRESS MODE CONFIGURATION                      */
/*     cflags.AM0 = __SE_AM_CIRC_CBK0;                                        */
/*     cflags.AM1 = __SE_AM_CIRC_CBK0;                                        */
/*     cflags.AM2 = __SE_AM_CIRC_CBK0;                                        */
/*                                                                            */
/*     // SETUP TEMPLATE VECTOR BASED ON SETTINGS AND OPEN THE STREAM         */
/*     // BASED ON ITERATION COUNTERS AND DIMENSIONS (IN TERMS OF # OF ELEMS) */
/*     params          = __set_ICNT0(params, 16);                             */
/*     params          = __set_ICNT1_DIM1(params, 16, 16);                    */
/*     params          = __set_ICNT2_DIM2(params, 1,   0);                    */
/*     params          = __set_SE_FLAGS(params, &flags, &cflags);             */
/*                                                                            */
/*     // DECDIM1 WIDTH (0 by default)                                        */
/*     params          = __set_DECDIM1_WIDTH(params, 0);                      */
/*                                                                            */
/*     // DECDIM2 WIDTH (0 by default)                                        */
/*     params          = __set_DECDIM2_WIDTH(params, 0);                      */
/*                                                                            */
/*     // LEZR COUNT (0 by default)                                           */
/*     params          = __set_LEZR_CNT(params, 0);                           */
/*                                                                            */
/*     __SE1_OPEN((const void*)startaddr, params);                            */
/*                                                                            */
/*     // READ THE STREAM AND ADVANCE THE COUNTERS                            */
/*     for (I0 = 0; I0 < 16; I0++)                                            */
/*     {                                                                      */
/*         uint16 Vout = __SE1ADV(uint16);                                    */
/*         Vresult += Vout;                                                   */
/*     }                                                                      */
/*                                                                            */
/*     // CLOSE THE STREAM                                                    */
/*     __SE1_CLOSE();                                                         */
/*                                                                            */
/*     return Vresult;                                                        */
/* }                                                                          */
/*                                                                            */
/* DEMONSTRATION FOR SETUP AND USAGE OF A STREAM ADDRESS GENERATOR:           */
/*                                                                            */
/* #include <c7x.h>                                                           */
/* #include <stddef.h>                                                        */
/* uint8 sa_func(uint32_t *startaddr)                                         */
/* {                                                                          */
/*     int I0;                                                                */
/*     uint8 Vresult;                                                         */
/*     __SA_FLAGS      flags;        // SA FLAGS STRUCTURE                    */
/*     __STRM_TEMPLATE params = (0); // SA PARAMETER VECTOR                   */
/*                                                                            */
/*     flags         = __SA_FLAGS_default();                                  */
/*                                                                            */
/*     flags.DIMFMT  = __SA_DIMFMT_4D;                                        */
/*     flags.VECLEN  = __SA_VECLEN_4ELEMS; // 4 ELEMENTS                      */
/*                                                                            */
/*     // SETUP TEMPLATE VECTOR BASED ON SETTINGS AND OPEN THE STREAM         */
/*     // BASED ON ITERATION COUNTERS AND DIMENSIONS (IN TERMS OF # OF ELEMS) */
/*     params       = __set_ICNT0(params, 4);                                 */
/*     params       = __set_ICNT1_DIM1(params, 2,   4);                       */
/*     params       = __set_ICNT2_DIM2(params, 2,   8);                       */
/*     params       = __set_ICNT3_DIM3(params, 4, -16);                       */
/*     params       = __set_SA_FLAGS(params, &flags);                         */
/*                                                                            */
/*     // DECDIM1 WIDTH (0 by default)                                        */
/*     params       = __set_DECDIM1_WIDTH(params, 0);                         */
/*                                                                            */
/*     // DECDIM2 WIDTH (0 by default)                                        */
/*     params       = __set_DECDIM2_WIDTH(params, 0);                         */
/*                                                                            */
/*     __SA1_OPEN(params);                                                    */
/*                                                                            */
/*     // READ THE STREAM AND ADVANCE THE COUNTERS                            */
/*     for (I0 = 0; I0 < 8; I0++)                                             */
/*     {                                                                      */
/*         uint8 Vout;                                                        */
/*         Vout.lo = __SA1ADV(uint4, startaddr);                              */
/*         Vout.hi = __SA1ADV(uint4, startaddr);                              */
/*                                                                            */
/*         Vresult += Vout;                                                   */
/*     }                                                                      */
/*                                                                            */
/*     // CLOSE THE STREAM                                                    */
/*     __SA1_CLOSE();                                                         */
/*                                                                            */
/*     return Vresult;                                                        */
/* }                                                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/


/*****************************************************************************/
/* STREAMING ENGINE COMMON CONTROLS                                          */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* Implementation details.  Do not use directly.                             */
/*---------------------------------------------------------------------------*/
void*    __BIFM   __se_mem       (const void*);
void     __BIFM   __se_open      (__RD void*, __CST(0, 1) __uint, __STRM_TEMPLATE);
void     __BIFM   __se_close     (__CST(0, 1) __uint);
void     __BIFM   __se_break     (__CST(0, 5) __uint, __CST(0, 1) __uint);
__uint16 __BIFM   __se_save      (__CST(0, 3) __uint, __CST(0, 1) __uint);
void     __BIFM   __se_restore   (__CST(0, 3) __uint, __CST(0, 1)__uint, __uint16);

/*---------------------------------------------------------------------------*/
/* void __SEn_OPEN(const void *addr, __SE_TEMPLATE)                          */
/*   Opens streaming engine n at address addr.                               */
/*---------------------------------------------------------------------------*/
#define __SE0_OPEN(addr,tmpl) __se_open   (__se_mem(addr), 0U, tmpl)
#define __SE1_OPEN(addr,tmpl) __se_open   (__se_mem(addr), 1U, tmpl)

/*---------------------------------------------------------------------------*/
/* void __SEn_CLOSE()                                                        */
/*   Closes streaming engine n.                                              */
/*---------------------------------------------------------------------------*/
#define __SE0_CLOSE()         __se_close(0U)
#define __SE1_CLOSE()         __se_close(1U)

/*---------------------------------------------------------------------------*/
/* type __SEn(type)                                                          */
/*   Retrieves a type from streaming engine n where type may be exactly:     */
/*     char, char2, char4, char8, char16, char32, char64                     */
/*     uchar, uchar2, uchar4, uchar8, uchar16, uchar32, uchar64              */
/*                                                                           */
/*     short, short2, short4, short8, short16, short32                       */
/*     ushort, ushort2, ushort4, ushort8, ushort16, ushort32                 */
/*     cchar, cchar2, cchar4, cchar8, cchar16, cchar32                       */
/*                                                                           */
/*     int, int2, int4, int8, int16                                          */
/*     uint, uint2, uint4, uint8, uint16                                     */
/*     float, float2, float4, float8, float16                                */
/*     cshort, cshort2, cshort4, cshort8, cshort16                           */
/*                                                                           */
/*     long, long2, long4, long8                                             */
/*     ulong, ulong2, ulong4, ulong8                                         */
/*     double, double2, double4, double8                                     */
/*     cint, cint2, cint4, cint8                                             */
/*     cfloat, cfloat2, cfloat4, cfloat8                                     */
/*---------------------------------------------------------------------------*/
#define __SE0(type)           __se_ac_##type(0U, 0U)
#define __SE1(type)           __se_ac_##type(1U, 0U)

/*---------------------------------------------------------------------------*/
/* type __SEnADV(type)                                                       */
/*   Retrieves a type from streaming engine n, then advances that engine.    */
/*   Argument restrictions and return types are the same as __SEn(type).     */
/*---------------------------------------------------------------------------*/
#define __SE0ADV(type)        __se_ac_##type(0U, 1U)
#define __SE1ADV(type)        __se_ac_##type(1U, 1U)

/*---------------------------------------------------------------------------*/
/* void __SEn_BREAK(__uint level)                                            */
/*   Causes streaming engine n to skip all remaining elements for the        */
/*   specified loop level.  level must be a constant.                        */
/*---------------------------------------------------------------------------*/
#define __SE0_BREAK(level)      __se_break(level, 0U)
#define __SE1_BREAK(level)      __se_break(level, 1U)

/*---------------------------------------------------------------------------*/
/* __uint16 __SEn_SAVE(__uint segment)                                       */
/*   Saves the specified segment from streaming engine n.  segment must be a */
/*   constant.                                                               */
/*---------------------------------------------------------------------------*/
#define __SE0_SAVE(segment) __se_save(segment, 0U)
#define __SE1_SAVE(segment) __se_save(segment, 1U)

/*---------------------------------------------------------------------------*/
/* void __SEn_RESTORE(__uint segment, __uint16 state)                        */
/*   Restores state into the specified segment of streaming engine n.        */
/*---------------------------------------------------------------------------*/
#define __SE0_RESTORE(segment, state) __se_restore(segment, 0U, state)
#define __SE1_RESTORE(segment, state) __se_restore(segment, 1U, state)

/*----------------------------------------------------------------------------*/
/* Some instructions can only take streaming engine operands (VFIR, VMATMPY). */
/* The intrinsics for these instructions take an immediate representing which */
/* streaming engine, as well as the advance option.                           */
/*----------------------------------------------------------------------------*/
/* Use the following for __SE_REG operands.                                   */
/*----------------------------------------------------------------------------*/
typedef enum
{
    __SE_REG_0     = 0,
    __SE_REG_0_ADV = 1,
    __SE_REG_1     = 2,
    __SE_REG_1_ADV = 3
} __SE_REG;

/*----------------------------------------------------------------------------*/
/* Use the following for SE_REG_PAIR operands.                                */
/*----------------------------------------------------------------------------*/
typedef enum
{
    __SE_REG_PAIR_0     = 0,
    __SE_REG_PAIR_0_ADV = 1
} __SE_REG_PAIR;

/*----------------------------------------------------------------------------*/
/* Streaming Engine Shortcut-Open Arguments.                                  */
/* The type of shortcut argument can be used in place of a vector template to */
/* open a stream using __SE0_OPEN_SHORTCUT() or __SE1_OPEN_SHORTCUT().        */
/*----------------------------------------------------------------------------*/
typedef enum
{
    __STROPENB   = 0x0,
    __STROPENBH  = 0x1,
    __STROPENBUH = 0x2,
    __STROPENH   = 0x3,
    __STROPENHW  = 0x4,
    __STROPENHUW = 0x5,
    __STROPENW   = 0x6,
    __STROPENWD  = 0x7,
    __STROPENWUD = 0x8,
    __STROPEND   = 0x9
} __SE_SHORTCUT;

/*----------------------------------------------------------------------------*/
/* Implementation detail.  Do not use directly.                               */
/*----------------------------------------------------------------------------*/
void    __BIFM   __se_open_sc(__RD const void*, __CST(0, 1) __uint, __CST(0,9) __SE_SHORTCUT);

/*----------------------------------------------------------------------------*/
/* void __SEn_OPEN_SHORTCUT(addr, sc)                                         */
/*   Open streaming engine n at addr using configuration sc.                  */
/*----------------------------------------------------------------------------*/
#define __SE0_OPEN_SHORTCUT(addr, sc) __se_open_sc(__se_mem(addr), 0U, sc)
#define __SE1_OPEN_SHORTCUT(addr, sc) __se_open_sc(__se_mem(addr), 1U, sc)

/*----------------------------------------------------------------------------*/
/* Block Cache Maintenance Instruction Arguments                              */
/* These arguments are used with __se_cache_op() to operate on a contiguous   */
/* block of addresses.                                                        */
/*----------------------------------------------------------------------------*/
typedef enum
{
    /* Sharable */
    __DCCIC     = 0x14, /* DataCache Clean/Invalidate to Point of Coherence   */
    __DCCMIC    = 0x15  /* DataCache Invalidate to Point of Coherence         */
} __BLK_OPTYPE;

/*----------------------------------------------------------------------------*/
/* __se_cache_op(const void*, __BLK_OPTYPE, __uint bytes)                     */
/*   Direct access to BLKCMO instruction.                                     */
/*----------------------------------------------------------------------------*/
void    __BIFM   __se_cache_op     (const void*, __CST(20,21) __BLK_OPTYPE, __uint);

/*----------------------------------------------------------------------------*/
/* Block Cache Preload Instruction Arguments                                  */
/* These arguments are used with __se_cache_preload() to operate on a         */
/* contiguous block of addresses.                                             */
/*----------------------------------------------------------------------------*/
typedef enum
{
    __L2R = 0x0, /* Preload to L2 for reading */
    __L2W = 0x1, /* Preload to L2 for writing */
    __L3R = 0x2, /* Preload to L3 for reading */
    __L3W = 0x3  /* Preload to L3 for writing */
} __BLK_PLDTYPE;

/*----------------------------------------------------------------------------*/
/* __se_cache_preload(const void*, __BLK_PLDTYPE, __uint bytes)               */
/*   Direct access to BLKPLD instruction.                                     */
/*----------------------------------------------------------------------------*/
void    __BIFM   __se_cache_preload(const void*, __BLK_PLDTYPE, __uint);

/*----------------------------------------------------------------------------*/
/* STREAMING ENGINE AUXILIARY API                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Template format selection for Streaming Engine                             */
/*----------------------------------------------------------------------------*/
#define __SE_DIMFMT_1D  (0)
#define __SE_DIMFMT_2D  (1)
#define __SE_DIMFMT_3D  (2)
#define __SE_DIMFMT_4D  (3)
#define __SE_DIMFMT_5D  (4)
#define __SE_DIMFMT_6D  (5)

/*----------------------------------------------------------------------------*/
/* Streaming Engine element type options.                                     */
/* Use the below macros as needed to indicate the element type of data read   */
/* via streaming engine.                                                      */
/*----------------------------------------------------------------------------*/
#define __SE_ELETYPE_8BIT                (0)
#define __SE_ELETYPE_16BIT               (1)
#define __SE_ELETYPE_32BIT               (2)
#define __SE_ELETYPE_64BIT               (3)

#define __SE_ELETYPE_8BIT_CMPLX_NOSWAP   (8)
#define __SE_ELETYPE_16BIT_CMPLX_NOSWAP  (9)
#define __SE_ELETYPE_32BIT_CMPLX_NOSWAP (10)
#define __SE_ELETYPE_64BIT_CMPLX_NOSWAP (11)
#define __SE_ELETYPE_8BIT_CMPLX_SWAP    (12)
#define __SE_ELETYPE_16BIT_CMPLX_SWAP   (13)
#define __SE_ELETYPE_32BIT_CMPLX_SWAP   (14)
#define __SE_ELETYPE_64BIT_CMPLX_SWAP   (15)

/*----------------------------------------------------------------------------*/
/* Streaming Engine Transpose options.                                        */
/* Use the below macros as needed to indicate the transpose settings.         */
/* Transpose "GRANULES" are of below sizes only.                              */
/*----------------------------------------------------------------------------*/
#define __SE_TRANSPOSE_OFF    (0)
#define __SE_TRANSPOSE_8BIT   (1)
#define __SE_TRANSPOSE_16BIT  (2)
#define __SE_TRANSPOSE_32BIT  (3)
#define __SE_TRANSPOSE_64BIT  (4)
#define __SE_TRANSPOSE_128BIT (5)
#define __SE_TRANSPOSE_256BIT (6)

/*----------------------------------------------------------------------------*/
/* Streaming Engine promote options.                                          */
/* Single power of 2 promotes are possible using below options.               */
/* Additionally the promotes can be sign or zero extended.                    */
/* Ex. If ELETYPE is 8bit the promoting it would result in 16 bit data.       */
/*----------------------------------------------------------------------------*/
#define __SE_PROMOTE_OFF          (0)
#define __SE_PROMOTE_2X_ZEROEXT   (1)
#define __SE_PROMOTE_4X_ZEROEXT   (2)
#define __SE_PROMOTE_8X_ZEROEXT   (3)
#define __SE_PROMOTE_2X_SIGNEXT   (5)
#define __SE_PROMOTE_4X_SIGNEXT   (6)
#define __SE_PROMOTE_8X_SIGNEXT   (7)

/*----------------------------------------------------------------------------*/
/* Streaming Engine group duplication.                                        */
/* Depending on the vector lengths, enabling group duplication will fill up   */
/* 512bit holding registers with multiple copies.                             */
/* Ex. For ELETYPE_8BIT and VECLEN_4ELEMS with group duplication enabled,     */
/* The streaming engine duplicates the 4 bytes in LSB 16 times to fill up the */
/* 512 bit double vector holding register.                                    */
/*----------------------------------------------------------------------------*/
#define __SE_GRPDUP_OFF (0) /* default */
#define __SE_GRPDUP_ON  (1)

/*----------------------------------------------------------------------------*/
/* Streaming Engine vector lengths.                                           */
/* Use the below macros to indicate the vector lengths in powers of two.      */
/* The vector lengths should be in multiples of ELETYPE.                      */
/* Ex. If the vector length is VECLEN_4ELEMS and ELETYPE_16BIT then the       */
/*     data in the holding registers will contain 4 16 bit values for each    */
/*     SE advance. The rest of the SB0, SB1 register will be zeroed out.      */
/*----------------------------------------------------------------------------*/
#define __SE_VECLEN_1ELEM        (0) /* default */
#define __SE_VECLEN_2ELEMS       (1)
#define __SE_VECLEN_4ELEMS       (2)
#define __SE_VECLEN_8ELEMS       (3)
#define __SE_VECLEN_16ELEMS      (4)
#define __SE_VECLEN_32ELEMS      (5)
#define __SE_VECLEN_64ELEMS      (6)

/*----------------------------------------------------------------------------*/
/* Streaming Engine element duplication.                                      */
/* Use the below macros to duplicate the vector elements in powers of two,    */
/* 2x, 4x, 8x, 16x, 32x, 64x (subject to ELETYPE)                             */
/* Ex. Using ELE_DUP_32X for a ELETYPE_16BIT duplicates 16bit elements        */
/*     32 times in SB0/SB1 double vector.                                     */
/*----------------------------------------------------------------------------*/
#define __SE_ELEDUP_OFF        (0) /* default */
#define __SE_ELEDUP_2X         (1)
#define __SE_ELEDUP_4X         (2)
#define __SE_ELEDUP_8X         (3)
#define __SE_ELEDUP_16X        (4)
#define __SE_ELEDUP_32X        (5)
#define __SE_ELEDUP_64X        (6)

/*----------------------------------------------------------------------------*/
/* Streaming Engine decimation flags.                                         */
/* Use the below macros to indicate if the SE should decimate (only keep      */
/* every nth element.) Note: Enabling decimation requires element promotion   */
/* to also be enabled.                                                        */
/*----------------------------------------------------------------------------*/
#define __SE_DECIM_OFF (0) /* default         */
#define __SE_DECIM_2   (1) /* 2:1 decimation */
#define __SE_DECIM_4   (2) /* 4:1 decimation */

/*----------------------------------------------------------------------------*/
/* Streaming Engine increment/decrement directions.                           */
/* Use the below macros as needed to indicate the direction of transfer.      */
/* Setting to _INC mode increments the resulting address.                     */
/* Setting to _DEC mode decrements the resulting address.                     */
/*----------------------------------------------------------------------------*/
#define __SE_DIR_INC (0) /* default */
#define __SE_DIR_DEC (1)

/*----------------------------------------------------------------------------*/
/* Streaming Engine Addressing Mode selection options.                        */
/* Choose either linear addressing or use CBK0 or CBK0+CBK1+1                 */
/*----------------------------------------------------------------------------*/
#define __SE_AM_LINEAR         (0)
#define __SE_AM_CIRC_CBK0      (1) /* Circ addressing with block size 0 */
#define __SE_AM_CIRC_CBK1      (2) /* Circ addressing with block size 1 */

/*----------------------------------------------------------------------------*/
/* Streaming Engine Data Strip Mining Decrement Dimension for innermost ICNT0 */
/* In this mode, the current I0 count is NOT reloaded with ICNT0 when each    */
/* dimension expires. Rather, when the selected DECDIM dimension is entered,  */
/* the current I0 count is decremented by the value of VECLEN when in Linear  */
/* Stream mode, or decremented by the GRANULE value when in Transpose Mode.   */
/* The I0 count is only reloaded when the selected DECDIM dimension expires,  */
/* or a dimension higher above it expires.                                    */
/*----------------------------------------------------------------------------*/
#define __SE_DECDIM_DIM0 (0) /* Normal Operating Mode - default */
#define __SE_DECDIM_DIM1 (1) /* Strip Mining on DIM1 (DECDIM_WIDTH decrements)*/
#define __SE_DECDIM_DIM2 (2) /* Strip Mining on DIM2 (DECDIM_WIDTH decrements)*/
#define __SE_DECDIM_DIM3 (3) /* Strip Mining on DIM3 (DECDIM_WIDTH decrements)*/
#define __SE_DECDIM_DIM4 (4) /* Strip Mining on DIM4 (DECDIM_WIDTH decrements)*/
#define __SE_DECDIM_DIM5 (5) /* Strip Mining on DIM5 (DECDIM_WIDTH decrements)*/

/*----------------------------------------------------------------------------*/
/* Streaming Engine Secondary Data Strip Mining Decrement Dimension           */
/*----------------------------------------------------------------------------*/
#define __SE_DECDIMSD_DIM0 (0) /* Normal Operating Mode - default */
#define __SE_DECDIMSD_DIM1 (1) /* SD Strip Mining on DIM1 (DECDIM_WIDTH decs) */
#define __SE_DECDIMSD_DIM2 (2) /* SD Strip Mining on DIM2 (DECDIM_WIDTH decs) */
#define __SE_DECDIMSD_DIM3 (3) /* SD Strip Mining on DIM3 (DECDIM_WIDTH decs) */

/*----------------------------------------------------------------------------*/
/* Selected Loop Dimension Count End, and Start Sending Zero-Padded Vectors   */
/* to CPU.  The number of zero-padded vectors sent to CPU is defined by the   */
/* LEZR_CNT field in the template.  Supported in Linear Stream Mode only.     */
/*----------------------------------------------------------------------------*/
#define __SE_LEZR_OFF   (0) /* Normal Operating Mode - default */
#define __SE_LEZR_ICNT0 (1) /* Send zero-padded vectors at end of ICNT0 */
#define __SE_LEZR_ICNT1 (2) /* Send zero-padded vectors at end of ICNT1 */
#define __SE_LEZR_ICNT2 (3) /* Send zero-padded vectors at end of ICNT2 */
#define __SE_LEZR_ICNT3 (4) /* Send zero-padded vectors at end of ICNT3 */
#define __SE_LEZR_ICNT4 (5) /* Send zero-padded vectors at end of ICNT4 */
#define __SE_LEZR_ICNT5 (6) /* Send zero-padded vectors at end of ICNT5 */

/*----------------------------------------------------------------------------*/
/* Streaming Engine param size is 64 bytes. All the above options             */
/* including iteration counts(ICNT) and dimensions(DIM) are packed in a       */
/* 512bit vector. Use this macro to derrive offsets while writing to L1D SRAM */
/*----------------------------------------------------------------------------*/
#define SE_PARAM_SIZE (64)


/*----------------------------------------------------------------------------*/
/* struct : __SE_FLAGS                                                        */
/* Desc   : Structure to hold the streaming engine transfer options,          */
/*          iteration counts and transfer dimensions.                         */
/*                                                                            */
/* elements:   uint8_t ELETYPE                                                */
/*              - Predefined macro values for indicating the element type.    */
/*             uint8_t TRANSPOSE                                              */
/*              - Predifined macro values for indicating transpose option.    */
/*             uint8_t PROMOTE                                                */
/*              - Predifined macro values for indicating promote option.      */
/*             uint8_t GRPDUP                                                 */
/*              - Predifined macro values for indicating group duplication.   */
/*             uint8_t VECLEN                                                 */
/*              - Predifined macro values for indicating vector length.       */
/*             uint8_t ELEDUP                                                 */
/*              - Predifined macro values for indicating element duplication. */
/*             uint8_t DECIM                                                  */
/*              - Predifined macro values for indicating vector decimation.   */
/*             uint8_t DIR                                                    */
/*              - Predifined macro values for indicating the direction of     */
/*                transfer.                                                   */
/*             uint8_t DIMFMT                                                 */
/*              - Predefined macro values for indicating dimensions in nest.  */
/*             uint8_t DECDIM1                                                */
/*              - Predefined macro values for indicating data strip mining    */
/*                dimension for DECDIM1_WIDTH.                                */
/*             uint8_t DECDIM1SD                                              */
/*              - Predefined macro values for indicating secondary data strip */
/*                mining dimension for DECDIM1_WIDTH.                         */
/*             uint8_t DECDIM2                                                */
/*              - Predefined macro values for indicating data strip mining    */
/*                dimension for DECDIM2_WIDTH.                                */
/*             uint8_t DECDIM2SD                                              */
/*              - Predefined macro values for indicating secondary data strip */
/*                mining dimension for DECDIM2_WIDTH.                         */
/*             uint8_t LEZR                                                   */
/*              - Loop Dimension Count End Zero Padding for LEZR_CNT.         */
/*                                                                            */
/*----------------------------------------------------------------------------*/
typedef struct __SE_FLAGS_t
{
   uint8_t ELETYPE;
   uint8_t TRANSPOSE;
   uint8_t PROMOTE;
   uint8_t GRPDUP;
   uint8_t VECLEN;
   uint8_t ELEDUP;
   uint8_t DECIM;
   uint8_t DIR;
   uint8_t DIMFMT;
   uint8_t DECDIM1;
   uint8_t DECDIM1SD;
   uint8_t DECDIM2;
   uint8_t DECDIM2SD;
   uint8_t LEZR;

} __SE_FLAGS;

/*----------------------------------------------------------------------------*/
/* struct : __SE_CIRC_FLAGS                                                   */
/* Desc   : Structure to hold the streaming engine circular address options.  */
/*                                                                            */
/* elements:   uint8_t CBK0                                                   */
/*              - Circular addressing block size for block 0.  The value      */
/*                corresponds to encoded block size specified by Table 1-17   */
/*                in the SE specification.                                    */
/*             uint8_t CBK1                                                   */
/*              - CBK1 combines with CBK0 to determine the circular block     */
/*                size for block 1 according to: CBK0 + CBK1 + 1.             */
/*             uint8_t AM{0-5}                                                */
/*              - Addressing mode selection for dimensions 0 through 5        */
/*                                                                            */
/*----------------------------------------------------------------------------*/
typedef struct __SE_CIRC_FLAGS_t
{
   uint8_t CBK0;
   uint8_t CBK1;
   uint8_t AM0;
   uint8_t AM1;
   uint8_t AM2;
   uint8_t AM3;
   uint8_t AM4;
   uint8_t AM5;

} __SE_CIRC_FLAGS;


/*****************************************************************************/
/* STREAMING ADDRESS GENERATOR COMMON CONTROLS                               */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* Implementation details.  Do not use directly.                             */
/*---------------------------------------------------------------------------*/
void     __BIFM     __sa_open    (__CST(0, 3) __uint, __STRM_TEMPLATE);
void     __BIFM     __sa_close   (__CST(0, 3) __uint);
void     __BIFM     __sa_break   (__CST(0, 5) __uint, __CST(0, 3) __uint);
void     __BIFM     __sa_set_cr  (__CST(0, 3) __uint, __uint16);
__uint16 __BIFM     __sa_get_cr  (__CST(0, 3) __uint);
__uint16 __BIFM     __sa_get_cntr(__CST(0, 3) __uint);
#if __C7120__
#define __sa_get_cntr0(x) __sa_get_cntr(x)
__uint16 __BIFM     __sa_get_cntr1(__CST(0, 3) __uint);
#endif
__vpred  __BIFM     __sa_vpred   (__CST(0, 3) __uint, __CST(1, 8) __uint);
void*    __BIFM __sa(__CST(0,3) __uint, __CST(1,32768) __uint, const void *);
void*    __BIFM __sa_adv(__CST(0,3) __uint, __CST(1,32768) __uint, const void *);

/*---------------------------------------------------------------------------*/
/* void __SAn_OPEN(__SA_TEMPLATE)                                            */
/*   Opens streaming address generator n.                                    */
/*---------------------------------------------------------------------------*/
#define __SA0_OPEN(tmpl)        __sa_open(0U, tmpl)
#define __SA1_OPEN(tmpl)        __sa_open(1U, tmpl)
#define __SA2_OPEN(tmpl)        __sa_open(2U, tmpl)
#define __SA3_OPEN(tmpl)        __sa_open(3U, tmpl)

/*---------------------------------------------------------------------------*/
/* void __SAn_CLOSE()                                                        */
/*   Closes streaming address generator n.                                   */
/*---------------------------------------------------------------------------*/
#define __SA0_CLOSE()           __sa_close(0U)
#define __SA1_CLOSE()           __sa_close(1U)
#define __SA2_CLOSE()           __sa_close(2U)
#define __SA3_CLOSE()           __sa_close(3U)

/*---------------------------------------------------------------------------*/
/* type *__SAn(type, baseptr)                                                */
/*   Retrieves the current address from streaming address generator n.  The  */
/*   address will be based off of baseptr and point to type, where type may  */
/*   be any scalar or vector type that:                                      */
/*     1) Has a total size no larger than 512 bits.                          */
/*     2) Has an element size no larger than 64 bits.  (A complex vector     */
/*        considers the complex type to be the element type.)                */
/*   Typedef'd types and qualified types are allowed.  For example, the      */
/*   following are all legal:                                                */
/*     - __SA0(int2, baseptr) -> returns int2*                               */
/*     - __SA0(__int2, baseptr) -> returns __int2*                           */
/*     - __SA0(const __int2, baseptr) -> returns const __int2*               */
/*---------------------------------------------------------------------------*/
#define __SA0(type, baseptr)    (type*)__sa(0U, sizeof(type)/__numelemof(type), baseptr)
#define __SA1(type, baseptr)    (type*)__sa(1U, sizeof(type)/__numelemof(type), baseptr)
#define __SA2(type, baseptr)    (type*)__sa(2U, sizeof(type)/__numelemof(type), baseptr)
#define __SA3(type, baseptr)    (type*)__sa(3U, sizeof(type)/__numelemof(type), baseptr)

/*---------------------------------------------------------------------------*/
/* type *__SAnADV(type, baseptr)                                             */
/*   Retrieves the current address from streaming address generator n, then  */
/*   advances that generator.  Argument restrictions and return types are    */
/*   the same as __SAn(type, baseptr).                                       */
/*---------------------------------------------------------------------------*/
#define __SA0ADV(type, baseptr) (type*)__sa_adv(0U, sizeof(type)/__numelemof(type), baseptr)
#define __SA1ADV(type, baseptr) (type*)__sa_adv(1U, sizeof(type)/__numelemof(type), baseptr)
#define __SA2ADV(type, baseptr) (type*)__sa_adv(2U, sizeof(type)/__numelemof(type), baseptr)
#define __SA3ADV(type, baseptr) (type*)__sa_adv(3U, sizeof(type)/__numelemof(type), baseptr)

/*---------------------------------------------------------------------------*/
/* void __SAn_BREAK(level)                                                   */
/*   Causes streaming address generator n to skip all remaining elements for */
/*   the specified loop level.  level must be a constant.                    */
/*---------------------------------------------------------------------------*/
#define __SA0_BREAK(level)      __sa_break(level, 0U)
#define __SA1_BREAK(level)      __sa_break(level, 1U)
#define __SA2_BREAK(level)      __sa_break(level, 2U)
#define __SA3_BREAK(level)      __sa_break(level, 3U)

/*----------------------------------------------------------------------------*/
/* __vpred __SAn_VPRED(type)                                                  */
/*   Extracts the vector predicate associated with streaming address generator*/
/*   n, scaled for type, where type may be exactly:                           */
/*     char, char2, char4, char8, char16, char32, char64                      */
/*     uchar, uchar2, uchar4, uchar8, uchar16, uchar32, uchar64               */
/*                                                                            */
/*     short, short2, short4, short8, short16, short32                        */
/*     ushort, ushort2, ushort4, ushort8, ushort16, ushort32                  */
/*     cchar, cchar2, cchar4, cchar8, cchar16, cchar32                        */
/*                                                                            */
/*     int, int2, int4, int8, int16                                           */
/*     uint, uint2, uint4, uint8, uint16                                      */
/*     float, float2, float4, float8, float16                                 */
/*     cshort, cshort2, cshort4, cshort8, cshort16                            */
/*                                                                            */
/*     long, long2, long4, long8                                              */
/*     ulong, ulong2, ulong4, ulong8                                          */
/*     double, double2, double4, double8                                      */
/*     cint, cint2, cint4, cint8                                              */
/*     cfloat, cfloat2, cfloat4, cfloat8                                      */
/*                                                                            */
/* NOTE: According to C rules, the order in which paramaters of a call are    */
/*   evaluated is unspecified, such that the shorthand way of using these     */
/*   predicates:                                                              */
/*     __vstore_pred(__SA0_VPRED(int16), __SA0ADV(int16, ptr), data)          */
/*   Invokes undefined behavior because SA0ADV modifies the value SA0_VPRED.  */
/*----------------------------------------------------------------------------*/
#define __SA0_VPRED(type)  __sa_vpred(0U, sizeof(type)/__numelemof(type))
#define __SA1_VPRED(type)  __sa_vpred(1U, sizeof(type)/__numelemof(type))
#define __SA2_VPRED(type)  __sa_vpred(2U, sizeof(type)/__numelemof(type))
#define __SA3_VPRED(type)  __sa_vpred(3U, sizeof(type)/__numelemof(type))

/*----------------------------------------------------------------------------*/
/* boolv __SAn_BOOL(type)                                                     */
/*   Extracts the vector predicate associated with streaming address generator*/
/*   n as a boolean vector.  Argument restrictions are the same as            */
/*   __SAn_VPRED(type).  boolv is a boolean vector with lanes equal to the    */
/*   number of lanes in type.  For example, if type is int2, boolv will be    */
/*   __bool2.                                                                 */
/*----------------------------------------------------------------------------*/
#define __SA0_BOOL(type)   __sa_bool_##type(__sa_vpred(0U, sizeof(type)/__numelemof(type)))
#define __SA1_BOOL(type)   __sa_bool_##type(__sa_vpred(1U, sizeof(type)/__numelemof(type)))
#define __SA2_BOOL(type)   __sa_bool_##type(__sa_vpred(2U, sizeof(type)/__numelemof(type)))
#define __SA3_BOOL(type)   __sa_bool_##type(__sa_vpred(3U, sizeof(type)/__numelemof(type)))

/*----------------------------------------------------------------------------*/
/* STREAMING ADDRESS GENERATOR AUXILIARY API                                  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Template format selection for Stream Address Generator                     */
/*----------------------------------------------------------------------------*/
#define __SA_DIMFMT_1D  (0)
#define __SA_DIMFMT_2D  (1)
#define __SA_DIMFMT_3D  (2)
#define __SA_DIMFMT_4D  (3)
#define __SA_DIMFMT_5D  (4)
#define __SA_DIMFMT_6D  (5)

/*----------------------------------------------------------------------------*/
/* Stream Address Generator vector lengths.                                   */
/* Use the below macros to indicate the vector lengths in elements.           */
/*----------------------------------------------------------------------------*/
#define __SA_VECLEN_1ELEM        (0) /* default */
#define __SA_VECLEN_2ELEMS       (1)
#define __SA_VECLEN_4ELEMS       (2)
#define __SA_VECLEN_8ELEMS       (3)
#define __SA_VECLEN_16ELEMS      (4)
#define __SA_VECLEN_32ELEMS      (5)
#define __SA_VECLEN_64ELEMS      (6)

/*----------------------------------------------------------------------------*/
/* Stream Address Generator Data Strip Mining Decrement Dimension for ICNT0   */
/* In this mode, the current I0 count is NOT reloaded with ICNT0 when each    */
/* dimension expires.  The I0 count is only reloaded when the selected DECDIM */
/* dimension expires, or a dimension higher above it expires.                 */
/*----------------------------------------------------------------------------*/
#define __SA_DECDIM_DIM0 (0) /* Normal Operating Mode - default */
#define __SA_DECDIM_DIM1 (1) /* Strip Mining on DIM1 */
#define __SA_DECDIM_DIM2 (2) /* Strip Mining on DIM2 */
#define __SA_DECDIM_DIM3 (3) /* Strip Mining on DIM3 */
#define __SA_DECDIM_DIM4 (4) /* Strip Mining on DIM4 */
#define __SA_DECDIM_DIM5 (5) /* Strip Mining on DIM5 */

/*----------------------------------------------------------------------------*/
/* Stream Address Generator Secondary Data Strip Mining Decrement Dimension   */
/*----------------------------------------------------------------------------*/
#define __SA_DECDIMSD_DIM0 (0) /* Normal Operating Mode - default */
#define __SA_DECDIMSD_DIM1 (1) /* SD Strip Mining on DIM1 (DECDIM_WIDTH decs) */
#define __SA_DECDIMSD_DIM2 (2) /* SD Strip Mining on DIM2 (DECDIM_WIDTH decs) */
#define __SA_DECDIMSD_DIM3 (3) /* SD Strip Mining on DIM3 (DECDIM_WIDTH decs) */

/*----------------------------------------------------------------------------*/
/* Stream Address Generator param size is 64 bytes. All the above options     */
/* including iteration counts(ICNT) and dimensions(DIM) are packed in a       */
/* 512bit vector. Use this macro to derrive offsets while writing to L1D SRAM */
/*----------------------------------------------------------------------------*/
#define SA_PARAM_SIZE (64)


/*----------------------------------------------------------------------------*/
/* struct : __SA_FLAGS                                                        */
/* Desc   : Structure to hold the Stream Address Generator options,           */
/*          iteration counts and transfer dimensions.                         */
/*                                                                            */
/* elements:   uint8_t VECLEN                                                 */
/*              - Predifined macro values for indicating vector length.       */
/*             uint8_t DIMFMT                                                 */
/*              - Predefined macro values for indicating dimensions in nest.  */
/*             uint8_t DECDIM1                                                */
/*              - Predefined macro values for indicating data strip mining    */
/*                dimension for DECDIM1_WIDTH.                                */
/*             uint8_t DECDIM1SD                                              */
/*              - Predefined macro values for indicating secondary data strip */
/*                mining dimension for DECDIM1_WIDTH.                         */
/*             uint8_t DECDIM2                                                */
/*              - Predefined macro values for indicating data strip mining    */
/*                dimension for DECDIM2_WIDTH.                                */
/*             uint8_t DECDIM2SD                                              */
/*              - Predefined macro values for indicating secondary data strip */
/*                mining dimension for DECDIM2_WIDTH.                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/
typedef struct __SA_FLAGS_t
{
   uint8_t VECLEN;
   uint8_t DIMFMT;
   uint8_t DECDIM1;
   uint8_t DECDIM1SD;
   uint8_t DECDIM2;
   uint8_t DECDIM2SD;

} __SA_FLAGS;


/******************************************************************************/


/*----------------------------------------------------------------------------*/
/* Func: __SE_FLAGS_default                                                   */
/*                                                                            */
/* Return: Returns a struct with __SE_FLAGS default values                    */
/*----------------------------------------------------------------------------*/
static __inline __SE_FLAGS __SE_FLAGS_default()
{
    __SE_FLAGS flags;

    flags.DIR       = __SE_DIR_INC;
    flags.TRANSPOSE = __SE_TRANSPOSE_OFF;
    flags.ELETYPE   = __SE_ELETYPE_8BIT;
    flags.PROMOTE   = __SE_PROMOTE_OFF;
    flags.GRPDUP    = __SE_GRPDUP_OFF;
    flags.ELEDUP    = __SE_ELEDUP_OFF;
    flags.DECIM     = __SE_DECIM_OFF;
    flags.DECDIM1   = __SE_DECDIM_DIM0;
    flags.DECDIM2   = __SE_DECDIM_DIM0;
    flags.DECDIM1SD = __SE_DECDIMSD_DIM0;
    flags.DECDIM2SD = __SE_DECDIMSD_DIM0;
    flags.LEZR      = __SE_LEZR_OFF;
    flags.VECLEN    = __SE_VECLEN_64ELEMS;

    return flags;
}

/*----------------------------------------------------------------------------*/
/* Func: __SE_CIRC_FLAGS_default                                              */
/*                                                                            */
/* Return: Returns a struct with __SE_CIRC_FLAGS default values               */
/*----------------------------------------------------------------------------*/
static __inline __SE_CIRC_FLAGS __SE_CIRC_FLAGS_default()
{
    __SE_CIRC_FLAGS cflags;

    cflags.CBK0 = 0;
    cflags.CBK1 = 0;
    cflags.AM0  = __SE_AM_LINEAR;
    cflags.AM1  = __SE_AM_LINEAR;
    cflags.AM2  = __SE_AM_LINEAR;
    cflags.AM3  = __SE_AM_LINEAR;
    cflags.AM4  = __SE_AM_LINEAR;
    cflags.AM5  = __SE_AM_LINEAR;

    return cflags;
}

/*----------------------------------------------------------------------------*/
/* Func: __set_SE_FLAGS                                                       */
/*                                                                            */
/* Args: __STRM_TEMPLATE param                                                */
/*            - param structure into which to program the flags.              */
/*       __SE_FLAGS *pFlags                                                   */
/*            - Pointer to __SE_FLAGS structure.                              */
/*       __SE_CIRC_FLAGS *pCFlags                                             */
/*            - Pointer to __SE_CIRC_FLAGS structure.                         */
/*              A NULL pointer means that no circular addressing is used.     */
/*                                                                            */
/* Return: Returns a 512 bit param packed with Stream Engine flags            */
/*----------------------------------------------------------------------------*/
static __inline __STRM_TEMPLATE __set_SE_FLAGS(__STRM_TEMPLATE param,
                                               __SE_FLAGS      *pFlags,
                                               __SE_CIRC_FLAGS *pCFlags)
{
    uint32_t LFLAGS = 0, HFLAGS = 0;

    /*------------------------------------------------------------------------*/
    /* Pack and set the flags as per streaming engine specs.                  */
    /*------------------------------------------------------------------------*/
    LFLAGS = ((pFlags->ELETYPE   & 0x0F) <<  0) |  /* ELTYPE    4-bits */
             ((pFlags->TRANSPOSE & 0x07) <<  4) |  /* TRANSPOSE 3-bits */
             ((pFlags->PROMOTE   & 0x07) <<  8) |  /* PROMOTE   3-bits */
             ((pFlags->VECLEN    & 0x07) << 12) |  /* VECLEN    3-bits */
             ((pFlags->ELEDUP    & 0x07) << 16) |  /* ELEDUP    3-bits */
             ((pFlags->GRPDUP    & 0x01) << 19) |  /* GRDUP     1-bit  */
             ((pFlags->DECIM     & 0x03) << 20) |  /* DECIM     2-bits */
             ((pFlags->DIMFMT    & 0x07) << 24) |  /* DIMFMT    3-bits */
             ((pFlags->DIR       & 0x01) << 27);   /* DIR       1-bit  */
    HFLAGS = ((pFlags->DECDIM1   & 0x07) << 16) |  /* DECDIM1   3-bits */
             ((pFlags->DECDIM1SD & 0x03) << 19) |  /* DECDIM1SD 2-bits */
             ((pFlags->DECDIM2   & 0x07) << 21) |  /* DECDIM2   3-bits */
             ((pFlags->DECDIM2SD & 0x03) << 24) |  /* DECDIM2SD 2-bits */
             ((pFlags->LEZR      & 0x07) << 26);   /* LEZR      3-bits */

    /*------------------------------------------------------------------------*/
    /* Pack and set the circular addr flags as per streaming engine specs.    */
    /*------------------------------------------------------------------------*/
    if (pCFlags)
    {
        LFLAGS = LFLAGS | ((pCFlags->CBK0 & 0x0F) << 28);   /* CBK0 4-bits */
        HFLAGS = HFLAGS | ((pCFlags->CBK1 & 0x0F) <<  0) |  /* CBK1 4-bits */
                          ((pCFlags->AM0  & 0x03) <<  4) |  /* AM0  2-bits */
                          ((pCFlags->AM1  & 0x03) <<  6) |  /* AM1  2-bits */
                          ((pCFlags->AM2  & 0x03) <<  8) |  /* AM2  2-bits */
                          ((pCFlags->AM3  & 0x03) << 10) |  /* AM3  2-bits */
                          ((pCFlags->AM4  & 0x03) << 12) |  /* AM4  2-bits */
                          ((pCFlags->AM5  & 0x03) << 14);   /* AM5  2-bits */
    }

    /*------------------------------------------------------------------------*/
    /* Program Parameter structure                                            */
    /*------------------------------------------------------------------------*/
    param.s[14]=LFLAGS;
    param.s[15]=HFLAGS;

    return param;
}

/*----------------------------------------------------------------------------*/
/* Func: __get_SE_FLAGS                                                       */
/*                                                                            */
/* Args: __STRM_TEMPLATE param                                                */
/*            - param structure from which to extract the flags.              */
/*                                                                            */
/* Return: Returns a struct with Stream Engine flags                          */
/*----------------------------------------------------------------------------*/
static __inline __SE_FLAGS __get_SE_FLAGS(__STRM_TEMPLATE param)
{
    __SE_FLAGS pFlags;

    uint32_t LFLAGS = param.s[14];
    uint32_t HFLAGS = param.s[15];

    /*------------------------------------------------------------------------*/
    /* Extract the flags as per streaming engine specs.                       */
    /*------------------------------------------------------------------------*/
    pFlags.ELETYPE   = (LFLAGS >>  0) & 0x0F;  /* ELTYPE    4-bits */
    pFlags.TRANSPOSE = (LFLAGS >>  4) & 0x07;  /* TRANSPOSE 3-bits */
    pFlags.PROMOTE   = (LFLAGS >>  8) & 0x07;  /* PROMOTE   3-bits */
    pFlags.VECLEN    = (LFLAGS >> 12) & 0x07;  /* VECLEN    3-bits */
    pFlags.ELEDUP    = (LFLAGS >> 16) & 0x07;  /* ELEDUP    3-bits */
    pFlags.GRPDUP    = (LFLAGS >> 19) & 0x01;  /* GRDUP     1-bit  */
    pFlags.DECIM     = (LFLAGS >> 20) & 0x03;  /* DECIM     2-bits */
    pFlags.DIMFMT    = (LFLAGS >> 24) & 0x07;  /* DIMFMT    3-bits */
    pFlags.DIR       = (LFLAGS >> 27) & 0x01;  /* DIR       1-bit  */
    pFlags.DECDIM1   = (HFLAGS >> 16) & 0x07;  /* DECDIM1   3-bits */
    pFlags.DECDIM1SD = (HFLAGS >> 19) & 0x03;  /* DECDIM1SD 2-bits */
    pFlags.DECDIM2   = (HFLAGS >> 21) & 0x07;  /* DECDIM2   3-bits */
    pFlags.DECDIM2SD = (HFLAGS >> 24) & 0x03;  /* DECDIM2SD 2-bits */
    pFlags.LEZR      = (HFLAGS >> 26) & 0x07;  /* LEZR      3-bits */

    return pFlags;
}

/*----------------------------------------------------------------------------*/
/* Func: __get_SE_CIRC_FLAGS                                                  */
/*                                                                            */
/* Args: __STRM_TEMPLATE param                                                */
/*            - param structure from which to extract the flags.              */
/*                                                                            */
/* Return: Returns a struct with Stream Engine circular addr flags            */
/*----------------------------------------------------------------------------*/
static __inline __SE_CIRC_FLAGS __get_SE_CIRC_FLAGS(__STRM_TEMPLATE param)
{
    __SE_CIRC_FLAGS pCFlags;

    uint32_t LFLAGS = param.s[14];
    uint32_t HFLAGS = param.s[15];

    /*------------------------------------------------------------------------*/
    /* Extract the circular addr flags as per streaming engine specs.         */
    /*------------------------------------------------------------------------*/
    pCFlags.CBK0 = (LFLAGS >> 28) & 0x0F;  /* CBK0 4-bits */
    pCFlags.CBK1 = (HFLAGS >>  0) & 0x0F;  /* CBK1 4-bits */
    pCFlags.AM0  = (HFLAGS >>  4) & 0x03;  /* AM0  2-bits */
    pCFlags.AM1  = (HFLAGS >>  6) & 0x03;  /* AM1  2-bits */
    pCFlags.AM2  = (HFLAGS >>  8) & 0x03;  /* AM2  2-bits */
    pCFlags.AM3  = (HFLAGS >> 10) & 0x03;  /* AM3  2-bits */
    pCFlags.AM4  = (HFLAGS >> 12) & 0x03;  /* AM4  2-bits */
    pCFlags.AM5  = (HFLAGS >> 14) & 0x03;  /* AM5  2-bits */

    return pCFlags;
}

/*----------------------------------------------------------------------------*/
/* Func: __SA_FLAGS_default                                                   */
/*                                                                            */
/* Return: Returns a struct with __SA_FLAGS default values                    */
/*----------------------------------------------------------------------------*/
static __inline __SA_FLAGS __SA_FLAGS_default()
{
    __SA_FLAGS flags;

    flags.VECLEN    = __SA_VECLEN_64ELEMS;
    flags.DECDIM1   = __SA_DECDIM_DIM0;
    flags.DECDIM2   = __SA_DECDIM_DIM0;
    flags.DECDIM1SD = __SA_DECDIM_DIM0;
    flags.DECDIM2SD = __SA_DECDIM_DIM0;

    return flags;
}

/*----------------------------------------------------------------------------*/
/* Func: __set_SA_FLAGS                                                       */
/*                                                                            */
/* Args: __STRM_TEMPLATE param                                                */
/*            - param structure into which to program the flags.              */
/*       __SA_FLAGS *pFlags                                                   */
/*            - Pointer to __SA_FLAGS structure.                              */
/*                                                                            */
/* Return: Returns a 512 bit param packed with Stream Address Generator flags */
/*----------------------------------------------------------------------------*/
static __inline __STRM_TEMPLATE __set_SA_FLAGS(__STRM_TEMPLATE param,
                                               __SA_FLAGS      *pFlags)
{
    uint32_t LFLAGS = 0, HFLAGS = 0;

    /*------------------------------------------------------------------------*/
    /* Pack the flags as per Stream Address Generator specs.                  */
    /*------------------------------------------------------------------------*/
    LFLAGS = ((pFlags->VECLEN    & 0x07) << 12)  | /* VECLEN    3-bits */
             ((pFlags->DIMFMT    & 0x07) << 24);   /* DIMFMT    3-bits */
    HFLAGS = ((pFlags->DECDIM1   & 0x07) << 16)  | /* DECDIM1   3-bits */
             ((pFlags->DECDIM1SD & 0x03) << 19)  | /* DECDIM1SD 2-bits */
             ((pFlags->DECDIM2   & 0x07) << 21)  | /* DECDIM2   3-bits */
             ((pFlags->DECDIM2SD & 0x03) << 24);   /* DECDIM2SD 2-bits */

    param.s[14]=LFLAGS;
    param.s[15]=HFLAGS;

    /*------------------------------------------------------------------------*/
    /* Zero-initialize reserved portions of parameter template                */
    /*------------------------------------------------------------------------*/
    param.s[13] = 0;

    return param;
}

/*----------------------------------------------------------------------------*/
/* Func: __get_SA_FLAGS                                                       */
/*                                                                            */
/* Args: __STRM_TEMPLATE param                                                */
/*            - param structure from which to extract the flags.              */
/*                                                                            */
/* Return: Returns a struct with Stream Address Generator flags               */
/*----------------------------------------------------------------------------*/
static __inline __SA_FLAGS __get_SA_FLAGS(__STRM_TEMPLATE param)
{
    __SA_FLAGS pFlags;

    uint32_t LFLAGS = param.s[14];
    uint32_t HFLAGS = param.s[15];

    /*------------------------------------------------------------------------*/
    /* Extract the flags as per Stream Address Generator specs.               */
    /*------------------------------------------------------------------------*/
    pFlags.VECLEN    = (LFLAGS >> 12) & 0x07; /* VECLEN    3-bits */
    pFlags.DIMFMT    = (LFLAGS >> 24) & 0x07; /* DIMFMT    3-bits */
    pFlags.DECDIM1   = (HFLAGS >> 16) & 0x07; /* DECDIM1   3-bits */
    pFlags.DECDIM1SD = (HFLAGS >> 19) & 0x03; /* DECDIM1SD 2-bits */
    pFlags.DECDIM2   = (HFLAGS >> 21) & 0x07; /* DECDIM2   3-bits */
    pFlags.DECDIM2SD = (HFLAGS >> 24) & 0x03; /* DECDIM2SD 2-bits */

    return pFlags;
}

/*----------------------------------------------------------------------------*/
/* DECDIM_WIDTH/ICNT/DIM Set routines                                         */
/*----------------------------------------------------------------------------*/
static __inline __STRM_TEMPLATE __set_ICNT0(__STRM_TEMPLATE param,
                                            uint32_t icnt)
{
    param.s[0] = icnt;
    return param;
}

static __inline __STRM_TEMPLATE __set_ICNT1_DIM1(__STRM_TEMPLATE param,
                                                 uint32_t icnt, int32_t dim)
{
    param.s[1] = icnt; param.s[8] = dim;
    return param;
}

static __inline __STRM_TEMPLATE __set_ICNT2_DIM2(__STRM_TEMPLATE param,
                                                 uint32_t icnt, int32_t dim)
{
    param.s[2] = icnt; param.s[9] = dim;
    return param;
}

static __inline __STRM_TEMPLATE __set_ICNT3_DIM3(__STRM_TEMPLATE param,
                                                 uint32_t icnt, int32_t dim)
{
    param.s[3] = icnt; param.s[10] = dim;
    return param;
}

static __inline __STRM_TEMPLATE __set_ICNT4_DIM4(__STRM_TEMPLATE param,
                                                 uint32_t icnt, int32_t dim)
{
    param.s[4] = icnt; param.s[11] = dim;
    return param;
}

static __inline __STRM_TEMPLATE __set_ICNT5_DIM5(__STRM_TEMPLATE param,
                                                 uint32_t icnt, int32_t dim)
{
    param.s[5] = icnt; param.s[12] = dim;
    return param;
}

static __inline __STRM_TEMPLATE __set_DECDIM1_WIDTH(__STRM_TEMPLATE param,
                                                    uint32_t decdim_width)
{
    param.s[6] = decdim_width;
    return param;
}

static __inline __STRM_TEMPLATE __set_DECDIM2_WIDTH(__STRM_TEMPLATE param,
                                                    uint32_t decdim_width)
{
    param.s[7] = decdim_width;
    return param;
}

static __inline __STRM_TEMPLATE __set_LEZR_CNT(__STRM_TEMPLATE param,
                                               uint8_t lezr_cnt)
{
    param.s[13] = lezr_cnt;
    return param;
}
/*----------------------------------------------------------------------------*/
/* DECDIM_WIDTH/ICNT/DIM Extraction routines (DEBUG)                          */
/*----------------------------------------------------------------------------*/
static __inline uint32_t __get_ICNT0     (__STRM_TEMPLATE p) { return p.s[0];  }
static __inline uint32_t __get_ICNT1     (__STRM_TEMPLATE p) { return p.s[1];  }
static __inline  int32_t __get_DIM1      (__STRM_TEMPLATE p) { return p.s[8];  }
static __inline uint32_t __get_ICNT2     (__STRM_TEMPLATE p) { return p.s[2];  }
static __inline  int32_t __get_DIM2      (__STRM_TEMPLATE p) { return p.s[9];  }
static __inline uint32_t __get_ICNT3     (__STRM_TEMPLATE p) { return p.s[3];  }
static __inline  int32_t __get_DIM3      (__STRM_TEMPLATE p) { return p.s[10]; }
static __inline uint32_t __get_ICNT4     (__STRM_TEMPLATE p) { return p.s[4];  }
static __inline  int32_t __get_DIM4      (__STRM_TEMPLATE p) { return p.s[11]; }
static __inline uint32_t __get_ICNT5     (__STRM_TEMPLATE p) { return p.s[5];  }
static __inline  int32_t __get_DIM5      (__STRM_TEMPLATE p) { return p.s[12]; }
static __inline uint32_t __get_DECDIM1_WIDTH(__STRM_TEMPLATE p)
                                                             { return p.s[6];  }
static __inline uint32_t __get_DECDIM2_WIDTH(__STRM_TEMPLATE p)
                                                             { return p.s[7];  }
static __inline  uint8_t __get_LEZR_CNT  (__STRM_TEMPLATE p) { return p.s[13]; }

/*----------------------------------------------------------------------------*/
/* Include struct-based configuration wrapper                                 */
/*----------------------------------------------------------------------------*/
#include <c7x_strm_struct.h>

#ifdef __cplusplus
}
#endif

#endif /* __C7X_STRM_DEPRECATED_H */
