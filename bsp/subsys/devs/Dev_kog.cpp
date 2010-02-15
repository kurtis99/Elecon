#include "Dev_kog.h"

    uint8_t ThisIsTotalNull;
    uint8_t KOG::add_delay;

    void KOG::auto_open()
    {
        if ( openStad.Read() > START_DELAY + add_delay ) {
            if ( stad != KOG_ST_OPEN ) {
                cmd = KOG_C_OPEN;
                add_delay+=10;
            }
        } else {
            openStad.SecInc();
        }
    }

    void KOG::auto_close()
    {
        openStad.Clear();
    
        if( !( enh_info & ( KOG_OPER|KOG_DIST ) ) )
            if( stad != KOG_ST_CLOSE )
                cmd = KOG_C_CLOSE;
    }
    #if 1
    void KOG::check_press()
    {
        switch( stad)
        {
            case KOG_ST_OPEN:
                if ( checkPress ) 
                    t_wait_press_counter=t_wait_press;
            break;
            case KOG_ST_CLOSE:
                if ( !checkPress ) 
                    t_wait_press_counter=t_wait_press;
            break;
        }

        if(!sec_tik && t_wait_press_counter) 
            t_wait_press_counter--;

        if ( !t_wait_press_counter ) {
            enh_info |= KOG_PRESS_ERROR;
            devNetStatus |= NETDEV_PRESS_ERROR;
        } else {
            enh_info &= ~KOG_PRESS_ERROR;
            devNetStatus &= ~NETDEV_PRESS_ERROR;
        }
    }
    #endif
    #if 0
	void KOG::check_mp()
	{
		switch( stad )
		{
			case KOG_ST_OPEN:
				if( checkMP ) 
                    t_wait_mp_counter=t_wait_mp;
                break;
			case KOG_ST_CLOSE://включен- авария
                //if( checkMP )
				t_wait_mp_counter=t_wait_mp;
                break;
		}
        
		if( !sec_tik && t_wait_mp_counter ) 
            t_wait_mp_counter--;
		
        if( t_wait_mp_counter ) {
            enh_info &= ~KOG_MP_ERROR;
            devNetStatus &= ~NETDEV_MP_ERROR;
        } else {
            enh_info |= KOG_MP_ERROR;
            devNetStatus |= NETDEV_MP_ERROR;
        }
	}
    #endif
    void KOG::check_os()
    {
        if ( IO_Port.Os.Check() ) {
            enh_info &= ~KOG_OS_ERROR;
            devNetStatus &= ~NETDEV_OS_ERROR;
        } else {
            enh_info |= KOG_OS_ERROR;
            devNetStatus |= NETDEV_OS_ERROR;
        }
    }

    void KOG::drv()
    {
        uint8_t cur_status = 0;
    
        if(!sec_tik)
            inc_t_stad();

        if ( !(enh_info & KOG_END_DEVICE ) ) {
            if ( !( scafe_fl & SCAFE_FIRE ) ) {
                if ( devNetCmd & PSK_NETDEV ) {
                    cmd=KOG_C_OPEN;
                } else if ( devNetCmd & STP_NETDEV ) {
                    cmd=KOG_C_CLOSE;
                }
            }
        }

        switch(cmd)
        {
            case KOG_C_OPEN:
                if ( stad != KOG_ST_OPEN ) {
                    stad=KOG_ST_OPEN;
                    clear_t_stad();
                }
                if ( !(enh_info & KOG_END_DEVICE ) ) {
                    cur_status |= NETDEV_OP;
                    cur_status &=~NETDEV_CL;
                }
                break;
            case KOG_C_CLOSE:
                if(stad!=KOG_ST_CLOSE) {
                    stad=KOG_ST_CLOSE;
                    clear_t_stad();
                }
                if ( !(enh_info & KOG_END_DEVICE ) ) {
                    cur_status |= NETDEV_CL;
                    cur_status &=~NETDEV_OP;
                }
                break;
            default:
                break;
        }

        switch(stad)
        {
            case KOG_ST_OPEN:
                IO_Port.Out.Set();
                break;
            case KOG_ST_CLOSE:
                IO_Port.Out.Clear();
                break;
            default:
                IO_Port.Out.Clear();
        }

        devNetStatus = cur_status;

        if( enh_info & KOG_CHECK_PRESS )   check_press();
        if( enh_info & KOG_CHECK_OS )      check_os();
        //if( enh_info & KOG_CHECK_MP )      check_mp();
        
    }

    void KOG::show_mnem()
    {
        uint8_t lamp = 0;

        if ( stad == KOG_ST_OPEN ) {
            lamp = GREEN_LAMP;
        } else if ( stad == KOG_ST_CLOSE ) {
            lamp = NULL_LAMP;
        }

        //if( enh_info&( KOG_DIST|KOG_OPER ) )            lamp &= ~B_YELLOW_LAMP;
        if( enh_info & KOG_OS_ERROR )    lamp = B_RED_LAMP;
        if( enh_info & KOG_PRESS_ERROR ) lamp = B_YELLOW_LAMP;

        mnemoLamp = lamp;
    }

    void KOG::show_lcd()
    {
        if(!(enh_info&KOG_DIST))
        {
            if(KEY_4) enh_info &=~KOG_OPER;
            if(KEY_7) enh_info |= KOG_OPER;
            if(enh_info&KOG_OPER)
            {
                if(KEY_8)  cmd=KOG_C_OPEN;
                if(KEY_NO) cmd=KOG_C_CLOSE;
            }
        }
        
        LCD.init();
        LCD << name << ' ';
//        LCD_abc((char*)name,0);

        if(stad==KOG_ST_OPEN)   LCD << strTechStadInfo[0];
        if(stad==KOG_ST_CLOSE)  LCD << strTechStadInfo[1];
        LCD << read_t_stad() << ' ';

        //if(stad==KOG_ST_OPEN)   LCD_abc((char*)strTechStadInfo[0],6);
        //if(stad==KOG_ST_CLOSE)  LCD_abc((char*)strTechStadInfo[1],6);
        //LCD_uind(read_t_stad(),7,5);

        if(enh_info&KOG_DIST)       LCD << strTechMode[2];
        else if(enh_info&KOG_OPER)  LCD << strTechMode[1];
        else                        LCD << strTechMode[0];

        //if(enh_info&KOG_DIST)       LCD_abc((char*)strTechMode[2],12);
        //else if(enh_info&KOG_OPER)  LCD_abc((char*)strTechMode[1],12);
        //else                        LCD_abc((char*)strTechMode[0],12);

        LCD.newLine();

        if ( enh_info & ( KOG_PRESS_ERROR|KOG_MP_ERROR|KOG_KTR_ERROR|KOG_OS_ERROR ) ) 
        {
            LCD << strKogErrorMessages[0];
            scafe_fl |= SCAFE_ERROR;
        }
        if (enh_info&KOG_PRESS_ERROR)   LCD << strKogErrorMessages[1];
        //if (enh_info&KOG_MP_ERROR)      LCD << strKogErrorMessages[2];
        if (enh_info&KOG_OS_ERROR)      LCD << strKogErrorMessages[4];

        if(KEY_1)
            enh_info&=~(KOG_PRESS_ERROR|KOG_MP_ERROR|KOG_KTR_ERROR|KOG_OS_ERROR);
    }
