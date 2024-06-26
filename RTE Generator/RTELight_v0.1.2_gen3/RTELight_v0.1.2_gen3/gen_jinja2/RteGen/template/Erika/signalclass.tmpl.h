#Path: rte/{{name}}
{% import "macros.tmpl" as macros %}
{% block content %}
/**
 *  file    {{name.upper()}}_signal.h
 *
 *  brief   signal base class for signal {{name}}
 *
 *  author  Autogenerated, Peter Fromm       <peter.fromm@h-da.de>
 *
{{ macros.descrBlock(data) }} *
 */



#ifndef {{name.upper()}}_SIGNAL_H_INCLUDED
#define {{name.upper()}}_SIGNAL_H_INCLUDED

/*================================================[ public includes  ]================================================*/
#include "global.h"
#include "project.h"
#include "rte.h"
#include "rte_types.h"

#include "{{name}}_type.h"


/********************************************************************************************************************/
/* The driver API block																						*/
/********************************************************************************************************************/
                                                                                                                       
/**
 *  Definition of function types for driver interfaces.
 *  I-Port
 */
typedef RC_t (*{{name.upper()}}_driverIn_t)({{name.upper()}}_data_t * const);

/**
 *  Definition of function types for driver interfaces.
 *  O-Port
 */
typedef RC_t (*{{name.upper()}}_driverOut_t)( const {{name.upper()}}_data_t * const);


/********************************************************************************************************************/
/* The signal configuration API block																				*/
/********************************************************************************************************************/

/**
 * Instances of the struct {{name.upper()}}_cfg_t represent the signal object configuration.
 */
struct {{name.upper()}}_cfg_s
{
    /**
     * Function pointer to the input driver
     */
    {{name.upper()}}_driverIn_t const inDriver;

    /**
     * Function pointer to the output driver table
     */
   {{name.upper()}}_driverOut_t const outDriver;
   
    /**
     * Event onUpdate
     */
    EventMaskType const evOnUpdate;
    
    
    /**
     * Event onError
     */
    EventMaskType const evOnError;
    
    /**
     * Task Count onUpdate
     */
    size_t const onUpdateTaskCount;

    /**
     * Task List onUpdate
     */
    TaskTypeArray* const onUpdateTasks;
    
    /**
     * Task Count onError
     */
    size_t const onErrorTaskCount;

    /**
     * Task List onError
     */
    TaskTypeArray* const onErrorTasks;
	
	
	/**
	 * Ressourse is active? We need an additional boolean as a ressource value 0 is valid.
	 */
	 boolean_t const resourceActive;
	 
	/**
	 * Ressourse 
	 */
	 ResourceType const resource;

};                                                                                                                     
typedef const struct {{name.upper()}}_cfg_s {{name.upper()}}_cfg_t;
                              
/********************************************************************************************************************/
/* The data interface block																							*/
/********************************************************************************************************************/

                                                                                                                       
							  
/**
 * Instances of the struct {{name.upper()}}_t represent the signal objects.
 * A signal object contains the current application value 'value' as well as relevant meta data.
 */
struct {{name.upper()}}_s
{                                                                                                                      

	/**
	 * Data buffer for the application value
	 */
    {{name.upper()}}_data_t value;

    /**
     * Current signal status
     */
    RTE_signalStatus_t status;

    /**
     * Current age of the signal (in calling cycles)
     */
    uint32_t age;

    /**
     * Pointer to the signal configuration
     */
	const {{name.upper()}}_cfg_t * const    pSigCfg;

};                                                                                                                     
typedef struct {{name.upper()}}_s {{name.upper()}}_t;

/********************************************************************************************************************/
/* Signal initialisation   																							*/
/********************************************************************************************************************/

/**
 * Initializes a signal instance with a passed init value.
 * Depending on the configured conversion or scaling function the raw_value will be calculated.
 * Signal status will change from RTE_SIGNALSTATUS_STARTUP to RTE_SIGNALSTATUS_INITIALIZED.
 *
 * @param  {{name.upper()}}_t * const signal: Pointer to the signal object which will be initialised
 * @return RC_t: standard return code, currently only RC_SUCCESS
 *
 **/
