#ifndef  __USART_DEF_H
    #define  __USART_DEF_H

#include <NetPack.h>

//----------------------------------------------------------------------
//
//      Привет USART0
//

UART1_SET (LCDkey, 0x20, 'S', lcd_data, key_data)

UART1_SET (Mnemo01, 0x30, 'd', mnemo[ 0], mnemo_in[ 0])
UART1_SET (Mnemo02, 0x31, 'd', mnemo[ 1], mnemo_in[ 1])
UART1_SET (Mnemo03, 0x32, 'd', mnemo[ 2], mnemo_in[ 2])
UART1_SET (Mnemo04, 0x33, 'd', mnemo[ 3], mnemo_in[ 3])

UART1_SET (VIT, 0x7F, 'd', data_for_vit, data_from_vit)

NetTransferConstrol * pUSART1_info[] =
{
    &Mnemo01,
    &LCDkey,
    &Mnemo02,
    &LCDkey,
    &Mnemo03,
    &LCDkey,
    &Mnemo04,
    &LCDkey,
    &VIT,
    &LCDkey,
};

UART0_SET (BFPP0,  0xB1, 'd', data_for_bfpp[ 0], data_from_bfpp[ 0])
UART0_SET (BFPP1,  0xB2, 'd', data_for_bfpp[ 1], data_from_bfpp[ 1])
UART0_SET (BFPP2,  0xB3, 'd', data_for_bfpp[ 2], data_from_bfpp[ 2])
UART0_SET (BFPP3,  0xB4, 'd', data_for_bfpp[ 3], data_from_bfpp[ 3])
UART0_SET (BFPP4,  0xB5, 'd', data_for_bfpp[ 4], data_from_bfpp[ 4])

UART0_SET (SCHPZ, 0x60, 'd', data_for_slave, data_from_slave)

NetTransferConstrol * pUSART0_info[] =
{
    &BFPP0,
    &BFPP1,
    &BFPP2,
    &BFPP3,
    &BFPP4,

    &SCHPZ,
};

#endif /* __USART_DEF_H */
