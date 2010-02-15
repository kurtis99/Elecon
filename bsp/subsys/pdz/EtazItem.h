// ====================================================================
//
//       Filename:  EtazItem.h
//
//    Description:  Описание базового класса для обработки состояния 
//                  БФПП
//
//        Version:  1.0
//        Created:  27.11.2009 15:55:19
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Mikhail Boiko (mb), kurtis99@bigmir.net
//        Company:  НТТОВ "Элекон
//
// ====================================================================

#ifndef  ETAZITEM_INC
#define  ETAZITEM_INC

#include	<TechObj.h>
#include	<struct_define.h>
#include    <Global_define.h>

class NetTransferConstrol; 

enum {
    ERROR_220V    = 1 << 0,
    NETWORK_ERROR = 1 << 1,
    ADDRESS_ERROR = 1 << 2,
    DIST_ERROR    = 1 << 3,
    KZ_ERROR      = 1 << 4,

/* максимальное значение (1 << 7), если нужно больше, то необходимо 
 * проверить тип статусной переменной в классе */
};

//        Class:  EtazItem
//  Description:  Уточняющий класс для обработки устройств бфпп.
//                Если напрямую наследовать класс TechObj, то мы не 
//                сможем унифицировать работу с БФПП разного типа, а 
//                так вводится промежуточный класс, который позволяет 
//                сделать некоторые уточнения и ввести требуемые 
//                функции, оставив за собой функционал класса TechObj.
// ====================================================================
class EtazItem : public TechObj
{
    public:
        EtazItem ()
        {
           number_of_created_devices++;
        };                             // constructor
        virtual ~EtazItem() {;};       
 
        /*Эти функции принадлежат классу TechObj*/
        virtual void drv() = 0;
        virtual void show_lcd() = 0;
        virtual void show_menu(uint8_t cur_floor) = 0;
        virtual void show_mnem() = 0;

        virtual void SetDeviceNetError() = 0;
        virtual void ClrDeviceNetError() = 0;

        virtual void doStopPdz() = 0;

        /*        virtual void CheckFireFloor() = 0;*/
        virtual uint8_t EtazDrv() = 0;

		virtual uint8_t return_lo_enh() = 0;
		virtual uint8_t return_hi_enh() = 0;

        virtual uint8_t getErrorPacket() = 0;
        virtual uint8_t getSendAddress() = 0;

        // увеличивает значение переменной CurrentFloor
        virtual uint8_t num_of_floors() = 0;
        /*        virtual void increment() = 0;*/
        virtual void CheckBfpp() = 0;

        virtual uint8_t set_fire(eFireSource state) = 0;
        /*        virtual void BfppStopPdz() = 0;*/
        virtual void set_next_fire_floor(BfppFloorCounter & floor_count) = 0;

        // Общее количество созданных устройств.
        static uint8_t number_of_created_devices;
        // текущий этаж в нормальной (человеческом формате)        
        static uint8_t CurrentFloor;
        // текущий этаж в формате понятном для программы
        static BfppFloorCounter CurrentBfppFloor; 
    private:
        // -- == Пусто == --
}; // -----  end of class EtazItem  -----

#endif   // ----- #ifndef ETAZITEM_INC  -----

