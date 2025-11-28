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

void idt_initialize(void);
void idt_reload(void);

void idt_gate_set_handler(int vector, IDTHandler handler);

void idt_isr_0(void);
void idt_isr_1(void);
void idt_isr_2(void);
void idt_isr_3(void);
void idt_isr_4(void);
void idt_isr_5(void);
void idt_isr_6(void);
void idt_isr_7(void);
void idt_isr_8(int error);
void idt_isr_9(void);
void idt_isr_10(int error);
void idt_isr_11(int error);
void idt_isr_12(int error);
void idt_isr_13(int error);
void idt_isr_14(int error);
void idt_isr_16(void);
void idt_isr_17(int error);
void idt_isr_18(void);
void idt_isr_19(void);
void idt_isr_20(void);
void idt_isr_21(int error);

#endif
