
#include "ssd1306.h"

#include "i2c.h"
#include "uart.h"

static char protocol;

char ssd1306_protocol(char protocol_arg) {
  switch (protocol_arg) {
  case SSD1306_I2C:
    protocol = SSD1306_I2C;
    break;
  case SSD1306_UART:
    protocol = SSD1306_UART;
    break;
  case SSD1306_SPI:
    protocol = SSD1306_SPI;
    break;
  default:
    return SSD1306_INVALID_PROTOCOL;
  }
  return 0;
}

char draw_pixel(char x, char y) {
  
}

