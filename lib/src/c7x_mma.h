/*****************************************************************************/
/*  C7X_MMA.H                                                                */
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

#ifndef __C7X_MMA_H
#define __C7X_MMA_H

#include <stdint.h>

/*----------------------------------------------------------------------------*/
/*                                                                            */
/* This file contains two structure definitions, enumerations, intrinsic      */
/* declarations, and a macro to enable use of the MMA.                        */
/*                                                                            */
/* Two structs are to be used with the __HWAOPEN intrinsic:                   */
/*   __HWA_CONFIG_REG_v1     -  contains fields to setup the MMA              */
/*   __HWA_OFFSET_REG        -  contains fields to setup the MMA              */
/*                                                                            */
/* The __HWAOPEN "built-in function" (intrinsic) should be used to open and   */
/* initialize the MMA.                                                        */
/*                                                                            */
/*   __HWAOPEN() - Used to pass the struct objects to initialize the MMA.     */
/*                                                                            */
/* The following built-in functions (intrinsics) that correspond to C7x       */
/* instructions control the MMA execution. Please see the MMA specification   */
/* for more details on MMA behavior.                                          */
/*                                                                            */
/*   __HWACLOSE                                                               */
/*   __HWALDA                                                                 */
/*   __HWALDB                                                                 */
/*   __HWALDC                                                                 */
/*   __HWALDAB                                                                */
/*   __HWALDBC                                                                */
/*   __HWAOP                                                                  */
/*   __HWAXFER                                                                */
/*   __HWAOPXFER                                                              */
/*   __HWAXFER_MASK                                                           */
/*   __HWAXFER_XSTATUS_DELAYED                                                */
/*   __HWARCV                                                                 */
/*                                                                            */
/* Example usage:                                                             */
/*                                                                            */
/* // In a place that is executed only once or rarely, set the fields for the */
/* // HWA_CONFIG_REG_v1                                                       */
/*                                                                            */
/* __HWA_CONFIG_REG_v1 mma_config_reg; // Create instance of the config struct*/
/* mma_config_reg = __gen_HWA_CONFIG_REG_v1(); // Set all fields to zero      */
/*                                                                            */
/* // Set individual fields                                                   */
/* mma_config_reg.A_ATYPE = __MMA_A_CONFIG_ATYPE_INT32;                       */
/* . . .                                                                      */
/* mma_config_reg.PARITYCTRL = _MMA_PNCM_NCK;                                 */
/*                                                                            */
/*                                                                            */
/* // Do the same with __HWA_OFFSET_REG...                                    */
/*                                                                            */
/* void user_function()                                                       */
/* {                                                                          */
/*     // Set remaining fields of the config and offset registers at runtime  */
/*     mma_config_reg.B_BOFFSET = ... ;                                       */
/*     ...                                                                    */
/*     // Initialize the MMA with the __HWAOPEN macro                         */
/*     __HWAOPEN (mma_config_reg, mma_offset_reg, __MMA_OPEN_FSM_RESET);      */
/*     ...                                                                    */
/* }                                                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C"
{
#endif

/*----------------------------------------------------------------------------*/
/* The --mma_version compiler option controls the definition of the following */
/* predefined macros:                                                         */
/*                                                                            */
/* Option:                   Predefined Macros:                               */
/*   --mma_version=1           __C7X_MMA_1__, __C7X_MMA__                     */
/*   --mma_version=2           __C7X_MMA_2__, __C7X_MMA__                     */
/*   --mma_version=disallow    (N/A)                                          */
/*                                                                            */
/* The following MMA interfaces are available depending on the existence      */
/* of those macros.                                                           */
/*----------------------------------------------------------------------------*/
#if defined (__C7X_MMA__)

/******************************************************************************/
/* MMA Feature Support                                                        */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Transfer, Receive Types                                                    */
/*   The type of vector used for a transfer or receive depends on the vector  */
/*   size of the C7x.                                                         */
/*----------------------------------------------------------------------------*/
typedef __uchar64 __mma_vec;
typedef __const_uchar64 __const_mma_vec;
typedef __uchar64_ptr __mma_vec_ptr;
typedef __const_uchar64_ptr __const_mma_vec_ptr;
#define __as_mma_vec(x) __as_uchar64(x)


/******************************************************************************/
/* Configuration Enumerations                                                 */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* Use the following for PARITYCTRL in HWA_CONFIG setup                       */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
{
    __MMA_NORMAL      = 0,
    __MMA_PNCM_CK     = 1,
    __MMA_PCM_NCK     = 2,
    __MMA_PNCM_NCK    = 3,
    __MMA_PARITYCTRL_LAST = 3 /* Don't use directly. */
} __MMA_PARITYCTRL;

/*----------------------------------------------------------------------------*/
/* Use the following for A_TYPE in HWA_CONFIG setup                           */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
{
    __MMA_A_CONFIG_ATYPE_UINT8  = 0,
    __MMA_A_CONFIG_ATYPE_UINT16 = 1,
    /* reserved = 2, */
    __MMA_A_CONFIG_ATYPE_UINT32 = 3,
    __MMA_A_CONFIG_ATYPE_INT8   = 4,
    __MMA_A_CONFIG_ATYPE_INT16  = 5,
    /* reserved = 6, */
    __MMA_A_CONFIG_ATYPE_INT32  = 7,
    __MMA_A_CONFIG_ATYPE_LAST   = 7 /* Don't use directly. */
} __MMA_A_CONFIG_ATYPE;

/*----------------------------------------------------------------------------*/
/* Use the following for A_ALUTEN in HWA_CONFIG setup                         */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
{
    __MMA_A_CONFIG_NOLUT = 0,
#if defined (__C7X_MMA_1__)
    __MMA_A_CONFIG_LUT   = 1,
#elif defined(__C7X_MMA_2__) || defined(__C7X_MMA_2_256__)
    __MMA_A_CONFIG_LUT2  = 1,
#endif
    __MMA_A_LUTEN_LAST   = 1 /* Don't use directly. */
} __MMA_A_LUTEN;

/*----------------------------------------------------------------------------*/
/* Use the following for ARF_CTRL in A_CONFIG in HWA_CONFIG setup             */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
{
  __MMA_A_CONFIG_ARF_DISABLE = 0,
#if !defined(__C7X_MMA_1__)
  __MMA_A_CONFIG_ARF_ENABLE  = 1,
#endif /* !__C7X_MMA_1__ */
  __MMA_A_CONFIG_ARF_CTRL_LAST = 1 /* Don't use directly. */
} __MMA_A_CONFIG_ARF_CTRL;

/*----------------------------------------------------------------------------*/
/* Use the following for B_BTYPE in HWA_CONFIG setup                          */
/* NOTE: C_CONFIG and B_CONFIG have different field needing different enums   */
/* with the same name: "BTYPE"                                                */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
{
    __MMA_B_CONFIG_SIZE8  = 0,
    __MMA_B_CONFIG_SIZE16 = 1,
    /* reserved = 2, */
    __MMA_B_CONFIG_SIZE32 = 3,
    __MMA_B_CONFIG_LAST   = 3 /* Don't use directly. */
} __MMA_B_BTYPE;

/*----------------------------------------------------------------------------*/
/* Use the following for LDBOPT in HWA_CONFIG setup                           */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
{
    __MMA_LDBOPT_MMA1  = 0,
#if !defined(__C7X_MMA_1__)
    __MMA_LDBOPT_LDB5X = 1,
    __MMA_LDBOPT_LDB2X = 2,
    __MMA_LDBOPT_LDB3X = 3,
#endif /* !__C7X_MMA_1__ */
    __MMA_LDBOPT_LAST  = 3 /* Don't use directly. */
} __MMA_LDBOPT;

/*----------------------------------------------------------------------------*/
/* Use the following for B_B4EXP in HWA_CONFIG setup                          */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
{
    __MMA_B_CONFIG_B4EXP_MMA1     = 0,
#if !defined(__C7X_MMA_1__)
    __MMA_B_CONFIG_B4EXP_UNSIGNED = 1,
    __MMA_B_CONFIG_B4EXP_SIGNED   = 2,
#endif /* !__C7X_MMA_1__ */
    /* reserved = 3, */
    __MMA_B4EXP_LAST              = 3 /* Don't use directly. */
} __MMA_B4EXP;

/*----------------------------------------------------------------------------*/
/* Use the following for B_ORDER in HWA_CONFIG setup                          */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
{
    __MMA_B_CONFIG_ROW = 0,
    __MMA_B_CONFIG_COL = 1,
    __MMA_B_CONFIG_ORDER_TRANSPOSE_CONTROL_LAST = 1 /* Don't use directly. */
} __MMA_B_CONFIG_ORDER_TRANSPOSE_CONTROL;

/*----------------------------------------------------------------------------*/
/* C CONFIG enumerations                                                      */
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/* Use the following for C_ATYPE in HWA_CONFIG setup                          */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
{
    __MMA_C_CONFIG_ATYPE_UA = 0, /* Vector elements are unsigned              */
    __MMA_C_CONFIG_ATYPE_SA = 1, /* Vector elements are signed                */
    __MMA_C_CONFIG_ATYPE_LAST = 1 /* Don't use directly. */
} __MMA_C_CONFIG_ATYPE;

/*----------------------------------------------------------------------------*/
/* Use the following for C_BTYPE in HWA_CONFIG setup                          */
/* NOTE: C_CONFIG and B_CONFIG have different field needing different enums   */
/* with the same name: "BTYPE"                                                */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
{
    __MMA_C_CONFIG_BTYPE_UINT8  = 0,
    __MMA_C_CONFIG_BTYPE_UINT16 = 1,
    /* reserved = 2, */
    __MMA_C_CONFIG_BTYPE_UINT32 = 3,
    __MMA_C_CONFIG_BTYPE_INT8   = 4,
    __MMA_C_CONFIG_BTYPE_INT16  = 5,
    /* reserved = 6, */
    __MMA_C_CONFIG_BTYPE_INT32  = 7,
    __MMA_C_CONFIG_BTYPE_LAST   = 7 /* Don't use directly. */
} __MMA_C_CONFIG_BTYPE;

