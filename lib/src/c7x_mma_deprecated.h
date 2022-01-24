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

/*****************************************************************************/
/*                                                                           */
/* NOTE!!!                                                                   */
/* NOTE!!!                                                                   */
/* NOTE!!!                                                                   */
/* NOTE!!!                                                                   */
/* NOTE!!!                                                                   */
/*                                                                           */
/* DO NOT USE THIS OLD AND DEPRECATED API FOR THE MMA FEATURE. THIS API HAS  */
/* BEEN DEPRECATED AND WILL BE REMOVED IN A FUTURE VERSION OF THE COMPILER   */
/* TOOLS. THIS DEPRECATED API IS ONLY PROVIDED FOR BACKWARDS COMPATIBILITY   */
/* WITH OLDER SOURCE CODE.                                                   */
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

#ifndef __C7X_MMA_DEPRECATED_H
#define __C7X_MMA_DEPRECATED_H

#include <stdint.h>

/*----------------------------------------------------------------------------*/
/*                                                                            */
/* This file contains two structure definitions, enumerations, intrinsic      */
/* declarations, and a macro to enable use of the MMA.                        */
/*                                                                            */
/* Two structs are to be used with the __HWAOPEN intrinsic:                   */
/*   __HWA_CONFIG_REG_v1/v2  -  contains fields to setup the MMA              */
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
/*   __HWARCV                                                                 */
/*                                                                            */
/* Example usage:                                                             */
/*                                                                            */
/* // In a place that is executed only once or rarely, set the fields for the */
/* // HWA_CONFIG_REG_v1/v2:                                                   */
/*                                                                            */
/* __HWA_CONFIG_REG_v1 mma_config_reg; // Create instance of the config struct*/
/* __gen_HWA_CONFIG_REG_v1(&mma_config_reg); // Set all fields to zero        */
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
/*                                                                            */
/* This file contains two structure definitions, enumerations, intrinsic      */
/* declarations, and a macro to enable use of the MMA.                        */
/*                                                                            */
/* Two structs are to be used with the __HWAOPEN intrinsic:                   */
/*   __HWA_CONFIG_REG  -  contains fields to setup the MMA                    */
/*   __HWA_OFFSET_REG  -  contains fields to setup the MMA                    */
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
/*   __HWARCV                                                                 */
/*                                                                            */
/* Example usage:                                                             */
/*                                                                            */
/* // At the file scope, declare a MMA config reg to setup most of the        */
/* // MMA config and offset fields at compile time (if those fields are       */
/* // known at compile time).                                                 */
/*                                                                            */
/* __HWA_CONFIG_REG mma_config_reg =                                          */
/* {                                                                          */
/*     .A_ATYPE = A_CONFIG_ATYPE_INT32, // See enumeration declarations below */
/*     .A_RSVD1 = 0,                    // Please set all RSVD fields to zero */
/*     ...                                                                    */
/*     .PARITYCTRL = PCNM_NCK                                                 */
/* };                                                                         */
/*                                                                            */
/* // Do the same with __HWA_OFFSET_REG...                                    */
/* __HWA_OFFSET_REG mma_offset_reg =                                          */
/* {                                                                          */
/*     ...                                                                    */
/* };                                                                         */
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

/*----------------------------------------------------------------------------*/
/* Enumeration for the third argument in the __HWAOPEN intrinsic              */
/*----------------------------------------------------------------------------*/
typedef enum
{
    __MMA_OPEN_FSM_RESET         = 0,
    __MMA_OPEN_FSM_MINRESET      = 2,
    __MMA_OPEN_FSM_MAXRESET      = 3
} __MMA_OPEN_FSM;

