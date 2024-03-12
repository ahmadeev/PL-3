#include <image.h>
#include <stdio.h>
#include <stdlib.h>
#pragma once

/*  deserializer   */
enum read_status {
  READ_OK = 0,
  READ_IS_NOT_AVAILABLE,
  READ_INVALID_SIGNATURE,
  READ_INVALID_BITS,
  READ_INVALID_HEADER,
  READ_INVALID_ALLOCATION
  /* коды других ошибок  */
};

enum read_status from_bmp(FILE *in, struct image *img);