/*----------------------------------------------------------------------------*/
/* Use the following for C_OPERATION0 and C_OPERATION1 in HWA_CONFIG setup    */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
{
    __MMA_C_CONFIG_MUL          = 0,
    __MMA_C_CONFIG_MULNEGATE    = 1,
    __MMA_C_CONFIG_MULMINUS     = 2,
    __MMA_C_CONFIG_MULPLUS      = 3,
    __MMA_C_CONFIG_OPERATION_LAST = 3 /* Don't use directly. */
} __MMA_C_CONFIG_OPERATION;

/*----------------------------------------------------------------------------*/
/* Use the following for C_LOP0 and C_LOP1 in HWA_CONFIG setup.               */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
{
    __MMA_C_CONFIG_LOP_C        = 0,
#if !defined(__C7X_MMA_1__)
    __MMA_C_CONFIG_LOP_BIAS     = 1,
#endif /* !__C7X_MMA_1__ */
    __MMA_C_CONFIG_LOP_LAST     = 1 /* Don't use directly. */
} __MMA_C_CONFIG_LOP;

/*----------------------------------------------------------------------------*/
/* Use the following for C_BIASORDER in the HWA_CONFIG setup                  */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
{
    __MMA_C_CONFIG_BIAS_ORDER_COLUMN = 0,
#if !defined(__C7X_MMA_1__)
    __MMA_C_CONFIG_BIAS_ORDER_ROW    = 1,
#endif /* !__C7X_MMA_1__ */
    __MMA_C_CONFIG_BIASORDER_LAST    = 1 /* Don't use directly. */
} __MMA_C_CONFIG_BIASORDER;

typedef enum __attribute__((__packed__))
{                                    /* Input data  | Shifted left?       */
                                     /* extended?                         */
    __MMA_C_CONFIG_HWLDDST_X4_0 = 0, /*  4 times      not shifted         */
    __MMA_C_CONFIG_HWLDDST_X4_1 = 1, /*  4 times      1x orig bit width   */
    __MMA_C_CONFIG_HWLDDST_X4_2 = 2, /*  4 times      2x orig bit width   */
    __MMA_C_CONFIG_HWLDDST_X4_3 = 3, /*  4 times      3x orig bit width   */
    /* reserved = 4, */
    /* reserved = 5, */
    /* reserved = 6, */
    __MMA_C_CONFIG_HWLDDST_X1   = 7, /*  No           not shifted         */
    __MMA_C_CONFIG_HWLDDST_LAST = 7  /* Don't use directly. */
} __MMA_C_CONFIG_HWLDDST;

/*----------------------------------------------------------------------------*/
/* Use the following for C_HWLDTYPE in HWA_CONFIG setup                       */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
{
    __MMA_C_CONFIG_HWLDTYPE_UINT8  = 0,
    __MMA_C_CONFIG_HWLDTYPE_UINT16 = 1,
    /* reserved = 2, */
    __MMA_C_CONFIG_HWLDTYPE_UINT32 = 3,
    /* reserved = 4, */
    /* reserved = 5, */
    /* reserved = 6, */
    /* reserved = 7, */
    __MMA_C_CONFIG_HWLDTYPE_INT8   = 8,
    __MMA_C_CONFIG_HWLDTYPE_INT16  = 9,
    /* reserved = 10, */
    __MMA_C_CONFIG_HWLDTYPE_INT32  = 11,
    /* reserved = 12, */
    /* reserved = 13, */
    /* reserved = 14, */
    /* reserved = 15, */
    __MMA_C_CONFIG_HWLDTYPE_LAST   = 15 /* Don't use directly. */
} __MMA_C_CONFIG_HWLDTYPE;

/*----------------------------------------------------------------------------*/
/* Use the following for C_OPSTART in HWA_CONFIG setup                        */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
{
    __MMA_C_CONFIG_OPSTART_OPERATION0 = 0,
    __MMA_C_CONFIG_OPSTART_OPERATION1 = 1,
    __MMA_C_CONFIG_OPSTART_LAST       = 1 /* Don't use directly. */
} __MMA_C_CONFIG_OPSTART;


/*----------------------------------------------------------------------------*/
/* X CONFIG enumerations                                                      */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Use the following for X_CONFIG RANGE in HWA_CONFIG setup                   */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
{
    __MMA_X_CONFIG_RANGE_DISABLE_NOINIT = 0,
#if !defined(__C7X_MMA_1__)
    __MMA_X_CONFIG_RANGE_DISABLE_INIT   = 1,
    __MMA_X_CONFIG_RANGE_ENABLE_NOINIT  = 2,
    __MMA_X_CONFIG_RANGE_ENABLE_INIT    = 3,
#endif /* !__C7X_MMA_1__ */
    __MMA_X_CONFIG_RANGE_LAST           = 3 /* Don't use directly. */
} __MMA_X_CONFIG_RANGE;

/*----------------------------------------------------------------------------*/
/* Use the following for X_CONFIG VPACKN in HWA_CONFIG setup                  */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
{
    __MMA_X_CONFIG_VPACKN_DISABLE = 0, /* 4-bit packing is disabled (MMA 1.0  */
                                       /* behavior)                           */
#if !defined(__C7X_MMA_1__)
    __MMA_X_CONFIG_VPACKN_ENABLE  = 1, /* Bits[3:0] of each 8-bit SIMD lane   */
                                       /* are packed into bits [255:0] of the */
                                       /* result after shifting, rounding,    */
                                       /* and non-linearity.                  */
#endif /* !__C7X_MMA_1__ */
    __MMA_C_CONFIG_VPACKN_LAST    = 1  /* Do not use directly. */
} __MMA_X_CONFIG_VPACKN;

/*----------------------------------------------------------------------------*/
/* Use the following for X_SHIFT in HWA_CONFIG setup when X_SCALE_SHIFT_CTRL  */
/* is __MMA_X_CONFIG_SCALE_SHIFT_CTRL_ENABLE.                                 */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
{
    __MMA_X_CONFIG_SHIFT_ROW_UNSIGNED = 0x40, /* Per row shift, unsigned scale*/
#if !defined(__C7X_MMA_1__)
    __MMA_X_CONFIG_SHIFT_ROW_SIGNED   = 0x41, /* Per row shift, signed sale   */
    __MMA_X_CONFIG_SHIFT_COL_UNSIGNED = 0x42, /* Per col shift, unsigned scale*/
    __MMA_X_CONFIG_SHIFT_COL_SIGNED   = 0x43, /* Per col shift, signed scale  */
#endif /* !__C7X_MMA_1__ */
    __MMA_X_CONFIG_SHIFT_LAST         = 0x7F  /* Do not use directly. */
} __MMA_X_CONFIG_SHIFT;

/*----------------------------------------------------------------------------*/
/* Use the following for X_SCALE_SHIFT_CTRL in HWA_CONFIG setup. When set to  */
/* __MMA_X_CONFIG_SCALE_SHIFT_CTRL_DISABLE, X_SHIFT takes an integral value.  */
/* When set to __MMA_X_CONFIG_SCALE_SHIFT_CTRL_ENABLE, X_SHIFT takes an       */
/* enumeration value from __MMA_X_CONFIG_SHIFT.                               */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
{
    __MMA_X_CONFIG_SCALE_SHIFT_CTRL_DISABLE = 0, /* No per row/col shift/scale*/
#if !defined(__C7X_MMA_1__)
    __MMA_X_CONFIG_SCALE_SHIFT_CTRL_ENABLE  = 1, /* Enable scale from         */
                                                 /* HWA_SCALE and HWA_SHIFT   */
#endif /* !__C7X_MMA_1__ */
    __MMA_X_CONFIG_SCALE_SHIFT_CTRL_LAST    = 1  /* Do not use directly. */
} __MMA_X_CONFIG_SCALE_SHIFT_CTRL;

/*----------------------------------------------------------------------------*/
/* Use the following for X_XTYPE in HWA_CONFIG setup                          */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
{
    __MMA_X_CONFIG_XTYPE_UINT8   = 0,
    __MMA_X_CONFIG_XTYPE_UINT16  = 1,
    /* reserved = 2, */
    __MMA_X_CONFIG_XTYPE_UINT32  = 3,
    __MMA_X_CONFIG_XTYPE_UINT64  = 4,
    __MMA_X_CONFIG_XTYPE_UINT128 = 5,
    /* reserved = 6, */
    /* reserved = 7, */
    __MMA_X_CONFIG_XTYPE_INT8    = 8,
    __MMA_X_CONFIG_XTYPE_INT16   = 9,
    /* reserved = 10, */
    __MMA_X_CONFIG_XTYPE_INT32   = 11,
    __MMA_X_CONFIG_XTYPE_INT64   = 12,
    __MMA_X_CONFIG_XTYPE_INT128  = 13,
    /* reserved = 14, */
    /* reserved = 15, */
    __MMA_X_CONFIG_XTYPE_LAST    = 15 /* Don't use directly. */
} __MMA_X_CONFIG_XTYPE;

/*----------------------------------------------------------------------------*/
/* Use the following for X_CTYPE in HWA_CONFIG setup                          */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
{
    __MMA_X_CONFIG_CTYPE_UINT32  = 0,
    __MMA_X_CONFIG_CTYPE_UINT64  = 1,
    /* reserved = 2, */
    __MMA_X_CONFIG_CTYPE_UINT128 = 3,
    __MMA_X_CONFIG_CTYPE_INT32   = 4,
    __MMA_X_CONFIG_CTYPE_INT64   = 5,
    /* reserved = 6, */
    __MMA_X_CONFIG_CTYPE_INT128  = 7,
    __MMA_X_CONFIG_CTYPE_LAST    = 7 /* Don't use directly. */
} __MMA_X_CONFIG_CTYPE;


