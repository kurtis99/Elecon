#ifndef SETCONFIG_H
    #define SETCONFIG_H

    extern uint8_t tech_fl;
    #define DIG_INPUT   0x01
    #define DIG_MINUS   0x02


    namespace Menu {
        extern uint8_t KEY_wrk[];
    }

    extern int16_t *pm_val;
    extern int16_t pm_minv,pm_maxv,pm2;
    extern uint8_t pm_dot;

    class SetConfig
    {
        public:
            const char *name;
            int16_t value;
            int16_t min_value;
            int16_t max_value;
            uint8_t dot;

            void makeDigitalInput()
            {
                if ( Menu::KEY_wrk[0] & ( 1 << 7 ) )
                {
                    tech_fl |=  DIG_INPUT;
                    tech_fl &=~ DIG_MINUS;
                    pm_val   =  &value;
                    pm_minv  =  min_value;
                    pm_maxv  =  max_value;
                    pm_dot   =  dot;
                    pm2      =  0;
                }
            };

            SetConfig(const char * _name, int16_t _value, int16_t _min_value, int16_t _max_value, uint8_t _dot)
            : name    ( _name      ),
            value     ( _value     ),
            min_value ( _min_value ),
            max_value ( _max_value ),
            dot       ( _dot       )
            {};
    };

#endif /* SETCONFIG_H */