/*
 * Filename: swc_logging.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * description: Logging data on UART/TFT
 * name: swc_logging
 * shortname: logging
 *
 */

#include "project.h"
#include "global.h"
#include "rte.h"
#include "rte_types.h"
#include "swc_logging.h"



/* USER CODE START SWC_LOGGING_INCLUDE */

#include "stdio.h"

/* USER CODE END SWC_LOGGING_INCLUDE */


#include "sp_common.h"

/* USER CODE START SWC_LOGGING_USERDEFINITIONS */

RC_t convertToString(sint8_t number, char_t *buffer) {
    if (number <= 0){
        buffer[0] = '0';
        buffer[1] = '\0';
        return RC_SUCCESS;
    }
    
    int i = 0;

    /* Convert the number to a string in reverse order. */
    while (number != 0) {
        int digit = number % 10;
        buffer[i++] = digit + '0';
        number = number / 10;
    }

    /* Add null terminator to the end of the string. */
    buffer[i] = '\0';

    /* Reverse the string to get the correct order. */
    reverseString(buffer, i);

    return RC_SUCCESS;
}

RC_t reverseString(char_t *str, uint8_t length) {
    int start = 0;
    int end = length - 1;

    /* Swap characters from start to end to reverse the string. */
    while (start < end) {
        char_t temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        start++;
        end--;
    }

    return RC_SUCCESS;
}

/* USER CODE END SWC_LOGGING_USERDEFINITIONS */



/*
 * component: swc_logging
 * cycletime: 0
 * description: Runnable
 * events: 
 * name: LOGGING_logging_run
 * shortname: logging
 * signalIN: so_joystick
 * signalOUT: so_logging
 * task: tsk_logging
 */
void LOGGING_logging_run(RTE_event ev){
	
	/* USER CODE START LOGGING_logging_run */
//    UART_Logs_PutString("In Logging swc\n");
    
    volatile SC_JOYSTICK_data_t joystick = RTE_SC_JOYSTICK_get(&SO_JOYSTICK_signal);
    SC_LOGGING_data_t log = SC_LOGGING_INIT_DATA;
    
    sint8_t acceleratorValue = joystick.m_joystickValue;
    char buffer[100];
    buffer[0] = '\0';
    char intBuffer[5];
    convertToString(acceleratorValue, intBuffer);
    
//    char* str = "Accelerator Value: ";
//    strcat(buffer, str);
    strcat(buffer, intBuffer);
    strcat(buffer, "\n");
    
//    snprintf(buffer, sizeof(buffer), "Accelerator value: %d", acceleratorValue);
    log.m_loggingValue = buffer;
    log.dataSize = sizeof(buffer);
    
    RTE_SC_LOGGING_set(&SO_LOGGING_signal, log);
    RC_t error = RTE_SC_LOGGING_pushPort(&SO_LOGGING_signal);
    
//    RTE_SC_LOGGING_set(SC_
    
    /* USER CODE END LOGGING_logging_run */
}

/* USER CODE START SWC_LOGGING_FUNCTIONS */

/* USER CODE END SWC_LOGGING_FUNCTIONS */