inline RC_t RTE_{{name.upper()}}_init( {{name.upper()}}_t * const signal )
{                                                                                                                      

   RC_t ret = RC_SUCCESS;

   //Set value and raw value
   signal->value  = {{name.upper()}}_INIT_DATA;
   signal->age    = 0;
   signal->status = RTE_SIGNALSTATUS_INITIALIZED;

   return ret;
}

/********************************************************************************************************************/
/* Status and timeout control																						*/
/********************************************************************************************************************/

/**
 *  Returns the current signal status of the passed signal instance.
 *
 * @param  {{name.upper()}}_t * const signal: Pointer to the signal object
 * @return  sig_status_t: The current signal status
 *
 **/
inline RTE_signalStatus_t RTE_{{name.upper()}}_getStatus( const {{name.upper()}}_t * const signal )
{
   return signal->status;
}


/**
 *  Sets a new signal status of the passed signal instance by passing the new status.
 *
 * @param  {{name.upper()}}_t * const signal: Pointer to the signal object
 * @param  const sig_status_t status: New signal status
 * @return RC_t: standard return code, currently only RC_SUCCESS
 *
 */
inline RC_t RTE_{{name.upper()}}_setStatus( {{name.upper()}}_t * const signal, const RTE_signalStatus_t status )
{
   signal->status = status;
   size_t taskNum=0;
   
   //Fire error events in case of invalid state
   if (signal->status == RTE_SIGNALSTATUS_INVALID)
   {
	    //Pointer to the Taskarray, containing the tasks receiving the onUpdate events
		TaskTypeArray* pTaskArray = signal->pSigCfg->onErrorTasks;

		if (0 != signal->pSigCfg->evOnError && NULL != pTaskArray){
			for( taskNum=0 ; taskNum < signal->pSigCfg->onErrorTaskCount ;taskNum++){
				TaskType task = (*pTaskArray)[taskNum];
				SetEvent( task, signal->pSigCfg->evOnError);
			}
		}
   }
   
   return RC_SUCCESS;
}


/**
 * Returns the count of refreshing trials (refresh, set or set_raw) that failed.
 * Prerquisite: The signal is refreshed cyclically
 *
 * @param  {{name.upper()}}_t * const signal: Pointer to the signal object
 * @return uint32_t: Number of cycles since the signal has been updated for the last time
 */
inline uint32_t RTE_{{name.upper()}}_getAge( const {{name.upper()}}_t * const signal )
{
   return signal->age;
}

/**
 * Should be called by application or driver if no new value can be provided.
 * @param  {{name.upper()}}_t * const signal: Pointer to the signal object
 * @param uint32_t increment: incrementvalue, typically in [ms]
 * @return void
 */
inline void RTE_{{name.upper()}}_incAge(  {{name.upper()}}_t * const signal , uint32_t increment)
{
	   //Hack....
	   if ( 0xFFFF0000 > (signal->age + increment) )
	   {
	      signal->age += increment;
	   }
}


/********************************************************************************************************************/
/* Application Data read/write Interface																			*/
/********************************************************************************************************************/

/**
 * Returns the current application value as pointer to the signal payload.
 * Careful: This is not threadsafe!!!
 *
 * @param  {{name.upper()}}_t * const signal: Pointer to the signal object
 * @return {{name}}_data_t*: pointer to the current value of the application data buffer
 *
 **/
inline {{name.upper()}}_data_t* RTE_{{name.upper()}}_getPtr( {{name.upper()}}_t * const signal )
{               
   //Todo: Critical region cannot be protected using return values																						
   return &(signal->value);                                                                                               
}

/**
 * Returns the current application value of the passed signal instance.
 *
 * @param  {{name.upper()}}_t * const signal: Pointer to the signal object
 * @return {{name}}_data_t: current value of the application data buffer
 *
 **/
inline {{name.upper()}}_data_t RTE_{{name.upper()}}_get( const {{name.upper()}}_t * const signal )
{               
   //Todo: Critical region cannot be protected using return values																						
   return signal->value;                                                                                               
}                                                                                                                      
                                                                                                                       
/**
 * Returns the current application value of the passed signal instance threadsafe.
 *
 * @param  {{name.upper()}}_t * const signal: Pointer to the signal object
 * @param  {{name.upper()}}_data_t* data: Pointer to the return data Pointer to the signal object
 * @return RC_SUCCESS
 *
 **/
