#include "Devs.h"

extern KOG_NET D1M, D2M, P1M, P2M, P3M, P4M, P5M, P6M;
extern KOG_NET YA26_1, YA26_2, YA26_3, YA26_4, YA26_5, YA26_6;

/* Никакого глубокого смысла данные строчки в себе не содержат, я 
 * просто хочу добиться общего сокращения длинны строк в обьявлении 
 * обьектов */
#define DFS(number) (data_from_slave.dev_status[number])
#define DTS(number) (data_for_slave.dev_cmd[number])

KOG_NET  D1M (str_D9M,  mD1M, DFS(0), DTS(0));
KOG_NET  D2M (str_D10M, mD2M, DFS(1), DTS(1));
KOG_NET  P1M (str_P7M,  mP1M, DFS(2), DTS(2));
KOG_NET  P2M (str_P8M,  mP2M, DFS(3), DTS(3));
KOG_NET  P3M (str_P9M,  mP3M, DFS(4), DTS(4));
KOG_NET  P4M (str_P10M, mP4M, DFS(5), DTS(5));
KOG_NET  P5M (str_P11M, mP5M, DFS(6), DTS(6));
KOG_NET  P6M (str_P12M, mP6M, DFS(7), DTS(7));

KOG_NET  YA26_1 (str_YA26_1, mYA26_1, DFS(8),  DTS(8));
KOG_NET  YA26_2 (str_YA26_2, mYA26_2, DFS(9),  DTS(9));
KOG_NET  YA26_3 (str_YA26_3, mYA26_3, DFS(10), DTS(10));
KOG_NET  YA26_4 (str_YA26_4, mYA26_4, DFS(11), DTS(11));
KOG_NET  YA26_5 (str_YA26_5, mYA26_5, DFS(12), DTS(12));
KOG_NET  YA26_6 (str_YA26_6, mYA26_6, DFS(13), DTS(13));

#undef DFS(number)
#undef DTS(number)
/* Дальше нам эти макросы не нужны */

TechObj * pDevs_arr[] =
{
    &D1M,
    &D2M,
    &P1M,
    &P2M,
    &P3M,
    &P4M,
    &P5M,
    &P6M,
    &YA26_1,
    &YA26_2,
    &YA26_3,
    &YA26_4,
    &YA26_5,
    &YA26_6,
};

//int16_t dev_set_iic_copy[NUM_OF_DEV_SET];

//SetConfig DevSet[NUM_OF_DEV_SET] =
//{
    //SetConfig ( dev_set_name_str[0], 3, 0, 1000, 0 ),
//};

void Dev_init()
{
//    uint8_t i;

    //считывание уставок из памяти
//    if(!(tech_fl&DEFAULT_SET)) {                            //считывание уставок из флэши
//        for(i=0;i<NUM_OF_DEV_SET;i++) {
//            DevSet[i].value=ReadSetIIC(0x200+i*2);
//            dev_set_iic_copy[i]=DevSet[i].value;
//        }
//    } else {                                                //запись заводских уставок во флэш
//        for(i=0;i<NUM_OF_DEV_SET;i++) {
//            WriteSetIIC(DevSet[i].value,0x200+i*2);
//            dev_set_iic_copy[i]=DevSet[i].value;
//            _delay_ms(10);
//        }
//    }
}

void Dev_drv()
{
    uint8_t i;

    if (SCHPZ.haveNetConnect()) {
        for (i=0 ; i < SIZE_OF(pDevs_arr) ; i++) {
            pDevs_arr[i] -> ClrDeviceNetError();
        }
    }
    else {
        for (i=0 ; i < SIZE_OF(pDevs_arr) ; i++) {
            pDevs_arr[i] -> SetDeviceNetError();
        }
    }

    for (i=0 ; i < SIZE_OF(pDevs_arr) ; i++) {
        pDevs_arr[i]->drv();
        pDevs_arr[i]->show_mnem();
    }
}

void show_devs()
{
    static uint8_t _cur_dev;

    if (SIZE_OF(pDevs_arr) == 0) {
        LCD_abc((char*)strNoDevsDefined,0);
        return;
    }
    _cur_dev = getpm(_cur_dev, SIZE_OF(pDevs_arr));
    pDevs_arr[_cur_dev]->show_lcd();
}
//
//void show_dev_set()
//{
//    static uint8_t _cur_dev_set;
//
//    _cur_dev_set=getpm(_cur_dev_set,NUM_OF_DEV_SET);
//    LCD_abc((char*)dev_set_name_str[_cur_dev_set],0);
//    LCD_float(DevSet[_cur_dev_set].value,DevSet[_cur_dev_set].dot,16);
//    DevSet[_cur_dev_set].makeDigitalInput();
//
//    if ( !( tech_fl&IIC_BUSY ) ) {
//        if (dev_set_iic_copy[_cur_dev_set]!=DevSet[_cur_dev_set].value) {   //запись в ИИС обновленного параметра
//            tech_fl|=IIC_BUSY;
//            WriteSetIIC(DevSet[_cur_dev_set].value,0x200+_cur_dev_set*2);
//            dev_set_iic_copy[_cur_dev_set]=DevSet[_cur_dev_set].value;
//        }
//    }
//}
