#ifndef __NETPACK_H
    #define __NETPACK_H

    #include "Uart.h"
    #include <Main.h>
    #include <string.h>

    #define NUM_OF_USART0  (sizeof(pUSART0_info) / sizeof(pUSART0_info[0]))
    #define NUM_OF_USART1  (sizeof(pUSART1_info) / sizeof(pUSART1_info[0]))

    class NetTransferConstrol
    {
    /*
        Рапологается информация про функцию отвечающую за передачу массива в сеть
        Обьект входит в состав более абстрактного класса, который управляет процессом передачи
                                                                                                */
    /*  Написанный выше комментарий ложный, но удалят его не стоит, т.к. он наталкивает
        на правильные мысли
                            */
        private:
            uint8_t status;
            /* Статусная информация */
            static const unsigned char NET_OK          = 0x01;
            static const unsigned char NET_PACKET_SEND = 0x02;
            static const unsigned char NET_PACKET_OVRF = 0x04;
            static const unsigned char NET_NOANSWER    = 0x08;
            static const unsigned char I_HAVE_NO_NET   = 15;

            uint8_t ErrorNetPack;           //Количество сбойных пакетов

            uint8_t send_addr;              //Адрес исходящей почты    (нпр 0x34, 0x55 и тд)
            uint8_t data_info;              //нформация о письме      ('d', 'D'...)

            void * Psend_arr;               //Место, где лежит исходящая почта
            uint8_t * Precv_arr;            //Место, куда класть входящую почту
            uint8_t size_sendmail;          //Размер исходящей почты, sizeof(почта_in)
            uint8_t size_recvmail;          //Размер входящей почты, sizeof(почта_out)
            uint8_t * uart_tx_buffer;       //Адрес буфера посылки USART, для разных УАПП буферы разные
            uint8_t * uart_rx_buffer;       //Адрес буфера приема USART, для разных УАПП буферы разные

            void set_status(uint8_t C_status) {status |= C_status;};
            void clr_status(uint8_t C_status) {status &=~C_status;};
        public:

            void data_send();       //Функция
            void data_recv();       // тоже функция

            void ReceiveWork() {;};
            void SendWork()    {;};

            inline uint8_t get_send_adr()       {return send_addr;    };
            inline uint8_t get_status()         {return status;       };
            inline uint8_t get_error_packet()   {return ErrorNetPack; };
            inline uint8_t Get_SizeSendMail()   {return size_sendmail;};
            inline uint8_t Get_SizeRecvMail()   {return size_recvmail;};

            inline void * Get_Psend_arr()       {return Psend_arr;    };

            void inc_error_packet();

            bool haveNetConnect() { return ( ErrorNetPack > I_HAVE_NO_NET ? false : true ); };
            bool haveNetMasterConnect() { return ( ErrorNetPack > 50 ? false : true ); };

            //bool haveNetConnect() { return ( status & NET_PACKET_OVRF ? false : true ); };

            NetTransferConstrol ( uint8_t EX_send_addr,
                                  uint8_t EX_data_info,
                                  uint8_t EX_size_sendmail,
                                  uint8_t EX_size_recvmail,
                                  uint8_t * EX_Psend_arr,
                                  uint8_t * EX_Precv_arr,
                                  uint8_t * EX_uart_tx_buffer,
                                  uint8_t * EX_uart_rx_buffer
                                                                )
                        {
                            send_addr       = EX_send_addr;
                            data_info       = EX_data_info;
                            size_sendmail   = EX_size_sendmail;
                            size_recvmail   = EX_size_recvmail;
                            Psend_arr       = EX_Psend_arr;
                            Precv_arr       = EX_Precv_arr;
                            uart_tx_buffer  = EX_uart_tx_buffer;
                            uart_rx_buffer  = EX_uart_rx_buffer;
                            ErrorNetPack = I_HAVE_NO_NET;
                        }
            //~NetTransferConstrol();
    };

    /* Глупый класс, который вызывает драйвер УАПП, который У А Пи Пирует всех и вся!!! */
    class USART_control
    {
        private:
            uint8_t temp;
            uint8_t NumOfUSART;
            void usart_inc();
            uint8_t switcher;
            USART_CONF & sUSART;        //Структура состояния УАПП
            NetTransferConstrol ** pUSART_info;
            uint8_t status;
            #define NOTHING_TO_SEND 0x01
            #define NOTHING_TO_RECV 0x02
        public:
            uint8_t UsartX_WorkDrv();

            USART_control(USART_CONF & _sUSART, NetTransferConstrol ** EX_pUSART_info, uint8_t EX_NumOfUSART)
            : sUSART ( _sUSART )
            {
                pUSART_info        = EX_pUSART_info;
                NumOfUSART         = EX_NumOfUSART;
                sUSART.switcher    = 0;
                switcher           = 0;
                status             = 0;
                usart_inc();
            }
    };

#define UART0_SET(_func_name, _net_in, _data_type, _mas_in, _mas_out) \
                NetTransferConstrol _func_name((uint8_t)_net_in,    \
                                        (uint8_t)_data_type,        \
                                        (uint8_t)sizeof(_mas_in),   \
                                        (uint8_t)sizeof(_mas_out),  \
                                        &_mas_out.head.size,        \
                                        &_mas_in.head.size,         \
                                        (uint8_t*)tx_local_buffer0, \
                                        (uint8_t*)rx_local_buffer0  \
                                        );

#define UART1_SET(_func_name, _net_in, _data_type, _mas_in, _mas_out) \
                NetTransferConstrol _func_name((uint8_t)_net_in,    \
                                        (uint8_t)_data_type,        \
                                        (uint8_t)sizeof(_mas_in),   \
                                        (uint8_t)sizeof(_mas_out),  \
                                        &_mas_out.head.size,        \
                                        &_mas_in.head.size,         \
                                        (uint8_t*)tx_local_buffer1, \
                                        (uint8_t*)rx_local_buffer1  \
                                        );

#endif
