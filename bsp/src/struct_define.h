#ifndef __STRUCT_DEFINE_H
    #define __STRUCT_DEFINE_H

    #include <scmRTOS.h>
    #include <Global_define.h>

    /*************************************************
     Структуры данных (не связанные с сетевым обменом)
     *************************************************/

    /* Структура содержащая информация о УАПП */
    typedef struct
    {
        uint8_t usart_info;
        uint8_t uart_status;
        uint8_t uart_switcher;
        uint8_t uart_checksum;
        uint8_t uart_flags;
        uint8_t uart_counter;
        uint8_t switcher;
        OS::TEventFlag efUSART_TX;
    }
        USART_CONF;

    //template <typename ClasssType>
    class ByteWork
    {
        private:
            uint8_t ByteValue;
        public:
            void Set()   { ByteValue = 0xFF; };
            void Clear() { ByteValue = 0x00; };
            bool Check() { return ( 0 == ByteValue ) ? false : true; };

            ByteWork()
            : ByteValue ( 0 )
            {};
    };

    struct outPort
    {
        ByteWork Out;    //Выдача в порт
        ByteWork Os;     //Состояние обратных связей
    };

/*
- В чем здесь смысл?
- Я не знаю!
    (с) Михаил Бойко, 2009
*/
struct BfppFloorCounter {
    uint8_t bfpp_counter;      // счетчик для БФПП
    uint8_t floor_counter;     // счетчик обслуживаемых этажей на БФПП
};				// ----------  end of struct BfppFloorCounter  ----

    /************************************************
                     Сетевые структуры
     ************************************************/

    /* Всегда должна быть сверху */
    /* Описует голову ВСЕХ сетевых пакетов */
    /* Исходя из предыдущего утверждения, голова должна быть ВЕЗДЕ и 
     * желательно в нужном месте */
    typedef struct
    {
        uint8_t size;
        uint8_t adr;
        uint8_t cmd;
    }
        HEAD_NET_STRUCT;

    #include <net485.h> /* Не переселять */

    typedef struct
    {
        HEAD_NET_STRUCT head;
        uint8_t out_led;
        uint8_t foo1;
        uint8_t foo2;
        uint8_t foo3;
    }
        NET_BFPP_OUTPUT_STRUCT;

    /* Îòâåò îò ÁÔÏÏ */
    typedef struct
    {
        HEAD_NET_STRUCT head;
        uint8_t msk1;
        uint8_t msk2;
        uint8_t status;
        uint8_t dip;
    }
        NET_BFPP_INPUT_STRUCT;


    /* Запрос к плате ЖКИ. Информация выводимая на экран */
    typedef struct
    {
        HEAD_NET_STRUCT head;
        uint8_t out_lcd[MAX_LENGTH*MAX_ROWS+4];
    }
        LCD_OUTPUT_STRUCT;

    /* Ответ от платы ЖКИ. Кнопки*/
    typedef struct
    {
        HEAD_NET_STRUCT head;
        uint8_t key[2];
    }
        LCD_INPUT_STRUCT;

    /* Îòîáðàæåíèå èíôîðìàöèè íà ÂÈÒ */
    typedef struct
    {
        HEAD_NET_STRUCT head;
        uint8_t fire_floor;
        uint8_t status;
        uint8_t fire_buzer;
    }
        VIT_OUTPUT_STRUCT;
    typedef struct
    {
        HEAD_NET_STRUCT head;
        uint8_t foo;
    }
        VIT_INPUT_STRUCT;

    /* Выдача на мнемосхему */
    typedef struct
    {
        HEAD_NET_STRUCT head;
        uint8_t status;
        uint8_t LED_FIELD[80];
    }
        MNEMO_OUTPUT_STRUCT;
    typedef struct
    {
        HEAD_NET_STRUCT head;
        uint8_t foo;
    }
        MNEMO_INPUT_STRUCT;

    /* принцип 3-х "Н" ( Не изменять, не удалять и не использовать ) */
    typedef struct
    {
        HEAD_NET_STRUCT head;
        uint8_t null;
    }
        NULL_STRUCT;

    /* Структкура общения с 7-ми сегментным индикатором типа НЕжопа */
    typedef struct
    {
        HEAD_NET_STRUCT head;
        int16_t base;
        uint8_t simb_d[5];
        uint8_t foo;
    }
        SEGM7_DATA_STUCT;

    #define UART0_MASTER DA
    #define UART1_MASTER DA

    /* Макросы, указующие линкеру, в какой секции памяти следует 
     * разместить информацию */
    #if I_HAVE_NORAM == 1
        #define XDATA DATA
        #define XBSS  BSS
    #else
        #define XDATA __attribute__((section(".xdata")))
        #define XBSS  __attribute__((section(".xbss")))
    #endif
    #define DATA  __attribute__((section(".data")))
    #define BSS   __attribute__((section(".bss")))

#endif  /*__STRUCT_DEFINE_H*/
