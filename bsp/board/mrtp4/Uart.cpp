#include <Uart.h>
#include <avr/io.h>

uint8_t rx_local_buffer0[MAX_LENGTH_RX_BUFFER0] XBSS;
uint8_t tx_local_buffer0[MAX_LENGTH_TX_BUFFER0] XBSS;

uint8_t rx_local_buffer1[MAX_LENGTH_RX_BUFFER1] XBSS;
uint8_t tx_local_buffer1[MAX_LENGTH_TX_BUFFER1] XBSS;

USART_CONF sUSART0, sUSART1;

void uart_init0(void)
{
	sUSART0.uart_switcher=0;
	sUSART0.uart_checksum=0;
	sUSART0.uart_flags=0;
	sUSART0.uart_counter=0;
}

/*
	0 - ожидание ! или #
	1 - идет процесс приема пакета
	2 - ошибка приема
	3 - прием закончен нормально
*/

void uart_init1(void)
{
	sUSART1.uart_switcher=0;
	sUSART1.uart_checksum=0;
	sUSART1.uart_flags=0;
	sUSART1.uart_counter=0;
}

uint8_t rx_uart_old_value0;
uint8_t return_value0;

uint8_t rx_uart_old_value1;
uint8_t return_value1;

/*
	0 - ожидание ! или #
	1 - идет процесс приема пакета
	2 - ошибка приема
	3 - прием закончен нормально
*/

