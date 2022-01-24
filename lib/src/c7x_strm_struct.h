/*****************************************************************************/
/*  C7X_STRM_STRUCT.H                                                        */
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
/* SOURCE CODE.                                                              */
/*                                                                           */
/* NOTE!!!                                                                   */
/* NOTE!!!                                                                   */
/* NOTE!!!                                                                   */
/* NOTE!!!                                                                   */
/* NOTE!!!                                                                   */
/*                                                                           */
/*****************************************************************************/
#ifndef __C7X_STRM_DEPRECATED_H
#error "This file can only be included by parent header c7x.h"
#endif

#ifndef __C7X_STRM_STRUCT_H
#define __C7X_STRM_STRUCT_H

/*----------------------------------------------------------------------------*/
/* DEMONSTRATION FOR SETUP AND USAGE OF A STREAMING ENGINE STREAM WITHOUT     */
/* CIRCULAR ADDRESSING:                                                       */
/*                                                                            */
/* #include <c7x.h>                                                           */
/* uint8 se_func(uint32_t *startaddr)                                         */
/* {                                                                          */
/*     int I0;                                                                */
/*     uint8 Vresult;                                                         */
/*     __SE_FLAGS      flags; // SE FLAGS STRUCTURE                           */
/*     __STRM_PARAM_4D param; // 4D-INNER PARAMETER STRUCTURE                 */
/*                                                                            */
/*     flags.DIR       = __SE_DIR_INC;                                        */
/*     flags.TRANSPOSE = __SE_TRANSPOSE_OFF;                                  */
/*     flags.DECIM     = __SE_DECIM_OFF;                                      */
/*                                                                            */
/*     flags.ELETYPE   = __SE_ELETYPE_32BIT;                                  */
/*     flags.PROMOTE   = __SE_PROMOTE_OFF;                                    */
/*     flags.GRPDUP    = __SE_GRPDUP_OFF;                                     */
/*     flags.ELEDUP    = __SE_ELEDUP_OFF;                                     */
/*     flags.DECDIM1   = __SE_DECDIM_DIM0;                                    */
/*     flags.DECDIM2   = __SE_DECDIM_DIM0;                                    */
/*     flags.DECDIM1SD = __SE_DECDIMSD_DIM0;                                  */
/*     flags.DECDIM2SD = __SE_DECDIMSD_DIM0;                                  */
/*     flags.LEZR      = __SE_LEZR_OFF;                                       */
/*                                                                            */
/*     flags.VECLEN    = __SE_VECLEN_4ELEMS; // 4 ELEMENTS                    */
/*                                                                            */
/*     // ITERATION COUNTERS                                                  */
/*     param.ICNT0 = 4;                                                       */
/*     param.ICNT1 = 2;                                                       */
/*     param.ICNT2 = 2;                                                       */
/*     param.ICNT3 = 4;                                                       */
/*                                                                            */
/*     // DIMENSIONS (BYTES)                                                  */
/*     param.DIM1  = 16;                                                      */
/*     param.DIM2  = 32;                                                      */
/*     param.DIM3  = -64;                                                     */
/*                                                                            */
/*     // SETUP TEMPLATE VECTOR BASED ON SETTINGS AND OPEN THE STREAM         */
/*     __STRM_TEMPLATE template = __SE_SET_PARAM_4D(&param, &flags);          */
/*     __SE1_OPEN((void*)startaddr, template);                                */
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
/* uint16 se_circ_func(uint32_t *startaddr)                                   */
/* {                                                                          */
/*     int I0;                                                                */
/*     uint16 Vresult;                                                        */
/*     __SE_FLAGS       flags;  // SE FLAGS STRUCTURE                         */
/*     __SE_CIRC_FLAGS  cflags; // SE CIRCULAR ADDRESSING FLAGS STRUCTURE     */
/*     __STRM_PARAM_3D  param;  // 3D PARAMETER STRUCTURE                     */
/*                                                                            */
/*     flags.DIR       = __SE_DIR_INC;                                        */
/*     flags.TRANSPOSE = __SE_TRANSPOSE_OFF;                                  */
/*     flags.DECIM     = __SE_DECIM_OFF;                                      */
/*                                                                            */
/*     flags.ELETYPE   = __SE_ELETYPE_32BIT;                                  */
/*     flags.PROMOTE   = __SE_PROMOTE_OFF;                                    */
/*     flags.GRPDUP    = __SE_GRPDUP_OFF;                                     */
/*     flags.ELEDUP    = __SE_ELEDUP_OFF;                                     */
/*     flags.DECDIM1   = __SE_DECDIM_DIM0;                                    */
/*     flags.DECDIM2   = __SE_DECDIM_DIM0;                                    */
/*     flags.DECDIM1SD = __SE_DECDIMSD_DIM0;                                  */
/*     flags.DECDIM2SD = __SE_DECDIMSD_DIM0;                                  */
/*     flags.LEZR      = __SE_LEZR_OFF;                                       */
/*                                                                            */
/*     flags.VECLEN    = __SE_VECLEN_16ELEMS; // 16 ELEMENTS                  */
/*                                                                            */
/*     // ITERATION COUNTERS                                                  */
/*     param.ICNT0 = 16;                                                      */
/*     param.ICNT1 = 16;                                                      */
/*     param.ICNT2 = 1;                                                       */
/*                                                                            */
/*     // DIMENSIONS (BYTES)                                                  */
/*     param.DIM1  = 64;                                                      */
/*     param.DIM2  = 0;                                                       */
/*                                                                            */
/*     // CIRCULAR ADDRESSING BLOCK CONFIGURATION (SEE SPEC FOR DETAILS)      */
/*     cflags.CBK0 = 0;                    // 512BYTE ENCODING                */
/*     cflags.CBK1 = 0;                    // UNUSED                          */
/*                                                                            */
/*     // CIRCULAR ADDRESSING ADDRESS MODE CONFIGURATION                      */
/*     cflags.AM0 = __SE_AM_CIRC_CBK0;                                        */
/*     cflags.AM1 = __SE_AM_CIRC_CBK0;                                        */
/*     cflags.AM2 = __SE_AM_CIRC_CBK0;                                        */
/*     cflags.AM3 = 0;                     // UNUSED                          */
/*     cflags.AM4 = 0;                     // UNUSED                          */
/*     cflags.AM5 = 0;                     // UNUSED                          */
/*                                                                            */
/*     // SETUP TEMPLATE VECTOR BASED ON SETTINGS AND OPEN THE STREAM         */
/*     __STRM_TEMPLATE template = __SE_SET_PARAM_3D_CIRC(&param, &flags,      */
/*                                                               &cflags);    */
/*     __SE1_OPEN((void*)startaddr, template);                                */
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
/* uint8 sa_func(uint32_t *startaddr)                                         */
/* {                                                                          */
/*     int I0;                                                                */
/*     uint8 Vresult;                                                         */
/*     __SA_FLAGS      flags; // SA FLAGS STRUCTURE                           */
/*     __STRM_PARAM_4D param; // 4D-INNER PARAMETER STRUCTURE                 */
/*                                                                            */
/*     flags.DECDIM1 = __SA_DECDIM_DIM0;                                      */
/*     flags.DECDIM2 = __SA_DECDIM_DIM0;                                      */
/*     flags.DECDIM1SD = __SA_DECDIMSD_DIM0;                                  */
/*     flags.DECDIM2SD = __SA_DECDIMSD_DIM0;                                  */
/*     flags.VECLEN  = __SA_VECLEN_4ELEMS; // 4 ELEMENTS                      */
/*                                                                            */
/*     // ITERATION COUNTERS                                                  */
/*     param.ICNT0 = 4;                                                       */
/*     param.ICNT1 = 2;                                                       */
/*     param.ICNT2 = 2;                                                       */
/*     param.ICNT3 = 4;                                                       */
/*                                                                            */
/*     // DIMENSIONS (NUMBER OF ELEMENTS)                                     */
/*     param.DIM1  = 4;                                                       */
/*     param.DIM2  = 8;                                                       */
/*     param.DIM3  = -16;                                                     */
/*                                                                            */
/*     // SETUP TEMPLATE VECTOR BASED ON SETTINGS AND OPEN THE STREAM         */
/*     __STRM_TEMPLATE template = __SA_SET_PARAM_4D(&param, &flags);          */
/*     __SA1_OPEN(template);                                                  */
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


