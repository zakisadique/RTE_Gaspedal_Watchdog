/*
 * Filename: tsk_output.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * description: Task contains all output operations. Engine, brake light
 * events: ev_speed_onData
 * mode: Cyclic and Event
 * name: tsk_output
 * shortname: output
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
#include "tsk_output.h"



/* USER CODE START TSK_OUTPUT_INCLUDE */

/* USER CODE END TSK_OUTPUT_INCLUDE */

#include "swc_output.h"



/* USER CODE START TSK_OUTPUT_USERDEFINITIONS */

/* USER CODE END TSK_OUTPUT_USERDEFINITIONS */

/*******************************************************************************
 * Runnable Tables from Activation Engine
 *******************************************************************************/

/* Cyclic Table */

const RTE_cyclicTable_t RTE_cyclicActivationTable_tsk_output[] = {
	{ OUTPUT_setEngine_run, 100 },	//Runnable
};
const uint16_t RTE_cyclicActivation_tsk_output_size = sizeof (RTE_cyclicActivationTable_tsk_output) / sizeof(RTE_cyclicTable_t); 

/* Event Table */
const RTE_eventTable_t RTE_eventActivationTable_tsk_output[] = {
    { OUTPUT_setBrakeLight_run, ev_speed_onData },  //Runnable
}; 
const uint16_t RTE_eventActivation_tsk_output_size = sizeof (RTE_eventActivationTable_tsk_output) / sizeof(RTE_eventTable_t);

/*******************************************************************************
 * Task Body
 *******************************************************************************/


/*
 * description: Task contains all output operations. Engine, brake light
 * events: ev_speed_onData
 * mode: Cyclic and Event
 * name: tsk_output
 * shortname: output
 * signalpoolsRO: sp_common
 * signalpoolsRW: sp_common
 * tickEvent: 0
 * timertickperiod: 1
 */
TASK(tsk_output)
{
	/* ticktime of the task */
	uint32_t ticktime = 0;
	
    EventMaskType ev = 0;
	
	/* USER CODE START TSK_OUTPUT_INIT */

	/* USER CODE END TSK_OUTPUT_INIT */
    
    while(1)
    {
        //Wait, read and clear the event
        WaitEvent(ev_speed_onData);
        GetEvent(tsk_output,&ev);
        ClearEvent(ev);
    
		/* USER CODE START TSK_OUTPUT_TASKBOBY_PRE */

		/* USER CODE END TSK_OUTPUT_TASKBODY_PRE */
        
        if (ev & 0){
            //Process Cyclic table on tick
            RTE_ProcessCyclicTable(RTE_cyclicActivationTable_tsk_output, RTE_cyclicActivation_tsk_output_size, ticktime);

			ticktime += 1;
			if (ticktime > 0xFFFFFF00) ticktime = 0;

		};
		
		//Process data driven events
		RTE_ProcessEventTable(RTE_eventActivationTable_tsk_output, RTE_eventActivation_tsk_output_size, ev);
		
		/* USER CODE START TSK_OUTPUT_TASKBODY_POST */

		/* USER CODE END TSK_OUTPUT_TASKBODY_POST */
        
    }
	
	//Just in Case
	TerminateTask();
}


/*******************************************************************************
 * Interrupt Service Routines
 *******************************************************************************/

/* USER CODE START TSK_OUTPUT_ISR */

/* USER CODE END TSK_OUTPUT_ISR */

