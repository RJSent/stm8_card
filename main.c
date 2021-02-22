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
  ssd1306_protocol(SSD1306_I2C); /* TODO: Move into ssd1306_init */
  i2c_init(2);
  uart_printf("%s\n\r", __DATE__);

  /* Initialize display */
  /* TODO: Move into ssd1306.c as ssd1306_init() */
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

  int smile_state = 0;
  int reverse = 0;
  clear_display();

  while (1) {
    /* Left smile line */
    draw_pixel(17, 17);
    draw_pixel(18, 18);
    draw_pixel(19, 19);
    draw_pixel(20, 20);
    draw_pixel(21, 21);
    /* Mouth */
    for (int i = 0; i <= 13; i++) {
      draw_pixel(i + 22, 22);
    }
    /* Right smile line */
    draw_pixel(36, 21);
    draw_pixel(37, 20);
    draw_pixel(38, 19);
    draw_pixel(39, 18);
    draw_pixel(40, 17);
    /* right eye */
    for (int i = 4; i <= 11; i++) {
      draw_pixel(35, i);
    }
    /* left eye */
    switch (smile_state) {
    case 0:
      for (int i = 4; i <= 11; i++) {
	draw_pixel(23, i);
      }
      break;
    case 1:
      for (int i = 5; i <= 10; i++) {
	draw_pixel(23, i);
      }
      break;
    case 2:
      for (int i = 6; i <= 9; i++) {
	draw_pixel(23, i);
      }
      break;
    case 3:
      for (int i = 7; i <= 8; i++) {
	draw_pixel(23, i);
      }
      break;
    case 4:
      for (int i = 22; i <= 24; i++) {
	draw_pixel(i, 7);
      }
      break;
    case 5:
      for (int i = 21; i <= 25; i++) {
	draw_pixel(i, 7);
      }
      break;
    case 6:
      for (int i = 20; i <= 26; i++) {
	draw_pixel(i, 7);
      }
      break;
    default:
      smile_state = 0;
    }
    if (reverse == 0) {
      if (smile_state < 6) {
	smile_state++;
      } else {
	reverse = 1;
      }
    } else {
      if (smile_state > 0) {
	smile_state--;
      } else {
	reverse = 0;
      }
    }
    draw_left_half();
    invert_buffer();
    /* mirror_buffer(X_AXIS_MIRROR); */
    /* mirror_buffer(Y_AXIS_MIRROR); */
    mirror_buffer(BOTH_AXIS_MIRROR);
    draw_right_half();
    clear_buffer();
    delay(50000);
    if (smile_state == 0 && reverse == 0) {
      delay(500000);
    }
  }
}

