#ifndef BSP_DEV_AT24C64_H
#define BSP_DEV_AT24C64_H

#include "twi.h"
#include "exit_codes.h"
#include <avr/pgmspace.h>

//declare eeprom functions
template <uint8_t EEPROM_W, uint8_t EEPROM_R>
class at24c64 : private TWI
{
private:
    static const uint16_t EEPROM_MEMORY_CAPACITY = 8192;
public:
    at24c64()
    {

    };

    uint16_t get_max_eeprom_address() {return EEPROM_MEMORY_CAPACITY;};

    i2c_errors word_read(const uint16_t addr, uint16_t & value);
    i2c_errors word_write(const uint16_t addr, const uint16_t word);

    i2c_errors byte_read(const uint16_t addr, uint8_t & value);
    i2c_errors byte_write(const uint16_t addr, const uint8_t data);

    i2c_errors page_read(const uint16_t addr,
                               uint8_t * message,
                         const uint8_t size_of_message);
    i2c_errors page_write(const uint16_t addr,
                          const uint8_t * message,
                          const uint8_t size_of_message);

    i2c_errors erase(void);
    bool is_present(void);
};

template <uint8_t EEPROM_W, uint8_t EEPROM_R>
i2c_errors at24c64 <EEPROM_W, EEPROM_R>::word_read(const uint16_t addr,
                                                         uint16_t & value)
{
    uint8_t low,high,status;

    union WORD_DATA_TYPE {
        uint16_t word_value;
        uint8_t byte_value[2];
    } data;

    high = (addr>>8);
    low = addr;

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

    status=i2c_sendData(high);
    if (status == 1) {
        i2c_stop();
        return ERROR_DATA;
    }

    status=i2c_sendData(low);
    if (status == 1) {
        i2c_stop();
        return ERROR_DATA;
    }

    status=i2c_repeatStart();
    if (status == 1) {
        i2c_stop();
        return ERROR_RESTART;
    }

    status=i2c_sendAddr(EEPROM_R);
    if (status == 1) {
        i2c_stop();
        return ERROR_ADDRESS;
    }

    data.byte_value[1] = i2c_receiveData_ACK();
    if (data.byte_value[1] == ERROR_CODE) {
        i2c_stop();
        return ERROR_RECEIVE;
    }

    //data <<= 8;
    data.byte_value[0] += i2c_receiveData_NACK();
    if (data.byte_value[0] == ERROR_CODE) {
        i2c_stop();
        return ERROR_RECEIVE;
    }

    i2c_stop();
    value = data.word_value;
    return I2C_OK;
}

template <uint8_t EEPROM_W, uint8_t EEPROM_R>
i2c_errors at24c64 <EEPROM_W, EEPROM_R>::word_write(const uint16_t addr,
                                                        const uint16_t data)
{
    unsigned char low,high,status;

    high = (addr>>8);
    low = addr;

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

    status = i2c_sendData(high);
    if (status == 1) {
        i2c_stop();
        return ERROR_DATA;
    }

    status = i2c_sendData(low);
    if (status == 1) {
        i2c_stop();
        return ERROR_DATA;
    }

    status = i2c_sendData(data>>8);
    if (status == 1) {
        i2c_stop();
        return ERROR_DATA;
    }

    status = i2c_sendData(data);
    if (status == 1) {
        i2c_stop();
        return ERROR_DATA;
    }

    i2c_stop();
    return I2C_OK;
}

template <uint8_t EEPROM_W, uint8_t EEPROM_R>
i2c_errors at24c64 <EEPROM_W, EEPROM_R>::byte_read(const uint16_t addr,
                                                             uint8_t & value)
{
    uint8_t low,high,status;

    high = (addr>>8);
    low = addr;

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

    status = i2c_sendData(high);
    if (status == 1) {
        i2c_stop();
        return ERROR_DATA;
    }

    status = i2c_sendData(low);
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

    value = i2c_receiveData_NACK();
    if (value == ERROR_CODE) {
        i2c_stop();
        return ERROR_RECEIVE;
    }

    i2c_stop();
    return I2C_OK;
}