/*----------------------------------------------------------------------------*/
/* __HWA_CONFIG_REG struct for use with MMA initialization with the __HWAOPEN */
/* intrinsic (see above).                                                     */
/* This struct needs to be cast to a ulong8 when being loaded/stored. Do this */
/* with the __HWAOPEN intrinsic (See example usage above).                    */
/*----------------------------------------------------------------------------*/
typedef struct __attribute__((__packed__)) __HWA_CONFIG_REG_t
{
#if __little_endian__
    uint64_t A_ATYPE:3;    /* A vector element type                           */
    uint64_t A_RSVD1:5;    /* Reserved                                        */
    uint64_t A_ALUTEN:1;   /* A vector element lookup table                   */
    uint64_t A_RSVD2:23;   /* Reserved                                        */

    uint64_t B_BSWPER:32;  /* B banks switch period                           */
    uint64_t B_BRSTPER:8;  /* B offset reset period                           */
    uint64_t B_BTYPE:2;    /* B matrix element type                           */
    uint64_t B_RSVD1:6;    /* Reserved                                        */
    uint64_t B_ORDER:1;    /* Transpose control                               */
    uint64_t B_RSVD2:7;    /* Reserved                                        */
    uint64_t B_BSTART:1;   /* Initial B bank selection for writing B matrix
                              data                                            */
    uint64_t B_RSVD3:7;    /* Reserved                                        */
    uint64_t B_BOFFSET:8;  /* Global row or column offset                     */
    uint64_t B_RSVD4:24;   /* Reserved                                        */

    uint64_t C_ATYPE:1;    /* unsigned or signed                              */
    uint64_t C_RSVD1:7;    /* Reserved                                        */
    uint64_t C_BTYPE:3;
    uint64_t C_RSVD2:5;    /* Reserved                                        */
    uint64_t C_OPERATION0:2;
    uint64_t C_RSVD3:6;    /* Reserved                                        */
    uint64_t C_OPERATION1:2;
    uint64_t C_RSVD4:6;    /* Reserved                                        */
    uint64_t C_HWLDDST:3;
    uint64_t C_RSVD5:5;    /* Reserved                                        */
    uint64_t C_HWLDTYPE:4; /* C matrix element type from a HWALD* instruction */
    uint64_t C_RSVD6:4;    /* Reserved                                        */
    uint64_t C_OPSTART:1;  /* Initial C operand selection                     */
    uint64_t C_BSTART:1;   /* Initial B bank selection for reading B matrix data
                              for the matrix computations                     */
    uint64_t C_CRSTART:1;  /* Initial C bank selection for reading operands   */
    uint64_t C_CWSTART:1;  /* Initial C bank selection for writing computation
                              results                                         */
    uint64_t C_CLSTART:1;  /* Initial C bank selection for writing operands from
                              HWALD*                                          */
    uint64_t C_RSVD7:3;    /* Reserved                                        */
    uint64_t C_CROFFSET:6; /* C row read offset                               */
    uint64_t C_RSVD8:2;    /* Reserved                                        */
    uint64_t C_CWOFFSET:6; /* C row write offset for computations             */
    uint64_t C_RSVD9:2;    /* Reserved                                        */
    uint64_t C_CLOFFSET:6; /* C row write offset for HWALD* instructions      */
    uint64_t C_RSVD10:2;   /* Reserved                                        */
    uint64_t C_CLSWPER:8;  /* C bank switch period for HWALD* instruction
                              writes                                          */
    uint64_t C_CLRSTPER:8; /* C write row offset reset period for HWALD*      */
    uint64_t C_OP1PER:32;  /* Operation 1 period                              */
    uint64_t C_OP0PER:32;  /* Operation 0 period                              */
    uint64_t C_BSWPER:32;  /* B bank switch period                            */
    uint64_t C_CRSWPER:32; /* C bank switch period for read instructions      */
    uint64_t C_CWSWPER:32; /* C bank switch period for computation writes     */
    uint64_t C_CRRSTPER:8; /* C read row offset reset period                  */
    uint64_t C_CWRSTPER:8; /* C write row offset reset period for
                              computations                                    */

    uint64_t X_ReLU:1;     /* Enable Rectified Linear Units non-linearity after
                              optional saturation                             */
    uint64_t X_RSVD1:7;    /* Reserved                                        */
    uint64_t X_SAT:1;      /* Enable saturation in the transfer buffer element
                              type after optional rounding                    */
    uint64_t X_RSVD2:7;    /* Reserved                                        */
    uint64_t X_RE:1;       /* Enable routing via 1/2 LSB addition after
                              shifting                                        */
    uint64_t X_RSVD3:7;    /* Reserved                                        */
    uint64_t X_SHIFT:7;    /* Right shift amount, signed or unsigned depending
                              on CTYPE field.                                 */
    uint64_t X_RSVD4:1;    /* Reserved                                        */
    uint64_t X_XTYPE:4;    /* Transfer buffer element type. Not all combinations
                              of CTYPE and XTYPE are supported                */
    uint64_t X_RSVD5:4;    /* Reserved                                        */
    uint64_t X_CTYPE:3;    /* C matrix element type.  This must be consistent
                              with the B FSM setting                          */
    uint64_t X_RSVD6:5;    /* Reserved                                        */
    uint64_t X_CSWPER:32;  /* C read bank switch period                       */
    uint64_t X_CRRSTPER:8; /* C read row offset reset period                  */
    uint64_t X_COFFSET:8;  /* C matrix row read address offset                */
    uint64_t X_CSTART:1;   /* Initial C bank selection                        */
    uint64_t X_RSVD7:7;    /* Reserved                                        */

    uint64_t RSVD:6;       /* Reserved                                        */
    uint64_t PARITYCTRL:2; /* Parity control                                  */
#else
    uint64_t B_BSWPER:32;  /* B banks switch period                           */

    uint64_t A_RSVD2:23;   /* Reserved                                        */
    uint64_t A_ALUTEN:1;   /* A vector element lookup table                   */
    uint64_t A_RSVD1:5;    /* Reserved                                        */
    uint64_t A_ATYPE:3;    /* A vector element type                           */

    uint64_t B_RSVD4:24;   /* Reserved                                        */
    uint64_t B_BOFFSET:8;  /* Global row or column offset                     */
    uint64_t B_RSVD3:7;    /* Reserved                                        */
    uint64_t B_BSTART:1;   /* Initial B bank selection for writing B matrix
                              data                                            */
    uint64_t B_RSVD2:7;    /* Reserved                                        */
    uint64_t B_ORDER:1;    /* Transpose control                               */
    uint64_t B_RSVD1:6;    /* Reserved                                        */
    uint64_t B_BTYPE:2;    /* B matrix element type                           */
    uint64_t B_BRSTPER:8;  /* B offset reset period                           */

    uint64_t C_RSVD8:2;    /* Reserved                                        */
    uint64_t C_CROFFSET:6; /* C row read offset                               */
    uint64_t C_RSVD7:3;    /* Reserved                                        */
    uint64_t C_CLSTART:1;  /* Initial C bank selection for writing operands from
                              HWALD*                                          */
    uint64_t C_CWSTART:1;  /* Initial C bank selection for writing computation
                              results                                         */
    uint64_t C_CRSTART:1;  /* Initial C bank selection for reading operands   */
    uint64_t C_BSTART:1;   /* Initial B bank selection for reading B matrix data
                              for the matrix computations                     */
    uint64_t C_OPSTART:1;  /* Initial C operand selection                     */
    uint64_t C_RSVD6:4;    /* Reserved                                        */
    uint64_t C_HWLDTYPE:4; /* C matrix element type from a HWALD* instruction */
    uint64_t C_RSVD5:5;    /* Reserved                                        */
    uint64_t C_HWLDDST:3;
    uint64_t C_RSVD4:6;    /* Reserved                                        */
    uint64_t C_OPERATION1:2;
    uint64_t C_RSVD3:6;    /* Reserved                                        */
    uint64_t C_OPERATION0:2;
    uint64_t C_RSVD2:5;    /* Reserved                                        */
    uint64_t C_BTYPE:3;
    uint64_t C_RSVD1:7;    /* Reserved                                        */
    uint64_t C_ATYPE:1;    /* unsigned or signed                              */
    uint64_t C_OP1PER:32;  /* Operation 1 period                              */
    uint64_t C_CLRSTPER:8; /* C write row offset reset period for HWALD*      */
    uint64_t C_CLSWPER:8;  /* C bank switch period for HWALD* instruction
                              writes                                          */
    uint64_t C_RSVD10:2;   /* Reserved                                        */
    uint64_t C_CLOFFSET:6; /* C row write offset for HWALD* instructions      */
    uint64_t C_RSVD9:2;    /* Reserved                                        */
    uint64_t C_CWOFFSET:6; /* C row write offset for computations             */
    uint64_t C_BSWPER:32;  /* B bank switch period                            */
    uint64_t C_OP0PER:32;  /* Operation 0 period                              */
    uint64_t C_CWSWPER:32; /* C bank switch period for computation writes     */
    uint64_t C_CRSWPER:32; /* C bank switch period for read instructions      */

    uint64_t X_RSVD6:5;    /* Reserved                                        */
    uint64_t X_CTYPE:3;    /* C matrix element type.  This must be consistent
                              with the B FSM setting                          */
    uint64_t X_RSVD5:4;    /* Reserved                                        */
    uint64_t X_XTYPE:4;    /* Transfer buffer element type. Not all combinations
                              of CTYPE and XTYPE are supported                */
    uint64_t X_RSVD4:1;    /* Reserved                                        */
    uint64_t X_SHIFT:7;    /* Right shift amount, signed or unsigned depending
                              on CTYPE field.                                 */
    uint64_t X_RSVD3:7;    /* Reserved                                        */
    uint64_t X_RE:1;       /* Enable routing via 1/2 LSB addition after
                              shifting                                        */
    uint64_t X_RSVD2:7;    /* Reserved                                        */
    uint64_t X_SAT:1;      /* Enable saturation in the transfer buffer element
                              type after optional rounding                    */
    uint64_t X_RSVD1:7;    /* Reserved                                        */
    uint64_t X_ReLU:1;     /* Enable Rectified Linear Units non-linearity after
                              optional saturation                             */

    uint64_t C_CWRSTPER:8; /* C write row offset reset period for computations*/
    uint64_t C_CRRSTPER:8; /* C read row offset reset period                  */

    uint64_t PARITYCTRL:2; /* Parity control                                  */
    uint64_t RSVD:6;       /* Reserved                                        */

    uint64_t X_RSVD7:7;    /* Reserved                                        */
    uint64_t X_CSTART:1;   /* Initial C bank selection                        */
    uint64_t X_COFFSET:8;  /* C matrix row read address offset                */
    uint64_t X_CRRSTPER:8; /* C read row offset reset period                  */
    uint64_t X_CSWPER:32;  /* C read bank switch period                       */
#endif

} __HWA_CONFIG_REG;


