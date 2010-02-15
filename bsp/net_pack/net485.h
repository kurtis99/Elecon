#ifndef __NET485_H
    #define __NET485_H

    /* Пакет для Slave от Center */
    typedef struct
    {
        HEAD_NET_STRUCT head;
        uint8_t     dev_status[14];
        uint8_t     lift;
        uint8_t     fooo;
    }
        STRUCT_FOR_CENTER;
    typedef struct
    {
        HEAD_NET_STRUCT head;
        uint8_t     start;
        uint8_t     dev_cmd[14];
        uint8_t     lift_cmd;
        uint8_t     fire;
        uint8_t     foo_foo;
    }
        STRUCT_FROM_CENTER;

#endif 	/* __NET485_H */
