#include "interrupt.h"
#include "idt.h"
#include "i386.h"

void interrupt_initialize(void) {
  idt_initialize();
  i386_cli();
}

void interrupt_enable(void) {
  i386_sti();
}

void interrupt_disable(void) {
  i386_cli();
}
