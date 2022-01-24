/*****************************************************************************/
/* C7X_ECR.H                                                                 */
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
/*****************************************************************************/

#ifndef __C7X_H_INCLUDE__
#error "This file can only be included by parent header c7x.h"
#endif

#ifndef __C7X_ECR_H
#define __C7X_ECR_H

/*****************************************************************************/
/* The following is a list of extended control register available on C7000.  */
/* NOTE: Some reset values may not be exact depending on external factors    */
/*       such as silicon version and configuration.                          */
/*                                                                           */
/* The extended control registers may be read and written through normal     */
/* assignments where permissions allow. To read or write a specific index    */
/* of an extended control register, use the following APIs:                  */
/*                                                                           */
/*   unsigned long __get_indexed(__ECR_NAME, unsigned int index);            */
/*   void __set_indexed(__ECR_NAME, unsigned int index, unsigned long val);  */
/*                                                                           */
/*****************************************************************************/

extern volatile __cregister unsigned long __ECR0;

/******************************************************************************/
/* ECR: DBG_CAP                                                               */
/* DESCRIPTION: DEVICE CAPABILITY Register                                    */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0xDEC00440                                            */
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
#define __ECR_DBG_CAP __ECR0

extern volatile __cregister unsigned long __ECR1;

/******************************************************************************/
/* ECR: DBG_PID                                                               */
/* DESCRIPTION: DEVICE PID Register                                           */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x62020400                                            */
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
#define __ECR_DBG_PID __ECR1

extern volatile __cregister unsigned long __ECR2;
extern volatile __cregister unsigned long __ECR3;
extern volatile __cregister unsigned long __ECR4;

/******************************************************************************/
/* ECR: DBG_CNTL                                                              */
/* DESCRIPTION: Debug control Register                                        */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x200                                                 */
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
#define __ECR_DBG_CNTL __ECR4

extern volatile __cregister unsigned long __ECR5;

/******************************************************************************/
/* ECR: DBG_STAT                                                              */
/* DESCRIPTION: Debug Status Register                                         */
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
#define __ECR_DBG_STAT __ECR5

extern volatile __cregister unsigned long __ECR6;

/******************************************************************************/
/* ECR: DBG_OWN                                                               */
/* DESCRIPTION: Ownership Control and Status Register                         */
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
#define __ECR_DBG_OWN __ECR6

extern volatile __cregister unsigned long __ECR7;
extern volatile __cregister unsigned long __ECR8;

/******************************************************************************/
/* ECR: DBG_INDRCT_CAP0                                                       */
/* DESCRIPTION: Indirect Access Port Capabilities Register for pages 0-3      */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x121212                                              */
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
#define __ECR_DBG_INDRCT_CAP0 __ECR8

extern volatile __cregister unsigned long __ECR9;

/******************************************************************************/
/* ECR: DBG_INDRCT_CAP1                                                       */
/* DESCRIPTION: Indirect Access Port Capabilities Register for pages 4-7      */
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
#define __ECR_DBG_INDRCT_CAP1 __ECR9

extern volatile __cregister unsigned long __ECR10;
extern volatile __cregister unsigned long __ECR11;
extern volatile __cregister unsigned long __ECR12;

/******************************************************************************/
/* ECR: DBG_INDRCT_CNTL                                                       */
/* DESCRIPTION: Indirect Memory Control and Status register                   */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x40080000                                            */
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
#define __ECR_DBG_INDRCT_CNTL __ECR12

extern volatile __cregister unsigned long __ECR13;

/******************************************************************************/
/* ECR: DBG_INDRCT_CTXT0                                                      */
/* DESCRIPTION: Indirect Memory Context ID Register 0                         */
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
#define __ECR_DBG_INDRCT_CTXT0 __ECR13

extern volatile __cregister unsigned long __ECR14;

/******************************************************************************/
/* ECR: DBG_INDRCT_CTXT1                                                      */
/* DESCRIPTION: Indirect Memory Context ID Register 1                         */
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
#define __ECR_DBG_INDRCT_CTXT1 __ECR14

extern volatile __cregister unsigned long __ECR15;

/******************************************************************************/
/* ECR: DBG_INDRCT_CTXT2                                                      */
/* DESCRIPTION: Indirect Memory Context ID Register 2                         */
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
#define __ECR_DBG_INDRCT_CTXT2 __ECR15

extern volatile __cregister unsigned long __ECR16;

/******************************************************************************/
/* ECR: DBG_INDRCT_ADDR0                                                      */
/* DESCRIPTION: Indirect Memory Address Register 0                            */
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
#define __ECR_DBG_INDRCT_ADDR0 __ECR16

extern volatile __cregister unsigned long __ECR17;

/******************************************************************************/
/* ECR: DBG_INDRCT_ADDR1                                                      */
/* DESCRIPTION: Indirect Memory Address Register 1                            */
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
#define __ECR_DBG_INDRCT_ADDR1 __ECR17

extern volatile __cregister unsigned long __ECR18;

/******************************************************************************/
/* ECR: DBG_INDRCT_DATA0                                                      */
/* DESCRIPTION: Indirect Memory Data Register 0                               */
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
#define __ECR_DBG_INDRCT_DATA0 __ECR18

extern volatile __cregister unsigned long __ECR19;

/******************************************************************************/
/* ECR: DBG_INDRCT_DATA1                                                      */
/* DESCRIPTION: Indirect Memory Data Register 1                               */
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
#define __ECR_DBG_INDRCT_DATA1 __ECR19

extern volatile __cregister unsigned long __ECR20;
extern volatile __cregister unsigned long __ECR21;
extern volatile __cregister unsigned long __ECR22;
extern volatile __cregister unsigned long __ECR23;
extern volatile __cregister unsigned long __ECR24;
extern volatile __cregister unsigned long __ECR25;
extern volatile __cregister unsigned long __ECR26;
extern volatile __cregister unsigned long __ECR27;
extern volatile __cregister unsigned long __ECR28;
extern volatile __cregister unsigned long __ECR29;
extern volatile __cregister unsigned long __ECR30;
extern volatile __cregister unsigned long __ECR31;
extern volatile __cregister unsigned long __ECR32;
extern volatile __cregister unsigned long __ECR33;
extern volatile __cregister unsigned long __ECR34;
extern volatile __cregister unsigned long __ECR35;
extern volatile __cregister unsigned long __ECR36;
extern volatile __cregister unsigned long __ECR37;
extern volatile __cregister unsigned long __ECR38;
extern volatile __cregister unsigned long __ECR39;
extern volatile __cregister unsigned long __ECR40;
extern volatile __cregister unsigned long __ECR41;
extern volatile __cregister unsigned long __ECR42;
extern volatile __cregister unsigned long __ECR43;
extern volatile __cregister unsigned long __ECR44;
extern volatile __cregister unsigned long __ECR45;
extern volatile __cregister unsigned long __ECR46;
extern volatile __cregister unsigned long __ECR47;
extern volatile __cregister unsigned long __ECR48;
extern volatile __cregister unsigned long __ECR49;
extern volatile __cregister unsigned long __ECR50;
extern volatile __cregister unsigned long __ECR51;
extern volatile __cregister unsigned long __ECR52;
extern volatile __cregister unsigned long __ECR53;
extern volatile __cregister unsigned long __ECR54;
extern volatile __cregister unsigned long __ECR55;
extern volatile __cregister unsigned long __ECR56;
extern volatile __cregister unsigned long __ECR57;
extern volatile __cregister unsigned long __ECR58;
extern volatile __cregister unsigned long __ECR59;
extern volatile __cregister unsigned long __ECR60;
extern volatile __cregister unsigned long __ECR61;
extern volatile __cregister unsigned long __ECR62;
extern volatile __cregister unsigned long __ECR63;
extern volatile __cregister unsigned long __ECR64;

/******************************************************************************/
/* ECR: DBG_HWBP_0_CNTL                                                       */
/* DESCRIPTION: HWBP_0 Control and Status Register                            */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x800                                                 */
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
#define __ECR_DBG_HWBP_0_CNTL __ECR64

extern volatile __cregister unsigned long __ECR65;
extern volatile __cregister unsigned long __ECR66;

/******************************************************************************/
/* ECR: DBG_HWBP_0_CTXT0                                                      */
/* DESCRIPTION: HWBP_0 Context ID register 0                                  */
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
#define __ECR_DBG_HWBP_0_CTXT0 __ECR66

extern volatile __cregister unsigned long __ECR67;

/******************************************************************************/
/* ECR: DBG_HWBP_0_CTXT1                                                      */
/* DESCRIPTION: HWBP_0 Context ID register 1                                  */
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
#define __ECR_DBG_HWBP_0_CTXT1 __ECR67

extern volatile __cregister unsigned long __ECR68;

/******************************************************************************/
/* ECR: DBG_HWBP_0_CTXT2                                                      */
/* DESCRIPTION: HWBP_0 Context ID register 2                                  */
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
#define __ECR_DBG_HWBP_0_CTXT2 __ECR68

extern volatile __cregister unsigned long __ECR69;
extern volatile __cregister unsigned long __ECR70;

/******************************************************************************/
/* ECR: DBG_HWBP_0_ADDR0                                                      */
/* DESCRIPTION: HWBP_0 Address Register 0                                     */
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
#define __ECR_DBG_HWBP_0_ADDR0 __ECR70

extern volatile __cregister unsigned long __ECR71;

/******************************************************************************/
/* ECR: DBG_HWBP_0_ADDR1                                                      */
/* DESCRIPTION: HWBP_0 Address Register 1                                     */
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
#define __ECR_DBG_HWBP_0_ADDR1 __ECR71

extern volatile __cregister unsigned long __ECR72;

/******************************************************************************/
/* ECR: DBG_HWBP_0_AMASK0                                                     */
/* DESCRIPTION: HWBP_0 Address Mask Register 0                                */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0xFFFFFFFC                                            */
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
#define __ECR_DBG_HWBP_0_AMASK0 __ECR72

extern volatile __cregister unsigned long __ECR73;

/******************************************************************************/
/* ECR: DBG_HWBP_0_AMASK1                                                     */
/* DESCRIPTION: HWBP_0 Address Mask Register 1                                */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0xFFFFFFFF                                            */
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
#define __ECR_DBG_HWBP_0_AMASK1 __ECR73

extern volatile __cregister unsigned long __ECR74;
extern volatile __cregister unsigned long __ECR75;
extern volatile __cregister unsigned long __ECR76;
extern volatile __cregister unsigned long __ECR77;
extern volatile __cregister unsigned long __ECR78;
extern volatile __cregister unsigned long __ECR79;
extern volatile __cregister unsigned long __ECR80;
extern volatile __cregister unsigned long __ECR81;
extern volatile __cregister unsigned long __ECR82;
extern volatile __cregister unsigned long __ECR83;
extern volatile __cregister unsigned long __ECR84;
extern volatile __cregister unsigned long __ECR85;
extern volatile __cregister unsigned long __ECR86;
extern volatile __cregister unsigned long __ECR87;
extern volatile __cregister unsigned long __ECR88;
extern volatile __cregister unsigned long __ECR89;
extern volatile __cregister unsigned long __ECR90;
extern volatile __cregister unsigned long __ECR91;
extern volatile __cregister unsigned long __ECR92;
extern volatile __cregister unsigned long __ECR93;
extern volatile __cregister unsigned long __ECR94;
extern volatile __cregister unsigned long __ECR95;
extern volatile __cregister unsigned long __ECR96;

/******************************************************************************/
/* ECR: DBG_HWBP_1_CNTL                                                       */
/* DESCRIPTION: HWBP_1 Control and Status Register                            */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x800                                                 */
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
#define __ECR_DBG_HWBP_1_CNTL __ECR96

extern volatile __cregister unsigned long __ECR97;
extern volatile __cregister unsigned long __ECR98;

/******************************************************************************/
/* ECR: DBG_HWBP_1_CTXT0                                                      */
/* DESCRIPTION: HWBP_1 Context ID register 0                                  */
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
#define __ECR_DBG_HWBP_1_CTXT0 __ECR98

extern volatile __cregister unsigned long __ECR99;

/******************************************************************************/
/* ECR: DBG_HWBP_1_CTXT1                                                      */
/* DESCRIPTION: HWBP_1 Context ID register 1                                  */
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
#define __ECR_DBG_HWBP_1_CTXT1 __ECR99

extern volatile __cregister unsigned long __ECR100;

/******************************************************************************/
/* ECR: DBG_HWBP_1_CTXT2                                                      */
/* DESCRIPTION: HWBP_1 Context ID register 2                                  */
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
#define __ECR_DBG_HWBP_1_CTXT2 __ECR100

extern volatile __cregister unsigned long __ECR101;
extern volatile __cregister unsigned long __ECR102;

/******************************************************************************/
/* ECR: DBG_HWBP_1_ADDR0                                                      */
/* DESCRIPTION: HWBP_1 Address Register 0                                     */
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
#define __ECR_DBG_HWBP_1_ADDR0 __ECR102

extern volatile __cregister unsigned long __ECR103;

/******************************************************************************/
/* ECR: DBG_HWBP_1_ADDR1                                                      */
/* DESCRIPTION: HWBP_1 Address Register 1                                     */
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
#define __ECR_DBG_HWBP_1_ADDR1 __ECR103

extern volatile __cregister unsigned long __ECR104;

/******************************************************************************/
/* ECR: DBG_HWBP_1_AMASK0                                                     */
/* DESCRIPTION: HWBP_1 Address Mask Register 0                                */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0xFFFFFFFC                                            */
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
#define __ECR_DBG_HWBP_1_AMASK0 __ECR104

extern volatile __cregister unsigned long __ECR105;

/******************************************************************************/
/* ECR: DBG_HWBP_1_AMASK1                                                     */
/* DESCRIPTION: HWBP_1 Address Mask Register 1                                */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0xFFFFFFFF                                            */
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
#define __ECR_DBG_HWBP_1_AMASK1 __ECR105

extern volatile __cregister unsigned long __ECR106;
extern volatile __cregister unsigned long __ECR107;
extern volatile __cregister unsigned long __ECR108;
extern volatile __cregister unsigned long __ECR109;
extern volatile __cregister unsigned long __ECR110;
extern volatile __cregister unsigned long __ECR111;
extern volatile __cregister unsigned long __ECR112;
extern volatile __cregister unsigned long __ECR113;
extern volatile __cregister unsigned long __ECR114;
extern volatile __cregister unsigned long __ECR115;
extern volatile __cregister unsigned long __ECR116;
extern volatile __cregister unsigned long __ECR117;
extern volatile __cregister unsigned long __ECR118;
extern volatile __cregister unsigned long __ECR119;
extern volatile __cregister unsigned long __ECR120;
extern volatile __cregister unsigned long __ECR121;
extern volatile __cregister unsigned long __ECR122;
extern volatile __cregister unsigned long __ECR123;
extern volatile __cregister unsigned long __ECR124;
extern volatile __cregister unsigned long __ECR125;
extern volatile __cregister unsigned long __ECR126;
extern volatile __cregister unsigned long __ECR127;
extern volatile __cregister unsigned long __ECR128;

/******************************************************************************/
/* ECR: DBG_HWBP_2_CNTL                                                       */
/* DESCRIPTION: HWBP_2 Control and Status Register                            */
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
#define __ECR_DBG_HWBP_2_CNTL __ECR128

extern volatile __cregister unsigned long __ECR129;
extern volatile __cregister unsigned long __ECR130;

/******************************************************************************/
/* ECR: DBG_HWBP_2_CTXT0                                                      */
/* DESCRIPTION: HWBP_2 Context ID register 0                                  */
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
#define __ECR_DBG_HWBP_2_CTXT0 __ECR130

extern volatile __cregister unsigned long __ECR131;

/******************************************************************************/
/* ECR: DBG_HWBP_2_CTXT1                                                      */
/* DESCRIPTION: HWBP_2 Context ID register 1                                  */
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
#define __ECR_DBG_HWBP_2_CTXT1 __ECR131

extern volatile __cregister unsigned long __ECR132;

/******************************************************************************/
/* ECR: DBG_HWBP_2_CTXT2                                                      */
/* DESCRIPTION: HWBP_2 Context ID register 2                                  */
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
#define __ECR_DBG_HWBP_2_CTXT2 __ECR132

extern volatile __cregister unsigned long __ECR133;
extern volatile __cregister unsigned long __ECR134;

/******************************************************************************/
/* ECR: DBG_HWBP_2_ADDR0                                                      */
/* DESCRIPTION: HWBP_2 Address Register 0                                     */
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
#define __ECR_DBG_HWBP_2_ADDR0 __ECR134

extern volatile __cregister unsigned long __ECR135;

/******************************************************************************/
/* ECR: DBG_HWBP_2_ADDR1                                                      */
/* DESCRIPTION: HWBP_2 Address Register 1                                     */
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
#define __ECR_DBG_HWBP_2_ADDR1 __ECR135

extern volatile __cregister unsigned long __ECR136;

/******************************************************************************/
/* ECR: DBG_HWBP_2_AMASK0                                                     */
/* DESCRIPTION: HWBP_2 Address Mask Register 0                                */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0xFFFFFFFC                                            */
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
#define __ECR_DBG_HWBP_2_AMASK0 __ECR136

extern volatile __cregister unsigned long __ECR137;

/******************************************************************************/
/* ECR: DBG_HWBP_2_AMASK1                                                     */
/* DESCRIPTION: HWBP_2 Address Mask Register 1                                */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0xFFFFFFFF                                            */
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
#define __ECR_DBG_HWBP_2_AMASK1 __ECR137

extern volatile __cregister unsigned long __ECR138;
extern volatile __cregister unsigned long __ECR139;
extern volatile __cregister unsigned long __ECR140;
extern volatile __cregister unsigned long __ECR141;
extern volatile __cregister unsigned long __ECR142;
extern volatile __cregister unsigned long __ECR143;
extern volatile __cregister unsigned long __ECR144;
extern volatile __cregister unsigned long __ECR145;
extern volatile __cregister unsigned long __ECR146;
extern volatile __cregister unsigned long __ECR147;
extern volatile __cregister unsigned long __ECR148;
extern volatile __cregister unsigned long __ECR149;
extern volatile __cregister unsigned long __ECR150;
extern volatile __cregister unsigned long __ECR151;
extern volatile __cregister unsigned long __ECR152;
extern volatile __cregister unsigned long __ECR153;
extern volatile __cregister unsigned long __ECR154;
extern volatile __cregister unsigned long __ECR155;
extern volatile __cregister unsigned long __ECR156;
extern volatile __cregister unsigned long __ECR157;
extern volatile __cregister unsigned long __ECR158;
extern volatile __cregister unsigned long __ECR159;
extern volatile __cregister unsigned long __ECR160;

/******************************************************************************/
/* ECR: DBG_HWBP_3_CNTL                                                       */
/* DESCRIPTION: HWBP_3 Control and Status Register                            */
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
#define __ECR_DBG_HWBP_3_CNTL __ECR160

extern volatile __cregister unsigned long __ECR161;
extern volatile __cregister unsigned long __ECR162;

/******************************************************************************/
/* ECR: DBG_HWBP_3_CTXT0                                                      */
/* DESCRIPTION: HWBP_3 Context ID register 0                                  */
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
#define __ECR_DBG_HWBP_3_CTXT0 __ECR162

extern volatile __cregister unsigned long __ECR163;

/******************************************************************************/
/* ECR: DBG_HWBP_3_CTXT1                                                      */
/* DESCRIPTION: HWBP_3 Context ID register 1                                  */
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
#define __ECR_DBG_HWBP_3_CTXT1 __ECR163

extern volatile __cregister unsigned long __ECR164;

/******************************************************************************/
/* ECR: DBG_HWBP_3_CTXT2                                                      */
/* DESCRIPTION: HWBP_3 Context ID register 2                                  */
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
#define __ECR_DBG_HWBP_3_CTXT2 __ECR164

extern volatile __cregister unsigned long __ECR165;
extern volatile __cregister unsigned long __ECR166;

/******************************************************************************/
/* ECR: DBG_HWBP_3_ADDR0                                                      */
/* DESCRIPTION: HWBP_3 Address Register 0                                     */
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
#define __ECR_DBG_HWBP_3_ADDR0 __ECR166

extern volatile __cregister unsigned long __ECR167;

/******************************************************************************/
/* ECR: DBG_HWBP_3_ADDR1                                                      */
/* DESCRIPTION: HWBP_3 Address Register 1                                     */
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
#define __ECR_DBG_HWBP_3_ADDR1 __ECR167

extern volatile __cregister unsigned long __ECR168;

/******************************************************************************/
/* ECR: DBG_HWBP_3_AMASK0                                                     */
/* DESCRIPTION: HWBP_3 Address Mask Register 0                                */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0xFFFFFFFC                                            */
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
#define __ECR_DBG_HWBP_3_AMASK0 __ECR168

extern volatile __cregister unsigned long __ECR169;

/******************************************************************************/
/* ECR: DBG_HWBP_3_AMASK1                                                     */
/* DESCRIPTION: HWBP_3 Address Mask Register 1                                */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0xFFFFFFFF                                            */
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
#define __ECR_DBG_HWBP_3_AMASK1 __ECR169

extern volatile __cregister unsigned long __ECR170;
extern volatile __cregister unsigned long __ECR171;
extern volatile __cregister unsigned long __ECR172;
extern volatile __cregister unsigned long __ECR173;
extern volatile __cregister unsigned long __ECR174;
extern volatile __cregister unsigned long __ECR175;
extern volatile __cregister unsigned long __ECR176;
extern volatile __cregister unsigned long __ECR177;
extern volatile __cregister unsigned long __ECR178;
extern volatile __cregister unsigned long __ECR179;
extern volatile __cregister unsigned long __ECR180;
extern volatile __cregister unsigned long __ECR181;
extern volatile __cregister unsigned long __ECR182;
extern volatile __cregister unsigned long __ECR183;
extern volatile __cregister unsigned long __ECR184;
extern volatile __cregister unsigned long __ECR185;
extern volatile __cregister unsigned long __ECR186;
extern volatile __cregister unsigned long __ECR187;
extern volatile __cregister unsigned long __ECR188;
extern volatile __cregister unsigned long __ECR189;
extern volatile __cregister unsigned long __ECR190;
extern volatile __cregister unsigned long __ECR191;
extern volatile __cregister unsigned long __ECR192;

/******************************************************************************/
/* ECR: DBG_HWWP_0_CNTL                                                       */
/* DESCRIPTION: HWWP_0 control and status register                            */
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
#define __ECR_DBG_HWWP_0_CNTL __ECR192

extern volatile __cregister unsigned long __ECR193;
extern volatile __cregister unsigned long __ECR194;

/******************************************************************************/
/* ECR: DBG_HWWP_0_CTXT0                                                      */
/* DESCRIPTION: HWWP_0 Context ID Register 0                                  */
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
#define __ECR_DBG_HWWP_0_CTXT0 __ECR194

extern volatile __cregister unsigned long __ECR195;

/******************************************************************************/
/* ECR: DBG_HWWP_0_CTXT1                                                      */
/* DESCRIPTION: HWWP_0 Context ID Register 1                                  */
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
#define __ECR_DBG_HWWP_0_CTXT1 __ECR195

extern volatile __cregister unsigned long __ECR196;

/******************************************************************************/
/* ECR: DBG_HWWP_0_CTXT2                                                      */
/* DESCRIPTION: HWWP_0 Context ID Register 2                                  */
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
#define __ECR_DBG_HWWP_0_CTXT2 __ECR196

extern volatile __cregister unsigned long __ECR197;
extern volatile __cregister unsigned long __ECR198;

/******************************************************************************/
/* ECR: DBG_HWWP_0_ADDR0                                                      */
/* DESCRIPTION: HWWP_0 Address Register 0                                     */
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
#define __ECR_DBG_HWWP_0_ADDR0 __ECR198

extern volatile __cregister unsigned long __ECR199;

/******************************************************************************/
/* ECR: DBG_HWWP_0_ADDR1                                                      */
/* DESCRIPTION: HWWP_0 Address Register 1                                     */
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
#define __ECR_DBG_HWWP_0_ADDR1 __ECR199

extern volatile __cregister unsigned long __ECR200;

/******************************************************************************/
/* ECR: DBG_HWWP_0_MASK0                                                      */
/* DESCRIPTION: HWWP_0 Address Qualification Mask Register 0                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0xFFFFFFFF                                            */
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
#define __ECR_DBG_HWWP_0_MASK0 __ECR200

extern volatile __cregister unsigned long __ECR201;

/******************************************************************************/
/* ECR: DBG_HWWP_0_MASK1                                                      */
/* DESCRIPTION: HWWP_0 Address Qualification Mask Register 1                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0xFFFFFFFF                                            */
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
#define __ECR_DBG_HWWP_0_MASK1 __ECR201

extern volatile __cregister unsigned long __ECR202;
extern volatile __cregister unsigned long __ECR203;
extern volatile __cregister unsigned long __ECR204;
extern volatile __cregister unsigned long __ECR205;
extern volatile __cregister unsigned long __ECR206;
extern volatile __cregister unsigned long __ECR207;
extern volatile __cregister unsigned long __ECR208;
extern volatile __cregister unsigned long __ECR209;
extern volatile __cregister unsigned long __ECR210;
extern volatile __cregister unsigned long __ECR211;
extern volatile __cregister unsigned long __ECR212;
extern volatile __cregister unsigned long __ECR213;
extern volatile __cregister unsigned long __ECR214;
extern volatile __cregister unsigned long __ECR215;
extern volatile __cregister unsigned long __ECR216;
extern volatile __cregister unsigned long __ECR217;
extern volatile __cregister unsigned long __ECR218;
extern volatile __cregister unsigned long __ECR219;
extern volatile __cregister unsigned long __ECR220;
extern volatile __cregister unsigned long __ECR221;
extern volatile __cregister unsigned long __ECR222;
extern volatile __cregister unsigned long __ECR223;
extern volatile __cregister unsigned long __ECR224;
extern volatile __cregister unsigned long __ECR225;
extern volatile __cregister unsigned long __ECR226;
extern volatile __cregister unsigned long __ECR227;
extern volatile __cregister unsigned long __ECR228;
extern volatile __cregister unsigned long __ECR229;
extern volatile __cregister unsigned long __ECR230;
extern volatile __cregister unsigned long __ECR231;
extern volatile __cregister unsigned long __ECR232;
extern volatile __cregister unsigned long __ECR233;
extern volatile __cregister unsigned long __ECR234;
extern volatile __cregister unsigned long __ECR235;
extern volatile __cregister unsigned long __ECR236;
extern volatile __cregister unsigned long __ECR237;
extern volatile __cregister unsigned long __ECR238;
extern volatile __cregister unsigned long __ECR239;
extern volatile __cregister unsigned long __ECR240;
extern volatile __cregister unsigned long __ECR241;
extern volatile __cregister unsigned long __ECR242;
extern volatile __cregister unsigned long __ECR243;
extern volatile __cregister unsigned long __ECR244;
extern volatile __cregister unsigned long __ECR245;
extern volatile __cregister unsigned long __ECR246;
extern volatile __cregister unsigned long __ECR247;
extern volatile __cregister unsigned long __ECR248;
extern volatile __cregister unsigned long __ECR249;
extern volatile __cregister unsigned long __ECR250;
extern volatile __cregister unsigned long __ECR251;
extern volatile __cregister unsigned long __ECR252;
extern volatile __cregister unsigned long __ECR253;
extern volatile __cregister unsigned long __ECR254;
extern volatile __cregister unsigned long __ECR255;
extern volatile __cregister unsigned long __ECR256;

/******************************************************************************/
/* ECR: L1DCFG                                                                */
/* DESCRIPTION: L1D Cache Configuration Register                              */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x7                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L1DCFG __ECR256

extern volatile __cregister unsigned long __ECR257;
extern volatile __cregister unsigned long __ECR258;

/******************************************************************************/
/* ECR: L1DWB                                                                 */
/* DESCRIPTION: L1D Global Writeback Register                                 */
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
#define __ECR_L1DWB __ECR258

extern volatile __cregister unsigned long __ECR259;

/******************************************************************************/
/* ECR: L1DWBINV                                                              */
/* DESCRIPTION: L1D Global Writeback Invalidate Register                      */
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
#define __ECR_L1DWBINV __ECR259

extern volatile __cregister unsigned long __ECR260;

/******************************************************************************/
/* ECR: L1DINV                                                                */
/* DESCRIPTION: L1D Invalidate Register                                       */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L1DINV __ECR260

extern volatile __cregister unsigned long __ECR261;
extern volatile __cregister unsigned long __ECR262;

/******************************************************************************/
/* ECR: L1DCTAG                                                               */
/* DESCRIPTION: L1D Cache tag View                                            */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */

extern volatile __cregister unsigned long __ECR263;
extern volatile __cregister unsigned long __ECR264;
extern volatile __cregister unsigned long __ECR265;
extern volatile __cregister unsigned long __ECR266;
extern volatile __cregister unsigned long __ECR267;
extern volatile __cregister unsigned long __ECR268;
extern volatile __cregister unsigned long __ECR269;
extern volatile __cregister unsigned long __ECR270;
extern volatile __cregister unsigned long __ECR271;
extern volatile __cregister unsigned long __ECR272;
extern volatile __cregister unsigned long __ECR273;

/******************************************************************************/
/* ECR: L1DADDREEA                                                            */
/* DESCRIPTION: L1D Addressing Error Event Address                            */
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
#define __ECR_L1DADDREEA __ECR273

extern volatile __cregister unsigned long __ECR274;

/******************************************************************************/
/* ECR: L1DADDREES                                                            */
/* DESCRIPTION: L1D Addressing Error Event Status                             */
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
#define __ECR_L1DADDREES __ECR274

extern volatile __cregister unsigned long __ECR275;

/******************************************************************************/
/* ECR: L1DADDREER                                                            */
/* DESCRIPTION: L1D Addressing Error Event Reset                              */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Supervisor: WO                                                  */
/*     Secure User:       WO                                                  */
/*     Supervisor:        WO                                                  */
/*     User:              WO                                                  */
/******************************************************************************/
#define __ECR_L1DADDREER __ECR275

extern volatile __cregister unsigned long __ECR276;

/******************************************************************************/
/* ECR: L1DCMDEEA                                                             */
/* DESCRIPTION: L1D CMD Error Event Address                                   */
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
#define __ECR_L1DCMDEEA __ECR276

extern volatile __cregister unsigned long __ECR277;

/******************************************************************************/
/* ECR: L1DCMDEES                                                             */
/* DESCRIPTION: L1D CMD Error Event Status                                    */
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
#define __ECR_L1DCMDEES __ECR277

extern volatile __cregister unsigned long __ECR278;

