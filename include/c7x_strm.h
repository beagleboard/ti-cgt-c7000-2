/*****************************************************************************/
/*  C7X_STRM.H                                                               */
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
#ifndef __C7X_H_INCLUDE__
#error "This file can only be included by parent header c7x.h"
#endif

#ifndef __C7X_STRM_H
#define __C7X_STRM_H

#include <stdint.h>
#include <linkage.h>
#include <c7x_ecr.h>

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************/
/* SE/SA Feature Support                                                      */
/******************************************************************************/
#if defined(__C7100__)
  #define __SE_FEAT_TEMPLATE_V1 1
#elif defined(__C7120__) || defined(__C7502__) || defined(__C7504__) || defined(__C7508__)
  #define __SE_FEAT_TEMPLATE_V1 1
  #define __SE_FEAT_TEMPLATE_V2 1
  #define __SE_FEAT_TEMPLATE_V3 1
  #define __SE_FEAT_NONZERO_FILLVAL 1
#else
  #error "Unknown SE/SA feature configuration"
#endif

/*----------------------------------------------------------------------------*/
/* Streaming Engine element type options.                                     */
/* Use the below enumeration to indicate the element type of data read via    */
/* streaming engine.                                                          */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__)) __SE_ELETYPE
{
    __SE_ELETYPE_8BIT = 0,
    __SE_ELETYPE_16BIT = 1,
    __SE_ELETYPE_32BIT = 2,
    __SE_ELETYPE_64BIT = 3,
    /* reserved = 4 */
    /* reserved = 5 */
    /* reserved = 6 */
    /* reserved = 7 */
    __SE_ELETYPE_8BIT_CMPLX_NOSWAP = 8,
    __SE_ELETYPE_16BIT_CMPLX_NOSWAP = 9,
    __SE_ELETYPE_32BIT_CMPLX_NOSWAP = 10,
    __SE_ELETYPE_64BIT_CMPLX_NOSWAP = 11,
    __SE_ELETYPE_8BIT_CMPLX_SWAP = 12,
    __SE_ELETYPE_16BIT_CMPLX_SWAP = 13,
    __SE_ELETYPE_32BIT_CMPLX_SWAP = 14,
    __SE_ELETYPE_64BIT_CMPLX_SWAP = 15,
    __SE_ELETYPE_LAST = 15 /* Don't use directly. */
} __SE_ELETYPE;

#if defined(__SE_FEAT_TEMPLATE_V1)
/*----------------------------------------------------------------------------*/
/* Streaming Engine transpose options.                                        */
/* Use the below enumeration to indicate the transpose settings.              */
/* Transpose "GRANULES" are of below sizes only.                              */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__)) __SE_TRANSPOSE
{
    __SE_TRANSPOSE_OFF = 0,
    __SE_TRANSPOSE_8BIT = 1,
    __SE_TRANSPOSE_16BIT = 2,
    __SE_TRANSPOSE_32BIT = 3,
    __SE_TRANSPOSE_64BIT = 4,
    __SE_TRANSPOSE_128BIT = 5,
    __SE_TRANSPOSE_256BIT = 6,
    /* reserved = 7 */
    __SE_TRANSPOSE_LAST = 7 /* Don't use directly. */
} __SE_TRANSPOSE;
#endif /* __SE_FEAT_TEMPLATE_V1 */

/*----------------------------------------------------------------------------*/
/* Streaming Engine promote options.                                          */
/* Single power of 2 promotes are possible using below options.               */
/* Additionally the promotes can be sign or zero extended.                    */
/* Ex. If ELETYPE is 8bit the promoting it would result in 16 bit data.       */
/*----------------------------------------------------------------------------*/
/* When using __SE_FILLVAL_MIN or __SE_FILLVAL_MAX, specify __SE_PROMOTE_OFF  */
/* to generate an unsigned min or max. Specify __SE_PROMOTE_OFF_SIGNED to     */
/* generate a signed min or max. Otherwise, __SE_PROMOTE_OFF_SIGNED behaves   */
/* identically to __SE_PROMOTE_OFF.                                           */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__)) __SE_PROMOTE
{
    __SE_PROMOTE_OFF = 0,
    __SE_PROMOTE_2X_ZEROEXT = 1,
    __SE_PROMOTE_4X_ZEROEXT = 2,
    __SE_PROMOTE_8X_ZEROEXT = 3,
#if defined(__SE_FEAT_NONZERO_FILLVAL)
    __SE_PROMOTE_OFF_SIGNED = 4,
#endif /* __SE_FEAT_NONZERO_FILLVAL */
    __SE_PROMOTE_2X_SIGNEXT = 5,
    __SE_PROMOTE_4X_SIGNEXT = 6,
    __SE_PROMOTE_8X_SIGNEXT = 7,
    __SE_PROMOTE_LAST = 7 /* Don't use directly. */
} __SE_PROMOTE;

/*----------------------------------------------------------------------------*/
/* Streaming Engine vector lengths.                                           */
/* Use the below enumeration to indicate the vector lengths in powers of two. */
/* The vector lengths should be in multiples of ELETYPE.                      */
/* Ex. If the vector length is __SE_VECLEN_4ELEMS and __SE_ELETYPE_16BIT then */
/*     the data in the holding registers will contain 4 16 bit values for     */
/*     each SE advance. The rest of the SB0, SB1 register will be zeroed out. */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__)) __SE_VECLEN
{
    __SE_VECLEN_1ELEM = 0,
    __SE_VECLEN_2ELEMS = 1,
    __SE_VECLEN_4ELEMS = 2,
    __SE_VECLEN_8ELEMS = 3,
    __SE_VECLEN_16ELEMS = 4,
    __SE_VECLEN_32ELEMS = 5,
    __SE_VECLEN_64ELEMS = 6,
    /* reserved = 7 */
    __SE_VECLEN_LAST = 7 /* Don't use directly. */
} __SE_VECLEN;

#if defined(__SE_FEAT_TEMPLATE_V1)
/*----------------------------------------------------------------------------*/
/* Streaming Engine element duplication.                                      */
/* Use the below enumeration to duplicate the vector elements in powers of    */
/* two, 2x, 4x, 8x, 16x, 32x, 64x (subject to ELETYPE).                       */
/* Ex. Using __SE_ELEDUP_32X for a ELETYPE_16BIT duplicates 16bit elements    */
/*     32 times in SB0/SB1 double vector.                                     */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__)) __SE_ELEDUP
{
    __SE_ELEDUP_OFF = 0,
    __SE_ELEDUP_2X = 1,
    __SE_ELEDUP_4X = 2,
    __SE_ELEDUP_8X = 3,
    __SE_ELEDUP_16X = 4,
    __SE_ELEDUP_32X = 5,
    __SE_ELEDUP_64X = 6,
    /* reserved = 7 */
    __SE_ELEDUP_LAST = 7 /* Don't use directly. */
} __SE_ELEDUP;
#endif /* __SE_FEAT_TEMPLATE_V1 */

#if defined(__SE_FEAT_TEMPLATE_V1)
/*----------------------------------------------------------------------------*/
/* Streaming Engine group duplication.                                        */
/* Depending on the vector lengths, enabling group duplication will fill up   */
/* 512bit holding registers with multiple copies.                             */
/* Ex. For __SE_ELETYPE_8BIT and __SE_VECLEN_4ELEMS with group duplication    */
/*     enabled, the streaming engine duplicates the 4 bytes in LSB 16 times   */
/*     to fill up the 512 bit vector holding register.                        */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__)) __SE_GRPDUP
{
    __SE_GRPDUP_OFF = 0,
    __SE_GRPDUP_ON = 1,
    __SE_GRPDUP_LAST = 1 /* Don't use directly. */
} __SE_GRPDUP;
#endif /* __SE_FEAT_TEMPLATE_V1 */

/*----------------------------------------------------------------------------*/
/* Streaming Engine decimation flags.                                         */
/* Use the below enumerations to indicate if the SE should decimate (only     */
/* keep every nth element.)                                                   */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__)) __SE_DECIM
{
    __SE_DECIM_OFF = 0,
    __SE_DECIM_2 = 1,
    __SE_DECIM_4 = 2,
    /* reserved = 3 */
    __SE_DECIM_LAST = 3 /* Don't use directly. */
} __SE_DECIM;

/*----------------------------------------------------------------------------*/
/* Streaming Engine fillval options.                                          */
/* Specifies the padding method for use with DECDIM, SPAD, LEZR, end of ICNT, */
/* or end of stream. If VECLEN does not fill all lanes of data and GRPDUP is  */
/* not enabled, the SE will only fill masked elements within VECLEN with      */
/* non-zero data. Elements outside of VECLEN will still be filled with 0s.    */
/*----------------------------------------------------------------------------*/
/* When using __SE_FILLVAL_USER, the fill value must be set in the            */
/* corresponding sideband ECR before opening the stream. The sideband ECRs    */
/* are:                                                                       */
/* - __ECR_SE0_SBND                                                           */
/* - __ECR_SE1_SBND                                                           */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__)) __SE_FILLVAL
{
    __SE_FILLVAL_ZERO = 0,
#if defined(__SE_FEAT_NONZERO_FILLVAL)
    __SE_FILLVAL_USER = 1,
    __SE_FILLVAL_MIN = 2,
    __SE_FILLVAL_MAX = 3,
#endif /* __SE_FEAT_NONZERO_FILLVAL */
    __SE_FILLVAL_LAST = 3 /* Don't use directly. */
} __SE_FILLVAL;

