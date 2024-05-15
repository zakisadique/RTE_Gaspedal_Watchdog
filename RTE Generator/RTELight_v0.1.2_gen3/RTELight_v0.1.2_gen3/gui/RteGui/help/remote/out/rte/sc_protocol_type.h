
/*
 * Filename: sc_protocol_type.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 */

#ifndef _H_DEFINE_SC_PROTOCOL_TYPE
#define _H_DEFINE_SC_PROTOCOL_TYPE

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START SC_PROTOCOL_INCLUDES */

/* USER CODE END SC_PROTOCOL_INCLUDES */



/**********************************************************************
 *       Type Definition for SC_PROTOCOL signal    
 **********************************************************************/

/* USER CODE START SC_PROTOCOL_USERDEFINITIONS */

/* USER CODE END SC_PROTOCOL_USERDEFINITIONS */

typedef 
/* USER CODE START SC_PROTOCOL_SIGNALDATADEFINITION */
struct
{
	#error "Provide your data structure"
} 
/* USER CODE END SC_PROTOCOL_SIGNALDATADEFINITION */
SC_PROTOCOL_data_t;

/* USER CODE START InitSC_PROTOCOL */
#error "Provide a sensible init value"
#define SC_PROTOCOL_INIT_DATA ((SC_PROTOCOL_data_t){})
/* USER CODE END InitSC_PROTOCOL */


/**
 * Default IN driver API
 * \param SC_PROTOCOL_data_t *const data : [OUT] scaled data read from the driver
 * \return RC_SUCCESS is all was ok, error code otherwise
 */
RC_t SC_PROTOCOL_driverIn(SC_PROTOCOL_data_t *const data);



/**
 * Default OUT driver API
 * \param const SC_PROTOCOL_data_t  *const data : [IN] signal data for the driver, will be scaled in this function
 * \return RC_SUCCESS is all was ok, error code otherwise
 */
RC_t SC_PROTOCOL_driverOut(const SC_PROTOCOL_data_t  *const data);


/* USER CODE START SC_PROTOCOL_USERFUNCTIONS */

/* USER CODE END SC_PROTOCOL_USERFUNCTIONS */


#endif