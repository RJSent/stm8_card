#include "i2c.h"
#include "registers.h"
#include "uart.h"
#include "baseline.h"

#define PERIPH_ENABLE 1
#define START_GEN 0x01
#define STOP_GEN 0x02

#define TRANSMIT 0
#define RECEIVE  1

#define SB   ((I2C_SR1 & 0x01))
#define ADDR ((I2C_SR1 & 0x02) >> 1)
#define BTF  ((I2C_SR1 & 0x04) >> 2)
#define TXE  ((I2C_SR1 & 0x80) >> 7)

#define AF   ((I2C_SR2 & 0x04) >> 2)

#define MSL  ((I2C_SR3 & 0x01))
#define BUSY ((I2C_SR3 & 0x02) >> 1)
#define TRA  ((I2C_SR3 & 0x04) >> 2)

/* FIXME: Disable before + reset to initial, also ensure GPIO is set properly */
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

void i2c_start_condition() {
  while (BUSY) {};              /* wait until bus is free */
  I2C_CR2 |= START_GEN;
  while (!SB) {};               /* return when start condition is sent */
}

void i2c_stop_condition() {
  I2C_CR2 |= STOP_GEN;
}

void i2c_debug() {
  uart_printf("SR1: 0b%b\n\r", I2C_SR1);
  uart_printf("SR2: 0b%b\n\r", I2C_SR2);
  uart_printf("SR3: 0b%b\n\r", I2C_SR3);
}

/* FIXME: i2c_start_condition() reads SR1, meaning we can't read SR3
   at all before the if statement as ADDR would be cleared and we'd
   have a NACK_ERROR even though it was ACK'd */
int i2c_send_bytes(uint8_t *data, char size, uint8_t addr) {
  volatile uint8_t temp;
  i2c_start_condition();
  I2C_DR = (addr << 1 | TRANSMIT);
  delay(30);                    /* FIXME: hardcoded delay. Need to wait until we get ACK, but I can't read SR3 to do it since that'll reset ADDR */
  /* clear ADDR by reading SR1 then SR3 */
  if (ADDR == 1) {              /* read SR1 */
    temp = I2C_SR3;             /* read SR3 */
    for (int i = 0; i < size; i++) {
      I2C_DR = data[i];
      while (TXE != 1) {};      /* order matters here since sending addr doesn't set TXE */
    }
    i2c_stop_condition();
    return 0;
  } else {
    return NACK_ERROR;
  }
}
