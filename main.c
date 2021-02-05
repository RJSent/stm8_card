// Goal:
// blink_code(char port, int *pins, int code)
// turns on blink code if high
// blink_clear(char port, int *pins)
// Toggles all pins to low

#include "baseline.h"
#include "blink_code.h"
#include "uart.h"

int main() {
  const char *pins[] = {"D3", "D2", "D1", "C7", "C6", "C5", "C4", "C3"};
  blink_set_pins((char**) pins);
  const int baud_rate = 9600;
  const long fmaster = 16000000;

  clk_hsi_prescaler(1);
  uart_init(baud_rate, fmaster);
  
  while (1) {
    uart_printf("Binary:    %b\n\r", 8);
    uart_printf("Character: %c\n\r", 'c');
    uart_printf("Signed:    %d\n\r", -14);
    uart_printf("String:    %s\n\r", "Hi there!");
    uart_printf("Unsigned:  %u\n\r", 14);
    uart_printf("Hex:       %x\n\r", 12);

    blink_code(random_upto((1 << 8) - 1));
    delay(4000000);
  }
}




