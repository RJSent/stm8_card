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

#define UART1_BASE      0x005230
/* #define UART2_BASE      0x005230 */
/* #define UART3_BASE      0x005230 */
/* #define UART4_BASE      0x005230 */
#define UART_SR_OFF     0x00     // Status
#define UART_DR_OFF     0x01     // Data
#define UART_BRR1_OFF   0x02     // Clock divider 1
#define UART_BRR2_OFF   0x03     // Clock divider 2
#define UART_CR1_OFF    0x04     // Control 1
#define UART_CR2_OFF    0x05     // Control 2

int uart_init(long baud_rate, long fmaster) {
  uint32_t uart_div = fmaster / baud_rate;
  uint64_t base_addr = UART1_BASE;

  // BRR2 should be programmed before BRR1
  *((uint8_t*) base_addr + UART_BRR2_OFF) = (0xF000 & uart_div) >> 8 | (0x000F & uart_div);
  *((uint8_t*) base_addr + UART_BRR1_OFF) = (0x0F00 & uart_div) >> 4 | (0x00F0 & uart_div) >> 4;

  *((uint8_t*) base_addr + UART_BRR2_OFF) = 0x02;
  *((uint8_t*) base_addr + UART_BRR1_OFF) = 0x68;

  /* Transmit mode */
  *((uint8_t*) base_addr + UART_CR2_OFF) |= (1 << 3);

  /* Break characters */
  /* *((uint8_t*) base_addr + UART_CR2_OFF) |= (1); */
  return 0;
}

/* uint64_t uart_get_base(char select) { */
/*   switch (select) { */
/*   case 1: */
/*     return UART1_BASE; */
/*   case 2: */
/*     return UART2_BASE; */
/*   case 3: */
/*     return UART3_BASE; */
/*   case 4: */
/*     return UART4_BASE: */
/*   default: */
/*     return NULL */
/*   } */
/* } */

int uart_one_char(char hi) {
  uint64_t base_addr = UART1_BASE;
  uint8_t* dr_addr = (uint8_t*) base_addr + UART_DR_OFF;
  uint8_t* sr_addr = (uint8_t*) base_addr + UART_SR_OFF;

  while(!(*sr_addr & (1 << 7))); /* Wait until previous transmission done */

  *dr_addr = hi;
  return 0;
}

int uart_transmit(char *message) {
  uint64_t base_addr = UART1_BASE;
  uint8_t* sr_addr = (uint8_t*) base_addr + UART_SR_OFF;
  
  while(*message != '\0') {
    uart_one_char(*message);
    message++;
  }
  return 0;
}

/* This method will eliminate the fHSI = fHSI / 8 prescaler. (So
fmaster = fHSI = 2MHz). This divided fmaster is sent to the UART,
where we further divide it using the BRR1 and BRR2 registers. The
problem is 2Mhz / 0x682 (my divider) should give a baud rate of 1200,
but what I actually got was 120. When I removed the prescaler, it
worked as expected, 9600 baud rate with a fmaster of 16Mhz and divider
of 0x682. */
#define CLK_CKDIVR (uint8_t*)0x0050C6

int clk_prescaler() {
  *CLK_CKDIVR = (!0x18) & (*CLK_CKDIVR);
}

int main() {
  const char *pins[] = {"D3", "D2", "D1", "C7", "C6", "C5", "C4", "C3"};
  blink_set_pins((char**) pins);
  const int baud_rate = 9600;
  const long fmaster = 16000000;
  char *message = "Hello world!\n\r";

  clk_prescaler();

  uart_init(baud_rate, fmaster);
  blink_code(5);
    
    
  while (1) {
    uart_transmit(message);
    blink_code(rand());
    delay(100000);
  }
}




