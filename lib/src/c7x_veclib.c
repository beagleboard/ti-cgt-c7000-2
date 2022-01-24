/*****************************************************************************/
/*  C7X_VECLIB.H                                                             */
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

/*----------------------------------------------------------------------------
* Built-In Functions: base cases implemented in RTS library
*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
* cmpy(), cdiv(): complex multiplication, complex division
* conj_cmpy(a, b): conj(a) * b, conjuate complex multiplication
*----------------------------------------------------------------------------*/
#define __COMPLEXMPY(CTYPE) \
CTYPE __attribute__((overloadable,builtin)) __c7xabi_cmpy(CTYPE a, CTYPE b) \
{ \
  return (CTYPE) (a.r*b.r - a.i*b.i,  a.r*b.i + a.i*b.r); \
}

#define __COMPLEXCONJMPY(CTYPE) \
CTYPE __attribute__((overloadable,builtin)) __c7xabi_conj_cmpy(CTYPE a, CTYPE b) \
{ \
  return (CTYPE) (a.r*b.r + a.i*b.i, a.r*b.i - a.i*b.r); \
}

#define __COMPLEXDIV(CTYPE) \
CTYPE __attribute__((overloadable,builtin)) __c7xabi_cdiv(CTYPE a, CTYPE b) \
{ \
  return (CTYPE) ((a.r*b.r + a.i*b.i) / (b.r*b.r + b.i*b.i), \
                  (a.i*b.r - a.r*b.i) / (b.r*b.r + b.i*b.i) ); \
}

__COMPLEXMPY(__cchar)
__COMPLEXMPY(__cshort)
__COMPLEXMPY(__cint)
__COMPLEXMPY(__clong)
__COMPLEXMPY(__cfloat)
__COMPLEXMPY(__cdouble)

__COMPLEXCONJMPY(__cchar)
__COMPLEXCONJMPY(__cshort)
__COMPLEXCONJMPY(__cint)
__COMPLEXCONJMPY(__clong)
__COMPLEXCONJMPY(__cfloat)
__COMPLEXCONJMPY(__cdouble)

__COMPLEXDIV(__cchar)
__COMPLEXDIV(__cshort)
__COMPLEXDIV(__cint)
__COMPLEXDIV(__clong)
__COMPLEXDIV(__cfloat)
__COMPLEXDIV(__cdouble)
