#include <stdlib.h>

volatile unsigned long dl;

int delay(unsigned long num) {
  for (dl = 0; dl < num; dl++);
  return 0;
}

int random(int max) {
  return rand() % (max + 1);
}
