#include <stdlib.h>

#include "baseline.h"
#include "i2c.h"
#include "uart.h"
#include "ssd1306.h"

/* Note that the dev board that I am using has a button meant to help
   quickly power cycle for testing. This power cycle seems to only
   partially power off the controller, as I've noticed changes to my
   I2C code not fully carrying over if I just press the button as
   opposed to fully cutting it from power. Weird unexpected behavior
   may occur otherwise. */
/* That said, there may be a simpler explanation. It's possible I
   might have just not zoomed out fully on the logic analyzer, leading
   to me misidentifying odd behavior. I thought I did in fact zoom out
   fully several times, so I'm not sure. */
/* There 1000% is odd behavior just using the button to power cycle.
   Confirmed when I noticed I2C communication wasn't being sent at
   all, but after fully power cycling it was sent again. */


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
  i2c_init(2);                  /* fixme no apparent effect */
  uart_printf("\n\r------------\n\r");
  uart_printf("Started!\n\r");
  uint8_t data[5];
  data[0] = CONTROL_BYTE(CO_BOTH, DC_COMMAND);
  data[1] = CMD_ON;
  data[2] = CONTROL_BYTE(CO_BOTH, DC_COMMAND);
  data[3] = CMD_FOLLOW_RAM;

  int err = i2c_send_bytes(data, 4, 0x3C);
  if (err == NACK_ERROR) {
    uart_printf("NACK ERROR!!!\n\r");
  }
  /* Funny story with (char) cast. Originally send_bytes took an int in that spot, but I changed it to char in i2c.c/h for memory concerns. I then noticed that addr wasn't being sent correctly after that. Turns out I needed to recompile main.c as well! */

  /* uart_printf("Done!\n\r"); */

  while (1) {
    data[0] = CONTROL_BYTE(CO_BOTH, DC_DATA);
    data[1] = random_upto(0xFF);
    i2c_send_bytes(data, 2, 0x3C);
    /* delay(50); */
  }
}
