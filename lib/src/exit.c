/*****************************************************************************/
/*  EXIT.C                                                                   */
/*                                                                           */
/* Copyright (c) 1995 Texas Instruments Incorporated                         */
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
#include <stdlib.h>

#if defined(__TI_RECURSIVE_RESOURCE_MUTEXES)
void   _DATA_ACCESS      (*__TI_delete_mutexes_ptr)(void) = NULL;
#endif

void   _DATA_ACCESS      (*__TI_cleanup_ptr)(void) = NULL;
void   _DATA_ACCESS      (*__TI_dtors_ptr)(int)    = NULL;

/****************************************************************************/
/* EXIT() - NORMAL PROGRAM TERMINATION.                                     */
/*--------------------------------------------------------------------------*/
/* For multi-threaded applications, it is assumed that only the main thread  */
/* will be running upon entry into the exit() function. By this reasoning,   */
/* there is no longer a need to protect access to shared resources like      */
/* __TI_dtors_ptr and __TI_cleanup_ptr after we have started the exit        */
/* sequence.                                                                 */
/*****************************************************************************/
_CODE_ACCESS void exit(int status)
{
   /*--------------------------------------------------------------------*/
   /* BOTH ATEXIT FUNCTIONS AND STATIC OBJECT DESTRUCTORS ARE REGISTERED */
   /* IN A LINK LIST POINTED BY __TI_dtors_ptr, NOW WALK THROUGH THIS    */
   /* LIST TO CALL THEM.                                                 */
   /*--------------------------------------------------------------------*/
   if (__TI_dtors_ptr)  (*__TI_dtors_ptr)(status);

   /*-------------------------------------------------------------------*/
   /* IF FILES ARE POSSIBLY OPEN, __TI_cleanup_ptr() WILL BE SETUP TO   */
   /* CLOSE THEM.                                                       */
   /*-------------------------------------------------------------------*/
   if (__TI_cleanup_ptr)  (*__TI_cleanup_ptr)();

#if defined(__TI_RECURSIVE_RESOURCE_MUTEXES)
   /*-------------------------------------------------------------------*/
   /* IF RECURSIVE RESOURCE MUTEXES ARE USED, THEN DELETE THEM BEFORE   */
   /* TERMINATION.                                                      */
   /*-------------------------------------------------------------------*/
   if (__TI_delete_mutexes_ptr) (*__TI_delete_mutexes_ptr)();
#endif

   abort();
}

/****************************************************************************/
/* ABORT - ABNORMAL PROGRAM TERMINATION.  CURRENTLY JUST HALTS EXECUTION.   */
/****************************************************************************/
_CODE_ACCESS void abort(void)
{
#pragma diag_suppress 1119
#ifndef __VIRTUAL_ENCODING__
   /*-------------------------------------------------------------------*/
   /* SET C$$EXIT LABEL SO THE DEBUGGER KNOWS WHEN THE C++ PROGRAM HAS  */
   /* COMPLETED.  THIS CAN BE REMOVED IF THE DEBUGGER IS NOT USED.      */
   /*-------------------------------------------------------------------*/
   __asm("        .global C$$EXIT");
   __asm("C$$EXIT: NOP 1");
#else
   /*-------------------------------------------------------------------*/
   /* GENERATE A C$$EXIT OPCODE.                                        */
   /*-------------------------------------------------------------------*/
   __asm("         .vinstr   C$$EXIT");
   __asm("C$$EXIT: .encode \"C$$EXIT\", $ENC_OPNDS, 0");
#endif
#pragma diag_default 1119

   for (;;);   /* CURRENTLY, THIS SPINS FOREVER */
}