/******************************************************************************/
/* Configuration Layouts                                                      */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* __HWA_CONFIG_REG_v1 struct for use with C7100 and C7120 MMA initialization */
/* with the __HWAOPEN intrinsic (see usage example above).                    */
/*                                                                            */
/* Note: A best practice is to first use the __gen_HWA_CONFIG_REG_v1() to     */
/* initialize an instance of this structure. This is because the reserved/    */
/* "RSVD" fields may be renamed in future compiler versions for future        */
/* features to avoid the proliferation of different configuration structures. */
/* So code using the name of a reserved field (or using "ordered struct       */
/* instantiation") may need changes to compile with future compiler versions. */
/*                                                                            */
/*----------------------------------------------------------------------------*/
typedef struct __attribute__((__packed__)) __HWA_CONFIG_REG_v1
{
#if __little_endian__
    __MMA_A_CONFIG_ATYPE A_ATYPE:3; /* A vector element type                  */
    uint64_t A_RSVD1:5;       /* Reserved                                     */
    __MMA_A_LUTEN A_ALUTEN:1; /* A vector element lookup table                */
    uint64_t A_RSVD2:7;       /* Reserved                                     */
    __MMA_A_CONFIG_ARF_CTRL A_ARF_CTRL:1; /* A opnd register file wrt enable  */
    uint64_t A_ARF_BASE:6;   /* Base value of circular buffer in the A operand
                                register file when ARF_CTRL is ARF_ENABLE     */
    uint64_t A_RSVD3:1;      /* Reserved                                      */
    uint64_t A_ARF_SIZE:7;   /* ARF array size for read and write operations  */
    uint64_t A_RSVD4:1;      /* Reserved                                      */

    uint64_t B_BSWPER:32;    /* B banks switch period                         */
    uint64_t B_BRSTPER:8;    /* B offset reset period                         */
    __MMA_B_BTYPE B_BTYPE:2; /* B matrix element type                         */
    __MMA_LDBOPT B_LDBOPT:2; /* Control for enhanced B operand row loading    */
    __MMA_B4EXP B_B4EXP:2;   /* B operand expansion control to conv 4-bit ops
                                to 8-bit ops                                  */
    uint64_t B_RSVD1:2;      /* Reserved                                      */
    __MMA_B_CONFIG_ORDER_TRANSPOSE_CONTROL B_ORDER:1; /* Transpose control    */
    uint64_t B_RSVD2:7;      /* Reserved                                      */
    uint64_t B_BSTART:1;     /* Initial B bank selection for writing B matrix
                                data                                          */
    uint64_t B_BCNT1_ENABLE:1;/* Enable bit for option B row write row cntr for
                                 B bank 1.                                    */
    uint64_t B_RSVD3:6;      /* Reserved                                      */
    uint64_t B_BOFFSET:8;    /* Global row or column offset                   */
    uint64_t B_RSVD4:24;     /* Reserved                                      */

    __MMA_C_CONFIG_ATYPE C_ATYPE:1; /* unsigned or signed                     */
    uint64_t C_ARF_BASE:6;   /* ARF read pointer base value when ARG_C7 is
                                cleared                                       */
    uint64_t C_ARF_C7:1;     /* ARF read addresses are supplied by the host C7
                                processor as an argument to the HWAOP or
                                HWAOPXFER instructions.                       */
    __MMA_C_CONFIG_BTYPE C_BTYPE:3; /* B matrix element type and bias table
                                       element size. Must be consistent with
                                       the B FSM setting.                     */
    uint64_t C_RSVD2:5;      /* Reserved                                      */
    __MMA_C_CONFIG_OPERATION C_OPERATION0:2;
    __MMA_C_CONFIG_LOP C_LOP0:1; /* Left operand selection for C_OPERATION0   */
    uint64_t C_RSVD3:5;      /* Reserved                                      */
    __MMA_C_CONFIG_OPERATION C_OPERATION1:2;
    __MMA_C_CONFIG_LOP C_LOP1:1; /* Left operand selection for C_OPERATION1   */
    __MMA_C_CONFIG_BIASORDER C_BIASORDER:1; /* Transpose bias matrix          */
    uint64_t C_RSVD4:4;      /* Reserved                                      */
    __MMA_C_CONFIG_HWLDDST C_HWLDDST:3;
    uint64_t C_RSVD5:5;      /* Reserved                                      */
    __MMA_C_CONFIG_HWLDTYPE C_HWLDTYPE:4; /* C matrix element type from a
                                             HWALD* instruction               */
    uint64_t C_RSVD6:4;      /* Reserved                                      */
    __MMA_C_CONFIG_OPSTART C_OPSTART:1; /* Initial C operand selection        */
    uint64_t C_BSTART:1;     /* Initial B bank selection for reading B matrix 
                                data for the matrix computations              */
    uint64_t C_CRSTART:1;    /* Initial C bank selection for reading operands */
    uint64_t C_CWSTART:1;    /* Initial C bank selection for writing 
                                computation results                           */
    uint64_t C_CLSTART:1;    /* Initial C bank selection for writing operands 
                                from HWALD*                                   */
    uint64_t C_RSVD7:3;      /* Reserved                                      */
    uint64_t C_CROFFSET:6;   /* C row read offset                             */
    uint64_t C_RSVD8:2;      /* Reserved                                      */
    uint64_t C_CWOFFSET:6;   /* C row write offset for computations           */
    uint64_t C_RSVD9:2;      /* Reserved                                      */
    uint64_t C_CLOFFSET:7;   /* C row write offset for HWALD* instructions    */
    uint64_t C_RSVD10:1;     /* Reserved                                      */
    uint64_t C_CLSWPER:8;    /* C bank switch period for HWALD* instruction
                                writes                                        */
    uint64_t C_CLRSTPER:8;   /* C write row offset reset period for HWALD*    */
    uint64_t C_OP1PER:32;    /* Operation 1 period                            */

    uint64_t C_OP0PER:32;    /* Operation 0 period                            */
    uint64_t C_BSWPER:32;    /* B bank switch period                          */
    uint64_t C_CRSWPER:32;   /* C bank switch period for read instructions    */
    uint64_t C_CWSWPER:32;   /* C bank switch period for computation writes   */

    uint64_t C_CRRSTPER:8;   /* C read row offset reset period                */
    uint64_t C_CWRSTPER:8;   /* C write row offset reset period for
                                computations                                  */

    uint64_t X_ReLU:1;       /* Enable Rectified Linear Units non-linearity
                                after optional saturation                     */
    uint64_t X_PSAT:1;       /* Enable paramterized saturation function       */
    uint64_t X_SAT_MIN_5_0:6; /* Bits 0-5 of PSAT SAT_MIN                     */
    uint64_t X_SAT:1;         /* Enable saturation in the transfer buffer
                                 element type after optional rounding         */
    uint64_t X_SAT_MIN_12_6:7; /* Bits 6-12 of PSAT SAT_MIN                   */
    uint64_t X_RE:1;         /* Enable routing via 1/2 LSB addition after
                                shifting                                      */
    uint64_t X_SAT_MIN_15_13:3; /* Bits 13-15 of PSAT SAT_MIN                 */
    __MMA_X_CONFIG_RANGE X_RANGE:2; /* Min/Max range accumulation control on
                                       C matrix reads by X FSM                */
    __MMA_X_CONFIG_SCALE_SHIFT_CTRL X_SCALE_SHIFT_CTRL:1; /* Shift mode       */
    uint64_t X_RSVD3:1;      /* Reserved                                      */
    uint64_t X_SHIFT:7;      /* Right shift amount, signed or unsigned
                                depending on CTYPE field. Accepts
                                __MMA_X_CONFIG_SHIFT values when
                                X_SCALE_SHIFT_CTRL is enabled.                */
    __MMA_X_CONFIG_VPACKN X_VPACKN:1; /* 4-bit packing control                */
    __MMA_X_CONFIG_XTYPE X_XTYPE:4; /* Transfer buffer element type. Not all
                                       combinations of CTYPE and XTYPE are
                                       supported                              */
    uint64_t X_SAT_MAX_3_0:4; /* Bits 0-3 of PSAT SAT_MAX                     */
    __MMA_X_CONFIG_CTYPE X_CTYPE:3; /* C matrix element type. This must be
                                       consistent with the B FSM setting      */
    uint64_t X_SAT_MAX_8_4:5; /* Bits 4-8 of PSAT SAT_MAX                     */

    uint64_t X_CSWPER:32;    /* C read bank switch period                     */
    uint64_t X_CRRSTPER:8;   /* C read row offset reset period                */
    uint64_t X_COFFSET:8;    /* C matrix row read address offset              */
    uint64_t X_CSTART:1;     /* Initial C bank selection                      */
    uint64_t X_SAT_MAX_15_9:7; /* Bits 9-15 of PSAT SAT_MAX                   */

    uint64_t RSVD:6;         /* Reserved                                      */
    __MMA_PARITYCTRL PARITYCTRL:2; /* Parity control                          */
#else /* Big-endian */
    /* Invert on 64 bit boundaries */
    uint64_t B_BSWPER:32;    /* B banks switch period                         */

    uint64_t A_RSVD4:1;      /* Reserved                                      */
    uint64_t A_ARF_SIZE:7;   /* ARF array size for read and write operations  */
    uint64_t A_RSVD3:1;      /* Reserved                                      */
    uint64_t A_ARF_BASE:6;   /* Base value of circular buffer in the A operand
                                register file when ARF_CTRL is ARF_ENABLE     */
    __MMA_A_CONFIG_ARF_CTRL A_ARF_CTRL:1; /* A opnd register file wrt enable  */
    uint64_t A_RSVD2:7;       /* Reserved                                     */
    __MMA_A_LUTEN A_ALUTEN:1; /* A vector element lookup table                */
    uint64_t A_RSVD1:5;       /* Reserved                                     */
    __MMA_A_CONFIG_ATYPE A_ATYPE:3; /* A vector element type                  */
/*---- */
    uint64_t B_RSVD4:24;     /* Reserved                                      */
    uint64_t B_BOFFSET:8;    /* Global row or column offset                   */
    uint64_t B_RSVD3:6;      /* Reserved                                      */
    uint64_t B_BCNT1_ENABLE:1;/* Enable bit for option B row write row cntr for
                                 B bank 1.                                    */
    uint64_t B_BSTART:1;     /* Initial B bank selection for writing B matrix
                                data                                          */
    uint64_t B_RSVD2:7;      /* Reserved                                      */
    __MMA_B_CONFIG_ORDER_TRANSPOSE_CONTROL B_ORDER:1; /* Transpose control    */
    uint64_t B_RSVD1:2;      /* Reserved                                      */
    __MMA_B4EXP B_B4EXP:2;   /* B operand expansion control to conv 4-bit ops
                                to 8-bit ops                                  */
    __MMA_LDBOPT B_LDBOPT:2; /* Control for enhanced B operand row loading    */
    __MMA_B_BTYPE B_BTYPE:2; /* B matrix element type                         */
    uint64_t B_BRSTPER:8;    /* B offset reset period                         */
/*---- */
    uint64_t C_RSVD8:2;      /* Reserved                                      */
    uint64_t C_CROFFSET:6;   /* C row read offset                             */
    uint64_t C_RSVD7:3;      /* Reserved                                      */
    uint64_t C_CLSTART:1;    /* Initial C bank selection for writing operands 
                                from HWALD*                                   */
    uint64_t C_CWSTART:1;    /* Initial C bank selection for writing 
                                computation results                           */
    uint64_t C_CRSTART:1;    /* Initial C bank selection for reading operands */
    uint64_t C_BSTART:1;     /* Initial B bank selection for reading B matrix 
                                data for the matrix computations              */
    __MMA_C_CONFIG_OPSTART C_OPSTART:1; /* Initial C operand selection        */
    uint64_t C_RSVD6:4;      /* Reserved                                      */
    __MMA_C_CONFIG_HWLDTYPE C_HWLDTYPE:4; /* C matrix element type from a
                                             HWALD* instruction               */
    uint64_t C_RSVD5:5;      /* Reserved                                      */
    __MMA_C_CONFIG_HWLDDST C_HWLDDST:3;
    uint64_t C_RSVD4:4;      /* Reserved                                      */
    __MMA_C_CONFIG_BIASORDER C_BIASORDER:1; /* Transpose bias matrix          */
    __MMA_C_CONFIG_LOP C_LOP1:1; /* Left operand selection for C_OPERATION1   */
    __MMA_C_CONFIG_OPERATION C_OPERATION1:2;
    uint64_t C_RSVD3:5;      /* Reserved                                      */
    __MMA_C_CONFIG_LOP C_LOP0:1; /* Left operand selection for C_OPERATION0   */
    __MMA_C_CONFIG_OPERATION C_OPERATION0:2;
    uint64_t C_RSVD2:5;      /* Reserved                                      */
    __MMA_C_CONFIG_BTYPE C_BTYPE:3; /* B matrix element type and bias table
                                       element size. Must be consistent with
                                       the B FSM setting.                     */
    uint64_t C_ARF_C7:1;     /* ARF read addresses are supplied by the host C7
                                processor as an argument to the HWAOP or
                                HWAOPXFER instructions.                       */
    uint64_t C_ARF_BASE:6;   /* ARF read pointer base value when ARG_C7 is
                                cleared                                       */
    __MMA_C_CONFIG_ATYPE C_ATYPE:1; /* unsigned or signed                     */
/*---- */
    uint64_t C_OP1PER:32;    /* Operation 1 period                            */
    uint64_t C_CLRSTPER:8;   /* C write row offset reset period for HWALD*    */
    uint64_t C_CLSWPER:8;    /* C bank switch period for HWALD* instruction
                                writes                                        */
    uint64_t C_RSVD10:1;     /* Reserved                                      */
    uint64_t C_CLOFFSET:7;   /* C row write offset for HWALD* instructions    */
    uint64_t C_RSVD9:2;      /* Reserved                                      */
    uint64_t C_CWOFFSET:6;   /* C row write offset for computations           */
/*---- */
    uint64_t C_BSWPER:32;    /* B bank switch period                          */
    uint64_t C_OP0PER:32;    /* Operation 0 period                            */
/*---- */
    uint64_t C_CWSWPER:32;   /* C bank switch period for computation writes   */
    uint64_t C_CRSWPER:32;   /* C bank switch period for read instructions    */
/*---- */
    uint64_t X_SAT_MAX_8_4:5; /* Bits 4-8 of PSAT SAT_MAX                     */
    __MMA_X_CONFIG_CTYPE X_CTYPE:3; /* C matrix element type. This must be
                                       consistent with the B FSM setting      */
    uint64_t X_SAT_MAX_3_0:4; /* Bits 0-3 of PSAT SAT_MAX                     */
    __MMA_X_CONFIG_XTYPE X_XTYPE:4; /* Transfer buffer element type. Not all
                                       combinations of CTYPE and XTYPE are
                                       supported                              */
    __MMA_X_CONFIG_VPACKN X_VPACKN:1; /* 4-bit packing control                */
    uint64_t X_SHIFT:7;      /* Right shift amount, signed or unsigned
                                depending on CTYPE field. Accepts
                                __MMA_X_CONFIG_SHIFT values when
                                X_SCALE_SHIFT_CTRL is enabled.                */
    uint64_t X_RSVD3:1;      /* Reserved                                      */
    __MMA_X_CONFIG_SCALE_SHIFT_CTRL X_SCALE_SHIFT_CTRL:1; /* Shift mode       */
    __MMA_X_CONFIG_RANGE X_RANGE:2; /* Min/Max range accumulation control on
                                       C matrix reads by X FSM                */
    uint64_t X_SAT_MIN_15_13:3; /* Bits 13-15 of PSAT SAT_MIN                 */
    uint64_t X_RE:1;         /* Enable routing via 1/2 LSB addition after
                                shifting                                      */
    uint64_t X_SAT_MIN_12_6:7; /* Bits 6-12 of PSAT SAT_MIN                   */
    uint64_t X_SAT:1;         /* Enable saturation in the transfer buffer
                                 element type after optional rounding         */
    uint64_t X_SAT_MIN_5_0:6; /* Bits 0-5 of PSAT SAT_MIN                     */
    uint64_t X_PSAT:1;       /* Enable paramterized saturation function       */
    uint64_t X_ReLU:1;       /* Enable Rectified Linear Units non-linearity
                                after optional saturation                     */
    uint64_t C_CWRSTPER:8;   /* C write row offset reset period for
                                computations                                  */
    uint64_t C_CRRSTPER:8;   /* C read row offset reset period                */

/*---- */
    __MMA_PARITYCTRL PARITYCTRL:2; /* Parity control                          */
    uint64_t RSVD:6;         /* Reserved                                      */
    uint64_t X_SAT_MAX_15_9:7; /* Bits 9-15 of PSAT SAT_MAX                   */
    uint64_t X_CSTART:1;     /* Initial C bank selection                      */
    uint64_t X_COFFSET:8;    /* C matrix row read address offset              */
    uint64_t X_CRRSTPER:8;   /* C read row offset reset period                */
    uint64_t X_CSWPER:32;    /* C read bank switch period                     */
#endif /* big_endian */
} __HWA_CONFIG_REG_v1;

