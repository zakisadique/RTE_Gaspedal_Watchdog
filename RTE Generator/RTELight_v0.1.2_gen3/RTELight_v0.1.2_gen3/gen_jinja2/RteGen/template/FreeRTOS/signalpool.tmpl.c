#Path: rte/{{name}}
{% extends "c_base.c" %}
{% block content %}
{% for signalobject in data.signalobjects -%}
#include "{{signalobject.signalclass.replace(" ","_").lower()}}.h"
#include "{{signalobject.signalclass.replace(" ","_").lower()}}_type.h"
{% endfor %}

{% for signalobject in data.signalobjects %}
/* signal configuration */
{{ macros.descrBlock(signalobject) }}


static const {{signalobject.signalclass.replace(" ","_").upper()}}_cfg_t {{signalobject.name.replace(" ","_").upper()}}_cfg = 
{
		/* indriver           */  {{signalobject.signalclass.replace(" ","_").upper()+"_driverIn" if signalobject.indriver=="default" else signalobject.indriver}},
		/* outdriver          */  {{signalobject.signalclass.replace(" ","_").upper()+"_driverOut" if signalobject.outdriver=="default" else signalobject.outdriver}},

		/* onUpdate           */  {{signalobject.onDataUpdate}},
		/* onError            */  {{signalobject.onDataError}},
		/* taskCount onUpdate */  {{signalobject.updateTasks|length}},
		/* taskCount onError  */  {{signalobject.errorTasks|length}},

		/* resource active    */  {{"FALSE" if signalobject.resource == "None" else "TRUE"}},
		/* resource           */  {{0  if signalobject.resource == "None" else signalobject.resource}},

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


void RTE_timertick_{{name}}_tick(uint32_t tick){
	{% for signalobject in data.signalobjects -%}
	RTE_{{signalobject.signalclass.replace(" ","_").upper()}}_incAge( &{{signalobject.name.replace(" ","_").upper()}}_signal, tick); 
	{% endfor %}
}


{% endblock %}
