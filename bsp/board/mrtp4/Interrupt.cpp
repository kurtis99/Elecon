#include "bsp_main.h"

#include "Timer.h"

//uint32_t IntervalTimer::NumOfSecTik;

#if !UART0_MASTER
    OS::TEventFlag efUART0;
#endif

#if !UART1_MASTER
    OS::TEventFlag efUART1;
#endif

//---------------------------------------------------------------------------
//
//      Обработка прерывания от USART0
//
OS_INTERRUPT void USART0_RX_vect()      /* USART0 Rx Complete */
{
    OS::TISRW_SS ISRW;
    
    /* Подпрограмму обработки прерывания пишем ТУТ */
    uint8_t ret_val;

    ret_val=Receive_buffer_uart0(cur_address0);
    switch( ret_val )
    {
        case 2:             /* Ошибка приема */
        {
            UCSR0B=0;
            #if !UART0_MASTER
            efUART0.Signal();
            #endif
            break;
        }
        case 3:             /* Прием закончен нормально */
        {
            sUSART0.uart_status |= UART_RX_OK;
            uart_init0();
            #if !UART0_MASTER
            UCSR0B=(1<<TXEN0)|(1<<TXCIE0);   //разрешение передатчика
            ON(SET_USART0_TX);
            UDR0='!';
            #endif
            sUSART0.efUSART_TX.SignalISR();
            break;
        }
    }
}
OS_INTERRUPT void USART0_TX_vect()      /* USART0 Tx Complete */
{
    OS::TISRW_SS ISRW;
    
    //CPL(LED_BLINK4);
    
    /* Подпрограмму обработки прерывания пишем ТУТ */
    Transmitt_buffer_uart0();
    #if !UART0_MASTER
    if(sUSART0.uart_status&UART_TX_OK)
    {
        efUART0.SignalISR();
    }
    #endif
}


//---------------------------------------------------------------------------
//
//      Обработка прерывания от USART1
//
OS_INTERRUPT void USART1_RX_vect()
{
    OS::TISRW_SS ISRW;
    /* Подпрограмму обработки прерывания пишем ТУТ */
    uint8_t ret_val;
    ret_val=Receive_buffer_uart1(cur_address1);
    switch(ret_val)
    {
        case 2:             /* Ошибка приема */
        {
            UCSR1B=0;
            #if !UART1_MASTER
            efUART1.SignalISR();
            #endif
            break;
        }
        case 3:             /* Прием закончен нормально */
        {
            sUSART1.uart_status|=UART_RX_OK;
            uart_init1();
            #if !UART1_MASTER
            UCSR1B=(1<<TXEN1)|(1<<TXCIE1);   //разрешение передатчика
            ON(SET_USART1_TX);
            ON(SET_USART1_RX);
            UDR1='!';
            #endif
            sUSART1.efUSART_TX.SignalISR();
            break;
        }
    }
}
OS_INTERRUPT void USART1_TX_vect()
{
    OS::TISRW_SS ISRW;
    /* Подпрограмму обработки прерывания пишем ТУТ */
    Transmitt_buffer_uart1();
    #if !UART1_MASTER
    if(sUSART1.uart_status&UART_TX_OK)
    {
        efUART1.SignalISR();
    }
    #endif
}

//---------------------------------------------------------------------------
//
//      Обработка переполнения таймера1
//
// ( Впринципе не очень нужен )

OS_INTERRUPT void TIMER3_COMPA_vect(void)
{
    OS::TISRW_SS ISRW;
    
//    IntervalTimer Timer1;
    
    sec_tik = 0x55;
    
    OCR3AL = 0x30;
    OCR3AH = 0x2A;    
}

//------	end of file  main.cpp	-------------------------------------------
