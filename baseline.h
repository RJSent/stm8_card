#ifndef BASELINE_H
#define BASELINE_H

#include <stdint.h>
#include "registers.h"

#define COUNT_PER_60HZ 670
#define COUNT_PER_1MS 59        /* Oddly not 670 / 16.66 */
#define CLOCK_MEASUREMENT       /* Clock used for COUNT_PER measurements */

/* Macro for sizeof array */
#define SIZEOFARRAY(x) (sizeof(x) / sizeof(x[0]))

typedef enum Boolean { FALSE, TRUE } boolean_t;

char delay(unsigned long num);

char random();

char random_upto(int max);

unsigned int math_absolute(int val); /* return absolute value of argument */

int math_mag_decrease(int val, int amount); /* decrease magnitude of val by amount. Returns 0 if |amount| > |val| */

int math_mag_increase(int val, int amount); /* increase magnitude of val by amount. */

int math_mag_set(int val, unsigned int amount); /* sets magnitude of val to amount while maintaining sign. */

uint8_t reverse_byte(uint8_t byte);

char clk_hsi_prescaler(char divider); /* 1, 2, 4, or 8. Both CPU and peripherals */

char clk_cpu_prescaler(unsigned char divider); /* Powers of 2. <= 128. [1, 2, 4, 8, ... 128]*/

#endif
