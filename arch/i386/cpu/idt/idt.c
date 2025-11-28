#include "idt.h"
#include "gdt.h"
#include "i386.h"
#include "kernel.h"
#include "tty.h"
#include <stddef.h>

static struct __attribute__ ((packed)) {
  uint16_t size;
  uint32_t offset;
} idt_descriptor;

static struct __attribute__ ((packed)) {
  uint64_t offset_low               : 16;
  uint64_t segment_selector         : 16;
  uint64_t reserved                 : 8;
  uint64_t type                     : 4;
  uint64_t zero                     : 1;
  uint64_t dpl                      : 2;
  uint64_t present                  : 1;
  uint64_t offset_high              : 16;
} idt_gates[IDT_MAX_GATES];

volatile IDTHandler idt_handlers[IDT_MAX_GATES];

static void handler_generic(int vector, int *error, I386Registers registers) {
  static const char *INTERRUPT_NAMES[] = {
    "#DE: Division Error",
    "#DB: Debug",
    "NMI: Non-maskable Interrupt",
    "#BP: Breakpoint",
    "#OF: Overflow",
    "#BR: Bound Range Exceeded",
    "#UD: Invalid Opcode",
    "#NM: Device Not Available",
    "#DF: Double Fault",
    "Coprocessor Segment Overrun",
    "#TS: Invalid TSS",
    "#NP: Segment Not Present",
    "#SS: Stack-Segment Fault",
    "#GP: General Protection Fault",
    "#PF: Page Fault",
    "Reserved",
    "#MF: x87 Floating-Point Exception",
    "#AC: Alignment Check",
    "#MC: Machine Check",
    "#XM: SIMD Floating-Point Exception",
    "#VE: Virtualization Exception",
    "#CP: Control Protection Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "#HV: Hypervisor Injection Exception",
    "#VC: VMM Communication Exception",
    "#SX: Security Exception",
    "Reserved"
  };

  tty_initialize();
  tty_printf("Interrupt[%d]", vector);

  if ((size_t) vector < sizeof(INTERRUPT_NAMES) / sizeof(INTERRUPT_NAMES[0])) {
    tty_printf(": %s", vector[INTERRUPT_NAMES]);
  }

  if (error != NULL) {
    tty_printf("\nError Code: [%d]", *error);
  }

  tty_printf("\n  EAX: 0x%x", registers.eax);
  tty_printf("\n  EBX: 0x%x", registers.ebx);
  tty_printf("\n  ECX: 0x%x", registers.ecx);
  tty_printf("\n  EDX: 0x%x", registers.edx);
  tty_printf("\n  ESI: 0x%x", registers.esi);
  tty_printf("\n  EDI: 0x%x", registers.edi);
  tty_printf("\n  ESP: 0x%x", registers.esp);
  tty_printf("\n  EBP: 0x%x", registers.ebp);

  kernel_halt();
}

static void gate_initialize(int vector, void *offset, GDTSelector selector, IDTGateType type, GDTRing dpl) {
  idt_gates[vector].present = 1;
  idt_gates[vector].offset_low = (uint32_t) offset & 0xffff;
  idt_gates[vector].offset_high = (uint32_t) offset >> 16;
  idt_gates[vector].type = type;
  idt_gates[vector].dpl = dpl;
  idt_gates[vector].zero = 0;
  idt_gates[vector].segment_selector = selector;
}

void idt_initialize(void) {
  idt_descriptor.size = sizeof(idt_gates) - 1;
  idt_descriptor.offset = (uint32_t) &idt_gates;

  for (size_t i = 0; i < IDT_MAX_GATES; i++) {
    idt_handlers[i] = handler_generic;
  }

  gate_initialize(0, idt_isr_0, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(1, idt_isr_1, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_TRAP32, GDT_RING_0);
  gate_initialize(2, idt_isr_2, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(3, idt_isr_3, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_TRAP32, GDT_RING_0);
  gate_initialize(4, idt_isr_4, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_TRAP32, GDT_RING_0);
  gate_initialize(5, idt_isr_5, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(6, idt_isr_6, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(7, idt_isr_7, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(8, idt_isr_8, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(9, idt_isr_9, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(10, idt_isr_10, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(11, idt_isr_11, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(12, idt_isr_12, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(13, idt_isr_13, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(14, idt_isr_14, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(16, idt_isr_16, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(17, idt_isr_17, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(18, idt_isr_18, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(19, idt_isr_19, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(20, idt_isr_20, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(21, idt_isr_21, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);

  gate_initialize(32, idt_isr_32, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(33, idt_isr_33, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(34, idt_isr_34, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(35, idt_isr_35, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(36, idt_isr_36, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(37, idt_isr_37, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(38, idt_isr_38, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(39, idt_isr_39, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(40, idt_isr_40, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(41, idt_isr_41, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(42, idt_isr_42, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(43, idt_isr_43, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(44, idt_isr_44, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(45, idt_isr_45, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(46, idt_isr_46, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);
  gate_initialize(47, idt_isr_47, GDT_SELECTOR_KERNEL_CODE, IDT_GATE_TYPE_INT32, GDT_RING_0);

  asm volatile ("lidt (%0)" :: "m" (idt_descriptor));
}

void idt_reload(void) {
  asm volatile ("lidt (%0)" :: "m" (idt_descriptor));
}

void idt_gate_set_handler(int vector, IDTHandler handler) {
  if (vector >= 0 && vector <= 21 && vector != 15) {
    kernel_panic("invalid idt gate vector");
  }
  idt_handlers[vector] = handler;
}
