#ifndef MENUBASECLASS
    #define MENUBASECLASS

    /*
        Базовый класс
    */

    #include <LcdOutput.h>
    #include <avr/pgmspace.h>
    #include <Nls.h>

    namespace Menu {

        extern uint8_t KEY_cpy[];
        extern uint8_t KEY_wrk[];

        class BaseClass
        {
            public:
                uint8_t getListValue(uint8_t Value,uint8_t MaxValue);
                const char * MenuName;      //мя пункта меню
                BaseClass * returnItem;     //Указатель на меню возврата
                BaseClass ** forwardItem;   //Указатель на меню перехода

                virtual void showMenu() = 0;
                virtual void showMenuItems() = 0;
                virtual void checkPushButtons() = 0;

                BaseClass()
                : returnItem (0), forwardItem (0)
                {};
                virtual ~BaseClass() {};
        };
    } //namespace

#endif /* MENUBASECLASS */