/*----------------------------------------------------------------------------*/
/* Enumerations for __HWA_CONFIG_REG                                          */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Use the following for PARITYCTRL in HWA_CONFIG setup                       */
/*----------------------------------------------------------------------------*/
typedef enum
{
    __MMA_NORMAL      = 0,
    __MMA_PNCM_CK     = 1,
    __MMA_PCM_NCK     = 2,
    __MMA_PNCM_NCK    = 3
} __MMA_PARITYCTRL;

/*----------------------------------------------------------------------------*/
/* Use the following for A_TYPE in HWA_CONFIG setup                           */
/*----------------------------------------------------------------------------*/
typedef enum
{
    __MMA_A_CONFIG_ATYPE_UINT8  = 0,
    __MMA_A_CONFIG_ATYPE_UINT16 = 1,
    /* reserved = 2, */
    __MMA_A_CONFIG_ATYPE_UINT32 = 3,
    __MMA_A_CONFIG_ATYPE_INT8   = 4,
    __MMA_A_CONFIG_ATYPE_INT16  = 5,
    /* reserved = 6, */
    __MMA_A_CONFIG_ATYPE_INT32  = 7
} __MMA_A_CONFIG_ATYPE;

/*----------------------------------------------------------------------------*/
/* Use the following for A_ALUTEN in HWA_CONFIG setup                         */
/*----------------------------------------------------------------------------*/
typedef enum
{
    __MMA_A_CONFIG_NOLUT = 0,
    __MMA_A_CONFIG_LUT   = 1
} __MMA_A_LUTEN;


