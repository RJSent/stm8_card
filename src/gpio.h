#ifndef GPIO_H
#define GPIO_H

#include <stdbool.h>

/* TODO: Incorporate with BSP somehow? BSP should probably specify
   available modes. */
typedef enum gpio_mode {
  GPIO_INPUT_FLOAT, GPIO_INPUT_PULLUP, GPIO_OUTPUT_OPEN_DRAIN, GPIO_OUTPUT_PUSH_PULL,
} gpio_mode_t;

typedef struct gpio_pin {
  const char port;              /* A, B, C, etc */
  const char num;               /* 0, 1, 2, etc */
} gpio_pin_t;

typedef bool gpio_data_t;

void gpio_mode(gpio_pin_t *pin, gpio_mode_t mode);

/* Undefined if called on pin in output mode */
gpio_data_t gpio_read(gpio_pin_t *pin);

void gpio_write(gpio_pin_t *pin, gpio_data_t val);

#endif
