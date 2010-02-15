#ifndef  ETAZ2_INC
#define  ETAZ2_INC

#include	<EtazItem.h>
#include	<Floor.h>
#include    <Nls.h>
#include    "Main.h"
#include    <struct_define.h>
#include    <Global_define.h>

class NetTransferConstrol;
class Floor;

class EtazItem2 : public EtazItem
{
    private:
        /* Лампочки и выдача БФПП    (data_for_bfpp.out_Лed) */
        static const unsigned char OUT_BFPP1  = (1 << 0);
        static const unsigned char OUT_BFPP2  = (1 << 1);
        static const unsigned char OUT_BFPP3  = (1 << 2);
        static const unsigned char OUT_BFPP4  = (1 << 3);
        static const unsigned char HL0        = (1 << 4);
        static const unsigned char HL1        = (1 << 5);
        static const unsigned char HL2        = (1 << 6);
        static const unsigned char HL3        = (1 << 7);

        /* Первая 8-ка МСК */
        static const unsigned char BFPP_FIRE_FLOOR1 = (1 << 6);
        static const unsigned char BFPP_FIRE_FLOOR2 = (1 << 7);
    public:
        void CheckBfpp();
        uint8_t EtazDrv();

        BfppFloorCounter return_CurrentBfppFloor();
        uint8_t return_CurrentFloor();

		uint8_t return_lo_enh() { return enh_info; };
		uint8_t return_hi_enh() { return enh_info >> 8; };

        uint8_t getErrorPacket();
        uint8_t getSendAddress();

        /*void increment();*/
        uint8_t get_current_floor();
        void set_next_fire_floor(BfppFloorCounter & bfpp_counter);
        uint8_t num_of_floors();

        void SetDeviceNetError() {;};
        void ClrDeviceNetError() {;};

        uint8_t set_fire(eFireSource state);

        EtazItem2 ( 
            
            uint8_t &  _mYA11,    
            uint8_t &  _mYA12,    
            uint8_t &  _mSPS1,
            uint8_t &  _mSB_SQ1,  
            uint8_t &  _mBUPK1,   
            
            uint8_t &  _mYA21,    
            uint8_t &  _mYA22,
            uint8_t &  _mSPS2,    
            uint8_t &  _mSB_SQ2,  
            uint8_t &  _mBUPK2,   

            uint8_t &  _mFire,

            uint8_t &  _kFireSPS1,
            uint8_t &  _kFireSPS2,

            NetTransferConstrol & _cBfppClass 
                )
              : 
                floor1 (_mYA11, _mYA12, _mSPS1, _mSB_SQ1, _mBUPK1),
                floor2 (_mYA21, _mYA22, _mSPS2, _mSB_SQ2, _mBUPK2),
                FireMnemo (_mFire),
                kFireSPS1 (_kFireSPS1),
                kFireSPS2 (_kFireSPS2),

                cBfppClass (_cBfppClass)
        {
            StartUp();
        };

        virtual void drv() {;};
        virtual void show_lcd() {};
        virtual void show_mnem();
        virtual void show_menu(uint8_t cur_floor);

        void auto_open();
        void auto_close();

        void doStopPdz();
    private:
        //static uint8_t CurrentFloor;
        uint8_t poweroff_counter;

        uint8_t status;

        Floor floor1;
        Floor floor2;

        void drv_YA1();
        void drv_YA2();

        uint8_t & FireMnemo; // лампочка БФПП
        uint8_t & kFireSPS1;
        uint8_t & kFireSPS2;

        uint8_t out;          //выдача БФПП
        NetTransferConstrol & cBfppClass;

        void BUPK_WorkDrv();
        void SBSQ_WorkDrv();
        void YA_WorkDrv();
        void YA_LedStatus();

        inline void StartUp()
        {
            clear_t_stad();
            read_t_sub_st();
            /*enh_info &= LINK_OK;*/
            /*enh_info  = 0;*/
            status    = 0;
            stad      = 0;
            sub_st    = 0;
            out       = 0xff;
            poweroff_counter = 0;
        };
};

#endif   // ----- #ifndef ETAZ2_INC  -----
