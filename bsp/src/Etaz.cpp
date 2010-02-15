#include <Etaz.h>

// TODO: Дописать поддержку БФПП с 3-мя и 4-мя клапанами

static uint8_t find_current_fire_etaz(const uint8_t end_value);

/* Статические переменные для перечисления этажей, возможно некоторые из
 * них в последствии окажутся лишними, писалось все итеративно и не
 * всегда отслеживалось что больше не используется и следует удалить */
BfppFloorCounter EtazItem::CurrentBfppFloor = {0, 0};
uint8_t EtazItem::number_of_created_devices = 0;
uint8_t EtazItem::CurrentFloor = 0;

EtazItem2
Bfpp1  (mY1_0,  mY2_0,  mSPS0,  mSBSQ0,  mBUPK0, \
        mY1_1,  mY2_1,  mSPS1,  mSBSQ1,  mBUPK1, mFIRE0, kFIRE1_0, kFIRE2_0, BFPP0);

EtazItem2
Bfpp2  (mY1_2,  mY2_2,  mSPS2,  mSBSQ2,  mBUPK2, \
        mY1_3,  mY2_3,  mSPS3,  mSBSQ3,  mBUPK3, mFIRE1, kFIRE1_1, kFIRE2_1, BFPP1);

EtazItem2
Bfpp3  (mY1_4,  mY2_4,  mSPS4,  mSBSQ4,  mBUPK4, \
        mY1_5,  mY2_5,  mSPS5,  mSBSQ5,  mBUPK5, mFIRE2, kFIRE1_2, kFIRE2_2, BFPP2);

EtazItem2
Bfpp4  (mY1_6,  mY2_6,  mSPS6,  mSBSQ6,  mBUPK6, \
        mY1_7,  mY2_7,  mSPS7,  mSBSQ7,  mBUPK7, mFIRE3, kFIRE1_3, kFIRE2_3, BFPP3);

EtazItem1
Bfpp5  (mY1_8,  mY2_8,  mSPS8,  mSBSQ8,  mBUPK8, \
                                                 mFIRE4, kFIRE1_4,           BFPP4);

EtazItem* pEtaz[] =
{
    &Bfpp1,
    &Bfpp2,
    &Bfpp3,
    &Bfpp4,
    &Bfpp5,
};

BfppFloorCounter BfppCount = {0, 0};    // структура перебора всех 
                                        // возможных этажей

void show_bfpp()
{
//    LCD.init();

    // Выбор нужного этажа в меню
    pEtaz[BfppCount.bfpp_counter]->set_next_fire_floor(BfppCount);
// БФПП на данном этапе может содержать или 1 или 2 обслуживаемых
// этажа, в близкой перспективе возможность использования БФПП с 3-мя
// и даже 4-мя этажами (в идеале хотелось вообще не быть привязанным к
// количеству этажей!).
//
// Смысл функции set_next_fire_floor(BfppCount):
// в этом месте программы, БФПП для нас представляются черными ящиками,
// т.е. мы не знаем количество этажей которое он обслуживает, это удобно
// для задания произвольного порядка следования БФПП. Далее, если у нас
// БФПП одноэтажный, то мы просто увеличиваем значение поля структуры
// BfppCount, которое отвечает за перебор БФПП. Таким образом, счетчик
// будет указывать на следующий элемент в массиве pEtaz. Если же у нас
// 2-х этажный БФПП, то счетчик БФПП не изменяется (место в массиве
// pEtaz не меняется) а меняется номер этажа (переменная floor_counter),
// т.е. не меняется фактический БФПП с которым мы работает, но меняется
// номер обслуживаемого этажа.

    if (FireSrc == NoFire) {
        if (KEY_8) {
            uint8_t cur_ff = 0; // current fire floor (пожарный этаж)

            cur_ff = find_current_fire_etaz(BfppCount.bfpp_counter);
            cur_ff += pEtaz[BfppCount.bfpp_counter]->set_fire(FromMenu);
            FireFloor.Set(cur_ff);
        }
    }

    pEtaz[BfppCount.bfpp_counter]->show_menu(
                    find_current_fire_etaz(BfppCount.bfpp_counter));
}

// В функция передаем номер БФПП (индекс в массиве pEtaz) до которого
// нужно подсчитать общее количество этажей
static uint8_t find_current_fire_etaz(const uint8_t end_value)
{
    uint8_t i;
    uint8_t etaz = 0;

    for (i=0; i<end_value; i++) {
        etaz += pEtaz[i]->num_of_floors();
    }

    return etaz;
}

uint8_t set_stad(uint8_t _stad)
{
    return _stad;
}

void Check_BFPP()
{
    uint8_t i;

    for (i=0; i<SIZE_OF(pEtaz); i++) {
        pEtaz[i]->CheckBfpp();
    }
}

void Etaz_init()
{
    uint8_t i;
 
    for (i=0; i < SIZE_OF(pEtaz); i++)
        data_for_bfpp[i].out_led = 0xFF;
}

/* Интерфес связующий класс с глобальными переменнными 
 * TODO: попытаться переделать
 * переделал, но все-равно не то... */
void Etaz_drv()
{
    uint8_t i;

    for (i=0; i<SIZE_OF(pEtaz); i++) {
        data_for_bfpp[i].out_led = pEtaz[i]->EtazDrv();

        if (FireSrc == StopPDZ) {
            pEtaz[i]->doStopPdz();
            // TODO: дописать функционал, сейчас там стоит заглушка
            FireFloor.Clear();
        }
    }
}

void show_bfpp_test()
{
    static uint8_t cur_bfpp_test;

    uint8_t lo_byte;
    uint8_t hi_byte;

    lo_byte = ( pEtaz[cur_bfpp_test] -> return_lo_enh() );
    hi_byte = ( pEtaz[cur_bfpp_test] -> return_hi_enh() );

    cur_bfpp_test = getpm (cur_bfpp_test,NUM_OF_BFPP);
    LCD_uind16 (data_from_bfpp[cur_bfpp_test].msk1,8,2|LEAD_ZERO);
    LCD_uind16 (data_from_bfpp[cur_bfpp_test].msk2,10,2|LEAD_ZERO);
    LCD_uind16 (data_from_bfpp[cur_bfpp_test].status,12,2|LEAD_ZERO);
    LCD_uind16 (data_from_bfpp[cur_bfpp_test].dip,14,2|LEAD_ZERO);

    LCD_uind16 (lo_byte, 3, 2|LEAD_ZERO);
    LCD_uind16 (hi_byte, 1, 2|LEAD_ZERO);

    //LCD_abc((char*)bfpp_test_str[1],16);
    LCD_uind (pEtaz[cur_bfpp_test]->getErrorPacket(),24,2|LEAD_ZERO);

    LCD_uind16 (pEtaz[cur_bfpp_test]->getSendAddress(),30,2|LEAD_ZERO);
}

