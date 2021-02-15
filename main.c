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
  uint8_t data[16];
  data[0] = CONTROL_BYTE(CO_DATA, DC_COMMAND);
  data[1] = CMD_OFF;
  data[2] = CMD_TIM_DISPLAY_CLK_DIVIDE_RATIO;
  data[3] = 0x80;                /* ratio 0x80 */
  data[4] = CMD_HW_MULTIPLEX_RATIO;
  data[5] = 0x3F;                /* ratio 63 mux */
  data[6] = CMD_HW_COM_PINS_CONFIG;
  data[7] = 0x12;                /* split for 128x32 */
  data[8] = 0x20;   /* set addressing mode */
  data[9] = 0x00;   /* horiztonal addressing mode */
  data[10] = CMD_PUMP_SETTING;
  data[11] = CHARGE_PUMP_75;
  data[12] = CMD_FOLLOW_RAM;
  data[13] = CMD_NOINVERSE;
  data[14] = CMD_ON;
  delay(75000);

  int err = i2c_send_bytes(data, 15, 0x3C);
  if (err == NACK_ERROR) {
    uart_printf("NACK ERROR!!!\n\r");
  }
  /* Funny story with (char) cast. Originally send_bytes took an int in that spot, but I changed it to char in i2c.c/h for memory concerns. I then noticed that addr wasn't being sent correctly after that. Turns out I needed to recompile main.c as well! */

  /* uart_printf("Done!\n\r"); */

    uint8_t buffer[16][4] = {   /* hello world attempt, transcribed from gimp manually */
    {0x00, 0x00, 0x00, 0x00},
    {0x50, 0x14, 0x00, 0x00},
    {0x53, 0xB9, 0x40, 0x00},
    {0x53, 0xB9, 0x40, 0x00},
    {0x73, 0x96, 0xB0, 0x00},
    {0x72, 0x16, 0x40, 0x00},
    {0x73, 0x96, 0xB0, 0x00},
    {0x00, 0x00, 0x00, 0x00},   /* 2 blank rows */
    {0x00, 0x00, 0x00, 0x00},
    {0x40, 0x40, 0x21, 0x00},
    {0x40, 0x40, 0x21, 0x00},
    {0x20, 0x80, 0x21, 0x00},
    {0x11, 0x00, 0x21, 0x00},
    {0x16, 0x2A, 0x26, 0x00},
    {0x0A, 0x3A, 0x37, 0x00}
  };           /* 16 columns of 32 pixels */
  
  while (1) {
    data[0] = CONTROL_BYTE(CO_DATA, DC_DATA);
    for (int i = 0; i < 32; i++) {
      for (int j = 0; j < 16; j++) {
	if (j > 3 || i > 15) {
	  data[1] = 0;
	} else {
	  data[1] = buffer[i][j];
	}
	i2c_send_bytes(data, 2, 0x3C);
      }
    }
    /* data[1] = random_upto(0xFF); */
    /* if (NACK_ERROR == i2c_send_bytes(data, 2, 0x3C)) { */
      /* uart_printf("err\n\r"); */
    /* } */
    delay(500);
  }
}
