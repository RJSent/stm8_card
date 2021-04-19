#include <stdlib.h>

#include "baseline.h"
#include "i2c.h"
#include "uart.h"
#include "ssd1306.h"
#include "image.h"
#include "space_invader.h"
#include "gpio.h"

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

gpio_pin_t btn0 = { .port = 'D', .num = 1 };
gpio_pin_t btn1 = { .port = 'D', .num = 2 };
gpio_pin_t btn2 = { .port = 'C', .num = 6 };
gpio_pin_t led0 = { .port = 'A', .num = 1 };
gpio_pin_t led1 = { .port = 'A', .num = 2 };

void gpio_initialize() {
  gpio_mode(&btn0, GPIO_INPUT_FLOAT);
  gpio_mode(&btn1, GPIO_INPUT_FLOAT);
  gpio_mode(&btn2, GPIO_INPUT_FLOAT);
  gpio_mode(&led0, GPIO_OUTPUT_PUSH_PULL);
  gpio_mode(&led1, GPIO_OUTPUT_PUSH_PULL);
}



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

  clear_display();

  invader_game_init(SSD1306_WIDTH, SSD1306_HEIGHT);
  struct InvaderCommands invader_commands = {.movement = DOWN};
  char cycle_num = 0;
  const char max_cycles = 2;
  gpio_initialize();
  /* something is resetting PORTD CR1 to reset val of 0x02 */
  /* no clue wtf is going on, stm8flash dump has cr1 as reset of 0x02,
     my printfs have it going from reset of 0x02 to 0x00 (expected) */
  /* gpio_write seems to work though! */
  while (1) {
    /* uart_printf("-----CYCLE %d-----\n\r", cycle_num); */
    uart_printf("PD_cr1 addr %x\n\r", (volatile uint8_t *)(PD_BASE + CR1_OFF));
    uart_printf("PD_cr1 val %b\n\r", *(volatile uint8_t *)(PD_BASE + CR1_OFF));
      /* if (gpio_read(&btn0)) { */
	gpio_write(&led0, true);
	gpio_write(&led1, false);
	invader_commands.movement = DOWN;
      /* } else */ if (gpio_read(&btn1)) {
	gpio_write(&led0, false);
	gpio_write(&led1, true);
	invader_commands.movement = UP;
      } else {
	gpio_write(&led0, false);
	gpio_write(&led1, false);
	invader_commands.movement = NOP;
      }
      delay(1600000);

    cycle_num++;

    /* if (cycle_num == max_cycles) { */
    /*   uart_printf("-----END-----\n\r"); */
    /*   while(1) {}; */
    /* } */
    
  }
}


