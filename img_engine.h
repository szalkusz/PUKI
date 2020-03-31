  /**   ===========================
  *     PUKI - Picture Utility King
  *     ===========================
  *
  *     === Image engine header ===
  *
  * @authr Szalai András - kapcsolat@szalkusz.hu
  */

#ifndef ENGINE
#define ENGINE

#include "img_types.h"

Image * Grayscale(Image *img);
Image * Darken(Image *img);
Image * Lighten(Image *img);
Image * Blur(Image *img);
Image * Sharpen(Image *img);

#endif
