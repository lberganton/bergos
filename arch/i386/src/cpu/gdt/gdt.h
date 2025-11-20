#ifndef GDT_H
#define GDT_H

typedef enum {
  GDT_RING_0 = 0x00,
  GDT_RING_1 = 0x01,
  GDT_RING_2 = 0x02,
  GDT_RING_3 = 0x03,
} GDTRing;

typedef enum {
  GDT_SELECTOR_KERNEL_CODE = 0x08,
  GDT_SELECTOR_KERNEL_DATA = 0x10,
} GDTSelector;

int gdt_initialize(void);

#endif
