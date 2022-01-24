/****************************************************************************/
/*  memset.c       							    */
/*                                                              */
/* Copyright (c) 2017 Texas Instruments Incorporated            */
/* http://www.ti.com/                                           */
/*                                                              */
/*  Redistribution and  use in source  and binary forms, with  or without */
/*  modification,  are permitted provided  that the  following conditions */
/*  are met:                                                    */
/*                                                              */
/*     Redistributions  of source  code must  retain the  above copyright */
/*     notice, this list of conditions and the following disclaimer. */
/*                                                              */
/*     Redistributions in binary form  must reproduce the above copyright */
/*     notice, this  list of conditions  and the following  disclaimer in */
/*     the  documentation  and/or   other  materials  provided  with  the */
/*     distribution.                                            */
/*                                                              */
/*     Neither the  name of Texas Instruments Incorporated  nor the names */
/*     of its  contributors may  be used to  endorse or  promote products */
/*     derived  from   this  software  without   specific  prior  written */
/*     permission.                                              */
/*                                                              */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */
/*                                                              */
/****************************************************************************/
#include <c7x.h>

#undef _INLINE
#include <string.h>

/*---------------------------------------------------------------------------*/
/* MEMSET: Generic memory set/fill routine.                                  */
/*---------------------------------------------------------------------------*/
_CODE_ACCESS void *memset(void *to, int fill, size_t n)
{
    register size_t rn   = 0;
    register size_t peel = n % 64;
    register size_t cnt  = n >> 6;

    register __char64   *rto   = (__char64 *) to;
    register __char64    vFill = (__char64)   fill;

    /* Standard 64x Copy Loop */
    for (rn = 0; rn < cnt; rn++) *rto++ = vFill;

    /* Peeled iteration guarded by vector predicate */
    if (peel) __vstore_pred(__mask_char((unsigned int)peel), rto, vFill);

    return (to);
}