/*----------------------------------------------------------------------------*/
/* Template format selection for Streaming Engine                             */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__)) __SE_DIMFMT
{
    __SE_DIMFMT_1D = 0,
    __SE_DIMFMT_2D = 1,
    __SE_DIMFMT_3D = 2,
    __SE_DIMFMT_4D = 3,
    __SE_DIMFMT_5D = 4,
    __SE_DIMFMT_6D = 5,
    /* reserved = 6 */
    /* reserved = 7 */
    __SE_DIMFMT_LAST = 7 /* Don't use directly. */
} __SE_DIMFMT;

#if defined(__SE_FEAT_TEMPLATE_V1)
/*----------------------------------------------------------------------------*/
/* Streaming Engine increment/decrement directions.                           */
/* Use the below enumerations as needed to indicate the direction of transfer.*/
/* Setting to _INC mode increments the resulting address.                     */
/* Setting to _DEC mode decrements the resulting address.                     */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__)) __SE_DIR
{
    __SE_DIR_INC = 0,
    __SE_DIR_DEC = 1,
    __SE_DIR_LAST = 1 /* Don't use directly. */
} __SE_DIR;
#endif /* __SE_FEAT_TEMPLATE_V1 */

/*----------------------------------------------------------------------------*/
/* Streaming Engine Addressing Mode selection options.                        */
/* Choose either linear addressing or use CBK0 or CBK0+CBK1+1                 */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__)) __SE_AM
{
    __SE_AM_LINEAR = 0,
    __SE_AM_CIRC_CBK0 = 1,
    __SE_AM_CIRC_CBK1 = 2,
    /* reserved = 3 */
    __SE_AM_LAST = 3 /* Don't use directly. */
} __SE_AM;

/*----------------------------------------------------------------------------*/
/* Streaming Engine Data Strip Mining Decrement Dimension for innermost ICNT0 */
/* In this mode, the current I0 count is NOT reloaded with ICNT0 when each    */
/* dimension expires. Rather, when the selected DECDIM dimension is entered,  */
/* the current I0 count is decremented by the value of VECLEN when in Linear  */
/* Stream mode, or decremented by the GRANULE value when in Transpose Mode.   */
/* The I0 count is only reloaded when the selected DECDIM dimension expires,  */
/* or a dimension higher above it expires.                                    */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__)) __SE_DECDIM
{
    __SE_DECDIM_DIM0 = 0,
    __SE_DECDIM_DIM1 = 1,
    __SE_DECDIM_DIM2 = 2,
    __SE_DECDIM_DIM3 = 3,
    __SE_DECDIM_DIM4 = 4,
    __SE_DECDIM_DIM5 = 5,
    /* reserved = 6 */
    /* reserved = 7 */
    __SE_DECDIM_LAST = 7 /* Don't use directly. */
} __SE_DECDIM;

#if defined(__SE_FEAT_TEMPLATE_V3)
/*----------------------------------------------------------------------------*/
/* Streaming Engine SPAD Horizontal Block Dimension                           */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__)) __SE_SPAD_HORIZONTAL_BLOCK_DIM
{
    __SE_SPAD_HORIZONTAL_BLOCK_DIM0 = 0,
    __SE_SPAD_HORIZONTAL_BLOCK_DIM1 = 1,
    __SE_SPAD_HORIZONTAL_BLOCK_DIM2 = 2,
    __SE_SPAD_HORIZONTAL_BLOCK_DIM3 = 3,
    __SE_SPAD_HORIZONTAL_BLOCK_DIM4 = 4,
    __SE_SPAD_HORIZONTAL_BLOCK_DIM5 = 5,
    /* reserved = 6 */
    /* reserved = 7 */
    __SE_SPAD_HORIZONTAL_BLOCK_DIM_LAST = 7 /* Don't use directly. */
} __SE_SPAD_HORIZONTAL_BLOCK_DIM;
#endif /* __SE_FEAT_TEMPLATE_V3 */

/*----------------------------------------------------------------------------*/
/* Streaming Engine Secondary Data Strip Mining Decrement Dimension           */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__)) __SE_DECDIMSD
{
    __SE_DECDIMSD_DIM0 = 0,
    __SE_DECDIMSD_DIM1 = 1,
    __SE_DECDIMSD_DIM2 = 2,
    __SE_DECDIMSD_DIM3 = 3,
    __SE_DECDIMSD_LAST = 3 /* Don't use directly. */
} __SE_DECDIMSD;

#if defined(__SE_FEAT_TEMPLATE_V3)
/*----------------------------------------------------------------------------*/
/* Streaming Engine SPAD Horizontal Pixel Dimension                           */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__)) __SE_SPAD_HORIZONTAL_PIXEL_DIM
{
    __SE_SPAD_HORIZONTAL_PIXEL_DIM0 = 0,
    __SE_SPAD_HORIZONTAL_PIXEL_DIM1 = 1,
    __SE_SPAD_HORIZONTAL_PIXEL_DIM2 = 2,
    __SE_SPAD_HORIZONTAL_PIXEL_DIM3 = 3,
    __SE_SPAD_HORIZONTAL_PIXEL_DIM_LAST = 3 /* Don't use directly. */
} __SE_SPAD_HORIZONTAL_PIXEL_DIM;
#endif /* __SE_FEAT_TEMPLATE_V3 */

/*----------------------------------------------------------------------------*/
/* Selected Loop Dimension Count End, and Start Sending Zero-Padded Vectors   */
/* to CPU.  The number of zero-padded vectors sent to CPU is defined by the   */
/* LEZR_CNT field in the template.  Supported in Linear Stream Mode only.     */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__)) __SE_LEZR
{
    __SE_LEZR_OFF = 0,
    __SE_LEZR_ICNT0 = 1,
    __SE_LEZR_ICNT1 = 2,
    __SE_LEZR_ICNT2 = 3,
    __SE_LEZR_ICNT3 = 4,
    __SE_LEZR_ICNT4 = 5,
    __SE_LEZR_ICNT5 = 6,
    /* reserved = 7 */
    __SE_LEZR_LAST = 7 /* Don't use directly. */
} __SE_LEZR;

/*----------------------------------------------------------------------------*/
/* Streaming Engine DECDIM field mode.                                        */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__)) __SE_DECDIM2_MODE
{
    __SE_DECDIM2_MODE_NORMAL = 0,
    __SE_DECDIM2_MODE_HORIZ_ZERO_PAD = 1,
    __SE_DECDIM2_MODE_LAST = 1 /* Don't use directly. */
} __SE_DECDIM2_MODE;

/*----------------------------------------------------------------------------*/
/* Streaming Engine template format.                                          */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__)) __SE_TEMPLATE_FMT
{
#if defined(__SE_FEAT_TEMPLATE_V1)
    __SE_TEMPLATE_FMT_v1 = 0,
#endif /* __SE_FEAT_TEMPLATE_V1 */
#if defined(__SE_FEAT_TEMPLATE_V2)
    __SE_TEMPLATE_FMT_v2 = 1,
#endif /* __SE_FEAT_TEMPLATE_V2 */
#if defined(__SE_FEAT_TEMPLATE_V3)
    __SE_TEMPLATE_FMT_v3 = 1, /* Duplicate encoding */
#endif /* __SE_FEAT_TEMPLATE_V3 */
    /* reserved = 2 */
    /* reserved = 3 */
    /* reserved = 4 */
    /* reserved = 5 */
    /* reserved = 6 */
    __SE_TEMPLATE_FMT_LAST = 7 /* Don't use directly. */
} __SE_TEMPLATE_FMT;

