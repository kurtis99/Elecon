#ifndef POSXY
#define POSXY

#include <Global_define.h>

extern char LCD_str[];

class C_posXY {
    private:
        unsigned char posX;
        unsigned char posY;
    public:
        unsigned char getX() { return posX; };
        unsigned char getY() { return posY; };

        void initialize() { posX = 0; posY = 0; };

        unsigned char get()
        {
            if( MAX_LENGTH * posY )
                return posX + ( MAX_LENGTH * posY );
            else
                return posX;
        };
        void new_line()
        {
            posX = 0;
            posY = posY + 1;
            if( posY > ( MAX_ROWS - 1 ) )
                posY = posY - 1;
        };

        C_posXY& operator++ ()
        {
            //unsigned char index;
        
            posX = posX + 1;
            if( posX > ( MAX_LENGTH - 1 ) ) {
                posX = posX - 1;
                //for(index=0; index<MAX_LENGTH-1; index++)
                //    LCD_str[MAX_LENGTH * posY+index]=LCD_str[MAX_LENGTH * posY+index+1];
            }

            return *this;
        }
        C_posXY operator++ (int)
        {
            C_posXY ans = *this;
            ++( *this );          // or just call operator++()
            return ans;
        }

        C_posXY( )
        : posX ( 0 ), posY ( 0 )
        {};
};

#endif