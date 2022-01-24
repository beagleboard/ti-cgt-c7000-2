;******************************************************************************
;* setjmp_512.asm                                                             *
;* Copyright (c) 2020       Texas Instruments Incorporated                    *
;******************************************************************************
;***************************************
;* Jump buffer layout (208 bytes):     *
;*                                     *
;* Reg:  |A8-A15|RP|VB15|VB14|SP|      *
;* Byte: 0     64 72  136  200 208     *
;*                                     *
;***************************************

;define offsets
||_A8||         .set 0
||_A9||         .set 8
||_A10||        .set 16
||_A11||        .set 24
||_A12||        .set 32
||_A13||        .set 40
||_A14||        .set 48
||_A15||        .set 56
||_RP||         .set 64
||_VB15||       .set 72
||_VB14||       .set 136
||_SP||         .set 200

        .sect   ".text:longjmp" 
        .global longjmp
longjmp: .asmfunc

;restore SOE A8-15
                LDD     .D1     *A4(||_A8||),A8
||              LDD     .D2     *A4(||_A9||),A9

                LDD     .D1     *A4(||_A10||),A10
||              LDD     .D2     *A4(||_A11||),A11

                LDD     .D1     *A4(||_A12||),A12
||              LDD     .D2     *A4(||_A13||),A13

                LDD     .D1     *A4(||_A14||),A14
||              LDD     .D2     *A4(||_A15||),A15

;restore RP value into A0 and VB15
                LDD     .D2     *A4(||_RP||),A0
||              VLD8D   .D1     *A4(||_VB15||),VB15

;restore VB14 and SP
                VLD8D   .D1     *A4(||_VB14||),VB14
||              LDD     .D2     *A4(||_SP||),D15
||              MVC     .S1     A0,RP

;check if int in 2nd arg is 0, if so set to 1   
    [!A5]       MVK64   .L1     1,A4
||  [A5]        MV      .D1     A5,A4   
||              RET     .B1

        .endasmfunc
        
        .sect   ".text:setjmp"         
        .global  setjmp
setjmp: .asmfunc
        
;save all SOE to buffer (pointer in A4)
        MVC     .S1     RP,A0
||      STD     .D1     A8,*A4(||_A8||)       

        STD     .D1     A0,*A4(||_RP||)
||      VST8D   .D2     VB15,*A4(||_VB15||) 

        STD     .D1     A9, *A4(||_A9||) 
||      VST8D   .D2     VB14,*A4(||_VB14||)

        STD     .D1     A10,*A4(||_A10||)        
||      STD     .D2X    A11,*A4(||_A11||)       
        
        STD     .D1     A12,*A4(||_A12||)      
||      STD     .D2X    A13,*A4(||_A13||)      
        
        STD     .D1     A14,*A4(||_A14||)      
||      STD     .D2X    A15,*A4(||_A15||)      

;store SP and return 0
        STD     .D1     D15,*A4(||_SP||)        
||      MVK64   .L1     0x0, A4 
||      RET     .B1

        .endasmfunc
