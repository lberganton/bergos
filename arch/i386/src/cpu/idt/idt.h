#ifndef IDT_H
#define IDT_H

#include "i386.h"

#define IDT_MAX_GATES 256

typedef enum {
  IDT_GATE_TYPE_TASK    = 0x05,
  IDT_GATE_TYPE_INT16   = 0x06,
  IDT_GATE_TYPE_TRAP16  = 0x07,
  IDT_GATE_TYPE_INT32   = 0x0e,
  IDT_GATE_TYPE_TRAP32  = 0x0f,
} IDTGateType;

typedef void (*IDTHandler)(int vector, int *error, I386Registers registers);

int idt_initialize(void);
int idt_reload(void);

int idt_gate_set_handler(int vector, IDTHandler handler);

void idt_isr0(void);
void idt_isr1(void);
void idt_isr2(void);
void idt_isr3(void);
void idt_isr4(void);
void idt_isr5(void);
void idt_isr6(void);
void idt_isr7(void);
void idt_isr8(int error);
void idt_isr9(void);
void idt_isr10(int error);
void idt_isr11(int error);
void idt_isr12(int error);
void idt_isr13(int error);
void idt_isr14(int error);
void idt_isr16(void);
void idt_isr17(int error);
void idt_isr18(void);
void idt_isr19(void);
void idt_isr20(void);
void idt_isr21(int error);

#endif
