  /**   ===========================
  *     PUKI - Picture Utility King
  *     ===========================
  *
  *     === Image IO header ===
  *
  * @authr Szalai András - kapcsolat@szalkusz.hu
  */

#ifndef IO
#define IO

#include "img_types.h"
#include <stdbool.h>

Image *ReadImg(char *fileName);
bool SaveImg(char *fileName, Image *img);

#endif
