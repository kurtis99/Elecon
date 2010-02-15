#include "Menu.h"

namespace Menu
{
    bool show_low_menu_string();

    BaseClass * pNextMenu;
    BaseClass * pCurrentMenu;

    uint8_t KEY_cpy[2];
    uint8_t KEY_wrk[2];
}

/*
Список сокращений использующихся в именовании переменных
pa - Pointer to Array, указатель на массив
lm - Local Menu, местное меню (не глобальное), обычно в него попадают из глобального
gm - Global Menu, вершина айсберга
*/

/* Меню Служебное */
extern void showSystVersion();
extern void mrtp_reset();

Menu::EndItem   lmServVersion   (showSystVersion, strShowVer);
Menu::EndItem   lmReset         (mrtp_reset, strReset);

Menu::BaseClass * paServiceSubMenu[] =
{
    &lmServVersion,
    &lmReset,
};

/*МЕНЮ ТЕСТ*/
extern void show_mt_test();
extern void show_msk_test();
extern void show_mnemo_test();
extern void show_bfpp_test();

Menu::EndItem   lmTestMt      (show_mt_test, strTestMt);
Menu::EndItem   lmTestMsk     (show_msk_test, strTestMsk);
Menu::EndItem   lmTestBfpp    (show_bfpp_test, strTestBfpp);
Menu::EndItem   lmTestMnemo   (show_mnemo_test, strTestMnemo);
Menu::InterItem lmMenuService (paServiceSubMenu, 
                               SIZE_OF(paServiceSubMenu), strMenuServ);

Menu::BaseClass * paTestSubMenu[] =
{
    &lmTestMt,
    &lmTestBfpp,
    &lmTestMsk,
    &lmTestMnemo,
    &lmMenuService,
};

/*МЕНЮ УСТАВОК*/
extern void show_time_set();

Menu::EndItem   lmSubSyst ( show_time_set, strSetSystem );

Menu::BaseClass * paSetSubMenu[] =
{
    &lmSubSyst,
};

/* Глобальное меню устройства */
extern void show_pdz();
//extern void show_etaz();
extern void show_bfpp();
extern void show_devs();
extern void show_message();

// Убираю меню "ПДЗ", вместо него будет меню "Этаж"
Menu::EndItem   gmMenuPdz      (show_pdz, strMenuPdz);
Menu::EndItem   gmMenuBFPP     (show_bfpp, strMenuBFPP);
//Menu::EndItem   gmMenuEtaz     (show_etaz, strMenuEtaz);
Menu::EndItem   gmMenuDevs     (show_devs, strMenuDevs);
Menu::InterItem gmMenuTest     (paTestSubMenu, 
                                SIZE_OF(paTestSubMenu), 
                                strMenuTest);

Menu::BaseClass * paGlobalMenu[] =
{
    &gmMenuPdz,
    &gmMenuBFPP,
    //&gmMenuEtaz,
    &gmMenuDevs,
    &gmMenuTest,
};

Menu::GlobalItem  myGlobalMenu(paGlobalMenu, SIZE_OF(paGlobalMenu));

void Menu_init()
{
    Menu::pCurrentMenu = &myGlobalMenu;
    Menu::pNextMenu    = &myGlobalMenu;

    Menu::KEY_cpy[0]=key_data.key[0];
    Menu::KEY_wrk[0]=key_data.key[0];
    Menu::KEY_cpy[1]=key_data.key[1];
    Menu::KEY_wrk[1]=key_data.key[1];
}

uint8_t LCD_light;

#include <Global_define.h>

