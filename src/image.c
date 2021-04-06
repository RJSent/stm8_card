#include "image.h"

boolean_t drawable_overlap(const struct DrawableImage* img1, const struct DrawableImage* img2) {
  /* check if img2 is right and inside of img1 */
  if (img1->x <= img2->x && img1->x + img1->images[img1->state]->width >= img2->x) {
    if (img1->y <= img2->y && img1->y + img1->images[img1->state]->height >= img2->y) {
      return TRUE;
    }
  }
  /* check if img1 is right and inside of img2 */
  if (img2->x <= img1->x && img2->x + img2->images[img2->state]->width >= img1->x) {
    if (img2->y <= img1->y && img2->y + img2->images[img2->state]->height >= img1->y) {
      return TRUE;
    }
  }

  return FALSE;
}
