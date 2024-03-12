#include "image.h"
#include "utility.h"
#include <stdint.h>
#include <stdio.h>
#include <to_bmp.h>

enum write_status to_bmp(FILE *out, const struct image *img) {
  struct bmp_header bmp_header = create_header(img);

  if (fwrite(&bmp_header, sizeof(struct bmp_header), 1, out) != 1) {
    fprintf(stderr, "Error while writing header!\n");
    return WRITE_ERROR;
  }
  uint8_t padding = get_padding(img->width);

  for (uint32_t i = 0; i < img->height; i++) {
    if (fwrite(img->data + img->width * i, sizeof(struct pixel), img->width,
               out) != img->width) {
      fprintf(stderr, "Error while writing data!\n");
      return WRITE_ERROR;
    }
    if (fseek(out, padding, SEEK_CUR) != 0) {
      fprintf(stderr, "Error while writing data!\n");
      return WRITE_ERROR;
    }
  }
  return WRITE_OK;
}