#if defined(__SE_FEAT_TEMPLATE_V1)
/*----------------------------------------------------------------------------*/
/* __SE_TEMPLATE_v1 struct for use with SE initialization via __SEn_OPEN()    */
/* intrinsics.                                                                */
/*----------------------------------------------------------------------------*/
typedef struct __attribute__((__packed__)) __SE_TEMPLATE_v1
{
#if __little_endian__
    uint64_t ICNT0:32;
    uint64_t ICNT1:32;
    uint64_t ICNT2:32;
    uint64_t ICNT3:32;
    uint64_t ICNT4:32;
    uint64_t ICNT5:32;
    uint64_t DECDIM1_WIDTH:32;
    uint64_t DECDIM2_WIDTH:32;
    int64_t  DIM1:32;
    int64_t  DIM2:32;
    int64_t  DIM3:32;
    int64_t  DIM4:32;
    int64_t  DIM5:32;
    uint64_t LEZR_CNT:8;
    uint64_t _reserved1:24;
    /* Flags */
    __SE_ELETYPE ELETYPE:4;
    __SE_TRANSPOSE TRANSPOSE:3;
    uint64_t _reserved2:1;
    __SE_PROMOTE PROMOTE:3;
    uint64_t _reserved3:1;
    __SE_VECLEN VECLEN:3;
    uint64_t _reserved4:1;
    __SE_ELEDUP ELEDUP:3;
    __SE_GRPDUP GRPDUP:1;
    __SE_DECIM DECIM:2;
    __SE_FILLVAL FILLVAL:2;
    __SE_DIMFMT DIMFMT:3;
    __SE_DIR DIR:1;
    uint64_t CBK0:4;
    uint64_t CBK1:4;
    __SE_AM AM0:2;
    __SE_AM AM1:2;
    __SE_AM AM2:2;
    __SE_AM AM3:2;
    __SE_AM AM4:2;
    __SE_AM AM5:2;
    __SE_DECDIM DECDIM1:3;
    __SE_DECDIMSD DECDIM1SD:2;
    __SE_DECDIM DECDIM2:3;
    __SE_DECDIMSD DECDIM2SD:2;
    __SE_LEZR LEZR:3;
    __SE_TEMPLATE_FMT TEMPLATE_FMT:3;
#else
    /* Invert on 64 bit boundaries */
    uint64_t ICNT1:32;
    uint64_t ICNT0:32;

    uint64_t ICNT3:32;
    uint64_t ICNT2:32;

    uint64_t ICNT5:32;
    uint64_t ICNT4:32;

    uint64_t DECDIM2_WIDTH:32;
    uint64_t DECDIM1_WIDTH:32;

    int64_t  DIM2:32;
    int64_t  DIM1:32;

    int64_t  DIM4:32;
    int64_t  DIM3:32;

    uint64_t _reserved1:24;
    uint64_t LEZR_CNT:8;
    int64_t  DIM5:32;

    /* Flags */
    __SE_TEMPLATE_FMT TEMPLATE_FMT:3;
    __SE_LEZR LEZR:3;
    __SE_DECDIMSD DECDIM2SD:2;
    __SE_DECDIM DECDIM2:3;
    __SE_DECDIMSD DECDIM1SD:2;
    __SE_DECDIM DECDIM1:3;
    __SE_AM AM5:2;
    __SE_AM AM4:2;
    __SE_AM AM3:2;
    __SE_AM AM2:2;
    __SE_AM AM1:2;
    __SE_AM AM0:2;
    uint64_t CBK1:4;
    uint64_t CBK0:4;
    __SE_DIR DIR:1;
    __SE_DIMFMT DIMFMT:3;
    __SE_FILLVAL FILLVAL:2;
    __SE_DECIM DECIM:2;
    __SE_GRPDUP GRPDUP:1;
    __SE_ELEDUP ELEDUP:3;
    uint64_t _reserved4:1;
    __SE_VECLEN VECLEN:3;
    uint64_t _reserved3:1;
    __SE_PROMOTE PROMOTE:3;
    uint64_t _reserved2:1;
    __SE_TRANSPOSE TRANSPOSE:3;
    __SE_ELETYPE ELETYPE:4;
#endif
} __SE_TEMPLATE_v1;
#endif /* __SE_FEAT_TEMPLATE_V1 */

#if defined(__SE_FEAT_TEMPLATE_V2)
/*----------------------------------------------------------------------------*/
/* __SE_TEMPLATE_v2 struct for use with SE initialization via __SEnOPEN()     */
/* intrinsics.                                                                */
/*----------------------------------------------------------------------------*/
typedef struct __attribute__((__packed__)) __SE_TEMPLATE_v2
{
#if __little_endian__
    uint64_t ICNT0:16;
    uint64_t SPAD_PAD_WIDTH:16;
    uint64_t ICNT1:16;
    uint64_t INVERSE_DECDIM1_WIDTH:16;
    uint64_t ICNT2:16;
    uint64_t INVERSE_DECDIM2_WIDTH:16;
    uint64_t ICNT3:32;
    uint64_t ICNT4:32;
    uint64_t ICNT5:32;
    uint64_t DECDIM1_WIDTH:32;
    uint64_t DECDIM2_WIDTH:32;
    int64_t  DIM1:32;
    int64_t  DIM2:32;
    int64_t  DIM3:32;
    int64_t  DIM4:32;
    int64_t  DIM5:32;
    uint64_t LEZR_CNT:8;
    uint64_t _reserved1:24;
    /* Flags */
    __SE_ELETYPE ELETYPE:4;
    uint64_t _reserved2:4;
    __SE_PROMOTE PROMOTE:3;
    uint64_t _reserved3:1;
    __SE_VECLEN VECLEN:3;
    uint64_t _reserved4:1;
    uint64_t _reserved5:4;
    __SE_DECIM DECIM:2;
    __SE_FILLVAL FILLVAL:2;
    __SE_DIMFMT DIMFMT:3;
    __SE_DECDIM2_MODE DECDIM2_MODE:1;
    uint64_t CBK0:4;
    uint64_t CBK1:4;
    __SE_AM AM0:2;
    __SE_AM AM1:2;
    __SE_AM AM2:2;
    __SE_AM AM3:2;
    __SE_AM AM4:2;
    __SE_AM AM5:2;
    __SE_DECDIM DECDIM1:3;
    __SE_DECDIMSD DECDIM1SD:2;
    __SE_DECDIM DECDIM2:3;
    __SE_DECDIMSD DECDIM2SD:2;
    __SE_LEZR LEZR:3;
    __SE_TEMPLATE_FMT TEMPLATE_FMT:3;
#else
    /* Invert on 64 bit boundaries */
    uint64_t INVERSE_DECDIM1_WIDTH:16;
    uint64_t ICNT1:16;
    uint64_t SPAD_PAD_WIDTH:16;
    uint64_t ICNT0:16;

    uint64_t ICNT3:32;
    uint64_t INVERSE_DECDIM2_WIDTH:16;
    uint64_t ICNT2:16;

    uint64_t ICNT5:32;
    uint64_t ICNT4:32;

    uint64_t DECDIM2_WIDTH:32;
    uint64_t DECDIM1_WIDTH:32;

    int64_t  DIM2:32;
    int64_t  DIM1:32;

    int64_t  DIM4:32;
    int64_t  DIM3:32;

    uint64_t _reserved1:24;
    uint64_t LEZR_CNT:8;
    int64_t  DIM5:32;

    /* Flags */
    __SE_TEMPLATE_FMT TEMPLATE_FMT:3;
    __SE_LEZR LEZR:3;
    __SE_DECDIMSD DECDIM2SD:2;
    __SE_DECDIM DECDIM2:3;
    __SE_DECDIMSD DECDIM1SD:2;
    __SE_DECDIM DECDIM1:3;
    __SE_AM AM5:2;
    __SE_AM AM4:2;
    __SE_AM AM3:2;
    __SE_AM AM2:2;
    __SE_AM AM1:2;
    __SE_AM AM0:2;
    uint64_t CBK1:4;
    uint64_t CBK0:4;
    __SE_DECDIM2_MODE DECDIM2_MODE:1;
    __SE_DIMFMT DIMFMT:3;
    __SE_FILLVAL FILLVAL:2;
    __SE_DECIM DECIM:2;
    uint64_t _reserved5:4;
    uint64_t _reserved4:1;
    __SE_VECLEN VECLEN:3;
    uint64_t _reserved3:1;
    __SE_PROMOTE PROMOTE:3;
    uint64_t _reserved2:4;
    __SE_ELETYPE ELETYPE:4;
#endif
} __SE_TEMPLATE_v2;
#endif /* __SE_FEAT_TEMPLATE_V2 */

