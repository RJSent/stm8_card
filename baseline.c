#include <stdlib.h>

#include "baseline.h"

char delay(unsigned long num) {
  volatile unsigned long dl;
  for (dl = 0; dl < num; dl++);
  return 0;
}

char random() {
  return rand();
}

char random_upto(int max) {
  return random() % (max);
}

/* Code from https://stackoverflow.com/questions/2602823/, should be
   simple enough that copyright doesn't apply but still sourced */
uint8_t reverse_byte(uint8_t byte) {
  byte = (byte & 0xF0) >> 4 | (byte & 0x0F) << 4;
  byte = (byte & 0xCC) >> 2 | (byte & 0x33) << 2;
  byte = (byte & 0xAA) >> 1 | (byte & 0x55) << 1;
  return byte;
}

/* This method will eliminate the fHSI = fHSI / 8 prescaler. (So
fmaster = fHSI = 2MHz). This divided fmaster is sent to the UART,
where we further divide it using the BRR1 and BRR2 registers. The
problem is 2Mhz / 0x682 (my divider) should give a baud rate of 1200,
but what I actually got was 120. When I removed the prescaler, it
worked as expected, 9600 baud rate with a fmaster of 16Mhz and divider
of 0x682. */
char clk_hsi_prescaler(char divider) {
  char bits;
  switch(divider) {
  case 1:
    bits = 0;
    break;
  case 2:
    bits = 1;
    break;
  case 4:
    bits = 2;
    break;
  case 8:
    bits = 3;
    break;
  default:
    return -1;
  }
  *CLK_CKDIVR &= (bits << 3);
  return 0;
}

char clk_cpu_prescaler(unsigned char divider) {
  char bits = 0;
  switch(divider) {
  case 1:
    bits = 0;
    break;
  case 2:
    bits = 1;
    break;
  case 4:
    bits = 2;
    break;
  case 8:
    bits = 3;
    break;
  case 16:
    bits = 4;
    break;
  case 32:
    bits = 5;
    break;
  case 64:
    bits = 6;
    break;
  case 128:
    bits = 7;
    break;
  default:
    return -1;
  }
  *CLK_CKDIVR &= bits;
  return 0;
}
