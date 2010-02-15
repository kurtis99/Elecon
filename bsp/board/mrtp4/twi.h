//**********************************************************************//
//FILE: twi.h
//AUTHOR: Adam Kadolph
//DATE:    10-6-08
//DESCRIPTION: I2C interface using AVR Two-Wire Interface (TWI) hardware
//**********************************************************************//

#ifndef BSP_MRTP4EX_TWI_H
#define BSP_MRTP4EX_TWI_H

//TWI internal functions to expand TWI/I2C for other devices like EEPROM
class TWI
{
private:
    // TWSR values
    // Master
    static const unsigned char START                 = 0x08;
    static const unsigned char REPEAT_START          = 0x10;

    // Master Transmitter
    static const unsigned char MT_SLA_ACK            = 0x18;
    static const unsigned char MT_SLA_NACK           = 0x20;
    static const unsigned char MT_DATA_ACK           = 0x28;
    static const unsigned char MT_DATA_NACK          = 0x30;
    static const unsigned char MT_ARB_LOST           = 0x38;

    // Master Receiver
    static const unsigned char MR_ARB_LOST           = 0x38;
    static const unsigned char MR_SLA_ACK            = 0x40;
    static const unsigned char MR_SLA_NACK           = 0x48;
    static const unsigned char MR_DATA_ACK           = 0x50;
    static const unsigned char MR_DATA_NACK          = 0x58;

    // Slave Transmitter
    static const unsigned char ST_SLA_ACK            = 0xA8;
    static const unsigned char ST_ARB_LOST_SLA_ACK   = 0xB0;
    static const unsigned char ST_DATA_ACK           = 0xB8;
    static const unsigned char ST_DATA_NACK          = 0xC0;
    static const unsigned char ST_LAST_DATA          = 0xC8;

    // Slave Receiver
    static const unsigned char SR_SLA_ACK            = 0x60;
    static const unsigned char SR_ARB_LOST_SLA_ACK   = 0x68;
    static const unsigned char SR_GCALL_ACK          = 0x70;
    static const unsigned char SR_ARB_LOST_GCALL_ACK = 0x78;
    static const unsigned char SR_DATA_ACK           = 0x80;
    static const unsigned char SR_DATA_NACK          = 0x88;
    static const unsigned char SR_GCALL_DATA_ACK     = 0x90;
    static const unsigned char SR_GCALL_DATA_NACK    = 0x98;
    static const unsigned char SR_STOP               = 0xA0;

    // Misc
    static const unsigned char NO_INFO               = 0xF8;
    static const unsigned char BUS_ERROR             = 0x00;

    // defines and constants
    static const unsigned char CMD_MASK              = 0x0F;
    static const unsigned char STATUS_MASK           = 0xF8;

    // return values
    //static const unsigned char I2C_OK                = 0x00;
    //static const unsigned char I2C_ERROR_NODEV       = 0x01;

    static const unsigned char ERROR_CODE            = 0x7E;

    void init();

public:
    TWI()
    {
        init();
    }
    unsigned char i2c_start(void);
    unsigned char i2c_repeatStart(void);
    unsigned char i2c_sendAddr(unsigned char addr);
    unsigned char i2c_sendData(unsigned char data);
    unsigned char i2c_receiveData_ACK(void);
    unsigned char i2c_receiveData_NACK(void);
    void i2c_stop(void);

};

#endif /* BSP_MRTP4EX_TWI_H */
