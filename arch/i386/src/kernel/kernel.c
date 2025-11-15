#include "kernel.h"
#include "i386.h"

void kernel_initialize(void) {
  
}

void kernel_halt(void) {
  i386_cli();
  i386_hlt();
}
