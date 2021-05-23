#include <stddef.h>
#include "ssd1306.h"

#include "i2c.h"
/* #include "uart.h" */

#include "baseline.h"

#define BUF_WIDTH  (SSD1306_WIDTH / 2)
#define BUF_HEIGHT (SSD1306_HEIGHT)
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
/* According to main.map, this is 262 bytes long. Why isn't it 257?
   (Or 264 if there's 8-bit padding, but there shouldn't be).
   sizeof(SSD1306_Data) is returning 257... Hmm... */
struct S {
  uint8_t control_byte;
  uint8_t frame_buffer[BUF_SIZE];
} SSD1306_Data = {.control_byte = CONTROL_BYTE(CO_DATA, DC_DATA)};

const uint8_t init_commands[] = {
  CONTROL_BYTE(CO_DATA, DC_COMMAND),
  CMD_OFF, CMD_TIM_DISPLAY_CLK_DIVIDE_RATIO,
  0x80,                         /* ratio 0x80 */
  CMD_HW_MULTIPLEX_RATIO,
  0x1F,                         /* ratio 31 mux */
  CMD_HW_COM_PINS_CONFIG,
  0x02,                         /* split for 128x32 TODO: generate
				   based on dimenstions */
  CMD_CONTRAST, 0x3F,           /* 1/4 brightness, reset is 1/2 */
  0x20,                         /* set addressing mode */
  0x00,                         /* horizontal addressing mode */
  CMD_PUMP_SETTING,
  CHARGE_PUMP_75,
  CMD_FOLLOW_RAM,
  CMD_NOINVERSE,
  CMD_ON,
};

static signed char _ssd1306_protocol(char protocol_arg) {
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
signed char send_data(const uint8_t *data, int size) {
  switch(protocol) {
  case SSD1306_I2C:
    return i2c_send_bytes(data, size, SSD1306_I2C_ADDR);
  case SSD1306_UART:
  case SSD1306_SPI:
    return NOT_IMPLEMENTED;
  default:
    return INVALID;
  }
}

signed char draw_frame_buffer() {
  return send_data(&SSD1306_Data.control_byte, sizeof(struct S));
}

signed char draw_half(ssd1306_side_t side) {
  const uint8_t change_start_right[7] = {CONTROL_BYTE(CO_DATA, DC_COMMAND),
    CMD_ADDR_COL, SSD1306_WIDTH / 2, SSD1306_WIDTH - 1,
    CMD_ADDR_PAGE, 0, 3};
  const uint8_t change_start_left[7] = {CONTROL_BYTE(CO_DATA, DC_COMMAND),
    CMD_ADDR_COL, 0, SSD1306_WIDTH / 2 - 1,
    CMD_ADDR_PAGE, 0, 3};
  int err;
  if (side == RIGHT) {
    err = send_data(change_start_right, sizeof(change_start_right) / sizeof(change_start_right[0]));
  } else {
    err = send_data(change_start_left, sizeof(change_start_left) / sizeof(change_start_left[0]));
  }
  if (err != 0) return err;

  draw_frame_buffer();
  return 0;
}

void clear_buffer() {
  for (int i = 0; i < BUF_SIZE; i++) {
    SSD1306_Data.frame_buffer[i] = 0;
  }
}

void invert_buffer() {
  for (int i = 0; i < BUF_SIZE; i++) {
    SSD1306_Data.frame_buffer[i] = ~(SSD1306_Data.frame_buffer[i]);
  }
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

signed char draw_pixel(char x, char y) {
  /* Since we split screen into two halves */
  if (x >= SSD1306_WIDTH / 2 || y >= SSD1306_HEIGHT) return INVALID;
  SSD1306_Data.frame_buffer[x + ((y / 8) * (SSD1306_WIDTH / 2))] |= (1 << (y % 8)); 

  return 0;
}

signed char clear_pixel(char x, char y) {
  /* Since we split screen into two halves */
  if (x >= SSD1306_WIDTH / 2 || y >= SSD1306_HEIGHT) return INVALID;
  SSD1306_Data.frame_buffer[x + ((y / 8) * (SSD1306_WIDTH / 2))] &= ~(1 << (y % 8)); 
  
  return 0;
}

signed char invert_pixel(char x, char y) {
  /* Since we split screen into two halves */
  if (x >= SSD1306_WIDTH / 2 || y >= SSD1306_HEIGHT) return INVALID;
  SSD1306_Data.frame_buffer[x + ((y / 8) * (SSD1306_WIDTH / 2))] ^= (1 << (y % 8)); 
  
  return 0;
}

void clear_display() {
  clear_buffer();
  draw_half(RIGHT);
  draw_half(LEFT);
}

signed char draw_image(struct DrawableImage *image, ssd1306_side_t side) {
  if (image == NULL) return -1;
  char width = image->images[image->state]->width;
  char need_redraw = 0;                                         /* flag for if any pixels outside bounds of buffer */
  if (side == LEFT && image->x > BUF_WIDTH) return need_redraw; /* don't waste time drawing images that don't appear */
  if (side == RIGHT && image->x + width < BUF_WIDTH) return need_redraw;
  for (int i = 0; i < image->images[image->state]->height; i++) {
    for (int j = 0; j < width; j++) {
      unsigned char subscript = (i * width + j) / 8;
      unsigned char bit_num = 7 - (i * width + j) % 8;
      if ((image->images[image->state]->pixels[subscript] & (1 << (bit_num))) != 0) {
	signed char xcord = image->x + j, ycord = image->y + i;
	if (side == RIGHT) xcord -= SSD1306_WIDTH / 2;
	if (draw_pixel(xcord, ycord) == INVALID) need_redraw = REDRAW_OTHER_HALF;
      }
    }
  }
  
  return need_redraw;
}

/* todo protocol enum typedef */
signed char ssd1306_init(char protocol) {
  _ssd1306_protocol(protocol);
  int err = send_data(init_commands, sizeof(init_commands) / sizeof(init_commands[0]));
  if (!err) clear_display();
  return err;
}
