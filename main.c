// Goal:
// blink_code(char port, int *pins, int code)
// turns on blink code if high
// blink_clear(char port, int *pins)
// Toggles all pins to low

#include "baseline.h"
#include "blink_code.h"
#include "uart.h"


#define CLK_CKDIVR2 (char*)0x0050C6

/* int clk_prescaler() { */
/*   *CLK_CKDIVR2 = (!0x18) & (*CLK_CKDIVR2); */

/*   return 0; */
/* } */



int main() {
  const char *pins[] = {"D3", "D2", "D1", "C7", "C6", "C5", "C4", "C3"};
  blink_set_pins((char**) pins);
  const int baud_rate = 9600;
  const long fmaster = 16000000;
  char *message = "Hello world!\n\r";
  char *message2 = "How are you?";

  /* clk_prescaler(); */

  clk_hsi_prescaler(1);

  uart_init(baud_rate, fmaster);
  blink_code(5);
  
  while (1) {
    uart_printf("%s\n\r", message2);
    uart_printf("Value is %d\n\r", 3);
    //    uart_printf("hello %d", 10);
    blink_code(random_upto((1 << 8) - 1));
    /* delay(100000); */
  }
}