#if defined(__SE_FEAT_TEMPLATE_V3)
/*----------------------------------------------------------------------------*/
/* __SE_TEMPLATE_v3 struct for use with SE initialization via __SEnOPEN()     */
/* intrinsics.                                                                */
/*----------------------------------------------------------------------------*/
typedef struct __attribute__((__packed__)) __SE_TEMPLATE_v3
{
#if __little_endian__
    uint64_t ICNT0:16;
    uint64_t SPAD_PAD_WIDTH:16;
    uint64_t ICNT1:16;
    uint64_t INVERSE_DECDIM1_WIDTH:16;
    uint64_t ICNT2:16;
    uint64_t SPAD_STARTING_OFFSET:16;
    uint64_t ICNT3:32;
    uint64_t ICNT4:32;
    uint64_t ICNT5:32;
    uint64_t DECDIM1_WIDTH:32;
    uint64_t SPAD_HORIZONTAL_WIDTH:16;
    uint64_t _reserved0:16;
    int64_t  DIM1:32;
    int64_t  DIM2:32;
    int64_t  DIM3:32;
    int64_t  DIM4:32;
    int64_t  DIM5:32;
    uint64_t LEZR_CNT:8;
    uint64_t _reserved1:24;
    /* Flags */
    __SE_ELETYPE ELETYPE:4;
    uint64_t _reserved2:4;
    __SE_PROMOTE PROMOTE:3;
    uint64_t _reserved3:1;
    __SE_VECLEN VECLEN:3;
    uint64_t _reserved4:1;
    uint64_t _reserved5:4;
    __SE_DECIM DECIM:2;
    __SE_FILLVAL FILLVAL:2;
    __SE_DIMFMT DIMFMT:3;
    __SE_DECDIM2_MODE DECDIM2_MODE:1;
    uint64_t CBK0:4;
    uint64_t CBK1:4;
    __SE_AM AM0:2;
    __SE_AM AM1:2;
    __SE_AM AM2:2;
    __SE_AM AM3:2;
    __SE_AM AM4:2;
    __SE_AM AM5:2;
    __SE_DECDIM DECDIM1:3;
    __SE_DECDIMSD DECDIM1SD:2;
    __SE_SPAD_HORIZONTAL_BLOCK_DIM SPAD_HORIZONTAL_BLOCK_DIM:3;
    __SE_SPAD_HORIZONTAL_PIXEL_DIM SPAD_HORIZONTAL_PIXEL_DIM:2;
    __SE_LEZR LEZR:3;
    __SE_TEMPLATE_FMT TEMPLATE_FMT:3;
#else
    /* Invert on 64 bit boundaries */
    uint64_t INVERSE_DECDIM1_WIDTH:16;
    uint64_t ICNT1:16;
    uint64_t SPAD_PAD_WIDTH:16;
    uint64_t ICNT0:16;

    uint64_t ICNT3:32;
    uint64_t SPAD_STARTING_OFFSET:16;
    uint64_t ICNT2:16;

    uint64_t ICNT5:32;
    uint64_t ICNT4:32;

    uint64_t _reserved0:16;
    uint64_t SPAD_HORIZONTAL_WIDTH:16;
    uint64_t DECDIM1_WIDTH:32;

    int64_t  DIM2:32;
    int64_t  DIM1:32;

    int64_t  DIM4:32;
    int64_t  DIM3:32;

    uint64_t _reserved1:24;
    uint64_t LEZR_CNT:8;
    int64_t  DIM5:32;

    /* Flags */
    __SE_TEMPLATE_FMT TEMPLATE_FMT:3;
    __SE_LEZR LEZR:3;
    __SE_SPAD_HORIZONTAL_PIXEL_DIM SPAD_HORIZONTAL_PIXEL_DIM:2;
    __SE_SPAD_HORIZONTAL_BLOCK_DIM SPAD_HORIZONTAL_BLOCK_DIM:3;
    __SE_DECDIMSD DECDIM1SD:2;
    __SE_DECDIM DECDIM1:3;
    __SE_AM AM5:2;
    __SE_AM AM4:2;
    __SE_AM AM3:2;
    __SE_AM AM2:2;
    __SE_AM AM1:2;
    __SE_AM AM0:2;
    uint64_t CBK1:4;
    uint64_t CBK0:4;
    __SE_DECDIM2_MODE DECDIM2_MODE:1;
    __SE_DIMFMT DIMFMT:3;
    __SE_FILLVAL FILLVAL:2;
    __SE_DECIM DECIM:2;
    uint64_t _reserved5:4;
    uint64_t _reserved4:1;
    __SE_VECLEN VECLEN:3;
    uint64_t _reserved3:1;
    __SE_PROMOTE PROMOTE:3;
    uint64_t _reserved2:4;
    __SE_ELETYPE ELETYPE:4;
#endif
} __SE_TEMPLATE_v3;
#endif /* __SE_FEAT_TEMPLATE_V3 */

/*----------------------------------------------------------------------------*/
/* Stream Address Generator vector lengths.                                   */
/* Use the below enumerations to indicate the vector lengths in elements.     */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__)) __SA_VECLEN
{
    __SA_VECLEN_1ELEM = 0,
    __SA_VECLEN_2ELEMS = 1,
    __SA_VECLEN_4ELEMS = 2,
    __SA_VECLEN_8ELEMS = 3,
    __SA_VECLEN_16ELEMS = 4,
    __SA_VECLEN_32ELEMS = 5,
    __SA_VECLEN_64ELEMS = 6,
    /* reserved = 7 */
    __SA_VECLEN_LAST = 7 /* Don't use directly. */
} __SA_VECLEN;

typedef enum __attribute__((__packed__)) __SA_INV_DD
{
    __SA_INV_DD_OFF = 0,
    __SA_INV_DD_ON = 1,
    __SA_INV_DD_LAST = 1 /* Don't use directly. */
} __SA_INV_DD;

/*----------------------------------------------------------------------------*/
/* Template format selection for Stream Address Generator                     */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__)) __SA_DIMFMT
{
    __SA_DIMFMT_1D = 0,
    __SA_DIMFMT_2D = 1,
    __SA_DIMFMT_3D = 2,
    __SA_DIMFMT_4D = 3,
    __SA_DIMFMT_5D = 4,
    __SA_DIMFMT_6D = 5,
    /* reserved = 6 */
    /* reserved = 7 */
    __SA_DIMFMT_LAST = 7 /* Don't use directly. */
} __SA_DIMFMT;

/*----------------------------------------------------------------------------*/
/* Stream Address Generator Data Strip Mining Decrement Dimension for ICNT0   */
/* In this mode, the current I0 count is NOT reloaded with ICNT0 when each    */
/* dimension expires.  The I0 count is only reloaded when the selected DECDIM */
/* dimension expires, or a dimension higher above it expires.                 */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__)) __SA_DECDIM
{
    __SA_DECDIM_DIM0 = 0,
    __SA_DECDIM_DIM1 = 1,
    __SA_DECDIM_DIM2 = 2,
    __SA_DECDIM_DIM3 = 3,
    __SA_DECDIM_DIM4 = 4,
    __SA_DECDIM_DIM5 = 5,
    /* reserved = 6 */
    /* reserved = 7 */
    __SA_DECDIM_LAST = 7 /* Don't use directly. */
} __SA_DECDIM;

/*----------------------------------------------------------------------------*/
/* Stream Address Generator Secondary Data Strip Mining Decrement Dimension   */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__)) __SA_DECDIMSD
{
    __SA_DECDIMSD_DIM0 = 0,
    __SA_DECDIMSD_DIM1 = 1,
    __SA_DECDIMSD_DIM2 = 2,
    __SA_DECDIMSD_DIM3 = 3,
    __SA_DECDIMSD_LAST = 3 /* Don't use directly. */
} __SA_DECDIMSD;

/*----------------------------------------------------------------------------*/
/* __SA_TEMPLATE_v1 struct for use with SA initialization via __SAn_OPEN      */
/* intrinsics.                                                                */
/*----------------------------------------------------------------------------*/
typedef struct __attribute__((__packed__)) __SA_TEMPLATE_v1
{
#if __little_endian__
    uint64_t ICNT0:32;
    uint64_t ICNT1:32;
    uint64_t ICNT2:32;
    uint64_t ICNT3:32;
    uint64_t ICNT4:32;
    uint64_t ICNT5:32;
    uint64_t DECDIM1_WIDTH:32;
    uint64_t DECDIM2_WIDTH:32;
    int64_t  DIM1:32;
    int64_t  DIM2:32;
    int64_t  DIM3:32;
    int64_t  DIM4:32;
    int64_t  DIM5:32;
    uint64_t DECDIM3_WIDTH:32;
    /* Flags */
    uint64_t _reserved2:12;
    __SA_VECLEN VECLEN:3;
    uint64_t _reserved3:6;
    __SA_INV_DD INV_DD3:1;
    __SA_INV_DD INV_DD1:1;
    __SA_INV_DD INV_DD2:1;
    __SA_DIMFMT DIMFMT:3;
    uint64_t _reserved4:5;
    uint64_t _reserved5:11;
    __SA_DECDIM DECDIM3:3;
    __SA_DECDIMSD DECDIM3SD:2;
    __SA_DECDIM DECDIM1:3;
    __SA_DECDIMSD DECDIM1SD:2;
    __SA_DECDIM DECDIM2:3;
    __SA_DECDIMSD DECDIM2SD:2;
    uint64_t _reserved:6;
#else
    /* Invert on 64 bit boundaries. */
    uint64_t ICNT1:32;
    uint64_t ICNT0:32;

    uint64_t ICNT3:32;
    uint64_t ICNT2:32;

    uint64_t ICNT5:32;
    uint64_t ICNT4:32;

    uint64_t DECDIM2_WIDTH:32;
    uint64_t DECDIM1_WIDTH:32;

    int64_t  DIM2:32;
    int64_t  DIM1:32;

    int64_t  DIM4:32;
    int64_t  DIM3:32;

    uint64_t DECDIM3_WIDTH:32;
    int64_t  DIM5:32;

    /* Flags */
    uint64_t _reserved:6;
    __SA_DECDIMSD DECDIM2SD:2;
    __SA_DECDIM DECDIM2:3;
    __SA_DECDIMSD DECDIM1SD:2;
    __SA_DECDIM DECDIM1:3;
    __SA_DECDIMSD DECDIM3SD:2;
    __SA_DECDIM DECDIM3:3;
    uint64_t _reserved5:11;
    uint64_t _reserved4:5;
    __SA_DIMFMT DIMFMT:3;
    __SA_INV_DD INV_DD2:1;
    __SA_INV_DD INV_DD1:1;
    __SA_INV_DD INV_DD3:1;
    uint64_t _reserved3:6;
    __SA_VECLEN VECLEN:3;
    uint64_t _reserved2:12;
#endif
} __SA_TEMPLATE_v1;