/*----------------------------------------------------------------------------*/
/* struct : __STRM_PARAM_{3D,4D,5D,6D}                                        */
/* Desc   : Struct to hold the iteration counts and transfer dimensions used  */
/*          by the Streaming Engine and Streaming Address Generator.  Counts  */
/*          and dimensions are defined in terms of supported streaming engine */
/*          formats.                                                          */
/*                                                                            */
/* elements:   ICNT0                                                          */
/*              - Number of columns of a transfer block.                      */
/*                Size indicated using ELETYPE.                               */
/*             ICNT1                                                          */
/*              - Number of rows of a transfer block.                         */
/*             ICNT2                                                          */
/*              - Number of (ICNT0 x ICNT1) blocks in 3rd dimension.          */
/*             ICNT3                                                          */
/*              - Number of (ICNT2 x (ICNT1 x ICNT0)) blocks in 4th dimension.*/
/*             ICNT4                                                          */
/*              - Number of (ICNT3 x (ICNT2 x (ICNT1 x ICNT0))) blocks in 5th */
/*                dimension.                                                  */
/*             ICNT5                                                          */
/*              - Number of (ICNT4 x (ICNT3 x (ICNT2 x (ICNT1 x ICNT0))))     */
/*                blocks in 6th dimension.                                    */
/*                                                                            */
/*             DIM1                                                           */
/*              - Stride in bytes for every ICNT1                             */
/*             DIM2                                                           */
/*              - Stride in bytes for every ICNT2                             */
/*             DIM3                                                           */
/*              - Stride in bytes for every ICNT3                             */
/*             DIM4                                                           */
/*              - Stride in bytes for every ICNT4                             */
/*             DIM5                                                           */
/*              - Stride in bytes for every ICNT5                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/
typedef struct __sParam3D_fmt_t
{
    uint32_t ICNT0, ICNT1, ICNT2;
    int32_t  DIM1, DIM2;
    uint32_t DECDIM1_WIDTH;
    uint32_t DECDIM2_WIDTH;
    uint8_t  LEZR_CNT;

} __STRM_PARAM_3D;

typedef struct __sParam4D_fmt_t
{
    uint32_t ICNT0, ICNT1, ICNT2, ICNT3;
    int32_t  DIM1, DIM2, DIM3;
    uint32_t DECDIM1_WIDTH;
    uint32_t DECDIM2_WIDTH;
    uint8_t  LEZR_CNT;

} __STRM_PARAM_4D;

typedef struct __sParam5D_fmt_t
{
    uint32_t ICNT0, ICNT1, ICNT2, ICNT3, ICNT4;
    int32_t  DIM1, DIM2, DIM3, DIM4;
    uint32_t DECDIM1_WIDTH;
    uint32_t DECDIM2_WIDTH;
    uint8_t  LEZR_CNT;

} __STRM_PARAM_5D;

typedef struct __sParam6D_fmt_t
{
    uint32_t ICNT0, ICNT1, ICNT2, ICNT3, ICNT4, ICNT5;
    int32_t  DIM1, DIM2, DIM3, DIM4, DIM5;
    uint32_t DECDIM1_WIDTH;
    uint32_t DECDIM2_WIDTH;
    uint8_t  LEZR_CNT;

} __STRM_PARAM_6D;


/*----------------------------------------------------------------------------*/
/* __SE_SET_PARAM MACROS WITHOUT CIRCULAR ADDRESSING                          */
/*----------------------------------------------------------------------------*/
#define __SE_SET_PARAM_3D(param, flags) __se_set_param_3D(param, flags, NULL)
#define __SE_SET_PARAM_4D(param, flags) __se_set_param_4D(param, flags, NULL)
#define __SE_SET_PARAM_5D(param, flags) __se_set_param_5D(param, flags, NULL)
#define __SE_SET_PARAM_6D(param, flags) __se_set_param_6D(param, flags, NULL)