/*----------------------------------------------------------------------------*/
/* __HWA_OFFSET_REG                                                           */
/* The same offset structure is used for both MMA1 and MMA2.                  */
/*----------------------------------------------------------------------------*/
typedef struct __attribute__((__packed__)) __HWA_OFFSET_REG_t
{
#if __little_endian__
    uint64_t offset0:6;
    uint64_t offset1:6;
    uint64_t offset2:6;
    uint64_t offset3:6;
    uint8_t A_LUT_VAL_0;
    uint64_t offset4:6;
    uint64_t offset5:6;
    uint64_t offset6:6;
    uint64_t offset7:6;
    uint8_t A_LUT_VAL_1;

    uint64_t offset8:6;
    uint64_t offset9:6;
    uint64_t offset10:6;
    uint64_t offset11:6;
    uint8_t A_LUT_VAL_2;
    uint64_t offset12:6;
    uint64_t offset13:6;
    uint64_t offset14:6;
    uint64_t offset15:6;
    uint8_t A_LUT_VAL_3;

    uint64_t offset16:6;
    uint64_t offset17:6;
    uint64_t offset18:6;
    uint64_t offset19:6;
    uint8_t A_LUT_VAL_4;
    uint64_t offset20:6;
    uint64_t offset21:6;
    uint64_t offset22:6;
    uint64_t offset23:6;
    uint8_t A_LUT_VAL_5;

    uint64_t offset24:6;
    uint64_t offset25:6;
    uint64_t offset26:6;
    uint64_t offset27:6;
    uint8_t A_LUT_VAL_6;
    uint64_t offset28:6;
    uint64_t offset29:6;
    uint64_t offset30:6;
    uint64_t offset31:6;
    uint8_t A_LUT_VAL_7;

    uint64_t offset32:6;
    uint64_t offset33:6;
    uint64_t offset34:6;
    uint64_t offset35:6;
    uint8_t A_LUT_VAL_8;
    uint64_t offset36:6;
    uint64_t offset37:6;
    uint64_t offset38:6;
    uint64_t offset39:6;
    uint8_t A_LUT_VAL_9;

    uint64_t offset40:6;
    uint64_t offset41:6;
    uint64_t offset42:6;
    uint64_t offset43:6;
    uint8_t A_LUT_VAL_10;
    uint64_t offset44:6;
    uint64_t offset45:6;
    uint64_t offset46:6;
    uint64_t offset47:6;
    uint8_t A_LUT_VAL_11;

    uint64_t offset48:6;
    uint64_t offset49:6;
    uint64_t offset50:6;
    uint64_t offset51:6;
    uint8_t A_LUT_VAL_12;
    uint64_t offset52:6;
    uint64_t offset53:6;
    uint64_t offset54:6;
    uint64_t offset55:6;
    uint8_t A_LUT_VAL_13;

    uint64_t offset56:6;
    uint64_t offset57:6;
    uint64_t offset58:6;
    uint64_t offset59:6;
    uint8_t A_LUT_VAL_14;
    uint64_t offset60:6;
    uint64_t offset61:6;
    uint64_t offset62:6;
    uint64_t offset63:6;
    uint8_t A_LUT_VAL_15;

#else /* elseif __big_endian__ */
    /* Invert on 64 bit boundaries */
    uint8_t A_LUT_VAL_1;
    uint64_t offset7:6;
    uint64_t offset6:6;
    uint64_t offset5:6;
    uint64_t offset4:6;
    uint8_t A_LUT_VAL_0;
    uint64_t offset3:6;
    uint64_t offset2:6;
    uint64_t offset1:6;
    uint64_t offset0:6;

    uint8_t A_LUT_VAL_3;
    uint64_t offset15:6;
    uint64_t offset14:6;
    uint64_t offset13:6;
    uint64_t offset12:6;
    uint8_t A_LUT_VAL_2;
    uint64_t offset11:6;
    uint64_t offset10:6;
    uint64_t offset9:6;
    uint64_t offset8:6;

    uint8_t A_LUT_VAL_5;
    uint64_t offset23:6;
    uint64_t offset22:6;
    uint64_t offset21:6;
    uint64_t offset20:6;
    uint8_t A_LUT_VAL_4;
    uint64_t offset19:6;
    uint64_t offset18:6;
    uint64_t offset17:6;
    uint64_t offset16:6;

    uint8_t A_LUT_VAL_7;
    uint64_t offset31:6;
    uint64_t offset30:6;
    uint64_t offset29:6;
    uint64_t offset28:6;
    uint8_t A_LUT_VAL_6;
    uint64_t offset27:6;
    uint64_t offset26:6;
    uint64_t offset25:6;
    uint64_t offset24:6;

    uint8_t A_LUT_VAL_9;
    uint64_t offset39:6;
    uint64_t offset38:6;
    uint64_t offset37:6;
    uint64_t offset36:6;
    uint8_t A_LUT_VAL_8;
    uint64_t offset35:6;
    uint64_t offset34:6;
    uint64_t offset33:6;
    uint64_t offset32:6;

    uint8_t A_LUT_VAL_11;
    uint64_t offset47:6;
    uint64_t offset46:6;
    uint64_t offset45:6;
    uint64_t offset44:6;
    uint8_t A_LUT_VAL_10;
    uint64_t offset43:6;
    uint64_t offset42:6;
    uint64_t offset41:6;
    uint64_t offset40:6;

    uint8_t A_LUT_VAL_13;
    uint64_t offset55:6;
    uint64_t offset54:6;
    uint64_t offset53:6;
    uint64_t offset52:6;
    uint8_t A_LUT_VAL_12;
    uint64_t offset51:6;
    uint64_t offset50:6;
    uint64_t offset49:6;
    uint64_t offset48:6;

    uint8_t A_LUT_VAL_15;
    uint64_t offset63:6;
    uint64_t offset62:6;
    uint64_t offset61:6;
    uint64_t offset60:6;
    uint8_t A_LUT_VAL_14;
    uint64_t offset59:6;
    uint64_t offset58:6;
    uint64_t offset57:6;
    uint64_t offset56:6;
#endif /* __little_endian__ / __big_endian__ */
} __HWA_OFFSET_REG;

