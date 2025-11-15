#include "tty.h"
#include "kernel.h"

void main(void) {
  tty_initialize();
  tty_printf("Hello, world!\n");
  tty_printf("I am BergOS!\n");
  kernel_halt();
}
