#ifndef I386_H
#define I386_H

#include <stdint.h>

typedef struct {
  uint16_t eax;
  uint16_t ecx;
  uint16_t edx;
  uint16_t ebx;
  uint16_t esp;
  uint16_t ebp;
  uint16_t esi;
  uint16_t edi;
} I386Registers;

static inline void i386_outb(uint16_t port, uint8_t value) {
  asm volatile ("out %%al, %%dx" :: "a" (value), "d" (port));
}

static inline uint8_t i386_inb(uint16_t port) {
  uint8_t byte;
  asm volatile ("in %%dx, %%al" : "=a" (byte) : "d" (port));
  return byte;
}

static inline void i386_cli(void) {
  asm volatile ("cli");
}

static inline void i386_sti(void) {
  asm volatile ("sti");
}

static inline void i386_hlt(void) {
  asm volatile ("hlt");
}

static inline void i386_io_wait(void) {
  i386_outb(0x80, 0x00);
}

#endif
