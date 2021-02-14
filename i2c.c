#include "i2c.h"
#include "registers.h"
#include "uart.h"
#include "baseline.h"

#define PERIPH_ENABLE 1
#define START_GEN 0x01
#define STOP_GEN 0x02

#define TRANSMIT 0
#define RECEIVE  1

#define TXE  ((I2C_SR1 & 0x80) >> 7)
#define ADDR ((I2C_SR1 & 0x02) >> 1)
#define BTF  ((I2C_SR1 & 0x04) >> 2)

#define TRA  ((I2C_SR3 & 0x04) >> 3)

int i2c_init(uint8_t freq_mhz) {
  uint8_t trise = freq_mhz + 1;      /* pg. 318 in rm0016. I think this shortcut calculation is valid */
  if (freq_mhz > 24 || freq_mhz < 1) return -1;      /* 1-24 valid */
  if (trise >= 2 << 6) return -1;                    /* <= 6 bits */

  I2C_FREQR = freq_mhz;
  I2C_TRISER = trise;           /* must configure before PE  */
  I2C_CCRL = 0x08;              /* this actually controls freq of communications */
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
  while ((I2C_SR1 & 0x01) != 1) {}; /* return when start condition is sent */
}

void i2c_stop_condition() {
  I2C_CR2 |= STOP_GEN;
  // while ((I2C_SR1 & 0x01) != 1) {}; /* return when start condition is sent */
}

void i2c_debug() {
  uart_printf("SR1: 0b%b\n\r", I2C_SR1);
  uart_printf("SR2: 0b%b\n\r", I2C_SR2);
  uart_printf("SR3: 0b%b\n\r", I2C_SR3);
}

int i2c_send_bytes(uint8_t *data, char size, uint8_t addr) {
  volatile uint8_t temp1, temp2, temp3, temp4, temp5, temp6;
  i2c_start_condition();
  i2c_send_byte(addr << 1 | TRANSMIT);
  /* while (TRA != 1) {}; */
  /* clear ADDR by reading SR1 and SR3 */
  delay(30);                    /* fixme hardcoded delay. Need to wait until we get ACK */
  if (ADDR == 1) {
    temp6 = I2C_SR3;
        /* while (BTF == 0) {}; */
        /* I2C_DR = 1; */
    for (int i = 0; i < size; i++) {
      i2c_send_byte(data[i]);
      while (TXE != 1) {};
    }
    i2c_stop_condition();
    return 0;
  } else {
    return NACK_ERROR;
  }

}
