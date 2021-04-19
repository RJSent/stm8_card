#include <stdint.h>

#include "gpio.h"

#include "registers.h"
#include "uart.h"

static uintptr_t _get_gpio_base(char port) {
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
  volatile uint8_t *base_addr = (uint8_t *) _get_gpio_base(pin->port);
  bool input = *(base_addr + DDR_OFF) & ((1 << pin->num) >> pin->num);
  bool cr1  =  *(base_addr + CR1_OFF) & ((1 << pin->num) >> pin->num);
  gpio_mode_t mode;
  if (input) {
    mode = cr1 ? GPIO_INPUT_PULLUP : GPIO_INPUT_FLOAT;
  } else {
    mode = cr1 ? GPIO_OUTPUT_PUSH_PULL : GPIO_OUTPUT_OPEN_DRAIN;
  }
  return mode;
}

void gpio_mode(gpio_pin_t *pin, gpio_mode_t mode) {
  volatile uint8_t *base_addr = (uint8_t *) _get_gpio_base(pin->port);
  uart_printf("setting mode for pin 0x%x\n\r", pin);
  uart_printf("port %c\n\r", pin->port);
  uart_printf("num %d\n\r", pin->num);
  uart_printf("base_addr %x\n\r", base_addr);
  switch (mode) {
  case GPIO_INPUT_FLOAT:
    *(base_addr + DDR_OFF) &= ~(1 << pin->num); // Turn on input
    uart_printf("CR1_ADDR %x\n\r", base_addr + CR1_OFF);
    uart_printf("cr1 b4 %b\n\r", *(base_addr + CR1_OFF));
    /* seems to fail for pd1, where reset is pullup. dumping periph
       bytes with swim shows reset value, but printing value of
       register shows reset value. However periph is almost definitely
       pulled-up physically. */
    *(base_addr + CR1_OFF) &= ~(1 << pin->num); // float
    uart_printf("cr1 af %b\n\r", *(base_addr + CR1_OFF));
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
  uart_printf("----\n\r");

}

/* TODO: rework to use lookup table and only pass this a pin # */
/* functional */
gpio_data_t gpio_read(gpio_pin_t *pin) {
  gpio_mode_t mode = _gpio_mode_read(pin);
  /* can't use assert statements without defining putchar and using stdio */
  /* assert(mode == GPIO_INPUT_FLOAT || mode == GPIO_INPUT_PULLUP); */
  volatile uint8_t *base_addr = (uint8_t *) _get_gpio_base(pin->port);
  return (*(base_addr + IDR_OFF) & (1 << pin->num)) != 0;
}

/* functional */
void gpio_write(gpio_pin_t *pin, gpio_data_t val) {
  gpio_mode_t mode = _gpio_mode_read(pin);
  /* can't use assert statements without defining putchar and using stdio */
  /* assert(mode == GPIO_OUTPUT_PUSH_PULL || mode == GPIO_OUTPUT_OPEN_DRAIN); */
  volatile uint8_t *base_addr = (uint8_t *) _get_gpio_base(pin->port);
  if (val) {
    *(base_addr + ODR_OFF) |= (1 << pin->num);  // Latch output high
  } else {
    *(base_addr + ODR_OFF) &= ~(1 << pin->num); // Latch output high
  }

}


