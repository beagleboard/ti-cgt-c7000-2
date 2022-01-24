#include "c7x.h"
#include "stdint.h"

/*----------------------------------------------------------------------------*/
/* Func: __lut_set_param                                                      */
/*                                                                            */
/* Args: __sLTCRFlags_t *pLTCR                                                */
/*            - Pointer to __sLTCRFlags_t structure.                          */
/*                                                                            */
/* Return: Returns a 32bit value packed with LTCR flags                       */
/*                                                                            */
/* Desc: This function is used to set the LTCR flags. The options are         */
/*       read from structure pointer and packed.                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/
uint32_t __lut_set_param(__sLTCRFlags_t *pLTCRFlags)
{
    uint32_t ctrVal = 0;

    /*------------------------------------------------------------------------*/
    /* Pack the flags as per spec as a 32bit value.                           */
    /*------------------------------------------------------------------------*/
    ctrVal = ((pLTCRFlags->NUMTBLS        & 0x07)  << 0)  |
             ((pLTCRFlags->ELETYPE        & 0x07)  << 3)  |
             ((pLTCRFlags->SIGNUNSIGN     & 0x01)  << 6)  |
             ((pLTCRFlags->SATURATION     & 0x01)  << 7)  |
             ((pLTCRFlags->INTERPOLATION  & 0x07)  << 8)  |
             ((pLTCRFlags->WEIGHTSIZE     & 0x07)  << 11) |
             ((pLTCRFlags->TBLSIZE        & 0x0ff) << 16) |
             ((pLTCRFlags->PROMOTION      & 0x03)  << 24);

    return ctrVal;
}