/******************************************************************************/
/* ECR: L1DCMDEER                                                             */
/* DESCRIPTION: L1D CMD Error Event Reset                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Supervisor: WO                                                  */
/*     Secure User:       WO                                                  */
/*     Supervisor:        WO                                                  */
/*     User:              WO                                                  */
/******************************************************************************/
#define __ECR_L1DCMDEER __ECR278

extern volatile __cregister unsigned long __ECR279;
extern volatile __cregister unsigned long __ECR280;
extern volatile __cregister unsigned long __ECR281;
extern volatile __cregister unsigned long __ECR282;
extern volatile __cregister unsigned long __ECR283;
extern volatile __cregister unsigned long __ECR284;
extern volatile __cregister unsigned long __ECR285;
extern volatile __cregister unsigned long __ECR286;
extern volatile __cregister unsigned long __ECR287;
extern volatile __cregister unsigned long __ECR288;
extern volatile __cregister unsigned long __ECR289;
extern volatile __cregister unsigned long __ECR290;
extern volatile __cregister unsigned long __ECR291;
extern volatile __cregister unsigned long __ECR292;
extern volatile __cregister unsigned long __ECR293;
extern volatile __cregister unsigned long __ECR294;
extern volatile __cregister unsigned long __ECR295;
extern volatile __cregister unsigned long __ECR296;
extern volatile __cregister unsigned long __ECR297;
extern volatile __cregister unsigned long __ECR298;
extern volatile __cregister unsigned long __ECR299;
extern volatile __cregister unsigned long __ECR300;
extern volatile __cregister unsigned long __ECR301;
extern volatile __cregister unsigned long __ECR302;
extern volatile __cregister unsigned long __ECR303;
extern volatile __cregister unsigned long __ECR304;
extern volatile __cregister unsigned long __ECR305;
extern volatile __cregister unsigned long __ECR306;
extern volatile __cregister unsigned long __ECR307;
extern volatile __cregister unsigned long __ECR308;
extern volatile __cregister unsigned long __ECR309;
extern volatile __cregister unsigned long __ECR310;
extern volatile __cregister unsigned long __ECR311;
extern volatile __cregister unsigned long __ECR312;
extern volatile __cregister unsigned long __ECR313;
extern volatile __cregister unsigned long __ECR314;
extern volatile __cregister unsigned long __ECR315;
extern volatile __cregister unsigned long __ECR316;
extern volatile __cregister unsigned long __ECR317;
extern volatile __cregister unsigned long __ECR318;
extern volatile __cregister unsigned long __ECR319;
extern volatile __cregister unsigned long __ECR320;
extern volatile __cregister unsigned long __ECR321;
extern volatile __cregister unsigned long __ECR322;
extern volatile __cregister unsigned long __ECR323;
extern volatile __cregister unsigned long __ECR324;

/******************************************************************************/
/* ECR: L1PCTAG                                                               */
/* DESCRIPTION: L1P Cache Tag View                                            */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */

extern volatile __cregister unsigned long __ECR325;
extern volatile __cregister unsigned long __ECR326;
extern volatile __cregister unsigned long __ECR327;
extern volatile __cregister unsigned long __ECR328;
extern volatile __cregister unsigned long __ECR329;
extern volatile __cregister unsigned long __ECR330;
extern volatile __cregister unsigned long __ECR331;
extern volatile __cregister unsigned long __ECR332;
extern volatile __cregister unsigned long __ECR333;
extern volatile __cregister unsigned long __ECR334;
extern volatile __cregister unsigned long __ECR335;
extern volatile __cregister unsigned long __ECR336;
extern volatile __cregister unsigned long __ECR337;
extern volatile __cregister unsigned long __ECR338;
extern volatile __cregister unsigned long __ECR339;
extern volatile __cregister unsigned long __ECR340;
extern volatile __cregister unsigned long __ECR341;
extern volatile __cregister unsigned long __ECR342;
extern volatile __cregister unsigned long __ECR343;
extern volatile __cregister unsigned long __ECR344;
extern volatile __cregister unsigned long __ECR345;
extern volatile __cregister unsigned long __ECR346;
extern volatile __cregister unsigned long __ECR347;
extern volatile __cregister unsigned long __ECR348;
extern volatile __cregister unsigned long __ECR349;
extern volatile __cregister unsigned long __ECR350;
extern volatile __cregister unsigned long __ECR351;
extern volatile __cregister unsigned long __ECR352;
extern volatile __cregister unsigned long __ECR353;
extern volatile __cregister unsigned long __ECR354;
extern volatile __cregister unsigned long __ECR355;
extern volatile __cregister unsigned long __ECR356;
extern volatile __cregister unsigned long __ECR357;
extern volatile __cregister unsigned long __ECR358;
extern volatile __cregister unsigned long __ECR359;
extern volatile __cregister unsigned long __ECR360;
extern volatile __cregister unsigned long __ECR361;
extern volatile __cregister unsigned long __ECR362;
extern volatile __cregister unsigned long __ECR363;
extern volatile __cregister unsigned long __ECR364;
extern volatile __cregister unsigned long __ECR365;
extern volatile __cregister unsigned long __ECR366;
extern volatile __cregister unsigned long __ECR367;
extern volatile __cregister unsigned long __ECR368;
extern volatile __cregister unsigned long __ECR369;
extern volatile __cregister unsigned long __ECR370;
extern volatile __cregister unsigned long __ECR371;
extern volatile __cregister unsigned long __ECR372;
extern volatile __cregister unsigned long __ECR373;
extern volatile __cregister unsigned long __ECR374;
extern volatile __cregister unsigned long __ECR375;
extern volatile __cregister unsigned long __ECR376;
extern volatile __cregister unsigned long __ECR377;
extern volatile __cregister unsigned long __ECR378;
extern volatile __cregister unsigned long __ECR379;
extern volatile __cregister unsigned long __ECR380;
extern volatile __cregister unsigned long __ECR381;
extern volatile __cregister unsigned long __ECR382;
extern volatile __cregister unsigned long __ECR383;
extern volatile __cregister unsigned long __ECR384;

/******************************************************************************/
/* ECR: L2CFG                                                                 */
/* DESCRIPTION: L2 Cache Configuration Register                               */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L2CFG __ECR384

extern volatile __cregister unsigned long __ECR385;

/******************************************************************************/
/* ECR: L2CC                                                                  */
/* DESCRIPTION: L2 Cache Control Register                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x10C60A00000000                                      */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RW                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RW                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L2CC __ECR385

extern volatile __cregister unsigned long __ECR386;

/******************************************************************************/
/* ECR: L2WB                                                                  */
/* DESCRIPTION: L2 Global Writeback Register                                  */
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
#define __ECR_L2WB __ECR386

extern volatile __cregister unsigned long __ECR387;

/******************************************************************************/
/* ECR: L2WBINV                                                               */
/* DESCRIPTION: L2 Global Writeback Invalidate Register                       */
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
#define __ECR_L2WBINV __ECR387

extern volatile __cregister unsigned long __ECR388;

/******************************************************************************/
/* ECR: L2INV                                                                 */
/* DESCRIPTION: L2 Invalidate Register                                        */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L2INV __ECR388

extern volatile __cregister unsigned long __ECR389;
extern volatile __cregister unsigned long __ECR390;

/******************************************************************************/
/* ECR: L2CTAG                                                                */
/* DESCRIPTION: L2 Cache tag View                                             */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */

extern volatile __cregister unsigned long __ECR391;

/******************************************************************************/
/* ECR: L2EDCFG                                                               */
/* DESCRIPTION: L2 EDC Configuration Control                                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x8000000004000001                                    */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L2EDCFG __ECR391

extern volatile __cregister unsigned long __ECR392;
extern volatile __cregister unsigned long __ECR393;
extern volatile __cregister unsigned long __ECR394;
extern volatile __cregister unsigned long __ECR395;
extern volatile __cregister unsigned long __ECR396;
extern volatile __cregister unsigned long __ECR397;
extern volatile __cregister unsigned long __ECR398;
extern volatile __cregister unsigned long __ECR399;
extern volatile __cregister unsigned long __ECR400;
extern volatile __cregister unsigned long __ECR401;

/******************************************************************************/
/* ECR: L2ADDREEA                                                             */
/* DESCRIPTION: L2 Addressing Error Event Address                             */
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
#define __ECR_L2ADDREEA __ECR401

extern volatile __cregister unsigned long __ECR402;

/******************************************************************************/
/* ECR: L2ADDREES                                                             */
/* DESCRIPTION: L2 Addressing Error Event Status                              */
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
#define __ECR_L2ADDREES __ECR402

extern volatile __cregister unsigned long __ECR403;

/******************************************************************************/
/* ECR: L2ADDREER                                                             */
/* DESCRIPTION: L2 Addressing Error Event Reset                               */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L2ADDREER __ECR403

extern volatile __cregister unsigned long __ECR404;

/******************************************************************************/
/* ECR: L2ALLOCEEA                                                            */
/* DESCRIPTION: L2 CMD Error Event Address                                    */
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
#define __ECR_L2ALLOCEEA __ECR404

extern volatile __cregister unsigned long __ECR405;

/******************************************************************************/
/* ECR: L2ALLOCEES                                                            */
/* DESCRIPTION: L2 CMD Error Event Status                                     */
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
#define __ECR_L2ALLOCEES __ECR405

extern volatile __cregister unsigned long __ECR406;

/******************************************************************************/
/* ECR: L2ALLOCEER                                                            */
/* DESCRIPTION: L2 CMD Error Event Reset                                      */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L2ALLOCEER __ECR406

extern volatile __cregister unsigned long __ECR407;

/******************************************************************************/
/* ECR: L2MEMMAP                                                              */
/* DESCRIPTION: L2 Memory Map Control                                         */
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
#define __ECR_L2MEMMAP __ECR407

extern volatile __cregister unsigned long __ECR408;

/******************************************************************************/
/* ECR: L2MSWCTL                                                              */
/* DESCRIPTION: L2 Memory Switch Control                                      */
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
#define __ECR_L2MSWCTL __ECR408

extern volatile __cregister unsigned long __ECR409;

/******************************************************************************/
/* ECR: L2MEMMAPIBUFA                                                         */
/* DESCRIPTION: L2 IBUFA Memory Base Control                                  */
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
#define __ECR_L2MEMMAPIBUFA __ECR409

extern volatile __cregister unsigned long __ECR410;

/******************************************************************************/
/* ECR: L2MEMMAPIBUFB                                                         */
/* DESCRIPTION: L2 IBUFB Memory Base Address                                  */
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
#define __ECR_L2MEMMAPIBUFB __ECR410

extern volatile __cregister unsigned long __ECR411;

/******************************************************************************/
/* ECR: L2MEMMAPWBUF                                                          */
/* DESCRIPTION: L2 WBUF Memory Base Address                                   */
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
#define __ECR_L2MEMMAPWBUF __ECR411

extern volatile __cregister unsigned long __ECR412;

/******************************************************************************/
/* ECR: L2MSWERRSTAT                                                          */
/* DESCRIPTION: L2 Memory Switch Error Status                                 */
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
#define __ECR_L2MSWERRSTAT __ECR412

extern volatile __cregister unsigned long __ECR413;

/******************************************************************************/
/* ECR: L2MSWERRCLR                                                           */
/* DESCRIPTION: L2 Memory Switch Error Clear                                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L2MSWERRCLR __ECR413

extern volatile __cregister unsigned long __ECR414;

/******************************************************************************/
/* ECR: L2MSWERRADDR                                                          */
/* DESCRIPTION: L2 Memory Switch Error Address                                */
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
#define __ECR_L2MSWERRADDR __ECR414

extern volatile __cregister unsigned long __ECR415;

/******************************************************************************/
/* ECR: L2EDTST                                                               */
/* DESCRIPTION: L2 EDC Test Control                                           */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Secure User:       RO                                                  */
/*     Supervisor:        RO                                                  */
/*     User:              RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/*     Guest User:        RO                                                  */
/******************************************************************************/
#define __ECR_L2EDTST __ECR415

extern volatile __cregister unsigned long __ECR416;
extern volatile __cregister unsigned long __ECR417;
extern volatile __cregister unsigned long __ECR418;
extern volatile __cregister unsigned long __ECR419;
extern volatile __cregister unsigned long __ECR420;
extern volatile __cregister unsigned long __ECR421;
extern volatile __cregister unsigned long __ECR422;
extern volatile __cregister unsigned long __ECR423;
extern volatile __cregister unsigned long __ECR424;
extern volatile __cregister unsigned long __ECR425;
extern volatile __cregister unsigned long __ECR426;
extern volatile __cregister unsigned long __ECR427;
extern volatile __cregister unsigned long __ECR428;
extern volatile __cregister unsigned long __ECR429;
extern volatile __cregister unsigned long __ECR430;
extern volatile __cregister unsigned long __ECR431;
extern volatile __cregister unsigned long __ECR432;
extern volatile __cregister unsigned long __ECR433;
extern volatile __cregister unsigned long __ECR434;
extern volatile __cregister unsigned long __ECR435;
extern volatile __cregister unsigned long __ECR436;
extern volatile __cregister unsigned long __ECR437;
extern volatile __cregister unsigned long __ECR438;
extern volatile __cregister unsigned long __ECR439;
extern volatile __cregister unsigned long __ECR440;
extern volatile __cregister unsigned long __ECR441;
extern volatile __cregister unsigned long __ECR442;
extern volatile __cregister unsigned long __ECR443;
extern volatile __cregister unsigned long __ECR444;
extern volatile __cregister unsigned long __ECR445;
extern volatile __cregister unsigned long __ECR446;
extern volatile __cregister unsigned long __ECR447;
extern volatile __cregister unsigned long __ECR448;
extern volatile __cregister unsigned long __ECR449;
extern volatile __cregister unsigned long __ECR450;
extern volatile __cregister unsigned long __ECR451;
extern volatile __cregister unsigned long __ECR452;
extern volatile __cregister unsigned long __ECR453;
extern volatile __cregister unsigned long __ECR454;
extern volatile __cregister unsigned long __ECR455;
extern volatile __cregister unsigned long __ECR456;
extern volatile __cregister unsigned long __ECR457;
extern volatile __cregister unsigned long __ECR458;
extern volatile __cregister unsigned long __ECR459;
extern volatile __cregister unsigned long __ECR460;
extern volatile __cregister unsigned long __ECR461;
extern volatile __cregister unsigned long __ECR462;
extern volatile __cregister unsigned long __ECR463;
extern volatile __cregister unsigned long __ECR464;
extern volatile __cregister unsigned long __ECR465;
extern volatile __cregister unsigned long __ECR466;
extern volatile __cregister unsigned long __ECR467;
extern volatile __cregister unsigned long __ECR468;
extern volatile __cregister unsigned long __ECR469;
extern volatile __cregister unsigned long __ECR470;
extern volatile __cregister unsigned long __ECR471;
extern volatile __cregister unsigned long __ECR472;
extern volatile __cregister unsigned long __ECR473;
extern volatile __cregister unsigned long __ECR474;
extern volatile __cregister unsigned long __ECR475;
extern volatile __cregister unsigned long __ECR476;
extern volatile __cregister unsigned long __ECR477;
extern volatile __cregister unsigned long __ECR478;
extern volatile __cregister unsigned long __ECR479;
extern volatile __cregister unsigned long __ECR480;
extern volatile __cregister unsigned long __ECR481;
extern volatile __cregister unsigned long __ECR482;
extern volatile __cregister unsigned long __ECR483;
extern volatile __cregister unsigned long __ECR484;
extern volatile __cregister unsigned long __ECR485;
extern volatile __cregister unsigned long __ECR486;
extern volatile __cregister unsigned long __ECR487;
extern volatile __cregister unsigned long __ECR488;
extern volatile __cregister unsigned long __ECR489;
extern volatile __cregister unsigned long __ECR490;
extern volatile __cregister unsigned long __ECR491;
extern volatile __cregister unsigned long __ECR492;
extern volatile __cregister unsigned long __ECR493;
extern volatile __cregister unsigned long __ECR494;
extern volatile __cregister unsigned long __ECR495;
extern volatile __cregister unsigned long __ECR496;
extern volatile __cregister unsigned long __ECR497;
extern volatile __cregister unsigned long __ECR498;
extern volatile __cregister unsigned long __ECR499;
extern volatile __cregister unsigned long __ECR500;
extern volatile __cregister unsigned long __ECR501;
extern volatile __cregister unsigned long __ECR502;
extern volatile __cregister unsigned long __ECR503;
extern volatile __cregister unsigned long __ECR504;
extern volatile __cregister unsigned long __ECR505;
extern volatile __cregister unsigned long __ECR506;
extern volatile __cregister unsigned long __ECR507;
extern volatile __cregister unsigned long __ECR508;
extern volatile __cregister unsigned long __ECR509;
extern volatile __cregister unsigned long __ECR510;
extern volatile __cregister unsigned long __ECR511;
extern volatile __cregister unsigned long __ECR512;

/******************************************************************************/
/* ECR: SE0_PID                                                               */
/* DESCRIPTION: Stream 0 PID Register                                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x60E00800                                            */
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
#define __ECR_SE0_PID __ECR512

extern volatile __cregister unsigned long __ECR513;

/******************************************************************************/
/* ECR: SE0_FAR                                                               */
/* DESCRIPTION: Stream 0 Fail Address Register                                */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_SE0_FAR __ECR513

extern volatile __cregister unsigned long __ECR514;

/******************************************************************************/
/* ECR: SE0_FSR                                                               */
/* DESCRIPTION: Stream 0 Fail Status Register                                 */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_SE0_FSR __ECR514

extern volatile __cregister unsigned long __ECR515;
extern volatile __cregister unsigned long __ECR516;
extern volatile __cregister unsigned long __ECR517;
extern volatile __cregister unsigned long __ECR518;
extern volatile __cregister unsigned long __ECR519;
extern volatile __cregister unsigned long __ECR520;

/******************************************************************************/
/* ECR: SE0_TAG                                                               */
/* DESCRIPTION: Stream 0 Tag Data and Metadata Register                       */
/* INDEX RANGE: [0,15]                                                        */
/* GENERAL RESET VALUE: 0x6                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */

extern volatile __cregister unsigned long __ECR521;

#if defined(__C7100__)
/******************************************************************************/
/* ECR: SE0_ICNT                                                              */
/* DESCRIPTION: Stream 0 Iteration Count Register                             */
/* INDEX RANGE: [0,28]                                                        */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */
#elif defined(__C7120__)
/******************************************************************************/
/* ECR: SE0_ICNT                                                              */
/* DESCRIPTION: Stream 0 Iteration Count Register                             */
/* INDEX RANGE: [0,54]                                                        */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */
#endif

extern volatile __cregister unsigned long __ECR522;

/******************************************************************************/
/* ECR: SE0_DIM                                                               */
/* DESCRIPTION: Stream 0 Dimension Register                                   */
/* INDEX RANGE: [0,4]                                                         */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */

extern volatile __cregister unsigned long __ECR523;

/******************************************************************************/
/* ECR: SE0_ADDR                                                              */
/* DESCRIPTION: Stream 0 Address Register                                     */
/* INDEX RANGE: [0,13]                                                        */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */

extern volatile __cregister unsigned long __ECR524;

#if defined(__C7100__)
/******************************************************************************/
/* ECR: SE0_STATUS                                                            */
/* DESCRIPTION: Stream 0 Status and Flag Register                             */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */
#elif defined(__C7120__)
/******************************************************************************/
/* ECR: SE0_STATUS                                                            */
/* DESCRIPTION: Stream 0 Status and Flag Register                             */
/* INDEX RANGE: [0,1]                                                         */
/* INDEX 0 RESET VALUE: 0x0                                                   */
/* INDEX 1 RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */
#endif

extern volatile __cregister unsigned long __ECR525;

#if defined(__C7120__)
/******************************************************************************/
/* ECR: SE0_SBND                                                              */
/* DESCRIPTION: Stream 0 Sideband Register                                    */
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
#define __ECR_SE0_SBND __ECR525
#endif

extern volatile __cregister unsigned long __ECR526;
extern volatile __cregister unsigned long __ECR527;
extern volatile __cregister unsigned long __ECR528;

/******************************************************************************/
/* ECR: SE1_PID                                                               */
/* DESCRIPTION: Stream 1 PID Register                                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x60E00800                                            */
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
#define __ECR_SE1_PID __ECR528

extern volatile __cregister unsigned long __ECR529;

/******************************************************************************/
/* ECR: SE1_FAR                                                               */
/* DESCRIPTION: Stream 1 Fail Address Register                                */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_SE1_FAR __ECR529

extern volatile __cregister unsigned long __ECR530;

/******************************************************************************/
/* ECR: SE1_FSR                                                               */
/* DESCRIPTION: Stream 1 Fail Status Register                                 */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_SE1_FSR __ECR530

extern volatile __cregister unsigned long __ECR531;
extern volatile __cregister unsigned long __ECR532;
extern volatile __cregister unsigned long __ECR533;
extern volatile __cregister unsigned long __ECR534;
extern volatile __cregister unsigned long __ECR535;
extern volatile __cregister unsigned long __ECR536;

/******************************************************************************/
/* ECR: SE1_TAG                                                               */
/* DESCRIPTION: Stream 1 Tag Data and Metadata Register                       */
/* INDEX RANGE: [0,15]                                                        */
/* GENERAL RESET VALUE: 0x6                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */

extern volatile __cregister unsigned long __ECR537;

#if defined(__C7100__)
/******************************************************************************/
/* ECR: SE1_ICNT                                                              */
/* DESCRIPTION: Stream 1 Iteration Count Register                             */
/* INDEX RANGE: [0,28]                                                        */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */
#elif defined(__C7120__)
/******************************************************************************/
/* ECR: SE1_ICNT                                                              */
/* DESCRIPTION: Stream 1 Iteration Count Register                             */
/* INDEX RANGE: [0,54]                                                        */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */
#endif

extern volatile __cregister unsigned long __ECR538;

/******************************************************************************/
/* ECR: SE1_DIM                                                               */
/* DESCRIPTION: Stream 1 Dimension Register                                   */
/* INDEX RANGE: [0,4]                                                         */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */

extern volatile __cregister unsigned long __ECR539;

/******************************************************************************/
/* ECR: SE1_ADDR                                                              */
/* DESCRIPTION: Stream 1 Address Register                                     */
/* INDEX RANGE: [0,13]                                                        */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */

extern volatile __cregister unsigned long __ECR540;

#if defined(__C7100__)
/******************************************************************************/
/* ECR: SE1_STATUS                                                            */
/* DESCRIPTION: Stream 1 Status and Flag Register                             */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */
#elif defined(__C7120__)
/******************************************************************************/
/* ECR: SE1_STATUS                                                            */
/* DESCRIPTION: Stream 1 Status and Flag Register                             */
/* INDEX RANGE: [0,1]                                                         */
/* INDEX 0 RESET VALUE: 0x0                                                   */
/* INDEX 1 RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */
#endif

extern volatile __cregister unsigned long __ECR541;

#if defined(__C7120__)
/******************************************************************************/
/* ECR: SE1_SBND                                                              */
/* DESCRIPTION: Stream 1 Sideband Register                                    */
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
#define __ECR_SE1_SBND __ECR541
#endif

extern volatile __cregister unsigned long __ECR542;
extern volatile __cregister unsigned long __ECR543;
extern volatile __cregister unsigned long __ECR544;

/******************************************************************************/
/* ECR: SE2_PID                                                               */
/* DESCRIPTION: Stream 2 PID Register                                         */
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
#define __ECR_SE2_PID __ECR544

extern volatile __cregister unsigned long __ECR545;
extern volatile __cregister unsigned long __ECR546;
extern volatile __cregister unsigned long __ECR547;
extern volatile __cregister unsigned long __ECR548;
extern volatile __cregister unsigned long __ECR549;
extern volatile __cregister unsigned long __ECR550;
extern volatile __cregister unsigned long __ECR551;
extern volatile __cregister unsigned long __ECR552;
extern volatile __cregister unsigned long __ECR553;
extern volatile __cregister unsigned long __ECR554;
extern volatile __cregister unsigned long __ECR555;
extern volatile __cregister unsigned long __ECR556;
extern volatile __cregister unsigned long __ECR557;
extern volatile __cregister unsigned long __ECR558;
extern volatile __cregister unsigned long __ECR559;
extern volatile __cregister unsigned long __ECR560;

/******************************************************************************/
/* ECR: SE3_PID                                                               */
/* DESCRIPTION: Stream 3 PID Register                                         */
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
#define __ECR_SE3_PID __ECR560

extern volatile __cregister unsigned long __ECR561;
extern volatile __cregister unsigned long __ECR562;
extern volatile __cregister unsigned long __ECR563;
extern volatile __cregister unsigned long __ECR564;
extern volatile __cregister unsigned long __ECR565;
extern volatile __cregister unsigned long __ECR566;
extern volatile __cregister unsigned long __ECR567;
extern volatile __cregister unsigned long __ECR568;
extern volatile __cregister unsigned long __ECR569;
extern volatile __cregister unsigned long __ECR570;
extern volatile __cregister unsigned long __ECR571;
extern volatile __cregister unsigned long __ECR572;
extern volatile __cregister unsigned long __ECR573;
extern volatile __cregister unsigned long __ECR574;
extern volatile __cregister unsigned long __ECR575;
extern volatile __cregister unsigned long __ECR576;
extern volatile __cregister unsigned long __ECR577;
extern volatile __cregister unsigned long __ECR578;
extern volatile __cregister unsigned long __ECR579;
extern volatile __cregister unsigned long __ECR580;
extern volatile __cregister unsigned long __ECR581;
extern volatile __cregister unsigned long __ECR582;
extern volatile __cregister unsigned long __ECR583;
extern volatile __cregister unsigned long __ECR584;
extern volatile __cregister unsigned long __ECR585;
extern volatile __cregister unsigned long __ECR586;
extern volatile __cregister unsigned long __ECR587;
extern volatile __cregister unsigned long __ECR588;
extern volatile __cregister unsigned long __ECR589;
extern volatile __cregister unsigned long __ECR590;
extern volatile __cregister unsigned long __ECR591;
extern volatile __cregister unsigned long __ECR592;
extern volatile __cregister unsigned long __ECR593;
extern volatile __cregister unsigned long __ECR594;
extern volatile __cregister unsigned long __ECR595;
extern volatile __cregister unsigned long __ECR596;
extern volatile __cregister unsigned long __ECR597;
extern volatile __cregister unsigned long __ECR598;
extern volatile __cregister unsigned long __ECR599;
extern volatile __cregister unsigned long __ECR600;
extern volatile __cregister unsigned long __ECR601;
extern volatile __cregister unsigned long __ECR602;
extern volatile __cregister unsigned long __ECR603;
extern volatile __cregister unsigned long __ECR604;
extern volatile __cregister unsigned long __ECR605;
extern volatile __cregister unsigned long __ECR606;
extern volatile __cregister unsigned long __ECR607;
extern volatile __cregister unsigned long __ECR608;
extern volatile __cregister unsigned long __ECR609;
extern volatile __cregister unsigned long __ECR610;
extern volatile __cregister unsigned long __ECR611;
extern volatile __cregister unsigned long __ECR612;
extern volatile __cregister unsigned long __ECR613;
extern volatile __cregister unsigned long __ECR614;
extern volatile __cregister unsigned long __ECR615;
extern volatile __cregister unsigned long __ECR616;
extern volatile __cregister unsigned long __ECR617;
extern volatile __cregister unsigned long __ECR618;
extern volatile __cregister unsigned long __ECR619;
extern volatile __cregister unsigned long __ECR620;
extern volatile __cregister unsigned long __ECR621;
extern volatile __cregister unsigned long __ECR622;
extern volatile __cregister unsigned long __ECR623;
extern volatile __cregister unsigned long __ECR624;
extern volatile __cregister unsigned long __ECR625;
extern volatile __cregister unsigned long __ECR626;
extern volatile __cregister unsigned long __ECR627;
extern volatile __cregister unsigned long __ECR628;
extern volatile __cregister unsigned long __ECR629;
extern volatile __cregister unsigned long __ECR630;
extern volatile __cregister unsigned long __ECR631;
extern volatile __cregister unsigned long __ECR632;
extern volatile __cregister unsigned long __ECR633;
extern volatile __cregister unsigned long __ECR634;
extern volatile __cregister unsigned long __ECR635;
extern volatile __cregister unsigned long __ECR636;
extern volatile __cregister unsigned long __ECR637;
extern volatile __cregister unsigned long __ECR638;
extern volatile __cregister unsigned long __ECR639;
extern volatile __cregister unsigned long __ECR640;
extern volatile __cregister unsigned long __ECR641;
extern volatile __cregister unsigned long __ECR642;
extern volatile __cregister unsigned long __ECR643;
extern volatile __cregister unsigned long __ECR644;
extern volatile __cregister unsigned long __ECR645;
extern volatile __cregister unsigned long __ECR646;
extern volatile __cregister unsigned long __ECR647;
extern volatile __cregister unsigned long __ECR648;
extern volatile __cregister unsigned long __ECR649;
extern volatile __cregister unsigned long __ECR650;
extern volatile __cregister unsigned long __ECR651;
extern volatile __cregister unsigned long __ECR652;
extern volatile __cregister unsigned long __ECR653;
extern volatile __cregister unsigned long __ECR654;
extern volatile __cregister unsigned long __ECR655;
extern volatile __cregister unsigned long __ECR656;
extern volatile __cregister unsigned long __ECR657;
extern volatile __cregister unsigned long __ECR658;
extern volatile __cregister unsigned long __ECR659;
extern volatile __cregister unsigned long __ECR660;
extern volatile __cregister unsigned long __ECR661;
extern volatile __cregister unsigned long __ECR662;
extern volatile __cregister unsigned long __ECR663;
extern volatile __cregister unsigned long __ECR664;
extern volatile __cregister unsigned long __ECR665;
extern volatile __cregister unsigned long __ECR666;
extern volatile __cregister unsigned long __ECR667;
extern volatile __cregister unsigned long __ECR668;
extern volatile __cregister unsigned long __ECR669;
extern volatile __cregister unsigned long __ECR670;
extern volatile __cregister unsigned long __ECR671;
extern volatile __cregister unsigned long __ECR672;
extern volatile __cregister unsigned long __ECR673;
extern volatile __cregister unsigned long __ECR674;
extern volatile __cregister unsigned long __ECR675;
extern volatile __cregister unsigned long __ECR676;
extern volatile __cregister unsigned long __ECR677;
extern volatile __cregister unsigned long __ECR678;
extern volatile __cregister unsigned long __ECR679;
extern volatile __cregister unsigned long __ECR680;
extern volatile __cregister unsigned long __ECR681;
extern volatile __cregister unsigned long __ECR682;
extern volatile __cregister unsigned long __ECR683;
extern volatile __cregister unsigned long __ECR684;
extern volatile __cregister unsigned long __ECR685;
extern volatile __cregister unsigned long __ECR686;
extern volatile __cregister unsigned long __ECR687;
extern volatile __cregister unsigned long __ECR688;
extern volatile __cregister unsigned long __ECR689;
extern volatile __cregister unsigned long __ECR690;
extern volatile __cregister unsigned long __ECR691;
extern volatile __cregister unsigned long __ECR692;
extern volatile __cregister unsigned long __ECR693;
extern volatile __cregister unsigned long __ECR694;
extern volatile __cregister unsigned long __ECR695;
extern volatile __cregister unsigned long __ECR696;
extern volatile __cregister unsigned long __ECR697;
extern volatile __cregister unsigned long __ECR698;
extern volatile __cregister unsigned long __ECR699;
extern volatile __cregister unsigned long __ECR700;
extern volatile __cregister unsigned long __ECR701;
extern volatile __cregister unsigned long __ECR702;
extern volatile __cregister unsigned long __ECR703;
extern volatile __cregister unsigned long __ECR704;
extern volatile __cregister unsigned long __ECR705;
extern volatile __cregister unsigned long __ECR706;
extern volatile __cregister unsigned long __ECR707;
extern volatile __cregister unsigned long __ECR708;
extern volatile __cregister unsigned long __ECR709;
extern volatile __cregister unsigned long __ECR710;
extern volatile __cregister unsigned long __ECR711;
extern volatile __cregister unsigned long __ECR712;
extern volatile __cregister unsigned long __ECR713;
extern volatile __cregister unsigned long __ECR714;
extern volatile __cregister unsigned long __ECR715;
extern volatile __cregister unsigned long __ECR716;
extern volatile __cregister unsigned long __ECR717;
extern volatile __cregister unsigned long __ECR718;
extern volatile __cregister unsigned long __ECR719;
extern volatile __cregister unsigned long __ECR720;
extern volatile __cregister unsigned long __ECR721;
extern volatile __cregister unsigned long __ECR722;
extern volatile __cregister unsigned long __ECR723;
extern volatile __cregister unsigned long __ECR724;
extern volatile __cregister unsigned long __ECR725;
extern volatile __cregister unsigned long __ECR726;
extern volatile __cregister unsigned long __ECR727;
extern volatile __cregister unsigned long __ECR728;
extern volatile __cregister unsigned long __ECR729;
extern volatile __cregister unsigned long __ECR730;
extern volatile __cregister unsigned long __ECR731;
extern volatile __cregister unsigned long __ECR732;
extern volatile __cregister unsigned long __ECR733;
extern volatile __cregister unsigned long __ECR734;
extern volatile __cregister unsigned long __ECR735;
extern volatile __cregister unsigned long __ECR736;
extern volatile __cregister unsigned long __ECR737;
extern volatile __cregister unsigned long __ECR738;
extern volatile __cregister unsigned long __ECR739;
extern volatile __cregister unsigned long __ECR740;
extern volatile __cregister unsigned long __ECR741;
extern volatile __cregister unsigned long __ECR742;
extern volatile __cregister unsigned long __ECR743;
extern volatile __cregister unsigned long __ECR744;
extern volatile __cregister unsigned long __ECR745;
extern volatile __cregister unsigned long __ECR746;
extern volatile __cregister unsigned long __ECR747;
extern volatile __cregister unsigned long __ECR748;
extern volatile __cregister unsigned long __ECR749;
extern volatile __cregister unsigned long __ECR750;
extern volatile __cregister unsigned long __ECR751;
extern volatile __cregister unsigned long __ECR752;
extern volatile __cregister unsigned long __ECR753;
extern volatile __cregister unsigned long __ECR754;
extern volatile __cregister unsigned long __ECR755;
extern volatile __cregister unsigned long __ECR756;
extern volatile __cregister unsigned long __ECR757;
extern volatile __cregister unsigned long __ECR758;
extern volatile __cregister unsigned long __ECR759;
extern volatile __cregister unsigned long __ECR760;
extern volatile __cregister unsigned long __ECR761;
extern volatile __cregister unsigned long __ECR762;
extern volatile __cregister unsigned long __ECR763;
extern volatile __cregister unsigned long __ECR764;
extern volatile __cregister unsigned long __ECR765;
extern volatile __cregister unsigned long __ECR766;
extern volatile __cregister unsigned long __ECR767;
extern volatile __cregister unsigned long __ECR768;

