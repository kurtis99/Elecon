#ifndef __DEVVZK_H
#define __DEVVZK_H

#include "Devs.h"
#include "Global_define.h"

const uint8_t VZK_END_DEVICE = 0x0010;

template < uint8_t NumOfClapans >
class dVZK: public TechObj
{
    private:
        enum {VZK_C_CLOSE,  VZK_C_OPEN};
        enum {VZK_ST_CLOSE, VZK_ST_OPEN};

        outPort & OPort;
        uint8_t * (&mnemoLamps)[NumOfClapans];  // Лампочки состояние клапанов
        uint8_t * (&kControl)[NumOfClapans];    // Контроль положения клапанов

        uint8_t * netSendLamp;                // Лампочки на ДПУ
        uint8_t index;

        void StartUp()
        {
            clear_t_stad();
            clear_t_sub_st();
            cmd = VZK_C_CLOSE;
        };
    public:
        virtual void drv();
        virtual void show_mnem();
        virtual void show_lcd();

        void check_os();
        void auto_open();
        void auto_close();

        dVZK (const char * _name,
              outPort & _II_Port,
              uint8_t * (&_mnemoLamps)[NumOfClapans],
              uint8_t * (&_kControl)[NumOfClapans],
              uint8_t * _netSend)
             : 
              OPort    (_II_Port),
              mnemoLamps (_mnemoLamps),
              kControl   (_kControl)
            {
                StartUp();
                name = _name;
                netSendLamp = _netSend;
                // Проверка наличия обратных связей и больше ничего
                enh_info = VZK_CHECK_OS;
            };

        virtual ~dVZK() {};
};

/* подключаем файл с реализацией класса */
#include "Vzk.cpp"

#endif

