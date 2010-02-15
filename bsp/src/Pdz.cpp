#include "Pdz.h"
#include "Sgwork.h"

extern KOG_NET D1M, D2M, P1M, P2M, P3M, P4M, P5M, P6M;
extern KOG_NET YA26_1, YA26_2, YA26_3, YA26_4, YA26_5, YA26_6;

const unsigned char SPS_FIRE = 0x55;

static uint8_t stop_pdz_counter;

Pdz Pdz1 (mnemo[0].LED_FIELD[47], mnemo[0].LED_FIELD[47]);

Pdz *pPdz_arr[NUM_OF_PDZ]=
{
    &Pdz1
};

void Pdz::show_mnem()
{
    switch (FireSrc)
    {
        case StopPDZ:
            lampFirePK = YELLOW_LAMP; 
            lampFireSPS = YELLOW_LAMP; 
            break;
        case FromSPS:
        case FromPK:
            lampFirePK = WARNING_LAMP; 
            lampFireSPS = WARNING_LAMP; 
            break;
        case FromMenu:
            lampFirePK = B_RED_LAMP; 
            lampFireSPS = B_RED_LAMP; 
            break;
        case NoFire:
            lampFirePK = NULL_LAMP; 
            lampFireSPS = NULL_LAMP; 
            break;
        default:
            lampFirePK = NULL_LAMP; 
            lampFireSPS = NULL_LAMP; 
            break;
    }
}

SetConfig PdzSet[] =
{
//    SetConfig( pdz_set_name_str[0], 5, 0, 100, 0 ),
//    SetConfig( pdz_set_name_str[1], 0, 0, 100, 0 ),
//    SetConfig( pdz_set_name_str[2], 0, 0, 100, 0 ),
};

//int16_t pdz_set_iic_copy[NUM_OF_PDZ_SET];

void Pdz_init()
{
    //uint8_t i;

    stop_pdz_counter = 0;

    //считывание уставок из памяти
//    if(!(tech_fl&DEFAULT_SET))//считывание уставок из флэши
//    {
//        for(i=0;i<NUM_OF_PDZ_SET;i++)
//        {
//            PdzSet[i].value=ReadSetIIC(0x100+i*2);
//            pdz_set_iic_copy[i]=PdzSet[i].value;
//        }
//    }
//    else //запись заводских уставок во флэш
//    {
//        for(i=0;i<NUM_OF_PDZ_SET;i++)
//        {
//            WriteSetIIC(PdzSet[i].value,0x100+i*2);
//            pdz_set_iic_copy[i]=PdzSet[i].value;
//            _delay_ms(10);
//        }
//    }
}

void Pdz_drv()
{
    uint8_t i;

    if ((!sec_tik) && (stop_pdz_counter > 0)) {
        stop_pdz_counter--;
    }

    if (FireSrc == StopPDZ) {
        FireSrc = NoFire;
    }
    if (K_STOP_PDZ) {
        stop_pdz_counter = 10;
        Pdz1.FireStopPdz();
        FireFloor.Clear();
        FireSrc = StopPDZ;
    }

    for (i = 0; i<NUM_OF_PDZ; i++) {
        if (!sec_tik) {
            pPdz_arr[i]->inc_t_stad();
            pPdz_arr[i]->inc_t_sub_st();
        }
        pPdz_arr[i]->drv();
        pPdz_arr[i]->show_mnem();
    }
}

void show_pdz()
{
    static uint8_t _cur_pdz;

    _cur_pdz=getpm(_cur_pdz,1);
    pPdz_arr[0]->show_lcd();
}

void show_pdz_set()
{
//    static uint8_t _cur_pdz_set;

//    _cur_pdz_set=getpm(_cur_pdz_set,NUM_OF_PDZ_SET);
//    LCD_abc((char*)pdz_set_name_str[_cur_pdz_set],0);
//    LCD_float(PdzSet[_cur_pdz_set].value,PdzSet[_cur_pdz_set].dot,16);
//    PdzSet[_cur_pdz_set].makeDigitalInput();
//
//    if ( !( tech_fl&IIC_BUSY ) ) {
//        if (pdz_set_iic_copy[_cur_pdz_set]!=PdzSet[_cur_pdz_set].value ) {
//            //запись в ИИС обновленного параметра
//            tech_fl|=IIC_BUSY;
//            WriteSetIIC(PdzSet[_cur_pdz_set].value,0x100+_cur_pdz_set*2);
//            pdz_set_iic_copy[_cur_pdz_set]=PdzSet[_cur_pdz_set].value;
//        }
//    }
}

