#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <Main.h>
#include <at24c64.h>
//#include <i2c_eeprom.h>

class WorkWithEEPROM
{
    private:
        /* было ли журнал стерт */
        bool eeprom_was_erased;
        /* было ли записано сообщение о стирании журнала */
        bool eeprom_erase_message_was_writen;

        int16_t sys_set_flag;
        int16_t sys_set_flag_copy;

        /* Текущий индекс сообщения.
         * Данный индекс используется при записи сообщений в память EEPROM. */
        uint16_t message_index;
        /* Копия текущего индекса сообщений */
        uint16_t message_index_old;
        /* Если эти два индекса не совпадают, значит мы принимаем решение по
         * поводу того что юзер что-то делал */

        /* Текущий индекс сообщения.
         * Этот индекс используется при просмотре меню "Архив". */
        uint16_t message_menu_index;
        /* Пока хз что это такое */
        uint16_t message_menu_index_old;

        ArchiveMessage current_message;
        ArchiveMessage last_read_message;

        at24c64 <0xA6, 0xA7> EEPROM;
        //at24c64 <0xA2, 0xA3> EEPROM;

        void init();
        void write_message();
        void read_message();
        void next_write_address();
    public:
        i2c_errors EraseBlock(uint16_t & erase_block); /* удаляем содержимое журнала */
        void show_lcd_set_reset();
        void MenuEraseEEPROM();
        WorkWithEEPROM ()
        {
            init();
            eeprom_was_erased = true;
            eeprom_erase_message_was_writen = true;
        }

        void drv();
        void show_lcd();

        //void WriteSetI2C(uint16_t _value, uint16_t _adr);
        //uint16_t ReadSetI2C(uint16_t _adr);
        void WriteSet(const uint16_t value, const uint16_t adr);
        uint16_t ReadSet(const uint16_t adr, uint16_t & value);
};

extern uint8_t Tr_iic_byte(uint8_t _byte);
extern uint8_t Rd_iic_byte(uint8_t _mode);
extern void Start_iic();
extern void Stop_iic();

#endif // ARCHIVE_H
