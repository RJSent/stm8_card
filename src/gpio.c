#include <stdint.h>

#include "gpio.h"

/* registers */
#define ODR_OFF 0x0000
#define IDR_OFF 0x0001
#define DDR_OFF 0x0002
#define CR1_OFF 0x0003
#define CR2_OFF 0x0004

#define PA_BASE ((volatile uint8_t*)0x5000)
#define PB_BASE ((volatile uint8_t*)0x5005)
#define PC_BASE ((volatile uint8_t*)0x500A)
#define PD_BASE ((volatile uint8_t*)0x500F)
#define PE_BASE ((volatile uint8_t*)0x5014)
#define PF_BASE ((volatile uint8_t*)0x5019)

static volatile uint8_t * _get_gpio_base(char port) {
  switch (port) {
  case 'A':
    return PA_BASE;
  case 'B':
    return PB_BASE;
  case 'C':
    return PC_BASE;
  case 'D':
    return PD_BASE;
  case 'E':
    return PE_BASE;
  case 'F':
    return PF_BASE;
  default:
    return 0;
  }
}

/* returns mode of pin */
static gpio_mode_t _gpio_mode_read(gpio_pin_t *pin) {
  volatile uint8_t *base_addr = _get_gpio_base(pin->port);
  bool input = *(base_addr + DDR_OFF) & ((1 << pin->num) >> pin->num);
  bool cr1  =  *(base_addr + CR1_OFF) & ((1 << pin->num) >> pin->num);
  gpio_mode_t mode;
  if (input) {
    mode = cr1 ? GPIO_INPUT_PULLUP     : GPIO_INPUT_FLOAT;
  } else {
    mode = cr1 ? GPIO_OUTPUT_PUSH_PULL : GPIO_OUTPUT_OPEN_DRAIN;
  }
  return mode;
}

void gpio_mode(gpio_pin_t *pin, gpio_mode_t mode) {
  volatile uint8_t *base_addr = _get_gpio_base(pin->port);
  switch (mode) {
  case GPIO_INPUT_FLOAT:
    *(base_addr + DDR_OFF) &= ~(1 << pin->num); // Turn on input
    *(base_addr + CR1_OFF) &= ~(1 << pin->num); // float
    break;
  case GPIO_INPUT_PULLUP:
    *(base_addr + DDR_OFF) &= (~(1 << pin->num)); // Turn on input
    *(base_addr + CR1_OFF) |= (1 << pin->num);    // interal pullup
    break;
  case GPIO_OUTPUT_PUSH_PULL:
    *(base_addr + DDR_OFF) |=  (1 << pin->num); // Turn on output
    *(base_addr + CR1_OFF) |=  (1 << pin->num); // Push-pull
    break;
  default:
    /* TODO: replace with ifndef NDEBUG? */
#ifdef UART_H
    uart_printf("Invalid gpio input in __FUNCTION__");
#endif
    break;
  }
}

/* TODO: rework to use lookup table and only pass this a pin # */
gpio_data_t gpio_read(gpio_pin_t *pin) {
  /* gpio_mode_t mode = _gpio_mode_read(pin); */
  /* can't use assert statements without defining putchar and using stdio */
  /* assert(mode == GPIO_INPUT_FLOAT || mode == GPIO_INPUT_PULLUP); */
  volatile uint8_t *base_addr = _get_gpio_base(pin->port);
  return (*(base_addr + IDR_OFF) & (1 << pin->num)) != 0;
}

void gpio_write(gpio_pin_t *pin, gpio_data_t val) {
  /* gpio_mode_t mode = _gpio_mode_read(pin); */
  /* can't use assert statements without defining putchar and using stdio */
  /* assert(mode == GPIO_OUTPUT_PUSH_PULL || mode == GPIO_OUTPUT_OPEN_DRAIN); */
  volatile uint8_t *base_addr = _get_gpio_base(pin->port);
  if (val) {
    *(base_addr + ODR_OFF) |= (1 << pin->num);  // Latch output high
  } else {
    *(base_addr + ODR_OFF) &= ~(1 << pin->num); // Latch output high
  }

}


