;******************************************************************************
;* tdeh_uwentry_c7000_512.asm                                                 *
;* Copyright (c) 2016       Texas Instruments Incorporated                    *
;******************************************************************************

        .cdecls CPP, LIST, "tdeh_c7000.h"

        .asg    D15, SP

        .global _Unwind_RaiseException
        .ref    __TI_Unwind_RaiseException

;------------------------------------------------------------------------------
; _Unwind_RaiseException - wrapper for C function __TI_Unwind_RaiseException
;
; _Unwind_Reason_Code _Unwind_RaiseException(_Unwind_Exception *);
;
; _Unwind_Reason_Code __TI_Unwind_RaiseException(_Unwind_Exception *uexcep,
;                                                _Unwind_Context   *context);
;------------------------------------------------------------------------------
; This function is the language-independent starting point for
; propagating an exception.  It is called by __cxa_throw.
;
; This function needs to capture the state of the caller, which means
; all of the SOE registers (including DP and SP) as well as the return
; address.  (The stack unwinder finds the data for the caller by
; looking up the return address in the EXIDX table to find the
; "apparently throwing call site.")
;
; The state is saved in an array allocated on the stack, which is
; passed as the second argument to __TI_Unwind_RaiseException.
;------------------------------------------------------------------------------

_Unwind_RaiseException: .asmfunc

        ; Unwind_RaiseException must call TI_Unwind_RaiseException
        ; Unwind_Resume must call TI_Unwind_Resume
        ; However, both have the same functionality, so set A2 accordingly
        ; for each and CALLA as needed.
        ADDKPC  .D1    $PCR_OFFSET(__TI_Unwind_RaiseException), A2

_Unwind_Resume_Entry:

        MV      .D1   SP,A0             ; Grab caller's SP as it is on entry
||      MVC     .S1   RP,A1             ; Grab RP's value now
||      MVK64   .L1   TI_UNWIND_RET, A3 ; Set return pointer in case of failure

        ; Room on the stack is allocated below for the following regs,
        ; corresponding with the order and size of the "_Unwind_Register_Buffer"
        ; struct defined in tdeh_c7000.h:
        ;
        ; A8    - 8bytes  (SOE)
        ; A9    - 8bytes  (SOE)
        ; A10   - 8bytes  (SOE)
        ; A11   - 8bytes  (SOE)
        ; A12   - 8bytes  (SOE)
        ; A13   - 8bytes  (SOE)
        ; A14   - 8bytes  (SOE)
        ; A15   - 8bytes  (SOE)
        ; RP    - 8bytes  (Return Pointer - saved later)
        ; VB15  - 64bytes (SOE)
        ; VB14  - 64bytes (SOE)
        ; A4    - 8bytes  (Arg/Parameter & Return Value Register - saved later)
        ; SP    - 8bytes  (Stack Pointer)
        ; PC    - 8bytes  (Program Counter)
        ;
        ; The frame's 16 free byte block is used to store SP and PC, and 224
        ; bytes is allocated for the rest of the stack frame, made up of:
        ;
        ; New free byte block:   16  bytes
        ; A8-A15,RP:           + 72  bytes
        ; VB15:                + 64  bytes
        ; VB14:                + 64  bytes
        ;   A4:                +  8  bytes
        ; --------------------------------
        ;                      = 224 bytes

        ; Begin storing SOEs:
        STD     .D1   A0,*SP++(-224)    ; Store caller's SP to register buffer
||      STD     .D2X  A1,*SP(8)         ; Store RP as "PC" in buffer

        ; Unwind_reg_Id's are offsets from the top of the buffer, the buffer
        ; sits at an offset of +2 from SP

        STD     .D1   A15,*SP[_Unwind_Reg_Id._UR_A15 + 2]
||      STD     .D2X  A14,*SP[_Unwind_Reg_Id._UR_A14 + 2]
||      MVC     .S1   A3, RP            ; RP is now TI_UNWIND_RET

        VST8D  .D2   VB14,*SP[_Unwind_Reg_Id._UR_VB14_Offset + 2]
||      STD    .D1   A13,*SP[_Unwind_Reg_Id._UR_A13 + 2]

        VST8D  .D2   VB15,*SP[_Unwind_Reg_Id._UR_VB15 + 2]
||      STD    .D1   A12,*SP[_Unwind_Reg_Id._UR_A12 + 2]

        STD    .D1   A11,*SP[_Unwind_Reg_Id._UR_A11 + 2]
