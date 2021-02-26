#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>

#define MAX_FRAMES (6) /* up to 6 frames of animation */

struct Image {
  const char width;
  const char height;
  const uint8_t *pixels;
};

struct DrawableImage {
  unsigned char x;
  unsigned char y;
  unsigned char state;
  const struct Image *images[MAX_FRAMES];
};


#endif