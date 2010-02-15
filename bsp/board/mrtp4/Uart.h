#ifndef UART_INC
#define UART_INC

#include <avr/io.h>
#include <pin_macros.h>

#include <struct_define.h>

const unsigned char  UART_RX_OK = (1 << 0); //uart_status
const unsigned char  UART_TX_OK = (1 << 1); //uart_status

const unsigned char MAX_LENGTH_RX_BUFFER0 = 200;
const unsigned char MAX_LENGTH_TX_BUFFER0 = 200;
const unsigned char MAX_LENGTH_RX_BUFFER1 = 200;
const unsigned char MAX_LENGTH_TX_BUFFER1 = 200;

extern USART_CONF sUSART0, sUSART1;

extern uint8_t rx_local_buffer0[MAX_LENGTH_RX_BUFFER0];
extern uint8_t tx_local_buffer0[MAX_LENGTH_TX_BUFFER0];

extern uint8_t rx_local_buffer1[MAX_LENGTH_RX_BUFFER1];
extern uint8_t tx_local_buffer1[MAX_LENGTH_TX_BUFFER1];

extern uint8_t rx_uart_old_value0;
extern uint8_t return_value0;
extern uint8_t rx_uart_old_value1;
extern uint8_t return_value1;

#define SPLIT	1
#define STRING	2

inline uint8_t hex_to_ASCII (uint8_t hex_to_ASCII_temp)
{
    hex_to_ASCII_temp&=0x0F;
    if ( hex_to_ASCII_temp>9 )	{
		hex_to_ASCII_temp+=7; //определение ASCII кода hex числа 9=39 A=41
	}
    return hex_to_ASCII_temp+=0x30;
}
                          //rx_data             USART_data
inline uint8_t ASCII_to_hex (uint8_t ASCII_to_hex_temp1, uint8_t ASCII_to_hex_temp2)
{
    ASCII_to_hex_temp1-=0x30;
    if ( ASCII_to_hex_temp1>9 ) {
		ASCII_to_hex_temp1-=7;
	}
    ASCII_to_hex_temp2-=0x30;
    if ( ASCII_to_hex_temp2>9 ) {
		ASCII_to_hex_temp2-=7;
	}
    return ((ASCII_to_hex_temp1<<4)&0xF0)+(ASCII_to_hex_temp2&0x0F);
}

