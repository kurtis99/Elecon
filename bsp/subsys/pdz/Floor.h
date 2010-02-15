// ====================================================================
//
//       Filename:  Floor.h
//
//    Description:  Работа с этажом, без привязки к БФПП 
//                  (типа следующий уровень абстракции).
//
//        Version:  1.0
//        Created:  27.11.2009 17:07:37
//       Revision:  none
//       Compiler:  avr-g++
//
//         Author:  Mikhail Boiko (mb), MikhailBoiko85@gmail.com
//        Company:  НТТОВ "Элекон
//
// ====================================================================
#ifndef  FLOOR_INC
#define  FLOOR_INC

#include    <Main.h>
#include    <Global_define.h>
#include    <MnemoColors.h>

// ====================================================================
//        Class:  Floor
//  Description:  контроль и управление состоянием этажа
// ====================================================================
class Floor
{
    public:
        Floor (
            uint8_t & _mYA1,
            uint8_t & _mYA2,
            uint8_t & _mSPS,
            uint8_t & _mSBSQ,
            uint8_t & _mBUPK
        )
        :
        mYA1  (_mYA1),
        mYA2  (_mYA2),
        mSPS  (_mSPS),
        mSBSQ (_mSBSQ),
        mBUPK (_mBUPK)
        {
            fire_info = NoFire;
            screen_off();
        };                    // constructor
        void set_event(eSBSQ state);
        void set_event(eBUPK state);
        void set_event(eSPS state);
        void set_event(eYA state, eYANo number);
        void driver();
        // установка пожара, нужно указать источник
        void set_fire(eFireSource fire_source);
        // получаем информацию о текущем пожаре
        eFireSource get_fire();
        // возвращаем "1" если есть пожар, иначе возвращаем "0"
        bool have_fire();
        void screen_off();
        void doStopPdz();
        void show_lcd(uint8_t cur_floor); // отображение состояния этажна ЖКИ
    private:
        uint8_t & mYA1;                // Лампочка состояния клапана
        uint8_t & mYA2;                // Тоже самое, только клапан 
                    // другой (в текущей версии класса, максимально 
                    // число клапанов равно двум)
        uint8_t & mSPS;                // Пожар от СПС
        uint8_t & mSBSQ;               // Переключатель какой-то
        uint8_t & mBUPK;               // БУПКа

        void fireMnemoWork();

        eFireSource  fire_info;  // информация о пожаре на этом этаже
}; // -----  end of class Floor  -----

#endif   // ----- #ifndef FLOOR_INC  ----

