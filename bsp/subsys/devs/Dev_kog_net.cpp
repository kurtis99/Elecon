#include "Dev_kog_net.h"

    void KOG_NET::auto_open()
    {
        if ( !( net_stat&NETDEV_OP ) ) net_cmd|=PSK_NETDEV;
    }
    void KOG_NET::auto_close()
    {
        if(!(net_stat&NETDEV_CL)) net_cmd|=STP_NETDEV;
    }

    void KOG_NET::drv()
    {
        if ( !( net_stat&NETDEV_NETERROR ) ) {
            if(!(net_stat&(NETDEV_PRESS_ERROR|NETDEV_MP_ERROR|NETDEV_OS_ERROR)))
                net_cmd&=~RESET_NETDEV;
            if(net_stat&NETDEV_OP) net_cmd&=~PSK_NETDEV;
            if(net_stat&NETDEV_CL) net_cmd&=~STP_NETDEV;
        } else {
            net_cmd&=~RESET_NETDEV;
            net_cmd&=~PSK_NETDEV;
            net_cmd&=~STP_NETDEV;
        }
    }

    void KOG_NET::show_mnem()
    {
        uint8_t lamp = NULL_LAMP;
    
        if(net_stat&NETDEV_OP)
            lamp = GREEN_LAMP;
        if(net_stat&NETDEV_CL)
            lamp = NULL_LAMP;

//        if(net_stat&NETDEV_OPER)        lamp &=~B_YELLOW_LAMP;

        if(net_stat&NETDEV_OS_ERROR) lamp = B_RED_LAMP;
        if(net_stat&(NETDEV_PRESS_ERROR|NETDEV_MP_ERROR))
            lamp = B_YELLOW_LAMP;

        if(net_stat&NETDEV_NETERROR)
            lamp = NULL_LAMP;
            
        mn_os = lamp;
    }

    void KOG_NET::show_lcd()
    {
        LCD_abc((char*)name,0);

        if( !(net_stat&NETDEV_NETERROR ) ) {
            if(net_stat&NETDEV_OP) 	LCD_abc((char*)strTechStadInfo[0],6);
            if(net_stat&NETDEV_CL) 	LCD_abc((char*)strTechStadInfo[1],6);

            if(net_cmd&PSK_NETDEV) 	LCD_abc((char*)strTechStadInfo[0],4);
            if(net_cmd&STP_NETDEV) 	LCD_abc((char*)strTechStadInfo[1],4);

            if(net_stat&NETDEV_OPER)    LCD_abc((char*)strTechMode[1],12);
            else                        LCD_abc((char*)strTechMode[0],12);

            if(net_stat&(NETDEV_PRESS_ERROR | 
                         NETDEV_MP_ERROR | 
                         NETDEV_OS_ERROR ) )
                                            LCD_abc((char*)strKogErrorMessages[0],20);
            if(net_stat&NETDEV_PRESS_ERROR) LCD_abc((char*)strKogErrorMessages[1],23);
            if(net_stat&NETDEV_MP_ERROR)    LCD_abc((char*)strKogErrorMessages[2],26);
            if(net_stat&NETDEV_OS_ERROR)    LCD_abc((char*)strKogErrorMessages[4],29);

            if ( KEY_1 ) 
                net_cmd|=RESET_NETDEV;
            if ( KEY_8 )  
                if ( !( net_stat&NETDEV_OP ) ) {
                    net_cmd|=PSK_NETDEV; 
                    enh_info|=KOG_HAND;
                }
            if ( KEY_NO )
                if ( !( net_stat&NETDEV_CL ) ) {
                    net_cmd|=STP_NETDEV; 
                    enh_info&=~KOG_HAND;
                }
        } else {
            LCD_abc((char*)strOutOfNetError,20);
        }
    }