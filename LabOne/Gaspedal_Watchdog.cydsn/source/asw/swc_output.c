/*
 * Filename: swc_output.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * description: engine and brakelights
 * name: swc_output
 * shortname: output
 *
 */

#include "project.h"
#include "global.h"
#include "rte.h"
#include "rte_types.h"
#include "swc_output.h"



/* USER CODE START SWC_OUTPUT_INCLUDE */
#include "watchdog.h"

/* USER CODE END SWC_OUTPUT_INCLUDE */


#include "sp_common.h"

/* USER CODE START SWC_OUTPUT_USERDEFINITIONS */

/* USER CODE END SWC_OUTPUT_USERDEFINITIONS */



/*
 * component: swc_output
 * cycletime: 100
 * description: Sets Green LED according to Engine Speed
 * events: 
 * name: OUTPUT_setEngine_run
 * shortname: setEngine
 * signalIN: so_speed
 * signalOUT: so_engine
 * task: tsk_io
 */
void OUTPUT_setEngine_run(RTE_event ev){
	
	/* USER CODE START OUTPUT_setEngine_run */
    
//    UART_Logs_PutString("In Engine\n");
//    UART_Logs_PutChar(SO_SPEED_signal.age);
//    UART_Logs_PutString("\n"); 
    
    SC_SPEED_data_t speed = RTE_SC_SPEED_get(&SO_SPEED_signal);
    SC_ENGINE_data_t engine = SC_ENGINE_INIT_DATA;
    
    if (RTE_SC_SPEED_getAge(&SO_SPEED_signal) < 50){
        engine.m_engineValue = speed.m_speedValue;
    } else {
        engine.m_engineValue = 0;
    }
    
    RTE_SC_ENGINE_set(&SO_ENGINE_signal, engine);
    RC_t error = RTE_SC_ENGINE_pushPort(&SO_ENGINE_signal);
    
    WD_Alive(WATCHDOG_RUN_SETENGINE);

    /* USER CODE END OUTPUT_setEngine_run */
}

/*
 * component: swc_output
 * cycletime: 0
 * description: Sets LED according to brake condition
 * events: ev_speed_onData
 * name: OUTPUT_setBrakeLight_run
 * shortname: setBrakeLight
 * signalIN: so_speed
 * signalOUT: so_brakelight
 * task: tsk_io
 */
void OUTPUT_setBrakeLight_run(RTE_event ev){
	
	/* USER CODE START OUTPUT_setBrakeLight_run */
    
//    UART_Logs_PutString("In Brakelight\n");
    
    
    volatile SC_SPEED_data_t speed = RTE_SC_SPEED_get(&SO_SPEED_signal);
    SC_BRAKELIGHT_data_t brake = SC_BRAKELIGHT_INIT_DATA;
    if (speed.m_speedValue <= 0){
        brake.m_brakeValue = TRUE;
    }
    RTE_SC_BRAKELIGHT_set(&SO_BRAKELIGHT_signal, brake);
    RC_t error = RTE_SC_BRAKELIGHT_pushPort(&SO_BRAKELIGHT_signal);
    WD_Alive(WATCHDOG_RUN_SETBRAKELIGHT);

    /* USER CODE END OUTPUT_setBrakeLight_run */
}

/* USER CODE START SWC_OUTPUT_FUNCTIONS */

/* USER CODE END SWC_OUTPUT_FUNCTIONS */

