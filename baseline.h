#ifndef BASELINE_H
#define BASELINE_H

#include <stdint.h>
#include "registers.h"

#define COUNT_PER_60HZ 670
#define COUNT_PER_1MS 59        /* Oddly not 670 / 16.66 */
#define CLOCK_MEASUREMENT       /* Clock used for COUNT_PER measurements */

int delay(unsigned long num);

int random();

int random_upto(int max);

uint8_t reverse_byte(uint8_t byte);

int clk_hsi_prescaler(int divider); /* 1, 2, 4, or 8. Both CPU and peripherals */

int clk_cpu_prescaler(int divider); /* Powers of 2. <= 128. [1, 2, 4, 8, ... 128]*/

#endif
