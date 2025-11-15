#include "vga.h"
#include <stdint.h>

#define VGA_MEMORY ((uint16_t*) 0xb8000)

int vga_write(int index, char character, VGAColor foreground, VGAColor background) {
  if (index < 0 || index >= VGA_MAXY * VGA_MAXX) {
    return 1;
  }

  *(VGA_MEMORY + index) = (uint16_t) character | foreground << 8 | (background << 12);
  return 0;
}
