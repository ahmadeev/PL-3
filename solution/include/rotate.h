#include <image.h>
#include <stdint.h>
#pragma once

/* создаёт копию изображения, которая повёрнута на 90 градусов */
struct image rotate(struct image source, int64_t angle);