||      STD    .D2X  A10,*SP[_Unwind_Reg_Id._UR_A10 + 2]

        STD    .D1   A9,*SP[_Unwind_Reg_Id._UR_A9 + 2]
||      STD    .D2X  A8,*SP[_Unwind_Reg_Id._UR_A8 + 2]

        ADDD   .D1   SP,16,A5           ; Grab ptr to context, save as 2nd arg
||      CALLA  .S1   A2

TI_UNWIND_RET:

       ; Only get here if __TI_Unwind_RaiseException experiences an error
       ; Return control to the caller whose return value is stored in _UR_PC

       LDD     .D1  *SP[_Unwind_Reg_Id._UR_PC_Offset + 2], A0

       MVC     .S1   A0,RP
||     ADDD    .D1   SP,224,SP                      ; Restore stack

       RET     .B1

       .endasmfunc


;------------------------------------------------------------------------------
; This function is a wrapper for the C function __TI_Unwind_Resume
;
; void _Unwind_Resume(_Unwind_Exception *);
;
; void __TI_Unwind_Resume(_Unwind_Exception *uexcep, _Unwind_Context *context);
;------------------------------------------------------------------------------
; This function is the language-independent "resume" function.  After
; each frame gets a chance to perform cleanup, this function is called
; to resume propagating the exception to the next call frame.  It is
; called by __cxa_end_cleanup, below.
;
; Creates a register buffer just as _Unwind_RaiseException does, but
; calls a different function afterward.  __TI_Unwind_Resume never returns.
;------------------------------------------------------------------------------

       .def _Unwind_Resume
       .ref __TI_Unwind_Resume


_Unwind_Resume: .asmfunc

        ADDKPC  .D1    $PCR_OFFSET(__TI_Unwind_Resume), A2

        B       .B1    _Unwind_Resume_Entry

       .endasmfunc

;------------------------------------------------------------------------------
; __TI_Install_CoreRegs - Set machine state to effect return, branch, or call
;
; void __TI_Install_CoreRegs(void *core_regs);
;------------------------------------------------------------------------------
; __TI_Install_CoreRegs is where the unwinder finally writes to the
; actual registers.  It is called when the actual registers need to be
; modified, such as when unwinding is completely done, or when handler
; code needs to be executed.  It called by __TI_targ_regbuf_install,
; which is just a wrapper for this function.  This function performs
; either a simulated return or a call to a cleanup/catch handler or
; __cxa_call_unexpected.
;
; __TI_targ_regbuf_install is eventually called from two places,
; __TI_Unwind_RaiseException and __TI_Unwind_Resume.
;
; __TI_Unwind_RaiseException calls __TI_unwind_frame to begin phase 2
; unwinding if a handler was found for the current exception.  (Phase
; 2 unwinding actually unwinds the stack and calls cleanup/catch
; handlers).  __TI_unwind_frame unwinds the frame until a
; cleanup/catch handler which needs to be run is found, at which point
; it calls __TI_targ_regbuf_install.  The pseudo-PC in the register
; buffer will have been set by the personality routine to the landing
; pad for the handler, so instead of performing a simulated return, we
; call the catch handler landing pad.  The very first thing the catch
; handler landing pad does is call __cxa_begin_catch, which takes one
; argument, the _Unwind_Exception pointer.  For this reason, this
; function needs to install A4 from the register buffer.
;
; During phase 2 unwinding, __cxa_end_cleanup calls _Unwind_Resume,
; which calls __TI_Unwind_Resume.  __TI_Unwind_Resume calls
; __TI_unwind_frame when the personality routine returns
; _URC_CONTINUE_UNWIND, and things proceed as when
; __TI_Unwind_RaiseException calls __TI_unwind_frame.
;
; __TI_Unwind_Resume will also call __TI_targ_regbuf_install if the
; personality routine returns _URC_INSTALL_CONTEXT.  This happens when
; a cleanup/catch/fespec handler is found.  The personality routine
; sets PC to the handler landing pad and A4 to the _Unwind_Context
; pointer.
;
; Additionally, for FESPEC, the personality routine may set PC to
; "__cxa_call_unexpected" and A4 to the _Unwind_Context pointer, and
; return _URC_INSTALL_CONTEXT, which results in a call to
; __cxa_call_unexpected.
;
; Returns to the location in "PC."
;------------------------------------------------------------------------------

        .def __TI_Install_CoreRegs

