/*
 * Filename: tsk_errorhandler.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * description: Task doing work
 * events: ev_error
 * mode: Event
 * name: tsk_errorHandler
 * shortname: errorHandler
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
#include "tsk_errorhandler.h"



/* USER CODE START TSK_ERRORHANDLER_INCLUDE */

/* USER CODE END TSK_ERRORHANDLER_INCLUDE */

#include "swc_errorhandler.h"



/* USER CODE START TSK_ERRORHANDLER_USERDEFINITIONS */

/* USER CODE END TSK_ERRORHANDLER_USERDEFINITIONS */

/*******************************************************************************
 * Runnable Tables from Activation Engine
 *******************************************************************************/

/* Event Table */
const RTE_eventTable_t RTE_eventActivationTable_tsk_errorhandler[] = {
    { ERRORHANDLER_errorHandler_run, ev_error },  //Runnable
}; 
const uint16_t RTE_eventActivation_tsk_errorhandler_size = sizeof (RTE_eventActivationTable_tsk_errorhandler) / sizeof(RTE_eventTable_t);

/*******************************************************************************
 * Task Body
 *******************************************************************************/


/*
 * description: Task doing work
 * events: ev_error
 * mode: Event
 * name: tsk_errorHandler
 * shortname: errorHandler
 * signalpoolsRO: sp_common
 * signalpoolsRW: sp_common
 * tickEvent: 0
 * timertickperiod: 1
 */
TASK(tsk_errorhandler)
{
    EventMaskType ev = 0;
    
	/* USER CODE START TSK_ERRORHANDLER_INIT */

	/* USER CODE END TSK_ERRORHANDLER_INIT */
	
    while(1)
    {
        //Wait, read and clear the event
        WaitEvent(ev_error);
        GetEvent(tsk_errorhandler,&ev);
        ClearEvent(ev);
		
		/* USER CODE START TSK_ERRORHANDLER_TASKBOBY_PRE */

		/* USER CODE END TSK_ERRORHANDLER_TASKBODY_PRE */
    

        //Process Event table on event
        RTE_ProcessEventTable(RTE_eventActivationTable_tsk_errorhandler, RTE_eventActivation_tsk_errorhandler_size, ev);
		
		/* USER CODE START TSK_ERRORHANDLER_TASKBODY_POST */

		/* USER CODE END TSK_ERRORHANDLER_TASKBODY_POST */

        
    }
	
	//Just in Case
	TerminateTask();
}


/*******************************************************************************
 * Interrupt Service Routines
 *******************************************************************************/

/* USER CODE START TSK_ERRORHANDLER_ISR */

/* USER CODE END TSK_ERRORHANDLER_ISR */