#if defined(__SE_FEAT_TEMPLATE_V1)
/*----------------------------------------------------------------------------*/
/* Generate an __SE_TEMPLATE_v1 with safe default values.                     */
/*----------------------------------------------------------------------------*/
_IDEFN __SE_TEMPLATE_v1 __attribute__((__always_inline__)) __gen_SE_TEMPLATE_v1()
{
    const __SE_TEMPLATE_v1 se =
    {
#if __little_endian__
        /* ICNT0            = */ 0,
        /* ICNT1            = */ 0,
        /* ICNT2            = */ 0,
        /* ICNT3            = */ 0,
        /* ICNT4            = */ 0,
        /* ICNT5            = */ 0,
        /* DECDIM1_WIDTH    = */ 0,
        /* DECDIM2_WIDTH    = */ 0,
        /* DIM1             = */ 0,
        /* DIM2             = */ 0,
        /* DIM3             = */ 0,
        /* DIM4             = */ 0,
        /* DIM5             = */ 0,
        /* LEZR_CN          = */ 0,
        /* _reserved1       = */ 0,
        /*** Flags ***/
        /* ELETYPE          = */ __SE_ELETYPE_8BIT,
        /* TRANSPOSE        = */ __SE_TRANSPOSE_OFF,
        /* _reserved2       = */ 0,
        /* PROMOTE          = */ __SE_PROMOTE_OFF,
        /* _reserved3       = */ 0,
        /* VECLEN           = */ __SE_VECLEN_64ELEMS,
        /* _reserved4       = */ 0,
        /* ELEDUP           = */ __SE_ELEDUP_OFF,
        /* GRPDUP           = */ __SE_GRPDUP_OFF,
        /* DECIM            = */ __SE_DECIM_OFF,
        /* FILLVAL          = */ __SE_FILLVAL_ZERO,
        /* DIMFMT           = */ __SE_DIMFMT_1D,
        /* DIR              = */ __SE_DIR_INC,
        /* CBK0             = */ 0,
        /* CBK1             = */ 0,
        /* AM0              = */ __SE_AM_LINEAR,
        /* AM1              = */ __SE_AM_LINEAR,
        /* AM2              = */ __SE_AM_LINEAR,
        /* AM3              = */ __SE_AM_LINEAR,
        /* AM4              = */ __SE_AM_LINEAR,
        /* AM5              = */ __SE_AM_LINEAR,
        /* DECDIM1          = */ __SE_DECDIM_DIM0,
        /* DECDIM1SD        = */ __SE_DECDIMSD_DIM0,
        /* DECDIM2          = */ __SE_DECDIM_DIM0,
        /* DECDIM2SD        = */ __SE_DECDIMSD_DIM0,
        /* LEZR             = */ __SE_LEZR_OFF,
        /* TEMPLATE_FMT     = */ __SE_TEMPLATE_FMT_v1
#else
        /* Invert on 64 bit boundaries */
        /* ICNT1            = */ 0,
        /* ICNT0            = */ 0,

        /* ICNT3            = */ 0,
        /* ICNT2            = */ 0,

        /* ICNT5            = */ 0,
        /* ICNT4            = */ 0,

        /* DECDIM2_WIDTH    = */ 0,
        /* DECDIM1_WIDTH    = */ 0,

        /* DIM2             = */ 0,
        /* DIM1             = */ 0,

        /* DIM4             = */ 0,
        /* DIM3             = */ 0,

        /* _reserved1       = */ 0,
        /* LEZR_CN          = */ 0,
        /* DIM5             = */ 0,

        /*** Flags ***/
        /* TEMPLATE_FMT     = */ __SE_TEMPLATE_FMT_v1,
        /* LEZR             = */ __SE_LEZR_OFF,
        /* DECDIM2SD        = */ __SE_DECDIMSD_DIM0,
        /* DECDIM2          = */ __SE_DECDIM_DIM0,
        /* DECDIM1SD        = */ __SE_DECDIMSD_DIM0,
        /* DECDIM1          = */ __SE_DECDIM_DIM0,
        /* AM5              = */ __SE_AM_LINEAR,
        /* AM4              = */ __SE_AM_LINEAR,
        /* AM3              = */ __SE_AM_LINEAR,
        /* AM2              = */ __SE_AM_LINEAR,
        /* AM1              = */ __SE_AM_LINEAR,
        /* AM0              = */ __SE_AM_LINEAR,
        /* CBK1             = */ 0,
        /* CBK0             = */ 0,
        /* DIR              = */ __SE_DIR_INC,
        /* DIMFMT           = */ __SE_DIMFMT_1D,
        /* FILLVAL          = */ __SE_FILLVAL_ZERO,
        /* DECIM            = */ __SE_DECIM_OFF,
        /* GRPDUP           = */ __SE_GRPDUP_OFF,
        /* ELEDUP           = */ __SE_ELEDUP_OFF,
        /* _reserved4       = */ 0,
        /* VECLEN           = */ __SE_VECLEN_64ELEMS,
        /* _reserved3       = */ 0,
        /* PROMOTE          = */ __SE_PROMOTE_OFF,
        /* _reserved2       = */ 0,
        /* TRANSPOSE        = */ __SE_TRANSPOSE_OFF,
        /* ELETYPE          = */ __SE_ELETYPE_8BIT
#endif
    };
    return se;
}
#endif /* __SE_FEAT_TEMPLATE_V1 */

#if defined(__SE_FEAT_TEMPLATE_V2)
/*----------------------------------------------------------------------------*/
/* Generate an __SE_TEMPLATE_v2 with safe default values.                     */
/*----------------------------------------------------------------------------*/
_IDEFN __SE_TEMPLATE_v2 __attribute__((__always_inline__)) __gen_SE_TEMPLATE_v2()
{
    const __SE_TEMPLATE_v2 se =
    {
#if __little_endian__
        /* ICNT0                 = */ 0,
        /* SPAD_PAD_WIDTH        = */ 0,
        /* ICNT1                 = */ 0,
        /* INVERSE_DECDIM1_WIDTH = */ 0,
        /* ICNT2                 = */ 0,
        /* INVERSE_DECDIM2_WIDTH = */ 0,
        /* ICNT3                 = */ 0,
        /* ICNT4                 = */ 0,
        /* ICNT5                 = */ 0,
        /* DECDIM1_WIDTH         = */ 0,
        /* DECDIM2_WIDTH         = */ 0,
        /* DIM1                  = */ 0,
        /* DIM2                  = */ 0,
        /* DIM3                  = */ 0,
        /* DIM4                  = */ 0,
        /* DIM5                  = */ 0,
        /* LEZR_CNT              = */ 0,
        /* _reserved1            = */ 0,
        /*** Flags ***/
        /* ELETYPE               = */ __SE_ELETYPE_8BIT,
        /* _reserved2            = */ 0,
        /* PROMOTE               = */ __SE_PROMOTE_OFF,
        /* _reserved3            = */ 0,
        /* VECLEN           = */ __SE_VECLEN_64ELEMS,
        /* _reserved4            = */ 0,
        /* _reserved5            = */ 0,
        /* DECIM                 = */ __SE_DECIM_OFF,
        /* FILLVAL               = */ __SE_FILLVAL_ZERO,
        /* DIMFMT                = */ __SE_DIMFMT_1D,
        /* DECDIM2_MODE          = */ __SE_DECDIM2_MODE_NORMAL,
        /* CBK0                  = */ 0,
        /* CBK1                  = */ 0,
        /* AM0                   = */ __SE_AM_LINEAR,
        /* AM1                   = */ __SE_AM_LINEAR,
        /* AM2                   = */ __SE_AM_LINEAR,
        /* AM3                   = */ __SE_AM_LINEAR,
        /* AM4                   = */ __SE_AM_LINEAR,
        /* AM5                   = */ __SE_AM_LINEAR,
        /* DECDIM1               = */ __SE_DECDIM_DIM0,
        /* DECDIM1SD             = */ __SE_DECDIMSD_DIM0,
        /* DECDIM2               = */ __SE_DECDIM_DIM0,
        /* DECDIM2SD             = */ __SE_DECDIMSD_DIM0,
        /* LEZR                  = */ __SE_LEZR_OFF,
        /* TEMPLATE_FMT          = */ __SE_TEMPLATE_FMT_v2
#else
        /* Invert on 64 bit boundaries */
        /* INVERSE_DECDIM1_WIDTH = */ 0,
        /* ICNT1                 = */ 0,
        /* SPAD_PAD_WIDTH        = */ 0,
        /* ICNT0                 = */ 0,

        /* ICNT3                 = */ 0,
        /* INVERSE_DECDIM2_WIDTH = */ 0,
        /* ICNT2                 = */ 0,

        /* ICNT5                 = */ 0,
        /* ICNT4                 = */ 0,

        /* DECDIM2_WIDTH         = */ 0,
        /* DECDIM1_WIDTH         = */ 0,

        /* DIM2                  = */ 0,
        /* DIM1                  = */ 0,

        /* DIM4                  = */ 0,
        /* DIM3                  = */ 0,

        /* _reserved1            = */ 0,
        /* LEZR_CNT              = */ 0,
        /* DIM5                  = */ 0,

        /*** Flags ***/
        /* TEMPLATE_FMT          = */ __SE_TEMPLATE_FMT_v2,
        /* LEZR                  = */ __SE_LEZR_OFF,
        /* DECDIM2SD             = */ __SE_DECDIMSD_DIM0,
        /* DECDIM2               = */ __SE_DECDIM_DIM0,
        /* DECDIM1SD             = */ __SE_DECDIMSD_DIM0,
        /* DECDIM1               = */ __SE_DECDIM_DIM0,
        /* AM5                   = */ __SE_AM_LINEAR,
        /* AM4                   = */ __SE_AM_LINEAR,
        /* AM3                   = */ __SE_AM_LINEAR,
        /* AM2                   = */ __SE_AM_LINEAR,
        /* AM1                   = */ __SE_AM_LINEAR,
        /* AM0                   = */ __SE_AM_LINEAR,
        /* CBK1                  = */ 0,
        /* CBK0                  = */ 0,
        /* DECDIM2_MODE          = */ __SE_DECDIM2_MODE_NORMAL,
        /* DIMFMT                = */ __SE_DIMFMT_1D,
        /* FILLVAL               = */ __SE_FILLVAL_ZERO,
        /* DECIM                 = */ __SE_DECIM_OFF,
        /* _reserved5            = */ 0,
        /* _reserved4            = */ 0,
        /* VECLEN           = */ __SE_VECLEN_64ELEMS,
        /* _reserved3            = */ 0,
        /* PROMOTE               = */ __SE_PROMOTE_OFF,
        /* _reserved2            = */ 0,
        /* ELETYPE               = */ __SE_ELETYPE_8BIT
#endif
    };
    return se;
}
#endif /* __SE_FEAT_TEMPLATE_V2 */