/******************************************************************************/
/* ECR: MMU_PID                                                               */
/* DESCRIPTION: Physical ID Register                                          */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x60F00000                                            */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/*     Secure Supervisor: RO                                                  */
/*     Supervisor:        RO                                                  */
/*     Guest Supervisor:  RO                                                  */
/******************************************************************************/
#define __ECR_MMU_PID __ECR768

extern volatile __cregister unsigned long __ECR769;
extern volatile __cregister unsigned long __ECR770;

/******************************************************************************/
/* ECR: MMU_REPL                                                              */
/* DESCRIPTION: Replacement Policy Register                                   */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_MMU_REPL __ECR770

extern volatile __cregister unsigned long __ECR771;
extern volatile __cregister unsigned long __ECR772;

/******************************************************************************/
/* ECR: TDRR                                                                  */
/* DESCRIPTION: Translation Debug Response Register                           */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_TDRR __ECR772

extern volatile __cregister unsigned long __ECR773;

/******************************************************************************/
/* ECR: TDFAR                                                                 */
/* DESCRIPTION: Translation Debug Fault Address Register                      */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_TDFAR __ECR773

extern volatile __cregister unsigned long __ECR774;
extern volatile __cregister unsigned long __ECR775;
extern volatile __cregister unsigned long __ECR776;

/******************************************************************************/
/* ECR: TLB_INV                                                               */
/* DESCRIPTION: TLB Invalidation Register                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      WO                                                  */
/*     Non-Secure Debug:  WO                                                  */
/*     Secure Supervisor: WO                                                  */
/*     Supervisor:        WO                                                  */
/*     Guest Supervisor:  WO                                                  */
/******************************************************************************/
#define __ECR_TLB_INV __ECR776

extern volatile __cregister unsigned long __ECR777;
extern volatile __cregister unsigned long __ECR778;

/******************************************************************************/
/* ECR: TLB_INVC                                                              */
/* DESCRIPTION: TLB Complete Register                                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_TLB_INVC __ECR778

extern volatile __cregister unsigned long __ECR779;

/******************************************************************************/
/* ECR: TLB_DBG                                                               */
/* DESCRIPTION: TLB Debug Access Register                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      WO                                                  */
/*     Non-Secure Debug:  WO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */

extern volatile __cregister unsigned long __ECR780;

/******************************************************************************/
/* ECR: TLB_DBG_DATA0                                                         */
/* DESCRIPTION: TLB Debug Data 0 Register                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */

extern volatile __cregister unsigned long __ECR781;

/******************************************************************************/
/* ECR: TLB_DBG_DATA1                                                         */
/* DESCRIPTION: TLB Debug Data 1 Register                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RO                                                  */
/*     Non-Secure Debug:  RO                                                  */
/******************************************************************************/
/* Debug only; no macro provided.                                             */

extern volatile __cregister unsigned long __ECR782;
extern volatile __cregister unsigned long __ECR783;
extern volatile __cregister unsigned long __ECR784;

/******************************************************************************/
/* ECR: SCR                                                                   */
/* DESCRIPTION: System Control Register                                       */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_SCR __ECR784

extern volatile __cregister unsigned long __ECR785;

/******************************************************************************/
/* ECR: TCR0                                                                  */
/* DESCRIPTION: Table Control Register 0                                      */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_TCR0 __ECR785

extern volatile __cregister unsigned long __ECR786;

/******************************************************************************/
/* ECR: TCR1                                                                  */
/* DESCRIPTION: Table Control Register 1                                      */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_TCR1 __ECR786

extern volatile __cregister unsigned long __ECR787;

/******************************************************************************/
/* ECR: TBR0                                                                  */
/* DESCRIPTION: Table Base Register 0                                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_TBR0 __ECR787

extern volatile __cregister unsigned long __ECR788;

/******************************************************************************/
/* ECR: TBR1                                                                  */
/* DESCRIPTION: Table Base Register 1                                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_TBR1 __ECR788

extern volatile __cregister unsigned long __ECR789;

/******************************************************************************/
/* ECR: MAR                                                                   */
/* DESCRIPTION: Memory Attribute Register                                     */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/*     Guest Supervisor:  RW                                                  */
/******************************************************************************/
#define __ECR_MAR __ECR789

extern volatile __cregister unsigned long __ECR790;

/******************************************************************************/
/* ECR: TDAR                                                                  */
/* DESCRIPTION: Translation Debug Address Register                            */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      WO                                                  */
/*     Non-Secure Debug:  WO                                                  */
/*     Secure Supervisor: WO                                                  */
/*     Supervisor:        WO                                                  */
/*     Guest Supervisor:  WO                                                  */
/******************************************************************************/
#define __ECR_TDAR __ECR790

extern volatile __cregister unsigned long __ECR791;
extern volatile __cregister unsigned long __ECR792;
extern volatile __cregister unsigned long __ECR793;
extern volatile __cregister unsigned long __ECR794;
extern volatile __cregister unsigned long __ECR795;
extern volatile __cregister unsigned long __ECR796;
extern volatile __cregister unsigned long __ECR797;
extern volatile __cregister unsigned long __ECR798;
extern volatile __cregister unsigned long __ECR799;
extern volatile __cregister unsigned long __ECR800;

/******************************************************************************/
/* ECR: SCR_GS                                                                */
/* DESCRIPTION: System Control Register - Non-Secure Guest Supervisor         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/******************************************************************************/
#define __ECR_SCR_GS __ECR800

extern volatile __cregister unsigned long __ECR801;

/******************************************************************************/
/* ECR: TCR0_GS                                                               */
/* DESCRIPTION: Table Control Register 0 - Non-Secure Guest Supervisor        */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/******************************************************************************/
#define __ECR_TCR0_GS __ECR801

extern volatile __cregister unsigned long __ECR802;

/******************************************************************************/
/* ECR: TCR1_GS                                                               */
/* DESCRIPTION: Table Control Register 1 - Non-Secure Guest Supervisor        */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/******************************************************************************/
#define __ECR_TCR1_GS __ECR802

extern volatile __cregister unsigned long __ECR803;

/******************************************************************************/
/* ECR: TBR0_GS                                                               */
/* DESCRIPTION: Table Base Register 0 - Non-Secure Guest Supervisor           */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/******************************************************************************/
#define __ECR_TBR0_GS __ECR803

extern volatile __cregister unsigned long __ECR804;

/******************************************************************************/
/* ECR: TBR1_GS                                                               */
/* DESCRIPTION: Table Base Register 1 - Non-Secure Guest Supervisor           */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/******************************************************************************/
#define __ECR_TBR1_GS __ECR804

extern volatile __cregister unsigned long __ECR805;

/******************************************************************************/
/* ECR: MAR_GS                                                                */
/* DESCRIPTION: Memory Attribute Register - Non-Secure Guest Supervisor       */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/******************************************************************************/
#define __ECR_MAR_GS __ECR805

extern volatile __cregister unsigned long __ECR806;

/******************************************************************************/
/* ECR: TDAR_GS                                                               */
/* DESCRIPTION: Translation Debug Address Register - Non-Secure Guest Supervisor */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      WO                                                  */
/*     Non-Secure Debug:  WO                                                  */
/*     Secure Supervisor: WO                                                  */
/*     Supervisor:        WO                                                  */
/******************************************************************************/
#define __ECR_TDAR_GS __ECR806

extern volatile __cregister unsigned long __ECR807;
extern volatile __cregister unsigned long __ECR808;
extern volatile __cregister unsigned long __ECR809;
extern volatile __cregister unsigned long __ECR810;
extern volatile __cregister unsigned long __ECR811;
extern volatile __cregister unsigned long __ECR812;
extern volatile __cregister unsigned long __ECR813;
extern volatile __cregister unsigned long __ECR814;
extern volatile __cregister unsigned long __ECR815;
extern volatile __cregister unsigned long __ECR816;

/******************************************************************************/
/* ECR: SCR_S                                                                 */
/* DESCRIPTION: System Control Register - Non-Secure Supervisor               */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Secure Supervisor: RW                                                  */
/******************************************************************************/
#define __ECR_SCR_S __ECR816

extern volatile __cregister unsigned long __ECR817;

/******************************************************************************/
/* ECR: TCR0_S                                                                */
/* DESCRIPTION: Table Control Register 0 - Non-Secure Supervisor              */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Secure Supervisor: RW                                                  */
/******************************************************************************/
#define __ECR_TCR0_S __ECR817

extern volatile __cregister unsigned long __ECR818;

/******************************************************************************/
/* ECR: TCR1_S                                                                */
/* DESCRIPTION: Table Control Register 1 - Non-Secure Supervisor              */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Secure Supervisor: RW                                                  */
/******************************************************************************/
#define __ECR_TCR1_S __ECR818

extern volatile __cregister unsigned long __ECR819;

/******************************************************************************/
/* ECR: TBR0_S                                                                */
/* DESCRIPTION: Table Base Register 0 - Non-Secure Supervisor                 */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Secure Supervisor: RW                                                  */
/******************************************************************************/
#define __ECR_TBR0_S __ECR819

extern volatile __cregister unsigned long __ECR820;

/******************************************************************************/
/* ECR: TBR1_S                                                                */
/* DESCRIPTION: Table Base Register 1 - Non-Secure Supervisor                 */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Secure Supervisor: RW                                                  */
/******************************************************************************/
#define __ECR_TBR1_S __ECR820

extern volatile __cregister unsigned long __ECR821;

/******************************************************************************/
/* ECR: MAR_S                                                                 */
/* DESCRIPTION: Memory Attribute Register - Non-Secure Supervisor             */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Secure Supervisor: RW                                                  */
/******************************************************************************/
#define __ECR_MAR_S __ECR821

extern volatile __cregister unsigned long __ECR822;

/******************************************************************************/
/* ECR: TDAR_S                                                                */
/* DESCRIPTION: Translation Debug Address Register - Non-Secure Supervisor    */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      WO                                                  */
/*     Secure Supervisor: WO                                                  */
/******************************************************************************/
#define __ECR_TDAR_S __ECR822

extern volatile __cregister unsigned long __ECR823;
extern volatile __cregister unsigned long __ECR824;
extern volatile __cregister unsigned long __ECR825;
extern volatile __cregister unsigned long __ECR826;
extern volatile __cregister unsigned long __ECR827;
extern volatile __cregister unsigned long __ECR828;
extern volatile __cregister unsigned long __ECR829;
extern volatile __cregister unsigned long __ECR830;
extern volatile __cregister unsigned long __ECR831;
extern volatile __cregister unsigned long __ECR832;
extern volatile __cregister unsigned long __ECR833;
extern volatile __cregister unsigned long __ECR834;
extern volatile __cregister unsigned long __ECR835;
extern volatile __cregister unsigned long __ECR836;
extern volatile __cregister unsigned long __ECR837;
extern volatile __cregister unsigned long __ECR838;
extern volatile __cregister unsigned long __ECR839;
extern volatile __cregister unsigned long __ECR840;
extern volatile __cregister unsigned long __ECR841;
extern volatile __cregister unsigned long __ECR842;
extern volatile __cregister unsigned long __ECR843;
extern volatile __cregister unsigned long __ECR844;
extern volatile __cregister unsigned long __ECR845;
extern volatile __cregister unsigned long __ECR846;
extern volatile __cregister unsigned long __ECR847;
extern volatile __cregister unsigned long __ECR848;
extern volatile __cregister unsigned long __ECR849;
extern volatile __cregister unsigned long __ECR850;
extern volatile __cregister unsigned long __ECR851;
extern volatile __cregister unsigned long __ECR852;
extern volatile __cregister unsigned long __ECR853;
extern volatile __cregister unsigned long __ECR854;
extern volatile __cregister unsigned long __ECR855;
extern volatile __cregister unsigned long __ECR856;
extern volatile __cregister unsigned long __ECR857;
extern volatile __cregister unsigned long __ECR858;
extern volatile __cregister unsigned long __ECR859;
extern volatile __cregister unsigned long __ECR860;
extern volatile __cregister unsigned long __ECR861;
extern volatile __cregister unsigned long __ECR862;
extern volatile __cregister unsigned long __ECR863;
extern volatile __cregister unsigned long __ECR864;

/******************************************************************************/
/* ECR: VCR                                                                   */
/* DESCRIPTION: Virtualization Control Register                               */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/******************************************************************************/
#define __ECR_VCR __ECR864

extern volatile __cregister unsigned long __ECR865;

/******************************************************************************/
/* ECR: VTCR                                                                  */
/* DESCRIPTION: Virtualization Table Control Register                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/******************************************************************************/
#define __ECR_VTCR __ECR865

extern volatile __cregister unsigned long __ECR866;

/******************************************************************************/
/* ECR: VTBR                                                                  */
/* DESCRIPTION: Virtualization Table Base Register                            */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      RW                                                  */
/*     Non-Secure Debug:  RW                                                  */
/*     Secure Supervisor: RW                                                  */
/*     Supervisor:        RW                                                  */
/******************************************************************************/
#define __ECR_VTBR __ECR866

extern volatile __cregister unsigned long __ECR867;

/******************************************************************************/
/* ECR: VTDAR                                                                 */
/* DESCRIPTION: Virtualization Translation Debug Address Register             */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x0                                                   */
/* PERMISSIONS (N/A not shown):                                               */
/*     Secure Debug:      WO                                                  */
/*     Non-Secure Debug:  WO                                                  */
/*     Secure Supervisor: WO                                                  */
/*     Supervisor:        WO                                                  */
/******************************************************************************/
#define __ECR_VTDAR __ECR867

extern volatile __cregister unsigned long __ECR868;
extern volatile __cregister unsigned long __ECR869;
extern volatile __cregister unsigned long __ECR870;
extern volatile __cregister unsigned long __ECR871;
extern volatile __cregister unsigned long __ECR872;
extern volatile __cregister unsigned long __ECR873;
extern volatile __cregister unsigned long __ECR874;
extern volatile __cregister unsigned long __ECR875;
extern volatile __cregister unsigned long __ECR876;
extern volatile __cregister unsigned long __ECR877;
extern volatile __cregister unsigned long __ECR878;
extern volatile __cregister unsigned long __ECR879;
extern volatile __cregister unsigned long __ECR880;
extern volatile __cregister unsigned long __ECR881;
extern volatile __cregister unsigned long __ECR882;
extern volatile __cregister unsigned long __ECR883;
extern volatile __cregister unsigned long __ECR884;
extern volatile __cregister unsigned long __ECR885;
extern volatile __cregister unsigned long __ECR886;
extern volatile __cregister unsigned long __ECR887;
extern volatile __cregister unsigned long __ECR888;
extern volatile __cregister unsigned long __ECR889;
extern volatile __cregister unsigned long __ECR890;
extern volatile __cregister unsigned long __ECR891;
extern volatile __cregister unsigned long __ECR892;
extern volatile __cregister unsigned long __ECR893;
extern volatile __cregister unsigned long __ECR894;
extern volatile __cregister unsigned long __ECR895;
extern volatile __cregister unsigned long __ECR896;

/******************************************************************************/
/* ECR: L1D_UTLB_MATCH                                                        */
/* DESCRIPTION: Indexed uTLB Page Match Entry                                 */
/* INDEX RANGE: [0,15]                                                        */
/* GENERAL RESET VALUE: 0x0                                                   */
/* INDEX 0 RESET VALUE: 0xF000070000000000                                    */
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
#define __ECR_L1D_UTLB_MATCH __ECR896

extern volatile __cregister unsigned long __ECR897;
extern volatile __cregister unsigned long __ECR898;

/******************************************************************************/
/* ECR: L1D_UTLB_ATTR                                                         */
/* DESCRIPTION: Indexed uTLB Page Attribute Entry                             */
/* INDEX RANGE: [0,15]                                                        */
/* GENERAL RESET VALUE: 0x0                                                   */
/* INDEX 0 RESET VALUE: 0x8000500000000000                                    */
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
#define __ECR_L1D_UTLB_ATTR __ECR898

extern volatile __cregister unsigned long __ECR899;
extern volatile __cregister unsigned long __ECR900;

/******************************************************************************/
/* ECR: L1D_UTLB_REPL                                                         */
/* DESCRIPTION: uTLB Replacement Policy Register                              */
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
#define __ECR_L1D_UTLB_REPL __ECR900

extern volatile __cregister unsigned long __ECR901;
extern volatile __cregister unsigned long __ECR902;
extern volatile __cregister unsigned long __ECR903;
extern volatile __cregister unsigned long __ECR904;

/******************************************************************************/
/* ECR: L1P_UTLB_MATCH                                                        */
/* DESCRIPTION: Indexed uTLB Page Match Entry                                 */
/* INDEX RANGE: [0,7]                                                         */
/* GENERAL RESET VALUE: 0x0                                                   */
/* INDEX 0 RESET VALUE: 0xF000070000000000                                    */
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
#define __ECR_L1P_UTLB_MATCH __ECR904

extern volatile __cregister unsigned long __ECR905;
extern volatile __cregister unsigned long __ECR906;

/******************************************************************************/
/* ECR: L1P_UTLB_ATTR                                                         */
/* DESCRIPTION: Indexed uTLB Page Attribute Entry                             */
/* INDEX RANGE: [0,7]                                                         */
/* GENERAL RESET VALUE: 0x0                                                   */
/* INDEX 0 RESET VALUE: 0x8000500000000000                                    */
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
#define __ECR_L1P_UTLB_ATTR __ECR906

extern volatile __cregister unsigned long __ECR907;
extern volatile __cregister unsigned long __ECR908;

/******************************************************************************/
/* ECR: L1P_UTLB_REPL                                                         */
/* DESCRIPTION: uTLB Replacement Policy Register                              */
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
#define __ECR_L1P_UTLB_REPL __ECR908

extern volatile __cregister unsigned long __ECR909;
extern volatile __cregister unsigned long __ECR910;
extern volatile __cregister unsigned long __ECR911;
extern volatile __cregister unsigned long __ECR912;

/******************************************************************************/
/* ECR: SE0_UTLB_MATCH                                                        */
/* DESCRIPTION: Indexed uTLB Page Match Entry                                 */
/* INDEX RANGE: [0,7]                                                         */
/* GENERAL RESET VALUE: 0x0                                                   */
/* INDEX 0 RESET VALUE: 0xF000070000000000                                    */
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
#define __ECR_SE0_UTLB_MATCH __ECR912

extern volatile __cregister unsigned long __ECR913;
extern volatile __cregister unsigned long __ECR914;

/******************************************************************************/
/* ECR: SE0_UTLB_ATTR                                                         */
/* DESCRIPTION: Indexed uTLB Page Attribute Entry                             */
/* INDEX RANGE: [0,7]                                                         */
/* GENERAL RESET VALUE: 0x0                                                   */
/* INDEX 0 RESET VALUE: 0x8000500000000000                                    */
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
#define __ECR_SE0_UTLB_ATTR __ECR914

extern volatile __cregister unsigned long __ECR915;
extern volatile __cregister unsigned long __ECR916;

/******************************************************************************/
/* ECR: SE0_UTLB_REPL                                                         */
/* DESCRIPTION: uTLB Replacement Policy Register                              */
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
#define __ECR_SE0_UTLB_REPL __ECR916

extern volatile __cregister unsigned long __ECR917;
extern volatile __cregister unsigned long __ECR918;
extern volatile __cregister unsigned long __ECR919;
extern volatile __cregister unsigned long __ECR920;

/******************************************************************************/
/* ECR: SE1_UTLB_MATCH                                                        */
/* DESCRIPTION: Indexed uTLB Page Match Entry                                 */
/* INDEX RANGE: [0,7]                                                         */
/* GENERAL RESET VALUE: 0x0                                                   */
/* INDEX 0 RESET VALUE: 0xF000070000000000                                    */
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
#define __ECR_SE1_UTLB_MATCH __ECR920

extern volatile __cregister unsigned long __ECR921;
extern volatile __cregister unsigned long __ECR922;

/******************************************************************************/
/* ECR: SE1_UTLB_ATTR                                                         */
/* DESCRIPTION: Indexed uTLB Page Attribute Entry                             */
/* INDEX RANGE: [0,7]                                                         */
/* GENERAL RESET VALUE: 0x0                                                   */
/* INDEX 0 RESET VALUE: 0x8000500000000000                                    */
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
#define __ECR_SE1_UTLB_ATTR __ECR922

extern volatile __cregister unsigned long __ECR923;
extern volatile __cregister unsigned long __ECR924;

/******************************************************************************/
/* ECR: SE1_UTLB_REPL                                                         */
/* DESCRIPTION: uTLB Replacement Policy Register                              */
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
#define __ECR_SE1_UTLB_REPL __ECR924

