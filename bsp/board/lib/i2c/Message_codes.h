#ifndef SRC_MESSAGE_CODES_H
#define SRC_MESSAGE_CODES_H

/* Сначала идет значение device_index, затем уточняющее значение
 * error_code для конкретизации ошибки. */

/* Возможные значения device_index */
const unsigned char PDZ_MSG = 0x30;
  /* нет уточняющего кода */

const unsigned char SYSTEM_MSG = 0x40;
  const unsigned char SYSTEM_ON = 0x01;
  const unsigned char SYSTEM_OFF = 0x02;
  const unsigned char SYSTEM_ERROR = 0x03;

const unsigned char EEPROM_ERASED = 0xFF;
  /* нет уточняющего кода */

#endif /* SRC_MESSAGE_CODES_H */
