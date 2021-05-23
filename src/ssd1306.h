
#ifndef SSD1306_H
#define SSD1306_H

#include "image.h"

#define SSD1306_I2C_ADDR                                (0x3C)  /* 0x3C xor 0x3D for SSD1306 and SSD1306B. Determined by D/C# pin */

#define SSD1306_WIDTH      (128)
#define SSD1306_HEIGHT     (32)

#define SSD1306_I2C                                     (1)
#define SSD1306_UART                                    (2)
#define SSD1306_SPI                                     (3)

#define HORIZONTAL_MODE                                 (0)
#define VERTICAL_MODE                                   (1)
#define PAGE_MODE                                       (2)

#define INVALID                                         (-1)
#define NOT_IMPLEMENTED                                 (-2)

/* Change this to enum??? */
#define Y_AXIS_MIRROR                                   (1)
#define X_AXIS_MIRROR                                   (2)
#define BOTH_AXIS_MIRROR                                (3)

#define PAGE0                                           (0x0)
#define PAGE1                                           (0x1)
#define PAGE2                                           (0x2)
#define PAGE3                                           (0x3)
#define PAGE4                                           (0x4)
#define PAGE5                                           (0x5)
#define PAGE6                                           (0x6)
#define PAGE7                                           (0x7)

/* Returned by draw_image if there were pixels on the other half of the frame buffer */
#define REDRAW_OTHER_HALF                         (1)

/* I dunno if an enum is the best way to do this, but I'm doing it! */
typedef enum { RIGHT, LEFT } ssd1306_side_t;

/* Control byte format: CO_DC_000000 */
/* CO = continuation bit */
/* DC = Data/command selection bit */
#define CO_BOTH                                         (1)
#define CO_DATA                                         (0)       /* 0 means rest of the transmission is data only. Continuation bit. */
#define DC_COMMAND                                      (0)       /* Next byte transmitted is command */
#define DC_DATA                                         (1)       /* Next byte transmitted is data */
#define CONTROL_BYTE(bit1, bit2) ((bit1 << 7) | (bit2 << 6))

/* fundamental commands */
#define CMD_CONTRAST                                    (0x81)  /* two byte command, 2nd selects contrast 1-255 */
#define CMD_FOLLOW_RAM                                  (0xA4)
#define CMD_NOFOLLOW_RAM                                (0xA5)  /* Output ignores ram content */
#define CMD_NOINVERSE                                   (0xA6)
#define CMD_INVERSE                                     (0xA7)
#define CMD_OFF                                         (0xAE)
#define CMD_ON                                          (0xAF)
#define CMD_NOP                                         (0xE3)

/* scrolling commands */
#define SCROLL_RIGHT                                    (0)
#define LEFT_SCROLL                                     (1)
#define CMD_SCROLL_H(direction)                         (0x26 + direction)      /* Composed of 7 commands */
#define CMD_SCROLL_HV(direction)                        (0x29 + direction)      /* Composed of 6 commands */
#define CMD_SCROLL_STOP                                 (0x2E)
#define CMD_SCROLL_START                                (0x2F)  /* Most recent scroll setup command overrights previous ones */
#define CMD_SCROLL_SET_V_AREA                           (0xA3)  /* 3 commands */
#define CMD_SCROLL_CONTENT_SETUP(direction)             (0x2C + direction)

/* address setting commands */
#define CMD_ADDR_LOW_COL_PAGE_MODE(nibble)              (nibble)
#define CMD_ADDR_HIGH_COL_PAGE_MODE(nibble)             (0x10 | nibble)
#define CMD_ADDR_MEM_MODE(mode)                         (0x2 | mode)
#define CMD_ADDR_COL                                    (0x21)  /* 3 commands */
#define CMD_ADDR_PAGE                                   (0x22)  /* 3 commands */
#define CMD_ADDR_PAGE_START_PAGE_MODE(three_bits)       (0xA0 | (three_bits))

/* hardware configuration commands */
#define CMD_HW_DISPLAY_START_LINE(five_bits)            (0x20 | five_bits)
#define CMD_HW_SEGMENT_REMAP_COL0                       (0xA0)
#define CMD_HW_SEGMENT_REMAP_COL127                     (0xA1)
#define CMD_HW_MULTIPLEX_RATIO                          (0xA8)  /* 2 commands */
#define CMD_HW_SCAN_COM0_TO_COMN1                       (0xC0)
#define CMD_HW_SCAN_COMN1_TO_COM0                       (0xC1)
#define CMD_HW_DISPLAY_OFFSET                           (0xD3)  /* 2 commands */
#define CMD_HW_COM_PINS_CONFIG                          (0xDA)  /* 2 commands */

