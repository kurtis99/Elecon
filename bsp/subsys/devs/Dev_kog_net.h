#ifndef __DEVKOGNET_H
    #define __DEVKOGNET_H

    #include "Devs.h"
    #include <Global_define.h>

    enum {KOGNET_C_CLOSE,KOGNET_C_OPEN};
    enum {KOGNET_ST_CLOSE,KOGNET_ST_OPEN};

    class KOG_NET: public TechObj
    {
        private:
            uint8_t &mn_os;         //лампочка устройства
            uint8_t &net_stat;      //сетевой статус устройства
            uint8_t &net_cmd;       //команда управления устройством   
        public:
            void SetDeviceNetError() { 
                net_stat |=  NETDEV_NETERROR; 
            };
            void ClrDeviceNetError() { 
                net_stat &= ~NETDEV_NETERROR; 
            };
            
            void drv();
            void show_mnem();
            void show_lcd();
            void auto_open();
            void auto_close();
            KOG_NET( const char * _name,
                     uint8_t& _mn_os,
                     uint8_t& _net_stat,
                     uint8_t& _net_cmd )
                    : mn_os  ( _mn_os    ),
                    net_stat ( _net_stat ),
                    net_cmd  ( _net_cmd  )
                {
                    clear_t_stad();
                    clear_t_sub_st();
                    name=_name;
                    //net_stat = NETDEV_CL;
                }
            virtual ~KOG_NET() {};
    };

#endif
