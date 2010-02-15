#ifndef SUBSYS_DEVS_VZK_CPP
#define SUBSYS_DEVS_VZK_CPP

// Старт устройства
template < uint8_t NumOfClapans >
void dVZK <NumOfClapans>::auto_open()
{
    if (stad!=VZK_ST_OPEN)
        cmd = VZK_C_OPEN;
}

// Останов устройства
template < uint8_t NumOfClapans >
void dVZK <NumOfClapans>::auto_close()
{
    if (!(enh_info & (VZK_OPER|VZK_DIST)))
        if (stad != VZK_ST_CLOSE)
            cmd = VZK_C_CLOSE;
}

// Проверка наиличия напряжения на исполнительном устройстве
template < uint8_t NumOfClapans >
void dVZK <NumOfClapans>::check_os()
{
    OPort.Os.Check() ? enh_info &= ~VZK_OS_ERROR : enh_info |= VZK_OS_ERROR;
}

// Логика работы с устройством
template < uint8_t NumOfClapans >
void dVZK <NumOfClapans>::drv()
{
    if (!sec_tik)
        inc_t_stad();

    switch (cmd) {
        case VZK_C_OPEN:
            if (stad != VZK_ST_OPEN) {
                stad=VZK_ST_OPEN;
                clear_t_stad();
            }
            break;
        case VZK_C_CLOSE:
            if (stad != VZK_ST_CLOSE) {
                stad=VZK_ST_CLOSE;
                clear_t_stad();
            }
            break;
        default:
            break;
    }

    switch (stad) {
        case VZK_ST_OPEN:
            OPort.Out.Set();
            break;
        case VZK_ST_CLOSE:
            OPort.Out.Clear();
            break;
        default:
            break;
    }

    if (enh_info & VZK_CHECK_OS)
        check_os();
}

// Отображения текущего состояния устройства на мнемосхеме
template < uint8_t NumOfClapans >
void dVZK <NumOfClapans>::show_mnem()
{
    for (index=0; index < NumOfClapans; index++) {
        // Проверка положения клапана (открыт/закрыт)
        *mnemoLamps[index] = *kControl[index] ? RED_LAMP : NULL_LAMP;

        if (enh_info & VZK_OS_ERROR)
            *mnemoLamps[index] = B_RED_LAMP;

        if (!(enh_info & VZK_END_DEVICE))
            netSendLamp[index] = *mnemoLamps[index];
    }
}

// Информационное табло на ЖКИ
template < uint8_t NumOfClapans >
void dVZK <NumOfClapans>::show_lcd()
{
    if (!(enh_info & VZK_DIST)) {
        if (KEY_4) enh_info &=~VZK_OPER;
        if (KEY_7) enh_info |= VZK_OPER;
        if (enh_info & VZK_OPER) {
            if (KEY_8)  cmd=VZK_C_CLOSE;
            if (KEY_NO) cmd=VZK_C_OPEN;
        }
    }

    LCD.init();
    LCD << name << ' ';

    if (stad == VZK_ST_OPEN)  LCD << strTechStadInfo[0];
    if (stad == VZK_ST_CLOSE) LCD << strTechStadInfo[1];
    LCD << ' ' << read_t_stad();

    if (enh_info & VZK_DIST)      LCD << strTechMode[2];
    else if (enh_info & VZK_OPER) LCD << strTechMode[1];
    else                          LCD << strTechMode[0];

    LCD.newLine();

    if (enh_info & VZK_OS_ERROR)  LCD << dev_error << ' ';
    if (enh_info & VZK_OS_ERROR)  LCD << dev_error_os << ' ';

    //if (KEY_1) enh_info &= ~VZK_OS_ERROR;
}

#endif /* SUBSYS_DEVS_VZK_CPP */

