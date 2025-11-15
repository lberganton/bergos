#include "kernel.h"
#include "tty.h"

void main(void) {
  kernel_initialize();

  tty_initialize();

  tty_printf("Hello, world!\n");
  tty_printf("I am BergOS!\n");

  kernel_halt();
}
