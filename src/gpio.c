#include "gpio.h"
#include "registers.h"

uint64_t get_gpio_base(char port) {
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
