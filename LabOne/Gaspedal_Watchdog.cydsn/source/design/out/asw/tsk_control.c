/*
 * Filename: tsk_control.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * description: Task where logic is performed
 * events: ev_joystick_onData
 * mode: Event
 * name: tsk_control
 * shortname: control
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
#include "tsk_control.h"



/* USER CODE START TSK_CONTROL_INCLUDE */

/* USER CODE END TSK_CONTROL_INCLUDE */

#include "swc_control.h"



/* USER CODE START TSK_CONTROL_USERDEFINITIONS */

/* USER CODE END TSK_CONTROL_USERDEFINITIONS */

/*******************************************************************************
 * Runnable Tables from Activation Engine
 *******************************************************************************/

/* Event Table */
const RTE_eventTable_t RTE_eventActivationTable_tsk_control[] = {
    { CONTROL_calcControl_run, ev_joystick_onData },  //Runnable
}; 
const uint16_t RTE_eventActivation_tsk_control_size = sizeof (RTE_eventActivationTable_tsk_control) / sizeof(RTE_eventTable_t);

/*******************************************************************************
 * Task Body
 *******************************************************************************/


/*
 * description: Task where logic is performed
 * events: ev_joystick_onData
 * mode: Event
 * name: tsk_control
 * shortname: control
 * signalpoolsRO: sp_common
 * signalpoolsRW: sp_common
 * tickEvent: 0
 * timertickperiod: 1
 */
TASK(tsk_control)
{
    EventMaskType ev = 0;
    
	/* USER CODE START TSK_CONTROL_INIT */

	/* USER CODE END TSK_CONTROL_INIT */
	
    while(1)
    {
        //Wait, read and clear the event
        WaitEvent(ev_joystick_onData);
        GetEvent(tsk_control,&ev);
        ClearEvent(ev);
		
		/* USER CODE START TSK_CONTROL_TASKBOBY_PRE */

		/* USER CODE END TSK_CONTROL_TASKBODY_PRE */
    

        //Process Event table on event
        RTE_ProcessEventTable(RTE_eventActivationTable_tsk_control, RTE_eventActivation_tsk_control_size, ev);
		
		/* USER CODE START TSK_CONTROL_TASKBODY_POST */

		/* USER CODE END TSK_CONTROL_TASKBODY_POST */

        
    }
	
	//Just in Case
	TerminateTask();
}


/*******************************************************************************
 * Interrupt Service Routines
 *******************************************************************************/

/* USER CODE START TSK_CONTROL_ISR */

/* USER CODE END TSK_CONTROL_ISR */

