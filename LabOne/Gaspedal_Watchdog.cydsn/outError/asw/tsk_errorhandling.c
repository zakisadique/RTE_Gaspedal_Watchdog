/*
 * Filename: tsk_errorhandling.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * description: Task doing work
 * events: ev_ev_errorHandler
 * mode: System
 * name: tsk_errorHandling
 * shortname: errorHandling
 * signalpoolsRO: sp_common
 * signalpoolsRW: sp_common
 * tickEvent: 0
 * timertickperiod: 1
 *
 */

#include "project.h"
#include "global.h"
#include "rte.h"
#include "rte_types.h"
#include "tsk_errorhandling.h"



/* USER CODE START TSK_ERRORHANDLING_INCLUDE */

/* USER CODE END TSK_ERRORHANDLING_INCLUDE */

#include "swc_errorhandler.h"



/* USER CODE START TSK_ERRORHANDLING_USERDEFINITIONS */

/* USER CODE END TSK_ERRORHANDLING_USERDEFINITIONS */

/*******************************************************************************
 * Runnable Tables from Activation Engine
 *******************************************************************************/


/*******************************************************************************
 * Task Body
 *******************************************************************************/


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
TASK(tsk_errorhandling)
{
	//Increment the age of all signals
	//Ticktime of the task: 1 ms
    
	/* USER CODE START TSK_ERRORHANDLING_TASKBOBY_PRE */

	/* USER CODE END TSK_ERRORHANDLING_TASKBODY_PRE */
	
    // tick for signalpool sp_common
    RTE_timertick_sp_common_tick(1);
    
    /* USER CODE START TSK_ERRORHANDLING_TASKBODY_POST */

    /* USER CODE END TSK_ERRORHANDLING_TASKBODY_POST */
	
	TerminateTask();
}

/*******************************************************************************
 * Interrupt Service Routines
 *******************************************************************************/

/* USER CODE START TSK_ERRORHANDLING_ISR */

/* USER CODE END TSK_ERRORHANDLING_ISR */
