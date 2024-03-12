#include <from_bmp.h>
#include <stdint.h>
#include <stdio.h>
#include <utility.h>

// Метод чтения картинки
enum read_status from_bmp(FILE *in, struct image *img) {
  struct bmp_header bmp_header;
  // Создаем структуру хедера и читаем ее из файла
  // fread принимает ссылку куда нужно прочиать, сколько байт прочитать, сколько раз прочитать и откуда. И возвращает количество прочитанных объектов
  if (fread(&bmp_header, sizeof(struct bmp_header), 1, in) != 1) {
    return READ_IS_NOT_AVAILABLE;
  }
  // Заполняем структуру имедж, аллоцируя дату
  img->width = bmp_header.biWidth;
  img->height = bmp_header.biHeight;
  img->data = malloc(sizeof(struct pixel) * img->width * img->height);
  // Если маллок не сработал....
  if (!img->data) {
    fprintf(stderr, "Error while memory allocation for reading input file\n");
    return READ_INVALID_ALLOCATION;
  }

  // Устанаваливаем каретку чтения с ввода на начало данных
  // fseek принимает файл откуда читать, сколько нужно пропустить, откуда (set - начало)
  fseek(in, bmp_header.bOffBits, SEEK_SET);

  // Подсчитаем выравнивание
  uint8_t padding = get_padding(bmp_header.biWidth);

  // Читаем по количеству строк
  for (uint64_t i = 0; i < bmp_header.biHeight; i++) {
    // Читаем в массив дата с отступом по количеству строк умноженным на их длину(ширину) (мы не пишем в массив педдинг)
    // Количество объектов - biWidth, размер объекта - sizeof(struct pixel)
    // Если не прочитали - количество прочитанных объектоа (возвращаемое значение fread не равно ширине)
    if (fread(img->data + i * bmp_header.biWidth, sizeof(struct pixel),
              bmp_header.biWidth, in) != bmp_header.biWidth) {
      fprintf(stderr, "Error occupped while reading bmp file!\n");
      //Не забываем очищать аллоцированные данные
      free(img->data);
      return READ_IS_NOT_AVAILABLE;
    }
    // fseek в случае удачи возвращает 0, а в случае неудачи (например файл кончился) возвращает не 0
    if (fseek(in, padding, SEEK_CUR) != 0) {
      fprintf(stderr, "Error occupped while reading bmp file!\n");
      free(img->data);
      return READ_IS_NOT_AVAILABLE;
    }
  }
  return READ_OK;
}