/*----------------------------------------------------------------------------*/
/* __SE_SET_PARAM MACROS WITH CIRCULAR ADDRESSING                             */
/*----------------------------------------------------------------------------*/
#define __SE_SET_PARAM_3D_CIRC(p,f,c) __se_set_param_3D(p, f, c)
#define __SE_SET_PARAM_4D_CIRC(p,f,c) __se_set_param_4D(p, f, c)
#define __SE_SET_PARAM_5D_CIRC(p,f,c) __se_set_param_5D(p, f, c)
#define __SE_SET_PARAM_6D_CIRC(p,f,c) __se_set_param_6D(p, f, c)


static __inline __STRM_TEMPLATE __se_set_param_3D(__STRM_PARAM_3D *pParam,
                                                __SE_FLAGS      *pSEFlags,
                                                __SE_CIRC_FLAGS *pSECFlags)
{
    __STRM_TEMPLATE params = (0);

    pSEFlags->DIMFMT = __SE_DIMFMT_3D;

    if (pSEFlags->DECDIM1 != __SE_DECDIM_DIM0)
        params = __set_DECDIM1_WIDTH(params, pParam->DECDIM1_WIDTH);

    if (pSEFlags->DECDIM2 != __SE_DECDIM_DIM0)
        params = __set_DECDIM2_WIDTH(params, pParam->DECDIM2_WIDTH);

    if (pSEFlags->LEZR != __SE_LEZR_OFF)
        params = __set_LEZR_CNT(params, pParam->LEZR_CNT);

    params = __set_ICNT0(params, pParam->ICNT0);
    params = __set_ICNT1_DIM1(params, pParam->ICNT1, pParam->DIM1);
    params = __set_ICNT2_DIM2(params, pParam->ICNT2, pParam->DIM2);
    return   __set_SE_FLAGS(params, pSEFlags, pSECFlags);
}

