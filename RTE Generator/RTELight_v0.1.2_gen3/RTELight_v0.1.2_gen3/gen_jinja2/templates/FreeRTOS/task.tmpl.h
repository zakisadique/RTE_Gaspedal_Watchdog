#Path: asw/{{name}}
{% extends "h_base.h" %}
{% block content %}

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

{{ macros.descrBlock(data) }}
extern void {{name}}(void *pvParameter);

{% endblock %}
