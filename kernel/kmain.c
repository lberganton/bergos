#include "tty.h"

void kmain(void) {
  static const char *msg = "Hello, world!\n";
  static const char *msg2 = "I am BergOS!\n";

  tty_initialize();

  while (*msg) {
    tty_putchar(*msg++);
  }

  while (*msg2) {
    tty_putchar(*msg2++);
  }

  while (1);
}
