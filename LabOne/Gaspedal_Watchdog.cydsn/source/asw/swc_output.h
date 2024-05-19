
/*
 * Filename: swc_output.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * Description: engine and brakelights
 */

#ifndef _H_DEFINE_SWC_OUTPUT
#define _H_DEFINE_SWC_OUTPUT

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START SWC_OUTPUT_INCLUDES */

/* USER CODE END SWC_OUTPUT_INCLUDES */



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
void OUTPUT_setEngine_run(RTE_event ev);

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
void OUTPUT_setBrakeLight_run(RTE_event ev);


#endif