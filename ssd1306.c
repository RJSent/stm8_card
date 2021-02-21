
#include "ssd1306.h"

#include "i2c.h"
#include "uart.h"

#define WIDTH    (128)
#define HEIGHT   (32)
#define BUF_SIZE (WIDTH * HEIGHT / (8 * 2))

/* Notice that char != signed char. Implementation defined so it might act like either
   stackoverflow.com/questions/451375 */
static signed char protocol = INVALID;
static char address_mode;

/* This structure is created so send_data and subfunctions will send a
   control byte as well as the frame_buffer. */
/* Note that structure padding is a thing on certain platforms,
   although apparently it's nott needed for this structure on the STM8
   (or maybe at all). If it becomes an issue down the line, follow the
   advice from stackoverflow.com/questions/4306186, namely the
   suggestion of using __attribute__((__packed__)) */
struct S {
  uint8_t control_byte;
  uint8_t frame_buffer[BUF_SIZE];
} SSD1306_Data = {.control_byte = CONTROL_BYTE(CO_DATA, DC_DATA)};

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
char send_data(const uint8_t *data, int size, char address) {
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

/* TODO: Speedup by minimizing redundant start conditions and function calls */
char draw_frame_buffer() {
  uart_printf("%d\n\r", sizeof(struct S));
  send_data(&SSD1306_Data.control_byte, sizeof(struct S), SSD1306_I2C_ADDR);
  return 0;
}

char draw_right_half() {
  const uint8_t change_start[7] = {CONTROL_BYTE(CO_DATA, DC_COMMAND),
    CMD_ADDR_COL, WIDTH / 2, WIDTH - 1,
    CMD_ADDR_PAGE, 0, 3};
  int err = send_data(change_start, 7, SSD1306_I2C_ADDR);
  if (err != 0) return err;

  draw_frame_buffer();

  return 0;
}

char draw_left_half() {
  const uint8_t change_start[7] = {CONTROL_BYTE(CO_DATA, DC_COMMAND),
    CMD_ADDR_COL, 0, WIDTH / 2 - 1,
    CMD_ADDR_PAGE, 0, 3};
  int err = send_data(change_start, 7, SSD1306_I2C_ADDR);
  if (err != 0) return err;

  draw_frame_buffer();

  return 0;
}

char clear_buffer() {
  for (int i = 0; i < BUF_SIZE; i++) {
    SSD1306_Data.frame_buffer[i] = 0;
  }
  return 0;
}

char draw_pixel(char x, char y) {
  /* Since we split screen into two halves */
  if (x >= WIDTH / 2 || y >= HEIGHT) return INVALID;
  SSD1306_Data.frame_buffer[x + ((y / 8) * (WIDTH / 2))] |= (1 << (y % 8)); 

  return 0;
}

char clear_display() {
  clear_buffer();
  draw_right_half();
  draw_left_half();
  
  return 0;
}