static __inline __STRM_TEMPLATE __se_set_param_4D(__STRM_PARAM_4D *pParam,
                                                __SE_FLAGS      *pSEFlags,
                                                __SE_CIRC_FLAGS *pSECFlags)
{
    __STRM_TEMPLATE params = (0);

    pSEFlags->DIMFMT = __SE_DIMFMT_4D;

    if (pSEFlags->DECDIM1 != __SE_DECDIM_DIM0)
        params = __set_DECDIM1_WIDTH(params, pParam->DECDIM1_WIDTH);

    if (pSEFlags->DECDIM2 != __SE_DECDIM_DIM0)
        params = __set_DECDIM2_WIDTH(params, pParam->DECDIM2_WIDTH);

    if (pSEFlags->LEZR != __SE_LEZR_OFF)
        params = __set_LEZR_CNT(params, pParam->LEZR_CNT);

    params = __set_ICNT0(params, pParam->ICNT0);
    params = __set_ICNT1_DIM1(params, pParam->ICNT1, pParam->DIM1);
    params = __set_ICNT2_DIM2(params, pParam->ICNT2, pParam->DIM2);
    params = __set_ICNT3_DIM3(params, pParam->ICNT3, pParam->DIM3);
    return   __set_SE_FLAGS(params, pSEFlags, pSECFlags);
}