/*----------------------------------------------------------------------------*/
/* Use the following for B_BTYPE in HWA_CONFIG setup                          */
/*----------------------------------------------------------------------------*/
typedef enum /* C_CONFIG and B_CONFIG have different field needing different  */
             /* enums with the same name: "BTYPE"                             */
{
    __MMA_B_CONFIG_SIZE8  = 0,
    __MMA_B_CONFIG_SIZE16 = 1,
    /* reserved = 2, */
    __MMA_B_CONFIG_SIZE32 = 3
} __MMA_B_BTYPE;

/*----------------------------------------------------------------------------*/
/* Use the following for B_ORDER in HWA_CONFIG setup                          */
/*----------------------------------------------------------------------------*/
typedef enum
{
    __MMA_B_CONFIG_ROW = 0,
    __MMA_B_CONFIG_COL = 1
} __MMA_B_CONFIG_ORDER_TRANSPOSE_CONTROL;


/*----------------------------------------------------------------------------*/
/* C CONFIG enumerations                                                      */
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/* Use the following for C_ATYPE in HWA_CONFIG setup                          */
/*----------------------------------------------------------------------------*/
typedef enum
{
    __MMA_C_CONFIG_ATYPE_UA = 0, /* Vector elements are unsigned              */
    __MMA_C_CONFIG_ATYPE_SA = 1  /* Vector elements are signed                */
} __MMA_C_CONFIG_ATYPE;

