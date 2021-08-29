#include <stdlib.h>

#include "baseline.h"
#include "i2c.h"
#include "uart.h"
#include "ssd1306.h"
#include "image.h"
#include "space_invader.h"
#include "gpio.h"

gpio_pin_t btn0 = { .port = 'C', .num = 6 };
gpio_pin_t btn1 = { .port = 'C', .num = 5 };
gpio_pin_t btn2 = { .port = 'C', .num = 4 };
gpio_pin_t led0 = { .port = 'A', .num = 1 };
gpio_pin_t led1 = { .port = 'A', .num = 2 };

static void initialize_gpio() {
  gpio_mode(&btn0, GPIO_INPUT_FLOAT);
  gpio_mode(&btn1, GPIO_INPUT_FLOAT);
  gpio_mode(&btn2, GPIO_INPUT_FLOAT);
  gpio_mode(&led0, GPIO_OUTPUT_PUSH_PULL);
  gpio_mode(&led1, GPIO_OUTPUT_PUSH_PULL);
}

/* TODO: move to power saving.c/h and take struct for what to gate */
static void periph_gating() {
  *CLK_PCKENR1 &= 0x1;           /* only i2c enabled */
  // *CLK_PCKENR1 |= 1 << 3;        /* enable uart1 */
  *CLK_PCKENR2 &= !(0x8C);      /* 0 to everything not reserved, rm0016 pg 96 */
}

static void power_saving() {
  clk_hsi_prescaler(1);
  clk_cpu_prescaler(128);        /* 125 kHz cpu */
  periph_gating();
  
}

static void initialize() {
  const int baud_rate = 9600;
  const long fmaster = 16000000;

  power_saving();

  uart_init(baud_rate, fmaster);
  i2c_init(2);
  initialize_gpio();
  ssd1306_init(SSD1306_I2C);
  invader_game_init(SSD1306_WIDTH, SSD1306_HEIGHT);
}

int main() {
  initialize();
  uart_printf("%s\n\r", __DATE__);
  char cycle_num = 0;
  const char max_cycles = 10;

  while (1) {
    /* uart_printf("-----CYCLE %d-----\n\r", cycle_num); */
      struct InvaderCommands invader_commands;
      if (gpio_read(&btn0)) {
	gpio_write(&led0, true);
	gpio_write(&led1, false);
	invader_commands.movement = DOWN;
      } else if (gpio_read(&btn1)) {
	gpio_write(&led0, false);
	gpio_write(&led1, true);
	invader_commands.movement = UP;
      } else {
	gpio_write(&led0, false);
	gpio_write(&led1, false);
	invader_commands.movement = NOP;
      }
      /* debounded input here. Maybe just have as timer though for
	 extra button to exit */
      if (random_upto(32) > 30) {
	invader_commands.shoot = TRUE;
      }
      struct DrawableImage *spaceship = debug_drawableimage_spaceship();
      invader_game_tick(&invader_commands);
      draw_image(spaceship, LEFT);
      struct DrawableImage *lasers[3];
      struct DrawableImage *invader_lasers[3];
      struct DrawableImage *invaders[3];
      for (int i = 0; i < 3; i++) {
	lasers[i] = debug_drawableimage_playerlaser(i);
	invader_lasers[i] = debug_drawableimage_invaderlaser(i);
	invaders[i] = debug_drawableimage_invader(i);
	draw_image(lasers[i], LEFT);
	draw_image(invader_lasers[i], LEFT);
	draw_image(invaders[i], LEFT);
      }
      draw_half(LEFT);
      clear_buffer();
      for (int i = 0; i < 3; i++) {
	draw_image(lasers[i], RIGHT);
	draw_image(invader_lasers[i], RIGHT);
	draw_image(invaders[i], RIGHT);
      }
      draw_half(RIGHT);
      clear_buffer();
      invader_commands.shoot = FALSE;
      /* delay(2000); */

    cycle_num++;

    /* if (cycle_num == max_cycles) { */
    /*   uart_printf("-----END-----\n\r"); */
    /* while(1) {}; */
    /* } */
    
    clear_buffer();    
  }
}