static __inline __STRM_TEMPLATE __se_set_param_5D(__STRM_PARAM_5D *pParam,
                                                __SE_FLAGS      *pSEFlags,
                                                __SE_CIRC_FLAGS *pSECFlags)
{
    __STRM_TEMPLATE params = (0);

    pSEFlags->DIMFMT = __SE_DIMFMT_5D;

    if (pSEFlags->DECDIM1 != __SE_DECDIM_DIM0)
        params = __set_DECDIM1_WIDTH(params, pParam->DECDIM1_WIDTH);

    if (pSEFlags->DECDIM2 != __SE_DECDIM_DIM0)
        params = __set_DECDIM2_WIDTH(params, pParam->DECDIM2_WIDTH);

    if (pSEFlags->LEZR != __SE_LEZR_OFF)
        params = __set_LEZR_CNT(params, pParam->LEZR_CNT);

    params = __set_ICNT0(params, pParam->ICNT0);
    params = __set_ICNT1_DIM1(params, pParam->ICNT1, pParam->DIM1);
    params = __set_ICNT2_DIM2(params, pParam->ICNT2, pParam->DIM2);
    params = __set_ICNT3_DIM3(params, pParam->ICNT3, pParam->DIM3);
    params = __set_ICNT4_DIM4(params, pParam->ICNT4, pParam->DIM4);
    return   __set_SE_FLAGS(params, pSEFlags, pSECFlags);
}

static __inline __STRM_TEMPLATE __se_set_param_6D(__STRM_PARAM_6D *pParam,
                                                __SE_FLAGS      *pSEFlags,
                                                __SE_CIRC_FLAGS *pSECFlags)
{
    __STRM_TEMPLATE params = (0);

    pSEFlags->DIMFMT = __SE_DIMFMT_6D;

    if (pSEFlags->DECDIM1 != __SE_DECDIM_DIM0)
        params = __set_DECDIM1_WIDTH(params, pParam->DECDIM1_WIDTH);

    if (pSEFlags->DECDIM2 != __SE_DECDIM_DIM0)
        params = __set_DECDIM2_WIDTH(params, pParam->DECDIM2_WIDTH);

    if (pSEFlags->LEZR != __SE_LEZR_OFF)
        params = __set_LEZR_CNT(params, pParam->LEZR_CNT);

    params = __set_ICNT0(params, pParam->ICNT0);
    params = __set_ICNT1_DIM1(params, pParam->ICNT1, pParam->DIM1);
    params = __set_ICNT2_DIM2(params, pParam->ICNT2, pParam->DIM2);
    params = __set_ICNT3_DIM3(params, pParam->ICNT3, pParam->DIM3);
    params = __set_ICNT4_DIM4(params, pParam->ICNT4, pParam->DIM4);
    params = __set_ICNT5_DIM5(params, pParam->ICNT5, pParam->DIM5);
    return   __set_SE_FLAGS(params, pSEFlags, pSECFlags);
}


/*****************************************************************************/
/* STREAMING ADDRESS GENERATOR COMMON CONTROLS                               */
/*****************************************************************************/

static __inline __STRM_TEMPLATE __SA_SET_PARAM_3D(__STRM_PARAM_3D *pParam,
                                                __SA_FLAGS      *pSAFlags)
{
    __STRM_TEMPLATE params = (0);

    pSAFlags->DIMFMT = __SE_DIMFMT_3D;

    if (pSAFlags->DECDIM1 != __SA_DECDIM_DIM0)
        params = __set_DECDIM1_WIDTH(params, pParam->DECDIM1_WIDTH);

    if (pSAFlags->DECDIM2 != __SA_DECDIM_DIM0)
        params = __set_DECDIM2_WIDTH(params, pParam->DECDIM2_WIDTH);

    params = __set_ICNT0(params, pParam->ICNT0);
    params = __set_ICNT1_DIM1(params, pParam->ICNT1, pParam->DIM1);
    params = __set_ICNT2_DIM2(params, pParam->ICNT2, pParam->DIM2);
    return   __set_SA_FLAGS(params, pSAFlags);
}

