#include "Main.h"
#include <avr/wdt.h>

/* Создаем интерфейс работы с ЖКИ */
C_Lcd LCD;

volatile uint8_t sec_tik;
volatile uint32_t timer_count;

NET_BFPP_OUTPUT_STRUCT  data_for_bfpp[NUM_OF_BFPP];
NET_BFPP_INPUT_STRUCT   data_from_bfpp[NUM_OF_BFPP];

MNEMO_OUTPUT_STRUCT     mnemo[NUM_OF_MNEMO];
MNEMO_INPUT_STRUCT      mnemo_in[NUM_OF_MNEMO];

/* Не изменять, не удалять и не использовать!!! */
NULL_STRUCT I_AM_NULL;

VIT_OUTPUT_STRUCT       data_for_vit;
VIT_INPUT_STRUCT       data_from_vit;

LCD_OUTPUT_STRUCT lcd_data;
LCD_INPUT_STRUCT  key_data;

char LCD_str[(MAX_LENGTH*MAX_ROWS)];

uint8_t tech_fl;

uint8_t error_kog_num;
uint8_t error_kog_num_cpy;
uint8_t error_vzk_num;
uint8_t error_vzk_num_cpy;
uint8_t error_buzz_num;
uint8_t error_buzz_num_cpy;

STRUCT_FROM_CENTER  data_for_slave;
STRUCT_FOR_CENTER   data_from_slave;

typedef OS::process<OS::pr2, 150>   TTechnolog;
typedef OS::process<OS::pr3, 150>   TPeripheral;

//---------------------------------------------------------------------
//
//      Process objects
//

TTechnolog  Technolog;
TPeripheral Peripheral;

//---------------------------------------------------------------------
/* Подключаем аппаратнозависимые модули начальной инициализации */
#include <start.h>

extern uint8_t stop_sound;

int main()
{
    uint8_t i,j;

    //timer_count = 0;

    //  ReadRTC_RAM();//Привет
    //  if ((message_arch_byte[0] & WATCH_FL) |
    //      (message_arch_byte[0] & VCC_FL))
    //       RTC_Ram[4]=0XF;

    wdt_reset();
    wdt_disable();
    wdt_enable(WDTO_2S);


    /* Гасим мнемосхему */
    for (i=0;i<NUM_OF_MNEMO;i++) {
        for (j=0;j<80;j++) {
            mnemo[i].LED_FIELD[j] = NULL_LAMP;
        }
        mnemo[i].status=0x00;
    }

    /* Инициализацию кнопок нулями (на вский случай) */
    KEY[0] = 0x00;
    KEY[1] = 0x00;

    /* Начальная инициализация периферии */
    low_init();

    check_iic_status();
    Etaz_init();
    Work_init();
    Dev_init();
    Menu_init();
    Message_init();

    FireSrc = NoFire;

    stop_sound = 0xFF;

    /* Запуск операционной системы */
    OS::Run();
}

//---------------------------------------------------------------------
extern uint8_t MSK[8];                 //отфильтрованное значение МСК

namespace OS {  /* TTechnolog */

template<> OS_PROCESS void TTechnolog::Exec()
{
    static uint8_t WaitWhenIronIsReady=5;

    for (;;) {
        wdt_enable(WDTO_1S);

        if (sec_tik == 0x55) {
            mReady ^= 0xf0;
            timer_count++;
            sec_tik = 0;
        }

        tech_fl & NO_IIC ? tech_fl |= IIC_BUSY : tech_fl &= ~IIC_BUSY;

        if (!WaitWhenIronIsReady) {
            Pdz_drv();
            Check_BFPP();
            Etaz_drv();
            Work_drv();
            Dev_drv();
            Message_drv();
            all_ind();
        } else {
            if (!sec_tik)
                WaitWhenIronIsReady--;
        }

        //if (scafe_fl&MNEMO_WRK) {
            mnemo_test_work();
            //scafe_fl&=~MNEMO_WRK;
        //}

        MenuDrv();
        VIT_FIREFLOOR = FireFloor.GetVit();

        if (sec_tik == 0)
            sec_tik = 0xFF;

        Sleep(10);//С этим нада что-то делать, мы не можем так долго 
        // спать, но иначе не работают ЧРВ
    }
} // TTechnolog::Exec()

} // namespace OS

extern uint8_t LCD_light;
//---------------------------------------------------------------------
namespace OS {  /* TPeripheral */

template<> OS_PROCESS void TPeripheral::Exec()
{
    /* Инициализации процесса */

    for (;;) {
        wdt_enable(WDTO_1S);
        low_drv();

        if (tech_fl & SOUND) {
            lcd_data.out_lcd[0]='1';
            lcd_data.out_lcd[1]='5';
        }
        else if (!LCD_light) {
            lcd_data.out_lcd[0]='0';
            lcd_data.out_lcd[1]='0';
        }
        else {
            lcd_data.out_lcd[0]='0';
            lcd_data.out_lcd[1]='8';
        }
        memcpy((uint8_t*)&lcd_data.out_lcd[2],
               (uint8_t*)&LCD_str[0],
               MAX_LENGTH);
        lcd_data.out_lcd[MAX_LENGTH+2]='\\';
        lcd_data.out_lcd[MAX_LENGTH+3]='n';
        memcpy((uint8_t*)&lcd_data.out_lcd[MAX_LENGTH+4],
               (uint8_t*)&LCD_str[MAX_LENGTH],
               MAX_LENGTH);

        Sleep(10);
    }
} // TPeripheral::Exec()

} // namespace OS

//---------------------------------------------------------------------
//
//      Обработка переполнения таймера1
//
OS_INTERRUPT void TIMER1_COMPA_vect(void)
{
    OS::TISRW_SS ISRW;

    sec_tik = 0x55;

    OCR1AL = 0x40;
    OCR1AH = 0x38;
}

//??\
ХУЙ!

void * operator new(size_t size)
{
    return malloc(size);
}

void operator delete(void * ptr)
{
    free(ptr);
}

int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);};
void __cxa_guard_release (__guard *g) {*(char *)g = 1;};
void __cxa_guard_abort (__guard *) {};
void __cxa_pure_virtual(void) {};

//------    end of file  main.cpp   -----------------------------------