/*----------------------------------------------------------------------------*/
/* Use the following for C_BTYPE in HWA_CONFIG setup                          */
/*----------------------------------------------------------------------------*/
typedef enum /* C_CONFIG and B_CONFIG have different field needing different  */
             /* enums with the same name: "BTYPE"                             */
{
    __MMA_C_CONFIG_BTYPE_UINT8  = 0,
    __MMA_C_CONFIG_BTYPE_UINT16 = 1,
    /* reserved = 2, */
    __MMA_C_CONFIG_BTYPE_UINT32 = 3,
    __MMA_C_CONFIG_BTYPE_INT8   = 4,
    __MMA_C_CONFIG_BTYPE_INT16  = 5,
    /* reserved = 6, */
    __MMA_C_CONFIG_BTYPE_INT32  = 7
} __MMA_C_CONFIG_BTYPE;

/*----------------------------------------------------------------------------*/
/* Use the following for C_OPERATION0 and C_OPERATION1 in HWA_CONFIG setup    */
/*----------------------------------------------------------------------------*/
typedef enum
{
    __MMA_C_CONFIG_MUL       = 0,
    __MMA_C_CONFIG_MULNEGATE = 1,
    __MMA_C_CONFIG_MULMINUS  = 2,
    __MMA_C_CONFIG_MULPLUS   = 3
} __MMA_C_CONFIG_OPERATION;

typedef enum
{                                    /* Input data  | Shifted left?       */
                                     /* extended?                         */
    __MMA_C_CONFIG_HWLDDST_X4_0 = 0, /*  4 times      not shifted         */
    __MMA_C_CONFIG_HWLDDST_X4_1 = 1, /*  4 times      1x orig bit width   */
    __MMA_C_CONFIG_HWLDDST_X4_2 = 2, /*  4 times      2x orig bit width   */
    __MMA_C_CONFIG_HWLDDST_X4_3 = 3, /*  4 times      3x orig bit width   */
    __MMA_C_CONFIG_HWLDDST_X1   = 7  /*  No           not shifted         */
    /* reserved = 4-6 */
} __MMA_C_CONFIG_HWLDDST;

