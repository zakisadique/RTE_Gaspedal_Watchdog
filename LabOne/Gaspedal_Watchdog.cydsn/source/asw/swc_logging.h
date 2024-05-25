
/*
 * Filename: swc_logging.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * Description: Logging data on UART/TFT
 */

#ifndef _H_DEFINE_SWC_LOGGING
#define _H_DEFINE_SWC_LOGGING

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START SWC_LOGGING_INCLUDES */

/* USER CODE END SWC_LOGGING_INCLUDES */



/* USER CODE START SWC_LOGGING_USERDEFINITIONS */
    
    RC_t convertToString(sint8_t number, char_t *buffer);
    RC_t reverseString(char_t *str, uint8_t length);
    
/* USER CODE END SWC_LOGGING_USERDEFINITIONS */


/*
 * component: swc_logging
 * cycletime: 0
 * description: Runnable
 * events: ev_joystick_onData
 * name: LOGGING_logging_run
 * shortname: logging
 * signalIN: so_joystick
 * signalOUT: so_logging
 * task: tsk_logging
 */
void LOGGING_logging_run(RTE_event ev);


#endif