#if defined(__SE_FEAT_TEMPLATE_V3)
/*----------------------------------------------------------------------------*/
/* Generate an __SE_TEMPLATE_v3 with safe default values.                     */
/*----------------------------------------------------------------------------*/
_IDEFN __SE_TEMPLATE_v3 __attribute__((__always_inline__)) __gen_SE_TEMPLATE_v3()
{
    const __SE_TEMPLATE_v3 se =
    {
#if __little_endian__
        /* ICNT0                 = */ 0,
        /* SPAD_PAD_WIDTH        = */ 0,
        /* ICNT1                 = */ 0,
        /* INVERSE_DECDIM1_WIDTH = */ 0,
        /* ICNT2                 = */ 0,
        /* SPAD_STARTING_OFFSET  = */ 0,
        /* ICNT3                 = */ 0,
        /* ICNT4                 = */ 0,
        /* ICNT5                 = */ 0,
        /* DECDIM1_WIDTH         = */ 0,
        /* SPAD_HORIZONTAL_WIDTH = */ 0,
        /* _reserved0            = */ 0,
        /* DIM1                  = */ 0,
        /* DIM2                  = */ 0,
        /* DIM3                  = */ 0,
        /* DIM4                  = */ 0,
        /* DIM5                  = */ 0,
        /* LEZR_CNT              = */ 0,
        /* _reserved1            = */ 0,
        /*** Flags ***/
        /* ELETYPE               = */ __SE_ELETYPE_8BIT,
        /* _reserved2            = */ 0,
        /* PROMOTE               = */ __SE_PROMOTE_OFF,
        /* _reserved3            = */ 0,
        /* VECLEN           = */ __SE_VECLEN_64ELEMS,
        /* _reserved4            = */ 0,
        /* _reserved5            = */ 0,
        /* DECIM                 = */ __SE_DECIM_OFF,
        /* FILLVAL               = */ __SE_FILLVAL_ZERO,
        /* DIMFMT                = */ __SE_DIMFMT_1D,
        /* DECDIM2_MODE          = */ __SE_DECDIM2_MODE_HORIZ_ZERO_PAD,
        /* CBK0                  = */ 0,
        /* CBK1                  = */ 0,
        /* AM0                   = */ __SE_AM_LINEAR,
        /* AM1                   = */ __SE_AM_LINEAR,
        /* AM2                   = */ __SE_AM_LINEAR,
        /* AM3                   = */ __SE_AM_LINEAR,
        /* AM4                   = */ __SE_AM_LINEAR,
        /* AM5                   = */ __SE_AM_LINEAR,
        /* DECDIM1               = */ __SE_DECDIM_DIM0,
        /* DECDIM1SD             = */ __SE_DECDIMSD_DIM0,
        /* SPAD_HORIZONTAL_BLO.. = */ __SE_SPAD_HORIZONTAL_BLOCK_DIM0,
        /* SPAD_HORIZONTAL_PIX.. = */ __SE_SPAD_HORIZONTAL_PIXEL_DIM0,
        /* LEZR                  = */ __SE_LEZR_OFF,
        /* TEMPLATE_FMT          = */ __SE_TEMPLATE_FMT_v2
#else
        /* Invert on 64 bit boundaries */
        /* INVERSE_DECDIM1_WIDTH = */ 0,
        /* ICNT1                 = */ 0,
        /* SPAD_PAD_WIDTH        = */ 0,
        /* ICNT0                 = */ 0,

        /* ICNT3                 = */ 0,
        /* SPAD_STARTING_OFFSET  = */ 0,
        /* ICNT2                 = */ 0,

        /* ICNT5                 = */ 0,
        /* ICNT4                 = */ 0,

        /* _reserved0            = */ 0,
        /* SPAD_HORIZONTAL_WIDTH = */ 0,
        /* DECDIM1_WIDTH         = */ 0,

        /* DIM2                  = */ 0,
        /* DIM1                  = */ 0,

        /* DIM4                  = */ 0,
        /* DIM3                  = */ 0,

        /* _reserved1            = */ 0,
        /* LEZR_CNT              = */ 0,
        /* DIM5                  = */ 0,

        /*** Flags ***/
        /* TEMPLATE_FMT          = */ __SE_TEMPLATE_FMT_v2,
        /* LEZR                  = */ __SE_LEZR_OFF,
        /* SPAD_HORIZONTAL_PIX.. = */ __SE_SPAD_HORIZONTAL_PIXEL_DIM0,
        /* SPAD_HORIZONTAL_BLO.. = */ __SE_SPAD_HORIZONTAL_BLOCK_DIM0,
        /* DECDIM1SD             = */ __SE_DECDIMSD_DIM0,
        /* DECDIM1               = */ __SE_DECDIM_DIM0,
        /* AM5                   = */ __SE_AM_LINEAR,
        /* AM4                   = */ __SE_AM_LINEAR,
        /* AM3                   = */ __SE_AM_LINEAR,
        /* AM2                   = */ __SE_AM_LINEAR,
        /* AM1                   = */ __SE_AM_LINEAR,
        /* AM0                   = */ __SE_AM_LINEAR,
        /* CBK1                  = */ 0,
        /* CBK0                  = */ 0,
        /* DECDIM2_MODE          = */ __SE_DECDIM2_MODE_HORIZ_ZERO_PAD,
        /* DIMFMT                = */ __SE_DIMFMT_1D,
        /* FILLVAL               = */ __SE_FILLVAL_ZERO,
        /* DECIM                 = */ __SE_DECIM_OFF,
        /* _reserved5            = */ 0,
        /* _reserved4            = */ 0,
        /* VECLEN           = */ __SE_VECLEN_64ELEMS,
        /* _reserved3            = */ 0,
        /* PROMOTE               = */ __SE_PROMOTE_OFF,
        /* _reserved2            = */ 0,
        /* ELETYPE               = */ __SE_ELETYPE_8BIT
#endif
    };
    return se;
}
#endif /* __SE_FEAT_TEMPLATE_V3 */