typedef enum
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
    __MMA_C_CONFIG_HWLDTYPE_INT32  = 11
    /* reserved = 12, */
    /* reserved = 13, */
    /* reserved = 14, */
    /* reserved = 15, */
} __MMA_C_CONFIG_HWLDTYPE;

typedef enum
{
    __MMA_C_CONFIG_OPSTART_OPERATION0 = 0,
    __MMA_C_CONFIG_OPSTART_OPERATION1 = 1
} __MMA_C_CONFIG_OPSTART;


/*----------------------------------------------------------------------------*/
/* X CONFIG enumerations                                                      */
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/* Use the following for X_XTYPE in HWA_CONFIG setup                          */
/*----------------------------------------------------------------------------*/
typedef enum
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
    __MMA_X_CONFIG_XTYPE_INT128  = 13
    /* reserved = 14, */
    /* reserved = 15, */
} __MMA_X_CONFIG_XTYPE;

/*----------------------------------------------------------------------------*/
/* Use the following for X_CTYPE in HWA_CONFIG setup                          */
/*----------------------------------------------------------------------------*/
enum __MMA_X_CONFIG_CTYPE
{
    __MMA_X_CONFIG_CTYPE_UINT32  = 0,
    __MMA_X_CONFIG_CTYPE_UINT64  = 1,
    /* reserved = 2, */
    __MMA_X_CONFIG_CTYPE_UINT128 = 3,
    __MMA_X_CONFIG_CTYPE_INT32   = 4,
    __MMA_X_CONFIG_CTYPE_INT64   = 5,
    /* reserved = 6, */
    __MMA_X_CONFIG_CTYPE_INT128  = 7
};


/*----------------------------------------------------------------------------*/
/* __HWA_OFFSET_REG                                                           */
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
#endif

} __HWA_OFFSET_REG;

/*----------------------------------------------------------------------------*/
/* It is recommended to use the __HWAOPEN intrinsic instead of the __hwaopen  */
/* intrinsic. Use the __HWA_CONFIG_REG and __HWA_OFFSET_REG structs that are  */
/* defined in this file to set up the necessary parameters for the MMA.       */
/* The programmer should pass an enum value from the __MMA_OPEN_FSM enum      */
/* typedef to the mma_open_fsm parameter (see the MMA specification for full  */
/* full details).                                                             */
/*----------------------------------------------------------------------------*/
void      __BIFM __hwaopen(__ulong8, __ulong8, __CST(0, 15) int);
void      __BIFM __HWAOPEN(__HWA_CONFIG_REG, __HWA_OFFSET_REG, __CST(0, 15) int);
void      __BIFM __HWACLOSE(__CST(0, 0) int);

void      __BIFM __HWALDA(__uchar64 src1);
void      __BIFM __HWALDB(__uchar64 src1);
void      __BIFM __HWALDC(__uchar64 src1);
void      __BIFM __HWALDAB(__uchar64 src1, __uchar64 src2);
void      __BIFM __HWALDBC(__uchar64 src1, __uchar64 src2);

void      __BIFM __HWAOP(__CST(0, 23) int);
void      __BIFM __HWAXFER(__CST(0, 15) int);
void      __BIFM __HWAFENCE_OPXFER();
void      __BIFM __HWAOPXFER(__CST(0, 23) int);

__uchar64 __BIFM __HWARCV(__CST(0,3) int); /* S-unit HWARCV (with constant) */

void      __BIFM __HWASWAP(__CST(0, 0) int); 

#define   __HWAADV()        /* Empty macro; API used only by Host Emulation */

#ifdef __cplusplus
}
#endif

#endif /* __C7X_MMA_DEPRECATED_H */