extern volatile __cregister unsigned long __ECR925;
extern volatile __cregister unsigned long __ECR926;
extern volatile __cregister unsigned long __ECR927;
extern volatile __cregister unsigned long __ECR928;
extern volatile __cregister unsigned long __ECR929;
extern volatile __cregister unsigned long __ECR930;
extern volatile __cregister unsigned long __ECR931;
extern volatile __cregister unsigned long __ECR932;
extern volatile __cregister unsigned long __ECR933;
extern volatile __cregister unsigned long __ECR934;
extern volatile __cregister unsigned long __ECR935;
extern volatile __cregister unsigned long __ECR936;
extern volatile __cregister unsigned long __ECR937;
extern volatile __cregister unsigned long __ECR938;
extern volatile __cregister unsigned long __ECR939;
extern volatile __cregister unsigned long __ECR940;
extern volatile __cregister unsigned long __ECR941;
extern volatile __cregister unsigned long __ECR942;
extern volatile __cregister unsigned long __ECR943;
extern volatile __cregister unsigned long __ECR944;
extern volatile __cregister unsigned long __ECR945;
extern volatile __cregister unsigned long __ECR946;
extern volatile __cregister unsigned long __ECR947;
extern volatile __cregister unsigned long __ECR948;
extern volatile __cregister unsigned long __ECR949;
extern volatile __cregister unsigned long __ECR950;
extern volatile __cregister unsigned long __ECR951;
extern volatile __cregister unsigned long __ECR952;
extern volatile __cregister unsigned long __ECR953;
extern volatile __cregister unsigned long __ECR954;
extern volatile __cregister unsigned long __ECR955;
extern volatile __cregister unsigned long __ECR956;
extern volatile __cregister unsigned long __ECR957;
extern volatile __cregister unsigned long __ECR958;
extern volatile __cregister unsigned long __ECR959;
extern volatile __cregister unsigned long __ECR960;
extern volatile __cregister unsigned long __ECR961;
extern volatile __cregister unsigned long __ECR962;
extern volatile __cregister unsigned long __ECR963;
extern volatile __cregister unsigned long __ECR964;
extern volatile __cregister unsigned long __ECR965;
extern volatile __cregister unsigned long __ECR966;
extern volatile __cregister unsigned long __ECR967;
extern volatile __cregister unsigned long __ECR968;
extern volatile __cregister unsigned long __ECR969;
extern volatile __cregister unsigned long __ECR970;
extern volatile __cregister unsigned long __ECR971;
extern volatile __cregister unsigned long __ECR972;
extern volatile __cregister unsigned long __ECR973;
extern volatile __cregister unsigned long __ECR974;
extern volatile __cregister unsigned long __ECR975;
extern volatile __cregister unsigned long __ECR976;
extern volatile __cregister unsigned long __ECR977;
extern volatile __cregister unsigned long __ECR978;
extern volatile __cregister unsigned long __ECR979;
extern volatile __cregister unsigned long __ECR980;
extern volatile __cregister unsigned long __ECR981;
extern volatile __cregister unsigned long __ECR982;
extern volatile __cregister unsigned long __ECR983;
extern volatile __cregister unsigned long __ECR984;
extern volatile __cregister unsigned long __ECR985;
extern volatile __cregister unsigned long __ECR986;
extern volatile __cregister unsigned long __ECR987;
extern volatile __cregister unsigned long __ECR988;
extern volatile __cregister unsigned long __ECR989;
extern volatile __cregister unsigned long __ECR990;
extern volatile __cregister unsigned long __ECR991;
extern volatile __cregister unsigned long __ECR992;
extern volatile __cregister unsigned long __ECR993;
extern volatile __cregister unsigned long __ECR994;
extern volatile __cregister unsigned long __ECR995;
extern volatile __cregister unsigned long __ECR996;
extern volatile __cregister unsigned long __ECR997;
extern volatile __cregister unsigned long __ECR998;
extern volatile __cregister unsigned long __ECR999;
extern volatile __cregister unsigned long __ECR1000;
extern volatile __cregister unsigned long __ECR1001;
extern volatile __cregister unsigned long __ECR1002;
extern volatile __cregister unsigned long __ECR1003;
extern volatile __cregister unsigned long __ECR1004;
extern volatile __cregister unsigned long __ECR1005;
extern volatile __cregister unsigned long __ECR1006;
extern volatile __cregister unsigned long __ECR1007;
extern volatile __cregister unsigned long __ECR1008;
extern volatile __cregister unsigned long __ECR1009;
extern volatile __cregister unsigned long __ECR1010;
extern volatile __cregister unsigned long __ECR1011;
extern volatile __cregister unsigned long __ECR1012;
extern volatile __cregister unsigned long __ECR1013;
extern volatile __cregister unsigned long __ECR1014;
extern volatile __cregister unsigned long __ECR1015;
extern volatile __cregister unsigned long __ECR1016;
extern volatile __cregister unsigned long __ECR1017;
extern volatile __cregister unsigned long __ECR1018;
extern volatile __cregister unsigned long __ECR1019;
extern volatile __cregister unsigned long __ECR1020;
extern volatile __cregister unsigned long __ECR1021;
extern volatile __cregister unsigned long __ECR1022;
extern volatile __cregister unsigned long __ECR1023;
extern volatile __cregister unsigned long __ECR1024;
extern volatile __cregister unsigned long __ECR1025;
extern volatile __cregister unsigned long __ECR1026;
extern volatile __cregister unsigned long __ECR1027;
extern volatile __cregister unsigned long __ECR1028;
extern volatile __cregister unsigned long __ECR1029;
extern volatile __cregister unsigned long __ECR1030;
extern volatile __cregister unsigned long __ECR1031;
extern volatile __cregister unsigned long __ECR1032;
extern volatile __cregister unsigned long __ECR1033;
extern volatile __cregister unsigned long __ECR1034;
extern volatile __cregister unsigned long __ECR1035;
extern volatile __cregister unsigned long __ECR1036;
extern volatile __cregister unsigned long __ECR1037;
extern volatile __cregister unsigned long __ECR1038;
extern volatile __cregister unsigned long __ECR1039;
extern volatile __cregister unsigned long __ECR1040;
extern volatile __cregister unsigned long __ECR1041;
extern volatile __cregister unsigned long __ECR1042;
extern volatile __cregister unsigned long __ECR1043;
extern volatile __cregister unsigned long __ECR1044;
extern volatile __cregister unsigned long __ECR1045;
extern volatile __cregister unsigned long __ECR1046;
extern volatile __cregister unsigned long __ECR1047;
extern volatile __cregister unsigned long __ECR1048;
extern volatile __cregister unsigned long __ECR1049;
extern volatile __cregister unsigned long __ECR1050;
extern volatile __cregister unsigned long __ECR1051;
extern volatile __cregister unsigned long __ECR1052;
extern volatile __cregister unsigned long __ECR1053;
extern volatile __cregister unsigned long __ECR1054;
extern volatile __cregister unsigned long __ECR1055;
extern volatile __cregister unsigned long __ECR1056;
extern volatile __cregister unsigned long __ECR1057;
extern volatile __cregister unsigned long __ECR1058;
extern volatile __cregister unsigned long __ECR1059;
extern volatile __cregister unsigned long __ECR1060;
extern volatile __cregister unsigned long __ECR1061;
extern volatile __cregister unsigned long __ECR1062;
extern volatile __cregister unsigned long __ECR1063;
extern volatile __cregister unsigned long __ECR1064;
extern volatile __cregister unsigned long __ECR1065;
extern volatile __cregister unsigned long __ECR1066;
extern volatile __cregister unsigned long __ECR1067;
extern volatile __cregister unsigned long __ECR1068;
extern volatile __cregister unsigned long __ECR1069;
extern volatile __cregister unsigned long __ECR1070;
extern volatile __cregister unsigned long __ECR1071;
extern volatile __cregister unsigned long __ECR1072;
extern volatile __cregister unsigned long __ECR1073;
extern volatile __cregister unsigned long __ECR1074;
extern volatile __cregister unsigned long __ECR1075;
extern volatile __cregister unsigned long __ECR1076;
extern volatile __cregister unsigned long __ECR1077;
extern volatile __cregister unsigned long __ECR1078;
extern volatile __cregister unsigned long __ECR1079;
extern volatile __cregister unsigned long __ECR1080;
extern volatile __cregister unsigned long __ECR1081;
extern volatile __cregister unsigned long __ECR1082;
extern volatile __cregister unsigned long __ECR1083;
extern volatile __cregister unsigned long __ECR1084;
extern volatile __cregister unsigned long __ECR1085;
extern volatile __cregister unsigned long __ECR1086;
extern volatile __cregister unsigned long __ECR1087;
extern volatile __cregister unsigned long __ECR1088;
extern volatile __cregister unsigned long __ECR1089;
extern volatile __cregister unsigned long __ECR1090;
extern volatile __cregister unsigned long __ECR1091;
extern volatile __cregister unsigned long __ECR1092;
extern volatile __cregister unsigned long __ECR1093;
extern volatile __cregister unsigned long __ECR1094;
extern volatile __cregister unsigned long __ECR1095;
extern volatile __cregister unsigned long __ECR1096;
extern volatile __cregister unsigned long __ECR1097;
extern volatile __cregister unsigned long __ECR1098;
extern volatile __cregister unsigned long __ECR1099;
extern volatile __cregister unsigned long __ECR1100;
extern volatile __cregister unsigned long __ECR1101;
extern volatile __cregister unsigned long __ECR1102;
extern volatile __cregister unsigned long __ECR1103;
extern volatile __cregister unsigned long __ECR1104;
extern volatile __cregister unsigned long __ECR1105;
extern volatile __cregister unsigned long __ECR1106;
extern volatile __cregister unsigned long __ECR1107;
extern volatile __cregister unsigned long __ECR1108;
extern volatile __cregister unsigned long __ECR1109;
extern volatile __cregister unsigned long __ECR1110;
extern volatile __cregister unsigned long __ECR1111;
extern volatile __cregister unsigned long __ECR1112;
extern volatile __cregister unsigned long __ECR1113;
extern volatile __cregister unsigned long __ECR1114;
extern volatile __cregister unsigned long __ECR1115;
extern volatile __cregister unsigned long __ECR1116;
extern volatile __cregister unsigned long __ECR1117;
extern volatile __cregister unsigned long __ECR1118;
extern volatile __cregister unsigned long __ECR1119;
extern volatile __cregister unsigned long __ECR1120;
extern volatile __cregister unsigned long __ECR1121;
extern volatile __cregister unsigned long __ECR1122;
extern volatile __cregister unsigned long __ECR1123;
extern volatile __cregister unsigned long __ECR1124;
extern volatile __cregister unsigned long __ECR1125;
extern volatile __cregister unsigned long __ECR1126;
extern volatile __cregister unsigned long __ECR1127;
extern volatile __cregister unsigned long __ECR1128;
extern volatile __cregister unsigned long __ECR1129;
extern volatile __cregister unsigned long __ECR1130;
extern volatile __cregister unsigned long __ECR1131;
extern volatile __cregister unsigned long __ECR1132;
extern volatile __cregister unsigned long __ECR1133;
extern volatile __cregister unsigned long __ECR1134;
extern volatile __cregister unsigned long __ECR1135;
extern volatile __cregister unsigned long __ECR1136;
extern volatile __cregister unsigned long __ECR1137;
extern volatile __cregister unsigned long __ECR1138;
extern volatile __cregister unsigned long __ECR1139;
extern volatile __cregister unsigned long __ECR1140;
extern volatile __cregister unsigned long __ECR1141;
extern volatile __cregister unsigned long __ECR1142;
extern volatile __cregister unsigned long __ECR1143;
extern volatile __cregister unsigned long __ECR1144;
extern volatile __cregister unsigned long __ECR1145;
extern volatile __cregister unsigned long __ECR1146;
extern volatile __cregister unsigned long __ECR1147;
extern volatile __cregister unsigned long __ECR1148;
extern volatile __cregister unsigned long __ECR1149;
extern volatile __cregister unsigned long __ECR1150;
extern volatile __cregister unsigned long __ECR1151;
extern volatile __cregister unsigned long __ECR1152;
extern volatile __cregister unsigned long __ECR1153;
extern volatile __cregister unsigned long __ECR1154;
extern volatile __cregister unsigned long __ECR1155;
extern volatile __cregister unsigned long __ECR1156;
extern volatile __cregister unsigned long __ECR1157;
extern volatile __cregister unsigned long __ECR1158;
extern volatile __cregister unsigned long __ECR1159;
extern volatile __cregister unsigned long __ECR1160;
extern volatile __cregister unsigned long __ECR1161;
extern volatile __cregister unsigned long __ECR1162;
extern volatile __cregister unsigned long __ECR1163;
extern volatile __cregister unsigned long __ECR1164;
extern volatile __cregister unsigned long __ECR1165;
extern volatile __cregister unsigned long __ECR1166;
extern volatile __cregister unsigned long __ECR1167;
extern volatile __cregister unsigned long __ECR1168;
extern volatile __cregister unsigned long __ECR1169;
extern volatile __cregister unsigned long __ECR1170;
extern volatile __cregister unsigned long __ECR1171;
extern volatile __cregister unsigned long __ECR1172;
extern volatile __cregister unsigned long __ECR1173;
extern volatile __cregister unsigned long __ECR1174;
extern volatile __cregister unsigned long __ECR1175;
extern volatile __cregister unsigned long __ECR1176;
extern volatile __cregister unsigned long __ECR1177;
extern volatile __cregister unsigned long __ECR1178;
extern volatile __cregister unsigned long __ECR1179;
extern volatile __cregister unsigned long __ECR1180;
extern volatile __cregister unsigned long __ECR1181;
extern volatile __cregister unsigned long __ECR1182;
extern volatile __cregister unsigned long __ECR1183;
extern volatile __cregister unsigned long __ECR1184;
extern volatile __cregister unsigned long __ECR1185;
extern volatile __cregister unsigned long __ECR1186;
extern volatile __cregister unsigned long __ECR1187;
extern volatile __cregister unsigned long __ECR1188;
extern volatile __cregister unsigned long __ECR1189;
extern volatile __cregister unsigned long __ECR1190;
extern volatile __cregister unsigned long __ECR1191;
extern volatile __cregister unsigned long __ECR1192;
extern volatile __cregister unsigned long __ECR1193;
extern volatile __cregister unsigned long __ECR1194;
extern volatile __cregister unsigned long __ECR1195;
extern volatile __cregister unsigned long __ECR1196;
extern volatile __cregister unsigned long __ECR1197;
extern volatile __cregister unsigned long __ECR1198;
extern volatile __cregister unsigned long __ECR1199;
extern volatile __cregister unsigned long __ECR1200;
extern volatile __cregister unsigned long __ECR1201;
extern volatile __cregister unsigned long __ECR1202;
extern volatile __cregister unsigned long __ECR1203;
extern volatile __cregister unsigned long __ECR1204;
extern volatile __cregister unsigned long __ECR1205;
extern volatile __cregister unsigned long __ECR1206;
extern volatile __cregister unsigned long __ECR1207;
extern volatile __cregister unsigned long __ECR1208;
extern volatile __cregister unsigned long __ECR1209;
extern volatile __cregister unsigned long __ECR1210;
extern volatile __cregister unsigned long __ECR1211;
extern volatile __cregister unsigned long __ECR1212;
extern volatile __cregister unsigned long __ECR1213;
extern volatile __cregister unsigned long __ECR1214;
extern volatile __cregister unsigned long __ECR1215;
extern volatile __cregister unsigned long __ECR1216;
extern volatile __cregister unsigned long __ECR1217;
extern volatile __cregister unsigned long __ECR1218;
extern volatile __cregister unsigned long __ECR1219;
extern volatile __cregister unsigned long __ECR1220;
extern volatile __cregister unsigned long __ECR1221;
extern volatile __cregister unsigned long __ECR1222;
extern volatile __cregister unsigned long __ECR1223;
extern volatile __cregister unsigned long __ECR1224;
extern volatile __cregister unsigned long __ECR1225;
extern volatile __cregister unsigned long __ECR1226;
extern volatile __cregister unsigned long __ECR1227;
extern volatile __cregister unsigned long __ECR1228;
extern volatile __cregister unsigned long __ECR1229;
extern volatile __cregister unsigned long __ECR1230;
extern volatile __cregister unsigned long __ECR1231;
extern volatile __cregister unsigned long __ECR1232;
extern volatile __cregister unsigned long __ECR1233;
extern volatile __cregister unsigned long __ECR1234;
extern volatile __cregister unsigned long __ECR1235;
extern volatile __cregister unsigned long __ECR1236;
extern volatile __cregister unsigned long __ECR1237;
extern volatile __cregister unsigned long __ECR1238;
extern volatile __cregister unsigned long __ECR1239;
extern volatile __cregister unsigned long __ECR1240;
extern volatile __cregister unsigned long __ECR1241;
extern volatile __cregister unsigned long __ECR1242;
extern volatile __cregister unsigned long __ECR1243;
extern volatile __cregister unsigned long __ECR1244;
extern volatile __cregister unsigned long __ECR1245;
extern volatile __cregister unsigned long __ECR1246;
extern volatile __cregister unsigned long __ECR1247;
extern volatile __cregister unsigned long __ECR1248;
extern volatile __cregister unsigned long __ECR1249;
extern volatile __cregister unsigned long __ECR1250;
extern volatile __cregister unsigned long __ECR1251;
extern volatile __cregister unsigned long __ECR1252;
extern volatile __cregister unsigned long __ECR1253;
extern volatile __cregister unsigned long __ECR1254;
extern volatile __cregister unsigned long __ECR1255;
extern volatile __cregister unsigned long __ECR1256;
extern volatile __cregister unsigned long __ECR1257;
extern volatile __cregister unsigned long __ECR1258;
extern volatile __cregister unsigned long __ECR1259;
extern volatile __cregister unsigned long __ECR1260;
extern volatile __cregister unsigned long __ECR1261;
extern volatile __cregister unsigned long __ECR1262;
extern volatile __cregister unsigned long __ECR1263;
extern volatile __cregister unsigned long __ECR1264;
extern volatile __cregister unsigned long __ECR1265;
extern volatile __cregister unsigned long __ECR1266;
extern volatile __cregister unsigned long __ECR1267;
extern volatile __cregister unsigned long __ECR1268;
extern volatile __cregister unsigned long __ECR1269;
extern volatile __cregister unsigned long __ECR1270;
extern volatile __cregister unsigned long __ECR1271;
extern volatile __cregister unsigned long __ECR1272;
extern volatile __cregister unsigned long __ECR1273;
extern volatile __cregister unsigned long __ECR1274;
extern volatile __cregister unsigned long __ECR1275;
extern volatile __cregister unsigned long __ECR1276;
extern volatile __cregister unsigned long __ECR1277;
extern volatile __cregister unsigned long __ECR1278;
extern volatile __cregister unsigned long __ECR1279;
extern volatile __cregister unsigned long __ECR1280;
extern volatile __cregister unsigned long __ECR1281;
extern volatile __cregister unsigned long __ECR1282;
extern volatile __cregister unsigned long __ECR1283;
extern volatile __cregister unsigned long __ECR1284;
extern volatile __cregister unsigned long __ECR1285;
extern volatile __cregister unsigned long __ECR1286;
extern volatile __cregister unsigned long __ECR1287;
extern volatile __cregister unsigned long __ECR1288;
extern volatile __cregister unsigned long __ECR1289;
extern volatile __cregister unsigned long __ECR1290;
extern volatile __cregister unsigned long __ECR1291;
extern volatile __cregister unsigned long __ECR1292;
extern volatile __cregister unsigned long __ECR1293;
extern volatile __cregister unsigned long __ECR1294;
extern volatile __cregister unsigned long __ECR1295;
extern volatile __cregister unsigned long __ECR1296;
extern volatile __cregister unsigned long __ECR1297;
extern volatile __cregister unsigned long __ECR1298;
extern volatile __cregister unsigned long __ECR1299;
extern volatile __cregister unsigned long __ECR1300;
extern volatile __cregister unsigned long __ECR1301;
extern volatile __cregister unsigned long __ECR1302;
extern volatile __cregister unsigned long __ECR1303;
extern volatile __cregister unsigned long __ECR1304;
extern volatile __cregister unsigned long __ECR1305;
extern volatile __cregister unsigned long __ECR1306;
extern volatile __cregister unsigned long __ECR1307;
extern volatile __cregister unsigned long __ECR1308;
extern volatile __cregister unsigned long __ECR1309;
extern volatile __cregister unsigned long __ECR1310;
extern volatile __cregister unsigned long __ECR1311;
extern volatile __cregister unsigned long __ECR1312;
extern volatile __cregister unsigned long __ECR1313;
extern volatile __cregister unsigned long __ECR1314;
extern volatile __cregister unsigned long __ECR1315;
extern volatile __cregister unsigned long __ECR1316;
extern volatile __cregister unsigned long __ECR1317;
extern volatile __cregister unsigned long __ECR1318;
extern volatile __cregister unsigned long __ECR1319;
extern volatile __cregister unsigned long __ECR1320;
extern volatile __cregister unsigned long __ECR1321;
extern volatile __cregister unsigned long __ECR1322;
extern volatile __cregister unsigned long __ECR1323;
extern volatile __cregister unsigned long __ECR1324;
extern volatile __cregister unsigned long __ECR1325;
extern volatile __cregister unsigned long __ECR1326;
extern volatile __cregister unsigned long __ECR1327;
extern volatile __cregister unsigned long __ECR1328;
extern volatile __cregister unsigned long __ECR1329;
extern volatile __cregister unsigned long __ECR1330;
extern volatile __cregister unsigned long __ECR1331;
extern volatile __cregister unsigned long __ECR1332;
extern volatile __cregister unsigned long __ECR1333;
extern volatile __cregister unsigned long __ECR1334;
extern volatile __cregister unsigned long __ECR1335;
extern volatile __cregister unsigned long __ECR1336;
extern volatile __cregister unsigned long __ECR1337;
extern volatile __cregister unsigned long __ECR1338;
extern volatile __cregister unsigned long __ECR1339;
extern volatile __cregister unsigned long __ECR1340;
extern volatile __cregister unsigned long __ECR1341;
extern volatile __cregister unsigned long __ECR1342;
extern volatile __cregister unsigned long __ECR1343;
extern volatile __cregister unsigned long __ECR1344;
extern volatile __cregister unsigned long __ECR1345;
extern volatile __cregister unsigned long __ECR1346;
extern volatile __cregister unsigned long __ECR1347;
extern volatile __cregister unsigned long __ECR1348;
extern volatile __cregister unsigned long __ECR1349;
extern volatile __cregister unsigned long __ECR1350;
extern volatile __cregister unsigned long __ECR1351;
extern volatile __cregister unsigned long __ECR1352;
extern volatile __cregister unsigned long __ECR1353;
extern volatile __cregister unsigned long __ECR1354;
extern volatile __cregister unsigned long __ECR1355;
extern volatile __cregister unsigned long __ECR1356;
extern volatile __cregister unsigned long __ECR1357;
extern volatile __cregister unsigned long __ECR1358;
extern volatile __cregister unsigned long __ECR1359;
extern volatile __cregister unsigned long __ECR1360;
extern volatile __cregister unsigned long __ECR1361;
extern volatile __cregister unsigned long __ECR1362;
extern volatile __cregister unsigned long __ECR1363;
extern volatile __cregister unsigned long __ECR1364;
extern volatile __cregister unsigned long __ECR1365;
extern volatile __cregister unsigned long __ECR1366;
extern volatile __cregister unsigned long __ECR1367;
extern volatile __cregister unsigned long __ECR1368;
extern volatile __cregister unsigned long __ECR1369;
extern volatile __cregister unsigned long __ECR1370;
extern volatile __cregister unsigned long __ECR1371;
extern volatile __cregister unsigned long __ECR1372;
extern volatile __cregister unsigned long __ECR1373;
extern volatile __cregister unsigned long __ECR1374;
extern volatile __cregister unsigned long __ECR1375;
extern volatile __cregister unsigned long __ECR1376;
extern volatile __cregister unsigned long __ECR1377;
extern volatile __cregister unsigned long __ECR1378;
extern volatile __cregister unsigned long __ECR1379;
extern volatile __cregister unsigned long __ECR1380;
extern volatile __cregister unsigned long __ECR1381;
extern volatile __cregister unsigned long __ECR1382;
extern volatile __cregister unsigned long __ECR1383;
extern volatile __cregister unsigned long __ECR1384;
extern volatile __cregister unsigned long __ECR1385;
extern volatile __cregister unsigned long __ECR1386;
extern volatile __cregister unsigned long __ECR1387;
extern volatile __cregister unsigned long __ECR1388;
extern volatile __cregister unsigned long __ECR1389;
extern volatile __cregister unsigned long __ECR1390;
extern volatile __cregister unsigned long __ECR1391;
extern volatile __cregister unsigned long __ECR1392;
extern volatile __cregister unsigned long __ECR1393;
extern volatile __cregister unsigned long __ECR1394;
extern volatile __cregister unsigned long __ECR1395;
extern volatile __cregister unsigned long __ECR1396;
extern volatile __cregister unsigned long __ECR1397;
extern volatile __cregister unsigned long __ECR1398;
extern volatile __cregister unsigned long __ECR1399;
extern volatile __cregister unsigned long __ECR1400;
extern volatile __cregister unsigned long __ECR1401;
extern volatile __cregister unsigned long __ECR1402;
extern volatile __cregister unsigned long __ECR1403;
extern volatile __cregister unsigned long __ECR1404;
extern volatile __cregister unsigned long __ECR1405;
extern volatile __cregister unsigned long __ECR1406;
extern volatile __cregister unsigned long __ECR1407;
extern volatile __cregister unsigned long __ECR1408;
extern volatile __cregister unsigned long __ECR1409;
extern volatile __cregister unsigned long __ECR1410;
extern volatile __cregister unsigned long __ECR1411;
extern volatile __cregister unsigned long __ECR1412;
extern volatile __cregister unsigned long __ECR1413;
extern volatile __cregister unsigned long __ECR1414;
extern volatile __cregister unsigned long __ECR1415;
extern volatile __cregister unsigned long __ECR1416;
extern volatile __cregister unsigned long __ECR1417;
extern volatile __cregister unsigned long __ECR1418;
extern volatile __cregister unsigned long __ECR1419;
extern volatile __cregister unsigned long __ECR1420;
extern volatile __cregister unsigned long __ECR1421;
extern volatile __cregister unsigned long __ECR1422;
extern volatile __cregister unsigned long __ECR1423;
extern volatile __cregister unsigned long __ECR1424;
extern volatile __cregister unsigned long __ECR1425;
extern volatile __cregister unsigned long __ECR1426;
extern volatile __cregister unsigned long __ECR1427;
extern volatile __cregister unsigned long __ECR1428;
extern volatile __cregister unsigned long __ECR1429;
extern volatile __cregister unsigned long __ECR1430;
extern volatile __cregister unsigned long __ECR1431;
extern volatile __cregister unsigned long __ECR1432;
extern volatile __cregister unsigned long __ECR1433;
extern volatile __cregister unsigned long __ECR1434;
extern volatile __cregister unsigned long __ECR1435;
extern volatile __cregister unsigned long __ECR1436;
extern volatile __cregister unsigned long __ECR1437;
extern volatile __cregister unsigned long __ECR1438;
extern volatile __cregister unsigned long __ECR1439;
extern volatile __cregister unsigned long __ECR1440;
extern volatile __cregister unsigned long __ECR1441;
extern volatile __cregister unsigned long __ECR1442;
extern volatile __cregister unsigned long __ECR1443;
extern volatile __cregister unsigned long __ECR1444;
extern volatile __cregister unsigned long __ECR1445;
extern volatile __cregister unsigned long __ECR1446;
extern volatile __cregister unsigned long __ECR1447;
extern volatile __cregister unsigned long __ECR1448;
extern volatile __cregister unsigned long __ECR1449;
extern volatile __cregister unsigned long __ECR1450;
extern volatile __cregister unsigned long __ECR1451;
extern volatile __cregister unsigned long __ECR1452;
extern volatile __cregister unsigned long __ECR1453;
extern volatile __cregister unsigned long __ECR1454;
extern volatile __cregister unsigned long __ECR1455;
extern volatile __cregister unsigned long __ECR1456;
extern volatile __cregister unsigned long __ECR1457;
extern volatile __cregister unsigned long __ECR1458;
extern volatile __cregister unsigned long __ECR1459;
extern volatile __cregister unsigned long __ECR1460;
extern volatile __cregister unsigned long __ECR1461;
extern volatile __cregister unsigned long __ECR1462;
extern volatile __cregister unsigned long __ECR1463;
extern volatile __cregister unsigned long __ECR1464;
extern volatile __cregister unsigned long __ECR1465;
extern volatile __cregister unsigned long __ECR1466;
extern volatile __cregister unsigned long __ECR1467;
extern volatile __cregister unsigned long __ECR1468;
extern volatile __cregister unsigned long __ECR1469;
extern volatile __cregister unsigned long __ECR1470;
extern volatile __cregister unsigned long __ECR1471;
extern volatile __cregister unsigned long __ECR1472;
extern volatile __cregister unsigned long __ECR1473;
extern volatile __cregister unsigned long __ECR1474;
extern volatile __cregister unsigned long __ECR1475;
extern volatile __cregister unsigned long __ECR1476;
extern volatile __cregister unsigned long __ECR1477;
extern volatile __cregister unsigned long __ECR1478;
extern volatile __cregister unsigned long __ECR1479;
extern volatile __cregister unsigned long __ECR1480;
extern volatile __cregister unsigned long __ECR1481;
extern volatile __cregister unsigned long __ECR1482;
extern volatile __cregister unsigned long __ECR1483;
extern volatile __cregister unsigned long __ECR1484;
extern volatile __cregister unsigned long __ECR1485;
extern volatile __cregister unsigned long __ECR1486;
extern volatile __cregister unsigned long __ECR1487;
extern volatile __cregister unsigned long __ECR1488;
extern volatile __cregister unsigned long __ECR1489;
extern volatile __cregister unsigned long __ECR1490;
extern volatile __cregister unsigned long __ECR1491;
extern volatile __cregister unsigned long __ECR1492;
extern volatile __cregister unsigned long __ECR1493;
extern volatile __cregister unsigned long __ECR1494;
extern volatile __cregister unsigned long __ECR1495;
extern volatile __cregister unsigned long __ECR1496;
extern volatile __cregister unsigned long __ECR1497;
extern volatile __cregister unsigned long __ECR1498;
extern volatile __cregister unsigned long __ECR1499;
extern volatile __cregister unsigned long __ECR1500;
extern volatile __cregister unsigned long __ECR1501;
extern volatile __cregister unsigned long __ECR1502;
extern volatile __cregister unsigned long __ECR1503;
extern volatile __cregister unsigned long __ECR1504;
extern volatile __cregister unsigned long __ECR1505;
extern volatile __cregister unsigned long __ECR1506;
extern volatile __cregister unsigned long __ECR1507;
extern volatile __cregister unsigned long __ECR1508;
extern volatile __cregister unsigned long __ECR1509;
extern volatile __cregister unsigned long __ECR1510;
extern volatile __cregister unsigned long __ECR1511;
extern volatile __cregister unsigned long __ECR1512;
extern volatile __cregister unsigned long __ECR1513;
extern volatile __cregister unsigned long __ECR1514;
extern volatile __cregister unsigned long __ECR1515;
extern volatile __cregister unsigned long __ECR1516;
extern volatile __cregister unsigned long __ECR1517;
extern volatile __cregister unsigned long __ECR1518;
extern volatile __cregister unsigned long __ECR1519;
extern volatile __cregister unsigned long __ECR1520;
extern volatile __cregister unsigned long __ECR1521;
extern volatile __cregister unsigned long __ECR1522;
extern volatile __cregister unsigned long __ECR1523;
extern volatile __cregister unsigned long __ECR1524;
extern volatile __cregister unsigned long __ECR1525;
extern volatile __cregister unsigned long __ECR1526;
extern volatile __cregister unsigned long __ECR1527;
extern volatile __cregister unsigned long __ECR1528;
extern volatile __cregister unsigned long __ECR1529;
extern volatile __cregister unsigned long __ECR1530;
extern volatile __cregister unsigned long __ECR1531;
extern volatile __cregister unsigned long __ECR1532;
extern volatile __cregister unsigned long __ECR1533;
extern volatile __cregister unsigned long __ECR1534;
extern volatile __cregister unsigned long __ECR1535;
extern volatile __cregister unsigned long __ECR1536;
extern volatile __cregister unsigned long __ECR1537;
extern volatile __cregister unsigned long __ECR1538;
extern volatile __cregister unsigned long __ECR1539;
extern volatile __cregister unsigned long __ECR1540;
extern volatile __cregister unsigned long __ECR1541;
extern volatile __cregister unsigned long __ECR1542;
extern volatile __cregister unsigned long __ECR1543;
extern volatile __cregister unsigned long __ECR1544;
extern volatile __cregister unsigned long __ECR1545;
extern volatile __cregister unsigned long __ECR1546;
extern volatile __cregister unsigned long __ECR1547;
extern volatile __cregister unsigned long __ECR1548;
extern volatile __cregister unsigned long __ECR1549;
extern volatile __cregister unsigned long __ECR1550;
extern volatile __cregister unsigned long __ECR1551;
extern volatile __cregister unsigned long __ECR1552;
extern volatile __cregister unsigned long __ECR1553;
extern volatile __cregister unsigned long __ECR1554;
extern volatile __cregister unsigned long __ECR1555;
extern volatile __cregister unsigned long __ECR1556;
extern volatile __cregister unsigned long __ECR1557;
extern volatile __cregister unsigned long __ECR1558;
extern volatile __cregister unsigned long __ECR1559;
extern volatile __cregister unsigned long __ECR1560;
extern volatile __cregister unsigned long __ECR1561;
extern volatile __cregister unsigned long __ECR1562;
extern volatile __cregister unsigned long __ECR1563;
extern volatile __cregister unsigned long __ECR1564;
extern volatile __cregister unsigned long __ECR1565;
extern volatile __cregister unsigned long __ECR1566;
extern volatile __cregister unsigned long __ECR1567;
extern volatile __cregister unsigned long __ECR1568;
extern volatile __cregister unsigned long __ECR1569;
extern volatile __cregister unsigned long __ECR1570;
extern volatile __cregister unsigned long __ECR1571;
extern volatile __cregister unsigned long __ECR1572;
extern volatile __cregister unsigned long __ECR1573;
extern volatile __cregister unsigned long __ECR1574;
extern volatile __cregister unsigned long __ECR1575;
extern volatile __cregister unsigned long __ECR1576;
extern volatile __cregister unsigned long __ECR1577;
extern volatile __cregister unsigned long __ECR1578;
extern volatile __cregister unsigned long __ECR1579;
extern volatile __cregister unsigned long __ECR1580;
extern volatile __cregister unsigned long __ECR1581;
extern volatile __cregister unsigned long __ECR1582;
extern volatile __cregister unsigned long __ECR1583;
extern volatile __cregister unsigned long __ECR1584;
extern volatile __cregister unsigned long __ECR1585;
extern volatile __cregister unsigned long __ECR1586;
extern volatile __cregister unsigned long __ECR1587;
extern volatile __cregister unsigned long __ECR1588;
extern volatile __cregister unsigned long __ECR1589;
extern volatile __cregister unsigned long __ECR1590;
extern volatile __cregister unsigned long __ECR1591;
extern volatile __cregister unsigned long __ECR1592;
extern volatile __cregister unsigned long __ECR1593;
extern volatile __cregister unsigned long __ECR1594;
extern volatile __cregister unsigned long __ECR1595;
extern volatile __cregister unsigned long __ECR1596;
extern volatile __cregister unsigned long __ECR1597;
extern volatile __cregister unsigned long __ECR1598;
extern volatile __cregister unsigned long __ECR1599;
extern volatile __cregister unsigned long __ECR1600;
extern volatile __cregister unsigned long __ECR1601;
extern volatile __cregister unsigned long __ECR1602;
extern volatile __cregister unsigned long __ECR1603;
extern volatile __cregister unsigned long __ECR1604;
extern volatile __cregister unsigned long __ECR1605;
extern volatile __cregister unsigned long __ECR1606;
extern volatile __cregister unsigned long __ECR1607;
extern volatile __cregister unsigned long __ECR1608;
extern volatile __cregister unsigned long __ECR1609;
extern volatile __cregister unsigned long __ECR1610;
extern volatile __cregister unsigned long __ECR1611;
extern volatile __cregister unsigned long __ECR1612;
extern volatile __cregister unsigned long __ECR1613;
extern volatile __cregister unsigned long __ECR1614;
extern volatile __cregister unsigned long __ECR1615;
extern volatile __cregister unsigned long __ECR1616;
extern volatile __cregister unsigned long __ECR1617;
extern volatile __cregister unsigned long __ECR1618;
extern volatile __cregister unsigned long __ECR1619;
extern volatile __cregister unsigned long __ECR1620;
extern volatile __cregister unsigned long __ECR1621;
extern volatile __cregister unsigned long __ECR1622;
extern volatile __cregister unsigned long __ECR1623;
extern volatile __cregister unsigned long __ECR1624;
extern volatile __cregister unsigned long __ECR1625;
extern volatile __cregister unsigned long __ECR1626;
extern volatile __cregister unsigned long __ECR1627;
extern volatile __cregister unsigned long __ECR1628;
extern volatile __cregister unsigned long __ECR1629;
extern volatile __cregister unsigned long __ECR1630;
extern volatile __cregister unsigned long __ECR1631;
extern volatile __cregister unsigned long __ECR1632;
extern volatile __cregister unsigned long __ECR1633;
extern volatile __cregister unsigned long __ECR1634;
extern volatile __cregister unsigned long __ECR1635;
extern volatile __cregister unsigned long __ECR1636;
extern volatile __cregister unsigned long __ECR1637;
extern volatile __cregister unsigned long __ECR1638;
extern volatile __cregister unsigned long __ECR1639;
extern volatile __cregister unsigned long __ECR1640;
extern volatile __cregister unsigned long __ECR1641;
extern volatile __cregister unsigned long __ECR1642;
extern volatile __cregister unsigned long __ECR1643;
extern volatile __cregister unsigned long __ECR1644;
extern volatile __cregister unsigned long __ECR1645;
extern volatile __cregister unsigned long __ECR1646;
extern volatile __cregister unsigned long __ECR1647;
extern volatile __cregister unsigned long __ECR1648;
extern volatile __cregister unsigned long __ECR1649;
extern volatile __cregister unsigned long __ECR1650;
extern volatile __cregister unsigned long __ECR1651;
extern volatile __cregister unsigned long __ECR1652;
extern volatile __cregister unsigned long __ECR1653;
extern volatile __cregister unsigned long __ECR1654;
extern volatile __cregister unsigned long __ECR1655;
extern volatile __cregister unsigned long __ECR1656;
extern volatile __cregister unsigned long __ECR1657;
extern volatile __cregister unsigned long __ECR1658;
extern volatile __cregister unsigned long __ECR1659;
extern volatile __cregister unsigned long __ECR1660;
extern volatile __cregister unsigned long __ECR1661;
extern volatile __cregister unsigned long __ECR1662;
extern volatile __cregister unsigned long __ECR1663;
extern volatile __cregister unsigned long __ECR1664;
extern volatile __cregister unsigned long __ECR1665;
extern volatile __cregister unsigned long __ECR1666;
extern volatile __cregister unsigned long __ECR1667;
extern volatile __cregister unsigned long __ECR1668;
extern volatile __cregister unsigned long __ECR1669;
extern volatile __cregister unsigned long __ECR1670;
extern volatile __cregister unsigned long __ECR1671;
extern volatile __cregister unsigned long __ECR1672;
extern volatile __cregister unsigned long __ECR1673;
extern volatile __cregister unsigned long __ECR1674;
extern volatile __cregister unsigned long __ECR1675;
extern volatile __cregister unsigned long __ECR1676;
extern volatile __cregister unsigned long __ECR1677;
extern volatile __cregister unsigned long __ECR1678;
extern volatile __cregister unsigned long __ECR1679;
extern volatile __cregister unsigned long __ECR1680;
extern volatile __cregister unsigned long __ECR1681;
extern volatile __cregister unsigned long __ECR1682;
extern volatile __cregister unsigned long __ECR1683;
extern volatile __cregister unsigned long __ECR1684;
extern volatile __cregister unsigned long __ECR1685;
extern volatile __cregister unsigned long __ECR1686;
extern volatile __cregister unsigned long __ECR1687;
extern volatile __cregister unsigned long __ECR1688;
extern volatile __cregister unsigned long __ECR1689;
extern volatile __cregister unsigned long __ECR1690;
extern volatile __cregister unsigned long __ECR1691;
extern volatile __cregister unsigned long __ECR1692;
extern volatile __cregister unsigned long __ECR1693;
extern volatile __cregister unsigned long __ECR1694;
extern volatile __cregister unsigned long __ECR1695;
extern volatile __cregister unsigned long __ECR1696;
extern volatile __cregister unsigned long __ECR1697;
extern volatile __cregister unsigned long __ECR1698;
extern volatile __cregister unsigned long __ECR1699;
extern volatile __cregister unsigned long __ECR1700;
extern volatile __cregister unsigned long __ECR1701;
extern volatile __cregister unsigned long __ECR1702;
extern volatile __cregister unsigned long __ECR1703;
extern volatile __cregister unsigned long __ECR1704;
extern volatile __cregister unsigned long __ECR1705;
extern volatile __cregister unsigned long __ECR1706;
extern volatile __cregister unsigned long __ECR1707;
extern volatile __cregister unsigned long __ECR1708;
extern volatile __cregister unsigned long __ECR1709;
extern volatile __cregister unsigned long __ECR1710;
extern volatile __cregister unsigned long __ECR1711;
extern volatile __cregister unsigned long __ECR1712;
extern volatile __cregister unsigned long __ECR1713;
extern volatile __cregister unsigned long __ECR1714;
extern volatile __cregister unsigned long __ECR1715;
extern volatile __cregister unsigned long __ECR1716;
extern volatile __cregister unsigned long __ECR1717;
extern volatile __cregister unsigned long __ECR1718;
extern volatile __cregister unsigned long __ECR1719;
extern volatile __cregister unsigned long __ECR1720;
extern volatile __cregister unsigned long __ECR1721;
extern volatile __cregister unsigned long __ECR1722;
extern volatile __cregister unsigned long __ECR1723;
extern volatile __cregister unsigned long __ECR1724;
extern volatile __cregister unsigned long __ECR1725;
extern volatile __cregister unsigned long __ECR1726;
extern volatile __cregister unsigned long __ECR1727;
extern volatile __cregister unsigned long __ECR1728;
extern volatile __cregister unsigned long __ECR1729;
extern volatile __cregister unsigned long __ECR1730;
extern volatile __cregister unsigned long __ECR1731;
extern volatile __cregister unsigned long __ECR1732;
extern volatile __cregister unsigned long __ECR1733;
extern volatile __cregister unsigned long __ECR1734;
extern volatile __cregister unsigned long __ECR1735;
extern volatile __cregister unsigned long __ECR1736;
extern volatile __cregister unsigned long __ECR1737;
extern volatile __cregister unsigned long __ECR1738;
extern volatile __cregister unsigned long __ECR1739;
extern volatile __cregister unsigned long __ECR1740;
extern volatile __cregister unsigned long __ECR1741;
extern volatile __cregister unsigned long __ECR1742;
extern volatile __cregister unsigned long __ECR1743;
extern volatile __cregister unsigned long __ECR1744;
extern volatile __cregister unsigned long __ECR1745;
extern volatile __cregister unsigned long __ECR1746;
extern volatile __cregister unsigned long __ECR1747;
extern volatile __cregister unsigned long __ECR1748;
extern volatile __cregister unsigned long __ECR1749;
extern volatile __cregister unsigned long __ECR1750;
extern volatile __cregister unsigned long __ECR1751;
extern volatile __cregister unsigned long __ECR1752;
extern volatile __cregister unsigned long __ECR1753;
extern volatile __cregister unsigned long __ECR1754;
extern volatile __cregister unsigned long __ECR1755;
extern volatile __cregister unsigned long __ECR1756;
extern volatile __cregister unsigned long __ECR1757;
extern volatile __cregister unsigned long __ECR1758;
extern volatile __cregister unsigned long __ECR1759;
extern volatile __cregister unsigned long __ECR1760;
extern volatile __cregister unsigned long __ECR1761;
extern volatile __cregister unsigned long __ECR1762;
extern volatile __cregister unsigned long __ECR1763;
extern volatile __cregister unsigned long __ECR1764;
extern volatile __cregister unsigned long __ECR1765;
extern volatile __cregister unsigned long __ECR1766;
extern volatile __cregister unsigned long __ECR1767;
extern volatile __cregister unsigned long __ECR1768;
extern volatile __cregister unsigned long __ECR1769;
extern volatile __cregister unsigned long __ECR1770;
extern volatile __cregister unsigned long __ECR1771;
extern volatile __cregister unsigned long __ECR1772;
extern volatile __cregister unsigned long __ECR1773;
extern volatile __cregister unsigned long __ECR1774;
extern volatile __cregister unsigned long __ECR1775;
extern volatile __cregister unsigned long __ECR1776;
extern volatile __cregister unsigned long __ECR1777;
extern volatile __cregister unsigned long __ECR1778;
extern volatile __cregister unsigned long __ECR1779;
extern volatile __cregister unsigned long __ECR1780;
extern volatile __cregister unsigned long __ECR1781;
extern volatile __cregister unsigned long __ECR1782;
extern volatile __cregister unsigned long __ECR1783;
extern volatile __cregister unsigned long __ECR1784;
extern volatile __cregister unsigned long __ECR1785;
extern volatile __cregister unsigned long __ECR1786;
extern volatile __cregister unsigned long __ECR1787;
extern volatile __cregister unsigned long __ECR1788;
extern volatile __cregister unsigned long __ECR1789;
extern volatile __cregister unsigned long __ECR1790;
extern volatile __cregister unsigned long __ECR1791;
extern volatile __cregister unsigned long __ECR1792;
extern volatile __cregister unsigned long __ECR1793;
extern volatile __cregister unsigned long __ECR1794;
extern volatile __cregister unsigned long __ECR1795;
extern volatile __cregister unsigned long __ECR1796;
extern volatile __cregister unsigned long __ECR1797;
extern volatile __cregister unsigned long __ECR1798;
extern volatile __cregister unsigned long __ECR1799;
extern volatile __cregister unsigned long __ECR1800;
extern volatile __cregister unsigned long __ECR1801;
extern volatile __cregister unsigned long __ECR1802;
extern volatile __cregister unsigned long __ECR1803;
extern volatile __cregister unsigned long __ECR1804;
extern volatile __cregister unsigned long __ECR1805;
extern volatile __cregister unsigned long __ECR1806;
extern volatile __cregister unsigned long __ECR1807;
extern volatile __cregister unsigned long __ECR1808;
extern volatile __cregister unsigned long __ECR1809;
extern volatile __cregister unsigned long __ECR1810;
extern volatile __cregister unsigned long __ECR1811;
extern volatile __cregister unsigned long __ECR1812;
extern volatile __cregister unsigned long __ECR1813;
extern volatile __cregister unsigned long __ECR1814;
extern volatile __cregister unsigned long __ECR1815;
extern volatile __cregister unsigned long __ECR1816;
extern volatile __cregister unsigned long __ECR1817;
extern volatile __cregister unsigned long __ECR1818;
extern volatile __cregister unsigned long __ECR1819;
extern volatile __cregister unsigned long __ECR1820;
extern volatile __cregister unsigned long __ECR1821;
extern volatile __cregister unsigned long __ECR1822;
extern volatile __cregister unsigned long __ECR1823;
extern volatile __cregister unsigned long __ECR1824;
extern volatile __cregister unsigned long __ECR1825;
extern volatile __cregister unsigned long __ECR1826;
extern volatile __cregister unsigned long __ECR1827;
extern volatile __cregister unsigned long __ECR1828;
extern volatile __cregister unsigned long __ECR1829;
extern volatile __cregister unsigned long __ECR1830;
extern volatile __cregister unsigned long __ECR1831;
extern volatile __cregister unsigned long __ECR1832;
extern volatile __cregister unsigned long __ECR1833;
extern volatile __cregister unsigned long __ECR1834;
extern volatile __cregister unsigned long __ECR1835;
extern volatile __cregister unsigned long __ECR1836;
extern volatile __cregister unsigned long __ECR1837;
extern volatile __cregister unsigned long __ECR1838;
extern volatile __cregister unsigned long __ECR1839;
extern volatile __cregister unsigned long __ECR1840;
extern volatile __cregister unsigned long __ECR1841;
extern volatile __cregister unsigned long __ECR1842;
extern volatile __cregister unsigned long __ECR1843;
extern volatile __cregister unsigned long __ECR1844;
extern volatile __cregister unsigned long __ECR1845;
extern volatile __cregister unsigned long __ECR1846;
extern volatile __cregister unsigned long __ECR1847;
extern volatile __cregister unsigned long __ECR1848;
extern volatile __cregister unsigned long __ECR1849;
extern volatile __cregister unsigned long __ECR1850;
extern volatile __cregister unsigned long __ECR1851;
extern volatile __cregister unsigned long __ECR1852;
extern volatile __cregister unsigned long __ECR1853;
extern volatile __cregister unsigned long __ECR1854;
extern volatile __cregister unsigned long __ECR1855;
extern volatile __cregister unsigned long __ECR1856;
extern volatile __cregister unsigned long __ECR1857;
extern volatile __cregister unsigned long __ECR1858;
extern volatile __cregister unsigned long __ECR1859;
extern volatile __cregister unsigned long __ECR1860;
extern volatile __cregister unsigned long __ECR1861;
extern volatile __cregister unsigned long __ECR1862;
extern volatile __cregister unsigned long __ECR1863;
extern volatile __cregister unsigned long __ECR1864;
extern volatile __cregister unsigned long __ECR1865;
extern volatile __cregister unsigned long __ECR1866;
extern volatile __cregister unsigned long __ECR1867;
extern volatile __cregister unsigned long __ECR1868;
extern volatile __cregister unsigned long __ECR1869;
extern volatile __cregister unsigned long __ECR1870;
extern volatile __cregister unsigned long __ECR1871;
extern volatile __cregister unsigned long __ECR1872;
extern volatile __cregister unsigned long __ECR1873;
extern volatile __cregister unsigned long __ECR1874;
extern volatile __cregister unsigned long __ECR1875;
extern volatile __cregister unsigned long __ECR1876;
extern volatile __cregister unsigned long __ECR1877;
extern volatile __cregister unsigned long __ECR1878;
extern volatile __cregister unsigned long __ECR1879;
extern volatile __cregister unsigned long __ECR1880;
extern volatile __cregister unsigned long __ECR1881;
extern volatile __cregister unsigned long __ECR1882;
extern volatile __cregister unsigned long __ECR1883;
extern volatile __cregister unsigned long __ECR1884;
extern volatile __cregister unsigned long __ECR1885;
extern volatile __cregister unsigned long __ECR1886;
extern volatile __cregister unsigned long __ECR1887;
extern volatile __cregister unsigned long __ECR1888;
extern volatile __cregister unsigned long __ECR1889;
extern volatile __cregister unsigned long __ECR1890;
extern volatile __cregister unsigned long __ECR1891;
extern volatile __cregister unsigned long __ECR1892;
extern volatile __cregister unsigned long __ECR1893;
extern volatile __cregister unsigned long __ECR1894;
extern volatile __cregister unsigned long __ECR1895;
extern volatile __cregister unsigned long __ECR1896;
extern volatile __cregister unsigned long __ECR1897;
extern volatile __cregister unsigned long __ECR1898;
extern volatile __cregister unsigned long __ECR1899;
extern volatile __cregister unsigned long __ECR1900;
extern volatile __cregister unsigned long __ECR1901;
extern volatile __cregister unsigned long __ECR1902;
extern volatile __cregister unsigned long __ECR1903;
extern volatile __cregister unsigned long __ECR1904;
extern volatile __cregister unsigned long __ECR1905;
extern volatile __cregister unsigned long __ECR1906;
extern volatile __cregister unsigned long __ECR1907;
extern volatile __cregister unsigned long __ECR1908;
extern volatile __cregister unsigned long __ECR1909;
extern volatile __cregister unsigned long __ECR1910;
extern volatile __cregister unsigned long __ECR1911;
extern volatile __cregister unsigned long __ECR1912;
extern volatile __cregister unsigned long __ECR1913;
extern volatile __cregister unsigned long __ECR1914;
extern volatile __cregister unsigned long __ECR1915;
extern volatile __cregister unsigned long __ECR1916;
extern volatile __cregister unsigned long __ECR1917;
extern volatile __cregister unsigned long __ECR1918;
extern volatile __cregister unsigned long __ECR1919;
extern volatile __cregister unsigned long __ECR1920;
extern volatile __cregister unsigned long __ECR1921;
extern volatile __cregister unsigned long __ECR1922;
extern volatile __cregister unsigned long __ECR1923;
extern volatile __cregister unsigned long __ECR1924;
extern volatile __cregister unsigned long __ECR1925;
extern volatile __cregister unsigned long __ECR1926;
extern volatile __cregister unsigned long __ECR1927;
extern volatile __cregister unsigned long __ECR1928;
extern volatile __cregister unsigned long __ECR1929;
extern volatile __cregister unsigned long __ECR1930;
extern volatile __cregister unsigned long __ECR1931;
extern volatile __cregister unsigned long __ECR1932;
extern volatile __cregister unsigned long __ECR1933;
extern volatile __cregister unsigned long __ECR1934;
extern volatile __cregister unsigned long __ECR1935;
extern volatile __cregister unsigned long __ECR1936;
extern volatile __cregister unsigned long __ECR1937;
extern volatile __cregister unsigned long __ECR1938;
extern volatile __cregister unsigned long __ECR1939;
extern volatile __cregister unsigned long __ECR1940;
extern volatile __cregister unsigned long __ECR1941;
extern volatile __cregister unsigned long __ECR1942;
extern volatile __cregister unsigned long __ECR1943;
extern volatile __cregister unsigned long __ECR1944;
extern volatile __cregister unsigned long __ECR1945;
extern volatile __cregister unsigned long __ECR1946;
extern volatile __cregister unsigned long __ECR1947;
extern volatile __cregister unsigned long __ECR1948;
extern volatile __cregister unsigned long __ECR1949;
extern volatile __cregister unsigned long __ECR1950;
extern volatile __cregister unsigned long __ECR1951;
extern volatile __cregister unsigned long __ECR1952;
extern volatile __cregister unsigned long __ECR1953;
extern volatile __cregister unsigned long __ECR1954;
extern volatile __cregister unsigned long __ECR1955;
extern volatile __cregister unsigned long __ECR1956;
extern volatile __cregister unsigned long __ECR1957;
extern volatile __cregister unsigned long __ECR1958;
extern volatile __cregister unsigned long __ECR1959;
extern volatile __cregister unsigned long __ECR1960;
extern volatile __cregister unsigned long __ECR1961;
extern volatile __cregister unsigned long __ECR1962;
extern volatile __cregister unsigned long __ECR1963;
extern volatile __cregister unsigned long __ECR1964;
extern volatile __cregister unsigned long __ECR1965;
extern volatile __cregister unsigned long __ECR1966;
extern volatile __cregister unsigned long __ECR1967;
extern volatile __cregister unsigned long __ECR1968;
extern volatile __cregister unsigned long __ECR1969;
extern volatile __cregister unsigned long __ECR1970;
extern volatile __cregister unsigned long __ECR1971;
extern volatile __cregister unsigned long __ECR1972;
extern volatile __cregister unsigned long __ECR1973;
extern volatile __cregister unsigned long __ECR1974;
extern volatile __cregister unsigned long __ECR1975;
extern volatile __cregister unsigned long __ECR1976;
extern volatile __cregister unsigned long __ECR1977;
extern volatile __cregister unsigned long __ECR1978;
extern volatile __cregister unsigned long __ECR1979;
extern volatile __cregister unsigned long __ECR1980;
extern volatile __cregister unsigned long __ECR1981;
extern volatile __cregister unsigned long __ECR1982;
extern volatile __cregister unsigned long __ECR1983;
extern volatile __cregister unsigned long __ECR1984;
extern volatile __cregister unsigned long __ECR1985;
extern volatile __cregister unsigned long __ECR1986;
extern volatile __cregister unsigned long __ECR1987;
extern volatile __cregister unsigned long __ECR1988;
extern volatile __cregister unsigned long __ECR1989;
extern volatile __cregister unsigned long __ECR1990;
extern volatile __cregister unsigned long __ECR1991;
extern volatile __cregister unsigned long __ECR1992;
extern volatile __cregister unsigned long __ECR1993;
extern volatile __cregister unsigned long __ECR1994;
extern volatile __cregister unsigned long __ECR1995;
extern volatile __cregister unsigned long __ECR1996;
extern volatile __cregister unsigned long __ECR1997;
extern volatile __cregister unsigned long __ECR1998;
extern volatile __cregister unsigned long __ECR1999;
extern volatile __cregister unsigned long __ECR2000;
extern volatile __cregister unsigned long __ECR2001;
extern volatile __cregister unsigned long __ECR2002;
extern volatile __cregister unsigned long __ECR2003;
extern volatile __cregister unsigned long __ECR2004;
extern volatile __cregister unsigned long __ECR2005;
extern volatile __cregister unsigned long __ECR2006;
extern volatile __cregister unsigned long __ECR2007;
extern volatile __cregister unsigned long __ECR2008;
extern volatile __cregister unsigned long __ECR2009;
extern volatile __cregister unsigned long __ECR2010;
extern volatile __cregister unsigned long __ECR2011;
extern volatile __cregister unsigned long __ECR2012;
extern volatile __cregister unsigned long __ECR2013;
extern volatile __cregister unsigned long __ECR2014;
extern volatile __cregister unsigned long __ECR2015;
extern volatile __cregister unsigned long __ECR2016;
extern volatile __cregister unsigned long __ECR2017;
extern volatile __cregister unsigned long __ECR2018;
extern volatile __cregister unsigned long __ECR2019;
extern volatile __cregister unsigned long __ECR2020;
extern volatile __cregister unsigned long __ECR2021;
extern volatile __cregister unsigned long __ECR2022;
extern volatile __cregister unsigned long __ECR2023;
extern volatile __cregister unsigned long __ECR2024;
extern volatile __cregister unsigned long __ECR2025;
extern volatile __cregister unsigned long __ECR2026;
extern volatile __cregister unsigned long __ECR2027;
extern volatile __cregister unsigned long __ECR2028;
extern volatile __cregister unsigned long __ECR2029;
extern volatile __cregister unsigned long __ECR2030;
extern volatile __cregister unsigned long __ECR2031;
extern volatile __cregister unsigned long __ECR2032;
extern volatile __cregister unsigned long __ECR2033;
extern volatile __cregister unsigned long __ECR2034;
extern volatile __cregister unsigned long __ECR2035;
extern volatile __cregister unsigned long __ECR2036;
extern volatile __cregister unsigned long __ECR2037;
extern volatile __cregister unsigned long __ECR2038;
extern volatile __cregister unsigned long __ECR2039;
extern volatile __cregister unsigned long __ECR2040;
extern volatile __cregister unsigned long __ECR2041;
extern volatile __cregister unsigned long __ECR2042;
extern volatile __cregister unsigned long __ECR2043;
extern volatile __cregister unsigned long __ECR2044;
extern volatile __cregister unsigned long __ECR2045;
extern volatile __cregister unsigned long __ECR2046;
extern volatile __cregister unsigned long __ECR2047;
extern volatile __cregister unsigned long __ECR2048;
extern volatile __cregister unsigned long __ECR2049;
extern volatile __cregister unsigned long __ECR2050;
extern volatile __cregister unsigned long __ECR2051;
extern volatile __cregister unsigned long __ECR2052;
extern volatile __cregister unsigned long __ECR2053;
extern volatile __cregister unsigned long __ECR2054;
extern volatile __cregister unsigned long __ECR2055;
extern volatile __cregister unsigned long __ECR2056;
extern volatile __cregister unsigned long __ECR2057;
extern volatile __cregister unsigned long __ECR2058;
extern volatile __cregister unsigned long __ECR2059;
extern volatile __cregister unsigned long __ECR2060;
extern volatile __cregister unsigned long __ECR2061;
extern volatile __cregister unsigned long __ECR2062;
extern volatile __cregister unsigned long __ECR2063;
extern volatile __cregister unsigned long __ECR2064;
extern volatile __cregister unsigned long __ECR2065;
extern volatile __cregister unsigned long __ECR2066;
extern volatile __cregister unsigned long __ECR2067;
extern volatile __cregister unsigned long __ECR2068;
extern volatile __cregister unsigned long __ECR2069;
extern volatile __cregister unsigned long __ECR2070;
extern volatile __cregister unsigned long __ECR2071;
extern volatile __cregister unsigned long __ECR2072;
extern volatile __cregister unsigned long __ECR2073;
extern volatile __cregister unsigned long __ECR2074;
extern volatile __cregister unsigned long __ECR2075;
extern volatile __cregister unsigned long __ECR2076;
extern volatile __cregister unsigned long __ECR2077;
extern volatile __cregister unsigned long __ECR2078;
extern volatile __cregister unsigned long __ECR2079;
extern volatile __cregister unsigned long __ECR2080;
extern volatile __cregister unsigned long __ECR2081;
extern volatile __cregister unsigned long __ECR2082;
extern volatile __cregister unsigned long __ECR2083;
extern volatile __cregister unsigned long __ECR2084;
extern volatile __cregister unsigned long __ECR2085;
extern volatile __cregister unsigned long __ECR2086;
extern volatile __cregister unsigned long __ECR2087;
extern volatile __cregister unsigned long __ECR2088;
extern volatile __cregister unsigned long __ECR2089;
extern volatile __cregister unsigned long __ECR2090;
extern volatile __cregister unsigned long __ECR2091;
extern volatile __cregister unsigned long __ECR2092;
extern volatile __cregister unsigned long __ECR2093;
extern volatile __cregister unsigned long __ECR2094;
extern volatile __cregister unsigned long __ECR2095;
extern volatile __cregister unsigned long __ECR2096;
extern volatile __cregister unsigned long __ECR2097;
extern volatile __cregister unsigned long __ECR2098;
extern volatile __cregister unsigned long __ECR2099;
extern volatile __cregister unsigned long __ECR2100;
extern volatile __cregister unsigned long __ECR2101;
extern volatile __cregister unsigned long __ECR2102;
extern volatile __cregister unsigned long __ECR2103;
extern volatile __cregister unsigned long __ECR2104;
extern volatile __cregister unsigned long __ECR2105;
extern volatile __cregister unsigned long __ECR2106;
extern volatile __cregister unsigned long __ECR2107;
extern volatile __cregister unsigned long __ECR2108;
extern volatile __cregister unsigned long __ECR2109;
extern volatile __cregister unsigned long __ECR2110;
extern volatile __cregister unsigned long __ECR2111;
extern volatile __cregister unsigned long __ECR2112;
extern volatile __cregister unsigned long __ECR2113;
extern volatile __cregister unsigned long __ECR2114;
extern volatile __cregister unsigned long __ECR2115;
extern volatile __cregister unsigned long __ECR2116;
extern volatile __cregister unsigned long __ECR2117;
extern volatile __cregister unsigned long __ECR2118;
extern volatile __cregister unsigned long __ECR2119;
extern volatile __cregister unsigned long __ECR2120;
extern volatile __cregister unsigned long __ECR2121;
extern volatile __cregister unsigned long __ECR2122;
extern volatile __cregister unsigned long __ECR2123;
extern volatile __cregister unsigned long __ECR2124;
extern volatile __cregister unsigned long __ECR2125;
extern volatile __cregister unsigned long __ECR2126;
extern volatile __cregister unsigned long __ECR2127;
extern volatile __cregister unsigned long __ECR2128;
extern volatile __cregister unsigned long __ECR2129;
extern volatile __cregister unsigned long __ECR2130;
extern volatile __cregister unsigned long __ECR2131;
extern volatile __cregister unsigned long __ECR2132;
extern volatile __cregister unsigned long __ECR2133;
extern volatile __cregister unsigned long __ECR2134;
extern volatile __cregister unsigned long __ECR2135;
extern volatile __cregister unsigned long __ECR2136;
extern volatile __cregister unsigned long __ECR2137;
extern volatile __cregister unsigned long __ECR2138;
extern volatile __cregister unsigned long __ECR2139;
extern volatile __cregister unsigned long __ECR2140;
extern volatile __cregister unsigned long __ECR2141;
extern volatile __cregister unsigned long __ECR2142;
extern volatile __cregister unsigned long __ECR2143;
extern volatile __cregister unsigned long __ECR2144;
extern volatile __cregister unsigned long __ECR2145;
extern volatile __cregister unsigned long __ECR2146;
extern volatile __cregister unsigned long __ECR2147;
extern volatile __cregister unsigned long __ECR2148;
extern volatile __cregister unsigned long __ECR2149;
extern volatile __cregister unsigned long __ECR2150;
extern volatile __cregister unsigned long __ECR2151;
extern volatile __cregister unsigned long __ECR2152;
extern volatile __cregister unsigned long __ECR2153;
extern volatile __cregister unsigned long __ECR2154;
extern volatile __cregister unsigned long __ECR2155;
extern volatile __cregister unsigned long __ECR2156;
extern volatile __cregister unsigned long __ECR2157;
extern volatile __cregister unsigned long __ECR2158;
extern volatile __cregister unsigned long __ECR2159;
extern volatile __cregister unsigned long __ECR2160;
extern volatile __cregister unsigned long __ECR2161;
extern volatile __cregister unsigned long __ECR2162;
extern volatile __cregister unsigned long __ECR2163;
extern volatile __cregister unsigned long __ECR2164;
extern volatile __cregister unsigned long __ECR2165;
extern volatile __cregister unsigned long __ECR2166;
extern volatile __cregister unsigned long __ECR2167;
extern volatile __cregister unsigned long __ECR2168;
extern volatile __cregister unsigned long __ECR2169;
extern volatile __cregister unsigned long __ECR2170;
extern volatile __cregister unsigned long __ECR2171;
extern volatile __cregister unsigned long __ECR2172;
extern volatile __cregister unsigned long __ECR2173;
extern volatile __cregister unsigned long __ECR2174;
extern volatile __cregister unsigned long __ECR2175;
extern volatile __cregister unsigned long __ECR2176;

