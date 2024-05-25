/**
* \file uart.h
* \author P. Fromm
* \date 8.12.19
*
* \brief uard wrapper driver
*
*
* \note Set the symbols in the cfg file to the port you want to use and configure the buffer size in the ringbuffer config file
*
* \todo <todos>
* \warning <warnings, e.g. dependencies, order of execution etc.>
*
*  Changelog:\n
*  - 1.0; 8.12.19; P. Fromm
*            - Initial Release
*
* \copyright Copyright ©2016
* Department of electrical engineering and information technology, Hochschule Darmstadt - University of applied sciences (h_da). All Rights Reserved.
* Permission to use, copy, modify, and distribute this software and its documentation for educational, and research purposes in the context of non-commercial
* (unless permitted by h_da) and official h_da projects, is hereby granted for enrolled students of h_da, provided that the above copyright notice,
* this paragraph and the following paragraph appear in all copies, modifications, and distributions.
* Contact Prof.Dr.-Ing. Peter Fromm, peter.fromm@h-da.de, Birkenweg 8 64295 Darmstadt - GERMANY for commercial requests.
*
* \warning This software is a PROTOTYPE version and is not designed or intended for use in production, especially not for safety-critical applications!
* The user represents and warrants that it will NOT use or redistribute the Software for such purposes.
* This prototype is for research purposes only. This software is provided "AS IS," without a warranty of any kind.
**/


 
#ifndef WATCHDOG_H
#define WATCHDOG_H

#include "global.h"

/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/
    
typedef enum {
    WATCHDOG_RUN_READJOYSTICK,
    WATCHDOG_RUN_CALCCONTROL,
    WATCHDOG_RUN_SETENGINE,
    WATCHDOG_RUN_SETBRAKELIGHT,
    WATCHDOG_RUN_LOGGING,
    WATCHDOG_RUN_SYSTEM
} WDT_Bits;
    
//typedef uint8_t WDT_Bits;

typedef struct{
    uint8_t    m_BitReadJoystick;	
    uint8_t    m_Bit_CalcControl;    
    uint8_t    m_Bit_SetEngine;     
    uint8_t    m_Bit_SetBrakelight;          
    uint8_t    m_Bit_Logging;            
    uint8_t    m_Bit_System;     
}WDT_Bitfields;
    
typedef enum {
    PERIOD_1_SEC,
    PERIOD_2_SEC,
    PERIOD_X_SEC,
    PERIOD_Y_SEC
} WDT_TimeOut_t;



//####################### Structures



// Wrapper to allow representing the file in Together as class
#ifdef TOGETHER

class Uart
{
public:
#endif /* Together */


/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/


RC_t WD_Start(WDT_TimeOut_t timeout);
RC_t WD_Trigger();
boolean_t WD_CheckResetBit();
RC_t WD_Alive(WDT_Bits bit);




/*****************************************************************************/
/* Private stuff, only visible for Together, declared static in cpp - File   */
/*****************************************************************************/


#ifdef TOGETHER
};
#endif /* Together */

#endif /* WATCHDOG_H */
