
/*
 * Filename: swc_errorhandler.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * Description: Software component
 */

#ifndef _H_DEFINE_SWC_ERRORHANDLER
#define _H_DEFINE_SWC_ERRORHANDLER

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START SWC_ERRORHANDLER_INCLUDES */

/* USER CODE END SWC_ERRORHANDLER_INCLUDES */



/* USER CODE START SWC_ERRORHANDLER_USERDEFINITIONS */

/* USER CODE END SWC_ERRORHANDLER_USERDEFINITIONS */


/*
 * component: swc_errorHandler
 * cycletime: 0
 * description: Runnable
 * events: ev_ev_errorHandler
 * name: ERRORHANDLER_errorHandler_run
 * shortname: errorHandler
 * signalIN: 
 * signalOUT: 
 * task: tsk_errorHandling
 */
void ERRORHANDLER_errorHandler_run(RTE_event ev);


#endif