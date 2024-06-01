
/*
 * Filename: tsk_errorhandling.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * Description: Task doing work
 */

#ifndef _H_DEFINE_TSK_ERRORHANDLING
#define _H_DEFINE_TSK_ERRORHANDLING

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START TSK_ERRORHANDLING_INCLUDES */

/* USER CODE END TSK_ERRORHANDLING_INCLUDES */



/*
 * description: Task doing work
 * events: ev_ev_errorHandler
 * mode: System
 * name: tsk_errorHandling
 * shortname: errorHandling
 * signalpoolsRO: sp_common
 * signalpoolsRW: sp_common
 * tickEvent: 0
 * timertickperiod: 1
 */
DeclareTask(tsk_errorhandling);

/* USER CODE START TSK_ERRORHANDLING_TASKUSERFUNCTION */

/* USER CODE END TSK_ERRORHANDLING_TASKUSERFUNCTION */


#endif