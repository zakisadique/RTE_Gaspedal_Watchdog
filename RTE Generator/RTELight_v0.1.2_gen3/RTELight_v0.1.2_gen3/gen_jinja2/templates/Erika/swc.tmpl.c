#Path: asw/{{name}}
{% extends "c_base.c" %}
{% block content %}
{% for signalpool in data.signalpools %}
#include "{{signalpool.name.replace(" ","_").lower()}}.h"
{%- endfor %}

/* USER CODE START {{name.upper()}}_USERDEFINITIONS */

/* USER CODE END {{name.upper()}}_USERDEFINITIONS */


{% for runnable in data.runnables %}
/*
{{ macros.descrBlock(runnable) }} */
void {{runnable.name}}(RTE_event ev){
	
	/* USER CODE START {{runnable.name}} */

    /* USER CODE END {{runnable.name}} */
}
{% endfor %}
/* USER CODE START {{name.upper()}}_FUNCTIONS */

/* USER CODE END {{name.upper()}}_FUNCTIONS */

{% endblock %}
