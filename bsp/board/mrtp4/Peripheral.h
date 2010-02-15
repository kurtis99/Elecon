#ifndef __PERIPHERAL_H
    #define __PERIPHERAL_H

    #include <Nls.h>
    #include <Main.h>

    #define CS0 0
    #define CS1 1
    #define CS2 2
    #define CS3 3
    #define CS4 4
    #define CS5 5

    #define CDC3 128//PORTD.7
    #define CDC2 64//PORTD.6
    #define CDC1 32//PORTD.5
    #define CDC0 16//PORTD.4

    //extern void outconv();
    extern void drv_Led();
    extern void LCD_init();
    extern void drv_LCD(char*);

    extern uint8_t KEY[2];// 1 - кнопка не нажата, 0 - кнопка нажата
    extern uint8_t MT[2];
    extern uint8_t MSK[8];
    extern uint8_t OS_MT[2];

    namespace nMSK {

    uint8_t CurMskSelector;

    class AskingMSK
    {
        public:
            INLINE inline AskingMSK(uint8_t _data, uint8_t & _pArray, uint8_t * _pFilter)
            : pMSK_array ( _pArray )
            {
                DataFromPort    = _data;
                pMSK_FilterTemp = _pFilter;
                MSK_in();
            }
            INLINE inline ~AskingMSK()
            {
                MSK_out();
            }

        private:
            uint8_t & pMSK_array;           // Указатель на байт массива МСК, с которым мы в данный момент работаем
            uint8_t DataFromPort;           // Данные считанные с порта
            uint8_t * pMSK_FilterTemp;      // Указатель на массив фильтрации дребезга сухих контактов
            static const unsigned char MskFiltTime = 10;    // Время фильтрации МСК
            //-----------------------------------------------------

    INLINE inline void MSK_in() // volatile
    {
        uint8_t j; //Просто индексная переменная, не несет глубокого смысла, используется для пробега по циклу, и ввиду того что она не несет абсолютно никакого глубокого смысла, этот коментарий можно было даже не читать!!!

        for ( j = 0 ; j < 8 ; j++ )
        {
            if ( DataFromPort & ( 1 << j ) ) /* МСК нажат */
            {
                if ( !( pMSK_array & ( 1 << j ) ) )
                {                                       //если в мск бит установлен нич не делаем
                    pMSK_FilterTemp[ j ]=0;
                }
                else
                {                                       //бит сброшен сщитаем и устанавливаем
                    pMSK_FilterTemp[ j ]++;
                    if ( pMSK_FilterTemp[ j ] > MskFiltTime )
                    {
                        pMSK_array &=~( 0x01 << j );    //установить МСК
                        pMSK_FilterTemp[ j ] = 0;       //очистить фильтр
                    }
                }
            }
            else
            {        /* МСК не нажат */
                if ( !( pMSK_array & ( 1 << j ) ) )
                {                                       //если установлен - сщит и сбрас
                    pMSK_FilterTemp[ j ]++;
                    if ( pMSK_FilterTemp[ j ] > MskFiltTime )
                    {
                        pMSK_array |= ( 0x01 << j );    //отпустить МСК
                        pMSK_FilterTemp[ j ] = 0;       //очистить фильтр
                    }
                }
                else
                {    /* Отфильтрованая кнопка не была нажата */
                    pMSK_FilterTemp[ j ] = 0;
                }
            }
        } /* for ( j = 0 ; j < 8 ; j++ )  */

    }/* INLINE inline void MSK_in() */
            //-----------------------------------------------------
            INLINE inline void MSK_out()
            {
                CurMskSelector > 6 ? CurMskSelector = 0 : CurMskSelector++;
            }
            //-----------------------------------------------------
    };

    } // namespace nMSK

#endif

