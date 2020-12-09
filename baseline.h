#ifndef BASELINE_H
#define BASELINE_H

#define COUNT_PER_60HZ 670
#define COUNT_PER_1MS 59        /* Oddly not 670 / 16.66 */
#define CLOCK_MEASUREMENT       /* Clock used for COUNT_PER measurements */

int delay(unsigned long num);

int random(int max);

int ascii_to_int(char);

#endif
