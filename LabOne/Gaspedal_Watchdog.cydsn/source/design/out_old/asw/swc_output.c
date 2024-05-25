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

/* USER CODE END SWC_OUTPUT_INCLUDE */


#include "sp_common.h"

/* USER CODE START SWC_OUTPUT_USERDEFINITIONS */

/* USER CODE END SWC_OUTPUT_USERDEFINITIONS */



/*
 * component: swc_output
 * cycletime: 100
 * description: Runnable
 * events: 
 * name: OUTPUT_setEngine_run
 * shortname: setEngine
 * signalIN: so_speed
 * signalOUT: so_engine
 * task: tsk_output
 */
void OUTPUT_setEngine_run(RTE_event ev){
	
	/* USER CODE START OUTPUT_setEngine_run */

    /* USER CODE END OUTPUT_setEngine_run */
}

/*
 * component: swc_output
 * cycletime: 0
 * description: Runnable
 * events: ev_speed_onData
 * name: OUTPUT_setBrakeLight_run
 * shortname: setBrakeLight
 * signalIN: so_speed
 * signalOUT: so_brakelight
 * task: tsk_output
 */
void OUTPUT_setBrakeLight_run(RTE_event ev){
	
	/* USER CODE START OUTPUT_setBrakeLight_run */

    /* USER CODE END OUTPUT_setBrakeLight_run */
}

/* USER CODE START SWC_OUTPUT_FUNCTIONS */

/* USER CODE END SWC_OUTPUT_FUNCTIONS */
