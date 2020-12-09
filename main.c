// Goal:
// blink_code(char port, int *pins, int code)
// turns on blink code if high
// blink_clear(char port, int *pins)
// Toggles all pins to low

#include <stdint.h>
#include <stdlib.h>

#include "registers.h"
#include "blink_code.h"
#include "baseline.h"

#define COUNT_PER_60HZ 670
#define COUNT_PER_1MS 59        /* Oddly not 670 / 16.66 */

const char *pins[] = {"C3", "C4", "C5", "C6", NULL};

int main() {
  const char *pins[] = {"D3", "D2", "D1", "C7", "C6", "C5", "C4", "C3"};
  blink_set_pins((char**) pins);
  uint8_t num = 1;
  char reverse = 0;
    
  while (1) {
    num = ((num >> 1) & reverse) | ((num << 1) & ~reverse);
    if (num == (1 << 7)) {
      reverse = 0xFF;
    } else if (num == (1)) {
      reverse = 0;
    }
    blink_code(num);
    delay(5000);
    blink_clear();
  }
}


