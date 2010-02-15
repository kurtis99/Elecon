#include "Start.h"

void start_init(void) __attribute__ ((naked)) __attribute__ ((section (".init5")));

void start_init(void)
{

  #if defined (__AVR_ATmega128__)
    TCCR0 =  (1 << CS02);    // clk/64^M
    TIMSK |= (1 << TOIE0);

    TCCR3B =  (1 << CS32) | (1 << CS30) | ( 1 << WGM32 );    // clk/1024
    OCR3AL = 0x30;
    OCR3AH = 0x2A;
    ETIMSK |= ( 1 << OCIE3A );
  #elif defined (__AVR_ATmega1281__)
    TCCR0B =  (1 << CS01) | (1 << CS00 );    // clk/64
    TIMSK0 |= (1 << TOIE0);

    TCCR3B =  (1 << CS32) | (1 << CS30) | ( 1 << WGM32 );    // clk/1024
    OCR3AL = 0x30;
    OCR3AH = 0x2A;
    TIMSK3 |= ( 1 << OCIE3A );
  #else
    #error "Чувак, не тупи!"
  #endif

    /* Привет медвед!!! */
    MCUSR &= ~0x1f;

    DDRA = 0x00;
    DDRB = 0x00;
    DDRC = 0x00;
    DDRD = 0x00;
    DDRE = 0x00;
    DDRF = 0x00;
    DDRG = 0x00;
    PORTA = 0xFF;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;
    PORTF = 0x00;
    PORTG = 0x00;

    DDRD|=(1<<PD7)|(1<<PD6)|(1<<PD5)|(1<<PD4);
    DDRA=0xff;

    PORTD=0xff;
    PORTD&=~((1<<PD4)|(1<<PD6));

    DDRC=(1<<PC0)|(1<<PC2)|(1<<PC3);
    PORTC|=(1<<PC3);

    RAMPZ=0;

    /* TODO: дописать условие при котором это будет убираться */
    DRIVER(LED_BLINK1, OUT);
    DRIVER(LED_BLINK2, OUT);
    DRIVER(LED_BLINK3, OUT);
    DRIVER(LED_BLINK4, OUT);

    OFF(LED_BLINK1);
    OFF(LED_BLINK2);
    OFF(LED_BLINK3);
    OFF(LED_BLINK4);

    /* нициализация I2C шины */
    /* TODO: нужно ли? */
    DDRD  &= ~( ( 1<<SCL ) | ( 1<<SDA ) );
    PORTD &= ~( ( 1<<SCL ) | ( 1<<SDA ) );

    /* нициализация USART0 */
    UCSR0A=0x00;
    UCSR0B=(1<<RXCIE0)|(1<<RXEN0);                      // RXCIE_x RXEN_x, x-номер USART[0..3]
    UCSR0C=(1<<UCSZ01)|(1<<UCSZ00);                     // UCSZ_x_1 UCSZ_x_0, x-номер USART[0..3]
    UBRR0H=(F_CPU/(BAUDRATE_USART0*16L)-1) >> 8;        // calculate baudrate and set high byte
    UBRR0L=(uint8_t)(F_CPU/(BAUDRATE_USART0*16L)-1);    // and low byte

    /* нициализация USART1 */
    UCSR1A=0x00;
    UCSR1B=(1<<RXCIE1)|(1<<RXEN1);
    UCSR1C=(1<<UCSZ11)|(1<<UCSZ10);
    UBRR1H=(F_CPU/(BAUDRATE_USART1*16L)-1) >> 8;        // calculate baudrate and set high byte
    UBRR1L=(uint8_t)(F_CPU/(BAUDRATE_USART1*16L)-1);    // and low byte
}

