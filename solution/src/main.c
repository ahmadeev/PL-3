#include "from_bmp.h"
#include "rotate.h"
#include "to_bmp.h"
#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  // Нам нужно 4 аргумента командной строки (учитывая название программы)
  if (argc != 4) {
    fprintf(
        stderr,
        "You need 3 parameters to start: <source-image> <transformed-image> "
        "<angle>\n");
    return 1;
  }
  // Парсим ввод
  char *source_image_file = argv[1];
  char *output_image_file = argv[2];
  // Перевод из строки в инт
  int64_t angle = atoi(argv[3]);
  struct image input_image = {0};

  // -------READ FROM INPUT FILE----------------
  // Открываем файл и проверям что открытие удалось (в случае неудачи возвращается NULL)
  // rb - чтение в битах
  FILE *input_file = fopen(source_image_file, "rb");
  if (!input_file) {
    fprintf(stderr, "Error while oppening source file!\n");
    return 1;
  }

  // Читаем и проверяем что чтение удалось
  enum read_status read_status = from_bmp(input_file, &input_image);
  if (read_status != READ_OK) {
    return 1;
  }
  // Закрываем вводный файл и провеяем что закрытие удалось 
  if (fclose(input_file) == EOF) {
    free(input_image.data);
    fprintf(stderr, "Error while closing file");
    return 1;
  }
  //------------------------------------------------------

  // Вращаем картинку и проверяем что поворот удался
  struct image output_image = rotate(input_image, angle);
  if (!output_image.data) {
    fprintf(stderr, "Error while creating rotated image!\n");
    return 1;
  }

  // --------------------WRITE TO OUTPUT FILE--------------
  // Открываем файл вывода и проверяем что файл открылся
  // wb - записать в битах
  FILE *output_file = fopen(output_image_file, "wb");
  if (!output_file) {
    free(output_image.data);
    fprintf(stderr, "Error while openning target file!\n");
    return 1;
  }
  // записываем в файл и проверяем
  enum write_status write_status = to_bmp(output_file, &output_image);
  free(output_image.data);
  if (write_status != WRITE_OK) {
    return 1;
  }
  // Запкрываем файл и проверяем что он закрылся
  if (fclose(output_file) == EOF) {
    fprintf(stderr, "Error while closing file!\n");
    return 1;
  }
  //------------------------------------------------------
  return 0;
}
