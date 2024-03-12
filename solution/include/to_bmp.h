#include <image.h>
#include <stdio.h>
#pragma once

/*  serializer   */
enum write_status {
  WRITE_OK = 0,
  WRITE_ERROR
  /* коды других ошибок  */
};

enum write_status to_bmp(FILE *out, struct image const *img);
