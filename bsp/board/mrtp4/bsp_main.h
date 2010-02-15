#ifndef __BSP_MAIN_H
    #define __BSP_MAIN_H

    #include "Uart.h"

#include <Main.h>

extern volatile uint8_t sec_tik; 

extern uint8_t cur_address0;
extern uint8_t cur_address1;

#if !UART0_MASTER
    extern OS::TEventFlag efUART0;
#endif

#if !UART1_MASTER
    extern OS::TEventFlag efUART1;
#endif

#endif /* __BSP_MAIN_H */