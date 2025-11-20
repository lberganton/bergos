#include "kernel.h"
#include "gdt.h"
#include "i386.h"
#include "idt.h"
#include "tty.h"

void kernel_initialize(void) {
  gdt_initialize();
  idt_initialize();
}

void kernel_panic(int error) {
  tty_initialize();
  tty_printf("Kernel Panic! error: 0x%x", error);
  kernel_halt();
}

void kernel_halt(void) {
  i386_cli();
  i386_hlt();
}
