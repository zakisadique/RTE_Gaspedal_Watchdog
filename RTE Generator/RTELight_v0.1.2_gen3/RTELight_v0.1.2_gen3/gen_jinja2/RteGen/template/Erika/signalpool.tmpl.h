#Path: rte/{{name}}
{% extends "h_base.h" %}
{% block content %}

{% for signalobject in data.signalobjects -%}
#include "{{signalobject.signalclass.replace(" ","_").lower()}}.h"
{% endfor %}

{% for signalobject in data.signalobjects %}
/*
{{ macros.descrBlock(signalobject) }} */
extern {{signalobject.signalclass.replace(" ","_").upper()}}_t {{signalobject.name.replace(" ","_").upper()}}_signal;

{% endfor %}

/*
 * Increments the age of the signals in this pool 
 */
void RTE_timertick_{{name}}_tick(uint32_t tick);

/*
 * Reset all signals in this pool
 */
void RTE_reset_{{name}}();
{% endblock %}


