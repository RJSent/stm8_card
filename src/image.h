#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>
#include "baseline.h"

#define MAX_FRAMES    (4) /* up to 4 frames of animation */
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

/* returns TRUE if two drawable images overlap. */
/* TODO: Test this */
boolean_t drawable_overlap(const struct DrawableImage* img1, const struct DrawableImage* img2);

/* TODO create struct with size + array of pointers to return when drawing images */


#endif
