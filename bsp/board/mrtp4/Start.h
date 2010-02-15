#ifndef __START_H
	#define __START_H

    #include <avr/io.h>
    #include <pin_macros.h>
    #include <Iic.h>

    /* Скорость работы УАПП, используется в ф-ции start_init(void)*/
	#if 1
		#define BAUDRATE_USART0 38400
		#define BAUDRATE_USART1 57600
	#else
		#define BAUDRATE_USART0 57600
		#define BAUDRATE_USART1 57600
	#endif


    extern void start_init(void) __attribute__ ((naked)) __attribute__ ((section (".init5")));

#endif /* __START_H */
