#include "LcdOutput.h"

    #include <LCD_simb.h>
    #include <Global_define.h>

//================== Функции отображения на ЖК==============
const uint8_t LCD_digits[] =
{
    '0','1','2','3','4','5','6','7',
    '8','9','A','B','C','D','E','F',
};

#define MAX_WORD_DIGS 5

void LCD_uind(uint16_t _num, uint8_t _ind, uint8_t _cntr)
{
    uint16_t _pos = _ind,/* max,temp,*/num_temp;
    uint8_t num_dig=1, i, length;
    uint8_t uind_str[MAX_WORD_DIGS];

    length = _cntr&0x3F;
//----------------------------------------------
//count number of digits in _num
    num_temp=_num;
    for(i=1;i<6;i++)
    {
        uind_str[i-1]=LCD_digits[num_temp%10];
        if(num_temp<10) break;
        num_temp/=10;
        num_dig++;
    }

    if(length+_pos-1>(MAX_LENGTH*2)-1) return;
    if(num_dig>length) num_dig=length;

    for(i=0;i<num_dig;i++)
    {
        if(!(_cntr&LEFT_ALIGN))
        {
            LCD_str[_pos+length-i-1]=uind_str[i];
        }
        else
        {
            LCD_str[_pos+i]=uind_str[num_dig-i-1];
        }
    }
    if(_cntr&LEAD_ZERO)
    {
        if(!(_cntr&LEFT_ALIGN))
        {
            if(num_dig<length)
            {
                for(i=0;i<length-num_dig;i++)
                {
                    LCD_str[_pos+i]='0';
                }
            }
        }
    }
    return;
}

void LCD_uind16(uint16_t _num, uint8_t _ind, uint8_t _cntr)
{
    uint16_t _pos = _ind,/* max,temp,*/num_temp;
    uint8_t num_dig=1, i, length;
    uint8_t uind_str[4];

    length = _cntr&0x3F;
//----------------------------------------------
//count number of digits in _num
    num_temp=_num;
    for(i=1;i<4;i++)
    {
        uind_str[i-1]=LCD_digits[num_temp%16];
        if(num_temp<16) break;
        num_temp/=16;
        num_dig++;
    }

    if(length+_pos-1>(MAX_LENGTH*2)-1) return;
    if(num_dig>length) num_dig=length;

    for(i=0;i<num_dig;i++)
    {
        if(!(_cntr&LEFT_ALIGN))
        {
            LCD_str[_pos+length-i-1]=uind_str[i];
        }
        else
        {
            LCD_str[_pos+i]=uind_str[num_dig-i-1];
        }
    }
    if(_cntr&LEAD_ZERO)
    {
        if(!(_cntr&LEFT_ALIGN))
        {
            if(num_dig<length)
            {
                for(i=0;i<length-num_dig;i++)
                {
                    LCD_str[_pos+i]='0';
                }
            }
        }
    }
    return;
}

void LCD_ind(int16_t _num, uint8_t _ind, uint8_t _cntr)
{
    if(!(_ind<(MAX_LENGTH*2))) return;
//-----------------------------------------------
//if negative, set leading MINUS
    if(_num<0)
    {
        LCD_str[_ind++] = '-';
        _num=-_num;
        _cntr = (_cntr&LEAD_ZERO)|((CLEAR_LENGTH(_cntr)-1));
    }
    LCD_uind(_num, _ind, _cntr);
}


void LCD_abc(const char *_str, uint8_t _pos)
{
    uint8_t i = _pos;
    //size_t _strlen;
    uint8_t _strlen;
    uint8_t lcd_temp[(MAX_LENGTH*2)];
    _strlen=strlen_P(_str);

    if(_strlen>((MAX_LENGTH*2)-_pos)) _strlen=(MAX_LENGTH*2)-_pos;

    strncpy_P((char*)(&lcd_temp),_str,_strlen+1);

    while(i<(MAX_LENGTH*2))
    {
        if(lcd_temp[i-_pos]==0x00)
            break;
        LCD_str[i] = pgm_read_byte(&LCD_simb[lcd_temp[i-_pos]]);
        ++i;
    }
}

void LCD_putc(uint8_t _sym, uint8_t _pos)
{
    if(_pos<(MAX_LENGTH*2))	LCD_str[_pos] = _sym;
}

void LCD_float(int16_t _num, uint8_t _base, uint8_t _pos)
{
    uint16_t _pos1 = _pos;// max,temp;
    int16_t num_temp;
    uint8_t num_dig=1, i;
    uint8_t uind_str[5];

//----------------------------------------------
//count number of digits in _num
    num_temp=_num;
    if(num_temp<0)
    {
        num_temp=-num_temp;
        num_dig++;
    }

    for(i=1;i<6;i++)
    {
        uind_str[i-1]=LCD_digits[num_temp%10];
        if(num_temp<10) break;
        num_temp/=10;
        num_dig++;
    }

    if(num_dig+_pos1-1>(MAX_LENGTH*2)-1) return;
    if(_num<0)
    {
        LCD_putc('-',_pos1);
        _pos1++;
        num_dig--;
    }
    //if(num_dig==1) LCD_str[_pos1++]='0';
    if(_base>=num_dig)
    {
        for(i=0;i<=_base-num_dig;i++)
        {
            LCD_str[_pos1++]='0';
        }
    }
    for(i=1;i<=num_dig;)
    {
        if(_base==num_dig-i+1) LCD_str[_pos1++]='.';
        LCD_str[_pos1++]=uind_str[num_dig-i];
        i++;
    }
}
