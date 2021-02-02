#ifndef BASELINE_H
#define BASELINE_H

#define COUNT_PER_60HZ 670
#define COUNT_PER_1MS 59        /* Oddly not 670 / 16.66 */
#define CLOCK_MEASUREMENT       /* Clock used for COUNT_PER measurements */

int delay(unsigned long num);

int random(int max);

int ascii_to_int(char);

/* Returns nth digit in integer num, in base b.
   e.g. int_to_digit(20, 16, 1) returns 4 */
char int_to_digit(int num, int b, int n);

/* Returns number of digits in num in base b
   e.g. num_digits(8, 2) returns 4 */
char num_digits(int num, int b);

#endif
