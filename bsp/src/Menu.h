#ifndef __MENU_H
    #define __MENU_H

    #include "Main.h"

    #include <class/MenuGlobal.h>
    #include <class/MenuInter.h>
    #include <class/MenuEnd.h>
    #include <class/MenuAlarm.h>


    extern void show_dig(void);
    extern void getpm_dig(int16_t *val, uint8_t dot, int16_t min_val, int16_t max_val);
    extern uint8_t getpm(uint8_t val,uint8_t max);

#endif
