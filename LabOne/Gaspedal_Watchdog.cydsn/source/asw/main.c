/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "global.h"
#include "joystick.h"

#include "tsk_io.h"
#include "tsk_logging.h"
#include "tsk_control.h"
#include "led.h"
#include "tft.h"
#include "watchdog.h"

//extern WDT_Bitfields wdtBitfields;

#define TEST_WATCHDOG 0

//ISR which will increment the systick counter every ms
ISR(systick_handler)
{
    CounterTick(cnt_systick);
}

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
   
    //Set systick period to 1 ms. Enable the INT and start it.
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));
	EE_systick_enable_int();
    
    
    
    // Start Operating System
    for(;;)	    
    	StartOS(OSDEFAULTAPPMODE);
}

void unhandledException()
{
    //Ooops, something terrible happened....check the call stack to see how we got here...
    __asm("bkpt");
}

/********************************************************************************
 * Task Definitions
 ********************************************************************************/

TASK(tsk_init)
{
    
    //Init MCAL Drivers

    UART_Logs_Start();
    JOYSTICK_Init();
    LED_Init();
    TFT_init();
    TFT_setCursor(0, 0);
    
    UART_Logs_PutString("\nSytem Online\n");
    if (WD_CheckResetBit() == TRUE){
        UART_Logs_PutString("Rebooted after watchdog reset\n");
        
        TFT_print((char_t*)"Rebooted after watchdog reset");
    } else {
        UART_Logs_PutString("Rebooted after power on reset\n");
        TFT_print((char_t*)"Rebooted after power on reset");
    }
    
    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver initialisation!
    EE_system_init();
	
    //Start SysTick
	//Must be done here, because otherwise the isr vector is not overwritten yet
    EE_systick_start();  
	
    
    
    //Start the alarm with 100ms cycle time
    SetRelAlarm(alrm_10_ms,1,20);
    SetRelAlarm(alrm_1_ms,1,1);
    
    ActivateTask(tsk_errorhandler);
    ActivateTask(tsk_io);
    ActivateTask(tsk_control);
    ActivateTask(tsk_logging);
    ActivateTask(tsk_system);
    ActivateTask(tsk_background);
    WD_Start(PERIOD_1024_TICK);
    TerminateTask();
    
}



TASK(tsk_background)
{
    while(1)
    {
        //do something with low prioroty
        #if TEST_WATCHDOG == 0 
//        
//        if (
////            wdtBitfields.m_Bit_CalcControl == 1 &&
////            wdtBitfields.m_Bit_Logging == 1 &&
////            wdtBitfields.m_Bit_SetBrakelight == 1 &&
////            wdtBitfields.m_Bit_SetEngine == 1 &&
////            wdtBitfields.m_Bit_System == 1 &&
////            wdtBitfields.m_BitReadJoystick == 1
//        ) {
//        WD_Trigger();
//        }
//        
//        wdtBitfields.m_Bit_CalcControl = 0;
//        wdtBitfields.m_Bit_Logging = 0;
//        wdtBitfields.m_Bit_SetBrakelight = 0;
//        wdtBitfields.m_Bit_SetEngine = 0;
//        wdtBitfields.m_Bit_System = 0;
//        wdtBitfields.m_BitReadJoystick = 0;
            
            
            if (WD_IsError() == FALSE){
                WD_Trigger();
                WD_resetState();
            }
            
            
        
        #endif
    }
    TerminateTask();
    
}





/********************************************************************************
 * ISR Definitions
 ********************************************************************************/

/* [] END OF FILE */