inline uint8_t  Receive_buffer_uart0(uint8_t adr)
{
    /*static uint8_t rx_uart_old_value0;*/
    /*static uint8_t return_value0;*/

	uint8_t temp,UDR_temp;

	UDR_temp=UDR0;
	switch(sUSART0.uart_switcher)
	{
		case 0:// receive # or !
		{
            sUSART0.uart_flags &= ~SPLIT;

#if UART0_MASTER
			if(UDR_temp=='!')
			{
				sUSART0.uart_switcher=1;
				return_value0=1;
			}
#else
			if(UDR_temp=='#')
			{
				sUSART0.uart_switcher=1;
				return_value0=1;
			}
#endif
			else
			return_value0=0;
			break;
		}
		case 1: //receive adr
		{
			if(sUSART0.uart_flags&SPLIT)
			{
				temp=ASCII_to_hex(rx_uart_old_value0,UDR_temp);
				if(temp==adr)
				{
					sUSART0.uart_flags&=~SPLIT;
					sUSART0.uart_checksum+=UDR_temp;
					*(rx_local_buffer0+1)=temp;
					sUSART0.uart_switcher=2;
				}
				else
				{
					return_value0=2;
				}
			}
			else
			{
				rx_uart_old_value0=UDR_temp;
				sUSART0.uart_flags|=SPLIT;
				sUSART0.uart_checksum=UDR_temp;
			}
			break;
		}
		case 2: //receive cmd
		{
			if(UDR_temp<0x60)
			{
				sUSART0.uart_flags|=STRING;
			}
			else
			{
				sUSART0.uart_flags&=~STRING;
			}
			sUSART0.uart_checksum+=UDR_temp;
			*(rx_local_buffer0+2)=UDR_temp;
			sUSART0.uart_counter=2;//num+adr+cmd
			sUSART0.uart_switcher=3;
			break;
		}
		case 3: //receive to 0x0d
		{
			if(sUSART0.uart_flags&STRING)
			{
				if(UDR_temp==0x0d)
				{
					sUSART0.uart_checksum-=*(rx_local_buffer0+sUSART0.uart_counter);// отмотка CRC2
					sUSART0.uart_checksum-=*(rx_local_buffer0+sUSART0.uart_counter-1);// отмотка CRC1
					sUSART0.uart_checksum-=*(rx_local_buffer0+sUSART0.uart_counter-2);// отмотка k
					temp=*(rx_local_buffer0+sUSART0.uart_counter-2);
					if(!((temp=='k')||(temp=='K'))) //no k or K before checksum
					{
						return_value0=2;
					}
					else
					{
						if(sUSART0.uart_checksum==ASCII_to_hex(*(rx_local_buffer0+sUSART0.uart_counter-1),
							*(rx_local_buffer0+sUSART0.uart_counter)))
						{
							*rx_local_buffer0=sUSART0.uart_counter-3;
							return_value0=3; //end of receiving
						}
						else
						{
							return_value0=2;
						}
					}
				}
				else
				{
					sUSART0.uart_checksum+=UDR_temp;
					sUSART0.uart_counter++;
					*(rx_local_buffer0+sUSART0.uart_counter)=UDR_temp;
				}
			}
			else//not STRING
			{
				if((UDR_temp=='k')||(UDR_temp=='K'))
				{
					sUSART0.uart_switcher=4;
				}
				if(sUSART0.uart_flags&SPLIT)
				{
					temp=ASCII_to_hex(rx_uart_old_value0,UDR_temp);
					sUSART0.uart_flags&=~SPLIT;
					sUSART0.uart_checksum+=temp;
					sUSART0.uart_counter++;
					*(rx_local_buffer0+sUSART0.uart_counter)=temp;
				}
				else
				{
					rx_uart_old_value0=UDR_temp;
					sUSART0.uart_flags|=SPLIT;
				}
			}
			break;
		}
		case 4:// receive CRC1
		{
			rx_uart_old_value0=UDR_temp;
			sUSART0.uart_switcher=5;
			break;
		}
		case 5:// receive CRC2
		{
			if(sUSART0.uart_checksum==ASCII_to_hex(rx_uart_old_value0,UDR_temp))
			{
				sUSART0.uart_switcher=6;
			}
			else
			{
				return_value0=2;
			}
			break;
		}
		case 6:
		{
			if(UDR_temp==0x0d)
			{
				*(rx_local_buffer0) = sUSART0.uart_counter+1;
				return_value0=3; // end of receiving
			}
			else
			{
				return_value0=2;
			}
			break;
		}
	}//rx_uart_switcher
	return return_value0;
}
inline uint8_t  Receive_buffer_uart1(uint8_t adr)
{
    /*static uint8_t rx_uart_old_value1;*/
    /*static uint8_t return_value1;*/

	uint8_t temp,UDR_temp;
	UDR_temp=UDR1;
	switch(sUSART1.uart_switcher)
	{
		case 0:// receive # or !
		{
#if UART1_MASTER
			if(UDR_temp=='!')
			{
				sUSART1.uart_switcher=1;
				return_value1=1;
			}

#else
			if(UDR_temp=='#')
			{
				sUSART1.uart_switcher=1;
				return_value1=1;
			}
#endif
			else
			return_value1=0;
			break;
		}
		case 1: //receive adr
		{
			if(sUSART1.uart_flags&SPLIT)
			{
				temp=ASCII_to_hex(rx_uart_old_value1,UDR_temp);
				if(temp==adr)
				{
					sUSART1.uart_flags&=~SPLIT;
					sUSART1.uart_checksum+=UDR_temp;
					*(rx_local_buffer1+1)=temp;
					sUSART1.uart_switcher=2;
				}
				else
				{
					return_value1=2;
				}
			}
			else
			{
				rx_uart_old_value1=UDR_temp;
				sUSART1.uart_flags|=SPLIT;
				sUSART1.uart_checksum=UDR_temp;
			}
			break;
		}
		case 2: //receive cmd
		{
			if(UDR_temp<0x60)
			{
				sUSART1.uart_flags|=STRING;
			}
			else
			{
				sUSART1.uart_flags&=~STRING;
			}
			sUSART1.uart_checksum+=UDR_temp;
			*(rx_local_buffer1+2)=UDR_temp;
			sUSART1.uart_counter=2;//num+adr+cmd
			sUSART1.uart_switcher=3;
			break;
		}
		case 3: //receive to 0x0d
		{
			if(sUSART1.uart_flags&STRING)
			{
				if(UDR_temp==0x0d)
				{
					sUSART1.uart_checksum-=*(rx_local_buffer1+sUSART1.uart_counter);// отмотка CRC2
					sUSART1.uart_checksum-=*(rx_local_buffer1+sUSART1.uart_counter-1);// отмотка CRC1
					sUSART1.uart_checksum-=*(rx_local_buffer1+sUSART1.uart_counter-2);// отмотка k
					temp=*(rx_local_buffer1+sUSART1.uart_counter-2);
					if(!((temp=='k')||(temp=='K'))) //no k or K before checksum
					{
						return_value1=2;
					}
					else
					{
						if(sUSART1.uart_checksum==ASCII_to_hex(*(rx_local_buffer1+sUSART1.uart_counter-1),
							*(rx_local_buffer1+sUSART1.uart_counter)))
						{
							*rx_local_buffer1=sUSART1.uart_counter-3;
							return_value1=3; //end of receiving
						}
						else
						{
							return_value1=2;
						}
					}
				}
				else
				{
					sUSART1.uart_checksum+=UDR_temp;
					sUSART1.uart_counter++;
					*(rx_local_buffer1+sUSART1.uart_counter)=UDR_temp;
				}
			}
			else//not string
			{
				if((UDR_temp=='k')||(UDR_temp=='K'))
				{
					sUSART1.uart_switcher=4;
				}
				if(sUSART1.uart_flags&SPLIT)
				{
					temp=ASCII_to_hex(rx_uart_old_value1,UDR_temp);
					sUSART1.uart_flags&=~SPLIT;
					sUSART1.uart_checksum+=temp;
					sUSART1.uart_counter++;
					*(rx_local_buffer1+sUSART1.uart_counter)=temp;
				}
				else
				{
					rx_uart_old_value1=UDR_temp;
					sUSART1.uart_flags|=SPLIT;
				}
			}
			break;
		}
		case 4:// receive CRC1
		{
			rx_uart_old_value1=UDR_temp;
			sUSART1.uart_switcher=5;
			break;
		}
		case 5:// receive CRC2
		{
			if(sUSART1.uart_checksum==ASCII_to_hex(rx_uart_old_value1,UDR_temp))
			{
				sUSART1.uart_switcher=6;
			}
			else
			{
				return_value1=2;
			}
			break;
		}
		case 6:
		{
			if(UDR_temp==0x0d)
			{
				*(rx_local_buffer1) = sUSART1.uart_counter+1;
				return_value1=3; // end of receiving
			}
			else
			{
				return_value1=2;
			}
			break;
		}
	}//rx_uart_switcher

    return return_value1;
}