inline RC_t RTE_{{name.upper()}}_getThreadSafe( const {{name.upper()}}_t * const signal, {{name.upper()}}_data_t * const data )
{    
   if (TRUE == signal->pSigCfg->resourceActive) GetResource(signal->pSigCfg->resource);
   *data = signal->value;
   if (TRUE == signal->pSigCfg->resourceActive) ReleaseResource(signal->pSigCfg->resource);          

   return RC_SUCCESS;                                                                   
   
}                                                                                                            
                                                                                                                       
/**
 * Sets a new application value to the passed signal instance by passing the new value.
 * The corresponding driver raw value will be calculated immediately by using the default conversion or calling the
 * signal specific scaling function.
 * The signal age will be set to 0 and the new status will be 'RTE_SIGNALSTATUS_VALID'.
 *
 * @param  {{name.upper()}}_t * const signal: Pointer to the signal object
 * @param  {{name}}_data_t const value: value for the application data buffer
 * @return RC_t: standard return code, currently only RC_SUCCESS
 *
 **/
inline RC_t RTE_{{name.upper()}}_set({{name.upper()}}_t * const signal, const {{name.upper()}}_data_t value  )
{

   RC_t ret = RC_SUCCESS;
   size_t taskNum=0;


   if (TRUE == signal->pSigCfg->resourceActive) GetResource(signal->pSigCfg->resource);
   signal->value  = value;
   signal->age    = 0;
   signal->status = RTE_SIGNALSTATUS_VALID;
   if (TRUE == signal->pSigCfg->resourceActive) ReleaseResource(signal->pSigCfg->resource);

   //Pointer to the Taskarray, containing the tasks receiving the onUpdate events
   TaskTypeArray* pTaskArray = signal->pSigCfg->onUpdateTasks;

   if (0 != signal->pSigCfg->evOnUpdate && NULL != pTaskArray){
      for( taskNum=0 ; taskNum < signal->pSigCfg->onUpdateTaskCount ;taskNum++){
		  
          TaskType task = (*pTaskArray)[taskNum];
	      SetEvent( task, signal->pSigCfg->evOnUpdate);
      }
   }

   return ret;
}                                                                                                                      
                                                                                                                       
                                                                                                                      
/********************************************************************************************************************/
/* Call functions to the connected drivers																			*/
/********************************************************************************************************************/

                                                                                                                       
/**
 *  Calls the connected driver interface to get a new value.
 *
 * @param {{name.upper()}}_t * const signal: Pointer to the signal object
 * @return  RC_t: Return value of the driver call
 *
 */
inline RC_t RTE_{{name.upper()}}_pullPort( {{name.upper()}}_t * const signal )
{                                                                                                                      
   RC_t ret = RC_SUCCESS;

                                                                                                                       
   if ( NULL != signal->pSigCfg->inDriver )
   {
	  {{name.upper()}}_data_t value = signal->value;
      ret = signal->pSigCfg->inDriver(&value);
                                                                                                                       
      if ( ret == RC_SUCCESS )                                                                                         
      {
    	  //Critical Section
    	  RTE_{{name.upper()}}_set(signal, value);
      }
      else
      {
		  //Signal is invalid. Error event (if present) will be fired
		  RTE_{{name.upper()}}_setStatus(signal, RTE_SIGNALSTATUS_INVALID);
      }

   }                                                                                                                   
                                                                                                                       
   return ret;                                                                                                         
}                                                                                                                      
                                                                                                                       
/**
 *  Calls the connected driver interfaces to send a value. Value will not be sent if it is INVALID.
 *
 * @param {{name.upper()}}_t * const signal: Pointer to the signal object
 * @return  RC_t: Return value of the driver call
 *
 **/
inline RC_t RTE_{{name.upper()}}_pushPort( const {{name.upper()}}_t * const signal )
{                                                                                                                      
   RC_t ret = RC_ERROR;

   if (RTE_SIGNALSTATUS_VALID == signal->status)
   {
	   ret = signal->pSigCfg->outDriver(&(signal->value));
   }
	
   //In case of an out-driver, no error event is thrown in case of an error code from the driver
   //Application has the responsibility to handle this
   
   return ret;                                                                                                         
}                                                                                                                      

#endif /* include guard */


{% endblock %}
