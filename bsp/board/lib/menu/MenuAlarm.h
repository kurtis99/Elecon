#ifndef MENUALARM
    #define MENUALARM

    #include "MenuBaseClass.h"

    /*
        квалификатор virtual на самом деле наследуется и тут он только для визуальности.
    */
    namespace Menu {

        class AlarmItem : public BaseClass
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
                AlarmItem(void (*_ShowCurrenMenu)(void), const char * _MenuName)
                : ShowCurrenMenu ( _ShowCurrenMenu )
                {
                    MenuName = _MenuName;
                };
                virtual ~AlarmItem() {};
        };
    }   //namespace Menu

#endif /* MENUALARM */