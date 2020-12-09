#include <stdlib.h>             /* NULL */
#include <stdint.h>
#include <string.h>

#include "baseline.h"
#include "blink_code.h"
#include "registers.h"
#include "gpio.h"

/* e.g. {"C3", "B7", ...} */
static char pins[MAX_PINS][2];

int blink_code(int code) {
  for (int i = 0; i < MAX_PINS; i++) {
    if ((pins[i][0]) == 0) break;
    uint8_t *base_addr = (uint8_t *)get_gpio_base(pins[i][0]);
    
    int pin = ascii_to_int(pins[i][1]);
    if (pin == -1) return -1;
    
    if (code & (1 << i)) {
      *(base_addr + ODR_OFF) |= (1 << pin);  // Latch output high
      *(base_addr + DDR_OFF) |= (1 << pin);  // Turn on output
      *(base_addr + CR1_OFF) |= (1 << pin);  // Push-pull
    } else {
      *(base_addr + ODR_OFF) &= ~(1 << pin); // Latch output low
    }
  }
  return 0;  
}

int blink_clear() {
  return blink_code(0);
}

int blink_flash(int code, int flashes) {
  blink_clear();
  for (int i = 0; i < flashes; i++) {
    blink_code(code);
    delay(15000);
    blink_clear();
    delay(15000);
  }
  return 0;
}

// Blink the code, delay, clear and return
int blink_code_clear(int code) {
  blink_code(code);
  delay(CODE_DELAY);
  blink_clear();
  return 0;
}

int blink_set_pins(char *import_pins[]) {
  for (int i = 0; i < MAX_PINS; i++) {
    if (import_pins[i] == NULL) {
      pins[i][0] = 0;
      break;
    }
    pins[i][0] = import_pins[i][0];
    pins[i][1] = import_pins[i][1];
  }
  return 0;
}
