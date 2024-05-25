/*
 * Filename: sc_joystick_type.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * description: Signal for Joystick 
 * name: sc_joystick
 * shortname: joystick
 *
 */

#include "project.h"
#include "global.h"
#include "rte.h"
#include "rte_types.h"
#include "sc_joystick_type.h"
#include "joystick.h"



/* USER CODE START SC_JOYSTICK_INCLUDE */

/* USER CODE END SC_JOYSTICK_INCLUDE */




/* USER CODE START SC_JOYSTICK_USERDEFINITIONS */

/* USER CODE END SC_JOYSTICK_USERDEFINITIONS */


/*****************************************************************************************
 *************** Port Wrapper Implementation for SC_JOYSTICK signal  ****************
 *****************************************************************************************/
 
 

/**
 * Default IN driver API
 */
inline RC_t SC_JOYSTICK_driverIn(SC_JOYSTICK_data_t *const data)
{
	/* USER CODE START driverInSC_JOYSTICK */
//    UART_Logs_PutString("JoystickIN\n");
	//Read data from the MCAL driver
    sint8_t x = 0;
    sint8_t y = 0; 
    
    sint8_t* x_ptr = &x;
    sint8_t* y_ptr = &y;
    
    JOYSTICK_ReadPosition(x_ptr, y_ptr);
    data -> m_joystickValue = y;
	//Scale it to the application type

	return RC_SUCCESS;
	/* USER CODE END driverInSC_JOYSTICK */
}