/******************************************************************************/
/* API Enumerations                                                           */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Enumeration for the third argument in the __HWAOPEN intrinsic              */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
{
    __MMA_OPEN_FSM_RESET    = 0,
    __MMA_OPEN_FSM_MINRESET = 2,
    __MMA_OPEN_FSM_MAXRESET = 3,
    __MMA_OPEN_FSM_LAST     = 3 /* Don't use directly. */
} __MMA_OPEN_FSM;

#if !defined(__C7X_MMA_1__)
/*----------------------------------------------------------------------------*/
/* Enumeration for the third argument in the __HWA_LOAD_2REG intrinsic        */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
{
    __MMA_LOAD_2REG_BIAS_1_0 = 8,   /* src1 to HWA_BIAS1, src2 to HWA_BIAS0   */
    __MMA_LOAD_2REG_BIAS_3_2 = 9,   /* src1 to HWA_BIAS3, src2 to HWA_BIAS2   */
    __MMA_LOAD_2REG_SCALE_1_0 = 10, /* src1 to HWA_SCALE1, src2 to HWA_SCALE0 */
    __MMA_LOAD_2REG_SHIFT_1_0 = 11, /* src1 to HWA_SHIFT1, src2 to HWA_SHIFT0 */
    __MMA_LOAD_2REG_BUSY  = 12,     /* src1 to HWA_BUSY, src2 unused          */
    __MMA_LOAD_2REG_LAST = 12 /* Don't use directly. */
} __MMA_LOAD_2REG;
#endif /* !__C7X_MMA_1__ */

/*----------------------------------------------------------------------------*/
/* Constants used in __HWAOP and __HWAOPXFER intrinsics                       */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
{
    __MMA_A_LDA         = 0,  /* 'A' vector sourced from most recent __HWALDA */
#if !defined(__C7X_MMA_1__)
    /* 1-3 reserved */
    __MMA_A_ARF_ROW_SA0 = 4,  /* Use ARF; SA0 value supplies ARF row index    */
    __MMA_A_ARF_ROW_SA1 = 5,  /* Use ARF; SA1 value supplies ARF row index    */
    __MMA_A_ARF_ROW_SA2 = 6,  /* Use ARF; SA2 value supplies ARF row index    */
    __MMA_A_ARF_ROW_SA3 = 7,  /* Use ARF; SA3 value supplies ARF row index    */
    /* 8-19 reserved */
    __MMA_A_ARF_ROW_SA0ADV = 20, /* Use ARF; SA0 value supplies ARF row index & advance SA0 */
    __MMA_A_ARF_ROW_SA1ADV = 21, /* Use ARF; SA1 value supplies ARF row index & advance SA1 */
    __MMA_A_ARF_ROW_SA2ADV = 22, /* Use ARF; SA2 value supplies ARF row index & advance SA2 */
    __MMA_A_ARF_ROW_SA3ADV = 23, /* Use ARF; SA3 value supplies ARF row index & advance SA3 */
#endif /* !__C7X_MMA_1__ */
    __MMA_A_SOURCE_SELECT_LAST = 23 /* Don't use directly. */
} __MMA_A_SOURCE_SELECT;

/*----------------------------------------------------------------------------*/
/* Constants used in __HWAXFER and __HWAOPXFER intrinsics                     */
/*----------------------------------------------------------------------------*/
#if !defined(__C7X_MMA_1__)
typedef enum __attribute__((__packed__))
{
    /* 0-3 reserved */
    __MMA_XFER_MASK_PSA0 = 4, /* Send PSA0 */
    __MMA_XFER_MASK_PSA1 = 5, /* Send PSA1 */
    __MMA_XFER_MASK_PSA2 = 6, /* Send PSA2 */
    __MMA_XFER_MASK_PSA3 = 7, /* Send PSA3 */
    /* 8-11 reserved */
    __MMA_XFER_MASK_PSA0ADV = 12, /* Send PSA0, then advance SA0 */
    __MMA_XFER_MASK_PSA1ADV = 13, /* Send PSA1, then advance SA1 */
    __MMA_XFER_MASK_PSA2ADV = 14, /* Send PSA2, then advance SA2 */
    __MMA_XFER_MASK_PSA3ADV = 15, /* Send PSA3, then advance SA3 */
    __MMA_XFER_MASK_LAST    = 15  /* Don't use directly. */
} __MMA_XFER_MASK;
#endif /* !__C7X_MMA_1__ */

/*----------------------------------------------------------------------------*/
/* Constants used in __HWAXFER intrinsic                                      */
/*----------------------------------------------------------------------------*/
typedef enum __attribute__((__packed__))
{
    __MMA_XFER_SRC_C = 0,     /* C matrix, X FSM sequences C matrix addresses */
    /* 1-3 reserved */
#if !defined(__C7X_MMA_1__)
    __MMA_XFER_SRC_HWA_SCALE0 = 4,  /* HWA_SCALE0, no X FSM update */
    __MMA_XFER_SRC_HWA_SCALE1 = 5,  /* HWA_SCALE1, no X FSM update */
    __MMA_XFER_SRC_HWA_SHIFT0 = 6,  /* HWA_SHIFT0, no X FSM update */
    __MMA_XFER_SRC_HWA_SHIFT1 = 7,  /* HWA_SHIFT1, no X FSM update */
#endif /* !__C7X_MMA_1__ */
    /* 4-7 reserved */
    __MMA_XFER_SRC_HWA_CONFIG = 8,  /* HWA_CONFIG, no X FSM update */
    __MMA_XFER_SRC_HWA_OFFSET = 9,  /* HWA_OFFSET, no X FSM update */
    __MMA_XFER_SRC_HWA_STATUS = 10, /* HWA_STATUS, no X FSM update */
    __MMA_XFER_SRC_HWA_BUSY   = 11, /* HWA_BUSY,   no X FSM update */
#if !defined(__C7X_MMA_1__)
    __MMA_XFER_SRC_HWA_BIAS0 = 12,  /* HWA_BIAS0, no X FSM update */
    __MMA_XFER_SRC_HWA_BIAS1 = 13,  /* HWA_BIAS1, no X FSM update */
    __MMA_XFER_SRC_HWA_BIAS2 = 14,  /* HWA_BIAS2, no X FSM update */
    __MMA_XFER_SRC_HWA_BIAS3 = 15,  /* HWA_BIAS3, no X FSM update */
#endif /* !__C7X_MMA_1__ */
    __MMA_XFER_SRC_LAST      = 15   /* Don't use directly. */
} __MMA_XFER_SRC;

