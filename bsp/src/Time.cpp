#include <Time.h>

const unsigned char WRITE_RAM_ADDRESS = 0x10;

extern uint8_t getpm(uint8_t val,uint8_t max);

//pcf8583 <0xA0, 0xA1> Clock; // Чаы

SysTime Time; /* текущее время */
SysTime Time_copy;
SysTime last_time_working;

void WorkWithTime::init()
{
    /* Ошибка чтения ОЗУ из часов, уходим */
    if (I2C_OK != Clock.read_ram(WRITE_RAM_ADDRESS, SIZE_RTC_RAM))
        return;

    /* Для начала, нам нужно узнать текущее время */
    refresh();

    /* устанавливаем флаг включения шкафа */
    tech_fl |= POWER_ON;

    /* Записать время последнего включения шкафа */
    last_time_working.min   = RTC_Ram[2];
    last_time_working.hour  = RTC_Ram[3];
    last_time_working.day   = RTC_Ram[4];
    last_time_working.month = RTC_Ram[5];
}

void WorkWithTime::refresh()
{
    Clock.get_time(Time);
    refresh_counter = 0;
}

/* Раз в секунду сохраняем состояние часов */
void WorkWithTime::work()
{
    /* сохранаяем текущее время во временный массив для последующей записи */
    RTC_Ram[1] = 0x00;  //(uint8_t) ( scafe_fl >> 8 );//просто так
    RTC_Ram[2] = Time.min;
    RTC_Ram[3] = Time.hour;
    RTC_Ram[4] = Time.day;
    RTC_Ram[5] = Time.month;

    /* Периодически обновляем счетчик времени */
    if (refresh_counter == REFRESH_RATE) {
        if (!(tech_fl & IIC_BUSY)) {
            tech_fl |= IIC_BUSY;
            refresh();
        }
    }
    else {
        refresh_counter++;
    }

    /* Если I2C не занята, то пытаемся что-то, куда-то записать */
    if (!(tech_fl & IIC_BUSY)) {
        tech_fl |= IIC_BUSY;
        Clock.write_ram(WRITE_RAM_ADDRESS , SIZE_RTC_RAM);
    }
}

void WorkWithTime::show_lcd()
{
    static uint8_t time_blink;

    time_selector = getpm(time_selector,5);

    if (!time_selector) {
        if (!time_set_flag) {
            Time_copy = Time;
        }
        else {
            if (!(tech_fl & IIC_BUSY)) {
                tech_fl|=IIC_BUSY;
                if (Time_copy != Time) {
                    /* Пишем уставки в память */
                    Clock.set_time(Time_copy);
                    Time = Time_copy;
                }
                time_set_flag = 0;
            }
        }
    }
    else {
        //запись временных уставок
        //LCD_putc('^',22+(time_selector-1)*3);
        switch (time_selector-1)
        {
            case 0:
                if (!(time_set_flag & SET_DAY)) {
                    time_set_selector=(int16_t)(Time_copy.day);
                    time_set_flag=SET_DAY;
                }
                getpm_dig(&time_set_selector,0,1,31);
                Time_copy.day=(uint8_t)time_set_selector;
                break;
            case 1:
                if (!(time_set_flag & SET_MONTH)) {
                    time_set_selector=(int16_t)(Time_copy.month);
                    time_set_flag=SET_MONTH;
                }
                getpm_dig(&time_set_selector,0,1,12);
                Time_copy.month=(uint8_t)time_set_selector;
                break;
            case 2:
                if (!(time_set_flag & SET_HOUR)) {
                    time_set_selector=(int16_t)(Time_copy.hour);
                    time_set_flag=SET_HOUR;
                }
                getpm_dig(&time_set_selector,0,0,23);
                Time_copy.hour=(uint8_t)time_set_selector;
                break;
            case 3:
                if (!(time_set_flag & SET_MIN)) {
                    time_set_selector=(int16_t)(Time_copy.min);
                    time_set_flag=SET_MIN;
                }
                getpm_dig(&time_set_selector,0,0,59);
                Time_copy.min=(uint8_t)time_set_selector;
                break;
        }
    }

    LCD.init();
    LCD << time_str << ':';
    LCD.newLine();

    if (time_selector == 1)     LCD << '>' << Time_copy.day << '<';
    else                        LCD << Time_copy.day;

    LCD << '.';

    if (time_selector == 2)     LCD << '>' << Time_copy.month << '<';
    else                        LCD << Time_copy.month;

    LCD << ' ';

    if (time_selector == 3)     LCD << '>' << Time_copy.hour << '<';
    else                        LCD << Time_copy.hour;

    if (!sec_tik)
        time_blink ^= 0xFF;

    LCD << ((time_blink & 0x1) ? ':' : ' ');

    if (time_selector == 4)     LCD << '>' << Time_copy.min << '<';
    else                        LCD << Time_copy.min;
}
