{% import "macros.tmpl" as macros -%}
/*
 * Filename: {{filename_nosuffix}}.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
{{ macros.descrBlock(data) }} *
 */

#include "project.h"
#include "global.h"
#include "rte.h"
#include "rte_types.h"
#include "{{filename_nosuffix}}.h"



/* USER CODE START {{name.upper()}}_INCLUDE */

/* USER CODE END {{name.upper()}}_INCLUDE */
{% block content -%}
{% endblock -%}