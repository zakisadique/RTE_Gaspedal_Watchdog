
/*
 * Filename: sp_common.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * Description: The common global signal pool, all signals will be stored here
 */

#ifndef _H_DEFINE_SP_COMMON
#define _H_DEFINE_SP_COMMON

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START SP_COMMON_INCLUDES */

/* USER CODE END SP_COMMON_INCLUDES */



#include "sc_joystick.h"
#include "sc_speed.h"
#include "sc_engine.h"
#include "sc_brakelight.h"
#include "sc_logging.h"



/*
 * description: Joystick position
 * indriver: default
 * name: so_joystick
 * onDataError: 0
 * onDataUpdate: ev_joystick_onData
 * outdriver: 0
 * resource: res_joystick
 * shortname: joystick
 * signalclass: sc_joystick
 * signalpool: sp_common
 */
extern SC_JOYSTICK_t SO_JOYSTICK_signal;


/*
 * description: Speed of the car 
 * indriver: 0
 * name: so_speed
 * onDataError: 0
 * onDataUpdate: ev_speed_onData
 * outdriver: 0
 * resource: res_speed
 * shortname: speed
 * signalclass: sc_speed
 * signalpool: sp_common
 */
extern SC_SPEED_t SO_SPEED_signal;


/*
 * description: Engine speed
 * indriver: 0
 * name: so_engine
 * onDataError: 0
 * onDataUpdate: 0
 * outdriver: default
 * resource: res_engine
 * shortname: engine
 * signalclass: sc_engine
 * signalpool: sp_common
 */
extern SC_ENGINE_t SO_ENGINE_signal;


/*
 * description: A Signal for brakelights
 * indriver: 0
 * name: so_brakelight
 * onDataError: 0
 * onDataUpdate: 0
 * outdriver: default
 * resource: res_brakelight
 * shortname: brakelight
 * signalclass: sc_brakelight
 * signalpool: sp_common
 */
extern SC_BRAKELIGHT_t SO_BRAKELIGHT_signal;


/*
 * description: A Signal for logging on an HMI device
 * indriver: 0
 * name: so_logging
 * onDataError: 0
 * onDataUpdate: 0
 * outdriver: default
 * resource: res_logging
 * shortname: logging
 * signalclass: sc_logging
 * signalpool: sp_common
 */
extern SC_LOGGING_t SO_LOGGING_signal;



/*
 * Increments the age of the signals in this pool 
 */
void RTE_timertick_sp_common_tick(uint32_t tick);

/*
 * Reset all signals in this pool
 */
void RTE_reset_sp_common();

#endif