
#include "ssd1306.h"

#include "i2c.h"
#include "uart.h"

#include "baseline.h"

#define WIDTH      (128)
#define HEIGHT     (32)
#define BUF_WIDTH  (WIDTH / 2)
#define BUF_HEIGHT (HEIGHT)
#define BUF_SIZE   (BUF_WIDTH * BUF_HEIGHT / (8))

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
/* sourceforge.net/p/sdcc/mailman/sdcc-user/thread/CACBduit4%2Ba08M3X0zaU-1YqEifDqK7sMCxy0wSn9Nq53BM8SHw%40mail.gmail.com/
   shows that packing is not support or traditionally necessary with
   8-bit processors */
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

char draw_frame_buffer() {
  send_data(&SSD1306_Data.control_byte, sizeof(struct S), SSD1306_I2C_ADDR);
  return 0;
}

/* TODO: Condense right_half and left_half into 1 function */
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

char invert_buffer() {
  for (int i = 0; i < BUF_SIZE; i++) {
    SSD1306_Data.frame_buffer[i] = ~(SSD1306_Data.frame_buffer[i]);
  }
  return 0;
}

char mirror_buffer(char axis) {
  switch (axis) {
  case Y_AXIS_MIRROR:
    /* 0 paired with BUF_WIDTH     */
    /* 1 paired with BUF_WIDTH - 1 */
    /* 2 paired with BUF_WIDTH - 2 */
    /* ... */
    /* BUF_WIDTH / 2 paired with BUF_WIDTH - BUF_WIDTH / 2 - 1 = BUF_WIDTH / 2 + 1 */
    /* Repeat for however many rows */
    for (int i = 0; i < BUF_HEIGHT / 8; i++) {
      for (int j = 0; j < BUF_WIDTH / 2; j++) {
	char temp = SSD1306_Data.frame_buffer[i * BUF_WIDTH + j];
	SSD1306_Data.frame_buffer[i * BUF_WIDTH + j] = SSD1306_Data.frame_buffer[i * BUF_WIDTH + BUF_WIDTH - 1 - j];
	SSD1306_Data.frame_buffer[i * BUF_WIDTH + BUF_WIDTH - 1 - j] = temp;
      }
    }
    break;
  case X_AXIS_MIRROR:
    /* 0 paired with 192 */
    /* 1 paired with 193 */
    /* 2 paired with 194 */
    /* ... */
    /* 63 paired with 255 */
    /* 64 paired with 128 */
    for (int i = 0; i < BUF_HEIGHT / 16; i++) {
      for (int j = 0; j < BUF_WIDTH; j++) {
	char temp = reverse_byte(SSD1306_Data.frame_buffer[i * BUF_WIDTH + j]);
	SSD1306_Data.frame_buffer[i * BUF_WIDTH + j] = reverse_byte(SSD1306_Data.frame_buffer[BUF_WIDTH * (3 - i) + j]);
	SSD1306_Data.frame_buffer[BUF_WIDTH * (3 - i) + j] = temp;
      }
    }
    break;
  case BOTH_AXIS_MIRROR:        /* faster to do this then mirror y & mirror x */
    for (int i = 0; i < BUF_SIZE / 2; i++) {
      char temp = reverse_byte(SSD1306_Data.frame_buffer[i]);
      SSD1306_Data.frame_buffer[i] = reverse_byte(SSD1306_Data.frame_buffer[BUF_SIZE - i]);
      SSD1306_Data.frame_buffer[BUF_SIZE - i] = temp;
    }
    break;
  default:
    return INVALID;
  }
  return 0; 
}

signed char set_pixel(char x, char y) {
  /* Since we split screen into two halves */
  if (x >= WIDTH / 2 || y >= HEIGHT) return INVALID;
  SSD1306_Data.frame_buffer[x + ((y / 8) * (WIDTH / 2))] |= (1 << (y % 8)); 

  return 0;
}

signed char clear_pixel(char x, char y) {
  /* Since we split screen into two halves */
  if (x >= WIDTH / 2 || y >= HEIGHT) return INVALID;
  SSD1306_Data.frame_buffer[x + ((y / 8) * (WIDTH / 2))] &= ~(1 << (y % 8)); 
  
  return 0;
}

signed char invert_pixel(char x, char y) {
  /* Since we split screen into two halves */
  if (x >= WIDTH / 2 || y >= HEIGHT) return INVALID;
  SSD1306_Data.frame_buffer[x + ((y / 8) * (WIDTH / 2))] ^= (1 << (y % 8)); 
  
  return 0;
}

char clear_display() {
  clear_buffer();
  draw_right_half();
  draw_left_half();
  
  return 0;
}

char draw_image(struct DrawableImage *image) {
  char need_redraw = 0;         /* flag for if some pixels of image were outside bounds of buffer*/
  for (int i = 0; i < image->images[image->state]->height; i++) {
    for (int j = 0; j < image->images[image->state]->width; j++) {
      unsigned char subscript = i + j / 8;
      unsigned char bit_num = j % 8;
      if ((image->images[image->state]->pixels[subscript] & (1 << (bit_num))) != 0) {
	if (set_pixel(image->x + j, image->y + i) == INVALID) need_redraw = REDRAW_OTHER_HALF;	
      }
    }
  }
  
  return need_redraw;
}