/******************************************************************************/
/* Core API                                                                   */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Use the __HWA_CONFIG_REG_v1/v2 and __HWA_OFFSET_REG structs that are       */
/* defined in this file to set up the necessary parameters for the MMA. The   */
/* programmer should pass an enum value from the __MMA_OPEN_FSM enum typedef  */
/* to the mma_open_fsm parameter (see the MMA specification for full          */
/* details).                                                                  */
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/* Implementation details.  Do not use directly.                              */
/*----------------------------------------------------------------------------*/
void      __BIFM __hwaopen(__ulong8, __ulong8, __CST(0, 3) __MMA_OPEN_FSM); /* Deprecated, do not use */

/*----------------------------------------------------------------------------*/
/* void __HWAOPEN(__HWA_CONFIG_REG_vn, __HWA_OFFSET_REG, __MMA_OPEN_FSM)      */
/*   Configures and opens the MMA.                                            */
/*----------------------------------------------------------------------------*/
void      __OVBIFM __HWAOPEN(__HWA_CONFIG_REG_v1, __HWA_OFFSET_REG, __CST(0,3) __MMA_OPEN_FSM);
#define __HWAOPEN(a, b, c) __overload("__HWAOPEN",(a),(b),(c))((a),(b),(c))

#if !defined(__C7X_MMA_1__)
/*----------------------------------------------------------------------------*/
/* void __HWA_LOAD_2REG(src1, src2, __MMA_LOAD_2REG)                          */
/*   Loads values into MMA two MMA registers specified by the __MMA_LOAD_2REG */
/*   argument.                                                                */
/*----------------------------------------------------------------------------*/
void      __BIFM __HWA_LOAD_2REG(__mma_vec, __mma_vec, __CST(8,12) __MMA_LOAD_2REG);
#endif /* !__C7X_MMA_1__ */

/*----------------------------------------------------------------------------*/
/* void __HWACLOSE(uint32_t dst)                                              */
/*   Closes the MMA. A constant literal value of 0 should be passed as dst.   */
/*----------------------------------------------------------------------------*/
void      __BIFM __HWACLOSE(__CST(0, 0) int);

/*----------------------------------------------------------------------------*/
/* void __HWALD*(__mma_vec src2)                                              */
/*   Load one row into a single MMA storage area.                             */
/*----------------------------------------------------------------------------*/
void      __BIFM __HWALDA(__mma_vec src1);
void      __BIFM __HWALDB(__mma_vec src1);
void      __BIFM __HWALDC(__mma_vec src1);

/*----------------------------------------------------------------------------*/
/* void __HWALD**(__mma_vec src2)                                             */
/*   Load one row into the first MMA storage area and another row into the    */
/*   other MMA storage area.                                                  */
/*----------------------------------------------------------------------------*/
void      __BIFM __HWALDAB(__mma_vec src1, __mma_vec src2);
void      __BIFM __HWALDBC(__mma_vec src1, __mma_vec src2);

/*----------------------------------------------------------------------------*/
/* void __HWAOP(__MMA_A_SOURCE_SELECT)                                        */
/*   Perform one operation on the MMA using the specified source.             */
/*----------------------------------------------------------------------------*/
void      __BIFM __HWAOP(__CST(0,23) __MMA_A_SOURCE_SELECT src1);

/*----------------------------------------------------------------------------*/
/* void __HWAXFER(__MMA_XFER_SRC)                                             */
/*   Load the MMA transfer buffer for the specified source.                   */
/*----------------------------------------------------------------------------*/
void      __BIFM __HWAXFER(__CST(0, 15) __MMA_XFER_SRC);

#if !defined(__C7X_MMA_1__)
/*----------------------------------------------------------------------------*/
/* void __HWAXFER_XSTATUS_DELAYED()                                           */
/*   In order to obtain the min/max values from the X_STATUS register, this   */
/*   intrinsic should be used instead of a normal __HWAXFER. This intrinsic   */
/*   loads the MMA transfer buffer with the X_STATUS register after an        */
/*   appropriate delay to allow the last C panel HWAXFER to write the min and */
/*   max values in the X_STATUS register.                                     */
/*                                                                            */
/*   Note that the programmer must do three things in order to have the       */
/*   min/max values recorded during MMA transfer of the C panel values:       */
/*   (1) Open the MMA with an MMA config reg where the __MMA_X_CONFIG_RANGE   */
/*       field is set to either                                               */
/*         __MMA_X_CONFIG_RANGE_ENABLE_INIT, or                               */
/*         __MMA_X_CONFIG_RANGE_ENABLE_NOINIT, and                            */
/*   (2) use a XFER_MASK_PSA enum value in the regular C panel value          */
/*       __HWAXFER_MASK instructions, e.g.:                                   */
/*       __HWAXFERH(__MMA_XFER_SRC_C, __MMA_XFER_MASK_PSA0);                  */
/*       and                                                                  */
/*   (3) have the associated SA set up so that appropriate C panel values are */
/*       masked/not-masked during transfer.                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/
void      __BIFM __HWAXFER_XSTATUS_DELAYED();

/* Implementation detail, do not use directly */
void      __BIFM __hwaxfer_mask(__CST(0,15) __MMA_XFER_SRC, __CST(4,15) __MMA_XFER_MASK, __CST(1,2) int scale);

/*----------------------------------------------------------------------------*/
/* void __HWAXFER_MASK(type,__MMA_XFER_SRC,__MMA_XFER_MASK)                   */
/*   Perform a transfer with masking. "type" may be an 8 or 16 bit type.      */
/*----------------------------------------------------------------------------*/
#define __HWAXFER_MASK(type,src,mask) __hwaxfer_mask(src,mask,sizeof(type)/__numelemof(type))

/*----------------------------------------------------------------------------*/
/* void __HWAXFERB(__MMA_XFER_SRC,__MMA_XFER_MASK)                            */
/*   Convenience API. Maps to __HWAXFER_MASK with char type.                  */
/*----------------------------------------------------------------------------*/
#define __HWAXFERB(src,mask) __HWAXFER_MASK(char,src,mask)

/*----------------------------------------------------------------------------*/
/* void __HWAXFERH(__MMA_XFER_SRC,__MMA_XFER_MASK)                            */
/*   Convenience API. Maps to __HWAXFER_MASK with short type.                 */
/*----------------------------------------------------------------------------*/
#define __HWAXFERH(src,mask) __HWAXFER_MASK(short,src,mask)
#endif /* !__C7X_MMA_1__ */

/*----------------------------------------------------------------------------*/
/* void __HWAFENCE_OPXFER()                                                   */
/*   Creates a barrier for scheduling that a MMA OP (__HWAOP) or MMA transfer */
/*   (__HWAXFER) cannot move past.                                            */
/*   When compiled under host emulation, __HWAFENCE_OPXFER does nothing.      */
/*----------------------------------------------------------------------------*/
void      __BIFM __HWAFENCE_OPXFER();

/*----------------------------------------------------------------------------*/
/* void __HWAOPXFER(__MMA_A_SOURCE_SELECT)                                    */
/*   Perform one operation on the MMA using the specified source and one      */
/*   transfer.                                                                */
/*----------------------------------------------------------------------------*/
void      __BIFM __HWAOPXFER(__CST(0,23) __MMA_A_SOURCE_SELECT src1);

#if !defined(__C7X_MMA_1__)
/* Implementation detail, do not use directly */
void      __BIFM __hwaopxfer_mask(__CST(0,23) __MMA_A_SOURCE_SELECT, __CST(4,15) __MMA_XFER_MASK, __CST(1,2) int scale);

/*----------------------------------------------------------------------------*/
/* void __HWAOPXFER_MASK(type,__MMA_A_SOURCE_SELECT,__MMA_XFER_MASK)          */
/*   Perform an operation and transfer with masking. "type" may be an 8 or 16 */
/*   bit type.                                                                */
/*----------------------------------------------------------------------------*/
#define __HWAOPXFER_MASK(type,src,mask) __hwaopxfer_mask(src,mask,sizeof(type)/__numelemof(type))

/*----------------------------------------------------------------------------*/
/* void __HWAOPXFERB(__MMA_A_SOURCE_SELECT,__MMA_XFER_MASK)                   */
/*   Convenience API. Maps to __HWAOPXFER_MASK with char type.                */
/*----------------------------------------------------------------------------*/
#define __HWAOPXFERB(src,mask) __HWAOPXFER_MASK(char,src,mask)

/*----------------------------------------------------------------------------*/
/* void __HWAOPXFERH(__MMA_A_SOURCE_SELECT,__MMA_XFER_MASK)                   */
/*   Convenience API. Maps to __HWAOPXFER_MASK with short type.               */
/*----------------------------------------------------------------------------*/
#define __HWAOPXFERH(src,mask) __HWAOPXFER_MASK(short,src,mask)
#endif /* !__C7X_MMA_1__ */

