#include "i2c.h"
#include "registers.h"
#include "uart.h"
#include "baseline.h"

#define PERIPH_ENABLE 1
#define START_GEN 0x01
#define STOP_GEN 0x02

#define TRANSMIT 0
#define RECEIVER 1

#define TXE 0x80

int i2c_init(uint8_t freq_mhz) {
  uint8_t trise = freq_mhz + 1;      /* pg. 318 in rm0016. I think this shortcut calculation is valid */
  if (freq_mhz > 24 || freq_mhz < 1) return -1;      /* 1-24 valid */
  if (trise >= 2 << 6) return -1;                    /* <= 6 bits */

  I2C_FREQR = freq_mhz;
  I2C_TRISER = trise;           /* must configure before PE  */
  I2C_CCRL = 0x32;
  I2C_CR1 |= PERIPH_ENABLE;     /* enable bit */

  return 0;
}

int i2c_send_byte(uint8_t data) {
  I2C_DR = (data);
  /* while () */
  return 0;
}

void i2c_start_condition() {
  I2C_CR2 |= START_GEN;
}

int i2c_send_bytes(uint8_t *data, int size, uint8_t addr) {
  i2c_start_condition();
  delay(50);
  i2c_send_byte(addr << 1 | TRANSMIT);
  /* for (int i = 0; i < size; i++) { */
  /*   while ((I2C_SR1 & TXE) != 0) {}; */
  /*   i2c_send_byte(data[i]); */
  /* } */
  /*   uart_printf("CR1 Byte 0b%b\n\r", I2C_CR1); */
  /* uart_printf("CR2 Byte 0b%b\n\r", I2C_CR2); */
  /* uart_printf("ADDR Bit %d\n\r", (I2C_SR1 & 0x2) >> 1); */
  /* uart_printf("SB Bit %d\n\r", (I2C_SR1 & 0x1) >> 1); */
  /* while ((I2C_SR1 & TXE) != 0) {}; */
  /* i2c_stop_condition(); */
  return 0;
}
