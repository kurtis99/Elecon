#ifndef LCD_H
#define LCD_H

#include <Main.h>
#include <StructInfo.h>
#include <posXY.h>

    extern const uint8_t LCD_digits111[] PROGMEM;

    class C_Lcd;

    class ILcdManipulator
    {
        public:
            virtual ~ILcdManipulator() {};
            virtual C_Lcd & operator << ( C_Lcd & out ) const = 0;
    };

    struct SetflagsStruct
    {
        unsigned char BitMask;
    };
    struct ClearflagsStruct
    {
        unsigned char BitMask;
    };
    struct SetBaseStruct
    {
        unsigned char Base;
    };

    inline
    SetflagsStruct SetF(uint8_t mask)
    {
        SetflagsStruct MisterX;
        MisterX.BitMask = mask;
        return MisterX;
    }
    inline
    ClearflagsStruct ClrF(uint8_t mask)
    {
        ClearflagsStruct MisterX;
        MisterX.BitMask = mask;
        return MisterX;
    }
    inline
    SetBaseStruct SetB(uint8_t mask)
    {
        SetBaseStruct MisterX;
        MisterX.Base = mask;
        return MisterX;
    }

    //const unsigned char HEX_OUTPUT = 0x01; // 1 - Hex / 0 - Dec
    const unsigned char ALIGN_RIGHT = 0x02; // 1 - Right, 0 - Left
    //const unsigned char SPACE_FILL = 0x04; // 1 - On / 0 - Off

    class C_Lcd
    {
        private:
            C_posXY posXY;

            static const unsigned char MAX_DIGS = 5;  // Наибольшее количестов цифр (32768)
            static const unsigned char MAX_LENGTH = 20; // Количество символов в строке
            static const unsigned char MAX_ROWS   = 2;  // Количество строк на экране

            static const unsigned char MAX_WORD_DIGS123 = 5;

            //unsigned char OutBase; // Система счисления (10-я или 16-я) ???
            //unsigned char LcdOutCtrl;  // Упавление параметрами вывода на ЖК
            unsigned char PositionX;   //Текущая позиция курсора по горизонтали [0..16(20)]
            unsigned char itoa(unsigned int uiVal, char* pBuff);

            StatusI <uint8_t> OutBase;
            StatusI <uint8_t> LcdCtrl;

            void IncPosotionX()
            {
                PositionX++;
                if( PositionX > 39 )
                    PositionX = 0;
            };
            void SetBase( SetBaseStruct myBase )
            {
                // Сделать проверку на корректность ввода информации
                if( ( myBase.Base != 10 ) || ( myBase.Base != 16 ) )
                    myBase.Base = 10;
                OutBase.Set(myBase.Base);
            };

        public:
            void ZeroPositionX() { PositionX = 0; };
            void newLine() { posXY.new_line(); };
            void init() {
                posXY.initialize();
                LcdCtrl.Null();
                OutBase.Null();
            };
            void set_flag(uint8_t _flag) { LcdCtrl.Set(_flag); };

            C_Lcd& operator << ( const char * );      /// Showing strings from RAM
            C_Lcd& operator << ( uint16_t );          /// Showing unsigned integers
            C_Lcd& operator << ( int16_t  );          /// Showing signed integers
            C_Lcd& operator << ( char     );          /// Prints signle char
            C_Lcd& operator << ( FloatNumber _fNum ); /// Float point number output
            C_Lcd& operator << ( const ILcdManipulator& HitroZopoManipulator )
            {
                return HitroZopoManipulator.operator << (*this);
            };
            C_Lcd& operator << ( SetflagsStruct Mymmmmm )
            {
                LcdCtrl.Set(Mymmmmm.BitMask);
                return * this;
            };
            C_Lcd& operator << ( ClearflagsStruct Mymmmmm )
            {
                LcdCtrl.Clear(Mymmmmm.BitMask);
                return * this;
            };
            C_Lcd& operator << ( SetBaseStruct Mymmmmm )
            {
                SetBase(Mymmmmm);
                return * this;
            };

            void LcdScreenInitialization();
            void LcdNewLine();

            C_Lcd ( void ) {
                // Periphs::UART0.Init();
            }
    };

    class InitScr : public ILcdManipulator
    {
        public:
            virtual C_Lcd & operator << (C_Lcd& out) const
            {
                out.LcdScreenInitialization();
                return out;
            };
    };
    class NewLine : public ILcdManipulator
    {
        public:
            virtual C_Lcd & operator << (C_Lcd& out) const
            {
                out.LcdNewLine();
                return out;
            };
    };

#endif
