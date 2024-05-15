#Path: asw/{{name}}
{% extends "c_base.c" %}
{% block content %}
{% for swc in data.swcs|unique -%}
#include "{{swc.lower().replace(" ","_")}}.h"
{% endfor %}


/* USER CODE START {{name.upper()}}_USERDEFINITIONS */

/* USER CODE END {{name.upper()}}_USERDEFINITIONS */

/*******************************************************************************
 * Runnable Tables from Activation Engine
 *******************************************************************************/
{% if data.mode in ["Cyclic","Cyclic and Event"] %}
/* Cyclic Table */

const RTE_cyclicTable_t RTE_cyclicActivationTable_{{name}}[] = {
    {%- for runnable in data.runnables %} 
		{%- if runnable.cycletime != "0" %}
	{ {{runnable.name}}, {{runnable.cycletime}} },	//{{runnable.description}} 
		{%- endif %}
	{%- endfor %}
};
const uint16_t RTE_cyclicActivation_{{name}}_size = sizeof (RTE_cyclicActivationTable_{{name}}) / sizeof(RTE_cyclicTable_t); 
{% endif -%}
{% if data.mode in ["Event","Cyclic and Event"] %}
/* Event Table */
const RTE_eventTable_t RTE_eventActivationTable_{{name}}[] = { 
   {%- for runnable in data.runnables %}
		{%- if runnable.events != "" %}
		{%- for event in  runnable.events.split("|") %}
    { {{runnable.name}}, {{event}} },  //{{runnable.description}} 
		{%- endfor %}
		{%- endif %}
	{%- endfor %}
}; 
const uint16_t RTE_eventActivation_{{name}}_size = sizeof (RTE_eventActivationTable_{{name}}) / sizeof(RTE_eventTable_t); 
{%- endif %}

/*******************************************************************************
 * Task Body
 *******************************************************************************/

{% if data.mode == "Event" %}
{{ macros.descrBlock(data) }}
void {{name}}(void *pvParameter)
{
	(void)pvParameter;
    EventBits_t ev = 0;
    
    while(1)
    {
        //Wait, read and clear the event
		ev = xEventGroupWaitBits(event, {{data.events}}, true, false, -1);
		
		/* USER CODE START {{name.upper()}}_TASKBOBY_PRE */

		/* USER CODE END {{name.upper()}}_TASKBODY_PRE */
    

        //Process Event table on event
        RTE_ProcessEventTable(RTE_eventActivationTable_{{name}}, RTE_eventActivation_{{name}}_size, ev);
		
		/* USER CODE START {{name.upper()}}_TASKBODY_POST */

		/* USER CODE END {{name.upper()}}_TASKBODY_POST */
        
    }
	vTaskDelete(NULL);
}
{% endif -%}
{% if data.mode == "Cyclic" %}
{{ macros.descrBlock(data) }}
void {{name}}(void *pvParameter)
{
	(void)pvParameter;
	/* ticktime of the task */
	static uint32_t ticktime = 0;
	TickType_t PreviousWakeTime = xTaskGetTickCount();
	
	while(1)
	{

		/* USER CODE START {{name.upper()}}_TASKBOBY_PRE */

		/* USER CODE END {{name.upper()}}_TASKBODY_PRE */
		
		//Process all cyclic runnables which are due
		RTE_ProcessCyclicTable(RTE_cyclicActivationTable_{{name}}, RTE_cyclicActivation_{{name}}_size, ticktime);
		
		/* USER CODE START {{name.upper()}}_TASKBODY_POST */

		/* USER CODE END {{name.upper()}}_TASKBODY_POST */

		ticktime += {{data.timertickperiod}};
		if (ticktime > 0xFFFFFF00) ticktime = 0;
		
		vTaskDelayUntil(&PreviousWakeTime, pdMS_TO_TICKS({{data.timertickperiod}}));
	}
    
}
{% endif -%}
{% if data.mode == "Cyclic and Event" %}
{{ macros.descrBlock(data) }}
void {{name}}(void *pvParameter)
{
	(void)pvParameter;
	/* ticktime of the task */
	static uint32_t ticktime = 0;
	
    EventBits_t ev = 0;
    
    while(1)
    {
        //Wait, read and clear the event
		ev = xEventGroupWaitBits(event, {{data.events}}, true, false, -1);
    
		/* USER CODE START {{name.upper()}}_TASKBOBY_PRE */

		/* USER CODE END {{name.upper()}}_TASKBODY_PRE */
        
        if (ev & {{data.tickEvent}}){
            //Process Cyclic table on tick
            RTE_ProcessCyclicTable(RTE_cyclicActivationTable_{{name}}, RTE_cyclicActivation_{{name}}_size, ticktime);

			ticktime += {{data.timertickperiod}};
			if (ticktime > 0xFFFFFF00) ticktime = 0;

		};
		
		//Process data driven events
		RTE_ProcessEventTable(RTE_eventActivationTable_{{name}}, RTE_eventActivation_{{name}}_size, ev);
		
		/* USER CODE START {{name.upper()}}_TASKBODY_POST */

		/* USER CODE END {{name.upper()}}_TASKBODY_POST */

        
    }
}
{% endif -%}
{% if data.mode == "System" %}
#include "sp_common.h"
{{ macros.descrBlock(data) }}
void {{name}}(void *pvParameter)
{
	(void)pvParameter;
	/* ticktime of the task */
	TickType_t PreviousWakeTime = xTaskGetTickCount();
	while(1)
	{
		//Increment the age of all signals
		//Ticktime of the task: {{data.timertickperiod}} ms
		
		/* USER CODE START {{name.upper()}}_TASKBOBY_PRE */

		/* USER CODE END {{name.upper()}}_TASKBODY_PRE */
		
		{% for sigpool in allData.signalpools -%}
		// tick for signalpool {{sigpool.signalpool.name}}
		RTE_timertick_{{sigpool.signalpool.name}}_tick({{data.timertickperiod}});
		{% endfor %}
		/* USER CODE START {{name.upper()}}_TASKBODY_POST */

		/* USER CODE END {{name.upper()}}_TASKBODY_POST */
		vTaskDelayUntil(&PreviousWakeTime, pdMS_TO_TICKS({{data.timertickperiod}}));
	}
}
{%- endif %}

/*******************************************************************************
 * Interrupt Service Routines
 *******************************************************************************/

/* USER CODE START {{name.upper()}}_ISR */

/* USER CODE END {{name.upper()}}_ISR */

{% endblock %}
