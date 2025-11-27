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
  asm volatile ("movw %[port],  %%dx  \n"
                "movb %[value], %%al  \n"
                "outb %%al,     %%dx  \n"
                :
                : [port] "r" (port), [value] "r" (value)
                : "al", "dx"
  );
}

static inline uint8_t i386_inb(uint16_t port) {
  uint8_t byte;
  asm volatile ("movw %[port],  %%dx    \n"
                "inb  %%dx,     %%al    \n"
                "movb %%al,     %[byte] \n"
                : [byte] "=r" (byte)
                : [port] "r" (port)
                : "al", "dx"
  );
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
