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

int main() {
  const int baud_rate = 9600;
  const long fmaster = 16000000;

  clk_hsi_prescaler(1);
  uart_init(baud_rate, fmaster);
  i2c_init(2);
  uart_printf("%s\n\r", __DATE__);

  /* Initialize display */
  uint8_t data[16];
  data[0] = CONTROL_BYTE(CO_DATA, DC_COMMAND);
  data[1] = CMD_OFF;
  data[2] = CMD_TIM_DISPLAY_CLK_DIVIDE_RATIO;
  data[3] = 0x80;                /* ratio 0x80 */
  data[4] = CMD_HW_MULTIPLEX_RATIO;
  data[5] = 0x1F;                /* ratio 31 mux */
  data[6] = CMD_HW_COM_PINS_CONFIG;
  data[7] = 0x02;                /* split for 128x32 */
  data[8] = 0x20;                /* set addressing mode */
  data[9] = 0x00;                /* horiztonal addressing mode */
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

  /* clear display */
  /* data[0] = CONTROL_BYTE(CO_DATA, DC_DATA); */
  /* data[1] = 0x00; */
  /* for (int i = 0; i < 512; i++) { */
  /*   i2c_send_bytes(data, 2, 0x3C); */
  /* } */

  /* Set address to start writing */
  /* data[0] = CONTROL_BYTE(CO_DATA, DC_COMMAND); */
  /* data[1] = CMD_ADDR_COL; */
  /* data[2] = 0; */
  /* data[3] = 127; */
  /* data[4] = CMD_ADDR_PAGE; */
  /* data[5] = 0x00; */
  /* data[6] = 0x03; */
  /* i2c_send_bytes(data, 7, 0x3C); */

  clear_display();
  ssd1306_protocol(SSD1306_I2C);

  while (1) {
    for (int i = 0; i < 16; i++) {
      draw_pixel(i, 0);
    }

    for (int i = 0; i < 16; i++) {
      draw_pixel(0, i);
    }


    draw_left_half();
    draw_right_half();
    clear_buffer();
    delay(500000);

    for (int i = 0; i < 16; i++) {
      draw_pixel(i, 15);
    }

    for (int i = 0; i < 16; i++) {
      draw_pixel(15, i);
    }


    draw_left_half();
    draw_right_half();
    clear_buffer();
    delay(500000);
  }
}
