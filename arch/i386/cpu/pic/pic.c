#include "pic.h"
#include "i386.h"

#define CASCADE_IRQ (1 << 2)

void pic_initialize(void) {
  i386_outb(PIC_PORT_1_COMMAND, PIC_ICW1_INIT | PIC_ICW1_ICW4);
  i386_io_wait();

  i386_outb(PIC_PORT_2_COMMAND, PIC_ICW1_INIT | PIC_ICW1_ICW4);
  i386_io_wait();

  i386_outb(PIC_PORT_1_DATA, PIC_GATE_VECTOR_OFFSET);
  i386_io_wait();

  i386_outb(PIC_PORT_2_DATA, PIC_GATE_VECTOR_OFFSET + 8);
  i386_io_wait();

  i386_outb(PIC_PORT_1_DATA, CASCADE_IRQ);
  i386_io_wait();

  i386_outb(PIC_PORT_2_DATA, 2);
  i386_io_wait();

  i386_outb(PIC_PORT_1_DATA, PIC_ICW4_8086);
  i386_io_wait();

  i386_outb(PIC_PORT_2_DATA, PIC_ICW4_8086);
  i386_io_wait();

  pic_enable();
}

void pic_enable(void) {
  i386_outb(PIC_PORT_1_DATA, 0x00);
  i386_outb(PIC_PORT_2_DATA, 0x00);
}

void pic_disable(void) {
  i386_outb(PIC_PORT_1_DATA, 0xff);
  i386_outb(PIC_PORT_2_DATA, 0xff);
}

void pic_send_eoi(int irq) {
  if (irq >= 8) {
    i386_outb(PIC_PORT_2_COMMAND, PIC_COMMAND_EOI);
  }
  i386_outb(PIC_PORT_1_COMMAND, PIC_COMMAND_EOI);
}
