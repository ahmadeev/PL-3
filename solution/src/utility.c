#include <stdint.h>
#include <utility.h>

#define BMP_BF_TYPE 0x4D42
#define BMP_BF_RESERVED 0
#define BMP_BI_PLANES 1
#define BMP_BI_BITCOUNT 24
#define BMP_BI_COMPRESSION 0
#define BMP_BI_XPEELSPERMETER 2834
#define BMP_BI_YPEELSPERMETER 2834
#define BMP_BI_CLRUSED 0
#define BMP_BI_CLRIMPORTANT 0


// Посчитаем выравнивание (подробно описнао в задании с лабой)
uint8_t get_padding(uint32_t width) {
  if (width % 4 == 0) {
    return 0;
  }
  return 4 - width * sizeof(struct pixel) % 4;
}

// Метод заполнения стандартного хедера
struct bmp_header create_header(const struct image *img) {
  // Отступ перед данными
  uint32_t offset = sizeof(struct bmp_header);
  // Размер файла без хедера
  uint32_t file_size = img->height * (get_padding(img->width) +
                                      img->width * sizeof(struct pixel));
  // размер файла с хедером
  uint32_t image_size = file_size + offset;

  return (struct bmp_header){.bfType = BMP_BF_TYPE, // Так называемое "магическое число" в системах юникс для бмп формата
                             .bfileSize = file_size,
                             .bfReserved = BMP_BF_RESERVED, // Пустые зарезервированные байты
                             .bOffBits = offset,
                             .biSize = offset, // Размер хедера
                             .biWidth = img->width,
                             .biHeight = img->height,
                             .biPlanes = BMP_BI_PLANES,
                             .biBitCount = BMP_BI_BITCOUNT, // Количество бит на пиксель 
                             .biCompression = BMP_BI_COMPRESSION, // Сжатие
                             .biSizeImage = image_size,
                             .biXPelsPerMeter = BMP_BI_XPEELSPERMETER, // Пиксели на метр
                             .biYPelsPerMeter = BMP_BI_YPEELSPERMETER,
                             .biClrUsed = BMP_BI_CLRUSED, // Размер таблицы цветов
                             .biClrImportant = BMP_BI_CLRIMPORTANT}; // Количество ячеек в таблице цветов
}
