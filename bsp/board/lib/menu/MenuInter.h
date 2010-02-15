#ifndef MENUFULLLIST
    #define MENUFULLLIST

    #include "MenuBaseClass.h"
    /*
        MenuFullList - Класс который имеет подменю и возможность перехода на уровень выше
    */

    namespace Menu {

        extern BaseClass * pNextMenu;
        extern BaseClass * pCurrentMenu;

        class InterItem : public BaseClass
        {
            private:
                int NumOfMenus;
                uint8_t curMenuPointer;  //Указатель текущего пункта в меню

                virtual void showMenuItems();       //Рисуем меню на экране ЖК
                virtual void checkPushButtons();    //Проверяем нажатия кнопок
            public:
                virtual void showMenu()
                {
                    if ( pNextMenu != pCurrentMenu ) {
                        returnItem = pNextMenu;
                        pNextMenu  = pCurrentMenu;
                    }
                    showMenuItems();
                    checkPushButtons();
                };
                InterItem ( BaseClass ** _forwardItem, int _NumOfMenus, const char * _MenuName )
                : NumOfMenus ( _NumOfMenus )
                {
                    forwardItem = _forwardItem;
                    MenuName    = _MenuName;
                };
                virtual ~InterItem() {};
        };
    }

#endif /* MENUFULLLIST */
