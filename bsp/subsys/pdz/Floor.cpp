// ====================================================================
// 
//       Filename:  Floor.cpp
// 
//    Description:  Реализация функций класса Floor
// 
//        Version:  1.0
//        Created:  30.11.2009 17:40:59
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Mikhail Boiko (mb), kurtis99@bigmir.net
//        Company:  НТТОВ "Элекон
// 
// ====================================================================

#include	<Floor.h>

void Floor::driver()
{


}

void Floor::set_event(eSBSQ state) {
    uint8_t store_temp_value;

    switch (state) {
        case SBSQNormal:
            store_temp_value = NULL_LAMP;
            break;

        case OpenPKDoor:
            store_temp_value = YELLOW_LAMP;
            break;

        case StartNasosFromPK:
            store_temp_value = RED_LAMP;
            break;

        case FireFromPK:
            store_temp_value = B_RED_LAMP;
            break;

        default:
            store_temp_value = NULL_LAMP;
            break;
    }				// -----  end switch  -----

    mSBSQ = store_temp_value;
    
    if (fire_info != NoFire) {
        fireMnemoWork();
    }
};

void Floor::set_event(eBUPK state) {
    uint8_t store_temp_value;

    switch (state) {
        case PkNormal:
            store_temp_value = NULL_LAMP;
            break;

        case PkNoPower:
            store_temp_value = B_YELLOW_LAMP;
            break;

        case PkIsOpen:
            store_temp_value = RED_LAMP;
            break;

        default:
            store_temp_value = NULL_LAMP;
            break;
    }				// -----  end switch  -----
    
    mBUPK = store_temp_value;
    
    if (fire_info != NoFire) {
        fireMnemoWork();
    }
};

void Floor::set_event(eSPS state) {
    uint8_t store_temp_value;

    switch (state) {
        case SpsNormal:	
            store_temp_value = NULL_LAMP;
            break;

        case FireFromSPS:	
            store_temp_value = B_RED_LAMP;
            break;

        default:	
            store_temp_value = NULL_LAMP;
            break;
    }				// -----  end switch  -----

    mSPS = store_temp_value;

    if (fire_info != NoFire) {
        fireMnemoWork();
    }
};

void Floor::set_event(eYA state, eYANo number) {
    uint8_t store_temp_value;

    switch (state) {
        case Closed:	
            store_temp_value = NULL_LAMP;
            break;

        case Opened:	
            store_temp_value = GREEN_LAMP;
            break;

        case Error:	
            store_temp_value = B_YELLOW_LAMP;
            break;

        default:	
            store_temp_value = NULL_LAMP;
            break;
    }				// -----  end switch  -----

    switch (number) {
        case YA1:
            mYA1 = store_temp_value;
            break;

        case YA2:
            mYA2 = store_temp_value;
            break;

        default:
            break;
    }
};

void Floor::screen_off()
{
    mYA1  = NULL_LAMP;
    mYA2  = NULL_LAMP;
    mSPS  = NULL_LAMP;
    mSBSQ = NULL_LAMP;
    mBUPK = NULL_LAMP;
}

void Floor::set_fire(eFireSource fire_source)
{

    // установка глобального флага пожар для всей системы ПДЗ
    if (FireSrc == NoFire)
        FireSrc = fire_source;
    else
        return; // Если состояние отличное от нормального (нет пожара), 
                // то выходим, поскольку пожар может быть только один.
       
    // Установка пожара для текущего этажа
    fire_info = fire_source;

    fireMnemoWork();
}

void Floor::fireMnemoWork()
{
    switch (fire_info) {
        case FromSPS:
            mSPS = B_RED_LAMP;
            break;

        case FromPK:
            mSBSQ = B_RED_LAMP;
            break;

        case FromMenu:
            mSPS = RED_LAMP;
            break;

        case NoFire:
            mSPS = NULL_LAMP;
            break;

        case StopPDZ:
            mSPS = YELLOW_LAMP;
            mSBSQ = YELLOW_LAMP;
            mBUPK = YELLOW_LAMP;
            break;

        default:
            break;
    }
}

bool Floor::have_fire()
{
    if (fire_info == FromSPS) {
        return true;
    } else if (fire_info == FromPK) {
        return true;
    } else if (fire_info == FromMenu) {
        return true;
    } else {
        return false;
    }
}

void Floor::show_lcd(uint8_t cur_floor)
{
    LCD << etaz_str << cur_floor << ' ';

    switch (fire_info) {
        case FromSPS:
        case FromPK:	
        case FromMenu:	
            LCD << fireSTR;
            break;

        default:
            LCD << norma_str;	
            break;
    }				// -----  end switch  -----
}

void Floor::doStopPdz()
{
    fire_info = NoFire;
    screen_off();
}

