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
/*
{{ macros.descrBlock(data) }} */
TASK({{name}})
{
    EventMaskType ev = 0;
    
	/* USER CODE START {{name.upper()}}_INIT */

	/* USER CODE END {{name.upper()}}_INIT */
	
    while(1)
    {
        //Wait, read and clear the event
        WaitEvent({{data.events}});
        GetEvent({{name}},&ev);
        ClearEvent(ev);
		
		/* USER CODE START {{name.upper()}}_TASKBOBY_PRE */

		/* USER CODE END {{name.upper()}}_TASKBODY_PRE */
    

        //Process Event table on event
        RTE_ProcessEventTable(RTE_eventActivationTable_{{name}}, RTE_eventActivation_{{name}}_size, ev);
		
		/* USER CODE START {{name.upper()}}_TASKBODY_POST */

		/* USER CODE END {{name.upper()}}_TASKBODY_POST */

        
    }
	
	//Just in Case
	TerminateTask();
}
{% endif -%}
{% if data.mode == "Cyclic" %}
/*
{{ macros.descrBlock(data) }} */
TASK({{name}})
{
	/* ticktime of the task */
	static uint32_t ticktime = 0;

	/* USER CODE START {{name.upper()}}_TASKBOBY_PRE */

	/* USER CODE END {{name.upper()}}_TASKBODY_PRE */
    
    //Process all cyclic runnables which are due
    RTE_ProcessCyclicTable(RTE_cyclicActivationTable_{{name}}, RTE_cyclicActivation_{{name}}_size, ticktime);
	
	/* USER CODE START {{name.upper()}}_TASKBODY_POST */

	/* USER CODE END {{name.upper()}}_TASKBODY_POST */

	ticktime += {{data.timertickperiod}};
	if (ticktime > 0xFFFFFF00) ticktime = 0;
	
	TerminateTask();
    
}
{% endif -%}

{% if data.mode == "Cyclic and Event" %}
/*
{{ macros.descrBlock(data) }} */
TASK({{name}})
{
	/* ticktime of the task */
	uint32_t ticktime = 0;
	
    EventMaskType ev = 0;
	
	/* USER CODE START {{name.upper()}}_INIT */

	/* USER CODE END {{name.upper()}}_INIT */
    
    while(1)
    {
        //Wait, read and clear the event
        WaitEvent({{data.events}});
        GetEvent({{name}},&ev);
        ClearEvent(ev);
    
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
	
	//Just in Case
	TerminateTask();
}
{% endif -%}
{% if data.mode == "System" %}
/*
{{ macros.descrBlock(data) }} */
TASK({{name}})
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
	
	TerminateTask();
}
{%- endif %}

/*******************************************************************************
 * Interrupt Service Routines
 *******************************************************************************/

/* USER CODE START {{name.upper()}}_ISR */

/* USER CODE END {{name.upper()}}_ISR */

{% endblock %}
