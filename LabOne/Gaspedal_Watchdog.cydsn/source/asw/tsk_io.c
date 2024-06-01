/*
 * Filename: tsk_io.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * description: Task where inputs and outputs are handled. Peripheral In/Out
 * events: ev_speed_onData|ev_tick_10ms
 * mode: Cyclic and Event
 * name: tsk_io
 * shortname: io
 * signalpoolsRO: sp_common
 * signalpoolsRW: sp_common
 * tickEvent: ev_tick_10ms
 * timertickperiod: 10
 *
 */

#include "project.h"
#include "global.h"
#include "rte.h"
#include "rte_types.h"
#include "tsk_io.h"



/* USER CODE START TSK_IO_INCLUDE */

/* USER CODE END TSK_IO_INCLUDE */

#include "swc_input.h"
#include "swc_output.h"



/* USER CODE START TSK_IO_USERDEFINITIONS */



/* USER CODE END TSK_IO_USERDEFINITIONS */

/*******************************************************************************
 * Runnable Tables from Activation Engine
 *******************************************************************************/

/* Cyclic Table */

const RTE_cyclicTable_t RTE_cyclicActivationTable_tsk_io[] = {
	{ INPUT_readJoystick_run, 20 },	//takes input from joystick
	{ OUTPUT_setEngine_run, 100 },	//Sets Green LED according to Engine Speed
};
const uint16_t RTE_cyclicActivation_tsk_io_size = sizeof (RTE_cyclicActivationTable_tsk_io) / sizeof(RTE_cyclicTable_t); 

/* Event Table */
const RTE_eventTable_t RTE_eventActivationTable_tsk_io[] = {
    { OUTPUT_setBrakeLight_run, ev_speed_onData },  //Sets LED according to brake condition
}; 
const uint16_t RTE_eventActivation_tsk_io_size = sizeof (RTE_eventActivationTable_tsk_io) / sizeof(RTE_eventTable_t);

/*******************************************************************************
 * Task Body
 *******************************************************************************/


/*
 * description: Task where inputs and outputs are handled. Peripheral In/Out
 * events: ev_speed_onData|ev_tick_10ms
 * mode: Cyclic and Event
 * name: tsk_io
 * shortname: io
 * signalpoolsRO: sp_common
 * signalpoolsRW: sp_common
 * tickEvent: ev_tick_10ms
 * timertickperiod: 10
 */
TASK(tsk_io)
{
	/* ticktime of the task */
	uint32_t ticktime = 0;
	
    EventMaskType ev = 0;
	
	/* USER CODE START TSK_IO_INIT */
    


	/* USER CODE END TSK_IO_INIT */
    
    while(1)
    {
        //Wait, read and clear the event
        WaitEvent(ev_speed_onData|ev_tick_10ms);
        GetEvent(tsk_io,&ev);
        ClearEvent(ev);
    
		/* USER CODE START TSK_IO_TASKBOBY_PRE */
        SetRelAlarm(alrm_error_io, 10, 0);
		/* USER CODE END TSK_IO_TASKBODY_PRE */
        
        if (ev & ev_tick_10ms){
            //Process Cyclic table on tick
            RTE_ProcessCyclicTable(RTE_cyclicActivationTable_tsk_io, RTE_cyclicActivation_tsk_io_size, ticktime);

			ticktime += 20;
			if (ticktime > 0xFFFFFF00) ticktime = 0;

		};
		
		//Process data driven events
		RTE_ProcessEventTable(RTE_eventActivationTable_tsk_io, RTE_eventActivation_tsk_io_size, ev);
		
		/* USER CODE START TSK_IO_TASKBODY_POST */
        CancelAlarm(alrm_error_io);
		/* USER CODE END TSK_IO_TASKBODY_POST */
        
    }
	
	//Just in Case
	TerminateTask();
}


/*******************************************************************************
 * Interrupt Service Routines
 *******************************************************************************/

/* USER CODE START TSK_IO_ISR */

/* USER CODE END TSK_IO_ISR */

