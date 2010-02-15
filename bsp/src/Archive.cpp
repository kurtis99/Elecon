#include "Archive.h"
#include "exit_codes.h"

void print_eeprom_debug(i2c_errors error_code)
{
    switch (error_code)
    {
        case I2C_OK:
            LCD << str_I2C_OK;
            break;
        case ERROR_START:
            LCD << str_ERROR_START;
            break;
        case ERROR_ADDRESS:
            LCD << str_ERROR_ADDRESS;
            break;
        case ERROR_DATA:
            LCD << str_ERROR_DATA;
            break;
        case ERROR_RESTART:
            LCD << str_ERROR_RESTART;
            break;
        case ERROR_RECEIVE:
            LCD << str_ERROR_RECEIVE;
            break;
        case ERROR:
            LCD << str_ERROR;
            break;
        case ERROR_PCF8583_RAM_CHECKSUM_FAIL:
            LCD << str_ERROR_PCF8583_RAM_CHECKSUM_FAIL;
            break;
        case ERROR_PCF8583_RAM_OK_CONST:
            LCD << str_ERROR_PCF8583_RAM_OK_CONST;
            break;
        default:
            LCD << str_DONT_KNOW_THIS_ERROR;
            break;
    }
}

uint8_t get_percentage(const uint16_t current_value,
                       const uint16_t full_value)
{
    uint8_t return_value = 0;

    return_value = (current_value * 100UL) / full_value;

    return return_value;
}

void erase_eeprom_menu()
{
    Archive.MenuEraseEEPROM();
}

void WorkWithEEPROM::MenuEraseEEPROM(void)
{
    static i2c_errors this_i2c_error = I2C_OK;
    static uint16_t erase_block = 0;

    LCD.init();

    if (KEY_NO) {
        eeprom_erase_message_was_writen = false;
        eeprom_was_erased = false;
    }

    LCD << strErasingEEPROM << ' ';
    LCD << get_percentage(erase_block, EEPROM.get_max_eeprom_address()) << '%';
    LCD.newLine();

    if (!eeprom_was_erased) {
        this_i2c_error = EraseBlock(erase_block);
        tech_fl |= IIC_BUSY;
        if (this_i2c_error == AT24CXX_WAS_ERASED)
            eeprom_was_erased = true;
    }
    if (eeprom_was_erased) {
        LCD << strEraseSuccess;
        /* Пишем сообщение что память была очищена */
        if (!eeprom_erase_message_was_writen) {
            arch_buffer.flush();
            arch_buffer.push(DeviceError(EEPROM_ERASED, 0x0));
            message_index = 0x510;
            eeprom_erase_message_was_writen = true;
        }
    }
    else {
        print_eeprom_debug(this_i2c_error);
    }
}
/* Текущее системное время */
extern SysTime Time;

i2c_errors WorkWithEEPROM::EraseBlock(uint16_t & erase_block)
{
    uint8_t temp_array[8]; /* пишем в память блоками по 8 байт (хз почему)*/
    i2c_errors return_value = I2C_OK;

    /* заполняем массив какими-то значениями */
    for (uint8_t i=0; i<SIZE_OF(temp_array); i++) {
        temp_array[i] = 0xFF;
    }

    return_value = EEPROM.page_write(erase_block,
                                     temp_array,
                                     SIZE_OF(temp_array));
    erase_block += SIZE_OF(temp_array);
    /* если записали уже ВСЮ память */
    if (erase_block > EEPROM.get_max_eeprom_address()) {
        erase_block = 0;
        return_value = AT24CXX_WAS_ERASED;
    }

    return return_value;
}

/* TODO: Может не работать */
void WorkWithEEPROM::WriteSet(const uint16_t addr, const uint16_t value)
{
    EEPROM.word_write(addr, value);
}

uint16_t WorkWithEEPROM::ReadSet(const uint16_t addr, uint16_t & value)
{
    EEPROM.word_read(addr, value);

    return value;
}

/* Вызывается в конструкторе */
void WorkWithEEPROM::init()
{
    uint8_t temp_val;

    tech_fl &= ~DEFAULT_SET;

    /* Определяем наличие микросхемы на линии, если она не отвечает по каким-то
     * причинам, то считаем что она отсутствует.
     * Например: может быть задано использование микросхемы в панельке, но она
     * физически будет отсутствовать (протупили с адрессом). */
    if (!EEPROM.is_present()) {
        tech_fl |= NO_IIC;
        return; /* Микросхемы нет? Тогда нахуй с пляжа! */
    }

    /* Нужно ли менять уставки на заводские? Если мы хотим изменить уставки на
     * заводские, то в меню устанавливаем значение в EEPROM по адрессу 0x10, и
     * здесь (при старте) мы его вычитываем и анализируем. */
    EEPROM.byte_read(0x10, temp_val);
    sys_set_flag = (int16_t)temp_val;

    /* Уставки таки нужно менять на заводские */
    if (sys_set_flag)
        tech_fl |= DEFAULT_SET;

    /* Если нужно сбросить уставки на заводские, то пишем по адрессу 0x10
     * нулевое значение для избежания несанкционированной перезаписи уставок во
     * время следующего перезапуска контроллера */
    if (tech_fl & DEFAULT_SET) {
        EEPROM.byte_write(0x10, 0x0);
        sys_set_flag = 0;
        sys_set_flag_copy = 0;
    }

    /* Индекс на последнее записанное в EERPOM сообщение */
    EEPROM.word_read(0x500, message_index);

    /* если прочитанное значение не лежит в пространстве адрессов EEPROM */
    if (message_index < 0x510 || message_index > 0x1FF0) {
        message_index = 0x510;
        EEPROM.word_write(0x500, message_index);
    }

    message_index_old = message_index;
}

