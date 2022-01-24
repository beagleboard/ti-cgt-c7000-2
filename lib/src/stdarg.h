/*****************************************************************************/
/* stdarg.h                                                                  */
/*                                                                           */
/* Copyright (c) 2015 Texas Instruments Incorporated                         */
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

#ifndef _STDARG
#define _STDARG

#pragma diag_push
#pragma CHECK_MISRA("-20.1") /* standard headers must define standard names */
#pragma CHECK_MISRA("-20.2") /* standard headers must define standard names */
#pragma CHECK_MISRA("-19.7") /* macros required for implementation */
#pragma CHECK_MISRA("-19.10") /* need types as macro arguments */

#include <sys/_types.h>

#ifndef _VA_LIST_DECLARED
#define _VA_LIST_DECLARED
    typedef __va_list va_list;
#endif

/*****************************************************************************/
/* LLVM VARARGS HANDLING - Use builtin operations.                           */
/*****************************************************************************/
#if defined(__TI_LLVM__)
#define va_start(_ap, _parmN)                                   \
         __builtin_va_start((_ap), (_parmN))
#define va_arg(_ap, _type)                                      \
         __builtin_va_arg((_ap), _type)
#define va_copy(_dst, _src)                                     \
         __builtin_va_copy((_dst), (_src))
#define va_end(_ap)                                             \
         __builtin_va_end(_ap) 
#else

/*****************************************************************************/
/* VA_END - Reclaim resources used by varargs handling.                      */
/*                                                                           */
/* No action needed                                                          */
/*****************************************************************************/
#define va_end(_ap) ((void)0)

/*****************************************************************************/
/* VA_COPY - Make a copy of the varargs.                                     */
/*****************************************************************************/
#define va_copy(_dst, _src) ((_dst)=(_src))

/*---------------------------------------------------------------------------*/
/* Helpers to determine ABI-conforming sizes for passed arguments            */
/*---------------------------------------------------------------------------*/
#define __TI_SIZEOF_SCALAR_STR(_type)                                      \
        ((sizeof(_type) > 32) ? 64 :                                       \
         (sizeof(_type) > 16) ? 32 :                                       \
         (sizeof(_type) >  8) ? 16 :                                       \
         (sizeof(_type) >  4) ?  8 :                                       \
         (sizeof(_type) >  2) ?  4 :                                       \
         (sizeof(_type) >  1) ?  2 : 1)

/*****************************************************************************/
/* VA_START - Set up the va_list pointer.                                    */
/*****************************************************************************/
/*---------------------------------------------------------------------------*/
/* ELF ABI convention:                                                       */
/* - va_list pointer points one byte beyond the last argument.               */
/*---------------------------------------------------------------------------*/
#define va_start(_ap, _parmN)                                    \
         (_ap = ((char *)__va_parmadr(_parmN)) +                 \
                (__va_argref(_parmN) ? sizeof(void *) :                 \
                 __va_argcsu(_parmN) ? __TI_SIZEOF_SCALAR_STR(_parmN) : \
                 sizeof(_parmN)))

/*****************************************************************************/
/* VA_ARG - Return the next argument, adjust va_list pointer                 */
/*                                                                           */
/* Some arguments passed by value are turned into pass-by-reference by       */
/* making a temporary object and passing a pointer to this temporary.  For   */
/* such an argument (indicated by __va_argref(_type)) the actual argument    */
/* passed is a pointer, so it must be dealt with specially.                  */
/*                                                                           */
/* When an argument is larger than the maximum alignment (8 bytes for double */
/* or long long), we only align to 8 bytes.                                  */
/*****************************************************************************/

/*---------------------------------------------------------------------------*/
/* What happens on every va_arg(_ap, _type) call is:                         */
/* 1) Align the value of _ap (the va_list pointer) appropriately for _type   */
/*    (the requested type).                                                  */
/* 2) Increment _ap appropriately for _type.                                 */
/* 3) Return the value desired by dereferencing _ap.                         */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* 1) Align _ap to satisfy alignment of _type.                               */
/* 2) Increment _ap by sizeof(_type)                                         */
/* 3) return *(ap-sizeof(_type))                                             */
/*                                                                           */
/* NOTE: We will re-evaluate the C7x struct-passing strategy in light of the */
/*       actual memory alignment requirements. See Jira COMPILE-415.         */
/*---------------------------------------------------------------------------*/
#define __TI_SIZEOF_PROMOTED_TYPE(_type)                                 \
        (__va_argref(_type) ? sizeof(void *) :                           \
         __va_argcsu(_type) ? __TI_SIZEOF_SCALAR_STR(_type) :            \
         (sizeof(_type) < 4) ? sizeof(int) : sizeof(_type))

#define __TI_ALIGNOF_SCALAR_STR(_type)                                   \
        ((sizeof(_type) >  4) ? 8 :                                      \
         (sizeof(_type) >  2) ? 4 :                                      \
         (sizeof(_type) >  1) ? 2 : 1)

#define __TI_ALIGNOF_PROMOTED_TYPE(_type)                                \
        (__va_argref(_type) ? __alignof__(_type *) :                     \
         __va_argcsu(_type) ? __TI_ALIGNOF_SCALAR_STR(_type) :           \
         (sizeof(_type) < 4) ? __alignof__(int) :                        \
                               __alignof__(_type))

#define __TI_ALIGN(e, _type)                                                \
        ((char *)(((unsigned long)(e) +                                     \
                  __TI_ALIGNOF_PROMOTED_TYPE(_type) - 1) &                  \
                 ~(__TI_ALIGNOF_PROMOTED_TYPE(_type) - 1)))

#define __TI_DEREF(e, _type)                                             \
        (__va_argref(_type) ? **(_type **)(e) : *(_type *)(e))

/*---------------------------------------------------------------------------*/
/* The big- and little-endian variants are different only because we are     */
/* trying to support the case of the user asking for "char" or "short",      */
/* which is actually undefined behavior (See ISO/IEC 9899:1999 7.15.1.1),    */
/* but we are trying to be friendly.                                         */
/*---------------------------------------------------------------------------*/

#ifdef _BIG_ENDIAN

#define __TI_BE_SIZEOF_UNPROMOTED_TYPE(_type)                            \
        (__va_argref(_type) ? sizeof(_type *) :                          \
         __va_argcsu(_type) ? __TI_SIZEOF_SCALAR_STR(_type) :            \
         (sizeof(_type)))

#define va_arg(_ap, _type)                                               \
        (_ap = __TI_ALIGN(_ap, _type),                                   \
         _ap += __TI_SIZEOF_PROMOTED_TYPE(_type),                        \
         __TI_DEREF(_ap - __TI_BE_SIZEOF_UNPROMOTED_TYPE(_type), _type))

#else

#define va_arg(_ap, _type)                                               \
        (_ap = __TI_ALIGN(_ap, _type),                                   \
         _ap += __TI_SIZEOF_PROMOTED_TYPE(_type),                        \
         __TI_DEREF(_ap - __TI_SIZEOF_PROMOTED_TYPE(_type), _type))

#endif /* _BIG_ENDIAN */

#endif /* defined(__TI_LLVM__) */

#pragma diag_pop

#endif /* _STDARG */