/*----------------------------------------------------------------------------*/
/* Generate an __SA_TEMPLATE_v1 with safe default values.                     */
/*----------------------------------------------------------------------------*/
_IDEFN __SA_TEMPLATE_v1 __attribute__((__always_inline__)) __gen_SA_TEMPLATE_v1()
{
    const __SA_TEMPLATE_v1 sa = 
    {
#if __little_endian__
        /* ICNT0            = */ 0,
        /* ICNT1            = */ 0,
        /* ICNT2            = */ 0,
        /* ICNT3            = */ 0,
        /* ICNT4            = */ 0,
        /* ICNT5            = */ 0,
        /* DECDIM1_WIDTH    = */ 0,
        /* DECDIM2_WIDTH    = */ 0,
        /* DIM1             = */ 0,
        /* DIM2             = */ 0,
        /* DIM3             = */ 0,
        /* DIM4             = */ 0,
        /* DIM5             = */ 0,
        /* DECDIM3_WIDTH    = */ 0,
        /*** Flags ***/
        /* _reserved2       = */ 0,
        /* VECLEN           = */ __SA_VECLEN_64ELEMS,
        /* _reserved3       = */ 0,
        /* INV_DD3          = */ __SA_INV_DD_OFF,
        /* INV_DD1          = */ __SA_INV_DD_OFF,
        /* INV_DD2          = */ __SA_INV_DD_OFF,
        /* DIMFMT           = */ __SA_DIMFMT_1D,
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
        /* Invert on 64 bit boundaries. */
        /* ICNT1            = */ 0,
        /* ICNT0            = */ 0,

        /* ICNT3            = */ 0,
        /* ICNT2            = */ 0,

        /* ICNT5            = */ 0,
        /* ICNT4            = */ 0,

        /* DECDIM2_WIDTH    = */ 0,
        /* DECDIM1_WIDTH    = */ 0,

        /* DIM2             = */ 0,
        /* DIM1             = */ 0,

        /* DIM4             = */ 0,
        /* DIM3             = */ 0,

        /* DECDIM3_WIDTH    = */ 0,
        /* DIM5             = */ 0,

        /*** Flags ***/
        /* _reserved        = */ 0,
        /* DECDIM2SD        = */ __SA_DECDIMSD_DIM0,
        /* DECDIM2          = */ __SA_DECDIM_DIM0,
        /* DECDIM1SD        = */ __SA_DECDIMSD_DIM0,
        /* DECDIM1          = */ __SA_DECDIM_DIM0,
        /* DECDIM3SD        = */ __SA_DECDIMSD_DIM0,
        /* DECDIM3          = */ __SA_DECDIM_DIM0,
        /* _reserved5       = */ 0,
        /* _reserved4       = */ 0,
        /* DIMFMT           = */ __SA_DIMFMT_1D,
        /* INV_DD2          = */ __SA_INV_DD_OFF,
        /* INV_DD1          = */ __SA_INV_DD_OFF,
        /* INV_DD3          = */ __SA_INV_DD_OFF,
        /* _reserved3       = */ 0,
        /* VECLEN           = */ __SA_VECLEN_64ELEMS,
        /* _reserved2       = */ 0
#endif
    };
    return sa;
}

/*----------------------------------------------------------------------------*/
/* DEMONSTRATION FOR SETUP AND USAGE OF A STREAMING ENGINE STREAM WITHOUT     */
/* CIRCULAR ADDRESSING:                                                       */
/*                                                                            */
/* #include <c7x.h>                                                           */
/* #include <stddef.h>                                                        */
/* uint8 se_func(uint32_t *startaddr)                                         */
/* {                                                                          */
/*     int I0;                                                                */
/*     uint8 Vresult;                                                         */
/*     __SE_TEMPLATE_v1 params = __gen_SE_TEMPLATE_v1(); // SE PARAMETERS     */
/*                                                                            */
/*     params.DIMFMT   = __SE_DIMFMT_4D;                                      */
/*     params.ELETYPE  = __SE_ELETYPE_32BIT;                                  */
/*     params.VECLEN   = __SE_VECLEN_4ELEMS; // 4 ELEMENTS                    */
/*                                                                            */
/*     // SETUP TEMPLATE VECTOR BASED ON SETTINGS AND OPEN THE STREAM         */
/*     // BASED ON ITERATION COUNTERS AND DIMENSIONS (IN TERMS OF # OF ELEMS) */
/*     params.ICNT0 = 4;                                                      */
/*     params.ICNT1 = 2;                                                      */
/*     params.DIM1  = 4;                                                      */
/*     params.ICNT2 = 2;                                                      */
/*     params.DIM2  = 8;                                                      */
/*     params.ICNT3 = 4;                                                      */
/*     params.DIM3  = -16;                                                    */
/*                                                                            */
/*     // DECDIM1 WIDTH (0 by default)                                        */
/*     params.DECDIM1_WIDTH = 0;                                              */
/*                                                                            */
/*     // DECDIM2 WIDTH (0 by default)                                        */
/*     params.DECDIM2_WIDTH = 0;                                              */
/*                                                                            */
/*     // LEZR COUNT (0 by default)                                           */
/*     params.LEZR_CNT = 0;                                                   */
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
/*     __SE_TEMPLATE_v1  params = __gen_SE_TEMPLATE_v1();   // SE PARAMETERS  */
/*                                                                            */
/*     params.DIMFMT    = __SE_DIMFMT_3D;                                     */
/*     params.ELETYPE   = __SE_ELETYPE_32BIT;                                 */
/*     params.VECLEN    = __SE_VECLEN_16ELEMS; // 16 ELEMENTS                 */
/*                                                                            */
/*     // CIRCULAR ADDRESSING BLOCK CONFIGURATION (SEE SPEC FOR DETAILS)      */
/*     params.CBK0 = 0;                    // 512BYTE ENCODING                */
/*                                                                            */
/*     // CIRCULAR ADDRESSING ADDRESS MODE CONFIGURATION                      */
/*     params.AM0 = __SE_AM_CIRC_CBK0;                                        */
/*     params.AM1 = __SE_AM_CIRC_CBK0;                                        */
/*     params.AM2 = __SE_AM_CIRC_CBK0;                                        */
/*                                                                            */
/*     // SETUP TEMPLATE VECTOR BASED ON SETTINGS AND OPEN THE STREAM         */
/*     // BASED ON ITERATION COUNTERS AND DIMENSIONS (IN TERMS OF # OF ELEMS) */
/*     params.ICNT0 = 16;                                                     */
/*     params.ICNT1 = 16;                                                     */
/*     params.DIM1  = 16;                                                     */
/*     params.ICNT2 = 1;                                                      */
/*     params.DIM2  = 0;                                                      */
/*                                                                            */
/*     // DECDIM1 WIDTH (0 by default)                                        */
/*     params.DECDIM1_WIDTH = 0;                                              */
/*                                                                            */
/*     // DECDIM2 WIDTH (0 by default)                                        */
/*     params.DECDIM2_WIDTH = 0;                                              */
/*                                                                            */
/*     // LEZR COUNT (0 by default)                                           */
/*     params.LEZR_CNT      =  0;                                             */
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
/*     __SA_TEMPLATE_v1 params = __gen_SA_TEMPLATE_v1(); // SA PARAMETER      */
/*                                                                            */
/*     params.DIMFMT  = __SA_DIMFMT_4D;                                       */
/*     params.VECLEN  = __SA_VECLEN_4ELEMS; // 4 ELEMENTS                     */
/*                                                                            */
/*     // SETUP TEMPLATE VECTOR BASED ON SETTINGS AND OPEN THE STREAM         */
/*     // BASED ON ITERATION COUNTERS AND DIMENSIONS (IN TERMS OF # OF ELEMS) */
/*     params.ICNT0 = 4;                                                      */
/*     params.ICNT1 = 2;                                                      */
/*     params.DIM1  = 4;                                                      */
/*     params.ICNT2 = 2;                                                      */
/*     params.DIM2  = 8;                                                      */
/*     params.ICNT3 = 4;                                                      */
/*     params.DIM3  = -16;                                                    */
/*                                                                            */
/*     // DECDIM1 WIDTH (0 by default)                                        */
/*     params.DECDIM1_WIDTH = 0;                                              */
/*                                                                            */
/*     // DECDIM2 WIDTH (0 by default)                                        */
/*     params.DECDIM2_WIDTH = 0;                                              */
/*                                                                            */
/*     __SA1_OPEN(params);                                                    */
/*                                                                            */
/*     // READ THE STREAM AND ADVANCE THE COUNTERS                            */
/*     for (I0 = 0; I0 < 8; I0++)                                             */
/*     {                                                                      */
/*         uint8 Vout;                                                        */
/*         Vout.lo = *__SA1ADV(uint4, startaddr);                             */
/*         Vout.hi = *__SA1ADV(uint4, startaddr);                             */
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
#if defined(__SE_FEAT_TEMPLATE_V1)
void     __OVBIFM __se_open      (__RD const void*, __CST(0, 1) __uint, __SE_TEMPLATE_v1);
#endif /* __SE_FEAT_TEMPLATE_V1 */
#if defined(__SE_FEAT_TEMPLATE_V2)
void     __OVBIFM __se_open      (__RD const void*, __CST(0, 1) __uint, __SE_TEMPLATE_v2);
#endif /* __SE_FEAT_TEMPLATE_V2 */
#if defined(__SE_FEAT_TEMPLATE_V3)
void     __OVBIFM __se_open      (__RD const void*, __CST(0, 1) __uint, __SE_TEMPLATE_v3);
#endif /* __SE_FEAT_TEMPLATE_V3 */
#define __se_open(a,b,c) __overload("__se_open",(a),(__uint)(b),(c))((a),(b),(c))

