#include <avr/io.h>
#include <avr/delay.h>
#include "Peripheral.h"

using namespace nMSK;

static uint8_t read_data_low(uint8_t adr);
static void set_data_low(uint8_t data, uint8_t adr);
#if I_HAVE_IMVV
static void imvv_mskconv(uint8_t* msk);
#endif
static void outconv();
static void inconv();

uint8_t KEY[2] = {0, 0};        //отфильтрованое состояние кнопок пульта
uint8_t MT[2];                  //выдача на МТ
uint8_t MSK[8];                 //отфильтрованное значение МСК
uint8_t MSK_FLT_TMP[64];        //фильтр МСК
uint8_t OS_MT[2];               //прием ОС
uint8_t MSK_FIELD[64];          // Отфилтрованное МСК

static void set_data_low(uint8_t data, uint8_t adr)//запись данных через ALS138D
{
    PORTD |=  CDC3;
    DDRA   =  0xff;
    PORTA  =~ data;                 //выдача данных в порт
    PORTD &=~ (CDC0|CDC1|CDC2);     //сброс всех бит адреса
    PORTD |=  (adr<<4);             //Установка адреса на ALS138D
    PORTD &=~ CDC3;                 //включение защелки

    asm("nop");

    PORTD |=  CDC3;                 //выключение защелки
    DDRA   =  0x00;
    PORTA  =  0xff;
}

static uint8_t read_data_low(uint8_t adr)//чтение данных через ALS138D
{
    uint8_t temp;
    PORTD |=  CDC3;
    DDRA   =  0x00;
    PORTA  =  0xff;
    PORTD &=~ (CDC0|CDC1|CDC2);     //сброс всех бит адреса
    PORTD |=  (adr<<4);             //Установка адреса на ALS138D
    PORTD &=~ CDC3;                 //включение защелки

    asm("nop");

    temp   =  PINA;                 //чтение данных из порта
    PORTD |=  CDC3;                 //выключение защелки

    return ~temp;
}

void low_drv()
{
    inconv();

    set_data_low(MT[0],CS0);        //выдача МТ[0]
    OS_MT[0]=read_data_low(CS1);    //чтение ОС[0]
    set_data_low(MT[1],CS2);        //выдача МТ[1]
    OS_MT[1]=read_data_low(CS3);    //чтение ОС[1]

    /* Скобки не убирать, в конце скобок вызывается дыструктар который считает циклы МСК */
    {
        AskingMSK My_MSK ( read_data_low(CS5), MSK[ 7 - CurMskSelector ],  &MSK_FLT_TMP[ CurMskSelector*8 ] );
    }
    set_data_low(1<<CurMskSelector,CS4);        //засвечивание следующего столбца МСК
#if I_HAVE_IMVV
    imvv_mskconv(&imvv_in.Msk[0]);
#endif
    outconv();
}

void low_init()
{
    set_data_low(0x00,CS0);//выдача МТ[0]
    set_data_low(0x00,CS2);//выдача МТ[1]
}

static void outconv()
{
    uint8_t i,j;

    for(i=0;i<8;i++) {
        for(j=0;j<8;j++) {
            MSK_FIELD[i*8+j/*+Mr_Jumbo*/]=MSK[i]&(1<<j);
        }
    }

    for(i=0;i<2;i++) {
        for(j=0;j<8;j++) {
            OS_MT[i]&(1<<j) ? IoField[i*8+j].Os.Set() : IoField[i*8+j].Os.Clear();
        }
    }
#if I_HAVE_IMVV
    for(i=0;i<4;i++) {
        for(j=0;j<4;j++) {
            imvv_in.Os[i] & ( 1 << j ) ? ImvvField[i*4+j].Os.Set() : ImvvField[i*4+j].Os.Clear();
        }
    }
#endif
}

static void inconv()
{
    uint8_t i,j;

    for(i=0;i<2;i++)
        for(j=0;j<8;j++)
            IoField[i*8+j].Out.Check() ? MT[i] |= ( 1 << j ) : MT[i] &= ~( 1 << j );
#if I_HAVE_IMVV
    for(i=2;i<4;i++)
        for(j=0;j<8;j++)
            ImvvField[(i-2)*8+j].Out.Check() ? imvv_out.imvv_out[i] &= ~( 1 << j ) : imvv_out.imvv_out[i] |= ( 1 << j );
#endif
}

#if I_HAVE_IMVV
static void imvv_mskconv(uint8_t* msk)
{
    uint8_t temp_msk[16];
    uint8_t i=8,j=0,shift=0;

    do
    {
        i-=2;
        if( !shift ) {
            temp_msk[j]=msk[i]&0xf;
            temp_msk[j+2]=(msk[i]&0xf0)>>4;
            temp_msk[j+4]=msk[i+1]&0xf;
            temp_msk[j+6]=(msk[i+1]&0xf0)>>4;
            shift=1;
        } else {
            temp_msk[j]|=(msk[i]&0xf)<<4;
            temp_msk[j+2]|=(msk[i]&0xf0);
            temp_msk[j+4]|=(msk[i+1]&0xf)<<4;
            temp_msk[j+6]|=(msk[i+1]&0xf0);
            shift=0;
            j++;
        }
        if( !i )
            i=16,j=8;
    } while( i!=8 );

    for(i=0;i<16;i++) {
        for(j=0;j<8;j++) {
            IMVV_MSK[i*8+j]=temp_msk[i]&(1<<j);
        }
    }
}
#endif