static __inline __STRM_TEMPLATE __SA_SET_PARAM_4D(__STRM_PARAM_4D *pParam,
                                                __SA_FLAGS      *pSAFlags)
{
    __STRM_TEMPLATE params = (0);

    pSAFlags->DIMFMT = __SE_DIMFMT_4D;

    if (pSAFlags->DECDIM1 != __SA_DECDIM_DIM0)
        params = __set_DECDIM1_WIDTH(params, pParam->DECDIM1_WIDTH);

    if (pSAFlags->DECDIM2 != __SA_DECDIM_DIM0)
        params = __set_DECDIM2_WIDTH(params, pParam->DECDIM2_WIDTH);

    params = __set_ICNT0(params, pParam->ICNT0);
    params = __set_ICNT1_DIM1(params, pParam->ICNT1, pParam->DIM1);
    params = __set_ICNT2_DIM2(params, pParam->ICNT2, pParam->DIM2);
    params = __set_ICNT3_DIM3(params, pParam->ICNT3, pParam->DIM3);
    return   __set_SA_FLAGS(params, pSAFlags);
}

static __inline __STRM_TEMPLATE __SA_SET_PARAM_5D(__STRM_PARAM_5D *pParam,
                                                __SA_FLAGS      *pSAFlags)
{
    __STRM_TEMPLATE params = (0);

    pSAFlags->DIMFMT = __SE_DIMFMT_5D;

    if (pSAFlags->DECDIM1 != __SA_DECDIM_DIM0)
        params = __set_DECDIM1_WIDTH(params, pParam->DECDIM1_WIDTH);

    if (pSAFlags->DECDIM2 != __SA_DECDIM_DIM0)
        params = __set_DECDIM2_WIDTH(params, pParam->DECDIM2_WIDTH);

    params = __set_ICNT0(params, pParam->ICNT0);
    params = __set_ICNT1_DIM1(params, pParam->ICNT1, pParam->DIM1);
    params = __set_ICNT2_DIM2(params, pParam->ICNT2, pParam->DIM2);
    params = __set_ICNT3_DIM3(params, pParam->ICNT3, pParam->DIM3);
    params = __set_ICNT4_DIM4(params, pParam->ICNT4, pParam->DIM4);
    return   __set_SA_FLAGS(params, pSAFlags);
}

static __inline __STRM_TEMPLATE __SA_SET_PARAM_6D(__STRM_PARAM_6D *pParam,
                                                __SA_FLAGS      *pSAFlags)
{
    __STRM_TEMPLATE params = (0);

    pSAFlags->DIMFMT = __SE_DIMFMT_6D;

    if (pSAFlags->DECDIM1 != __SA_DECDIM_DIM0)
        params = __set_DECDIM1_WIDTH(params, pParam->DECDIM1_WIDTH);

    if (pSAFlags->DECDIM2 != __SA_DECDIM_DIM0)
        params = __set_DECDIM2_WIDTH(params, pParam->DECDIM2_WIDTH);

    params = __set_ICNT0(params, pParam->ICNT0);
    params = __set_ICNT1_DIM1(params, pParam->ICNT1, pParam->DIM1);
    params = __set_ICNT2_DIM2(params, pParam->ICNT2, pParam->DIM2);
    params = __set_ICNT3_DIM3(params, pParam->ICNT3, pParam->DIM3);
    params = __set_ICNT4_DIM4(params, pParam->ICNT4, pParam->DIM4);
    params = __set_ICNT5_DIM5(params, pParam->ICNT5, pParam->DIM5);
    return   __set_SA_FLAGS(params, pSAFlags);
}

#endif /* __C7X_STRM_STRUCT_H */