__TI_Install_CoreRegs: .asmfunc

        VLD8D  .D1    *A4[_Unwind_Reg_Id._UR_VB14_Offset], VB14
||      LDD    .D2    *A4[_Unwind_Reg_Id._UR_PC_Offset],   A0

        VLD8D  .D1    *A4[_Unwind_Reg_Id._UR_VB15],        VB15
||      LDD    .D2    *A4[_Unwind_Reg_Id._UR_RP],          A1

        MVC    .S1    A1,RP
||      LDD    .D1    *A4[_Unwind_Reg_Id._UR_A8],          A8
||      LDD    .D2    *A4[_Unwind_Reg_Id._UR_A9],          A9

        LDD    .D1    *A4[_Unwind_Reg_Id._UR_A10],         A10
||      LDD    .D2    *A4[_Unwind_Reg_Id._UR_A11],         A11

        LDD    .D1    *A4[_Unwind_Reg_Id._UR_A12],         A12
||      LDD    .D2    *A4[_Unwind_Reg_Id._UR_A13],         A13

        LDD    .D1    *A4[_Unwind_Reg_Id._UR_A14],         A14
||      LDD    .D2    *A4[_Unwind_Reg_Id._UR_A15],         A15

        LDD    .D1    *A4[_Unwind_Reg_Id._UR_SP_Offset],   SP
||      LDD    .D2    *A4[_Unwind_Reg_Id._UR_A4_Offset],   A4
||      BA     .S1    A0                ; This function does not return

       .endasmfunc

;------------------------------------------------------------------------------
; __cxa_end_cleanup - generic C++ helper function
;
; void __cxa_end_cleanup(void)
;
; _Unwind_Exception *__TI_cxa_end_cleanup(void);
;
; void _Unwind_Resume(_Unwind_Exception *);
;------------------------------------------------------------------------------
; __cxa_end_cleanup is a C++-specific function, called directly in
; compiler-generated code.  It calls __TI_cxa_end_cleanup to perform
; bookkeeping for foreign exceptions and exceptions thrown during
; cleanup.  It calls _Unwind_Resume to continue unwinding the stack.
;
; Saves/restores state to preserve changes made during destructors
; from changes made in the course of executing __TI_cxa_end_cleanup.
;------------------------------------------------------------------------------

       .def __cxa_end_cleanup
       .ref __TI_cxa_end_cleanup

__cxa_end_cleanup: .asmfunc

        ;----------------------------------------------------------------------
        ; This function must:
        ; 1. store SOEs on to the stack
        ; 2. call __TI_cxa_end_cleanup (1 and 3 are setup/teardown for this)
        ; 3. load SOEs from the stack
        ; 4. jump to Unwind_Resume
        ;----------------------------------------------------------------------

        ; make room for SOEs a8-a15, RP, VB15, VB14 and free 16 byte block
        ; 200 = 56 (scalar SOEs) + 128 (vector SOEs) + 16 (free byte block)
        STD    .D1   A9,*SP++(-200)
||      STD    .D2X  A8,*SP(8)

        VST8D  .D2   VB14,*SP[2]
||      MVC    .S1   RP,A1

        VST8D  .D2   VB15,*SP[10]
||      STD    .D1   A10,*SP[24]

        STD    .D1   A15,*SP[19]
||      STD    .D2X  A14,*SP[20]

        STD    .D1   A13,*SP[21]
||      STD    .D2X  A12,*SP[22]

        STD    .D1   A11,*SP[23]
||      STD    .D2X  A1, *SP[18]

        CALL   .B1    __TI_cxa_end_cleanup ; returns a value in A4

        LDD    .D2    *SP[18], A0
||      VLD8D  .D1    *SP[2],  VB14

        VLD8D  .D1    *SP[10], VB15
||      LDD    .D2    *SP[19], A15

        LDD    .D1    *SP[20], A14
||      LDD    .D2    *SP[21], A13

        LDD    .D1    *SP[22], A12
||      LDD    .D2    *SP[23], A11

        MVC    .S1    A0,RP
||      LDD    .D1    *SP[24], A10
||      LDD    .D2    *SP[25], A9

        LDD    .D2    *SP[26], A8
||      ADDD   .D1    SP, 200, SP
||      B      .B1    _Unwind_Resume

        .endasmfunc