void     __BIFM   __se_close     (__CST(0, 1) __uint);
void     __BIFM   __se_break     (__CST(0, 5) __uint, __CST(0, 1) __uint);
__uint16 __BIFM   __se_save      (__CST(0, 3) __uint, __CST(0, 1) __uint);
void     __BIFM   __se_restore   (__CST(0, 3) __uint, __CST(0, 1) __uint, __uint16);

/*---------------------------------------------------------------------------*/
/* void __SEn_OPEN(const void *addr, __SE_TEMPLATE)                          */
/*   Opens streaming engine n at address addr.                               */
/*---------------------------------------------------------------------------*/
#define __SE0_OPEN(addr,tmpl)   __se_open(__se_mem(addr), 0U, tmpl)
#define __SE1_OPEN(addr,tmpl)   __se_open(__se_mem(addr), 1U, tmpl)

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
/*                                                                           */
/*  The specified type cannot be larger than the size of a vector register.  */
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
typedef enum __attribute__((__packed__))
{
    __SE_REG_0     = 0,
    __SE_REG_0_ADV = 1,
    __SE_REG_1     = 2,
    __SE_REG_1_ADV = 3,
    __SE_REG_LAST  = 3 /* Don't use directly. */
} __SE_REG;

/*----------------------------------------------------------------------------*/
/* Use the following for SE_REG_PAIR operands.                                */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
{
    __SE_REG_PAIR_0     = 0,
    __SE_REG_PAIR_0_ADV = 1,
    __SE_REG_PAIR_LAST  = 1 /* Don't use directly. */
} __SE_REG_PAIR;

/*----------------------------------------------------------------------------*/
/* Streaming Engine Shortcut-Open Arguments.                                  */
/* The type of shortcut argument can be used in place of a vector template to */
/* open a stream using __SE0_OPEN_SHORTCUT() or __SE1_OPEN_SHORTCUT().        */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
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
    __STROPEND   = 0x9,
    __SE_SHORTCUT_LAST = 0x9 /* Don't use directly. */
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
typedef enum __attribute__((__packed__))
{
    /* Sharable */
    __DCCIC     = 0x14, /* DataCache Clean/Invalidate to Point of Coherence   */
    __DCCMIC    = 0x15, /* DataCache Invalidate to Point of Coherence         */
    __BLK_OPTYPE_LAST = 0x15 /* Don't use directly. */
} __BLK_OPTYPE;

/*----------------------------------------------------------------------------*/
/* __se_cache_op(const void*, __BLK_OPTYPE, __uint bytes)                     */
/*   Direct access to BLKCMO instruction.                                     */
/*----------------------------------------------------------------------------*/
/* No operation performed under host emulation. */
void    __BIFM   __se_cache_op     (const void*, __CST(20,21) __BLK_OPTYPE, __uint);

/*----------------------------------------------------------------------------*/
/* Block Cache Preload Instruction Arguments                                  */
/* These arguments are used with __se_cache_preload() to operate on a         */
/* contiguous block of addresses.                                             */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
{
    __L2R = 0x0, /* Preload to L2 for reading */
    __L2W = 0x1, /* Preload to L2 for writing */
    __L3R = 0x2, /* Preload to L3 for reading */
    __L3W = 0x3, /* Preload to L3 for writing */
    __BLK_PLDTYPE_LAST = 0x3 /* Don't use directly. */
} __BLK_PLDTYPE;

/*----------------------------------------------------------------------------*/
/* __se_cache_preload(const void*, __BLK_PLDTYPE, __uint bytes)               */
/*   Direct access to BLKPLD instruction.                                     */
/*----------------------------------------------------------------------------*/
/* No operation performed under host emulation. */
void    __BIFM   __se_cache_preload(const void*, __CST(0,3) __BLK_PLDTYPE, __uint);

/*----------------------------------------------------------------------------*/
/* Streaming Engine param size is 64 bytes. All the above options             */
/* including iteration counts(ICNT) and dimensions(DIM) are packed in a       */
/* 512bit vector. Use this macro to derrive offsets while writing to L1D SRAM */
/*----------------------------------------------------------------------------*/
#define SE_PARAM_SIZE (64)

/*----------------------------------------------------------------------------*/
/* Stream Address Generator param size is 64 bytes. All the above options     */
/* including iteration counts(ICNT) and dimensions(DIM) are packed in a       */
/* 512bit vector. Use this macro to derrive offsets while writing to L1D SRAM */
/*----------------------------------------------------------------------------*/
#define SA_PARAM_SIZE (64)

/*****************************************************************************/
/* STREAMING ADDRESS GENERATOR COMMON CONTROLS                               */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* Implementation details.  Do not use directly.                             */
/*---------------------------------------------------------------------------*/
void     __OVBIFM   __sa_open    (__CST(0, 3) __uint, __SA_TEMPLATE_v1);
#define __sa_open(a,b) __overload("__sa_open",(__uint)(a),(b))((a),(b))

void     __BIFM     __sa_close   (__CST(0, 3) __uint);
void     __BIFM     __sa_break   (__CST(0, 5) __uint, __CST(0, 3) __uint);
void     __BIFM     __sa_set_cr  (__CST(0, 3) __uint, __uint16);
__uint16 __BIFM     __sa_get_cr  (__CST(0, 3) __uint);
__uint16 __BIFM     __sa_get_cntr(__CST(0, 3) __uint);
#define __sa_get_cntr0(x) __sa_get_cntr(x)
#ifndef __C7100__
__uint16 __BIFM     __sa_get_cntr1(__CST(0, 3) __uint);
#endif
__vpred  __BIFM     __sa_vpred   (__CST(0, 3) __uint, __CST(1, 8) __uint);
void*    __BIFM     __sa(__CST(0,3) __uint, __CST(1,8) __uint, const void *);
void*    __BIFM     __sa_adv(__CST(0,3) __uint, __CST(1,8) __uint, const void *);

/*---------------------------------------------------------------------------*/
/* void __SAn_OPEN(__SA_TEMPLATE)                                            */
/*   Opens streaming address generator n.                                    */
/*---------------------------------------------------------------------------*/
#define __SA0_OPEN(tmpl) __sa_open(0U, tmpl)
#define __SA1_OPEN(tmpl) __sa_open(1U, tmpl)
#define __SA2_OPEN(tmpl) __sa_open(2U, tmpl)
#define __SA3_OPEN(tmpl) __sa_open(3U, tmpl)

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
/*     - __SA0(int2, baseptr) -> returns int2_ptr                            */
/*     - __SA0(__int2, baseptr) -> returns __int2_ptr                        */
/*     - __SA0(__const_int2, baseptr) -> returns __const_int2_ptr            */
/*                                                                           */
/*  The specified type cannot be larger than the size of a vector register.  */
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

/*---------------------------------------------------------------------------*/
/* void __SAn_SET_CR(__uint16 data)                                          */
/*   Set the contents of the streaming address generator n's configuration   */
/*   control register.                                                       */
/*---------------------------------------------------------------------------*/
#define __SA0_SET_CR(data)      __sa_set_cr(0U, data)
#define __SA1_SET_CR(data)      __sa_set_cr(1U, data)
#define __SA2_SET_CR(data)      __sa_set_cr(2U, data)
#define __SA3_SET_CR(data)      __sa_set_cr(3U, data)

/*---------------------------------------------------------------------------*/
/* __uint16 __SAn_GET_CR()                                                   */
/*   Retrieve the contents of streaming address generator n's configuration  */
/*   control register.                                                       */
/*---------------------------------------------------------------------------*/
#define __SA0_GET_CR()          __sa_get_cr(0U)
#define __SA1_GET_CR()          __sa_get_cr(1U)
#define __SA2_GET_CR()          __sa_get_cr(2U)
#define __SA3_GET_CR()          __sa_get_cr(3U)

/*---------------------------------------------------------------------------*/
/* __uint16 __SAn_GET_CNTR0()                                                */
/*   Retrieve the contents of streaming address generator n's counter 0      */
/*   control register.                                                       */
/*---------------------------------------------------------------------------*/
#define __SA0_GET_CNTR0()       __sa_get_cntr0(0U)
#define __SA1_GET_CNTR0()       __sa_get_cntr0(1U)
#define __SA2_GET_CNTR0()       __sa_get_cntr0(2U)
#define __SA3_GET_CNTR0()       __sa_get_cntr0(3U)

/*---------------------------------------------------------------------------*/
/* __uint16 __SAn_GET_CNTR1()                                                */
/*   Retrieve the contents of streaming address generator n's counter 1      */
/*   control register.                                                       */
/*---------------------------------------------------------------------------*/
#define __SA0_GET_CNTR1()       __sa_get_cntr1(0U)
#define __SA1_GET_CNTR1()       __sa_get_cntr1(1U)
#define __SA2_GET_CNTR1()       __sa_get_cntr1(2U)
#define __SA3_GET_CNTR1()       __sa_get_cntr1(3U)

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

#ifdef __cplusplus
}
#endif

#endif /* __C7X_STRM_H */
