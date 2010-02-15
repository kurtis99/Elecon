#ifndef __TECHOBJ_H
    #define __TECHOBJ_H

    #include <avr/io.h>
    #include <avr/pgmspace.h>
    
    extern volatile uint8_t sec_tik;

    template <typename ClasssType> 
    class TechStad
    {
        private:
            ClasssType techno_stad;
            uint8_t disableCount;
        public:
            void Inc();
            void SecInc();

            void Disable()
            {
                disableCount = 0xFF;
                Clear();
            };
            void Enable()
            {
                disableCount = 0x00;
            };
            void Clear()
            {
                techno_stad = 0;
            };
            ClasssType Read()
            {
                return techno_stad;
            };
            TechStad()
            : techno_stad ( 0 ) 
            {;};
    };
    // Сильно подумать!!!
    // Написанное здесь полная хуйня планетарного масштаба...
    template<> inline void TechStad<uint8_t>::Inc()
    {
        if( !disableCount && ( techno_stad < 250 ) )
            techno_stad++;
    };
    template<> inline void TechStad<uint16_t>::Inc()
    {
        if( !disableCount && ( techno_stad < 65000 ) )
            techno_stad++;
    };
    template<> inline void TechStad<uint8_t>::SecInc()
    {
        if( !disableCount && ( techno_stad < 250 ) && !sec_tik )
            techno_stad++;
    };
    template<> inline void TechStad<uint16_t>::SecInc()
    {
        if( !disableCount && ( techno_stad < 65000 ) && !sec_tik )
            techno_stad++;
    };

    class TechObj
    {
        private:
            TechStad < uint16_t > t_stad;       // Раньше это было: uint16_t t_stad;
            TechStad < uint16_t > t_sub_st;     // Раньше это было: uint16_t t_sub_st;
        public:
            uint8_t stad;
            uint8_t sub_st;                     // Нужно подумать и убрать
            uint8_t cmd;
            uint16_t enh_info;

            const char *name;

            virtual void drv( ) = 0;
            virtual void show_lcd( ) = 0;            
            virtual void show_mnem( ) = 0;

            virtual void SetDeviceNetError( ) {};
            virtual void ClrDeviceNetError( ) {};

            uint16_t    read_t_stad( )      { return t_stad.Read(); };
            void        clear_t_stad( )     { t_stad.Clear();       };
            void        inc_t_stad( )       { t_stad.Inc();         };

            uint16_t    read_t_sub_st( )    { return t_sub_st.Read(); };
            void        clear_t_sub_st( )   { t_sub_st.Clear();       };
            void        inc_t_sub_st( )     { t_sub_st.Inc();         };

            void to_stad(uint8_t cur_stad, uint8_t cur_sub_st)
            {
                if( stad != cur_stad ) {
                    t_stad.Clear();
                    t_sub_st.Clear();
                    stad = cur_stad;
                    //sub_st = 0;
                }
                if( sub_st != cur_sub_st ) {
                    t_sub_st.Clear();
                    sub_st = cur_sub_st;
                }
            }

            TechObj()
            :
            stad     ( 0 ), 
            sub_st   ( 0 ),
            cmd      ( 0 ), 
            enh_info ( 0 ), 
            name     ( 0 )
            { };
            virtual ~TechObj() {};
    };
    
    class TechObjTemplate
    {
        private:
            static const unsigned char NET_NO = 0x00;
            static const unsigned char NET_YES = 0xFF;
            uint8_t NetStatus;
        public:
            virtual void show_mnem( ) = 0;
            void setNetError()   { NetStatus = NET_NO;  };
            void clearNetError() { NetStatus = NET_YES; };
            bool isNetOk()       
            {
                if( NetStatus )
                    return true;
                else
                    return false;
            };

            TechObjTemplate( )
            : NetStatus ( 0 )
            { };
            virtual ~TechObjTemplate() {};
    };

#endif
