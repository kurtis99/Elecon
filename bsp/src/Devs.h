#ifndef __DEVS_H
    #define __DEVS_H

    #include <avr/delay.h>

    #include <Nls.h>
    #include "TechObj.h"
    #include "Menu.h"
    #include "Main.h"

    #include <Dev_kog_net.h>
    #include <Dev_vzk_net.h>
    #include <Dev_kpd_net.h>

    #define SIZE_OF(_array)    ( sizeof(_array) / sizeof(_array[0]) )

    /* Количество наборов уставок */
    #define NUM_OF_DEV_SET 1

#endif
