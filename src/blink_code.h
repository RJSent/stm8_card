#ifndef BLINK_CODE_H
#define BLINK_CODE_H

#define CODE_DELAY 50000
#define FLASH_DELAY 15000
#define MAX_PINS 8

int blink_code(int);
int blink_clear();
int blink_flash(int, int);
int blink_code_clear(int);
int blink_set_pins(char **);

#endif
