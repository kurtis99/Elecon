#ifndef __DEVKOG_H
    #define __DEVKOG_H

    #include "Devs.h"
    #include <Global_define.h>
    
    #define KOG_END_DEVICE     0x0008
    
    enum { KOG_C_CLOSE,  KOG_C_OPEN };
    enum { KOG_ST_CLOSE, KOG_ST_OPEN };

    extern uint8_t ThisIsTotalNull;

    class KOG: public TechObj
    {
        private:
            static const unsigned char START_DELAY = 10;
//            void to_start()     { BusyWork = 0xFF; };
//            void to_stop() { BusyWork = 0x00; };
//            bool is_start()   { return ( BusyWork == 0xFF ); };

            //static uint8_t BusyWork;
            static uint8_t add_delay;

            TechStad < uint8_t > openStad;
        
            uint8_t & mnemoLamp;    //лампочка устройства
            outPort & IO_Port;
            uint8_t & checkPress;   //Где на МСК перепад давления
            //uint8_t & checkMP;      //Ошибка магнитного пускателя
            uint8_t & devNetStatus; //сетевой статус устройства
            uint8_t & devNetCmd;    //команда управления устройством
        public:
            uint16_t t_wait_press;
            uint16_t t_wait_press_counter;
            //uint16_t t_wait_mp;
            //uint16_t t_wait_mp_counter;
            bool isRunning()
            {
                return ( stad == KOG_ST_OPEN ) ? true : false;
            }

            virtual void drv();
            virtual void show_mnem();
            virtual void show_lcd();

            void check_press();
            void check_mp();
            void check_os();

            void auto_open();
            void auto_close();

            KOG( const char * _name, 
                 uint8_t& _mn_os, 
                 outPort& _IO_Port,
                 uint8_t& _press,
                 //uint8_t& _MP,
                 uint8_t& _net_stat,
                 uint8_t& _net_cmd )
                : mnemoLamp  ( _mn_os    ),
                IO_Port      ( _IO_Port  ),
                checkPress   ( _press    ),
                //checkMP      ( _MP       ),
                devNetStatus ( _net_stat ),
                devNetCmd    ( _net_cmd  )            
                {
                    add_delay = 0;
                    clear_t_stad();
                    clear_t_sub_st();
                    cmd = KOG_C_CLOSE;
                    t_wait_press=10;
                    t_wait_press_counter=t_wait_press;
                    //t_wait_mp=5;
                    //t_wait_mp_counter=t_wait_mp;
                    name = _name;
                    
                    enh_info = KOG_CHECK_PRESS|KOG_CHECK_OS;
                }

            KOG( const char * _name, 
                 uint8_t& _mn_os, 
                 outPort& _IO_Port,
                 uint8_t& _press)
                 //uint8_t& _MP)
                : mnemoLamp  ( _mn_os   ),
                IO_Port      ( _IO_Port ),
                checkPress   ( _press   ),
                //checkMP      ( _MP      ),
                devNetStatus ( ThisIsTotalNull ),
                devNetCmd    ( ThisIsTotalNull )            
                {
                    clear_t_stad();
                    clear_t_sub_st();
                    cmd = KOG_C_CLOSE;
                    t_wait_press=10;
                    t_wait_press_counter=t_wait_press;
                    //t_wait_mp=5;
                    //t_wait_mp_counter=t_wait_mp;
                    name = _name;

                    enh_info = KOG_CHECK_PRESS|KOG_CHECK_OS|KOG_END_DEVICE;
                }
            virtual ~KOG() {};
    };

#endif