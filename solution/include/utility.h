#include <image.h>
#include <stdint.h>
#pragma once

uint8_t get_padding(uint32_t width);
struct bmp_header create_header(const struct image *img);
