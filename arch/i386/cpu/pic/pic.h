#ifndef PIC_H
#define PIC_H

#define PIC_GATE_VECTOR_OFFSET 32

typedef enum {
  PIC_PORT_1_COMMAND  = 0x20,
  PIC_PORT_1_DATA     = 0x21,
  PIC_PORT_2_COMMAND  = 0xa0,
  PIC_PORT_2_DATA     = 0xa1,
} PICPort;

typedef enum {
  PIC_ICW1_ICW4       = 0x01,
  PIC_ICW1_SINGLE     = 0x02,
  PIC_ICW1_INTERVAL4  = 0x04,
  PIC_ICW1_LEVEL      = 0x08,
  PIC_ICW1_INIT       = 0x10,

  PIC_ICW4_8086       = 0x01,
  PIC_ICW4_AUTO       = 0x02,
  PIC_ICW4_BUF_SLAVE  = 0x08,
  PIC_ICW4_BUF_MASTER = 0x0c,
  PIC_ICW4_SFNM       = 0x10,
} PICICW;

typedef enum {
  PIC_COMMAND_EOI     = 0x20,
} PICCommand;

void pic_initialize(void);
void pic_enable(void);
void pic_disable(void);
void pic_send_eoi(int irq);

#endif