/******************************************************************************/
/* ECR: TRC_ID                                                                */
/* DESCRIPTION: Trace ID Register                                             */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x62010000                                            */
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
#define __ECR_TRC_ID __ECR2176

extern volatile __cregister unsigned long __ECR2177;

/******************************************************************************/
/* ECR: TRC_OWN                                                               */
/* DESCRIPTION: Trace OWN Register                                            */
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
#define __ECR_TRC_OWN __ECR2177

extern volatile __cregister unsigned long __ECR2178;

/******************************************************************************/
/* ECR: TRC_CNTL                                                              */
/* DESCRIPTION: Trace Control Register                                        */
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
#define __ECR_TRC_CNTL __ECR2178

extern volatile __cregister unsigned long __ECR2179;

/******************************************************************************/
/* ECR: TRC_PER_CNT                                                           */
/* DESCRIPTION: Trace Periodic Counter Register                               */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x400                                                 */
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
#define __ECR_TRC_PER_CNT __ECR2179

extern volatile __cregister unsigned long __ECR2180;

/******************************************************************************/
/* ECR: TRC_STAT                                                              */
/* DESCRIPTION: Trace Status Register                                         */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x7F                                                  */
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
#define __ECR_TRC_STAT __ECR2180

extern volatile __cregister unsigned long __ECR2181;

