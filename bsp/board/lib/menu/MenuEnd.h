#ifndef MENUEND
    #define MENUEND

    #include <MenuBaseClass.h>
/*#include <Etaz.h>*/

    /*
        квалификатор virtual на самом деле наследуется и тут он только для визуальности.
    */
    namespace Menu {

        class EndItem : public BaseClass
        {
            private:
                void (*ShowCurrenMenu)(void);

                virtual void showMenuItems();
                virtual void checkPushButtons();
            public:
                virtual void showMenu()
                {
                    if ( pNextMenu != pCurrentMenu) {
                        returnItem = pNextMenu;
                        pNextMenu  = pCurrentMenu;
                    }
                    showMenuItems();
                    checkPushButtons();
                };
                EndItem(void (*_ShowCurrenMenu)(void), const char * _MenuName)
                : ShowCurrenMenu ( _ShowCurrenMenu )
                {
                    MenuName = _MenuName;
                };
//                /* Перегружаем конструктор для приема указателя на метод в классе
//                Должно выглядет приблизительно так
//                int (XXX::*fp_3) (int);
//
//                */
//                EndItem(void (FireEtaz::*fp_3) (void), const char * _MenuName)
//                : ShowCurrenMenu ( fp_3 )
//                {
//                    MenuName = _MenuName;
//                };
                virtual ~EndItem() {};
        };
    }   //namespace Menu

#endif /* MENUEND */