static void Pdz1_work()
{
    SoundON();

    switch (Pdz1.sub_st)
    {
        case 0:
            YA26_1.auto_open();
            YA26_2.auto_open();
            YA26_3.auto_open();
            YA26_4.auto_open();
            YA26_5.auto_open();
            YA26_6.auto_open();
            if (Pdz1.read_t_sub_st() > 5)
                Pdz1.to_stad (PDZ_ST_WORK, 1);
            break;
        case 1:
            D1M.auto_open();
            if (Pdz1.read_t_sub_st() > 5)
                Pdz1.to_stad (PDZ_ST_WORK, 2);
            break;
        case 2:
            D2M.auto_open();
            if (Pdz1.read_t_sub_st() > 5)
                Pdz1.to_stad (PDZ_ST_WORK, 3);
            break;
        case 3:
            P1M.auto_open();
            if (Pdz1.read_t_sub_st() > 5)
                Pdz1.to_stad (PDZ_ST_WORK, 4);
            break;
        case 4:
            P2M.auto_open();
            if (Pdz1.read_t_sub_st() > 5)
                Pdz1.to_stad (PDZ_ST_WORK, 5);
            break;
        case 5:
            P3M.auto_open();
            if (Pdz1.read_t_sub_st() > 5)
                Pdz1.to_stad (PDZ_ST_WORK, 6);
            break;
        case 6:
            P4M.auto_open();
            if (Pdz1.read_t_sub_st() > 5)
                Pdz1.to_stad (PDZ_ST_WORK, 7);
            break;
        case 7:
            P5M.auto_open();
            if (Pdz1.read_t_sub_st() > 5)
                Pdz1.to_stad (PDZ_ST_WORK, 8);
            break;
        case 8:
            P6M.auto_open();
            if (Pdz1.read_t_sub_st() > 5)
                Pdz1.to_stad (PDZ_ST_WORK, 9);
            break;
        default:
            break;
    }
}

static void Pdz1_stop()
{
    SoundOFF();
    D1M.auto_close();
    D2M.auto_close();
    P1M.auto_close();
    P2M.auto_close();
    P3M.auto_close();
    P4M.auto_close();
    P5M.auto_close();
    P6M.auto_close();
    YA26_1.auto_close();
    YA26_2.auto_close();
    YA26_3.auto_close();
    YA26_4.auto_close();
    YA26_5.auto_close();
    YA26_6.auto_close();
}

void Pdz::show_lcd()
{
    LCD.init();
    LCD << pdz_name_str << ' ';

    switch (FireSrc)
    {
        case FromPK:
            // "Пожар БФПП"
            LCD << firePK_str;
            break;

        case FromSPS:
            // "Пожар СПС "
            LCD << fireSPS_str;
            break;

        case FromMenu:
            // "Пожар Меню"
            LCD << fireMenu_str;
            break;

        case StopPDZ:
            // " Стоп ПДЗ"
            LCD << strStopPdz;
            break;

        case NoFire:
            // "В норме"
            LCD << norma_str;
            break;

        default:
            break;
    }

    LCD.newLine();

    if (Pdz1.stad == PDZ_ST_WORK) {
        LCD << sub_st;
    }
    else if (Pdz1.stad == PDZ_ST_STOP) {
        LCD << sub_st;
    }
}

void Pdz::drv()
{
    uint8_t new_st = Pdz1.stad;

    switch (FireSrc)
    {
    	case FromPK:
    	case FromSPS:
    	case FromMenu:
            new_st = PDZ_ST_WORK;
    		break;
        case NoFire:
        case StopPDZ:
            new_st = PDZ_ST_STOP;
            break;
    	default:
            new_st = PDZ_ST_STOP;
    		break;
    }

    if (new_st != Pdz1.stad) {
        switch (new_st)
        {
            case (PDZ_ST_STOP):
                Pdz1.to_stad(new_st,0);
                break;
            case (PDZ_ST_WORK):
                switch (FireSrc)
                {
                    case FromSPS:
                    case FromPK:
                    case FromMenu:
                        Pdz1.to_stad(new_st,0);
                        break;
                    default:
                        break;
                }
                break;
        }
    }

    if (Pdz1.stad == PDZ_ST_WORK) {
        Pdz1_work();
    } else if (Pdz1.stad == PDZ_ST_STOP) {
        if (stop_pdz_counter) {
            Pdz1_stop();
        }
    }
}