inline void     Transmitt_buffer_uart0()
{
	uint8_t temp;

	switch(sUSART0.uart_switcher)
	{
		case 0: //transmitt adr
		{
			temp=tx_local_buffer0[1];
			if ( sUSART0.uart_flags & SPLIT ) {
				temp=hex_to_ASCII(temp);
				sUSART0.uart_flags&=~SPLIT;
				sUSART0.uart_checksum+=temp;
				sUSART0.uart_switcher=1;
				UDR0 = temp;
			} else {
				temp=hex_to_ASCII(temp>>4);
				sUSART0.uart_flags|=SPLIT;
				sUSART0.uart_checksum=temp;
				UDR0 = temp;
			}
			break;
		}
		case 1: //transmitt cmd
		{
			temp=tx_local_buffer0[2];
			if(temp<0x60)
			{
				sUSART0.uart_flags|=STRING;
			}
			sUSART0.uart_checksum+=temp;
			sUSART0.uart_counter=3;
			sUSART0.uart_switcher=2;
			if(sUSART0.uart_counter==tx_local_buffer0[0])
				{
					sUSART0.uart_switcher=3;
				}
			UDR0 = temp;
			break;
		}
		case 2: //transmitt to end of buffer
		{
			temp=tx_local_buffer0[sUSART0.uart_counter];
			if ( sUSART0.uart_flags&STRING ) {
				sUSART0.uart_checksum+=temp;
				sUSART0.uart_counter++;
				if ( sUSART0.uart_counter == tx_local_buffer0[0] ) {
					sUSART0.uart_switcher=3;
				}
				UDR0 = temp;
			} else {			//not STRING
				if ( sUSART0.uart_flags&SPLIT ) {
					temp=hex_to_ASCII(temp);
					sUSART0.uart_flags&=~SPLIT;
					sUSART0.uart_checksum+=tx_local_buffer0[sUSART0.uart_counter];
					sUSART0.uart_counter++;
					if ( sUSART0.uart_counter == tx_local_buffer0[0] ) {
						sUSART0.uart_switcher=3;
					}
					UDR0 = temp;
				} else {
					temp=hex_to_ASCII(temp>>4);
					sUSART0.uart_flags|=SPLIT;
					UDR0 = temp;
				}
			}
			break;
		}
		case 3:// transmitt 'k'
		{
			sUSART0.uart_switcher=4;
			UDR0 = 'k';
			break;
		}
		case 4:
		{
			if(sUSART0.uart_flags&SPLIT)
			{
				temp=hex_to_ASCII(sUSART0.uart_checksum);
				sUSART0.uart_flags&=~SPLIT;
				sUSART0.uart_switcher=5;
				UDR0 = temp;
			}
			else
			{
				temp=hex_to_ASCII(sUSART0.uart_checksum>>4);
				sUSART0.uart_flags|=SPLIT;
				UDR0 = temp;
			}
			break;
		}
		case 5:// transmitt 0x0d
		{
			sUSART0.uart_switcher=6;
			UDR0 = 0x0d;
			break;
		}
		case 6:
		{
			sUSART0.uart_switcher=0;
			OFF(SET_USART0_TX);
			UCSR0B&=~((1<<TXEN0)|(1<<TXCIE0));
#if UART0_MASTER
			UCSR0B=(1<<RXEN0)|(1<<RXCIE0);
#else
			sUSART0.uart_status|=UART_TX_OK;
#endif
			break;
		}
	}//tr_uart_switcher
}
inline void     Transmitt_buffer_uart1()
{
	uint8_t temp;
	switch(sUSART1.uart_switcher)
	{
		case 0: //transmitt adr
		{
			temp=tx_local_buffer1[1];
			if(sUSART1.uart_flags&SPLIT)
			{
				temp=hex_to_ASCII(temp);
				sUSART1.uart_flags&=~SPLIT;
				sUSART1.uart_checksum+=temp;
				sUSART1.uart_switcher=1;
				UDR1 = temp;
			}
			else
			{
				temp=hex_to_ASCII(temp>>4);
				sUSART1.uart_flags|=SPLIT;
				sUSART1.uart_checksum=temp;
				UDR1 = temp;
			}
			break;
		}
		case 1: //transmitt cmd
		{
			temp=tx_local_buffer1[2];
			if(temp<0x60)
			{
				sUSART1.uart_flags|=STRING;
			}
			sUSART1.uart_checksum+=temp;
			sUSART1.uart_counter=3;
			sUSART1.uart_switcher=2;
			if(sUSART1.uart_counter==tx_local_buffer1[0])
				{
					sUSART1.uart_switcher=3;
				}
			UDR1 = temp;
			break;
		}
		case 2: //transmitt to end of buffer
		{
			temp=tx_local_buffer1[sUSART1.uart_counter];
			if(sUSART1.uart_flags&STRING)
			{
				sUSART1.uart_checksum+=temp;
				sUSART1.uart_counter++;
				if(sUSART1.uart_counter==tx_local_buffer1[0])
				{
					sUSART1.uart_switcher=3;
				}
				UDR1 = temp;
			}
			else//not string
			{
				if(sUSART1.uart_flags&SPLIT)
				{
					temp=hex_to_ASCII(temp);
					sUSART1.uart_flags&=~SPLIT;
					sUSART1.uart_checksum+=tx_local_buffer1[sUSART1.uart_counter];
					sUSART1.uart_counter++;
					if(sUSART1.uart_counter==tx_local_buffer1[0])
					{
						sUSART1.uart_switcher=3;
					}
					UDR1 = temp;
				}
				else
				{
					temp=hex_to_ASCII(temp>>4);
					sUSART1.uart_flags|=SPLIT;
					UDR1 = temp;
				}
			}
			break;
		}
		case 3:// transmitt 'k'
		{
			sUSART1.uart_switcher=4;
			UDR1 = 'k';
			break;
		}
		case 4:
		{
			if(sUSART1.uart_flags&SPLIT)
			{
				temp=hex_to_ASCII(sUSART1.uart_checksum);
				sUSART1.uart_flags&=~SPLIT;
				sUSART1.uart_switcher=5;
				UDR1 = temp;
			}
			else
			{
				temp=hex_to_ASCII(sUSART1.uart_checksum>>4);
				sUSART1.uart_flags|=SPLIT;
				UDR1 = temp;
			}
			break;
		}
		case 5:// transmitt 0x0d
		{
			sUSART1.uart_switcher=6;
			UDR1 = 0x0d;
			break;
		}
		case 6:
		{
			sUSART1.uart_switcher=0;
            OFF(SET_USART1_TX);
            OFF(SET_USART1_RX);
			UCSR1B&=~((1<<TXEN1)|(1<<TXCIE1));
#if UART1_MASTER
			UCSR1B=(1<<RXEN1)|(1<<RXCIE1);
#else
			sUSART1.uart_status |= UART_TX_OK;
#endif
			break;
		}
	}//tr_uart_switcher
}

extern uint8_t  rx_local_buffer0[];
extern uint8_t  tx_local_buffer0[];

extern uint8_t  rx_local_buffer1[];
extern uint8_t  tx_local_buffer1[];

extern uint8_t  hex_to_ASCII(uint8_t hex_to_ASCII_temp);

extern void     uart_init0();
extern void     uart_init1();

#endif
