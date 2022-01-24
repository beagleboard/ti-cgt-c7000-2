/*****************************************************************************/
/* vcop.h                                                                    */
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
/* Header file for VCOP kernels written in VCOP-C.                           */
/*                                                                           */
/* VCOP-C is an embedded language based on C++ that can be used to           */
/* express VCOP kernels.                                                     */
/*                                                                           */
/* VCOP-C kernels can be translated and run in three ways:                   */
/*   1. In emulation mode, using C++ classes defined in this file to         */
/*      execute the kernel on a host computer.                               */
/*   2. In native mode, by using the VCOP-C Kernel Compiler to translate     */
/*      the kernel to native VCOP assembly.                                  */
/*   3. In C7x translation mode, using the C7x VCOP-C Kernel translator      */
/*      to translate the kernel to C7x code.                                 */
/*                                                                           */
/* This file supports modes (1) and (3). For native compilation, use the     */
/* APR32 version of this file.                                               */
/*                                                                           */
/* Note that the classes defined for emulation mode implement a superset     */
/* of the language. That is, you can write programs that will compile and    */
/* run in emulation mode but that cannot be translated in native mode.       */
/* The kernel compiler is the ultimate authority on what constitutes a legal */
/* kernel.                                                                   */
/*****************************************************************************/
#ifndef __VCOP_H__
#define __VCOP_H__

#ifndef VCOP_SIMD_WIDTH
   #error "VCOP_SIMD_WIDTH has not been defined!"
#endif

#ifdef __cplusplus
#define __EXTERN_C extern "C"
#else /* ! __cplusplus */
#define __EXTERN_C 
#endif

/*----------------------------------------------------------------------------
* In host emulation mode, include the host implementation
*---------------------------------------------------------------------------*/
#if VCOP_HOST_EMULATION
#include <vcop_host_emulation.h>

/*----------------------------------------------------------------------------
* For C7000 translation mode, declare the API to be compatible with EVE
*---------------------------------------------------------------------------*/
#elif defined(__C7000__)

#include <c7x.h>
#include <stdint.h>
#include <vcop/vcopmem.h>

// use char instead of uint8_t, since that's how it's defined for EVE
typedef char*            __vptr_int8;
typedef unsigned char*   __vptr_uint8;
typedef int16_t*         __vptr_int16;
typedef uint16_t*        __vptr_uint16;
typedef int32_t*         __vptr_int32;
typedef uint32_t*        __vptr_uint32;

typedef int32_t*         __vptr_scratch32;
typedef uint32_t*        __vptr_uscratch32;

typedef char**           __vptr_int8_arr;
typedef unsigned char**  __vptr_uint8_arr;
typedef short**          __vptr_int16_arr;
typedef unsigned short** __vptr_uint16_arr;
typedef int**            __vptr_int32_arr;
typedef unsigned int**   __vptr_uint32_arr;

/* API for built-in kernel profiling */
typedef unsigned long __TSC_TYPE;
#define __TSC_FMT "%lu"

#define _tsc_start() (__get_GTSC(1))
#define _tsc_gettime() (__TSC)

__EXTERN_C
void __vcop_log_kernel_profile(const char* name, 
                               __TSC_TYPE init, __TSC_TYPE vloops);

#define WPREG_INIT() {}

/*----------------------------------------------------------------------------
* API for EVE buffer and dispatch management
*---------------------------------------------------------------------------*/
#define WBUF_VCOP        (1u)
#define WBUF_SYST        (0u)
#define IBUFHB_VCOP      (1u)
#define IBUFHB_SYST      (0u)
#define IBUFHA_VCOP      (1u)
#define IBUFHA_SYST      (0u)
#define IBUFLB_VCOP      (1u)
#define IBUFLB_SYST      (0u)
#define IBUFLA_VCOP      (1u)
#define IBUFLA_SYST      (0u)

#define FLAT_MEM_VIEW    0
#define ALIAS_128K_VIEW  0x11

#define BUF_PING         1
#define BUF_PONG         0

/* Mem Map Control          */
#define L2MEMMAP      __ECR407
/* Mem Switch Control       */
#define L2MSWCTL      __ECR408
/* Mem Map IBUFA Control    */
#define L2MEMMAPIBUFA __ECR409
/* Mem Map IBUFB Control    */
#define L2MEMMAPIBUFB __ECR410
/* Mem Map WBUF Control     */
#define L2MEMMAPWBUF  __ECR411
/* Mem Switch Error Status  */
#define L2MSWERRSTAT  __ECR412
/* Mem Switch Error Clear   */
#define L2MSWERRCLR   __ECR413
/* Mem Switch Error Address */
#define L2MSWERRADDR  __ECR414

#define _vcop_vloop_ready()
#define _vcop_vloop_done()

/*----------------------------------------------------------------------------
* Determine which buffers belong to System (DMA) and which belong to CPU ('VCOP'
* on EVE). A value of '1' in the buffer locations means the buffer is owned by
* the CPU, a value of '0' means the buffer is owned by the System.
*
* Supported settings are:
*  VCOP_BUF_SWITCH_SET(0, 0, 0, 1, 1)
*  VCOP_BUF_SWITCH_SET(1, 0, 0, 1, 1)
*  VCOP_BUF_SWITCH_SET(0, 1, 1, 0, 0)
*  VCOP_BUF_SWITCH_SET(1, 1, 1, 0, 0)
* 
*---------------------------------------------------------------------------*/
#define VCOP_BUF_SWITCH_SET(w, hb, lb, ha, la) (L2MSWCTL =                \
                                      ((unsigned int)(w  & 0xFu) << 16) | \
                                      ((unsigned int)(hb & 0xFu) << 12) | \
                                      ((unsigned int)(lb & 0xFu) << 8)  | \
                                      ((unsigned int)(ha & 0xFu) << 4)  | \
                                                    ((la & 0xFu)))

/*----------------------------------------------------------------------------
* Return the value contained in the MSW_CTL ECR
*---------------------------------------------------------------------------*/
#define VCOP_READ_BUF_SWITCH() (L2MSWCTL)

/*----------------------------------------------------------------------------
* Set the memory view to be either FLAT_MEM_VIEW or ALIAS_128K_VIEW
*---------------------------------------------------------------------------*/
#define VCOP_SET_MEM_VIEW(view) (L2MEMMAP = view)

/*----------------------------------------------------------------------------
* These macros switch between the 'ping' buffer setup and 'pong' buffer setup
*---------------------------------------------------------------------------*/
static inline void VCOP_BUF_SWITCH_AVCOP()
{
    VCOP_BUF_SWITCH_SET(WBUF_VCOP,
                        IBUFHB_SYST, IBUFLB_SYST,
                        IBUFHA_VCOP, IBUFLA_VCOP);
}

static inline void VCOP_BUF_SWITCH_BVCOP()
{
    VCOP_BUF_SWITCH_SET(WBUF_VCOP,
                        IBUFHB_VCOP, IBUFLB_VCOP,
                        IBUFHA_SYST, IBUFLA_SYST);
}

/*----------------------------------------------------------------------------
* Toggle all the values around effecting a context switch between the CPU and
* System buffers.  This is useful when communicating when DMA and ping-pong
* buffering is needed.  This also eliminates the need to remember which buffer
* belonged to whom prior to switching.
*---------------------------------------------------------------------------*/
static inline unsigned int VCOP_BUF_SWITCH_TOGGLE (unsigned int flag)
{
    if (flag == BUF_PING) VCOP_BUF_SWITCH_AVCOP();
    else                  VCOP_BUF_SWITCH_BVCOP();
    return (flag ^ 0x1u);
}

static inline void __vcop_buffers_system()
{
    VCOP_BUF_SWITCH_SET(WBUF_SYST,
                        IBUFHB_SYST, IBUFLB_SYST,
                        IBUFHA_SYST, IBUFLA_SYST);
}

static inline void __vcop_buffers_vcop()
{
    VCOP_BUF_SWITCH_SET(WBUF_VCOP,
                        IBUFHB_VCOP, IBUFLB_VCOP,
                        IBUFHA_VCOP, IBUFLA_VCOP);
}

#define NO_CIRC  0
#define CIRC_1K  1
#define CIRC_2K  2
#define CIRC_4K  3
#define CIRC_8K  4
#define CIRC_16K 5
#define CIRC_32K 6

/*----------------------------------------------------------------------------
* Memory locations for the start of VCOP buffers
*---------------------------------------------------------------------------*/
#define ibufla ((void*) 0x80000000)
#define ibufha ((void*) 0x80008000)
#define ibuflb ((void*) 0x80010000)
#define ibufhb ((void*) 0x80018000)
#define wbuf   ((void*) 0x80020000)

/*----------------------------------------------------------------------------
* Unsupported / unknown target
*---------------------------------------------------------------------------*/
#else
#error "Unsupported target (use cl7x or #define VCOP_HOST_EMULATION)" 
#endif 

#endif /*__VCOP_H__ */