void MenuDrv()
{
    uint8_t i;

    KEY[0]=key_data.key[0];
    KEY[1]=key_data.key[1];

    if ((Menu::KEY_cpy[0] != KEY[0]) || (Menu::KEY_cpy[1] != KEY[1])) {
        Menu::KEY_cpy[0] = KEY[0];
        Menu::KEY_cpy[1] = KEY[1];
        Menu::KEY_wrk[0] = Menu::KEY_cpy[0];
        Menu::KEY_wrk[1] = Menu::KEY_cpy[1];
        LCD_light=60;
    }

    // принудительная очистка экрана ЖКИ
    for (i=0; i<(MAX_LENGTH*MAX_ROWS); i++) {
        LCD_str[i] = 0x20;
    }

    tech_fl & DIG_INPUT ? show_dig() : Menu::pCurrentMenu->showMenu();

    Menu::KEY_wrk[0] = 0x00;
    Menu::KEY_wrk[1] = 0x00;
}

// Если нам нужно показать нижнюю строчку, то выводим что нам нужно и 
// возвращаем false иначе ничего не выводим и возвращаем true
bool Menu::show_low_menu_string()
{
    switch (FireSrc)
    {
        case FromPK:
            // "Пожар ПК"
            LCD << firePK_str << ' ' << FireFloor.GetLcd();
            break;

        case FromSPS:
            // "Пожар СПС "
            LCD << fireSPS_str << ' ' << FireFloor.GetLcd();
            break;

        case FromMenu:
            // "Пожар Меню"
            LCD << fireMenu_str << ' ' << FireFloor.GetLcd();
            break;

        case StopPDZ:
            // " Стоп ПДЗ"
            LCD << strStopPdz;
            break;

        case NoFire:
    	default:
            return true;
    		break;
    }

    return false;
}

/*
    Функция инкрементирует передаваемые в нее значению по нажатию кнопки
*/
uint8_t getpm(uint8_t val,uint8_t max)
{
    if ( KEY_5 ) {
        val++;
        if(val>=max) val=0;
    }
    if ( KEY_2 ) {
        if(!val)    val=max-1;
        else        val--;
    }
    return val;
}

int16_t *pm_val;
int16_t pm_minv,pm_maxv,pm2;
uint8_t pm_dot;

void getpm_dig(int16_t *val, uint8_t dot, int16_t min_val, int16_t max_val)
{
    if(KEY_0)//(KEY_2)
    {
        tech_fl|=DIG_INPUT;
        tech_fl&=~DIG_MINUS;
        pm_val=val;
        pm_minv=min_val;
        pm_maxv=max_val;
        pm_dot=dot;
        pm2=0;
    }
}

extern const char show_dig_str[][5] PROGMEM;
const char show_dig_str[2][5] =
{
    "min:",
    "max:"
};

