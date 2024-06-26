
/*
 * Filename: sp_common.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 */

#ifndef _H_DEFINE_SP_COMMON
#define _H_DEFINE_SP_COMMON

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START SP_COMMON_INCLUDES */

/* USER CODE END SP_COMMON_INCLUDES */



#include "sc_protocol.h"
#include "sc_protocol.h"
#include "sc_joystick.h"
#include "sc_button.h"
#include "sc_display.h"
#include "sc_connectionstate.h"
#include "sc_event.h"
#include "sc_event.h"
#include "sc_event.h"



/*
* description: Data received over XBee
* indriver: default
* name: so_protocolRx
* onDataError: ev_protocolrx_onError
* onDataUpdate: 0
* outdriver: 0
* resource: None
* shortname: protocolRx
* signalclass: sc_Protocol
* signalpool: sp_common
*/
extern SC_PROTOCOL_t SO_PROTOCOLRX_signal;


/*
* description: Protocol send over XBEE
* indriver: 0
* name: so_protocolTx
* onDataError: 0
* onDataUpdate: 0
* outdriver: default
* resource: None
* shortname: protocolTx
* signalclass: sc_Protocol
* signalpool: sp_common
*/
extern SC_PROTOCOL_t SO_PROTOCOLTX_signal;


/*
* description: Signal representing all analogue SIgnals of the HMI
* indriver: default
* name: so_joystick
* onDataError: 0
* onDataUpdate: 0
* outdriver: 0
* resource: None
* shortname: joystick
* signalclass: sc_Joystick
* signalpool: sp_common
*/
extern SC_JOYSTICK_t SO_JOYSTICK_signal;


/*
* description: Button representation
* indriver: default
* name: so_button
* onDataError: 0
* onDataUpdate: 0
* outdriver: 0
* resource: None
* shortname: button
* signalclass: sc_Button
* signalpool: sp_common
*/
extern SC_BUTTON_t SO_BUTTON_signal;


/*
* description: Display representation
* indriver: 0
* name: so_display
* onDataError: 0
* onDataUpdate: ev_display_onData
* outdriver: default
* resource: res_display_Lock
* shortname: display
* signalclass: sc_Display
* signalpool: sp_common
*/
extern SC_DISPLAY_t SO_DISPLAY_signal;


/*
* description: Connection State of the remote - must be in sync with the car
* indriver: 0
* name: so_connectionstate
* onDataError: 0
* onDataUpdate: 0
* outdriver: 0
* resource: None
* shortname: connectionstate
* signalclass: sc_ConnectionState
* signalpool: sp_common
*/
extern SC_CONNECTIONSTATE_t SO_CONNECTIONSTATE_signal;


/*
* description: Event fired from remote to central state machine
* indriver: 0
* name: so_event_rx_remote
* onDataError: 0
* onDataUpdate: ev_event_rx_remote_onData
* outdriver: 0
* resource: res_event_rx_Lock
* shortname: event_rx_remote
* signalclass: sc_Event
* signalpool: sp_common
*/
extern SC_EVENT_t SO_EVENT_RX_REMOTE_signal;


/*
* description: Event fired from the central state machine
* indriver: 0
* name: so_event_tx
* onDataError: 0
* onDataUpdate: ev_event_tx_onData
* outdriver: 0
* resource: None
* shortname: event_tx
* signalclass: sc_Event
* signalpool: sp_common
*/
extern SC_EVENT_t SO_EVENT_TX_signal;


/*
* description: Event fired from hmi to central state machine
* indriver: 0
* name: so_event_rx_hmi
* onDataError: 0
* onDataUpdate: ev_event_rx_hmi_onData
* outdriver: 0
* resource: res_event_rx_Lock
* shortname: event_rx_hmi
* signalclass: sc_Event
* signalpool: sp_common
*/
extern SC_EVENT_t SO_EVENT_RX_HMI_signal;



/*
 * Increments the age of the signals in this pool 
 */
void RTE_timertick_sp_common_tick(uint32_t tick);

#endif