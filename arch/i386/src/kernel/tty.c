#include "tty.h"
#include "vga.h"
#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>

static struct {
  size_t index;
  _Bool crlf;
} tty;

int tty_initialize(void) {
  tty_clear();
  tty.crlf = 0;
  return 0;
}

int tty_clear(void) {
  for (size_t i = 0; i < VGA_MAXY * VGA_MAXX; i++) {
    vga_write(i, ' ', VGA_COLOR_BLACK, VGA_COLOR_BLACK);
  }
  tty.index = 0;
  return 0;
}

int tty_maxy(void) {
  return VGA_MAXY;
}

int tty_maxx(void) {
  return VGA_MAXX;
}

int tty_gety(void) {
  return tty.index / VGA_MAXX;
}

int tty_getx(void) {
  return tty.index % VGA_MAXX;
}

int tty_sety(int y) {
  if (y < 0 || y >= VGA_MAXY) {
    return 1;
  }
  tty.index = y * VGA_MAXY + tty_getx();
  return 0;
}

int tty_setx(int x) {
  if (x < 0 || x >= VGA_MAXX) {
    return 1;
  }
  tty.index = tty.index - tty_getx() + x;
  return 0;
}

int tty_iscrlf(void) {
  return tty.crlf;
}

int tty_setcrlf(int status) {
  tty.crlf = status;
  return 0;
}

static void rollup(void) {
  for (size_t i = VGA_MAXX; i < VGA_MAXY * VGA_MAXX; i++) {
    char character;
    VGAColor foreground;
    VGAColor background;

    vga_read(i - VGA_MAXX, &character, &foreground, &background);
    vga_write(i - VGA_MAXX, character, foreground, background);
  }
  tty.index -= VGA_MAXX;
}

static void putchar(int ch) {
  if (tty.index >= VGA_MAXY * VGA_MAXX) {
    rollup();
  }

  switch (ch) {
    case '\r':
      tty.index -= tty_getx();
      break;
    case '\n':
      tty.index += VGA_MAXX;
      if (tty.index >= VGA_MAXY * VGA_MAXX) {
        rollup();
      }
      break;
    default:
      vga_write(tty.index, ch, VGA_COLOR_WHITE, VGA_COLOR_BLACK);
      tty.index++;
  }
}

int tty_putchar(int ch) {
  if (!tty.crlf && ch == '\n') {
    putchar('\r');
  }
  putchar(ch);
  return 0;
}

static void puts(const char *s) {
  while (*s) {
    tty_putchar(*s++);
  }
}

int tty_printf(const char *format, ...) {
  va_list args;
  va_start(args, format);

  while (*format) {
    if (*format != '%') {
      tty_putchar(*format++);
      continue;
    }

    format++;

    switch (*format) {
      case 'c':
        tty_putchar(va_arg(args, int));
        break;
      case 's':
        puts(va_arg(args, char*));
        break;
      case '%':
        tty_putchar('%');
        break;
    }

    format++;
  }

  return 0;
}