void show_dig(void)
{
    if(tech_fl&DIG_MINUS) LCD_putc('-',10);

    LCD_float(pm2, pm_dot, 0);
    LCD_abc((char*)show_dig_str[0],6);
    LCD_float(pm_minv, pm_dot, 10);

    LCD_float(*pm_val, pm_dot, 16);
    LCD_abc((char*)show_dig_str[1],22);
    LCD_float(pm_maxv, pm_dot, 26);

    if(KEY_OK)
    {
        if((pm2<=pm_maxv)&&(pm2>=pm_minv))
            *pm_val=pm2;
        tech_fl&=~DIG_INPUT;
    }
    if(KEY_NO)
    {
        if(pm2) {pm2=0;tech_fl&=~DIG_MINUS;}
        else tech_fl&=~DIG_INPUT;
    }
    if(!(tech_fl&DIG_MINUS))
    {
        if(KEY_1) {if(((pm2*10+1)<=pm_maxv)//&&((pm2*10+1)>=pm_minv)
                &&((pm2*10+1)>0)) pm2=(pm2*10+1);}
        if(KEY_2) {if(((pm2*10+2)<=pm_maxv)//&&((pm2*10+2)>=pm_minv)
                &&((pm2*10+2)>0)) pm2=(pm2*10+2);}
        if(KEY_3) {if(((pm2*10+3)<=pm_maxv)//&&((pm2*10+3)>=pm_minv)
                &&((pm2*10+3)>0)) pm2=(pm2*10+3);}
        if(KEY_4) {if(((pm2*10+4)<=pm_maxv)//&&((pm2*10+4)>=pm_minv)
                &&((pm2*10+4)>0)) pm2=(pm2*10+4);}
        if(KEY_5) {if(((pm2*10+5)<=pm_maxv)//&&((pm2*10+5)>=pm_minv)
                &&((pm2*10+5)>0)) pm2=(pm2*10+5);}
        if(KEY_6) {if(((pm2*10+6)<=pm_maxv)//&&((pm2*10+6)>=pm_minv)
                &&((pm2*10+6)>0)) pm2=(pm2*10+6);}
        if(KEY_7) {if(((pm2*10+7)<=pm_maxv)//&&((pm2*10+7)>=pm_minv)
                &&((pm2*10+7)>0)) pm2=(pm2*10+7);}
        if(KEY_8) {if(((pm2*10+8)<=pm_maxv)//&&((pm2*10+8)>=pm_minv)
                &&((pm2*10+8)>0)) pm2=(pm2*10+8);}
        if(KEY_9) {if(((pm2*10+9)<=pm_maxv)//&&((pm2*10+9)>=pm_minv)
                &&((pm2*10+9)>0)) pm2=(pm2*10+9);}
        if(KEY_0) { if(!pm2)
                {
                    if(pm_minv<0)
                        tech_fl|=DIG_MINUS;
                }
                if(((pm2*10+0)<=pm_maxv)//&&((pm2*10+0)>=pm_minv)
                    &&((pm2*10+0)>0)) pm2=(pm2*10+0);}
    }
    else
    {
        if(KEY_1) {if(((pm2*10-1)>=pm_minv)//&&((pm2*10-1)<=pm_maxv)
                &&((pm2*10-1)<0)) pm2=(pm2*10-1);}
        if(KEY_2) {if(((pm2*10-2)>=pm_minv)//&&((pm2*10-2)<=pm_maxv)
                  &&((pm2*10-2)<0)) pm2=(pm2*10-2);}
        if(KEY_3) {if(((pm2*10-3)>=pm_minv)//&&((pm2*10-3)<=pm_maxv)
                  &&((pm2*10-3)<0)) pm2=(pm2*10-3);}
        if(KEY_4) {if(((pm2*10-4)>=pm_minv)//&&((pm2*10-4)<=pm_maxv)
                  &&((pm2*10-4)<0)) pm2=(pm2*10-4);}
        if(KEY_5) {if(((pm2*10-5)>=pm_minv)//&&((pm2*10-5)<=pm_maxv)
                  &&((pm2*10-5)<0)) pm2=(pm2*10-5);}
        if(KEY_6) {if(((pm2*10-6)>=pm_minv)//&&((pm2*10-6)<=pm_maxv)
                  &&((pm2*10-6)<0)) pm2=(pm2*10-6);}
        if(KEY_7) {if(((pm2*10-7)>=pm_minv)//&&((pm2*10-7)<=pm_maxv)
                  &&((pm2*10-7)<0)) pm2=(pm2*10-7);}
        if(KEY_8) {if(((pm2*10-8)>=pm_minv)//&&((pm2*10-8)<=pm_maxv)
                  &&((pm2*10-8)<0)) pm2=(pm2*10-8);}
        if(KEY_9) {if(((pm2*10-9)>=pm_minv)//&&((pm2*10-9)<=pm_maxv)
                  &&((pm2*10-9)<0)) pm2=(pm2*10-9);}
        if(KEY_0) {if(((pm2*10-0)>=pm_minv)//&&((pm2*10-0)<=pm_maxv)
                  &&((pm2*10-0)<0)) pm2=(pm2*10-0);}
    }
}

/* Используем если нам нужно перезагрузить мртп. Функция вызывает из
 * меню и мы никогда из нее не возвращаемся
 *
 * Перезагрузка возможно только при включенном watchdog таймером.
 * Операционная система никак не влияет на ход перезагрузки, поскольку
 * не происходит переключения процессов а сторожевой таймер сбрасывается
 * только в самом начале, когда программа заново запускает процесс на
 * выполнение.
 * */
void mrtp_reset()
{
    for (;;) {
        ;
    }
}

