#include "vga.h"
#include "i386.h"
#include <stdint.h>
#include <stddef.h>

#define VGA_MEMORY ((uint16_t*) 0xb8000)

int vga_write(int index, char character, VGAColor foreground, VGAColor background) {
  if (index < 0 || index >= VGA_MAXY * VGA_MAXX) {
    return 1;
  }

  VGA_MEMORY[index] = (uint16_t) character | foreground << 8 | (background << 12);
  return 0;
}

int vga_read(int index, char *character, VGAColor *foreground, VGAColor *background) {
  if (index < 0 || index >= VGA_MAXY * VGA_MAXX) {
    return 1;
  }

  if (character != NULL) {
    *character = (char) VGA_MEMORY[index];
  }
  if (foreground != NULL) {
    *foreground = (VGAColor) VGA_MEMORY[index] >> 8 & 0xf;
  }
  if (background != NULL) {
    *background = (VGAColor) VGA_MEMORY[index] >> 12 & 0xf;
  }

  return 0;
}

int vga_cursor_enable(int cursor_start, int cursor_end) {
  if (cursor_start < 0 || cursor_start >= 16 || cursor_end < 0 || cursor_end >= 16) {
    return 1;
  }

  i386_outb(VGA_REGISTER_CRT_ADDR, VGA_REGISTER_CRT_INDEX_CURSOR_START);
  cursor_start |= i386_inb(VGA_REGISTER_CRT_DATA) & 0b100000;
  i386_outb(VGA_REGISTER_CRT_DATA, cursor_start);

  i386_outb(VGA_REGISTER_CRT_ADDR, VGA_REGISTER_CRT_INDEX_CURSOR_END);
  cursor_end |= i386_inb(VGA_REGISTER_CRT_DATA) & 0b1100000;
  i386_outb(VGA_REGISTER_CRT_DATA, cursor_end);

  return 0;
}

int vga_cursor_disable(void) {
  i386_outb(VGA_REGISTER_CRT_ADDR, VGA_REGISTER_CRT_INDEX_CURSOR_START);
  i386_outb(VGA_REGISTER_CRT_DATA, 0b100000);
  return 0;
}

int vga_cursor_set_position(int index) {
  if (index < 0 || index >= VGA_MAXY * VGA_MAXX) {
    return 1;
  }

  i386_outb(VGA_REGISTER_CRT_ADDR, VGA_REGISTER_CRT_INDEX_CURSOR_LOW);
  i386_outb(VGA_REGISTER_CRT_DATA, index);

  i386_outb(VGA_REGISTER_CRT_ADDR, VGA_REGISTER_CRT_INDEX_CURSOR_HIGH);
  i386_outb(VGA_REGISTER_CRT_DATA, index >> 8);

  return 0;
}
