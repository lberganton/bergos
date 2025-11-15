#ifndef VGA_H
#define VGA_H

#define VGA_MAXY 25
#define VGA_MAXX 80

typedef enum {
  VGA_COLOR_BLACK         = 0b0000,
  VGA_COLOR_BLUE          = 0b0001,
  VGA_COLOR_GREEN         = 0b0010,
  VGA_COLOR_CYAN          = 0b0011,
  VGA_COLOR_RED           = 0b0100,
  VGA_COLOR_MAGENTA       = 0b0101,
  VGA_COLOR_BROWN         = 0b0110,
  VGA_COLOR_LIGHT_GRAY    = 0b0111,
  VGA_COLOR_DARK_GRAY     = 0b1000,
  VGA_COLOR_LIGHT_BLUE    = 0b1001,
  VGA_COLOR_LIGHT_GREEN   = 0b1010,
  VGA_COLOR_LIGHT_CYAN    = 0b1011,
  VGA_COLOR_LIGHT_RED     = 0b1100,
  VGA_COLOR_LIGHT_MAGENTA = 0b1101,
  VGA_COLOR_YELLOW        = 0b1110,
  VGA_COLOR_WHITE         = 0b1111,
} VGAColor;

int vga_write(int index, char character, VGAColor foreground, VGAColor background);

#endif
