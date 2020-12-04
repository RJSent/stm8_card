// Goal:
// blink_code(char port, int *pins, int code)
// turns on blink code if high
// blink_clear(char port, int *pins)
// Toggles all pins to low

#include <stdint.h>
#include "registers.h"

volatile unsigned long int dl;
const uint8_t num_pins = 4;
const uint8_t pins[] = {3, 4, 5, 6};
const uint32_t flash_delay = 15000;
const uint32_t code_delay = 50000;

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

int8_t blink_code(char port, const uint8_t pins[], uint8_t num_pins, uint8_t code) {
  uint8_t *base_addr = (uint8_t *)get_gpio_base(port);
  if (base_addr == 0) return -1;
  
  for (int i = 0; i < num_pins; i++) {
    if (pins[i] > 7) return -1;
    
    if (code & (1 << i)) {
      *(base_addr + ODR_OFF) |= (1 << pins[i]);  // Latch output high
      *(base_addr + DDR_OFF) |= (1 << pins[i]);  // Turn on output
      *(base_addr + CR1_OFF) |= (1 << pins[i]);  // Push-pull
    } else {
      *(base_addr + ODR_OFF) &= ~(1 << pins[i]); // Latch output low
    }
  }
  return 0;  
}

int8_t blink_clear(char port, const uint8_t pins[], uint8_t num_pins) {
  return blink_code(port, pins, num_pins, 0);
}

int8_t delay(uint32_t num) {
  for (dl = 0; dl < num; dl++);
  return 0;
}

int8_t blink_flash(char port, const uint8_t pins[], uint8_t num_pins, uint8_t flashes, uint8_t code) {
  for (int i = 0; i < flashes; i++) {
    blink_code(port, pins, num_pins, code);
    delay(15000);
    blink_clear(port, pins, num_pins);
    delay(15000);
  }
  return 0;
}

// Blink the code, delay, clear and return
int8_t blink_code_clear(char port, const uint8_t pins[], uint8_t num_pins, uint8_t code) {
  blink_code(port, pins, num_pins, code);
  delay(code_delay);
  blink_clear(port, pins, num_pins);
  return 0;
}

int main() {
  
  while (1) {
    /* blink_code('C', pins, num_pins, 13); */
    /* delay(50000); */
    /* blink_clear('C', pins, num_pins); */
    /* delay(50000); */
    /* blink_code('C', pins, num_pins, 3); */
    /* delay(50000); */
    /* blink_clear('C', pins, num_pins); */
    /* delay(50000); */
    /* blink_flash('C', pins, num_pins, 2, 10); */
    /* delay(50000); */
    blink_code_clear('C', pins, num_pins, 13);
    blink_code_clear('C', pins, num_pins, 2);
  }
}

