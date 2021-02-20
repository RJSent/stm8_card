
#include "ssd1306.h"

#include "i2c.h"
#include "uart.h"

#define WIDTH  (128)
#define HEIGHT (32)

/* Notice that char != signed char. Implementation defined so it might act like either
   stackoverflow.com/questions/451375 */
static signed char protocol = INVALID;
static char address_mode;
static uint8_t frame_buffer[256];

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
    return INVALID;
  }
  return 0;
}

/* transmits data depending on what protocol to use */
char send_data(const uint8_t *data, char size, char address) {
  switch(protocol) {
  case SSD1306_I2C:
    return i2c_send_bytes(data, size, address);
  case SSD1306_UART:
  case SSD1306_SPI:
    return NOT_IMPLEMENTED;
  default:
    return INVALID;
  }
}

char draw_frame_buffer() {
  uint8_t data[2] = {CONTROL_BYTE(CO_DATA, DC_DATA)};
  int size_buf = sizeof(frame_buffer) / sizeof(frame_buffer[0]);
  for (int i = 0; i < size_buf; i++) {
    data[1] = frame_buffer[i];
    int err = send_data(data, 2, SSD1306_I2C_ADDR);
    if (err != 0) return err;
  }
  return 0;
}

char draw_right_half() {
  const uint8_t change_start[7] = {CONTROL_BYTE(CO_DATA, DC_COMMAND),
    CMD_ADDR_COL, 64, 127,
    CMD_ADDR_PAGE, 0, 3};
  int err = send_data(change_start, 7, SSD1306_I2C_ADDR);
  if (err != 0) return err;

  draw_frame_buffer();

  return 0;
}

char draw_left_half() {
  const uint8_t change_start[7] = {CONTROL_BYTE(CO_DATA, DC_COMMAND),
    CMD_ADDR_COL, 0, 63,
    CMD_ADDR_PAGE, 0, 3};
  int err = send_data(change_start, 7, SSD1306_I2C_ADDR);
  if (err != 0) return err;

  draw_frame_buffer();

  return 0;
}

char draw_pixel(char x, char y) {
  frame_buffer[0] = 0xFF;

  return NOT_IMPLEMENTED;
}

char clear_display() {
  const uint8_t data[2] = {CONTROL_BYTE(CO_DATA, DC_DATA),
    0};

  for (int i = 0; i < WIDTH * HEIGHT; i++) {
    int err = send_data(data, 2, SSD1306_I2C_ADDR);
    if (err != 0) return err;
  }
  
  return 0;
}

