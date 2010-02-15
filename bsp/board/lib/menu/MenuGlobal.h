#ifndef MENUGLOBAL
    #define MENUGLOBAL

    #include "MenuBaseClass.h"

    /*
        MenuGlobal - Класс глобального меню, т.е. без возможности перехода на уровень выше
    */

    namespace Menu {

        extern BaseClass * pNextMenu;
        extern BaseClass * pCurrentMenu;

        class GlobalItem : public BaseClass
        {
            private:
                uint8_t NumOfMenus;      //Количестве пунктов меню
                uint8_t curMenuPointer;  //Указатель текущего пункта в меню

                virtual void showMenuItems();       //Рисуем меню на экране ЖК
                virtual void checkPushButtons();    //Проверяем нажатия кнопок
            public:
                virtual void showMenu()
                {
                    showMenuItems();
                    checkPushButtons();
                };
                GlobalItem(BaseClass ** _forwardItem, int _NumOfMenus)
                : NumOfMenus ( _NumOfMenus )
                {
                    forwardItem = _forwardItem;
                };
                virtual ~GlobalItem() {};
        };

    } //namespace

#endif /* MENUGLOBAL */
