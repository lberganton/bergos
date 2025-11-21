#include "tty.h"
#include "vga.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

static int cursor;
static bool crlf;

int tty_initialize(void) {
  tty_clear();
  crlf = false;
  return 0;
}

int tty_clear(void) {
  for (int i = 0; i < VGA_MAXY * VGA_MAXX; i++) {
    vga_write(i, ' ', VGA_COLOR_BLACK, VGA_COLOR_BLACK);
  }
  cursor = 0;
  return 0;
}

int tty_maxy(void) {
  return VGA_MAXY;
}

int tty_maxx(void) {
  return VGA_MAXX;
}

int tty_gety(void) {
  return cursor / VGA_MAXX;
}

int tty_getx(void) {
  return cursor % VGA_MAXX;
}

int tty_sety(int y) {
  if (y < 0 || y >= VGA_MAXY) {
    return 1;
  }
  cursor = y * VGA_MAXY + tty_getx();
  return 0;
}

int tty_setx(int x) {
  if (x < 0 || x >= VGA_MAXX) {
    return 1;
  }
  cursor += x - tty_getx();
  return 0;
}

int tty_iscrlf(void) {
  return crlf;
}

int tty_setcrlf(int status) {
  crlf = status;
  return 0;
}

static void scroll(void) {
  for (int i = VGA_MAXX; i < VGA_MAXY * VGA_MAXX; i++) {
    char character;
    VGAColor foreground;
    VGAColor background;

    vga_read(i, &character, &foreground, &background);
    vga_write(i - VGA_MAXX, character, foreground, background);
  }

  for (int i = VGA_MAXX * (VGA_MAXY - 1); i < VGA_MAXX * VGA_MAXY; i++) {
    vga_write(i, ' ', VGA_COLOR_BLACK, VGA_COLOR_BLACK);
  }

  cursor -= VGA_MAXX;
}

int tty_putchar(int ch) {
  if (!crlf && ch == '\n') {
    tty_putchar('\r');
  }

  switch (ch) {
    case '\r':
      cursor -= tty_getx();
      break;
    case '\n':
      cursor += VGA_MAXX;
      break;
    default:
      vga_write(cursor, ch, VGA_COLOR_WHITE, VGA_COLOR_BLACK);
      cursor++;
  }

  if (cursor >= VGA_MAXY * VGA_MAXX) {
    scroll();
  }

  return 0;
}

static void puts(const char *s) {
  while (*s) {
    tty_putchar(*s++);
  }
}

static void putint(uint32_t num, bool is_negative, int base) {
  static const char DIGITS[] = "0123456789abcdef";

  if (base > 16 || base < 1) {
    return;
  }

  char stack[sizeof(num) * 8];
  int stack_top = 0;

  do {
    stack[stack_top++] = DIGITS[num % base];
    num /= base;
  } while (num > 0);

  if (is_negative) {
    stack[stack_top++] = '-';
  }

  while (stack_top > 0) {
    tty_putchar(stack[--stack_top]);
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
      case 'd': {
        int num = va_arg(args, int);
        bool is_negative = num < 0;
        num = is_negative ? -num : num;
        putint((uint32_t) num, is_negative, 10);
      } break;
      case 'u': {
        int num = va_arg(args, unsigned int);
        putint((uint32_t) num, false, 10);
      } break;
      case 'x': {
        int num = va_arg(args, unsigned int);
        putint((uint32_t) num, false, 16);
      } break;
      case '%':
        tty_putchar('%');
        break;
    }

    format++;
  }

  return 0;
}
