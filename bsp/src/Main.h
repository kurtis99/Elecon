#ifndef __MAIN_H
#define __MAIN_H

#include    <avr/pgmspace.h>
#include    <util/delay.h>
#include    <stdlib.h>

#include    <Iic.h>
#include    <string.h>

#include    <AllStrings.h>
#include    <struct_define.h>
#include    <Nls.h>
#include    <NetPack.h>
#include    <Menu.h>
#include    <Global_define.h>

#include    <FloatNumber.h>
#include    <LCD.h>
#include    <FireFloor.h>
#include    <SetConfig.h>

#include    <Timer.h>
#include    <LCD_old/LcdOutput.h>

#include    <MenuBaseClass.h>
#include    <MenuGlobal.h>
#include    <MenuFullList.h>
#include    <MenuEnd.h>

#include "MiscFire.h"

// получаем количество элементов в массиве
#define SIZE_OF(_array)    ( sizeof(_array) / sizeof(_array[0]) )

/*
что это такое и зачем оно нада читать по ссылке
http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&t=59453
*/
/* Определяем операторы new и delete */
void * operator new(size_t size);
void operator delete(void * ptr);

/* Я не знаю что это, но без него не работает */
__extension__ typedef int __guard __attribute__((mode (__DI__)));
extern "C" int __cxa_guard_acquire ( __guard * );
extern "C" void __cxa_guard_release ( __guard * );
extern "C" void __cxa_guard_abort ( __guard * );

/* Для чИста кАнкретных виртуальных функций */
extern "C" void __cxa_pure_virtual(void);

// не работает???
//#define PSTR(s) (__extension__({static prog_char __c[] = (s); &__c[0];}))

//Дальше креатив мой

#include <NetPack.h>
class NetTransferConstrol;
extern NetTransferConstrol BFPP0;
extern NetTransferConstrol BFPP1;
extern NetTransferConstrol BFPP2;
extern NetTransferConstrol BFPP3;
extern NetTransferConstrol BFPP4;
extern NetTransferConstrol SCHPZ;

class C_Lcd;
extern C_Lcd LCD;

class cFireFloor;
extern cFireFloor FireFloor;

extern eFireSource FireSrc; // Источник пожара
// структура перебора всех возможных этажей
extern BfppFloorCounter BfppCount;

extern uint8_t message_arch_byte[];
extern uint8_t message_arch_byte_cpy[];

extern uint8_t error_kog_num;
extern uint8_t error_kog_num_cpy;
extern uint8_t error_vzk_num;
extern uint8_t error_vzk_num_cpy;
extern uint8_t error_buzz_num;
extern uint8_t error_buzz_num_cpy;

extern uint8_t tech_fl;
const uint8_t DIG_INPUT   = (1 << 0);
const uint8_t DIG_MINUS   = (1 << 1);
const uint8_t DEFAULT_SET = (1 << 2);
const uint8_t IIC_BUSY    = (1 << 3);
const uint8_t NO_IIC      = (1 << 4);
const uint8_t SOUND       = (1 << 5);
/* TODO: убрать нахуй!!! */
#define SCAFE_FIRE 0x01

/* Тики операционной системы. Каждый тик равен ~1.1 мс */
extern volatile uint8_t sec_tik;
extern volatile uint32_t timer_count;

/* Кнопки на клавиатуре */
extern uint8_t KEY[];

extern void ReadRTC_RAM(void);
extern void SaveRTC_RAM(void);

extern void SoundON();
extern void SoundOFF();

extern void low_init();

extern void Etaz_init();
extern void mnemo_test_work();
extern void check_iic_status();
extern void Work_init();
extern void Dev_init();
extern void Pdz_init();
extern void Menu_init();
extern void Message_init();

extern void low_drv();
extern void Pdz_drv();
extern void Etaz_drv();
extern void Check_BFPP();
extern void Work_drv();
extern void Dev_drv();
extern void Message_drv();
extern void all_ind();
extern void MenuDrv();

/* Сетевые структуры данных */
extern NULL_STRUCT I_AM_NULL; /*Пустая структура, не использовать!!!*/

extern NET_BFPP_OUTPUT_STRUCT  data_for_bfpp[NUM_OF_BFPP];
extern NET_BFPP_INPUT_STRUCT   data_from_bfpp[NUM_OF_BFPP];

extern MNEMO_OUTPUT_STRUCT  mnemo[NUM_OF_MNEMO];
extern MNEMO_INPUT_STRUCT   mnemo_in[NUM_OF_MNEMO];

extern LCD_OUTPUT_STRUCT    lcd_data;
extern LCD_INPUT_STRUCT     key_data;

extern STRUCT_FROM_CENTER   data_for_slave;
extern STRUCT_FOR_CENTER    data_from_slave;

extern VIT_OUTPUT_STRUCT       data_for_vit;
extern VIT_INPUT_STRUCT       data_from_vit;

#endif