/******************************************************************************/
/* ECR: TRC_TRIG0_CNTL_STAT                                                   */
/* DESCRIPTION: Trace Trigger0 Control and Status Register                    */
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
#define __ECR_TRC_TRIG0_CNTL_STAT __ECR2181

extern volatile __cregister unsigned long __ECR2182;

/******************************************************************************/
/* ECR: TRC_TRIG1_CNTL_STAT                                                   */
/* DESCRIPTION: Trace Trigger0 Control and Status Register                    */
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
#define __ECR_TRC_TRIG1_CNTL_STAT __ECR2182

extern volatile __cregister unsigned long __ECR2183;

/******************************************************************************/
/* ECR: TRC_TIMESTAMP_CNT_REG0                                                */
/* DESCRIPTION: Trace Time Stamp Counter Register 0                           */
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
#define __ECR_TRC_TIMESTAMP_CNT_REG0 __ECR2183

extern volatile __cregister unsigned long __ECR2184;

/******************************************************************************/
/* ECR: TRC_TIMESTAMP_CNT_REG1                                                */
/* DESCRIPTION: Trace Time Stamp Counter Register 1                           */
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
#define __ECR_TRC_TIMESTAMP_CNT_REG1 __ECR2184

extern volatile __cregister unsigned long __ECR2185;

/******************************************************************************/
/* ECR: TRC_EXPT_CNTL                                                         */
/* DESCRIPTION: Trace Export Control Register                                 */
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
#define __ECR_TRC_EXPT_CNTL __ECR2185

extern volatile __cregister unsigned long __ECR2186;

/******************************************************************************/
/* ECR: TRC_EXPT_STAT                                                         */
/* DESCRIPTION: Trace Export Status Register                                  */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x80000002                                            */
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
#define __ECR_TRC_EXPT_STAT __ECR2186

extern volatile __cregister unsigned long __ECR2187;

/******************************************************************************/
/* ECR: TRC_EXPT_ATID                                                         */
/* DESCRIPTION: Trace Export Trace ID Register                                */
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
#define __ECR_TRC_EXPT_ATID __ECR2187

extern volatile __cregister unsigned long __ECR2188;
extern volatile __cregister unsigned long __ECR2189;
extern volatile __cregister unsigned long __ECR2190;
extern volatile __cregister unsigned long __ECR2191;
extern volatile __cregister unsigned long __ECR2192;
extern volatile __cregister unsigned long __ECR2193;
extern volatile __cregister unsigned long __ECR2194;
extern volatile __cregister unsigned long __ECR2195;
extern volatile __cregister unsigned long __ECR2196;
extern volatile __cregister unsigned long __ECR2197;
extern volatile __cregister unsigned long __ECR2198;
extern volatile __cregister unsigned long __ECR2199;
extern volatile __cregister unsigned long __ECR2200;
extern volatile __cregister unsigned long __ECR2201;
extern volatile __cregister unsigned long __ECR2202;
extern volatile __cregister unsigned long __ECR2203;
extern volatile __cregister unsigned long __ECR2204;
extern volatile __cregister unsigned long __ECR2205;
extern volatile __cregister unsigned long __ECR2206;
extern volatile __cregister unsigned long __ECR2207;
extern volatile __cregister unsigned long __ECR2208;
extern volatile __cregister unsigned long __ECR2209;
extern volatile __cregister unsigned long __ECR2210;
extern volatile __cregister unsigned long __ECR2211;
extern volatile __cregister unsigned long __ECR2212;
extern volatile __cregister unsigned long __ECR2213;
extern volatile __cregister unsigned long __ECR2214;
extern volatile __cregister unsigned long __ECR2215;
extern volatile __cregister unsigned long __ECR2216;
extern volatile __cregister unsigned long __ECR2217;
extern volatile __cregister unsigned long __ECR2218;
extern volatile __cregister unsigned long __ECR2219;
extern volatile __cregister unsigned long __ECR2220;
extern volatile __cregister unsigned long __ECR2221;
extern volatile __cregister unsigned long __ECR2222;
extern volatile __cregister unsigned long __ECR2223;
extern volatile __cregister unsigned long __ECR2224;
extern volatile __cregister unsigned long __ECR2225;
extern volatile __cregister unsigned long __ECR2226;
extern volatile __cregister unsigned long __ECR2227;
extern volatile __cregister unsigned long __ECR2228;
extern volatile __cregister unsigned long __ECR2229;
extern volatile __cregister unsigned long __ECR2230;
extern volatile __cregister unsigned long __ECR2231;
extern volatile __cregister unsigned long __ECR2232;
extern volatile __cregister unsigned long __ECR2233;
extern volatile __cregister unsigned long __ECR2234;
extern volatile __cregister unsigned long __ECR2235;
extern volatile __cregister unsigned long __ECR2236;
extern volatile __cregister unsigned long __ECR2237;
extern volatile __cregister unsigned long __ECR2238;
extern volatile __cregister unsigned long __ECR2239;
extern volatile __cregister unsigned long __ECR2240;
extern volatile __cregister unsigned long __ECR2241;
extern volatile __cregister unsigned long __ECR2242;
extern volatile __cregister unsigned long __ECR2243;
extern volatile __cregister unsigned long __ECR2244;
extern volatile __cregister unsigned long __ECR2245;
extern volatile __cregister unsigned long __ECR2246;
extern volatile __cregister unsigned long __ECR2247;
extern volatile __cregister unsigned long __ECR2248;
extern volatile __cregister unsigned long __ECR2249;
extern volatile __cregister unsigned long __ECR2250;
extern volatile __cregister unsigned long __ECR2251;
extern volatile __cregister unsigned long __ECR2252;
extern volatile __cregister unsigned long __ECR2253;
extern volatile __cregister unsigned long __ECR2254;
extern volatile __cregister unsigned long __ECR2255;
extern volatile __cregister unsigned long __ECR2256;
extern volatile __cregister unsigned long __ECR2257;
extern volatile __cregister unsigned long __ECR2258;
extern volatile __cregister unsigned long __ECR2259;
extern volatile __cregister unsigned long __ECR2260;
extern volatile __cregister unsigned long __ECR2261;
extern volatile __cregister unsigned long __ECR2262;
extern volatile __cregister unsigned long __ECR2263;
extern volatile __cregister unsigned long __ECR2264;
extern volatile __cregister unsigned long __ECR2265;
extern volatile __cregister unsigned long __ECR2266;
extern volatile __cregister unsigned long __ECR2267;
extern volatile __cregister unsigned long __ECR2268;
extern volatile __cregister unsigned long __ECR2269;
extern volatile __cregister unsigned long __ECR2270;
extern volatile __cregister unsigned long __ECR2271;
extern volatile __cregister unsigned long __ECR2272;
extern volatile __cregister unsigned long __ECR2273;
extern volatile __cregister unsigned long __ECR2274;
extern volatile __cregister unsigned long __ECR2275;
extern volatile __cregister unsigned long __ECR2276;
extern volatile __cregister unsigned long __ECR2277;
extern volatile __cregister unsigned long __ECR2278;
extern volatile __cregister unsigned long __ECR2279;
extern volatile __cregister unsigned long __ECR2280;
extern volatile __cregister unsigned long __ECR2281;
extern volatile __cregister unsigned long __ECR2282;
extern volatile __cregister unsigned long __ECR2283;
extern volatile __cregister unsigned long __ECR2284;
extern volatile __cregister unsigned long __ECR2285;
extern volatile __cregister unsigned long __ECR2286;
extern volatile __cregister unsigned long __ECR2287;
extern volatile __cregister unsigned long __ECR2288;
extern volatile __cregister unsigned long __ECR2289;
extern volatile __cregister unsigned long __ECR2290;
extern volatile __cregister unsigned long __ECR2291;
extern volatile __cregister unsigned long __ECR2292;
extern volatile __cregister unsigned long __ECR2293;
extern volatile __cregister unsigned long __ECR2294;
extern volatile __cregister unsigned long __ECR2295;
extern volatile __cregister unsigned long __ECR2296;
extern volatile __cregister unsigned long __ECR2297;
extern volatile __cregister unsigned long __ECR2298;
extern volatile __cregister unsigned long __ECR2299;
extern volatile __cregister unsigned long __ECR2300;
extern volatile __cregister unsigned long __ECR2301;
extern volatile __cregister unsigned long __ECR2302;
extern volatile __cregister unsigned long __ECR2303;
extern volatile __cregister unsigned long __ECR2304;

/******************************************************************************/
/* ECR: AET_ID                                                                */
/* DESCRIPTION: AET ID                                                        */
/* INDEX RANGE: [0,0] (not indexed)                                           */
/* GENERAL RESET VALUE: 0x62000100                                            */
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
#define __ECR_AET_ID __ECR2304

extern volatile __cregister unsigned long __ECR2305;

/******************************************************************************/
/* ECR: AET_OWN                                                               */
/* DESCRIPTION: AET Ownership Register                                        */
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
#define __ECR_AET_OWN __ECR2305

extern volatile __cregister unsigned long __ECR2306;

/******************************************************************************/
/* ECR: AET_STAT                                                              */
/* DESCRIPTION: AET Status Register                                           */
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
#define __ECR_AET_STAT __ECR2306

extern volatile __cregister unsigned long __ECR2307;
extern volatile __cregister unsigned long __ECR2308;

/******************************************************************************/
/* ECR: AET_EVT                                                               */
/* DESCRIPTION: AET Event Register                                            */
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
#define __ECR_AET_EVT __ECR2308

extern volatile __cregister unsigned long __ECR2309;

/******************************************************************************/
/* ECR: AET_PC0                                                               */
/* DESCRIPTION: AET PC0 Register                                              */
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
#define __ECR_AET_PC0 __ECR2309

extern volatile __cregister unsigned long __ECR2310;

/******************************************************************************/
/* ECR: AET_PC1                                                               */
/* DESCRIPTION: AET PC1 Register                                              */
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
#define __ECR_AET_PC1 __ECR2310

extern volatile __cregister unsigned long __ECR2311;
extern volatile __cregister unsigned long __ECR2312;

/******************************************************************************/
/* ECR: AET_IAR_ADD                                                           */
/* DESCRIPTION: AET Indirect ADDR Register                                    */
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
#define __ECR_AET_IAR_ADD __ECR2312

extern volatile __cregister unsigned long __ECR2313;

/******************************************************************************/
/* ECR: AET_IAR_DAT                                                           */
/* DESCRIPTION: AET Indirect Data Register                                    */
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
#define __ECR_AET_IAR_DAT __ECR2313

