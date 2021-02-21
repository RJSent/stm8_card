#ifndef I2C_H
#define I2C_H

#include <stdint.h>

#define NACK_ERROR -3

int i2c_init(uint8_t freq_mhz);

int i2c_send_bytes(const uint8_t *data, int size, uint8_t addr);

#endif
