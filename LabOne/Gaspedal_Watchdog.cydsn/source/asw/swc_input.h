
/*
 * Filename: swc_input.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * Description: Input
 */

#ifndef _H_DEFINE_SWC_INPUT
#define _H_DEFINE_SWC_INPUT

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START SWC_INPUT_INCLUDES */

/* USER CODE END SWC_INPUT_INCLUDES */



/* USER CODE START SWC_INPUT_USERDEFINITIONS */

/* USER CODE END SWC_INPUT_USERDEFINITIONS */


/*
 * component: swc_input
 * cycletime: 10
 * description: takes input from joystick
 * events: 
 * name: INPUT_readJoystick_run
 * shortname: readJoystick
 * signalIN: 
 * signalOUT: so_joystick
 * task: tsk_io
 */
void INPUT_readJoystick_run(RTE_event ev);


#endif