void WorkWithEEPROM::show_lcd_set_reset()
{
    getpm_dig(&sys_set_flag,0,0,1);
    LCD_abc((char*)sys_set_restart_str,0);
    LCD_uind(sys_set_flag,16,1);

    if (!(tech_fl & IIC_BUSY)) {
        if (sys_set_flag != sys_set_flag_copy) {
            tech_fl |= IIC_BUSY;
            //EEPROM.write_byte(sys_set_flag, 0x10);
            EEPROM.byte_write(0x10, (uint8_t) sys_set_flag);
            sys_set_flag_copy = sys_set_flag;
        }
    }
}

void Message_drv()
{
    Archive.drv();
}

void WorkWithEEPROM::drv()
{
    /* Шина занята */
    if (tech_fl & IIC_BUSY)
        return;

    if (message_index != message_index_old) {
        tech_fl |= IIC_BUSY;
        /* Если запись прошла без ошибок (еще не гарантия записи) */
        if (I2C_OK == EEPROM.word_write(0x500, message_index)) {
            message_index_old = message_index;
        } else
            return;
    }

    /* Отсутствуют элементы в кольцевом буфере */
    if (0 == arch_buffer.get_count())
        return;

    if (tech_fl & IIC_BUSY)
        return;
    else
        tech_fl |= IIC_BUSY;

    write_message();
    next_write_address();
}

SysTime time_message;

void WorkWithEEPROM::write_message()
{
    /* Текущее время, которое будет записанно в архив */
    current_message.archive_time = Time;

    /* Код ошибки */
    current_message.msg_code = arch_buffer.pop();

    /*TODO: тут нужно написать запись имени устройства в журнал */
    if (current_message.msg_code.device_index < 0x20) {
        //void * memcpy ( void * destination, const void * source, size_t num );
        //memcpy(current_message.error_dev_name,
               //)
               ;
    } else if (current_message.msg_code.device_index == SYSTEM_MSG) {
        //char * strcpy ( char * destination, const char * source );
        strcpy(current_message.error_dev_name, message_str[0]);
    }

    EEPROM.page_write(message_index, (uint8_t *)&current_message, 0x10);
}

void WorkWithEEPROM::read_message()
{
    EEPROM.page_read(message_menu_index, (uint8_t *)&last_read_message, 0x10);
}

void WorkWithEEPROM::next_write_address()
{
    message_index += 0x10;
    if (message_index>0x1ff0)
        message_index=0x0510;
    if (message_index<0x0510)
        message_index=0x0510;
}

void show_message()
{
    Archive.show_lcd();
}

void WorkWithEEPROM::show_lcd()
{
    if (tech_fl & NO_IIC) {
        LCD_abc((char*)no_iic_str,0);
        return;
    }

    if (!(tech_fl & IIC_BUSY)) {
        if (KEY_5) {
            tech_fl|=IIC_BUSY;

            if (message_menu_index < 0x1ff0)
                message_menu_index += 0x10;
            else
                message_menu_index = 0x0510;

            read_message();
        }
        if (KEY_2) {
            tech_fl|=IIC_BUSY;

            if (message_menu_index > 0x0510)
                message_menu_index -= 0x10;
            else
                message_menu_index = 0x1ff0;

            read_message();
        }
    }

    /* Если поступило новое сообщение */
    if (!(tech_fl & IIC_BUSY)) {
        if(message_menu_index_old != message_index-0x10) {
            tech_fl|=IIC_BUSY;
            message_menu_index=message_index-0x10;
            message_menu_index_old=message_index-0x10;
            read_message();
        }
    }

    LCD_uind(last_read_message.archive_time.hour, 0, 2|LEAD_ZERO);
    LCD_putc(':',2);
    LCD_uind(last_read_message.archive_time.min, 3, 2|LEAD_ZERO);
    LCD_uind(last_read_message.archive_time.day, 6, 2|LEAD_ZERO);
    LCD_putc('.',8);
    LCD_uind(last_read_message.archive_time.month, 9, 2|LEAD_ZERO);
    /* если вышли за границы журнала */
    if (last_read_message.msg_code.device_index == 0xff &&
        last_read_message.msg_code.error_code == 0xff) {
        LCD_abc(no_arch_str,20);
    } else {
        LCD_uind16(last_read_message.msg_code.device_index,20, 2|LEAD_ZERO);
        LCD_putc(':', 22);
        LCD_uind16(last_read_message.msg_code.error_code,23,2|LEAD_ZERO);
    }
    LCD_ind((((int16_t)(message_menu_index-0x500)-0x10)/0x10)+1, 12, 4|LEAD_ZERO);
}
