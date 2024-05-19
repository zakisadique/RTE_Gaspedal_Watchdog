
/*
 * Filename: sc_speed_type.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * Description: Speed data type
 */

#ifndef _H_DEFINE_SC_SPEED_TYPE
#define _H_DEFINE_SC_SPEED_TYPE

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START SC_SPEED_INCLUDES */

/* USER CODE END SC_SPEED_INCLUDES */



/**********************************************************************
 *       Type Definition for SC_SPEED signal    
 **********************************************************************/

/* USER CODE START SC_SPEED_USERDEFINITIONS */

/* USER CODE END SC_SPEED_USERDEFINITIONS */

typedef 
/* USER CODE START SC_SPEED_SIGNALDATADEFINITION */
struct
{
	#error "Provide your data structure"
} 
/* USER CODE END SC_SPEED_SIGNALDATADEFINITION */
SC_SPEED_data_t;

/* USER CODE START InitSC_SPEED */
#error "Provide a sensible init value"
#define SC_SPEED_INIT_DATA ((SC_SPEED_data_t){})
/* USER CODE END InitSC_SPEED */


/**
 * Default IN driver API
 * \param SC_SPEED_data_t *const data : [OUT] scaled data read from the driver
 * \return RC_SUCCESS is all was ok, error code otherwise
 */
RC_t SC_SPEED_driverIn(SC_SPEED_data_t *const data);




/* USER CODE START SC_SPEED_USERFUNCTIONS */

/* USER CODE END SC_SPEED_USERFUNCTIONS */


#endif