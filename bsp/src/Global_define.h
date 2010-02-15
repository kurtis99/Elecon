#ifndef GLOBALDEFINES_H
#define GLOBALDEFINES_H

const unsigned char MAX_LENGTH = 16;
const unsigned char MAX_ROWS = 2;

const unsigned char TIME_WAIT_OPEN = 120;

extern uint16_t scafe_fl;
const uint16_t SCAFE_ERROR     = (1 << 0);  //авария

const uint16_t SCAFE_STOP_PDZ  = (1 << 1 );
const uint16_t SCAFE_FIRE      = (1 << 2 );
const uint16_t SCAFE_FIRE_PK   = (1 << 3 );
const uint16_t SCAFE_FIRE_SPS  = (1 << 4 );

const uint16_t RED             = (1 << 5);
const uint16_t GREEN           = (1 << 6);
const uint16_t YELLOW          = (1 << 7);
const uint16_t FREEZ           = (1 << 8);
const uint16_t FIELD           = (1 << 9);
const uint16_t MNEMO_WRK       = (1 << 10);

extern uint8_t cmd;//объявлены в Main.h в структуре
#define FIRE_ZONE   0x0001//
//#define FIRE_VZK	0x0002//
//#define FIRE		0x0004//
#define STOP_NET    0x0008//

/* Описание флагов для локального технологического устройства */
//флаги enh_info
#define KOG_CHECK_PRESS 0x8000 //проверка перепада давления
#define KOG_CHECK_MP    0x4000 //проверка состояния магнитного пускателя
#define KOG_CHECK_KTR   0x2000 //проверка состояния теплового реле
#define KOG_CHECK_OS    0x1000 //проверка обратной связи
#define KOG_OPER        0x0200 //устройство управляется оператором
#define KOG_DIST        0x0100 //устройство управляется дистанционно
#define KOG_PRESS_ERROR 0x0080 //ошибка перепада давления
#define KOG_MP_ERROR    0x0040 //ошибка магнитного пускателя
#define KOG_KTR_ERROR   0x0020 //ошибка теплового реле
#define KOG_OS_ERROR    0x0010 //ошибка обратной связи
#define KOG_END_DEVICE  0x0008 //Это устройство никуда никому ничего не отдает

/* Описание флагов для сетевого техноустройства */
//флаги enh_info
#define KOGNET_CHECK_PRESS  0x8000 //проверка перепада давления
#define KOGNET_CHECK_MP     0x4000 //проверка состояния магнитного пускателя
#define KOGNET_CHECK_KTR    0x2000 //проверка состояния теплового реле
#define KOGNET_CHECK_OS     0x1000 //проверка обратной связи

#define KOG_HAND            0x0400
#define KOGNET_OPER         0x0200 //устройство управляется оператором
#define KOGNET_DIST         0x0100 //устройство управляется дистанционно
#define KOGNET_PRESS_ERROR  0x0080 //ошибка перепада давления
#define KOGNET_MP_ERROR     0x0040 //ошибка магнитного пускателя
#define KOGNET_KTR_ERROR    0x0020 //ошибка теплового реле
#define KOGNET_OS_ERROR     0x0010 //ошибка обратной связи

//devs_net_stat[]
#define NETDEV_OP           0x01 //сетевое устройство запущено
#define NETDEV_CL           0x02 //сетевое устройство закрыто/остановлено
#define NETDEV_ST           0x04 //сетевое устройство закрыто
#define NETDEV_OPER         0x08 //устройство в опере (не на концерте)
#define NETDEV_PRESS_ERROR  0x10 //авария по перепаду давления
#define NETDEV_MP_ERROR     0x20 //авария по магнитному пускателю
#define NETDEV_OS_ERROR     0x40 //авария по обратной связи
#define NETDEV_NETERROR     0x80 //устройство доступно по сети

//devs_net_cmd[]
#define PSK_NETDEV          0x01 //пуск сетевого устройства
#define STP_NETDEV          0x02 //стоп/закрытие сетевого устройства
#define CLS_NETDEV          0x04 //закрытие сетевого устройства
#define RESET_NETDEV        0x08 //сетевое устройство закрыто/остановлено

//флаги enh_info //Смотреть файл Dev_kdp.h
#define KPD_CHECK_OP	0x0001 //проверка открытия
#define KPD_CHECK_ALT	0x0002 //проверка готовности
#define KPD_CHECK_OS	0x0004 //проверка обратной связи
#define KPD_OPER		0x0008 //устройство управляется оператором
#define KPD_DIST		0x0010 //устройство управляется дистанционно
#define KPD_OP_ERROR	0x0020 //ошибка открытия
#define KPD_CL_ERROR	0x0040 //ошибка открытия
#define KPD_ALT_ERROR	0x0080 //ошибка не готов
#define KPD_OS_ERROR	0x0100 //ошибка обратной связи
#define KPD_POS_ERROR	0x0200 //ошибка положения (неоткрыт или незакрыт)

//флаги enh_info // Смотреть файл Dev_zvk.h
#define VZK_CHECK_OS    0x0001 //проверка обратной связи
#define VZK_OPER        0x0002 //устройство управляется оператором
#define VZK_DIST        0x0004 //устройство управляется дистанционно
#define VZK_OS_ERROR    0x0008 //ошибка обратной связи

#endif /* GLOBALDEFINES_H */
