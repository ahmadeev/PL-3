#include <inttypes.h>
#include <rotate.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static struct image rotate_90(const struct image source) {
  struct image output_image = {
      .height = source.width, .width = source.height, .data = NULL};
  output_image.data =
      malloc(sizeof(struct pixel) * source.height * source.width);
  if (!output_image.data) {
    return output_image;
  }
  for (uint32_t h = 0; h < source.height; h++) {
    for (uint32_t w = 0; w < source.width; w++) {
      output_image.data[(source.width - w - 1) * source.height + h] =
          source.data[h * source.width + w];
    }
  }
  return output_image;
}

struct image rotate(struct image source, int64_t angle) {
  if (angle < 0) {
    angle += 360;
  }
  uint8_t rotate_count = angle / 90;
  struct image output_image = source;
  while (rotate_count--) {
    output_image = rotate_90(source);
    free(source.data);
    source = output_image;
    if (!source.data) {
      return source;
    };
  }
  return output_image;
}
