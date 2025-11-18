#include "kernel.h"
#include "gdt.h"
#include "i386.h"

void kernel_initialize(void) {
  gdt_initialize();
}

void kernel_halt(void) {
  i386_cli();
  i386_hlt();
}
