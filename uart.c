#include <stdarg.h>             /* flycheck has issue parsing stdarg.h */
#include <stdint.h>
#include <stdlib.h>

#include "registers.h"
#include "uart.h"

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

int uart_putc(char c) {
  uint64_t base_addr = UART1_BASE; /* hardcoded for now */
  volatile uint8_t* dr_addr = (uint8_t*) base_addr + UART_DR_OFF;
  volatile uint8_t* sr_addr = (uint8_t*) base_addr + UART_SR_OFF;

  while (!(*sr_addr & (1 << 7))); /* Wait until previous transmission done */

  *dr_addr = c;
  return 0;
}

/* Based on
   hackerearth.com/practice/notes/know-our-printf-variable-number-of-arguments-to-a-function */
int uart_printf(char *format, ...) {
  va_list ap;
  char *p, *sval;
  int ival;
  va_start(ap, format);
  for (p = format; *p; p++) {
    if (*p != '%') {
      uart_putc(*p);
      continue;
    }
    int buf[16];
    switch(*++p) {
    case 'b':
      ival = va_arg(ap, int);
      _uitoa(ival, buf, 2);     /* sdcc nonstandard stdlib extension */
      uart_printf("%s", buf);
      break;
    case 'c':
      ival = va_arg(ap, int);
      uart_putc(ival);
      break;
    case 'd':
    case 'i':
      ival = va_arg(ap, int);
      _itoa(ival, buf, 10);
      uart_printf("%s", buf);
      break;
    case 's':
      for (sval = va_arg(ap, char *); *sval; sval++)
	uart_putc(*sval);
      break;
    case 'u':
      ival = va_arg(ap, int);
      _uitoa(ival, buf, 10);
      uart_printf("%s", buf);
      break;
    case 'x':
      ival = va_arg(ap, int);
      _uitoa(ival, buf, 16);
      uart_printf("%s", buf);
      break;
    default:
      uart_putc(*p);
      break;
    }
  }
  va_end(ap);
  return 0;
}
