#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>

#define MAX_FRAMES    (6) /* up to 6 frames of animation */
#define UNINITIALIZED (-1)

struct Image {
  const char width;
  const char height;
  const uint8_t *pixels;
};

struct DrawableImage {
  signed char x;
  signed char y;
  unsigned char state;
  const struct Image *images[MAX_FRAMES];
};

/* TODO create struct with size + array of pointers to return when drawing images */


#endif