/* timing and driving scheme setting commands */
#define VCC_65                                          (0x00)    /* used by vchomh deselect level */
#define VCC_71                                          (0x10)
#define VCC_77                                          (0x20)    /* reset value */
#define VCC_83                                          (0x30)
#define CMD_TIM_DISPLAY_CLK_DIVIDE_RATIO                (0xD5)  /* 2 commands */
#define CMD_TIM_PRECHARGE_PERIOD                        (0xD9)  /* 2 commands */
#define CMD_TIM_VCOMH_DESELECT_LEVEL                    (0xD8)  /* 2 commands */

/* advanced graphic commands */
#define DISABLE_FADE_BLINK                              (0x0)
#define ENABLE_FADE                                     (0x20)
#define ENABLE_BLINK                                    (0x30)
#define DISABLE_ZOOM                                    (0x0)
#define ENABLE_ZOOM                                     (0x1)
#define CMD_ADV_FADE_BLINK                              (0x23)  /* 3 commands */
#define CMD_ZOOM                                        (0xD6)  /* 2 commands. Must be in alternative COM pin configuration: */

/* charge pump commands */
#define DISABLE_CHARGE_PUMP                             (0x0)
#define ENABLE_CHARGE_PUMP                              (0x4)
#define CHARGE_PUMP_75                                  (0x14)
#define CHARGE_PUMP_60                                  (0x15)
#define CHARGE_PUMP_85                                  (0x94)
#define CHARGE_PUMP_90                                  (0x95)
#define CMD_PUMP_SETTING                                (0x8D)  /* 2 commands. Might require CMD_ON afterwards */

/* struct containing commands */
struct MultiCommand {
  char  cmd0;
  char  cmd1;
  char  cmd2;
  char  cmd3;
  char  cmd4;
  char  cmd5;
  char  cmd6;
  char  num_commands;
};

/* scroll functions */
struct MultiCommand cmd_scroll_h(char direction, char start_page, char time_between, char end_page, char start_col, char end_col);
struct MultiCommand cmd_scroll_hv(char direction, char start_page, char time_between, char end_page, char v_offset);
struct MultiCommand cmd_scroll_set_v_area(char num_top_fixed_rows, char num_scroll_rows);

/* address setting functions */
struct MultiCommand cmd_addr_col(char col_start, char col_end);            /* 7 bits */
struct MultiCommand cmd_addr_page(char page_start, char page_end);         /* 3 bits */

/* hardware configuration functions */
struct MultiCommand cmd_hw_multiplex_ratio(char mux_ratio);                /* 0 to (through?) 14 are invalid */
struct MultiCommand cmd_hw_display_offset(char offset);                    /* 6 bits */
struct MultiCommand cmd_hw_coms_pins_config(char com_alt_config, char com_left_right_remap);        /* 1 bit each */

/* timing and driving scheme setting functions */
struct MultiCommand cmd_tim_display_clk_divide_ratio(char div_ratio, char oscillator_freq);         /* 4 bits each */
struct MultiCommand cmd_tim_precharge_period(char phase_1_period, char phase_2_period);             /* 4 bits each */
struct MultiCommand cmd_tim_vcomh_deselect_level(char deselect_level);

/* advanced graphic functions */
struct MultiCommand cmd_adv_fade_blink(char enable, char time_interval);   /* 2 bits, 4 bits. Frames = 8 * time_interval */
struct MultiCommand cmd_zoom(char enable);

/* charge pump commands */
struct MultiCommand cmd_pump_setting();

/* TODO: enum for protocol */
signed char ssd1306_init(char protocol);

/* x < WIDTH / 2 and y < HEIGHT / 2. This is needed because we split
   the screen into two halves. The calling function / source code
   needs to keep track itself as to what half we're on. */
/* (0,0) refers to top-left corner for the half */
signed char draw_pixel(char x, char y);

signed char clear_pixel(char x, char y);

signed char invert_pixel(char x, char y);

/* Draw the frame buffer to the selected side */
signed char draw_half(ssd1306_side_t side);

/* User probably should manually call after every draw_half */
void clear_buffer();

void invert_buffer();

/* Change to enum?? */
char mirror_buffer(char axis);

void clear_display();

signed char draw_image(struct DrawableImage *image, ssd1306_side_t side);


#endif
