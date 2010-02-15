#ifndef __SGWORK_H
    #define __SGWORK_H

    #include <avr/io.h>

    #include "Main.h"
    #include <Nls.h>

    #include <Global_define.h>

    extern uint16_t scafe_fl;
    extern uint8_t status;//объявлены в Main.h в структуре
    extern uint8_t cmd;//объявлены в Main.h в структуре

    //extern uint8_t stat_g;
    #define VIT_READY       0x01//
    #define VIT_DUTY        0x02//
    #define VIT_NET         0x04//
    #define VIT_PUMP        0x08//
    //#define           0x0010//
    //#define           0x0020//
    //#define           0x0040//
    #define VIT_LIFT        0x80//

#endif
