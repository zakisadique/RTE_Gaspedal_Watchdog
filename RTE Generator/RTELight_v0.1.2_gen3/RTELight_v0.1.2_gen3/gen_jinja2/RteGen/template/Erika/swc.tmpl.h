#Path: asw/{{name}}
{% extends "h_base.h" %}
{% block content %}

/* USER CODE START {{name.upper()}}_USERDEFINITIONS */

/* USER CODE END {{name.upper()}}_USERDEFINITIONS */

{% for runnable in data.runnables %}
/*
{{ macros.descrBlock(runnable) }} */
void {{runnable.name}}(RTE_event ev);
{% endfor %}
{% endblock %}
