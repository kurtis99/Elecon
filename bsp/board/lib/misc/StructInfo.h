#ifndef __STRUCTINFO_H
    #define __STRUCTINFO_H

    /* Класс создан для управления статусами */
    template <typename ClasssType> 
    class StatusI
    {
        private:
            ClasssType status;
        public:
            void Null() { 
                status = 0; 
            };
            void Clear( ClasssType _ClrFld ) { 
                status &= ~_ClrFld; 
            };
            void Set( ClasssType _SetFld ) { 
                status |=  _SetFld; 
            };
            bool Check( ClasssType _CheckStat ) 
            { 
                return ( status & _CheckStat) ? true : false;
            };
            ClasssType Get() 
            { 
                return status; 
            };
            StatusI() : status ( 0 )
            {};
    };
    
#endif /* __STRUCTINFO_H */