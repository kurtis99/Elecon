#include "LCD.h"
#include <avr/pgmspace.h>

#include <LCD_simb.h>

const uint8_t LCD_digits111[] =
{
    '0','1','2','3','4','5','6','7',
    '8','9','A','B','C','D','E','F',
};

C_Lcd& C_Lcd::operator << ( const char * pBuffer )
{
    uint8_t i = 0;

    for(;;) {
        if( 0x00 == pgm_read_byte( &pBuffer[i] ) ) {
            break;
        }
        if( i >= ( MAX_LENGTH * MAX_ROWS ) ) {
            break;
        }
        LCD_str[posXY.get()] = pgm_read_byte( &LCD_simb[ pgm_read_byte( &pBuffer[i] ) ] );
        i++;
        posXY++;
    }

    return *this;
}

C_Lcd& C_Lcd::operator << ( uint16_t _num )
{
    uint16_t num_temp;
    uint8_t num_dig = 1;
    uint8_t i, length;
    uint8_t uind_str[MAX_WORD_DIGS123];

    // TODO:
    // Длинна вывода вроде как должна от чего-то зависеть, ПОДУМАТЬ!
    length = 4;

//----------------------------------------------
//count number of digits in _num
    num_temp=_num;
    for(i=1;i<6;i++)
    {
        uind_str[i-1]=pgm_read_byte(&LCD_digits111[num_temp%10]);
        if(num_temp<10) break;
        num_temp/=10;
        num_dig++;
    }

    if(num_dig>length) 
        num_dig=length;

    for(i=0;i<num_dig;i++)
    {
//        if(!(_cntr&LEFT_ALIGN))
//        {
//            LCD_str[length-i-1]=uind_str[i];
//        }
//        else
        {
            LCD_str[posXY.get()]=uind_str[num_dig-i-1];
            posXY++;
        }
    }
    /*if(_cntr&LEAD_ZERO)
    {
        if(!(_cntr&LEFT_ALIGN))
        {
            if(num_dig<length)
            {
                for(i=0;i<num_dig;i++)
                {
                    LCD_str[_pos+i]='0';
                }
            }
        }
    }*/

    return * this;
}

C_Lcd& C_Lcd::operator << ( int16_t _num )
{
    if ( _num < 0 ) {
        * this << '-';
        _num *= -1;
    }

    * this << ( uint16_t )_num;

    return * this;
}

C_Lcd& C_Lcd::operator << ( char char_sym )
{
    LCD_str[posXY.get()] = char_sym;
    posXY++;

    return * this;
}

C_Lcd& C_Lcd::operator << ( FloatNumber _fNum )
{
    //uint16_t _pos1 = 20;// max,temp;
    int16_t num_temp;
    uint8_t num_dig=1, i;
    uint8_t uind_str[5];
    
//----------------------------------------------
//count number of digits in _num
    num_temp=_fNum.num;
    if(num_temp<0) {
        num_temp=-num_temp;
        num_dig++;
    }
    for(i=1;i<6;i++)
    {
        uind_str[i-1]=pgm_read_byte(&LCD_digits111[num_temp%10]);
        if(num_temp<10) break;
        num_temp/=10;
        num_dig++;
    }
    if(num_dig+PositionX-1>31) 
        return * this;
    if(_fNum.num<0) {
        * this << '-';
        //_pos1++;
        num_dig--;
    }
    //if(num_dig==1) LCD_str[_pos1++]='0';
    if(_fNum.base>=num_dig) {
        for(i=0;i<=_fNum.base-num_dig;i++)
        {
            LCD_str[PositionX]='0';
            IncPosotionX();
        }
    }
    for(i=1;i<=num_dig;) {
        if(_fNum.base==num_dig-i+1) { 
            LCD_str[PositionX]='.';
            IncPosotionX();
        }
        LCD_str[PositionX]=uind_str[num_dig-i];
        i++;
        IncPosotionX();
    }

    return * this;
}

// вроде как не нужно, следует в будущем убрать!
unsigned char C_Lcd::itoa(unsigned int uiVal, char * pBuff)
{
    unsigned char ucIndex  = 0;
    unsigned char ucHelper = 0;
    unsigned char ucLenght = 0;
    char cDigit;

    do 
    {
        cDigit = '0' + uiVal%10;
        pBuff[ucIndex++] = cDigit;
        uiVal /= 10;
    } while ( uiVal );

    ucLenght = ucIndex;
    pBuff[ucIndex--] = 0;

    while ( ucHelper < ucIndex ) {
        cDigit = pBuff[ucIndex];
        pBuff[ucIndex--]  = pBuff[ucHelper];
        pBuff[ucHelper++] = cDigit;
    }

    return ucLenght;
};

// Это атавизм, от которого стоит избавиться
void C_Lcd::LcdScreenInitialization()
{
    PositionX = 0;
};
void C_Lcd::LcdNewLine()
{
    PositionX = MAX_LENGTH;
};