extern volatile __cregister unsigned long __ECR2314;
extern volatile __cregister unsigned long __ECR2315;
extern volatile __cregister unsigned long __ECR2316;
extern volatile __cregister unsigned long __ECR2317;
extern volatile __cregister unsigned long __ECR2318;
extern volatile __cregister unsigned long __ECR2319;
extern volatile __cregister unsigned long __ECR2320;
extern volatile __cregister unsigned long __ECR2321;
extern volatile __cregister unsigned long __ECR2322;
extern volatile __cregister unsigned long __ECR2323;
extern volatile __cregister unsigned long __ECR2324;
extern volatile __cregister unsigned long __ECR2325;
extern volatile __cregister unsigned long __ECR2326;
extern volatile __cregister unsigned long __ECR2327;
extern volatile __cregister unsigned long __ECR2328;
extern volatile __cregister unsigned long __ECR2329;
extern volatile __cregister unsigned long __ECR2330;
extern volatile __cregister unsigned long __ECR2331;
extern volatile __cregister unsigned long __ECR2332;
extern volatile __cregister unsigned long __ECR2333;
extern volatile __cregister unsigned long __ECR2334;
extern volatile __cregister unsigned long __ECR2335;
extern volatile __cregister unsigned long __ECR2336;
extern volatile __cregister unsigned long __ECR2337;
extern volatile __cregister unsigned long __ECR2338;
extern volatile __cregister unsigned long __ECR2339;
extern volatile __cregister unsigned long __ECR2340;
extern volatile __cregister unsigned long __ECR2341;
extern volatile __cregister unsigned long __ECR2342;
extern volatile __cregister unsigned long __ECR2343;
extern volatile __cregister unsigned long __ECR2344;
extern volatile __cregister unsigned long __ECR2345;
extern volatile __cregister unsigned long __ECR2346;
extern volatile __cregister unsigned long __ECR2347;
extern volatile __cregister unsigned long __ECR2348;
extern volatile __cregister unsigned long __ECR2349;
extern volatile __cregister unsigned long __ECR2350;
extern volatile __cregister unsigned long __ECR2351;
extern volatile __cregister unsigned long __ECR2352;
extern volatile __cregister unsigned long __ECR2353;
extern volatile __cregister unsigned long __ECR2354;
extern volatile __cregister unsigned long __ECR2355;
extern volatile __cregister unsigned long __ECR2356;
extern volatile __cregister unsigned long __ECR2357;
extern volatile __cregister unsigned long __ECR2358;
extern volatile __cregister unsigned long __ECR2359;
extern volatile __cregister unsigned long __ECR2360;
extern volatile __cregister unsigned long __ECR2361;
extern volatile __cregister unsigned long __ECR2362;
extern volatile __cregister unsigned long __ECR2363;
extern volatile __cregister unsigned long __ECR2364;
extern volatile __cregister unsigned long __ECR2365;
extern volatile __cregister unsigned long __ECR2366;
extern volatile __cregister unsigned long __ECR2367;
extern volatile __cregister unsigned long __ECR2368;
extern volatile __cregister unsigned long __ECR2369;
extern volatile __cregister unsigned long __ECR2370;
extern volatile __cregister unsigned long __ECR2371;
extern volatile __cregister unsigned long __ECR2372;
extern volatile __cregister unsigned long __ECR2373;
extern volatile __cregister unsigned long __ECR2374;
extern volatile __cregister unsigned long __ECR2375;
extern volatile __cregister unsigned long __ECR2376;
extern volatile __cregister unsigned long __ECR2377;
extern volatile __cregister unsigned long __ECR2378;
extern volatile __cregister unsigned long __ECR2379;
extern volatile __cregister unsigned long __ECR2380;
extern volatile __cregister unsigned long __ECR2381;
extern volatile __cregister unsigned long __ECR2382;
extern volatile __cregister unsigned long __ECR2383;
extern volatile __cregister unsigned long __ECR2384;
extern volatile __cregister unsigned long __ECR2385;
extern volatile __cregister unsigned long __ECR2386;
extern volatile __cregister unsigned long __ECR2387;
extern volatile __cregister unsigned long __ECR2388;
extern volatile __cregister unsigned long __ECR2389;
extern volatile __cregister unsigned long __ECR2390;
extern volatile __cregister unsigned long __ECR2391;
extern volatile __cregister unsigned long __ECR2392;
extern volatile __cregister unsigned long __ECR2393;
extern volatile __cregister unsigned long __ECR2394;
extern volatile __cregister unsigned long __ECR2395;
extern volatile __cregister unsigned long __ECR2396;
extern volatile __cregister unsigned long __ECR2397;
extern volatile __cregister unsigned long __ECR2398;
extern volatile __cregister unsigned long __ECR2399;
extern volatile __cregister unsigned long __ECR2400;
extern volatile __cregister unsigned long __ECR2401;
extern volatile __cregister unsigned long __ECR2402;
extern volatile __cregister unsigned long __ECR2403;
extern volatile __cregister unsigned long __ECR2404;
extern volatile __cregister unsigned long __ECR2405;
extern volatile __cregister unsigned long __ECR2406;
extern volatile __cregister unsigned long __ECR2407;
extern volatile __cregister unsigned long __ECR2408;
extern volatile __cregister unsigned long __ECR2409;
extern volatile __cregister unsigned long __ECR2410;
extern volatile __cregister unsigned long __ECR2411;
extern volatile __cregister unsigned long __ECR2412;
extern volatile __cregister unsigned long __ECR2413;
extern volatile __cregister unsigned long __ECR2414;
extern volatile __cregister unsigned long __ECR2415;
extern volatile __cregister unsigned long __ECR2416;
extern volatile __cregister unsigned long __ECR2417;
extern volatile __cregister unsigned long __ECR2418;
extern volatile __cregister unsigned long __ECR2419;
extern volatile __cregister unsigned long __ECR2420;
extern volatile __cregister unsigned long __ECR2421;
extern volatile __cregister unsigned long __ECR2422;
extern volatile __cregister unsigned long __ECR2423;
extern volatile __cregister unsigned long __ECR2424;
extern volatile __cregister unsigned long __ECR2425;
extern volatile __cregister unsigned long __ECR2426;
extern volatile __cregister unsigned long __ECR2427;
extern volatile __cregister unsigned long __ECR2428;
extern volatile __cregister unsigned long __ECR2429;
extern volatile __cregister unsigned long __ECR2430;
extern volatile __cregister unsigned long __ECR2431;
extern volatile __cregister unsigned long __ECR2432;
extern volatile __cregister unsigned long __ECR2433;
extern volatile __cregister unsigned long __ECR2434;
extern volatile __cregister unsigned long __ECR2435;
extern volatile __cregister unsigned long __ECR2436;
extern volatile __cregister unsigned long __ECR2437;
extern volatile __cregister unsigned long __ECR2438;
extern volatile __cregister unsigned long __ECR2439;
extern volatile __cregister unsigned long __ECR2440;
extern volatile __cregister unsigned long __ECR2441;
extern volatile __cregister unsigned long __ECR2442;
extern volatile __cregister unsigned long __ECR2443;
extern volatile __cregister unsigned long __ECR2444;
extern volatile __cregister unsigned long __ECR2445;
extern volatile __cregister unsigned long __ECR2446;
extern volatile __cregister unsigned long __ECR2447;
extern volatile __cregister unsigned long __ECR2448;
extern volatile __cregister unsigned long __ECR2449;
extern volatile __cregister unsigned long __ECR2450;
extern volatile __cregister unsigned long __ECR2451;
extern volatile __cregister unsigned long __ECR2452;
extern volatile __cregister unsigned long __ECR2453;
extern volatile __cregister unsigned long __ECR2454;
extern volatile __cregister unsigned long __ECR2455;
extern volatile __cregister unsigned long __ECR2456;
extern volatile __cregister unsigned long __ECR2457;
extern volatile __cregister unsigned long __ECR2458;
extern volatile __cregister unsigned long __ECR2459;
extern volatile __cregister unsigned long __ECR2460;
extern volatile __cregister unsigned long __ECR2461;
extern volatile __cregister unsigned long __ECR2462;
extern volatile __cregister unsigned long __ECR2463;
extern volatile __cregister unsigned long __ECR2464;
extern volatile __cregister unsigned long __ECR2465;
extern volatile __cregister unsigned long __ECR2466;
extern volatile __cregister unsigned long __ECR2467;
extern volatile __cregister unsigned long __ECR2468;
extern volatile __cregister unsigned long __ECR2469;
extern volatile __cregister unsigned long __ECR2470;
extern volatile __cregister unsigned long __ECR2471;
extern volatile __cregister unsigned long __ECR2472;
extern volatile __cregister unsigned long __ECR2473;
extern volatile __cregister unsigned long __ECR2474;
extern volatile __cregister unsigned long __ECR2475;
extern volatile __cregister unsigned long __ECR2476;
extern volatile __cregister unsigned long __ECR2477;
extern volatile __cregister unsigned long __ECR2478;
extern volatile __cregister unsigned long __ECR2479;
extern volatile __cregister unsigned long __ECR2480;
extern volatile __cregister unsigned long __ECR2481;
extern volatile __cregister unsigned long __ECR2482;
extern volatile __cregister unsigned long __ECR2483;
extern volatile __cregister unsigned long __ECR2484;
extern volatile __cregister unsigned long __ECR2485;
extern volatile __cregister unsigned long __ECR2486;
extern volatile __cregister unsigned long __ECR2487;
extern volatile __cregister unsigned long __ECR2488;
extern volatile __cregister unsigned long __ECR2489;
extern volatile __cregister unsigned long __ECR2490;
extern volatile __cregister unsigned long __ECR2491;
extern volatile __cregister unsigned long __ECR2492;
extern volatile __cregister unsigned long __ECR2493;
extern volatile __cregister unsigned long __ECR2494;
extern volatile __cregister unsigned long __ECR2495;
extern volatile __cregister unsigned long __ECR2496;
extern volatile __cregister unsigned long __ECR2497;
extern volatile __cregister unsigned long __ECR2498;
extern volatile __cregister unsigned long __ECR2499;
extern volatile __cregister unsigned long __ECR2500;
extern volatile __cregister unsigned long __ECR2501;
extern volatile __cregister unsigned long __ECR2502;
extern volatile __cregister unsigned long __ECR2503;
extern volatile __cregister unsigned long __ECR2504;
extern volatile __cregister unsigned long __ECR2505;
extern volatile __cregister unsigned long __ECR2506;
extern volatile __cregister unsigned long __ECR2507;
extern volatile __cregister unsigned long __ECR2508;
extern volatile __cregister unsigned long __ECR2509;
extern volatile __cregister unsigned long __ECR2510;
extern volatile __cregister unsigned long __ECR2511;
extern volatile __cregister unsigned long __ECR2512;
extern volatile __cregister unsigned long __ECR2513;
extern volatile __cregister unsigned long __ECR2514;
extern volatile __cregister unsigned long __ECR2515;
extern volatile __cregister unsigned long __ECR2516;
extern volatile __cregister unsigned long __ECR2517;
extern volatile __cregister unsigned long __ECR2518;
extern volatile __cregister unsigned long __ECR2519;
extern volatile __cregister unsigned long __ECR2520;
extern volatile __cregister unsigned long __ECR2521;
extern volatile __cregister unsigned long __ECR2522;
extern volatile __cregister unsigned long __ECR2523;
extern volatile __cregister unsigned long __ECR2524;
extern volatile __cregister unsigned long __ECR2525;
extern volatile __cregister unsigned long __ECR2526;
extern volatile __cregister unsigned long __ECR2527;
extern volatile __cregister unsigned long __ECR2528;
extern volatile __cregister unsigned long __ECR2529;
extern volatile __cregister unsigned long __ECR2530;
extern volatile __cregister unsigned long __ECR2531;
extern volatile __cregister unsigned long __ECR2532;
extern volatile __cregister unsigned long __ECR2533;
extern volatile __cregister unsigned long __ECR2534;
extern volatile __cregister unsigned long __ECR2535;
extern volatile __cregister unsigned long __ECR2536;
extern volatile __cregister unsigned long __ECR2537;
extern volatile __cregister unsigned long __ECR2538;
extern volatile __cregister unsigned long __ECR2539;
extern volatile __cregister unsigned long __ECR2540;
extern volatile __cregister unsigned long __ECR2541;
extern volatile __cregister unsigned long __ECR2542;
extern volatile __cregister unsigned long __ECR2543;
extern volatile __cregister unsigned long __ECR2544;
extern volatile __cregister unsigned long __ECR2545;
extern volatile __cregister unsigned long __ECR2546;
extern volatile __cregister unsigned long __ECR2547;
extern volatile __cregister unsigned long __ECR2548;
extern volatile __cregister unsigned long __ECR2549;
extern volatile __cregister unsigned long __ECR2550;
extern volatile __cregister unsigned long __ECR2551;
extern volatile __cregister unsigned long __ECR2552;
extern volatile __cregister unsigned long __ECR2553;
extern volatile __cregister unsigned long __ECR2554;
extern volatile __cregister unsigned long __ECR2555;
extern volatile __cregister unsigned long __ECR2556;
extern volatile __cregister unsigned long __ECR2557;
extern volatile __cregister unsigned long __ECR2558;
extern volatile __cregister unsigned long __ECR2559;
extern volatile __cregister unsigned long __ECR2560;
extern volatile __cregister unsigned long __ECR2561;
extern volatile __cregister unsigned long __ECR2562;
extern volatile __cregister unsigned long __ECR2563;
extern volatile __cregister unsigned long __ECR2564;
extern volatile __cregister unsigned long __ECR2565;
extern volatile __cregister unsigned long __ECR2566;
extern volatile __cregister unsigned long __ECR2567;
extern volatile __cregister unsigned long __ECR2568;
extern volatile __cregister unsigned long __ECR2569;
extern volatile __cregister unsigned long __ECR2570;
extern volatile __cregister unsigned long __ECR2571;
extern volatile __cregister unsigned long __ECR2572;
extern volatile __cregister unsigned long __ECR2573;
extern volatile __cregister unsigned long __ECR2574;
extern volatile __cregister unsigned long __ECR2575;
extern volatile __cregister unsigned long __ECR2576;
extern volatile __cregister unsigned long __ECR2577;
extern volatile __cregister unsigned long __ECR2578;
extern volatile __cregister unsigned long __ECR2579;
extern volatile __cregister unsigned long __ECR2580;
extern volatile __cregister unsigned long __ECR2581;
extern volatile __cregister unsigned long __ECR2582;
extern volatile __cregister unsigned long __ECR2583;
extern volatile __cregister unsigned long __ECR2584;
extern volatile __cregister unsigned long __ECR2585;
extern volatile __cregister unsigned long __ECR2586;
extern volatile __cregister unsigned long __ECR2587;
extern volatile __cregister unsigned long __ECR2588;
extern volatile __cregister unsigned long __ECR2589;
extern volatile __cregister unsigned long __ECR2590;
extern volatile __cregister unsigned long __ECR2591;
extern volatile __cregister unsigned long __ECR2592;
extern volatile __cregister unsigned long __ECR2593;
extern volatile __cregister unsigned long __ECR2594;
extern volatile __cregister unsigned long __ECR2595;
extern volatile __cregister unsigned long __ECR2596;
extern volatile __cregister unsigned long __ECR2597;
extern volatile __cregister unsigned long __ECR2598;
extern volatile __cregister unsigned long __ECR2599;
extern volatile __cregister unsigned long __ECR2600;
extern volatile __cregister unsigned long __ECR2601;
extern volatile __cregister unsigned long __ECR2602;
extern volatile __cregister unsigned long __ECR2603;
extern volatile __cregister unsigned long __ECR2604;
extern volatile __cregister unsigned long __ECR2605;
extern volatile __cregister unsigned long __ECR2606;
extern volatile __cregister unsigned long __ECR2607;
extern volatile __cregister unsigned long __ECR2608;
extern volatile __cregister unsigned long __ECR2609;
extern volatile __cregister unsigned long __ECR2610;
extern volatile __cregister unsigned long __ECR2611;
extern volatile __cregister unsigned long __ECR2612;
extern volatile __cregister unsigned long __ECR2613;
extern volatile __cregister unsigned long __ECR2614;
extern volatile __cregister unsigned long __ECR2615;
extern volatile __cregister unsigned long __ECR2616;
extern volatile __cregister unsigned long __ECR2617;
extern volatile __cregister unsigned long __ECR2618;
extern volatile __cregister unsigned long __ECR2619;
extern volatile __cregister unsigned long __ECR2620;
extern volatile __cregister unsigned long __ECR2621;
extern volatile __cregister unsigned long __ECR2622;
extern volatile __cregister unsigned long __ECR2623;
extern volatile __cregister unsigned long __ECR2624;
extern volatile __cregister unsigned long __ECR2625;
extern volatile __cregister unsigned long __ECR2626;
extern volatile __cregister unsigned long __ECR2627;
extern volatile __cregister unsigned long __ECR2628;
extern volatile __cregister unsigned long __ECR2629;
extern volatile __cregister unsigned long __ECR2630;
extern volatile __cregister unsigned long __ECR2631;
extern volatile __cregister unsigned long __ECR2632;
extern volatile __cregister unsigned long __ECR2633;
extern volatile __cregister unsigned long __ECR2634;
extern volatile __cregister unsigned long __ECR2635;
extern volatile __cregister unsigned long __ECR2636;
extern volatile __cregister unsigned long __ECR2637;
extern volatile __cregister unsigned long __ECR2638;
extern volatile __cregister unsigned long __ECR2639;
extern volatile __cregister unsigned long __ECR2640;
extern volatile __cregister unsigned long __ECR2641;
extern volatile __cregister unsigned long __ECR2642;
extern volatile __cregister unsigned long __ECR2643;
extern volatile __cregister unsigned long __ECR2644;
extern volatile __cregister unsigned long __ECR2645;
extern volatile __cregister unsigned long __ECR2646;
extern volatile __cregister unsigned long __ECR2647;
extern volatile __cregister unsigned long __ECR2648;
extern volatile __cregister unsigned long __ECR2649;
extern volatile __cregister unsigned long __ECR2650;
extern volatile __cregister unsigned long __ECR2651;
extern volatile __cregister unsigned long __ECR2652;
extern volatile __cregister unsigned long __ECR2653;
extern volatile __cregister unsigned long __ECR2654;
extern volatile __cregister unsigned long __ECR2655;
extern volatile __cregister unsigned long __ECR2656;
extern volatile __cregister unsigned long __ECR2657;
extern volatile __cregister unsigned long __ECR2658;
extern volatile __cregister unsigned long __ECR2659;
extern volatile __cregister unsigned long __ECR2660;
extern volatile __cregister unsigned long __ECR2661;
extern volatile __cregister unsigned long __ECR2662;
extern volatile __cregister unsigned long __ECR2663;
extern volatile __cregister unsigned long __ECR2664;
extern volatile __cregister unsigned long __ECR2665;
extern volatile __cregister unsigned long __ECR2666;
extern volatile __cregister unsigned long __ECR2667;
extern volatile __cregister unsigned long __ECR2668;
extern volatile __cregister unsigned long __ECR2669;
extern volatile __cregister unsigned long __ECR2670;
extern volatile __cregister unsigned long __ECR2671;
extern volatile __cregister unsigned long __ECR2672;
extern volatile __cregister unsigned long __ECR2673;
extern volatile __cregister unsigned long __ECR2674;
extern volatile __cregister unsigned long __ECR2675;
extern volatile __cregister unsigned long __ECR2676;
extern volatile __cregister unsigned long __ECR2677;
extern volatile __cregister unsigned long __ECR2678;
extern volatile __cregister unsigned long __ECR2679;
extern volatile __cregister unsigned long __ECR2680;
extern volatile __cregister unsigned long __ECR2681;
extern volatile __cregister unsigned long __ECR2682;
extern volatile __cregister unsigned long __ECR2683;
extern volatile __cregister unsigned long __ECR2684;
extern volatile __cregister unsigned long __ECR2685;
extern volatile __cregister unsigned long __ECR2686;
extern volatile __cregister unsigned long __ECR2687;
extern volatile __cregister unsigned long __ECR2688;
extern volatile __cregister unsigned long __ECR2689;
extern volatile __cregister unsigned long __ECR2690;
extern volatile __cregister unsigned long __ECR2691;
extern volatile __cregister unsigned long __ECR2692;
extern volatile __cregister unsigned long __ECR2693;
extern volatile __cregister unsigned long __ECR2694;
extern volatile __cregister unsigned long __ECR2695;
extern volatile __cregister unsigned long __ECR2696;
extern volatile __cregister unsigned long __ECR2697;
extern volatile __cregister unsigned long __ECR2698;
extern volatile __cregister unsigned long __ECR2699;
extern volatile __cregister unsigned long __ECR2700;
extern volatile __cregister unsigned long __ECR2701;
extern volatile __cregister unsigned long __ECR2702;
extern volatile __cregister unsigned long __ECR2703;
extern volatile __cregister unsigned long __ECR2704;
extern volatile __cregister unsigned long __ECR2705;
extern volatile __cregister unsigned long __ECR2706;
extern volatile __cregister unsigned long __ECR2707;
extern volatile __cregister unsigned long __ECR2708;
extern volatile __cregister unsigned long __ECR2709;
extern volatile __cregister unsigned long __ECR2710;
extern volatile __cregister unsigned long __ECR2711;
extern volatile __cregister unsigned long __ECR2712;
extern volatile __cregister unsigned long __ECR2713;
extern volatile __cregister unsigned long __ECR2714;
extern volatile __cregister unsigned long __ECR2715;
extern volatile __cregister unsigned long __ECR2716;
extern volatile __cregister unsigned long __ECR2717;
extern volatile __cregister unsigned long __ECR2718;
extern volatile __cregister unsigned long __ECR2719;
extern volatile __cregister unsigned long __ECR2720;
extern volatile __cregister unsigned long __ECR2721;
extern volatile __cregister unsigned long __ECR2722;
extern volatile __cregister unsigned long __ECR2723;
extern volatile __cregister unsigned long __ECR2724;
extern volatile __cregister unsigned long __ECR2725;
extern volatile __cregister unsigned long __ECR2726;
extern volatile __cregister unsigned long __ECR2727;
extern volatile __cregister unsigned long __ECR2728;
extern volatile __cregister unsigned long __ECR2729;
extern volatile __cregister unsigned long __ECR2730;
extern volatile __cregister unsigned long __ECR2731;
extern volatile __cregister unsigned long __ECR2732;
extern volatile __cregister unsigned long __ECR2733;
extern volatile __cregister unsigned long __ECR2734;
extern volatile __cregister unsigned long __ECR2735;
extern volatile __cregister unsigned long __ECR2736;
extern volatile __cregister unsigned long __ECR2737;
extern volatile __cregister unsigned long __ECR2738;
extern volatile __cregister unsigned long __ECR2739;
extern volatile __cregister unsigned long __ECR2740;
extern volatile __cregister unsigned long __ECR2741;
extern volatile __cregister unsigned long __ECR2742;
extern volatile __cregister unsigned long __ECR2743;
extern volatile __cregister unsigned long __ECR2744;
extern volatile __cregister unsigned long __ECR2745;
extern volatile __cregister unsigned long __ECR2746;
extern volatile __cregister unsigned long __ECR2747;
extern volatile __cregister unsigned long __ECR2748;
extern volatile __cregister unsigned long __ECR2749;
extern volatile __cregister unsigned long __ECR2750;
extern volatile __cregister unsigned long __ECR2751;
extern volatile __cregister unsigned long __ECR2752;
extern volatile __cregister unsigned long __ECR2753;
extern volatile __cregister unsigned long __ECR2754;
extern volatile __cregister unsigned long __ECR2755;
extern volatile __cregister unsigned long __ECR2756;
extern volatile __cregister unsigned long __ECR2757;
extern volatile __cregister unsigned long __ECR2758;
extern volatile __cregister unsigned long __ECR2759;
extern volatile __cregister unsigned long __ECR2760;
extern volatile __cregister unsigned long __ECR2761;
extern volatile __cregister unsigned long __ECR2762;
extern volatile __cregister unsigned long __ECR2763;
extern volatile __cregister unsigned long __ECR2764;
extern volatile __cregister unsigned long __ECR2765;
extern volatile __cregister unsigned long __ECR2766;
extern volatile __cregister unsigned long __ECR2767;
extern volatile __cregister unsigned long __ECR2768;
extern volatile __cregister unsigned long __ECR2769;
extern volatile __cregister unsigned long __ECR2770;
extern volatile __cregister unsigned long __ECR2771;
extern volatile __cregister unsigned long __ECR2772;
extern volatile __cregister unsigned long __ECR2773;
extern volatile __cregister unsigned long __ECR2774;
extern volatile __cregister unsigned long __ECR2775;
extern volatile __cregister unsigned long __ECR2776;
extern volatile __cregister unsigned long __ECR2777;
extern volatile __cregister unsigned long __ECR2778;
extern volatile __cregister unsigned long __ECR2779;
extern volatile __cregister unsigned long __ECR2780;
extern volatile __cregister unsigned long __ECR2781;
extern volatile __cregister unsigned long __ECR2782;
extern volatile __cregister unsigned long __ECR2783;
extern volatile __cregister unsigned long __ECR2784;
extern volatile __cregister unsigned long __ECR2785;
extern volatile __cregister unsigned long __ECR2786;
extern volatile __cregister unsigned long __ECR2787;
extern volatile __cregister unsigned long __ECR2788;
extern volatile __cregister unsigned long __ECR2789;
extern volatile __cregister unsigned long __ECR2790;
extern volatile __cregister unsigned long __ECR2791;
extern volatile __cregister unsigned long __ECR2792;
extern volatile __cregister unsigned long __ECR2793;
extern volatile __cregister unsigned long __ECR2794;
extern volatile __cregister unsigned long __ECR2795;
extern volatile __cregister unsigned long __ECR2796;
extern volatile __cregister unsigned long __ECR2797;
extern volatile __cregister unsigned long __ECR2798;
extern volatile __cregister unsigned long __ECR2799;
extern volatile __cregister unsigned long __ECR2800;
extern volatile __cregister unsigned long __ECR2801;
extern volatile __cregister unsigned long __ECR2802;
extern volatile __cregister unsigned long __ECR2803;
extern volatile __cregister unsigned long __ECR2804;
extern volatile __cregister unsigned long __ECR2805;
extern volatile __cregister unsigned long __ECR2806;
extern volatile __cregister unsigned long __ECR2807;
extern volatile __cregister unsigned long __ECR2808;
extern volatile __cregister unsigned long __ECR2809;
extern volatile __cregister unsigned long __ECR2810;
extern volatile __cregister unsigned long __ECR2811;
extern volatile __cregister unsigned long __ECR2812;
extern volatile __cregister unsigned long __ECR2813;
extern volatile __cregister unsigned long __ECR2814;
extern volatile __cregister unsigned long __ECR2815;
extern volatile __cregister unsigned long __ECR2816;
extern volatile __cregister unsigned long __ECR2817;
extern volatile __cregister unsigned long __ECR2818;
extern volatile __cregister unsigned long __ECR2819;
extern volatile __cregister unsigned long __ECR2820;
extern volatile __cregister unsigned long __ECR2821;
extern volatile __cregister unsigned long __ECR2822;
extern volatile __cregister unsigned long __ECR2823;
extern volatile __cregister unsigned long __ECR2824;
extern volatile __cregister unsigned long __ECR2825;
extern volatile __cregister unsigned long __ECR2826;
extern volatile __cregister unsigned long __ECR2827;
extern volatile __cregister unsigned long __ECR2828;
extern volatile __cregister unsigned long __ECR2829;
extern volatile __cregister unsigned long __ECR2830;
extern volatile __cregister unsigned long __ECR2831;
extern volatile __cregister unsigned long __ECR2832;
extern volatile __cregister unsigned long __ECR2833;
extern volatile __cregister unsigned long __ECR2834;
extern volatile __cregister unsigned long __ECR2835;
extern volatile __cregister unsigned long __ECR2836;
extern volatile __cregister unsigned long __ECR2837;
extern volatile __cregister unsigned long __ECR2838;
extern volatile __cregister unsigned long __ECR2839;
extern volatile __cregister unsigned long __ECR2840;
extern volatile __cregister unsigned long __ECR2841;
extern volatile __cregister unsigned long __ECR2842;
extern volatile __cregister unsigned long __ECR2843;
extern volatile __cregister unsigned long __ECR2844;
extern volatile __cregister unsigned long __ECR2845;
extern volatile __cregister unsigned long __ECR2846;
extern volatile __cregister unsigned long __ECR2847;
extern volatile __cregister unsigned long __ECR2848;
extern volatile __cregister unsigned long __ECR2849;
extern volatile __cregister unsigned long __ECR2850;
extern volatile __cregister unsigned long __ECR2851;
extern volatile __cregister unsigned long __ECR2852;
extern volatile __cregister unsigned long __ECR2853;
extern volatile __cregister unsigned long __ECR2854;
extern volatile __cregister unsigned long __ECR2855;
extern volatile __cregister unsigned long __ECR2856;
extern volatile __cregister unsigned long __ECR2857;
extern volatile __cregister unsigned long __ECR2858;
extern volatile __cregister unsigned long __ECR2859;
extern volatile __cregister unsigned long __ECR2860;
extern volatile __cregister unsigned long __ECR2861;
extern volatile __cregister unsigned long __ECR2862;
extern volatile __cregister unsigned long __ECR2863;
extern volatile __cregister unsigned long __ECR2864;
extern volatile __cregister unsigned long __ECR2865;
extern volatile __cregister unsigned long __ECR2866;
extern volatile __cregister unsigned long __ECR2867;
extern volatile __cregister unsigned long __ECR2868;
extern volatile __cregister unsigned long __ECR2869;
extern volatile __cregister unsigned long __ECR2870;
extern volatile __cregister unsigned long __ECR2871;
extern volatile __cregister unsigned long __ECR2872;
extern volatile __cregister unsigned long __ECR2873;
extern volatile __cregister unsigned long __ECR2874;
extern volatile __cregister unsigned long __ECR2875;
extern volatile __cregister unsigned long __ECR2876;
extern volatile __cregister unsigned long __ECR2877;
extern volatile __cregister unsigned long __ECR2878;
extern volatile __cregister unsigned long __ECR2879;
extern volatile __cregister unsigned long __ECR2880;
extern volatile __cregister unsigned long __ECR2881;
extern volatile __cregister unsigned long __ECR2882;
extern volatile __cregister unsigned long __ECR2883;
extern volatile __cregister unsigned long __ECR2884;
extern volatile __cregister unsigned long __ECR2885;
extern volatile __cregister unsigned long __ECR2886;
extern volatile __cregister unsigned long __ECR2887;
extern volatile __cregister unsigned long __ECR2888;
extern volatile __cregister unsigned long __ECR2889;
extern volatile __cregister unsigned long __ECR2890;
extern volatile __cregister unsigned long __ECR2891;
extern volatile __cregister unsigned long __ECR2892;
extern volatile __cregister unsigned long __ECR2893;
extern volatile __cregister unsigned long __ECR2894;
extern volatile __cregister unsigned long __ECR2895;
extern volatile __cregister unsigned long __ECR2896;
extern volatile __cregister unsigned long __ECR2897;
extern volatile __cregister unsigned long __ECR2898;
extern volatile __cregister unsigned long __ECR2899;
extern volatile __cregister unsigned long __ECR2900;
extern volatile __cregister unsigned long __ECR2901;
extern volatile __cregister unsigned long __ECR2902;
extern volatile __cregister unsigned long __ECR2903;
extern volatile __cregister unsigned long __ECR2904;
extern volatile __cregister unsigned long __ECR2905;
extern volatile __cregister unsigned long __ECR2906;
extern volatile __cregister unsigned long __ECR2907;
extern volatile __cregister unsigned long __ECR2908;
extern volatile __cregister unsigned long __ECR2909;
extern volatile __cregister unsigned long __ECR2910;
extern volatile __cregister unsigned long __ECR2911;
extern volatile __cregister unsigned long __ECR2912;
extern volatile __cregister unsigned long __ECR2913;
extern volatile __cregister unsigned long __ECR2914;
extern volatile __cregister unsigned long __ECR2915;
extern volatile __cregister unsigned long __ECR2916;
extern volatile __cregister unsigned long __ECR2917;
extern volatile __cregister unsigned long __ECR2918;
extern volatile __cregister unsigned long __ECR2919;
extern volatile __cregister unsigned long __ECR2920;
extern volatile __cregister unsigned long __ECR2921;
extern volatile __cregister unsigned long __ECR2922;
extern volatile __cregister unsigned long __ECR2923;
extern volatile __cregister unsigned long __ECR2924;
extern volatile __cregister unsigned long __ECR2925;
extern volatile __cregister unsigned long __ECR2926;
extern volatile __cregister unsigned long __ECR2927;
extern volatile __cregister unsigned long __ECR2928;
extern volatile __cregister unsigned long __ECR2929;
extern volatile __cregister unsigned long __ECR2930;
extern volatile __cregister unsigned long __ECR2931;
extern volatile __cregister unsigned long __ECR2932;
extern volatile __cregister unsigned long __ECR2933;
extern volatile __cregister unsigned long __ECR2934;
extern volatile __cregister unsigned long __ECR2935;
extern volatile __cregister unsigned long __ECR2936;
extern volatile __cregister unsigned long __ECR2937;
extern volatile __cregister unsigned long __ECR2938;
extern volatile __cregister unsigned long __ECR2939;
extern volatile __cregister unsigned long __ECR2940;
extern volatile __cregister unsigned long __ECR2941;
extern volatile __cregister unsigned long __ECR2942;
extern volatile __cregister unsigned long __ECR2943;
extern volatile __cregister unsigned long __ECR2944;
extern volatile __cregister unsigned long __ECR2945;
extern volatile __cregister unsigned long __ECR2946;
extern volatile __cregister unsigned long __ECR2947;
extern volatile __cregister unsigned long __ECR2948;
extern volatile __cregister unsigned long __ECR2949;
extern volatile __cregister unsigned long __ECR2950;
extern volatile __cregister unsigned long __ECR2951;
extern volatile __cregister unsigned long __ECR2952;
extern volatile __cregister unsigned long __ECR2953;
extern volatile __cregister unsigned long __ECR2954;
extern volatile __cregister unsigned long __ECR2955;
extern volatile __cregister unsigned long __ECR2956;
extern volatile __cregister unsigned long __ECR2957;
extern volatile __cregister unsigned long __ECR2958;
extern volatile __cregister unsigned long __ECR2959;
extern volatile __cregister unsigned long __ECR2960;
extern volatile __cregister unsigned long __ECR2961;
extern volatile __cregister unsigned long __ECR2962;
extern volatile __cregister unsigned long __ECR2963;
extern volatile __cregister unsigned long __ECR2964;
extern volatile __cregister unsigned long __ECR2965;
extern volatile __cregister unsigned long __ECR2966;
extern volatile __cregister unsigned long __ECR2967;
extern volatile __cregister unsigned long __ECR2968;
extern volatile __cregister unsigned long __ECR2969;
extern volatile __cregister unsigned long __ECR2970;
extern volatile __cregister unsigned long __ECR2971;
extern volatile __cregister unsigned long __ECR2972;
extern volatile __cregister unsigned long __ECR2973;
extern volatile __cregister unsigned long __ECR2974;
extern volatile __cregister unsigned long __ECR2975;
extern volatile __cregister unsigned long __ECR2976;
extern volatile __cregister unsigned long __ECR2977;
extern volatile __cregister unsigned long __ECR2978;
extern volatile __cregister unsigned long __ECR2979;
extern volatile __cregister unsigned long __ECR2980;
extern volatile __cregister unsigned long __ECR2981;
extern volatile __cregister unsigned long __ECR2982;
extern volatile __cregister unsigned long __ECR2983;
extern volatile __cregister unsigned long __ECR2984;
extern volatile __cregister unsigned long __ECR2985;
extern volatile __cregister unsigned long __ECR2986;
extern volatile __cregister unsigned long __ECR2987;
extern volatile __cregister unsigned long __ECR2988;
extern volatile __cregister unsigned long __ECR2989;
extern volatile __cregister unsigned long __ECR2990;
extern volatile __cregister unsigned long __ECR2991;
extern volatile __cregister unsigned long __ECR2992;
extern volatile __cregister unsigned long __ECR2993;
extern volatile __cregister unsigned long __ECR2994;
extern volatile __cregister unsigned long __ECR2995;
extern volatile __cregister unsigned long __ECR2996;
extern volatile __cregister unsigned long __ECR2997;
extern volatile __cregister unsigned long __ECR2998;
extern volatile __cregister unsigned long __ECR2999;
extern volatile __cregister unsigned long __ECR3000;
extern volatile __cregister unsigned long __ECR3001;
extern volatile __cregister unsigned long __ECR3002;
extern volatile __cregister unsigned long __ECR3003;
extern volatile __cregister unsigned long __ECR3004;
extern volatile __cregister unsigned long __ECR3005;
extern volatile __cregister unsigned long __ECR3006;
extern volatile __cregister unsigned long __ECR3007;
extern volatile __cregister unsigned long __ECR3008;
extern volatile __cregister unsigned long __ECR3009;
extern volatile __cregister unsigned long __ECR3010;
extern volatile __cregister unsigned long __ECR3011;
extern volatile __cregister unsigned long __ECR3012;
extern volatile __cregister unsigned long __ECR3013;
extern volatile __cregister unsigned long __ECR3014;
extern volatile __cregister unsigned long __ECR3015;
extern volatile __cregister unsigned long __ECR3016;
extern volatile __cregister unsigned long __ECR3017;
extern volatile __cregister unsigned long __ECR3018;
extern volatile __cregister unsigned long __ECR3019;
extern volatile __cregister unsigned long __ECR3020;
extern volatile __cregister unsigned long __ECR3021;
extern volatile __cregister unsigned long __ECR3022;
extern volatile __cregister unsigned long __ECR3023;
extern volatile __cregister unsigned long __ECR3024;
extern volatile __cregister unsigned long __ECR3025;
extern volatile __cregister unsigned long __ECR3026;
extern volatile __cregister unsigned long __ECR3027;
extern volatile __cregister unsigned long __ECR3028;
extern volatile __cregister unsigned long __ECR3029;
extern volatile __cregister unsigned long __ECR3030;
extern volatile __cregister unsigned long __ECR3031;
extern volatile __cregister unsigned long __ECR3032;
extern volatile __cregister unsigned long __ECR3033;
extern volatile __cregister unsigned long __ECR3034;
extern volatile __cregister unsigned long __ECR3035;
extern volatile __cregister unsigned long __ECR3036;
extern volatile __cregister unsigned long __ECR3037;
extern volatile __cregister unsigned long __ECR3038;
extern volatile __cregister unsigned long __ECR3039;
extern volatile __cregister unsigned long __ECR3040;
extern volatile __cregister unsigned long __ECR3041;
extern volatile __cregister unsigned long __ECR3042;
extern volatile __cregister unsigned long __ECR3043;
extern volatile __cregister unsigned long __ECR3044;
extern volatile __cregister unsigned long __ECR3045;
extern volatile __cregister unsigned long __ECR3046;
extern volatile __cregister unsigned long __ECR3047;
extern volatile __cregister unsigned long __ECR3048;
extern volatile __cregister unsigned long __ECR3049;
extern volatile __cregister unsigned long __ECR3050;
extern volatile __cregister unsigned long __ECR3051;
extern volatile __cregister unsigned long __ECR3052;
extern volatile __cregister unsigned long __ECR3053;
extern volatile __cregister unsigned long __ECR3054;
extern volatile __cregister unsigned long __ECR3055;
extern volatile __cregister unsigned long __ECR3056;
extern volatile __cregister unsigned long __ECR3057;
extern volatile __cregister unsigned long __ECR3058;
extern volatile __cregister unsigned long __ECR3059;
extern volatile __cregister unsigned long __ECR3060;
extern volatile __cregister unsigned long __ECR3061;
extern volatile __cregister unsigned long __ECR3062;
extern volatile __cregister unsigned long __ECR3063;
extern volatile __cregister unsigned long __ECR3064;
extern volatile __cregister unsigned long __ECR3065;
extern volatile __cregister unsigned long __ECR3066;
extern volatile __cregister unsigned long __ECR3067;
extern volatile __cregister unsigned long __ECR3068;
extern volatile __cregister unsigned long __ECR3069;
extern volatile __cregister unsigned long __ECR3070;
extern volatile __cregister unsigned long __ECR3071;
extern volatile __cregister unsigned long __ECR3072;
extern volatile __cregister unsigned long __ECR3073;
extern volatile __cregister unsigned long __ECR3074;
extern volatile __cregister unsigned long __ECR3075;
extern volatile __cregister unsigned long __ECR3076;
extern volatile __cregister unsigned long __ECR3077;
extern volatile __cregister unsigned long __ECR3078;
extern volatile __cregister unsigned long __ECR3079;
extern volatile __cregister unsigned long __ECR3080;
extern volatile __cregister unsigned long __ECR3081;
extern volatile __cregister unsigned long __ECR3082;
extern volatile __cregister unsigned long __ECR3083;
extern volatile __cregister unsigned long __ECR3084;
extern volatile __cregister unsigned long __ECR3085;
extern volatile __cregister unsigned long __ECR3086;
extern volatile __cregister unsigned long __ECR3087;
extern volatile __cregister unsigned long __ECR3088;
extern volatile __cregister unsigned long __ECR3089;
extern volatile __cregister unsigned long __ECR3090;
extern volatile __cregister unsigned long __ECR3091;
extern volatile __cregister unsigned long __ECR3092;
extern volatile __cregister unsigned long __ECR3093;
extern volatile __cregister unsigned long __ECR3094;
extern volatile __cregister unsigned long __ECR3095;
extern volatile __cregister unsigned long __ECR3096;
extern volatile __cregister unsigned long __ECR3097;
extern volatile __cregister unsigned long __ECR3098;
extern volatile __cregister unsigned long __ECR3099;
extern volatile __cregister unsigned long __ECR3100;
extern volatile __cregister unsigned long __ECR3101;
extern volatile __cregister unsigned long __ECR3102;
extern volatile __cregister unsigned long __ECR3103;
extern volatile __cregister unsigned long __ECR3104;
extern volatile __cregister unsigned long __ECR3105;
extern volatile __cregister unsigned long __ECR3106;
extern volatile __cregister unsigned long __ECR3107;
extern volatile __cregister unsigned long __ECR3108;
extern volatile __cregister unsigned long __ECR3109;
extern volatile __cregister unsigned long __ECR3110;
extern volatile __cregister unsigned long __ECR3111;
extern volatile __cregister unsigned long __ECR3112;
extern volatile __cregister unsigned long __ECR3113;
extern volatile __cregister unsigned long __ECR3114;
extern volatile __cregister unsigned long __ECR3115;
extern volatile __cregister unsigned long __ECR3116;
extern volatile __cregister unsigned long __ECR3117;
extern volatile __cregister unsigned long __ECR3118;
extern volatile __cregister unsigned long __ECR3119;
extern volatile __cregister unsigned long __ECR3120;
extern volatile __cregister unsigned long __ECR3121;
extern volatile __cregister unsigned long __ECR3122;
extern volatile __cregister unsigned long __ECR3123;
extern volatile __cregister unsigned long __ECR3124;
extern volatile __cregister unsigned long __ECR3125;
extern volatile __cregister unsigned long __ECR3126;
extern volatile __cregister unsigned long __ECR3127;
extern volatile __cregister unsigned long __ECR3128;
extern volatile __cregister unsigned long __ECR3129;
extern volatile __cregister unsigned long __ECR3130;
extern volatile __cregister unsigned long __ECR3131;
extern volatile __cregister unsigned long __ECR3132;
extern volatile __cregister unsigned long __ECR3133;
extern volatile __cregister unsigned long __ECR3134;
extern volatile __cregister unsigned long __ECR3135;
extern volatile __cregister unsigned long __ECR3136;
extern volatile __cregister unsigned long __ECR3137;
extern volatile __cregister unsigned long __ECR3138;
extern volatile __cregister unsigned long __ECR3139;
extern volatile __cregister unsigned long __ECR3140;
extern volatile __cregister unsigned long __ECR3141;
extern volatile __cregister unsigned long __ECR3142;
extern volatile __cregister unsigned long __ECR3143;
extern volatile __cregister unsigned long __ECR3144;
extern volatile __cregister unsigned long __ECR3145;
extern volatile __cregister unsigned long __ECR3146;
extern volatile __cregister unsigned long __ECR3147;
extern volatile __cregister unsigned long __ECR3148;
extern volatile __cregister unsigned long __ECR3149;
extern volatile __cregister unsigned long __ECR3150;
extern volatile __cregister unsigned long __ECR3151;
extern volatile __cregister unsigned long __ECR3152;
extern volatile __cregister unsigned long __ECR3153;
extern volatile __cregister unsigned long __ECR3154;
extern volatile __cregister unsigned long __ECR3155;
extern volatile __cregister unsigned long __ECR3156;
extern volatile __cregister unsigned long __ECR3157;
extern volatile __cregister unsigned long __ECR3158;
extern volatile __cregister unsigned long __ECR3159;
extern volatile __cregister unsigned long __ECR3160;
extern volatile __cregister unsigned long __ECR3161;
extern volatile __cregister unsigned long __ECR3162;
extern volatile __cregister unsigned long __ECR3163;
extern volatile __cregister unsigned long __ECR3164;
extern volatile __cregister unsigned long __ECR3165;
extern volatile __cregister unsigned long __ECR3166;
extern volatile __cregister unsigned long __ECR3167;
extern volatile __cregister unsigned long __ECR3168;
extern volatile __cregister unsigned long __ECR3169;
extern volatile __cregister unsigned long __ECR3170;
extern volatile __cregister unsigned long __ECR3171;
extern volatile __cregister unsigned long __ECR3172;
extern volatile __cregister unsigned long __ECR3173;
extern volatile __cregister unsigned long __ECR3174;
extern volatile __cregister unsigned long __ECR3175;
extern volatile __cregister unsigned long __ECR3176;
extern volatile __cregister unsigned long __ECR3177;
extern volatile __cregister unsigned long __ECR3178;
extern volatile __cregister unsigned long __ECR3179;
extern volatile __cregister unsigned long __ECR3180;
extern volatile __cregister unsigned long __ECR3181;
extern volatile __cregister unsigned long __ECR3182;
extern volatile __cregister unsigned long __ECR3183;
extern volatile __cregister unsigned long __ECR3184;
extern volatile __cregister unsigned long __ECR3185;
extern volatile __cregister unsigned long __ECR3186;
extern volatile __cregister unsigned long __ECR3187;
extern volatile __cregister unsigned long __ECR3188;
extern volatile __cregister unsigned long __ECR3189;
extern volatile __cregister unsigned long __ECR3190;
extern volatile __cregister unsigned long __ECR3191;
extern volatile __cregister unsigned long __ECR3192;
extern volatile __cregister unsigned long __ECR3193;
extern volatile __cregister unsigned long __ECR3194;
extern volatile __cregister unsigned long __ECR3195;
extern volatile __cregister unsigned long __ECR3196;
extern volatile __cregister unsigned long __ECR3197;
extern volatile __cregister unsigned long __ECR3198;
extern volatile __cregister unsigned long __ECR3199;
extern volatile __cregister unsigned long __ECR3200;
extern volatile __cregister unsigned long __ECR3201;
extern volatile __cregister unsigned long __ECR3202;
extern volatile __cregister unsigned long __ECR3203;
extern volatile __cregister unsigned long __ECR3204;
extern volatile __cregister unsigned long __ECR3205;
extern volatile __cregister unsigned long __ECR3206;
extern volatile __cregister unsigned long __ECR3207;
extern volatile __cregister unsigned long __ECR3208;
extern volatile __cregister unsigned long __ECR3209;
extern volatile __cregister unsigned long __ECR3210;
extern volatile __cregister unsigned long __ECR3211;
extern volatile __cregister unsigned long __ECR3212;
extern volatile __cregister unsigned long __ECR3213;
extern volatile __cregister unsigned long __ECR3214;
extern volatile __cregister unsigned long __ECR3215;
extern volatile __cregister unsigned long __ECR3216;
extern volatile __cregister unsigned long __ECR3217;
extern volatile __cregister unsigned long __ECR3218;
extern volatile __cregister unsigned long __ECR3219;
extern volatile __cregister unsigned long __ECR3220;
extern volatile __cregister unsigned long __ECR3221;
extern volatile __cregister unsigned long __ECR3222;
extern volatile __cregister unsigned long __ECR3223;
extern volatile __cregister unsigned long __ECR3224;
extern volatile __cregister unsigned long __ECR3225;
extern volatile __cregister unsigned long __ECR3226;
extern volatile __cregister unsigned long __ECR3227;
extern volatile __cregister unsigned long __ECR3228;
extern volatile __cregister unsigned long __ECR3229;
extern volatile __cregister unsigned long __ECR3230;
extern volatile __cregister unsigned long __ECR3231;
extern volatile __cregister unsigned long __ECR3232;
extern volatile __cregister unsigned long __ECR3233;
extern volatile __cregister unsigned long __ECR3234;
extern volatile __cregister unsigned long __ECR3235;
extern volatile __cregister unsigned long __ECR3236;
extern volatile __cregister unsigned long __ECR3237;
extern volatile __cregister unsigned long __ECR3238;
extern volatile __cregister unsigned long __ECR3239;
extern volatile __cregister unsigned long __ECR3240;
extern volatile __cregister unsigned long __ECR3241;
extern volatile __cregister unsigned long __ECR3242;
extern volatile __cregister unsigned long __ECR3243;
extern volatile __cregister unsigned long __ECR3244;
extern volatile __cregister unsigned long __ECR3245;
extern volatile __cregister unsigned long __ECR3246;
extern volatile __cregister unsigned long __ECR3247;
extern volatile __cregister unsigned long __ECR3248;
extern volatile __cregister unsigned long __ECR3249;
extern volatile __cregister unsigned long __ECR3250;
extern volatile __cregister unsigned long __ECR3251;
extern volatile __cregister unsigned long __ECR3252;
extern volatile __cregister unsigned long __ECR3253;
extern volatile __cregister unsigned long __ECR3254;
extern volatile __cregister unsigned long __ECR3255;
extern volatile __cregister unsigned long __ECR3256;
extern volatile __cregister unsigned long __ECR3257;
extern volatile __cregister unsigned long __ECR3258;
extern volatile __cregister unsigned long __ECR3259;
extern volatile __cregister unsigned long __ECR3260;
extern volatile __cregister unsigned long __ECR3261;
extern volatile __cregister unsigned long __ECR3262;
extern volatile __cregister unsigned long __ECR3263;
extern volatile __cregister unsigned long __ECR3264;
extern volatile __cregister unsigned long __ECR3265;
extern volatile __cregister unsigned long __ECR3266;
extern volatile __cregister unsigned long __ECR3267;
extern volatile __cregister unsigned long __ECR3268;
extern volatile __cregister unsigned long __ECR3269;
extern volatile __cregister unsigned long __ECR3270;
extern volatile __cregister unsigned long __ECR3271;
extern volatile __cregister unsigned long __ECR3272;
extern volatile __cregister unsigned long __ECR3273;
extern volatile __cregister unsigned long __ECR3274;
extern volatile __cregister unsigned long __ECR3275;
extern volatile __cregister unsigned long __ECR3276;
extern volatile __cregister unsigned long __ECR3277;
extern volatile __cregister unsigned long __ECR3278;
extern volatile __cregister unsigned long __ECR3279;
extern volatile __cregister unsigned long __ECR3280;
extern volatile __cregister unsigned long __ECR3281;
extern volatile __cregister unsigned long __ECR3282;
extern volatile __cregister unsigned long __ECR3283;
extern volatile __cregister unsigned long __ECR3284;
extern volatile __cregister unsigned long __ECR3285;
extern volatile __cregister unsigned long __ECR3286;
extern volatile __cregister unsigned long __ECR3287;
extern volatile __cregister unsigned long __ECR3288;
extern volatile __cregister unsigned long __ECR3289;
extern volatile __cregister unsigned long __ECR3290;
extern volatile __cregister unsigned long __ECR3291;
extern volatile __cregister unsigned long __ECR3292;
extern volatile __cregister unsigned long __ECR3293;
extern volatile __cregister unsigned long __ECR3294;
extern volatile __cregister unsigned long __ECR3295;
extern volatile __cregister unsigned long __ECR3296;
extern volatile __cregister unsigned long __ECR3297;
extern volatile __cregister unsigned long __ECR3298;
extern volatile __cregister unsigned long __ECR3299;
extern volatile __cregister unsigned long __ECR3300;
extern volatile __cregister unsigned long __ECR3301;
extern volatile __cregister unsigned long __ECR3302;
extern volatile __cregister unsigned long __ECR3303;
extern volatile __cregister unsigned long __ECR3304;
extern volatile __cregister unsigned long __ECR3305;
extern volatile __cregister unsigned long __ECR3306;
extern volatile __cregister unsigned long __ECR3307;
extern volatile __cregister unsigned long __ECR3308;
extern volatile __cregister unsigned long __ECR3309;
extern volatile __cregister unsigned long __ECR3310;
extern volatile __cregister unsigned long __ECR3311;
extern volatile __cregister unsigned long __ECR3312;
extern volatile __cregister unsigned long __ECR3313;
extern volatile __cregister unsigned long __ECR3314;
extern volatile __cregister unsigned long __ECR3315;
extern volatile __cregister unsigned long __ECR3316;
extern volatile __cregister unsigned long __ECR3317;
extern volatile __cregister unsigned long __ECR3318;
extern volatile __cregister unsigned long __ECR3319;
extern volatile __cregister unsigned long __ECR3320;
extern volatile __cregister unsigned long __ECR3321;
extern volatile __cregister unsigned long __ECR3322;
extern volatile __cregister unsigned long __ECR3323;
extern volatile __cregister unsigned long __ECR3324;
extern volatile __cregister unsigned long __ECR3325;
extern volatile __cregister unsigned long __ECR3326;
extern volatile __cregister unsigned long __ECR3327;
extern volatile __cregister unsigned long __ECR3328;
extern volatile __cregister unsigned long __ECR3329;
extern volatile __cregister unsigned long __ECR3330;
extern volatile __cregister unsigned long __ECR3331;
extern volatile __cregister unsigned long __ECR3332;
extern volatile __cregister unsigned long __ECR3333;
extern volatile __cregister unsigned long __ECR3334;
extern volatile __cregister unsigned long __ECR3335;
extern volatile __cregister unsigned long __ECR3336;
extern volatile __cregister unsigned long __ECR3337;
extern volatile __cregister unsigned long __ECR3338;
extern volatile __cregister unsigned long __ECR3339;
extern volatile __cregister unsigned long __ECR3340;
extern volatile __cregister unsigned long __ECR3341;
extern volatile __cregister unsigned long __ECR3342;
extern volatile __cregister unsigned long __ECR3343;
extern volatile __cregister unsigned long __ECR3344;
extern volatile __cregister unsigned long __ECR3345;
extern volatile __cregister unsigned long __ECR3346;
extern volatile __cregister unsigned long __ECR3347;
extern volatile __cregister unsigned long __ECR3348;
extern volatile __cregister unsigned long __ECR3349;
extern volatile __cregister unsigned long __ECR3350;
extern volatile __cregister unsigned long __ECR3351;
extern volatile __cregister unsigned long __ECR3352;
extern volatile __cregister unsigned long __ECR3353;
extern volatile __cregister unsigned long __ECR3354;
extern volatile __cregister unsigned long __ECR3355;
extern volatile __cregister unsigned long __ECR3356;
extern volatile __cregister unsigned long __ECR3357;
extern volatile __cregister unsigned long __ECR3358;
extern volatile __cregister unsigned long __ECR3359;
extern volatile __cregister unsigned long __ECR3360;
extern volatile __cregister unsigned long __ECR3361;
extern volatile __cregister unsigned long __ECR3362;
extern volatile __cregister unsigned long __ECR3363;
extern volatile __cregister unsigned long __ECR3364;
extern volatile __cregister unsigned long __ECR3365;
extern volatile __cregister unsigned long __ECR3366;
extern volatile __cregister unsigned long __ECR3367;
extern volatile __cregister unsigned long __ECR3368;
extern volatile __cregister unsigned long __ECR3369;
extern volatile __cregister unsigned long __ECR3370;
extern volatile __cregister unsigned long __ECR3371;
extern volatile __cregister unsigned long __ECR3372;
extern volatile __cregister unsigned long __ECR3373;
extern volatile __cregister unsigned long __ECR3374;
extern volatile __cregister unsigned long __ECR3375;
extern volatile __cregister unsigned long __ECR3376;
extern volatile __cregister unsigned long __ECR3377;
extern volatile __cregister unsigned long __ECR3378;
extern volatile __cregister unsigned long __ECR3379;
extern volatile __cregister unsigned long __ECR3380;
extern volatile __cregister unsigned long __ECR3381;
extern volatile __cregister unsigned long __ECR3382;
extern volatile __cregister unsigned long __ECR3383;
extern volatile __cregister unsigned long __ECR3384;
extern volatile __cregister unsigned long __ECR3385;
extern volatile __cregister unsigned long __ECR3386;
extern volatile __cregister unsigned long __ECR3387;
extern volatile __cregister unsigned long __ECR3388;
extern volatile __cregister unsigned long __ECR3389;
extern volatile __cregister unsigned long __ECR3390;
extern volatile __cregister unsigned long __ECR3391;
extern volatile __cregister unsigned long __ECR3392;
extern volatile __cregister unsigned long __ECR3393;
extern volatile __cregister unsigned long __ECR3394;
extern volatile __cregister unsigned long __ECR3395;
extern volatile __cregister unsigned long __ECR3396;
extern volatile __cregister unsigned long __ECR3397;
extern volatile __cregister unsigned long __ECR3398;
extern volatile __cregister unsigned long __ECR3399;
extern volatile __cregister unsigned long __ECR3400;
extern volatile __cregister unsigned long __ECR3401;
extern volatile __cregister unsigned long __ECR3402;
extern volatile __cregister unsigned long __ECR3403;
extern volatile __cregister unsigned long __ECR3404;
extern volatile __cregister unsigned long __ECR3405;
extern volatile __cregister unsigned long __ECR3406;
extern volatile __cregister unsigned long __ECR3407;
extern volatile __cregister unsigned long __ECR3408;
extern volatile __cregister unsigned long __ECR3409;
extern volatile __cregister unsigned long __ECR3410;
extern volatile __cregister unsigned long __ECR3411;
extern volatile __cregister unsigned long __ECR3412;
extern volatile __cregister unsigned long __ECR3413;
extern volatile __cregister unsigned long __ECR3414;
extern volatile __cregister unsigned long __ECR3415;
extern volatile __cregister unsigned long __ECR3416;
extern volatile __cregister unsigned long __ECR3417;
extern volatile __cregister unsigned long __ECR3418;
extern volatile __cregister unsigned long __ECR3419;
extern volatile __cregister unsigned long __ECR3420;
extern volatile __cregister unsigned long __ECR3421;
extern volatile __cregister unsigned long __ECR3422;
extern volatile __cregister unsigned long __ECR3423;
extern volatile __cregister unsigned long __ECR3424;
extern volatile __cregister unsigned long __ECR3425;
extern volatile __cregister unsigned long __ECR3426;
extern volatile __cregister unsigned long __ECR3427;
extern volatile __cregister unsigned long __ECR3428;
extern volatile __cregister unsigned long __ECR3429;
extern volatile __cregister unsigned long __ECR3430;
extern volatile __cregister unsigned long __ECR3431;
extern volatile __cregister unsigned long __ECR3432;
extern volatile __cregister unsigned long __ECR3433;
extern volatile __cregister unsigned long __ECR3434;
extern volatile __cregister unsigned long __ECR3435;
extern volatile __cregister unsigned long __ECR3436;
extern volatile __cregister unsigned long __ECR3437;
extern volatile __cregister unsigned long __ECR3438;
extern volatile __cregister unsigned long __ECR3439;
extern volatile __cregister unsigned long __ECR3440;
extern volatile __cregister unsigned long __ECR3441;
extern volatile __cregister unsigned long __ECR3442;
extern volatile __cregister unsigned long __ECR3443;
extern volatile __cregister unsigned long __ECR3444;
extern volatile __cregister unsigned long __ECR3445;
extern volatile __cregister unsigned long __ECR3446;
extern volatile __cregister unsigned long __ECR3447;
extern volatile __cregister unsigned long __ECR3448;
extern volatile __cregister unsigned long __ECR3449;
extern volatile __cregister unsigned long __ECR3450;
extern volatile __cregister unsigned long __ECR3451;
extern volatile __cregister unsigned long __ECR3452;
extern volatile __cregister unsigned long __ECR3453;
extern volatile __cregister unsigned long __ECR3454;
extern volatile __cregister unsigned long __ECR3455;
extern volatile __cregister unsigned long __ECR3456;
extern volatile __cregister unsigned long __ECR3457;
extern volatile __cregister unsigned long __ECR3458;
extern volatile __cregister unsigned long __ECR3459;
extern volatile __cregister unsigned long __ECR3460;
extern volatile __cregister unsigned long __ECR3461;
extern volatile __cregister unsigned long __ECR3462;
extern volatile __cregister unsigned long __ECR3463;
extern volatile __cregister unsigned long __ECR3464;
extern volatile __cregister unsigned long __ECR3465;
extern volatile __cregister unsigned long __ECR3466;
extern volatile __cregister unsigned long __ECR3467;
extern volatile __cregister unsigned long __ECR3468;
extern volatile __cregister unsigned long __ECR3469;
extern volatile __cregister unsigned long __ECR3470;
extern volatile __cregister unsigned long __ECR3471;
extern volatile __cregister unsigned long __ECR3472;
extern volatile __cregister unsigned long __ECR3473;
extern volatile __cregister unsigned long __ECR3474;
extern volatile __cregister unsigned long __ECR3475;
extern volatile __cregister unsigned long __ECR3476;
extern volatile __cregister unsigned long __ECR3477;
extern volatile __cregister unsigned long __ECR3478;
extern volatile __cregister unsigned long __ECR3479;
extern volatile __cregister unsigned long __ECR3480;
extern volatile __cregister unsigned long __ECR3481;
extern volatile __cregister unsigned long __ECR3482;
extern volatile __cregister unsigned long __ECR3483;
extern volatile __cregister unsigned long __ECR3484;
extern volatile __cregister unsigned long __ECR3485;
extern volatile __cregister unsigned long __ECR3486;
extern volatile __cregister unsigned long __ECR3487;
extern volatile __cregister unsigned long __ECR3488;
extern volatile __cregister unsigned long __ECR3489;
extern volatile __cregister unsigned long __ECR3490;
extern volatile __cregister unsigned long __ECR3491;
extern volatile __cregister unsigned long __ECR3492;
extern volatile __cregister unsigned long __ECR3493;
extern volatile __cregister unsigned long __ECR3494;
extern volatile __cregister unsigned long __ECR3495;
extern volatile __cregister unsigned long __ECR3496;
extern volatile __cregister unsigned long __ECR3497;
extern volatile __cregister unsigned long __ECR3498;
extern volatile __cregister unsigned long __ECR3499;
extern volatile __cregister unsigned long __ECR3500;
extern volatile __cregister unsigned long __ECR3501;
extern volatile __cregister unsigned long __ECR3502;
extern volatile __cregister unsigned long __ECR3503;
extern volatile __cregister unsigned long __ECR3504;
extern volatile __cregister unsigned long __ECR3505;
extern volatile __cregister unsigned long __ECR3506;
extern volatile __cregister unsigned long __ECR3507;
extern volatile __cregister unsigned long __ECR3508;
extern volatile __cregister unsigned long __ECR3509;
extern volatile __cregister unsigned long __ECR3510;
extern volatile __cregister unsigned long __ECR3511;
extern volatile __cregister unsigned long __ECR3512;
extern volatile __cregister unsigned long __ECR3513;
extern volatile __cregister unsigned long __ECR3514;
extern volatile __cregister unsigned long __ECR3515;
extern volatile __cregister unsigned long __ECR3516;
extern volatile __cregister unsigned long __ECR3517;
extern volatile __cregister unsigned long __ECR3518;
extern volatile __cregister unsigned long __ECR3519;
extern volatile __cregister unsigned long __ECR3520;
extern volatile __cregister unsigned long __ECR3521;
extern volatile __cregister unsigned long __ECR3522;
extern volatile __cregister unsigned long __ECR3523;
extern volatile __cregister unsigned long __ECR3524;
extern volatile __cregister unsigned long __ECR3525;
extern volatile __cregister unsigned long __ECR3526;
extern volatile __cregister unsigned long __ECR3527;
extern volatile __cregister unsigned long __ECR3528;
extern volatile __cregister unsigned long __ECR3529;
extern volatile __cregister unsigned long __ECR3530;
extern volatile __cregister unsigned long __ECR3531;
extern volatile __cregister unsigned long __ECR3532;
extern volatile __cregister unsigned long __ECR3533;
extern volatile __cregister unsigned long __ECR3534;
extern volatile __cregister unsigned long __ECR3535;
extern volatile __cregister unsigned long __ECR3536;
extern volatile __cregister unsigned long __ECR3537;
extern volatile __cregister unsigned long __ECR3538;
extern volatile __cregister unsigned long __ECR3539;
extern volatile __cregister unsigned long __ECR3540;
extern volatile __cregister unsigned long __ECR3541;
extern volatile __cregister unsigned long __ECR3542;
extern volatile __cregister unsigned long __ECR3543;
extern volatile __cregister unsigned long __ECR3544;
extern volatile __cregister unsigned long __ECR3545;
extern volatile __cregister unsigned long __ECR3546;
extern volatile __cregister unsigned long __ECR3547;
extern volatile __cregister unsigned long __ECR3548;
extern volatile __cregister unsigned long __ECR3549;
extern volatile __cregister unsigned long __ECR3550;
extern volatile __cregister unsigned long __ECR3551;
extern volatile __cregister unsigned long __ECR3552;
extern volatile __cregister unsigned long __ECR3553;
extern volatile __cregister unsigned long __ECR3554;
extern volatile __cregister unsigned long __ECR3555;
extern volatile __cregister unsigned long __ECR3556;
extern volatile __cregister unsigned long __ECR3557;
extern volatile __cregister unsigned long __ECR3558;
extern volatile __cregister unsigned long __ECR3559;
extern volatile __cregister unsigned long __ECR3560;
extern volatile __cregister unsigned long __ECR3561;
extern volatile __cregister unsigned long __ECR3562;
extern volatile __cregister unsigned long __ECR3563;
extern volatile __cregister unsigned long __ECR3564;
extern volatile __cregister unsigned long __ECR3565;
extern volatile __cregister unsigned long __ECR3566;
extern volatile __cregister unsigned long __ECR3567;
extern volatile __cregister unsigned long __ECR3568;
extern volatile __cregister unsigned long __ECR3569;
extern volatile __cregister unsigned long __ECR3570;
extern volatile __cregister unsigned long __ECR3571;
extern volatile __cregister unsigned long __ECR3572;
extern volatile __cregister unsigned long __ECR3573;
extern volatile __cregister unsigned long __ECR3574;
extern volatile __cregister unsigned long __ECR3575;
extern volatile __cregister unsigned long __ECR3576;
extern volatile __cregister unsigned long __ECR3577;
extern volatile __cregister unsigned long __ECR3578;
extern volatile __cregister unsigned long __ECR3579;
extern volatile __cregister unsigned long __ECR3580;
extern volatile __cregister unsigned long __ECR3581;
extern volatile __cregister unsigned long __ECR3582;
extern volatile __cregister unsigned long __ECR3583;
extern volatile __cregister unsigned long __ECR3584;
extern volatile __cregister unsigned long __ECR3585;
extern volatile __cregister unsigned long __ECR3586;
extern volatile __cregister unsigned long __ECR3587;
extern volatile __cregister unsigned long __ECR3588;
extern volatile __cregister unsigned long __ECR3589;
extern volatile __cregister unsigned long __ECR3590;
extern volatile __cregister unsigned long __ECR3591;
extern volatile __cregister unsigned long __ECR3592;
extern volatile __cregister unsigned long __ECR3593;
extern volatile __cregister unsigned long __ECR3594;
extern volatile __cregister unsigned long __ECR3595;
extern volatile __cregister unsigned long __ECR3596;
extern volatile __cregister unsigned long __ECR3597;
extern volatile __cregister unsigned long __ECR3598;
extern volatile __cregister unsigned long __ECR3599;
extern volatile __cregister unsigned long __ECR3600;
extern volatile __cregister unsigned long __ECR3601;
extern volatile __cregister unsigned long __ECR3602;
extern volatile __cregister unsigned long __ECR3603;
extern volatile __cregister unsigned long __ECR3604;
extern volatile __cregister unsigned long __ECR3605;
extern volatile __cregister unsigned long __ECR3606;
extern volatile __cregister unsigned long __ECR3607;
extern volatile __cregister unsigned long __ECR3608;
extern volatile __cregister unsigned long __ECR3609;
extern volatile __cregister unsigned long __ECR3610;
extern volatile __cregister unsigned long __ECR3611;
extern volatile __cregister unsigned long __ECR3612;
extern volatile __cregister unsigned long __ECR3613;
extern volatile __cregister unsigned long __ECR3614;
extern volatile __cregister unsigned long __ECR3615;
extern volatile __cregister unsigned long __ECR3616;
extern volatile __cregister unsigned long __ECR3617;
extern volatile __cregister unsigned long __ECR3618;
extern volatile __cregister unsigned long __ECR3619;
extern volatile __cregister unsigned long __ECR3620;
extern volatile __cregister unsigned long __ECR3621;
extern volatile __cregister unsigned long __ECR3622;
extern volatile __cregister unsigned long __ECR3623;
extern volatile __cregister unsigned long __ECR3624;
extern volatile __cregister unsigned long __ECR3625;
extern volatile __cregister unsigned long __ECR3626;
extern volatile __cregister unsigned long __ECR3627;
extern volatile __cregister unsigned long __ECR3628;
extern volatile __cregister unsigned long __ECR3629;
extern volatile __cregister unsigned long __ECR3630;
extern volatile __cregister unsigned long __ECR3631;
extern volatile __cregister unsigned long __ECR3632;
extern volatile __cregister unsigned long __ECR3633;
extern volatile __cregister unsigned long __ECR3634;
extern volatile __cregister unsigned long __ECR3635;
extern volatile __cregister unsigned long __ECR3636;
extern volatile __cregister unsigned long __ECR3637;
extern volatile __cregister unsigned long __ECR3638;
extern volatile __cregister unsigned long __ECR3639;
extern volatile __cregister unsigned long __ECR3640;
extern volatile __cregister unsigned long __ECR3641;
extern volatile __cregister unsigned long __ECR3642;
extern volatile __cregister unsigned long __ECR3643;
extern volatile __cregister unsigned long __ECR3644;
extern volatile __cregister unsigned long __ECR3645;
extern volatile __cregister unsigned long __ECR3646;
extern volatile __cregister unsigned long __ECR3647;
extern volatile __cregister unsigned long __ECR3648;
extern volatile __cregister unsigned long __ECR3649;
extern volatile __cregister unsigned long __ECR3650;
extern volatile __cregister unsigned long __ECR3651;
extern volatile __cregister unsigned long __ECR3652;
extern volatile __cregister unsigned long __ECR3653;
extern volatile __cregister unsigned long __ECR3654;
extern volatile __cregister unsigned long __ECR3655;
extern volatile __cregister unsigned long __ECR3656;
extern volatile __cregister unsigned long __ECR3657;
extern volatile __cregister unsigned long __ECR3658;
extern volatile __cregister unsigned long __ECR3659;
extern volatile __cregister unsigned long __ECR3660;
extern volatile __cregister unsigned long __ECR3661;
extern volatile __cregister unsigned long __ECR3662;
extern volatile __cregister unsigned long __ECR3663;
extern volatile __cregister unsigned long __ECR3664;
extern volatile __cregister unsigned long __ECR3665;
extern volatile __cregister unsigned long __ECR3666;
extern volatile __cregister unsigned long __ECR3667;
extern volatile __cregister unsigned long __ECR3668;
extern volatile __cregister unsigned long __ECR3669;
extern volatile __cregister unsigned long __ECR3670;
extern volatile __cregister unsigned long __ECR3671;
extern volatile __cregister unsigned long __ECR3672;
extern volatile __cregister unsigned long __ECR3673;
extern volatile __cregister unsigned long __ECR3674;
extern volatile __cregister unsigned long __ECR3675;
extern volatile __cregister unsigned long __ECR3676;
extern volatile __cregister unsigned long __ECR3677;
extern volatile __cregister unsigned long __ECR3678;
extern volatile __cregister unsigned long __ECR3679;
extern volatile __cregister unsigned long __ECR3680;
extern volatile __cregister unsigned long __ECR3681;
extern volatile __cregister unsigned long __ECR3682;
extern volatile __cregister unsigned long __ECR3683;
extern volatile __cregister unsigned long __ECR3684;
extern volatile __cregister unsigned long __ECR3685;
extern volatile __cregister unsigned long __ECR3686;
extern volatile __cregister unsigned long __ECR3687;
extern volatile __cregister unsigned long __ECR3688;
extern volatile __cregister unsigned long __ECR3689;
extern volatile __cregister unsigned long __ECR3690;
extern volatile __cregister unsigned long __ECR3691;
extern volatile __cregister unsigned long __ECR3692;
extern volatile __cregister unsigned long __ECR3693;
extern volatile __cregister unsigned long __ECR3694;
extern volatile __cregister unsigned long __ECR3695;
extern volatile __cregister unsigned long __ECR3696;
extern volatile __cregister unsigned long __ECR3697;
extern volatile __cregister unsigned long __ECR3698;
extern volatile __cregister unsigned long __ECR3699;
extern volatile __cregister unsigned long __ECR3700;
extern volatile __cregister unsigned long __ECR3701;
extern volatile __cregister unsigned long __ECR3702;
extern volatile __cregister unsigned long __ECR3703;
extern volatile __cregister unsigned long __ECR3704;
extern volatile __cregister unsigned long __ECR3705;
extern volatile __cregister unsigned long __ECR3706;
extern volatile __cregister unsigned long __ECR3707;
extern volatile __cregister unsigned long __ECR3708;
extern volatile __cregister unsigned long __ECR3709;
extern volatile __cregister unsigned long __ECR3710;
extern volatile __cregister unsigned long __ECR3711;
extern volatile __cregister unsigned long __ECR3712;
extern volatile __cregister unsigned long __ECR3713;
extern volatile __cregister unsigned long __ECR3714;
extern volatile __cregister unsigned long __ECR3715;
extern volatile __cregister unsigned long __ECR3716;
extern volatile __cregister unsigned long __ECR3717;
extern volatile __cregister unsigned long __ECR3718;
extern volatile __cregister unsigned long __ECR3719;
extern volatile __cregister unsigned long __ECR3720;
extern volatile __cregister unsigned long __ECR3721;
extern volatile __cregister unsigned long __ECR3722;
extern volatile __cregister unsigned long __ECR3723;
extern volatile __cregister unsigned long __ECR3724;
extern volatile __cregister unsigned long __ECR3725;
extern volatile __cregister unsigned long __ECR3726;
extern volatile __cregister unsigned long __ECR3727;
extern volatile __cregister unsigned long __ECR3728;
extern volatile __cregister unsigned long __ECR3729;
extern volatile __cregister unsigned long __ECR3730;
extern volatile __cregister unsigned long __ECR3731;
extern volatile __cregister unsigned long __ECR3732;
extern volatile __cregister unsigned long __ECR3733;
extern volatile __cregister unsigned long __ECR3734;
extern volatile __cregister unsigned long __ECR3735;
extern volatile __cregister unsigned long __ECR3736;
extern volatile __cregister unsigned long __ECR3737;
extern volatile __cregister unsigned long __ECR3738;
extern volatile __cregister unsigned long __ECR3739;
extern volatile __cregister unsigned long __ECR3740;
extern volatile __cregister unsigned long __ECR3741;
extern volatile __cregister unsigned long __ECR3742;
extern volatile __cregister unsigned long __ECR3743;
extern volatile __cregister unsigned long __ECR3744;
extern volatile __cregister unsigned long __ECR3745;
extern volatile __cregister unsigned long __ECR3746;
extern volatile __cregister unsigned long __ECR3747;
extern volatile __cregister unsigned long __ECR3748;
extern volatile __cregister unsigned long __ECR3749;
extern volatile __cregister unsigned long __ECR3750;
extern volatile __cregister unsigned long __ECR3751;
extern volatile __cregister unsigned long __ECR3752;
extern volatile __cregister unsigned long __ECR3753;
extern volatile __cregister unsigned long __ECR3754;
extern volatile __cregister unsigned long __ECR3755;
extern volatile __cregister unsigned long __ECR3756;
extern volatile __cregister unsigned long __ECR3757;
extern volatile __cregister unsigned long __ECR3758;
extern volatile __cregister unsigned long __ECR3759;
extern volatile __cregister unsigned long __ECR3760;
extern volatile __cregister unsigned long __ECR3761;
extern volatile __cregister unsigned long __ECR3762;
extern volatile __cregister unsigned long __ECR3763;
extern volatile __cregister unsigned long __ECR3764;
extern volatile __cregister unsigned long __ECR3765;
extern volatile __cregister unsigned long __ECR3766;
extern volatile __cregister unsigned long __ECR3767;
extern volatile __cregister unsigned long __ECR3768;
extern volatile __cregister unsigned long __ECR3769;
extern volatile __cregister unsigned long __ECR3770;
extern volatile __cregister unsigned long __ECR3771;
extern volatile __cregister unsigned long __ECR3772;
extern volatile __cregister unsigned long __ECR3773;
extern volatile __cregister unsigned long __ECR3774;
extern volatile __cregister unsigned long __ECR3775;
extern volatile __cregister unsigned long __ECR3776;
extern volatile __cregister unsigned long __ECR3777;
extern volatile __cregister unsigned long __ECR3778;
extern volatile __cregister unsigned long __ECR3779;
extern volatile __cregister unsigned long __ECR3780;
extern volatile __cregister unsigned long __ECR3781;
extern volatile __cregister unsigned long __ECR3782;
extern volatile __cregister unsigned long __ECR3783;
extern volatile __cregister unsigned long __ECR3784;
extern volatile __cregister unsigned long __ECR3785;
extern volatile __cregister unsigned long __ECR3786;
extern volatile __cregister unsigned long __ECR3787;
extern volatile __cregister unsigned long __ECR3788;
extern volatile __cregister unsigned long __ECR3789;
extern volatile __cregister unsigned long __ECR3790;
extern volatile __cregister unsigned long __ECR3791;
extern volatile __cregister unsigned long __ECR3792;
extern volatile __cregister unsigned long __ECR3793;
extern volatile __cregister unsigned long __ECR3794;
extern volatile __cregister unsigned long __ECR3795;
extern volatile __cregister unsigned long __ECR3796;
extern volatile __cregister unsigned long __ECR3797;
extern volatile __cregister unsigned long __ECR3798;
extern volatile __cregister unsigned long __ECR3799;
extern volatile __cregister unsigned long __ECR3800;
extern volatile __cregister unsigned long __ECR3801;
extern volatile __cregister unsigned long __ECR3802;
extern volatile __cregister unsigned long __ECR3803;
extern volatile __cregister unsigned long __ECR3804;
extern volatile __cregister unsigned long __ECR3805;
extern volatile __cregister unsigned long __ECR3806;
extern volatile __cregister unsigned long __ECR3807;
extern volatile __cregister unsigned long __ECR3808;
extern volatile __cregister unsigned long __ECR3809;
extern volatile __cregister unsigned long __ECR3810;
extern volatile __cregister unsigned long __ECR3811;
extern volatile __cregister unsigned long __ECR3812;
extern volatile __cregister unsigned long __ECR3813;
extern volatile __cregister unsigned long __ECR3814;
extern volatile __cregister unsigned long __ECR3815;
extern volatile __cregister unsigned long __ECR3816;
extern volatile __cregister unsigned long __ECR3817;
extern volatile __cregister unsigned long __ECR3818;
extern volatile __cregister unsigned long __ECR3819;
extern volatile __cregister unsigned long __ECR3820;
extern volatile __cregister unsigned long __ECR3821;
extern volatile __cregister unsigned long __ECR3822;
extern volatile __cregister unsigned long __ECR3823;
extern volatile __cregister unsigned long __ECR3824;
extern volatile __cregister unsigned long __ECR3825;
extern volatile __cregister unsigned long __ECR3826;
extern volatile __cregister unsigned long __ECR3827;
extern volatile __cregister unsigned long __ECR3828;
extern volatile __cregister unsigned long __ECR3829;
extern volatile __cregister unsigned long __ECR3830;
extern volatile __cregister unsigned long __ECR3831;
extern volatile __cregister unsigned long __ECR3832;
extern volatile __cregister unsigned long __ECR3833;
extern volatile __cregister unsigned long __ECR3834;
extern volatile __cregister unsigned long __ECR3835;
extern volatile __cregister unsigned long __ECR3836;
extern volatile __cregister unsigned long __ECR3837;
extern volatile __cregister unsigned long __ECR3838;
extern volatile __cregister unsigned long __ECR3839;

#endif /* __C7X_ECR_H */