template <uint8_t EEPROM_W, uint8_t EEPROM_R>
i2c_errors at24c64 <EEPROM_W, EEPROM_R>::byte_write(const uint16_t addr,
                                                        const uint8_t value)
{
    uint8_t low,high,status;

    high = (addr>>8);
    low = addr;

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

    status = i2c_sendData(high);
    if (status == 1) {
        i2c_stop();
        return ERROR_DATA;
    }

    status = i2c_sendData(low);
    if (status == 1) {
        i2c_stop();
        return ERROR_DATA;
    }

    status = i2c_sendData(value);
    if (status == 1) {
        i2c_stop();
        return ERROR_DATA;
    }

    i2c_stop();
    return I2C_OK;
}

template <uint8_t EEPROM_W, uint8_t EEPROM_R>
i2c_errors at24c64 <EEPROM_W,
                  EEPROM_R>::page_read(const uint16_t addr,
                                       uint8_t * message,
                                       const uint8_t size_of_page)
{
    uint8_t i;
    uint8_t low,high,status,data;

    high = (addr>>8);
    low = addr;

    status=i2c_start();
    if (status == 1) {
        i2c_stop();
        return ERROR_START;
    }

    status = i2c_sendAddr(EEPROM_W);
    if (status == 1) {
        i2c_stop();
        return ERROR_ADDRESS;
    }

    status = i2c_sendData(high);
    if (status == 1) {
        i2c_stop();
        return ERROR_DATA;
    }

    status = i2c_sendData(low);
    if (status == 1)  {
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

    for (i=0; i<size_of_page; i++) {
        data = (i == (size_of_page - 1)) ? i2c_receiveData_NACK()
                                         : i2c_receiveData_ACK();
        if (data == ERROR_CODE) {
            i2c_stop();
            return ERROR_DATA;
        }
        *message = data;
        message++;
    }

    i2c_stop();
    return I2C_OK;
}

template <uint8_t EEPROM_W, uint8_t EEPROM_R>
i2c_errors at24c64 <EEPROM_W,
                  EEPROM_R>::page_write(const uint16_t addr,
                                        const uint8_t * message,
                                        const uint8_t size_of_message)
{
    uint8_t i;
    uint8_t low,high,status,data;

    high = (addr>>8);    //split page integer into two bytes for transfer
    low = addr;

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

    status = i2c_sendData(high);
    if (status == 1) {
        i2c_stop();
        return ERROR_DATA;
    }

    status = i2c_sendData(low);
    if (status == 1) {
        i2c_stop();
        return ERROR_DATA;
    }

    for (i=0; i<size_of_message; i++)
    {
        data = *message;        //write data to memory from buffer array
        message++;

        status = i2c_sendData(data);
        if (status == 1) {
            i2c_stop();
            return ERROR_DATA;
        }
    }

    i2c_stop();
    return I2C_OK;
}

#include <avr/delay.h>

template <uint8_t EEPROM_W, uint8_t EEPROM_R>
i2c_errors at24c64 <EEPROM_W, EEPROM_R>::erase(void)
{
    uint16_t i;
    unsigned char data,status;

    status = i2c_start();
    if (status == 1) {
        i2c_stop();
        return ERROR_START;
    }

    status=i2c_sendAddr(EEPROM_W);
    if (status == 1) {
        i2c_stop();
        return ERROR_ADDRESS;
    }

    status=i2c_sendData(0x00);        //set memory pointer to location 0
    if (status == 1) {
        i2c_stop();
        return ERROR_DATA;
    }

    status=i2c_sendData(0x00);
    if (status == 1) {
        i2c_stop();
        return ERROR_DATA;
    }

    for (i=0; i<EEPROM_MEMORY_CAPACITY; i++) {
        data = 0xFF;        //clear all memory

        status = i2c_sendData(data);
        if(status == 1) {
            i2c_stop();
            return ERROR_DATA;
        }
        //_delay_ms(1);
    }

    i2c_stop();
    return I2C_OK;
}

template <uint8_t EEPROM_W, uint8_t EEPROM_R>
bool at24c64 <EEPROM_W, EEPROM_R>::is_present(void)
{
    uint8_t value;

    if (I2C_OK != byte_read(0x0, value))
        return false;

    return true;
}

#endif /* BSP_DEV_AT24C64_H */
