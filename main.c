#include <stdlib.h>

#include "baseline.h"
#include "i2c.h"
#include "uart.h"


/* void second_func(int i) { */
/*   volatile char char_var = 'c'; */
/*   i -= 1; */
/*   if (i > 0) { */
/*     second_func(i); */
/*   } */
/* } */

int main() {
  const int baud_rate = 9600;
  const long fmaster = 16000000;

  clk_hsi_prescaler(1);
  uart_init(baud_rate, fmaster);
  i2c_init(2);
  uint8_t data[] = {1, 2, 3};
  i2c_send_bytes(data, 3, 0x3C);

  while (1) {
    /* uart_printf("Binary:    %b\n\r", 8); */
    /* uart_printf("Character: %c\n\r", 'c'); */
    /* uart_printf("Signed:    %d\n\r", -14); */
    /* uart_printf("String:    %s\n\r", "Hi there!"); */
    /* uart_printf("Unsigned:  %u\n\r", 14); */
    /* uart_printf("Hex:       %x\n\r", 12); */
    delay(50000);
  }
}
