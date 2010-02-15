#ifndef Center_Time_h
#define Center_Time_h

#include <Main.h>
#include <pcf8583.h>

class WorkWithTime
{
    private:
        static const uint8_t SET_DAY   = 0x01;
        static const uint8_t SET_MONTH = 0x02;
        static const uint8_t SET_HOUR  = 0x04;
        static const uint8_t SET_MIN   = 0x08;

        /* Период обновления часов */
        static const unsigned char REFRESH_RATE = 30;

        uint8_t status;
        void refresh();
        // переделать
        int16_t time_set_selector;//переменная для хранения уставок времени
        uint8_t time_set_flag;

        pcf8583 <0xA0, 0xA1> Clock; // Чаы

        /* частота обновления системного времени */
        uint8_t refresh_counter;
        uint8_t time_selector;
    public:
        void init();
        void work();
        void power_on();
        void show_lcd();

        WorkWithTime()
        {
            refresh_counter = 0;
            // хз что тут делать
        }
};

#endif /* Center_Time_h */
