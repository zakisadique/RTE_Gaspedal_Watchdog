
/*
 * Filename: tsk_input.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * Description: Task where inputs are handled
 */

#ifndef _H_DEFINE_TSK_INPUT
#define _H_DEFINE_TSK_INPUT

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START TSK_INPUT_INCLUDES */

/* USER CODE END TSK_INPUT_INCLUDES */



/*
 * description: Task where inputs are handled
 * events: 
 * mode: Cyclic
 * name: tsk_input
 * shortname: input
 * signalpoolsRO: sp_common
 * signalpoolsRW: sp_common
 * tickEvent: 0
 * timertickperiod: 1
 */
DeclareTask(tsk_input);

/* USER CODE START TSK_INPUT_TASKUSERFUNCTION */

/* USER CODE END TSK_INPUT_TASKUSERFUNCTION */


#endif