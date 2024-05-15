#Path: asw/{{name}}
{% extends "h_base.h" %}
{% block content %}

/*
{{ macros.descrBlock(data) }} */
DeclareTask({{name}});

/* USER CODE START {{name.upper()}}_TASKUSERFUNCTION */

/* USER CODE END {{name.upper()}}_TASKUSERFUNCTION */

{% endblock %}
