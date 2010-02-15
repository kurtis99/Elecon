#include "NetPack.h"

#include <Usart_def.h>

//---------------------------------------------------------------------------
//
//      Я хз что это такое но без него ничего не будет работать!!!
//

USART_control cUSART0 ( sUSART0, pUSART0_info, NUM_OF_USART0 );
USART_control cUSART1 ( sUSART1, pUSART1_info, NUM_OF_USART1 );

USART_control * pMegoUSART[] =
{
    &cUSART0,
    &cUSART1,
};

uint8_t USART_control::UsartX_WorkDrv()
{
    /* Если перед получением данных нам нужно срочно что-то сделать */
    pUSART_info[sUSART.switcher] -> ReceiveWork();

    if ( ( sUSART.uart_status ) & UART_RX_OK ) {
        ( sUSART.uart_status ) &= ~UART_RX_OK;
                        /* Хреньпринимание */
        pUSART_info[sUSART.switcher] -> data_recv();
    } else {
        pUSART_info[sUSART.switcher] -> inc_error_packet();
    }
    usart_inc();

    /* Если перед отправкой нам нужно срочно что-то сделать */
    pUSART_info[sUSART.switcher] -> SendWork();
                    /* Хреньпередавание */
    if ( !(status & NOTHING_TO_SEND ) ) {
        pUSART_info[sUSART.switcher] -> data_send();
    }

    return pUSART_info[sUSART.switcher] -> get_send_adr();
}

void USART_control::usart_inc()
{
    ( sUSART.switcher )++;
    if ( NumOfUSART != 0 ) {
        if ( sUSART.switcher > NumOfUSART - 1 )
            ( sUSART.switcher ) = 0;
        status &= ~NOTHING_TO_SEND;
    } else {
        status |=  NOTHING_TO_SEND;
    }
}
/***************************************************
****************************************************
****************************************************/

void NetTransferConstrol::data_send()
{
    //Mr.Rabbit

    if ( Precv_arr != (uint8_t *) &I_AM_NULL ) {
        memcpy( (uint8_t*) ( uart_tx_buffer ),
                (uint8_t*) ( Precv_arr ),
                size_sendmail );
    /* так исторически сложилось */
        *(uart_tx_buffer+0) = size_sendmail;
        *(uart_tx_buffer+1) = send_addr;
        *(uart_tx_buffer+2) = data_info;
    }
}

void NetTransferConstrol::data_recv()
{
    ErrorNetPack = 0;

//    if ( Psend_arr != (uint8_t *) & I_AM_NULL ) {
        memcpy( (uint8_t*) ( Psend_arr ),
                (uint8_t*) ( uart_rx_buffer ),
                size_recvmail );
//    }
}

void NetTransferConstrol::inc_error_packet()
{
    ErrorNetPack++;
    if (ErrorNetPack > 250)
        ErrorNetPack = I_HAVE_NO_NET+1;

    if ( ErrorNetPack > I_HAVE_NO_NET ) {
        status |= NET_PACKET_OVRF;
    }
}
