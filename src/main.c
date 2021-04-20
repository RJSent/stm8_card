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

void initialize_gpio() {
  gpio_mode(&btn0, GPIO_INPUT_FLOAT);
  gpio_mode(&btn1, GPIO_INPUT_FLOAT);
  gpio_mode(&btn2, GPIO_INPUT_FLOAT);
  gpio_mode(&led0, GPIO_OUTPUT_PUSH_PULL);
  gpio_mode(&led1, GPIO_OUTPUT_PUSH_PULL);
}

int main() {
  const int baud_rate = 9600;
  const long fmaster = 16000000;

  clk_hsi_prescaler(1); 
  uart_init(baud_rate, fmaster);
  ssd1306_protocol(SSD1306_I2C); /* TODO: Move into ssd1306_init */
  i2c_init(2);
  initialize_gpio();
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

  clear_display();

  invader_game_init(SSD1306_WIDTH, SSD1306_HEIGHT);
  struct InvaderCommands invader_commands = {.movement = DOWN};
  char cycle_num = 0;
  const char max_cycles = 10;

  while (1) {
    /* uart_printf("-----CYCLE %d-----\n\r", cycle_num); */
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
      delay(15000);

    cycle_num++;

    /* if (cycle_num == max_cycles) { */
    /*   uart_printf("-----END-----\n\r"); */
    /* while(1) {}; */
    /* } */
    
    clear_buffer();    
  }
}