/*----------------------------------------------------------------------------*/
/* __mma_vec __HWARCV(uint32_t)                                               */
/*   Retrieves data from the MMA transfer buffer. A constant literal value of */
/*   0 should be passed as index.                                             */
/*----------------------------------------------------------------------------*/
__mma_vec __BIFM __HWARCV(__CST(0,0) int); /* S-unit HWARCV (with constant) */

/*----------------------------------------------------------------------------*/
/* void __HWASWAP(uint32_t)                                                   */
/*   Prevents high level optimization between two MMA loops. In particular,   */
/*   it will prevent loop fusion. Under host emulation mode, it does nothing. */
/*----------------------------------------------------------------------------*/
void      __BIFM __HWASWAP(__CST(0, 0) int); 

/*----------------------------------------------------------------------------*/
/* void __HWAADV()                                                            */
/*   Models an advance of the MMA finite state machines. When compiling with  */
/*   the target compiler, __HWAADV does nothing.                              */
/*----------------------------------------------------------------------------*/
#define   __HWAADV()        /* Empty macro; API used only by Host Emulation */


/******************************************************************************/
/* Helper API -- Initializations                                              */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* Generate an __HWA_CONFIG_REG_v1 with safe default values                   */
/*----------------------------------------------------------------------------*/
_IDEFN __HWA_CONFIG_REG_v1 __attribute__((__always_inline__))
__gen_HWA_CONFIG_REG_v1()
{
    const __HWA_CONFIG_REG_v1 config =
    {
#if __little_endian__
        /* A_ATYPE            = */ __MMA_A_CONFIG_ATYPE_UINT8,
        /* A_RSVD1            = */ 0,
        /* A_A_LUTEN          = */ __MMA_A_CONFIG_NOLUT,
        /* A_RSVD2            = */ 0,
        /* A_ARF_CTRL         = */ __MMA_A_CONFIG_ARF_DISABLE,
        /* A_ARF_BASE         = */ 0,
        /* A_RSVD3            = */ 0,
        /* A_ARF_SIZE         = */ 0,
        /* A_RSVD4            = */ 0,
        /* B_BSWPER           = */ 0,
        /* B_BRSTPER          = */ 0,
        /* B_BTYPE            = */ __MMA_B_CONFIG_SIZE8,
        /* B_LDBOPT           = */ __MMA_LDBOPT_MMA1,
        /* B_B4EXP            = */ __MMA_B_CONFIG_B4EXP_MMA1,
        /* B_RSVD1            = */ 0,
        /* B_ORDER            = */ __MMA_B_CONFIG_ROW,
        /* B_RSVD2            = */ 0,
        /* B_BSTART           = */ 0,
        /* B_BCNT1_ENABLE     = */ 0,
        /* B_RSVD3            = */ 0,
        /* B_BOFFSET          = */ 0,
        /* B_RSVD4            = */ 0,
        /* C_ATYPE            = */ __MMA_C_CONFIG_ATYPE_UA,
        /* C_ARF_BASE         = */ 0,
        /* C_ARF_C7           = */ 0,
        /* C_BTYPE            = */ __MMA_C_CONFIG_BTYPE_UINT8,
        /* C_RSVD2            = */ 0,
        /* C_OPERATION0       = */ __MMA_C_CONFIG_MUL,
        /* C_LOP0             = */ __MMA_C_CONFIG_LOP_C,
        /* C_RSVD3            = */ 0,
        /* C_OPERATION1       = */ __MMA_C_CONFIG_MUL,
        /* C_LOP1             = */ __MMA_C_CONFIG_LOP_C,
        /* C_BIASORDER        = */ __MMA_C_CONFIG_BIAS_ORDER_COLUMN,
        /* C_RSVD4            = */ 0,
        /* C_HWLDDST          = */ __MMA_C_CONFIG_HWLDDST_X4_0,
        /* C_RSVD5            = */ 0,
        /* C_HWLDTYPE         = */ __MMA_C_CONFIG_HWLDTYPE_UINT8,
        /* C_RSVD6            = */ 0,
        /* C_OPSTART          = */ __MMA_C_CONFIG_OPSTART_OPERATION0,
        /* C_BSTART           = */ 0,
        /* C_CRSTART          = */ 0,
        /* C_CWSTART          = */ 0,
        /* C_CLSTART          = */ 0,
        /* C_RSVD7            = */ 0,
        /* C_CROFFSET         = */ 0,
        /* C_RSVD8            = */ 0,
        /* C_CWOFFSET         = */ 0,
        /* C_RSVD9            = */ 0,
        /* C_CLOFFSET         = */ 0,
        /* C_RSVD10           = */ 0,
        /* C_CLSWTPER         = */ 0,
        /* C_CLRSTPER         = */ 0,
        /* C_OP1PER           = */ 0,
        /* C_OP0PER           = */ 0,
        /* C_BSWPER           = */ 0,
        /* C_CRSWPER          = */ 0,
        /* C_CWSWPER          = */ 0,
        /* C_CRRSTPER         = */ 0,
        /* C_CWRSTPER         = */ 0,
        /* X_ReLU             = */ 0,
        /* X_PSAT             = */ 0,
        /* X_SAT_MIN_5_0      = */ 0,
        /* X_SAT              = */ 0,
        /* X_SAT_MIN_12_6     = */ 0,
        /* X_RE               = */ 0,
        /* X_SAT_MIN_15_13    = */ 0,
        /* X_RANGE            = */ __MMA_X_CONFIG_RANGE_DISABLE_NOINIT,
        /* X_SCALE_SHIFT_CTRL = */ __MMA_X_CONFIG_SCALE_SHIFT_CTRL_DISABLE,
        /* X_RSVD3            = */ 0,
        /* X_SHIFT            = */ 0,
        /* X_VPACKN           = */ __MMA_X_CONFIG_VPACKN_DISABLE,
        /* X_XTYPE            = */ __MMA_X_CONFIG_XTYPE_UINT8,
        /* X_SAT_MAX_3_0      = */ 0,
        /* X_CTYPE            = */ __MMA_X_CONFIG_CTYPE_UINT32,
        /* X_SAT_MAX_8_4      = */ 0,
        /* X_CSWPER           = */ 0,
        /* X_CRRSTPER         = */ 0,
        /* X_COFFSET          = */ 0,
        /* X_CSTART           = */ 0,
        /* X_SAT_MAX_15_9     = */ 0,
        /* X_RSVD6            = */ 0,
        /* PARITYCTRL         = */ __MMA_NORMAL
#else /* __big_endian__ */
        /* Invert on 64 bit boundaries */
        /* B_BSWPER           = */ 0,
        /* A_RSVD4            = */ 0,
        /* A_ARF_SIZE         = */ 0,
        /* A_RSVD3            = */ 0,
        /* A_ARF_BASE         = */ 0,
        /* A_ARF_CTRL         = */ __MMA_A_CONFIG_ARF_DISABLE,
        /* A_RSVD2            = */ 0,
        /* A_A_LUTEN          = */ __MMA_A_CONFIG_NOLUT,
        /* A_RSVD1            = */ 0,
        /* A_ATYPE            = */ __MMA_A_CONFIG_ATYPE_UINT8,

        /* B_RSVD4            = */ 0,
        /* B_BOFFSET          = */ 0,
        /* B_RSVD3            = */ 0,
        /* B_BCNT1_ENABLE     = */ 0,
        /* B_BSTART           = */ 0,
        /* B_RSVD2            = */ 0,
        /* B_ORDER            = */ __MMA_B_CONFIG_ROW,
        /* B_RSVD1            = */ 0,
        /* B_B4EXP            = */ __MMA_B_CONFIG_B4EXP_MMA1,
        /* B_LDBOPT           = */ __MMA_LDBOPT_MMA1,
        /* B_BTYPE            = */ __MMA_B_CONFIG_SIZE8,
        /* B_BRSTPER          = */ 0,

        /* C_RSVD8            = */ 0,
        /* C_CROFFSET         = */ 0,
        /* C_RSVD7            = */ 0,
        /* C_CLSTART          = */ 0,
        /* C_CWSTART          = */ 0,
        /* C_CRSTART          = */ 0,
        /* C_BSTART           = */ 0,
        /* C_OPSTART          = */ __MMA_C_CONFIG_OPSTART_OPERATION0,
        /* C_RSVD6            = */ 0,
        /* C_HWLDTYPE         = */ __MMA_C_CONFIG_HWLDTYPE_UINT8,
        /* C_RSVD5            = */ 0,
        /* C_HWLDDST          = */ __MMA_C_CONFIG_HWLDDST_X4_0,
        /* C_RSVD4            = */ 0,
        /* C_BIASORDER        = */ __MMA_C_CONFIG_BIAS_ORDER_COLUMN,
        /* C_LOP1             = */ __MMA_C_CONFIG_LOP_C,
        /* C_OPERATION1       = */ __MMA_C_CONFIG_MUL,
        /* C_RSVD3            = */ 0,
        /* C_LOP0             = */ __MMA_C_CONFIG_LOP_C,
        /* C_OPERATION0       = */ __MMA_C_CONFIG_MUL,
        /* C_RSVD2            = */ 0,
        /* C_BTYPE            = */ __MMA_C_CONFIG_BTYPE_UINT8,
        /* C_ARF_C7           = */ 0,
        /* C_ARF_BASE         = */ 0,
        /* C_ATYPE            = */ __MMA_C_CONFIG_ATYPE_UA,

        /* C_OP1PER           = */ 0,
        /* C_CLRSTPER         = */ 0,
        /* C_CLSWPER          = */ 0,
        /* C_RSVD10           = */ 0,
        /* C_CLOFFSET         = */ 0,
        /* C_RSVD9            = */ 0,
        /* C_CWOFFSET         = */ 0,

        /* C_BSWPER           = */ 0,
        /* C_OP0PER           = */ 0,

        /* C_CWSWPER          = */ 0,
        /* C_CRSWPER          = */ 0,

        /* X_SAT_MAX_8_4      = */ 0,
        /* X_CTYPE            = */ __MMA_X_CONFIG_CTYPE_UINT32,
        /* X_SAT_MAX_3_0      = */ 0,
        /* X_XTYPE            = */ __MMA_X_CONFIG_XTYPE_UINT8,
        /* X_VPACKN           = */ __MMA_X_CONFIG_VPACKN_DISABLE,
        /* X_SHIFT            = */ 0,
        /* X_RSVD3            = */ 0,
        /* X_SCALE_SHIFT_CTRL = */ __MMA_X_CONFIG_SCALE_SHIFT_CTRL_DISABLE,
        /* X_RANGE            = */ __MMA_X_CONFIG_RANGE_DISABLE_NOINIT,
        /* X_SAT_MIN_15_13    = */ 0,
        /* X_RE               = */ 0,
        /* X_SAT_MIN_12_6     = */ 0,
        /* X_SAT              = */ 0,
        /* X_SAT_MIN_5_0      = */ 0,
        /* X_PSAT             = */ 0,
        /* X_ReLU             = */ 0,
        /* C_CWRSTPER         = */ 0,
        /* C_CRRSTPER         = */ 0,

        /* PARITYCTRL         = */ __MMA_NORMAL,
        /* X_RSVD6            = */ 0,
        /* X_SAT_MAX_15_9     = */ 0,
        /* X_CSTART           = */ 0,
        /* X_COFFSET          = */ 0,
        /* X_CRRSTPER         = */ 0,
        /* X_CSWPER           = */ 0
#endif /* big_endian */
    };
    return config;
}

