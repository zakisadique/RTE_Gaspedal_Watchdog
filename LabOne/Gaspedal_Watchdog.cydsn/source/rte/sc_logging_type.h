
/*
 * Filename: sc_logging_type.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * Description: signal for HMI devices
 */

#ifndef _H_DEFINE_SC_LOGGING_TYPE
#define _H_DEFINE_SC_LOGGING_TYPE

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START SC_LOGGING_INCLUDES */

/* USER CODE END SC_LOGGING_INCLUDES */



/**********************************************************************
 *       Type Definition for SC_LOGGING signal    
 **********************************************************************/

/* USER CODE START SC_LOGGING_USERDEFINITIONS */
    
#define MAX_ENTITIES 2 
#define MAX_LOG_LENGTH 10

/* USER CODE END SC_LOGGING_USERDEFINITIONS */

typedef 
/* USER CODE START SC_LOGGING_SIGNALDATADEFINITION */
struct
{
    
	char_t* m_loggingEntity;
    char_t* m_loggingValue;
    uint8_t m_loggingDisabled;
} 
/* USER CODE END SC_LOGGING_SIGNALDATADEFINITION */
SC_LOGGING_data_t;

/* USER CODE START InitSC_LOGGING */
#define SC_LOGGING_INIT_DATA ((SC_LOGGING_data_t){  "Accelerator Value: " ,  NULL , 0 })
/* USER CODE END InitSC_LOGGING */




/**
 * Default OUT driver API
 * \param const SC_LOGGING_data_t  *const data : [IN] signal data for the driver, will be scaled in this function
 * \return RC_SUCCESS is all was ok, error code otherwise
 */
RC_t SC_LOGGING_driverOut(const SC_LOGGING_data_t  *const data);


/* USER CODE START SC_LOGGING_USERFUNCTIONS */

/* USER CODE END SC_LOGGING_USERFUNCTIONS */


#endif