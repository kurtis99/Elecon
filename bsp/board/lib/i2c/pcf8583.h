#ifndef BSP_DEV_PCF8583_H
#define BSP_DEV_PCF8583_H

#include "twi.h"
#include "struct_define.h"
#include "exit_codes.h"

extern uint8_t Ram_RTC[];

/* По какой-то непонятно причине, если размер массива четный, то микросхема
 * во время записи зависает */
const unsigned char SIZE_RTC_RAM = 11;
const unsigned char PCF883_RAM_OK_CONST = 0xF4;

template <uint8_t EEPROM_W, uint8_t EEPROM_R>
class pcf8583 : private TWI
{
    private:
        uint8_t digi2bcd(uint8_t value);
        uint8_t bcd2digi(uint8_t value);
        i2c_errors init();

    public:
        pcf8583 ()
        {
            init();
        }

        i2c_errors read_ram(const uint8_t adr, const uint8_t size);
        i2c_errors write_ram(const uint8_t adr, const uint8_t size);

        i2c_errors set_time(const SysTime & time);
        i2c_errors get_time(SysTime & time);
};

template <uint8_t EEPROM_W, uint8_t EEPROM_R>
i2c_errors pcf8583 <EEPROM_W, EEPROM_R>::read_ram(const uint8_t addr,
                                                  const uint8_t size)
{
    uint8_t status, data, i, checksum;

    status = i2c_start();
    if (status == 1) {
        i2c_stop();
        return ERROR_START;
    }

    /* Адресс микросхемы на линии */
    status = i2c_sendAddr(EEPROM_W);
    if (status == 1) {
        i2c_stop();
        return ERROR_ADDRESS;
    }

    /* внутренний адресс в самом устройстве */
    status = i2c_sendData(addr);
    if (status == 1) {
        i2c_stop();
        return ERROR_DATA;
    }

    /* повторная инициализация "старт" условия для чтения */
    status = i2c_repeatStart();
    if (status == 1) {
        i2c_stop();
        return ERROR_RESTART;
    }

    /* Ставим микросхему по удобней, для чтения */
    status = i2c_sendAddr(EEPROM_R);
    if (status == 1) {
        i2c_stop();
        return ERROR_ADDRESS;
    }

    checksum = 0;
    for (i = 0; i < size; i++) {
        data = i2c_receiveData_ACK();
        if (data == ERROR_CODE) {
            i2c_stop();
            return ERROR_RECEIVE;
        }

        Ram_RTC[i] = data;
        checksum += data;         // контрольная сумма
    }

    /* не совпала контрольная сума */
    data = i2c_receiveData_ACK();
    if (data == ERROR_CODE) {
        /* Ошибка получения байта */
        i2c_stop();
        return ERROR_RECEIVE;
    } else if (data != checksum) {
        /* контрольная сумма не ОК */
        i2c_stop();
        return ERROR_PCF8583_RAM_CHECKSUM_FAIL;
    }

    data = i2c_receiveData_NACK();
    if (data == ERROR_CODE) {
        /* Ошибка получения байта */
        i2c_stop();
        return ERROR_RECEIVE;
    } else if (data != PCF883_RAM_OK_CONST) {
        /* Ошибочный константный байт в озу */
        i2c_stop();
        return ERROR_PCF8583_RAM_OK_CONST;
    }

    i2c_stop();
    return I2C_OK;
}

template <uint8_t EEPROM_W, uint8_t EEPROM_R>
i2c_errors pcf8583 <EEPROM_W, EEPROM_R>::write_ram(const uint8_t addr,
                                                   const uint8_t size)
{
    uint8_t i,checksum, status;

    status = i2c_start();
    if (status == 1) {
        i2c_stop();
        return ERROR_START;
    }

    status = i2c_sendAddr(EEPROM_W);
    if (status == 1) {
        i2c_stop();
        return ERROR_ADDRESS;
    }

    status = i2c_sendData(addr);
    if (status == 1) {
        i2c_stop();
        return ERROR_DATA;
    }

    /* Считаем контрольную сумму и шлем данные по I2C */
    checksum = 0;
    for (i=0; i < size; i++) {
        status = i2c_sendData(Ram_RTC[i]);
        if (status == 1) {
            i2c_stop();
            return ERROR_DATA;
        }
        checksum += Ram_RTC[i];
    }

    status = i2c_sendData(checksum);
    if (status == 1) {
        i2c_stop();
        return ERROR_DATA;
    }

    status = i2c_sendData(PCF883_RAM_OK_CONST);
    if (status == 1) {
        i2c_stop();
        return ERROR_DATA;
    }

    i2c_stop();
    return I2C_OK;
}

