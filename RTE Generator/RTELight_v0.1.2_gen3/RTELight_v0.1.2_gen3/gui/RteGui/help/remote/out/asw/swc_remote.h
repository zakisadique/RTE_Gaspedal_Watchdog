
/*
 * Filename: swc_remote.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 */

#ifndef _H_DEFINE_SWC_REMOTE
#define _H_DEFINE_SWC_REMOTE

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START SWC_REMOTE_INCLUDES */

/* USER CODE END SWC_REMOTE_INCLUDES */



/* USER CODE START SWC_REMOTE_USERDEFINITIONS */

/* USER CODE END SWC_REMOTE_USERDEFINITIONS */


/*
* component: swc_Remote
* cycletime: 0
* description: Read protocol from XBEE
* events: ev_isr_protocolBufferComplete
* name: REMOTE_readProtocol_run
* shortname: readProtocol
* signalIN: so_protocolRx
* signalOUT: so_event_rx_remote
* task: tsk_com
*/
void REMOTE_readProtocol_run(RTE_event ev);

/*
* component: swc_Remote
* cycletime: 100
* description: Send protocol trhough XBEE
* events: ev_event_tx_onData
* name: REMOTE_sendProtocol_run
* shortname: sendProtocol
* signalIN: so_connectionstate|so_event_tx
* signalOUT: so_protocolTx
* task: tsk_com
*/
void REMOTE_sendProtocol_run(RTE_event ev);

/*
* component: swc_Remote
* cycletime: 0
* description: Error Handler for transmission errors
* events: ev_protocolrx_onError
* name: REMOTE_readProtocolError_run
* shortname: readProtocolError
* signalIN: so_protocolRx
* signalOUT: 
* task: tsk_com
*/
void REMOTE_readProtocolError_run(RTE_event ev);


#endif