#include "kernel.h"
#include "gdt.h"
#include "i386.h"
#include "idt.h"
#include "tty.h"
#include <stddef.h>

void kernel_initialize(void) {
  gdt_initialize();
  idt_initialize();
}

void kernel_panic(const char *msg) {
  tty_initialize();
  tty_printf("kernel panic");
  if (msg == NULL) {
    tty_printf("!");
  }
  else {
    tty_printf(": %s", msg);
  }
  kernel_halt();
}

void kernel_halt(void) {
  i386_cli();
  i386_hlt();
}
