#ifndef __PDZ_H
    #define __PDZ_H

    #include "Devs.h"
    #include "TechObj.h"
    #include "Menu.h"

    #include "Dev_kog.h"
    #include "Dev_kog_net.h"
    #include "AllStrings.h"

    #include <Nls.h>

    //#include <pin_macros.h>

    enum {
        PDZ_ST_STOP,
        PDZ_ST_WORK
    };

    /* Флаги enh_info */
    //#define PDZ_STOP_ERROR	0x0001
    //#define PDZ_FULL_OPEN	0x0002

    /* Флаги FireStatus */
    //#define SET_FIRE 0x01
    //#define STOP_PDZ 0x02

    /* Флаги FireReturnStatus */
    //#define I_HAVE_FIRE 0x01
    //#define I_HAVE_STOP 0x02

    /* Количество систем ПДЗ */
    #define NUM_OF_PDZ 1

    extern void Pdz1_drv();
    extern void Pdz1_show_lcd();

    extern const char pdz_name_str[6] PROGMEM;

    class Pdz: public TechObj
    {
        private:
            static const unsigned char FIRE_SPS = 0x01;
            static const unsigned char FIRE_PK  = 0x02;
            static const unsigned char FIRE     = 0x04;
            static const unsigned char FIRE_NET = 0x08;

            uint8_t & lampFirePK;               // Лампочка пожара от ПК
            uint8_t & lampFireSPS;              // Лампочка пожара от СПС

            uint8_t FireFloorSPS;
            uint8_t FireFloorPK;

            StatusI <uint8_t> FireInfo;         // Информация о пожаре
        public:
            virtual void drv();
            virtual void show_mnem();
            virtual void show_lcd();

            void SetDeviceNetError() {;};
            void ClrDeviceNetError() {;};

            void FireStopPdz()
            {
                FireInfo.Null();
                FireFloorSPS = 0;
                FireFloorPK = 0;
                //scafe_fl &= ~(SCAFE_FIRE|SCAFE_FIRE_SPS|SCAFE_FIRE_PK);
                //scafe_fl |= SCAFE_STOP_PDZ;
//                cFireFloor.ClearFireFloor();
            };

            void to_stad(uint8_t _stad, uint8_t _sub_st)
            {
                if( stad != _stad ) {
                    clear_t_stad();
                    clear_t_sub_st();
                    stad = _stad;
                    sub_st = 0;
                }
                if( sub_st != _sub_st ) {
                    clear_t_sub_st();
                    sub_st = _sub_st;
                }
            }
            void inc_stad()
            {
                sub_st++;
            }

            Pdz( uint8_t & _mn_osPK,
                 uint8_t & _mn_osSPS )
            : lampFirePK ( _mn_osPK  ),
            lampFireSPS  ( _mn_osSPS )
            {
//                name = pdz_name_str[0];

                clear_t_stad();
                clear_t_sub_st();
                FireFloorSPS = 0;
                FireFloorPK = 0;
            }
            virtual ~Pdz() {};
    };
#endif
