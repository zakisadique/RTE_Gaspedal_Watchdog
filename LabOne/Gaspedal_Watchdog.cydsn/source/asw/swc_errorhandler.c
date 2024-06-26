/*
 * Filename: swc_errorhandler.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * description: Software component
 * name: swc_errorHandler
 * shortname: errorHandler
 *
 */

#include "project.h"
#include "global.h"
#include "rte.h"
#include "rte_types.h"
#include "swc_errorhandler.h"



/* USER CODE START SWC_ERRORHANDLER_INCLUDE */

#include "error.h"

/* USER CODE END SWC_ERRORHANDLER_INCLUDE */


#include "sp_common.h"

/* USER CODE START SWC_ERRORHANDLER_USERDEFINITIONS */

/* USER CODE END SWC_ERRORHANDLER_USERDEFINITIONS */



/*
 * component: swc_errorHandler
 * cycletime: 0
 * description: Runnable
 * events: ev_error
 * name: ERRORHANDLER_errorHandler_run
 * shortname: errorHandler
 * signalIN: 
 * signalOUT: 
 * task: tsk_errorHandler
 */
void ERRORHANDLER_errorHandler_run(RTE_event ev){
	
	/* USER CODE START ERRORHANDLER_errorHandler_run */
    
    
    ERROR_disableRunnable(ERROR_LOGGING);
    SC_LOGGING_data_t log = SC_LOGGING_INIT_DATA;
    
    log.m_loggingDisabled = 1;
    log.m_loggingEntity = "";
    log.m_loggingValue = "";
    RTE_SC_LOGGING_set(&SO_LOGGING_signal, log);
    RTE_SC_LOGGING_pushPort(&SO_LOGGING_signal);

    
    

    /* USER CODE END ERRORHANDLER_errorHandler_run */
}

/* USER CODE START SWC_ERRORHANDLER_FUNCTIONS */

/* USER CODE END SWC_ERRORHANDLER_FUNCTIONS */

