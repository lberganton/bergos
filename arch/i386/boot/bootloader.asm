%define KERNEL_SIZE   (64 * 1024 - 512)
%define KERNEL_OFFSET 0x7e00

section .bootloader

extern _start

[bits 16]
set_segmentation:
  xor ax, ax
  mov ds, ax
  mov es, ax
  mov ss, ax

set_stack:
  mov bp, 0x7c00
  mov sp, bp

set_video_mode:
  mov ah, 0x00
  mov al, 0x03
  int 0x10

read_kernel:
  mov ah, 0x42
  mov si, DAP
  int 0x13

  jnc load_gdt

  mov ah, 0x13
  mov al, 0x01
  mov bp, ERROR_KERNEL
  mov cx, ERROR_KERNEL_LEN
  mov bl, 0x0f
  xor dx, dx
  int 0x10

  cli
  hlt

load_gdt:
  cli
  lgdt [GDT]

enable_protected_mode:
  mov eax, cr0
  or eax, 0x01
  mov cr0, eax

  mov ax, (GDT.data - GDT.begin)
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax

  jmp (GDT.code - GDT.begin):_start

DAP:
  db 0x10
  db 0x00
  dw KERNEL_SIZE / 512
  dw KERNEL_OFFSET
  dw 0x0000
  dd 0x0001
  dd 0x0000
DAP.end:

GDT:
  dw .end - .begin - 1
  dd .begin
  .begin:
    .null: db 0x00, 0x00, 0x00, 0x00, 0x00, 0b00000000, 0b00000000, 0x00
    .code: db 0xff, 0xff, 0x00, 0x00, 0x00, 0b10011010, 0b11001111, 0x00
    .data: db 0xff, 0xff, 0x00, 0x00, 0x00, 0b10010010, 0b11001111, 0x00
GDT.end:

ERROR_KERNEL: db "Error: failed to read kernel"
ERROR_KERNEL_LEN EQU $ - ERROR_KERNEL

times 510 - ($ - $$) db 0x00
dw 0xaa55
