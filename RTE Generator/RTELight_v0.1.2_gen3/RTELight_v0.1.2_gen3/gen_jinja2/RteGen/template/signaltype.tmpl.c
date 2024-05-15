#Path: rte/{{name}}_type
{% extends "c_base.c" %}
{% block content %}



/* USER CODE START {{name.upper()}}_USERDEFINITIONS */

/* USER CODE END {{name.upper()}}_USERDEFINITIONS */


/*****************************************************************************************
 *************** Port Wrapper Implementation for {{name.upper()}} signal  ****************
 *****************************************************************************************/
 
 
{% if data.needsDefaultInDriver %}
/**
 * Default IN driver API
 */
inline RC_t {{name.upper()}}_driverIn({{name.upper()}}_data_t *const data)
{
	/* USER CODE START driverIn{{name.upper()}} */
#error "Add your code here"

	//Read data from the MCAL driver

	//Scale it to the application type

	return RC_SUCCESS;
	/* USER CODE END driverIn{{name.upper()}} */
}
{% endif -%}
{% if data.needsDefaultOutDriver -%}
/**
 * Default OUT driver API
 */
inline RC_t {{name.upper()}}_driverOut(const {{name.upper()}}_data_t  *const data)
{
	/* USER CODE START driverOut{{name.upper()}} */
#error "Add your code here"

	//Scale application data to drive format

	//Write scaled data to driver

	return RC_SUCCESS;
	/* USER CODE END driverOut{{name.upper()}} */
}
{% endif %}


{% endblock %}
