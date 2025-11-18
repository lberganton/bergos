%define GDT_SELECTOR_KERNEL_CODE 0x08
%define GDT_SELECTOR_KERNEL_DATA 0x10

section .text

global gdt_initialize
gdt_initialize:
  lgdt [GDT]

  mov ax, GDT_SELECTOR_KERNEL_DATA
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax

  jmp GDT_SELECTOR_KERNEL_CODE:.flush

.flush:
  ret

section .data

GDT:
  dw .end - .begin - 1
  dd .begin
  .begin:
    .null:        db 0x00, 0x00, 0x00, 0x00, 0x00, 0b00000000, 0b00000000, 0x00
    .kernel_code: db 0xff, 0xff, 0x00, 0x00, 0x00, 0b10011010, 0b11001111, 0x00
    .kernel_data: db 0xff, 0xff, 0x00, 0x00, 0x00, 0b10010010, 0b11001111, 0x00
GDT.end:
