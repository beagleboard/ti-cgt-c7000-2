/*****************************************************************************/
/* C7X_CR.H                                                                  */
/*                                                                           */
/* Copyright (c) 2021 Texas Instruments Incorporated                         */
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

#ifndef __C7X_CR_H
#define __C7X_CR_H

/*****************************************************************************/
/* The following is a list of CPU control registers available on C7000.      */
/* NOTE: Some reset values may not be exact depending on external factors    */
/*       such as silicon version and configuration.                          */
/*                                                                           */
/* The CPU control register may be read and written through normal           */
/* assignments where permissions allow. To read or write a specific index    */
/* of a CPU control register, use the following APIs:                        */
/*                                                                           */
/*   unsigned long __get_indexed(__CR_NAME, unsigned int index);             */
/*   void __set_indexed(__CR_NAME, unsigned int index, unsigned long val);   */
/*                                                                           */
/*****************************************************************************/

/******************************************************************************/
/* CR: CPUID                                                                  */
/* DESCRIPTION: CPU ID register                                               */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x60C00000                                            */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __CPUID;

/******************************************************************************/
/* CR: PMR                                                                    */
/* DESCRIPTION: Power Management register, not functional                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __PMR;

/******************************************************************************/
/* CR: DNUM                                                                   */
/* DESCRIPTION: DSP core number register                                      */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __DNUM;

/******************************************************************************/
/* CR: TSC                                                                    */
/* DESCRIPTION: Time-stamp counter register                                   */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __TSC;

/******************************************************************************/
/* CR: TSR                                                                    */
/* DESCRIPTION: Task state register                                           */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x100000000101FF05                                    */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __TSR;

/******************************************************************************/
/* CR: RP                                                                     */
/* DESCRIPTION: Return pointer register                                       */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __RP;

/******************************************************************************/
/* CR: BPCR                                                                   */
/* DESCRIPTION: Branch Predictor Control Register                             */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __BPCR;

/******************************************************************************/
/* CR: FPCR                                                                   */
/* DESCRIPTION: Floating-point  control register                              */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x10                                                  */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __FPCR;

/******************************************************************************/
/* CR: FSR                                                                    */
/* DESCRIPTION: Flag status register                                          */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __FSR;

/******************************************************************************/
/* CR: ECLMR                                                                  */
/* DESCRIPTION: Event Claim Register                                          */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0xFFFFFFFFFFFFFFFF                                    */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __ECLMR;

/******************************************************************************/
/* CR: EASGR                                                                  */
/* DESCRIPTION: Event Assign Register                                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __EASGR;

/******************************************************************************/
/* CR: EPRI                                                                   */
/* DESCRIPTION: Event Priority Register Event priority Register               */
/* INDEX RANGE: [0,63]                                                        */
/* GENERAL RESET VALUE: 0xE0                                                  */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __EPRI;

/******************************************************************************/
/* CR: EER                                                                    */
/* DESCRIPTION: Event Enable Register                                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __EER;

/******************************************************************************/
/* CR: EESET                                                                  */
/* DESCRIPTION: Event Enable Set  Register                                    */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      WO                                                  */
/*     Non-Secure Debug:  WO                                                  */
/*     Secure Supervisor: WO                                                  */
/*     Supervisor:        WO                                                  */
/*     Guest Supervisor:  WO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __EESET;

/******************************************************************************/
/* CR: EECLR                                                                  */
/* DESCRIPTION: Event Enable Clear Register                                   */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      WO                                                  */
/*     Non-Secure Debug:  WO                                                  */
/*     Secure Supervisor: WO                                                  */
/*     Supervisor:        WO                                                  */
/*     Guest Supervisor:  WO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __EECLR;

/******************************************************************************/
/* CR: DEPR                                                                   */
/* DESCRIPTION: Debug Event Priority Register                                 */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __DEPR;

/******************************************************************************/
/* CR: EFR                                                                    */
/* DESCRIPTION: Event Flag Register                                           */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __EFR;

/******************************************************************************/
/* CR: EFSET                                                                  */
/* DESCRIPTION: Event Flag Set  Register                                      */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      WO                                                  */
/*     Non-Secure Debug:  WO                                                  */
/*     Secure Supervisor: WO                                                  */
/*     Supervisor:        WO                                                  */
/*     Guest Supervisor:  WO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __EFSET;

/******************************************************************************/
/* CR: EFCLR                                                                  */
/* DESCRIPTION: Event Flag Clear Register                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      WO                                                  */
/*     Non-Secure Debug:  WO                                                  */
/*     Secure Supervisor: WO                                                  */
/*     Supervisor:        WO                                                  */
/*     Guest Supervisor:  WO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __EFCLR;

/******************************************************************************/
/* CR: IESET                                                                  */
/* DESCRIPTION: Internal Exception Event Set Register                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __IESET;

/******************************************************************************/
/* CR: ESTP_SS                                                                */
/* DESCRIPTION: Event Service Table Pointer Register, Secure Supervisor       */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __ESTP_SS;

/******************************************************************************/
/* CR: ESTP_S                                                                 */
/* DESCRIPTION: Event Service Table Pointer Register, Supervisor              */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __ESTP_S;

/******************************************************************************/
/* CR: ESTP_GS                                                                */
/* DESCRIPTION: Event Service Table Pointer Register, Guest Supervisor        */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __ESTP_GS;

/******************************************************************************/
/* CR: EDR                                                                    */
/* DESCRIPTION: Event Dropped Register                                        */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __EDR;

/******************************************************************************/
/* CR: ECSP_SS                                                                */
/* DESCRIPTION: Event Context Save Pointer, Secure Supervisor                 */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __ECSP_SS;

/******************************************************************************/
/* CR: ECSP_S                                                                 */
/* DESCRIPTION: Event Context Save Pointer, Supervisor                        */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __ECSP_S;

/******************************************************************************/
/* CR: ECSP_GS                                                                */
/* DESCRIPTION: Event Context Save Pointer, Guest Supervisor                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __ECSP_GS;

/******************************************************************************/
/* CR: TCSP                                                                   */
/* DESCRIPTION: Task Context Save Pointer                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __TCSP;

/******************************************************************************/
/* CR: RXMR_SS                                                                */
/* DESCRIPTION: Returning Execution Mode Register, Secure Supervisor          */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __RXMR_SS;

/******************************************************************************/
/* CR: RXMR_S                                                                 */
/* DESCRIPTION: Returning Execution Mode Register, Supervisor                 */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __RXMR_S;

/******************************************************************************/
/* CR: AHPEE                                                                  */
/* DESCRIPTION: Highest Priority Enabled Event, Currently in service          */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __AHPEE;

/******************************************************************************/
/* CR: PHPEE                                                                  */
/* DESCRIPTION: Pending HPEE                                                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __PHPEE;

/******************************************************************************/
/* CR: IPE                                                                    */
/* DESCRIPTION: Inter-processor Events Register                               */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      WO                                                  */
/*     Non-Secure Debug:  WO                                                  */
/*     Secure Supervisor: WO                                                  */
/*     Supervisor:        WO                                                  */
/*     Guest Supervisor:  WO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __IPE;

/******************************************************************************/
/* CR: IERR                                                                   */
/* DESCRIPTION: Internal exception report register                            */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __IERR;

/******************************************************************************/
/* CR: IEAR                                                                   */
/* DESCRIPTION: Internal Exception Address Register                           */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __IEAR;

/******************************************************************************/
/* CR: IESR                                                                   */
/* DESCRIPTION: Internal exception Status Register                            */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __IESR;

/******************************************************************************/
/* CR: IEDR                                                                   */
/* DESCRIPTION: Internal Exception Data Register                              */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __IEDR;

/******************************************************************************/
/* CR: TCR                                                                    */
/* DESCRIPTION: Test Count register                                           */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __TCR;

/******************************************************************************/
/* CR: TCCR                                                                   */
/* DESCRIPTION: Test Count Config register                                    */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __TCCR;

/******************************************************************************/
/* CR: GMER                                                                   */
/* DESCRIPTION: Guest Mode Enable Register                                    */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __GMER;

/******************************************************************************/
/* CR: UMER                                                                   */
/* DESCRIPTION: User Mask Enable Register                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __UMER;

/******************************************************************************/
/* CR: SPBR                                                                   */
/* DESCRIPTION: Stack pointer boundary Register                               */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __SPBR;

/******************************************************************************/
/* CR: LTBR0                                                                  */
/* DESCRIPTION: Lookup Table Base Address  register 0                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __LTBR0;

/******************************************************************************/
/* CR: LTBR1                                                                  */
/* DESCRIPTION: Lookup Table Base Address  register 1                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __LTBR1;

/******************************************************************************/
/* CR: LTBR2                                                                  */
/* DESCRIPTION: Lookup Table Base Address  register 2                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __LTBR2;

/******************************************************************************/
/* CR: LTBR3                                                                  */
/* DESCRIPTION: Lookup Table Base Address register 3                          */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __LTBR3;

/******************************************************************************/
/* CR: LTCR0                                                                  */
/* DESCRIPTION: Lookup Table configuration register 0                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __LTCR0;

/******************************************************************************/
/* CR: LTCR1                                                                  */
/* DESCRIPTION: Lookup Table configuration register 1                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __LTCR1;

/******************************************************************************/
/* CR: LTCR2                                                                  */
/* DESCRIPTION: Lookup Table configuration register 2                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __LTCR2;

/******************************************************************************/
/* CR: LTCR3                                                                  */
/* DESCRIPTION: Lookup Table configuration register 3                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __LTCR3;

/******************************************************************************/
/* CR: LTER                                                                   */
/* DESCRIPTION: Lookup Table Enable register                                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __LTER;

/******************************************************************************/
/* CR: DBGCTXT                                                                */
/* DESCRIPTION: Debug Context (Overlay) Register                              */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __DBGCTXT;

/******************************************************************************/
/* CR: GPLY                                                                   */
/* DESCRIPTION: Galois Polynomial Register                                    */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __GPLY;

/******************************************************************************/
/* CR: GFPGFR                                                                 */
/* DESCRIPTION: Galois Field Polynomial Generator Function Register           */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x700001D                                             */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RW                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RW                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __GFPGFR;

/******************************************************************************/
/* CR: GTSC                                                                   */
/* DESCRIPTION: Global Time Stamp Counter                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __GTSC;

/******************************************************************************/
/* CR: STSC                                                                   */
/* DESCRIPTION: Shadow Time Stamp Counter                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __STSC;

/******************************************************************************/
/* CR: UFCMR                                                                  */
/* DESCRIPTION: User Flag Clear Mask Register                                 */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
extern volatile __cregister unsigned long __UFCMR;

#endif /* __C7X_CR_H */
