#include <stdlib.h>

#include "baseline.h"
#include "i2c.h"
#include "uart.h"
#include "ssd1306.h"
#include "image.h"
#include "space_invader.h"

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

  /* Similar issue to one I had before came up again! I changed the
     argument to hsi_prescaler to a char and recompiled. However,
     main.c had no changes and wasn't recompiled. This means an int
     was being sent to an argument expecting a char without any
     casting or similar, causing undefined behavior. In my case, I'm
     pretty sure the prescaler was just returning -1 and not setting
     the CLK_CKDIVR register */
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

  clear_display();

  /* temporary for testing ssd1306.h/draw_image */
  /* drawn horizontally */
  const uint8_t smile_image_data[7] = {0x24, 0x24, 0x24, 0x00, 0x81, 0x42, 0x3C};
  const struct Image smile_image = {.width = 8, .height = 7, .pixels = smile_image_data};
  struct DrawableImage smile_drawable = {.x = 1, .y = 1, .state = 0, .images = {&smile_image} };

  const uint8_t spaceship_frame_0[24] = {
    0x01, 0x00, 0x00,
    0x01, 0x80, 0x00,
    0x41, 0xC1, 0x80,
    0x6F, 0xFF, 0xF0,
    0x0F, 0xFF, 0xF0,
    0x81, 0xC1, 0x80,
    0x11, 0x80, 0x00,
    0x41, 0x00, 0x00
  };
  const uint8_t spaceship_frame_1[24] = {
    0x01, 0x00, 0x00,
    0xC1, 0x80, 0x00,
    0x01, 0xC1, 0x80,
    0x8F, 0xFF, 0xF0,
    0x2F, 0xFF, 0xF0,
    0x21, 0xC1, 0x80,
    0x11, 0x80, 0x00,
    0x11, 0x00, 0x00
  };
  const uint8_t spaceship_frame_2[24] = {
    0x21, 0x00, 0x00,
    0x41, 0x80, 0x00,
    0x21, 0xC1, 0x80,
    0x8F, 0xFF, 0xF0,
    0x0F, 0xFF, 0xF0,
    0x81, 0xC1, 0x80,
    0x41, 0x80, 0x00,
    0x61, 0x00, 0x00
  };

  const uint8_t odd_width_grid[3] = {
    0xAB, 0xDE, 0xA8
  };

  const struct Image odd_width_image = {.width = 7, .height = 3, .pixels = odd_width_grid};
  struct DrawableImage odd_width_drawable = {.x = 16, .y = 8, .state = 0, .images = {&odd_width_image}};

const struct Image spaceship_image_0 = {.width = 24, .height = 8, .pixels = spaceship_frame_0};
const struct Image spaceship_image_1 = {.width = 24, .height = 8, .pixels = spaceship_frame_1};
const struct Image spaceship_image_2 = {.width = 24, .height = 8, .pixels = spaceship_frame_2};
struct DrawableImage spaceship = {.x = 0, .y = 16, .state = 0, .images = {&spaceship_image_0, &spaceship_image_1, &spaceship_image_2}};

 invader_game_init(SSD1306_WIDTH, SSD1306_HEIGHT);
 struct InvaderCommands invader_commands = {.movement = DOWN};
 

  while (1) {
    ssd1306_side_t side = LEFT; /*  */
    /* draw_image(&smile_drawable, side); */
    /* draw_image(&odd_width_drawable, side); */
    /* draw_image(&spaceship, side); */
    /* draw_half(side); */
    /* side = RIGHT; */
    /* clear_buffer(); */
    /* draw_image(&spaceship, side); */
    /* draw_half(side); */
    /* side = LEFT; */
    /* spaceship.x++; */
    /* spaceship.state++; */
    /* if (spaceship.state == 3) spaceship.state = 0; */
    /* if (spaceship.x == SSD1306_WIDTH - spaceship.images[spaceship.state]->width) spaceship.x = 0; */
    /* clear_buffer(); */

    char loops = 24;
    for (int i = 0; i < loops; i++) {
      if (i < loops / 3) {
	invader_commands.movement = DOWN;
      } else if (i < 2 * loops / 3) {
	invader_commands.movement = UP;
      } else {
	invader_commands.movement = NOP;
      }
      if (random_upto(16) > 14) {
	invader_commands.shoot = TRUE;
      }
      struct DrawableImage *spaceship = debug_drawableimage_spaceship();
      invader_game_tick(&invader_commands);
      draw_image(spaceship, LEFT);
      struct DrawableImage *lasers[3];
      char redrawlasers[3];
      for (int i = 0; i < 3; i++) {
	lasers[i] = debug_drawableimage_playerlaser(i);
	redrawlasers[i] = draw_image(lasers[i], LEFT);
      }
      draw_half(side);
      clear_buffer();
      for (int i = 0; i < 3; i++) {
	if (redrawlasers[i] != 0) {
	  redrawlasers[i] = 0;
	  draw_image(lasers[i], RIGHT);
	}
      }
      clear_buffer();
      invader_commands.shoot = FALSE;
      delay(100000);
    }

    /* uart_printf("-----END-----\n\r"); */
    /* while(1) {}; */

    
    clear_buffer();    
  }
}


