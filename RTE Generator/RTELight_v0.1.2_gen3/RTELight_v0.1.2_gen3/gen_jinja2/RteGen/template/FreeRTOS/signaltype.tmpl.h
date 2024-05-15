#Path: rte/{{name}}_type
{% extends "h_base.h" %}
{% block content %}

/**********************************************************************
 *       Type Definition for {{name.upper()}} signal    
 **********************************************************************/

/* USER CODE START {{name.upper()}}_USERDEFINITIONS */

/* USER CODE END {{name.upper()}}_USERDEFINITIONS */

typedef 
/* USER CODE START {{name.upper()}}_SIGNALDATADEFINITION */
struct
{
	#error "Provide your data structure"
} 
/* USER CODE END {{name.upper()}}_SIGNALDATADEFINITION */
{{name.upper()}}_data_t;

/* USER CODE START Init{{name.upper()}} */
#error "Provide a sensible init value"
#define {{name.upper()}}_INIT_DATA (({{name.upper()}}_data_t){})
/* USER CODE END Init{{name.upper()}} */

{% if data.needsDefaultInDriver %}
/**
 * Default IN driver API
 * \param {{name.upper()}}_data_t *const data : [OUT] scaled data read from the driver
 * \return RC_SUCCESS is all was ok, error code otherwise
 */
RC_t {{name.upper()}}_driverIn({{name.upper()}}_data_t *const data);
{% endif %}

{% if data.needsDefaultOutDriver %}
/**
 * Default OUT driver API
 * \param const {{name.upper()}}_data_t  *const data : [IN] signal data for the driver, will be scaled in this function
 * \return RC_SUCCESS is all was ok, error code otherwise
 */
RC_t {{name.upper()}}_driverOut(const {{name.upper()}}_data_t  *const data);
{% endif %}

/* USER CODE START {{name.upper()}}_USERFUNCTIONS */

/* USER CODE END {{name.upper()}}_USERFUNCTIONS */

{% endblock %}
