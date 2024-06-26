/**
* \file uart.c
* \author P. Fromm
* \date 8.12.19
*
* \brief UART wrapper
*
* \copyright Copyright �2016
* Department of electrical engineering and information technology, Hochschule Darmstadt - University of applied sciences (h_da). All Rights Reserved.
* Permission to use, copy, modify, and distribute this software and its documentation for educational, and research purposes in the context of non-commercial
* (unless permitted by h_da) and official h_da projects, is hereby granted for enrolled students of h_da, provided that the above copyright notice,
* this paragraph and the following paragraph appear in all copies, modifications, and distributions.
* Contact Prof.Dr.-Ing. Peter Fromm, peter.fromm@h-da.de, Birkenweg 8 64295 Darmstadt - GERMANY for commercial requests.
*
* \warning This software is a PROTOTYPE version and is not designed or intended for use in production, especially not for safety-critical applications!
* The user represents and warrants that it will NOT use or redistribute the Software for such purposes.
* This prototype is for research purposes only. This software is provided "AS IS," without a warranty of any kind.
*/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/

#include "project.h"
#include "watchdog.h"
#include "tft.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/



/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

//WDT_Bitfields wdtBitfields = {0};

boolean_t wdtBitfields[NUMBER_OF_WATCHDOGS] = {0};

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/



/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/
RC_t WD_Start(WDT_TimeOut_t timeout){
    
    switch (timeout){
        case PERIOD_1024_TICK:
            CyWdtStart(CYWDT_1024_TICKS, 0);
            break;
        case PERIOD_128_TICK:
            CyWdtStart(CYWDT_128_TICKS, 0);
            break;
        case PERIOD_16_TICK:
            CyWdtStart(CYWDT_16_TICKS, 0);
            break;
        case PERIOD_2_TICK:
            CyWdtStart(CYWDT_2_TICKS, 0);
            break;
    }
        
    return RC_SUCCESS;
}

RC_t WD_Trigger(){
    CyWdtClear();
    return RC_SUCCESS;
}

boolean_t WD_CheckResetBit() {
    
    if (CyResetStatus & CY_RESET_WD){
        return TRUE;
    } else {
        return FALSE;
    }
}

RC_t WD_Alive(WDT_Bits_t bit){
    

    wdtBitfields[bit] = TRUE;
    return RC_SUCCESS;
    
    
}

boolean_t WD_IsError(){
    
    for (uint8_t i = 0; i < NUMBER_OF_WATCHDOGS; ++i){
        if (wdtBitfields[i] == FALSE){
            return TRUE;
        
        }
    
    }
    return FALSE;

}

RC_t WD_resetState(){
    for (uint8_t i = 0; i < NUMBER_OF_WATCHDOGS; ++i){
        wdtBitfields[i] = FALSE;
    }
    
    return RC_SUCCESS;
}

RC_t WD_displayInitialMessage(){
    if (WD_CheckResetBit() == TRUE){
        UART_Logs_PutString("Rebooted after watchdog reset\n");
        
        TFT_print((char_t*)"Rebooted after watchdog reset");
    } else {
        UART_Logs_PutString("Rebooted after power on reset\n");
        TFT_print((char_t*)"Rebooted after power on reset");
    }
}