/*----------------------------------------------------------------------------*/
/* Generate an __HWA_OFFSET_REG with default values (all 0's)                 */
/*----------------------------------------------------------------------------*/
_IDEFN __HWA_OFFSET_REG __attribute__((__always_inline__)) __gen_HWA_OFFSET_REG()
{
    const __HWA_OFFSET_REG offset =
    {
#if __little_endian__
        /* offset0      = */ 0,
        /* offset1      = */ 0,
        /* offset2      = */ 0,
        /* offset3      = */ 0,
        /* A_LUT_VAL_0  = */ 0,
        /* offset4      = */ 0,
        /* offset5      = */ 0,
        /* offset6      = */ 0,
        /* offset7      = */ 0,
        /* A_LUT_VAL_1  = */ 0,

        /* offset8      = */ 0,
        /* offset9      = */ 0,
        /* offset10     = */ 0,
        /* offset11     = */ 0,
        /* A_LUT_VAL_2  = */ 0,
        /* offset12     = */ 0,
        /* offset13     = */ 0,
        /* offset14     = */ 0,
        /* offset15     = */ 0,
        /* A_LUT_VAL_3  = */ 0,

        /* offset16     = */ 0,
        /* offset17     = */ 0,
        /* offset18     = */ 0,
        /* offset19     = */ 0,
        /* A_LUT_VAL_4  = */ 0,
        /* offset20     = */ 0,
        /* offset21     = */ 0,
        /* offset22     = */ 0,
        /* offset23     = */ 0,
        /* A_LUT_VAL_5  = */ 0,

        /* offset24     = */ 0,
        /* offset25     = */ 0,
        /* offset26     = */ 0,
        /* offset27     = */ 0,
        /* A_LUT_VAL_6  = */ 0,
        /* offset28     = */ 0,
        /* offset29     = */ 0,
        /* offset30     = */ 0,
        /* offset31     = */ 0,
        /* A_LUT_VAL_7  = */ 0,

        /* offset32     = */ 0,
        /* offset33     = */ 0,
        /* offset34     = */ 0,
        /* offset35     = */ 0,
        /* A_LUT_VAL_8  = */ 0,
        /* offset36     = */ 0,
        /* offset37     = */ 0,
        /* offset38     = */ 0,
        /* offset39     = */ 0,
        /* A_LUT_VAL_9  = */ 0,

        /* offset40     = */ 0,
        /* offset41     = */ 0,
        /* offset42     = */ 0,
        /* offset43     = */ 0,
        /* A_LUT_VAL_10 = */ 0,
        /* offset44     = */ 0,
        /* offset45     = */ 0,
        /* offset46     = */ 0,
        /* offset47     = */ 0,
        /* A_LUT_VAL_11 = */ 0,

        /* offset48     = */ 0,
        /* offset49     = */ 0,
        /* offset50     = */ 0,
        /* offset51     = */ 0,
        /* A_LUT_VAL_12 = */ 0,
        /* offset52     = */ 0,
        /* offset53     = */ 0,
        /* offset54     = */ 0,
        /* offset55     = */ 0,
        /* A_LUT_VAL_13 = */ 0,

        /* offset56     = */ 0,
        /* offset57     = */ 0,
        /* offset58     = */ 0,
        /* offset59     = */ 0,
        /* A_LUT_VAL_14 = */ 0,
        /* offset60     = */ 0,
        /* offset61     = */ 0,
        /* offset62     = */ 0,
        /* offset63     = */ 0,
        /* A_LUT_VAL_15 = */ 0
#else /* __big_endian__ */
        /* Invert on 64 bit boundaries */
        /* A_LUT_VAL_1  = */ 0,
        /* offset7      = */ 0,
        /* offset6      = */ 0,
        /* offset5      = */ 0,
        /* offset4      = */ 0,
        /* A_LUT_VAL_0  = */ 0,
        /* offset3      = */ 0,
        /* offset2      = */ 0,
        /* offset1      = */ 0,
        /* offset0      = */ 0,

        /* A_LUT_VAL_3  = */ 0,
        /* offset15     = */ 0,
        /* offset14     = */ 0,
        /* offset13     = */ 0,
        /* offset12     = */ 0,
        /* A_LUT_VAL_2  = */ 0,
        /* offset11     = */ 0,
        /* offset10     = */ 0,
        /* offset9      = */ 0,
        /* offset8      = */ 0,

        /* A_LUT_VAL_5  = */ 0,
        /* offset23     = */ 0,
        /* offset22     = */ 0,
        /* offset21     = */ 0,
        /* offset20     = */ 0,
        /* A_LUT_VAL_4  = */ 0,
        /* offset19     = */ 0,
        /* offset18     = */ 0,
        /* offset17     = */ 0,
        /* offset16     = */ 0,

        /* A_LUT_VAL_7  = */ 0,
        /* offset31     = */ 0,
        /* offset30     = */ 0,
        /* offset29     = */ 0,
        /* offset28     = */ 0,
        /* A_LUT_VAL_6  = */ 0,
        /* offset27     = */ 0,
        /* offset26     = */ 0,
        /* offset25     = */ 0,
        /* offset24     = */ 0,

        /* A_LUT_VAL_9  = */ 0,
        /* offset39     = */ 0,
        /* offset38     = */ 0,
        /* offset37     = */ 0,
        /* offset36     = */ 0,
        /* A_LUT_VAL_8  = */ 0,
        /* offset35     = */ 0,
        /* offset34     = */ 0,
        /* offset33     = */ 0,
        /* offset32     = */ 0,

        /* A_LUT_VAL_11 = */ 0,
        /* offset47     = */ 0,
        /* offset46     = */ 0,
        /* offset45     = */ 0,
        /* offset44     = */ 0,
        /* A_LUT_VAL_10 = */ 0,
        /* offset43     = */ 0,
        /* offset42     = */ 0,
        /* offset41     = */ 0,
        /* offset40     = */ 0,

        /* A_LUT_VAL_13 = */ 0,
        /* offset55     = */ 0,
        /* offset54     = */ 0,
        /* offset53     = */ 0,
        /* offset52     = */ 0,
        /* A_LUT_VAL_12 = */ 0,
        /* offset51     = */ 0,
        /* offset50     = */ 0,
        /* offset49     = */ 0,
        /* offset48     = */ 0,

        /* A_LUT_VAL_15 = */ 0,
        /* offset63     = */ 0,
        /* offset62     = */ 0,
        /* offset61     = */ 0,
        /* offset60     = */ 0,
        /* A_LUT_VAL_14 = */ 0,
        /* offset59     = */ 0,
        /* offset58     = */ 0,
        /* offset57     = */ 0,
        /* offset56     = */ 0
#endif /* __little_endian__ / __big_endian__ */
    };
    return offset;
}

#if !defined(__C7X_MMA_1__)
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Helpful initialization functions for the SAT_MAX and SAT_MIN bitfields     */
/* located in the __HWA_CONFIG_REG. The max or min values is placed into      */
/* three separate bitfields in the __HWA_CONFIG_REG struct.                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/
_IDEFN void __attribute__((__always_inline__))
__set_HWA_SAT_MAX(__HWA_CONFIG_REG_v1 *config, uint16_t max)
{
    config->X_SAT_MAX_3_0  =  (max       /*& 0xf*/);  /* 4 bits [3:0] */
    config->X_SAT_MAX_8_4  = ((max >> 4) /*& 0x1f*/); /* 5 bits [8:4] */
    config->X_SAT_MAX_15_9 = ((max >> 9) /*& 0x7f*/); /* 7 bits [15:9] */
}

_IDEFN void __attribute__((__always_inline__))
__set_HWA_SAT_MIN(__HWA_CONFIG_REG_v1 *config, uint16_t min)
{
    config->X_SAT_MIN_5_0   =  (min        /*& 0x3f*/); /* 6 bits [5:0] */
    config->X_SAT_MIN_12_6  = ((min >>  6) /*& 0x7f*/); /* 7 bits [12:6] */
    config->X_SAT_MIN_15_13 = ((min >> 13) /*&  0x7*/); /* 3 bits [15:13] */
}
#endif /* !__C7X_MMA_1__ */

#endif /* __C7X_MMA__ */

#ifdef __cplusplus
}
#endif

#endif /* __C7X_MMA_H */
