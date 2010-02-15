/*
    Файл реализации классов работающих с меню
*/
#include "MenuGlobal.h"
#include "MenuInter.h"
#include "MenuEnd.h"
#include "MenuAlarm.h"
#include <Main.h>

#include <Global_define.h>

extern const char FirstItem[] PROGMEM;
       const char FirstItem[] = " 1";

namespace Menu {

    extern bool show_low_menu_string();

    extern BaseClass * pNextMenu;
    extern BaseClass * pCurrentMenu;

/**************************************************************
*                                                             *
*                                                             *
*                                                             *
*              Описание членовк класса GlobalItem             *
*                                                             *
*                                                             *
*                                                             *
**************************************************************/

    /*
      Отрисуем 2 строки, на экране ЖК  */
    void GlobalItem::showMenuItems()
    {
        curMenuPointer = getListValue ( curMenuPointer , NumOfMenus );

        LCD.init();
        LCD << '>' << ' ' << curMenuPointer + 1 << forwardItem[curMenuPointer] -> MenuName << ' ' << '<';
        LCD.newLine();
        if (show_low_menu_string()) {
            if (curMenuPointer >= NumOfMenus-1) {
                LCD << '1' << forwardItem[0] -> MenuName;
            }
            else {
                LCD << curMenuPointer + 2 << forwardItem[curMenuPointer+1] -> MenuName;
            }
        }
    }

    /*
      Проверяем состояние кнопок клавиатуры
    */
    void GlobalItem::checkPushButtons()
    {
        /* Переход в следующее меню */
        if(KEY_OK) {
            pNextMenu    = pCurrentMenu;
            pCurrentMenu = forwardItem[curMenuPointer];
        }
    }

/**************************************************************
*                                                             *
*                                                             *
*                                                             *
*              Описание членовк класса InterItem              *
*                                                             *
*                                                             *
*                                                             *
**************************************************************/

    void InterItem::showMenuItems()
    {
        curMenuPointer = getListValue ( curMenuPointer , NumOfMenus );

        LCD.init();
        LCD << ' ' << ' ' << MenuName << ' '
            << '(' << curMenuPointer+1 << '/' << NumOfMenus << ')';
        LCD.newLine();
        LCD << ' ' << curMenuPointer+1 << (forwardItem[curMenuPointer] -> MenuName);
    }

    /*
      Проверяем состояние кнопок клавиатуры
    */
    void InterItem::checkPushButtons()
    {
        /* Переход в следующее меню */
        if (KEY_OK) {
            pNextMenu    = pCurrentMenu;
            pCurrentMenu = forwardItem[curMenuPointer];
        }
        /* Выход из текущего меню */
        if (KEY_OUT) {
            pCurrentMenu = returnItem;
            pNextMenu    = pCurrentMenu;
        }
    }

/**************************************************************
*                                                             *
*                                                             *
*                                                             *
*              Описание членовк класса EndItem                *
*                                                             *
*                                                             *
*                                                             *
**************************************************************/

    void EndItem::showMenuItems()
    {
        ShowCurrenMenu();
    }
    void EndItem::checkPushButtons()
    {
        /* Выход из текущего меню */
        if (KEY_OUT) {
            pCurrentMenu = returnItem;
            pNextMenu    = pCurrentMenu;
        }
    }

/**************************************************************
*                                                             *
*                                                             *
*                                                             *
*              Описание членовк класса EndItem                *
*                                                             *
*                                                             *
*                                                             *
**************************************************************/

    void AlarmItem::showMenuItems()
    {
        ShowCurrenMenu();
    }
    void AlarmItem::checkPushButtons()
    {
        /* Выход из текущего меню */
        if (KEY_wrk[0] || KEY_wrk[1]) {
            pCurrentMenu = returnItem;
            pNextMenu    = pCurrentMenu;
        }
    }

/**************************************************************
*                                                             *
*                                                             *
*                                                             *
*              Описание членов класса BaseClass               *
*                                                             *
*                                                             *
*                                                             *
**************************************************************/

    uint8_t BaseClass::getListValue(uint8_t Value,uint8_t MaxValue)
    {
        if (KEY_P) {
            if ( ++Value >= MaxValue ) Value=0;
        }
        else if (KEY_M) {
            !Value ? Value = ( MaxValue - 1 ) : Value--;
        }

        return Value;
    }
}
