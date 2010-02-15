#include "Test.h"

void showSystVersion()
{
    LCD.init();
    LCD << strCompilationDate;
    LCD.newLine();
    LCD << strCompilationTime;
}

extern uint8_t MSK[];
extern outPort IoField[];

// Проверяем выдачу синалов на порты вывода
void show_mt_test()
{
    static uint8_t counter;

    IoField[counter].Out.Clear();

    counter=getpm(counter,16);
    IoField[counter].Out.Set();

    LCD.init();
    LCD << '[' << counter << ']';

    // Если выходим то гасим лампочку
    if (KEY_3) {
        IoField[counter].Out.Clear();
        counter = 0;
    }
}

// Смотрим текущее состояние МСК
void show_msk_test()
{
    LCD_abc((char*)msk_test_str[0],0);
    LCD_uind16(MSK[3],5, 2);//|LEAD_ZERO);
    LCD_uind16(MSK[2],8, 2);
    LCD_uind16(MSK[1],11,2);
    LCD_uind16(MSK[0],14,2);

    LCD_abc((char*)msk_test_str[1],MAX_LENGTH);
    LCD_uind16(MSK[7],MAX_LENGTH+5,2);
    LCD_uind16(MSK[6],MAX_LENGTH+8,2);
    LCD_uind16(MSK[5],MAX_LENGTH+11,2);
    LCD_uind16(MSK[4],MAX_LENGTH+14,2);
}

// Не трогать!
static uint8_t mnemo_number;

static const uint8_t       RED = 0x01;
static const uint8_t     GREEN = 0x02;
static const uint8_t    YELLOW = 0x04;
static const uint8_t     FREEZ = 0x08;
static const uint8_t     FIELD = 0x10;
static const uint8_t MNEMO_WRK = 0x20;

static uint8_t mnemo_test_color;

void show_mnemo_test()
{
    mnemo_number=getpm(mnemo_number,NUM_OF_MNEMO);
    mnemo_test_color|=MNEMO_WRK;
    if (KEY_4)   mnemo_test_color ^= FIELD;
    if (KEY_7)  {mnemo_test_color &= ~(GREEN|YELLOW|RED);}
    if (KEY_8)  {mnemo_test_color &= ~(GREEN|YELLOW    ); mnemo_test_color |= RED;}
    if (KEY_9)  {mnemo_test_color &= ~(GREEN|       RED); mnemo_test_color |= YELLOW;}
    if (KEY_NO) {mnemo_test_color &= ~(      YELLOW|RED); mnemo_test_color |= GREEN;}

    if (mnemo_test_color&FIELD)
        LCD_abc((char*)mnemo_str[0],0);
    else
        LCD_abc((char*)mnemo_str[1],0);

    if (mnemo_test_color&FREEZ)
        LCD_abc((char*)mnemo_str[6],10);

    if (!(mnemo_test_color&(RED|GREEN|YELLOW)))  LCD_abc((char*)mnemo_str[2],5);
    else if (mnemo_test_color&RED)               LCD_abc((char*)mnemo_str[3],5);
    else if (mnemo_test_color&YELLOW)            LCD_abc((char*)mnemo_str[4],5);
    else                                         LCD_abc((char*)mnemo_str[5],5);

    if (KEY_3) {
        mnemo_test_color &= ~(RED|GREEN|YELLOW);
    }

    LCD_uind16(mnemo_number,20,2|LEAD_ZERO);
}

void mnemo_test_work()
{
    uint8_t counter;
    uint8_t color = NULL_LAMP;
    static uint8_t OLDVAL_mnemo_number = 0;

    if (!(mnemo_test_color & MNEMO_WRK))
        return;

    mnemo_test_color&=~MNEMO_WRK;

    if (mnemo_test_color & RED) {
        color=RED_LAMP;
    } else if (mnemo_test_color & YELLOW) {
        color=YELLOW_LAMP;
    } else if (mnemo_test_color & GREEN) {
        color=GREEN_LAMP;
    } else {
        color=NULL_LAMP;
    }

    for (counter = 0; counter < 80; counter++) {
        mnemo[mnemo_number].LED_FIELD[counter] = color;
    }
    if (OLDVAL_mnemo_number != mnemo_number) {
        for (counter = 0; counter < 80; counter++) {
            mnemo[OLDVAL_mnemo_number].LED_FIELD[counter] = NULL_LAMP;
        }
    }
    OLDVAL_mnemo_number = mnemo_number;
}
