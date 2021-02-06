#include <stdlib.h>
#include <stdint.h>

#include "baseline.h"

int delay(unsigned long num) {
  volatile unsigned long dl;
  for (dl = 0; dl < num; dl++);
  return 0;
}

int random() {
  return rand();
}

int random_upto(int max) {
  return random() % (max + 1);
}

/* This method will eliminate the fHSI = fHSI / 8 prescaler. (So
fmaster = fHSI = 2MHz). This divided fmaster is sent to the UART,
where we further divide it using the BRR1 and BRR2 registers. The
problem is 2Mhz / 0x682 (my divider) should give a baud rate of 1200,
but what I actually got was 120. When I removed the prescaler, it
worked as expected, 9600 baud rate with a fmaster of 16Mhz and divider
of 0x682. */
int clk_hsi_prescaler(int divider) {
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

int clk_cpu_prescaler(int divider) {
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
