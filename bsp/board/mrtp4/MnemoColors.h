// ====================================================================
//
//       Filename:  MnemoColors.h
//
//    Description:  Макросы для заданиця цветов мнемосхемы
//
//        Version:  1.0
//        Created:  30.11.2009 13:31:06
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Mikhail Boiko (mb), kurtis99@bigmir.net
//        Company:  НТТОВ "Элекон
//
// ====================================================================
#ifndef  MNEMOCOLORS_INC
#define  MNEMOCOLORS_INC

//Задаем все цвета радуги
//нормальное горение
const unsigned char RED_LAMP       = 0xF0;
const unsigned char YELLOW_LAMP    = 0x00;
const unsigned char GREEN_LAMP     = 0x0F;
const unsigned char NULL_LAMP      = 0xFF;
/* нормальное моргание */
const unsigned char B_RED_LAMP     = 0xF1;
const unsigned char B_GREEN_LAMP   = 0x1F;
const unsigned char B_YELLOW_LAMP  = 0x11;
/* нормальное ускоренное моргание */
const unsigned char BF_RED_LAMP    = 0xF3;
const unsigned char BF_GREEN_LAMP  = 0x3F;
const unsigned char BF_YELLOW_LAMP = 0x33;
/* моргающий красный (Всем баяцца!!!) */
const unsigned char WARNING_LAMP   = 0x55;

#endif   // ----- #ifndef MNEMOCOLORS_INC -----

