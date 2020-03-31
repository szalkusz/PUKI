  /**   ===========================
  *     PUKI - Picture Utility King
  *     ===========================
  *
  *     === Image types header ===
  *
  * @authr Szalai András - kapcsolat@szalkusz.hu
  */

#ifndef TYPES
#define TYPES

typedef struct Pixel{
     unsigned char R,G,B;
} Pixel;

typedef struct Image{
     int width, height;
     Pixel **data;
} Image;

#endif
