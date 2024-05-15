#Path: rte/{{name}}
{% extends "c_base.c" %}
{% block content %}
{% for signalobject in data.signalobjects -%}
#include "{{signalobject.signalclass.replace(" ","_").lower()}}.h"
#include "{{signalobject.signalclass.replace(" ","_").lower()}}_type.h"
{% endfor %}

{% for signalobject in data.signalobjects %}
/* signal configuration */
/*
{{ macros.descrBlock(signalobject) }} */

{% if signalobject.updateTasks %}
/* The following array contains the receiving tasks for onUpdate signal events */
const TaskTypeArray {{ signalobject.name.replace(" ","_")}}_updTasks = {{"{ "+signalobject.updateTasks | join(", ")+" }" }};
{% endif %} {% if signalobject.errorTasks %}
/* The following array contains the receiving tasks for onError signal events */
const TaskTypeArray {{ signalobject.name.replace(" ","_")}}_errTasks = {{"{ "+signalobject.errorTasks | join(", ")+" }" }};
{% endif %}

static const {{signalobject.signalclass.replace(" ","_").upper()}}_cfg_t {{signalobject.name.replace(" ","_").upper()}}_cfg = 
{
   /* indriver           */  {{signalobject.signalclass.replace(" ","_").upper()+"_driverIn" if signalobject.indriver=="default" else signalobject.indriver}},
   /* outdriver          */  {{signalobject.signalclass.replace(" ","_").upper()+"_driverOut" if signalobject.outdriver=="default" else signalobject.outdriver}},

   /* onUpdate           */  {{signalobject.onDataUpdate}},
   /* onError            */  {{signalobject.onDataError}},
   /* taskCount onUpdate */  {{signalobject.updateTasks|length}},
   /* task list onUpdate */  {{"&"+signalobject.name.replace(" ","_")+"_updTasks" if signalobject.updateTasks else "NULL"}},
   /* taskCount onError  */  {{signalobject.errorTasks|length}},
   /* task list onError  */  {{"&"+signalobject.name.replace(" ","_")+"_errTasks" if signalobject.errorTasks else "NULL"}},

   /* resource active    */  {{"FALSE" if signalobject.resource == "None" else "TRUE"}},
   /* resource           */  {{"0"  if signalobject.resource == "None" else signalobject.resource}},
   
}; /* configuration {{signalobject.name.replace(" ","_").lower()}} */


/* signal data */

{{signalobject.signalclass.replace(" ","_").upper()}}_t {{signalobject.name.replace(" ","_").upper()}}_signal= 
{
   /* init value    */  {{signalobject.signalclass.replace(" ","_").upper()}}_INIT_DATA,
   /* status        */  RTE_SIGNALSTATUS_STARTUP,
   /* age           */  0,
   /* cfg           */  &{{signalobject.name.replace(" ","_").upper()}}_cfg,
}; /* data {{signalobject.name.replace(" ","_").lower()}} */
{% endfor %}


/*
 * Increments the age of the signals in this pool 
 */
void RTE_timertick_{{name}}_tick(uint32_t tick){
   {% for signalobject in data.signalobjects -%}
   RTE_{{signalobject.signalclass.replace(" ","_").upper()}}_incAge( &{{signalobject.name.replace(" ","_").upper()}}_signal, tick); 
   {% endfor %}
}

/*
 * Reset all signals in this pool
 */
void RTE_reset_{{name}}(){
   {% for signalobject in data.signalobjects -%}
   RTE_{{signalobject.signalclass.replace(" ","_").upper()}}_init( &{{signalobject.name.replace(" ","_").upper()}}_signal); 
   {% endfor %}
}		


{% endblock %}
