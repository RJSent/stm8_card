
#ifndef UART_H
#define UART_H

int uart_init(long baud_rate, long fmaster);

int uart_printf(char *format, ...);

#endif
