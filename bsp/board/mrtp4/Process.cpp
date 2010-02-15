#include "bsp_main.h"

//#include "NetPack.h"
#include <USART_control.h>

uint8_t cur_address0;
uint8_t cur_address1;

//---------------------------------------------------------------------------
//
//      Process types
//

typedef OS::process<OS::pr0, 150>   TUART0;
typedef OS::process<OS::pr1, 150>   TUART1;

//---------------------------------------------------------------------------
//
//      Process objects
//

TUART0 UART0;
TUART1 UART1;

extern USART_control * pMegoUSART[];

namespace OS {  /* TUART0 */

template<> OS_PROCESS void TUART0::Exec()
{
    /* нициализации процесса */

    OFF(SET_USART0_TX);

    for(;;) {
        //CPL(LED_BLINK1);
      #if !UART0_MASTER
        efUART0.Wait(200);
      #endif
        cur_address0 = ( pMegoUSART[USART0] -> UsartX_WorkDrv() );
        sUSART0.uart_status=0;
        uart_init0();
        OFF(SET_USART0_TX);
      #if UART0_MASTER
        UCSR0B=(1<<TXEN0)|(1<<TXCIE0);   //разрешение передатчика
        ON(SET_USART0_TX);
        _delay_us(100);
        UDR0='#';
      #else
        UCSR0B=(1<<RXEN0)|(1<<RXCIE0);
      #endif

        //#if !UART0_MASTER
        //    Sleep(5);
        //#else
        //    sUSART0.efUSART_TX.Wait(100);
        //#endif
        Sleep(5);
      #if UART0_MASTER
        sUSART0.efUSART_TX.Wait(100);
      #endif
    }
} // TUART0::Exec()

} // namespace OS

//---------------------------------------------------------------------------
namespace OS {  /* TUART1 */

template<> OS_PROCESS void TUART1::Exec()
{
    /* нициализации процесса */

    OFF(SET_USART1_TX);
    OFF(SET_USART1_RX);

    for(;;) {
        //CPL(LED_BLINK2);
      #if !UART1_MASTER
        efUART1.Wait(200);
      #endif
        cur_address1 = ( pMegoUSART[USART1] -> UsartX_WorkDrv() );
        sUSART1.uart_status=0;
        uart_init1();
        OFF(SET_USART1_TX);
        OFF(SET_USART1_RX);
      #if UART1_MASTER
        UCSR1B=(1<<TXEN1)|(1<<TXCIE1);   //разрешение передатчика
        ON(SET_USART1_TX);
        ON(SET_USART1_RX);
        _delay_us(100);
        UDR1='#';
      #else
        UCSR1B=(1<<RXEN1)|(1<<RXCIE1);
      #endif
        
      #if !UART1_MASTER
        Sleep(5);
      #else
        sUSART1.efUSART_TX.Wait(100);          //Ждет ответа от раба ( 100 умножить 1.1(1) мс )
      #endif
    }
} // TUART1::Exec()

} // namespace OS