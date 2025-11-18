#ifndef I386_H
#define I386_H

#include <stdint.h>

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

#endif
