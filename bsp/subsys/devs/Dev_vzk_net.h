#ifndef DEVNETVZK_H
    #define DEVNETVZK_H

    #include <Devs.h>
    #include <Global_define.h>

    template < uint8_t NumOfClapans >
    class VZK_NET : public TechObjTemplate
    {
        private:
            uint8_t * (&mnemoLamps)[NumOfClapans];  // Лампочки состояние клапанов
            uint8_t * netGetLamp;                   // Лампочки на ДПУ
            uint8_t error_count;
            uint8_t error_store_val;
        public:
            virtual void show_mnem();

            VZK_NET(uint8_t * (&_mnemoLamps)[NumOfClapans],
                    uint8_t * _netReceive )
                    : mnemoLamps (_mnemoLamps)
                    {
                        netGetLamp = _netReceive;
                    };
            virtual ~VZK_NET() {};
    };

    template < uint8_t NumOfClapans >
    void VZK_NET<NumOfClapans>::show_mnem()
    {
        uint8_t index;

        error_count = 0;

        for (index=0; index < NumOfClapans; index++) {
            if (isNetOk()) {
                *mnemoLamps[index] = netGetLamp[index];
                if (netGetLamp[index] == B_RED_LAMP) {
                    error_count++;
                }
            }
            else {
                *mnemoLamps[index] = NULL_LAMP;
            }
        }

        error_vzk_num++;

        if (error_count) {
            if (error_store_val == 0xff)
                error_vzk_num--;
            error_store_val = 0xff;
        }
        else {
            error_vzk_num--;
            error_store_val = 0x0;
        }
    }

#endif
