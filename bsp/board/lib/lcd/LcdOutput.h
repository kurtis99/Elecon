#ifndef LCDOUTPUT
    #define LCDOUTPUT

    #include <avr/pgmspace.h>
    
    #define LEAD_ZERO  0x40 //ставить впереди 0
	#define LEFT_ALIGN 0x80
	
	#define CLEAR_LENGTH(b) ((b)&0x3f)//младшие 6 битов на длину

    extern char LCD_str[];

	extern void LCD_uind16 ( uint16_t _num, uint8_t _ind, uint8_t _cntr);
	extern void LCD_float ( int16_t _num, uint8_t _base, uint8_t _pos);  
	extern void LCD_putc ( uint8_t _sym, uint8_t _pos);  
	extern void LCD_uind ( uint16_t _num, uint8_t _ind, uint8_t _cntr);    
	extern void LCD_abc ( const char *_str, uint8_t _pos);	
    extern void LCD_ind ( int16_t _num, uint8_t _ind, uint8_t _cntr);

#endif LCDOUTPUT