template <uint8_t EEPROM_W, uint8_t EEPROM_R>
i2c_errors pcf8583 <EEPROM_W, EEPROM_R>::get_time(SysTime & time)
{
    uint8_t status, data;

    status = i2c_start();
    if (status == 1) {
        i2c_stop();
        return ERROR_START;
    }

    status = i2c_sendAddr(EEPROM_W);
    if (status == 1) {
        i2c_stop();
        return ERROR_ADDRESS;
    }

    status = i2c_sendData(0x03);
    if (status == 1) {
        i2c_stop();
        return ERROR_DATA;
    }

    status = i2c_repeatStart();
    if (status == 1) {
        i2c_stop();
        return ERROR_RESTART;
    }

    status = i2c_sendAddr(EEPROM_R);
    if (status == 1) {
        i2c_stop();
        return ERROR_ADDRESS;
    }

    /* Проверяем только первый байт */
    data = i2c_receiveData_ACK();
    if (data == ERROR_CODE) {
        i2c_stop();
        return ERROR_RECEIVE;
    }
    time.min    = bcd2digi(data);  // bcd2digi
    time.hour   = bcd2digi(i2c_receiveData_ACK() & 0x3f);
    time.day    = bcd2digi(i2c_receiveData_ACK() & 0x3f);
    time.month  = bcd2digi(i2c_receiveData_NACK() & 0x1f);

    i2c_stop();
    return I2C_OK;
}

template <uint8_t EEPROM_W, uint8_t EEPROM_R>
i2c_errors pcf8583 <EEPROM_W, EEPROM_R>::set_time(const SysTime & time)
{
    uint8_t status;

    status = i2c_start();
    if (status == 1) {
        i2c_stop();
        return ERROR_START;
    }

    //(void)write_i2c(i2c_address);//10100000 select iic write
    status = i2c_sendAddr(EEPROM_W);
    if (status == 1) {
        i2c_stop();
        return ERROR_ADDRESS;
    }

    status = i2c_sendData(0x03);
    if (status == 1) {
        i2c_stop();
        return ERROR_DATA;
    }

    status = i2c_sendData(time.min);
    if (status == 1) {
        i2c_stop();
        return ERROR_DATA;
    }
    (void)i2c_sendData(time.hour);
    (void)i2c_sendData(time.day);
    (void)i2c_sendData(time.month);

    i2c_stop();
    return I2C_OK;
}

template <uint8_t EEPROM_W, uint8_t EEPROM_R>
uint8_t pcf8583 <EEPROM_W, EEPROM_R>::bcd2digi(uint8_t value)
{
    /* x=(x % 10) + ((x/ 10)<<4); */
    uint8_t temp;

    temp  = (value >> 4);
    temp *= 10;
    temp += (value & 0xf);

    return temp;
}

template <uint8_t EEPROM_W, uint8_t EEPROM_R>
uint8_t pcf8583 <EEPROM_W, EEPROM_R>::digi2bcd(uint8_t value)
{
    uint8_t temp;

    temp   = (value / 10);
    temp <<= 4;
    temp  += (value % 10);

    return temp;
}

template <uint8_t EEPROM_W, uint8_t EEPROM_R>
i2c_errors pcf8583 <EEPROM_W, EEPROM_R>::init()
{
    uint8_t status;

    status = i2c_start();
    if (status == 1) {
        i2c_stop();
        return ERROR_START;
    }

    /* Проверяем наличие часов на линии */
    status = i2c_sendAddr(EEPROM_W);
    if (status == 1) {
        i2c_stop();
        return ERROR_ADDRESS;
    }

    status = i2c_sendData(0x0);
    if (status == 1) {
        i2c_stop();
        return ERROR_DATA;
    }

    status = i2c_sendData(0x08);
    if (status == 1) {
        i2c_stop();
        return ERROR_DATA;
    }
    /* 0x08 - mask flag:
    *      0  read locations 05 to 06 unmasked
    *      1  read date and month count directly */

    i2c_stop();
    return I2C_OK;
}

#endif /* BSP_DEV_PCF8583_H */
