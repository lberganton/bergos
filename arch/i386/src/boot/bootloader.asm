section .bootloader

[bits 16]

_start:
  mov ah, 0x0e
  mov al, '!'
  int 0x10

  hlt

times 510 - ($ - $$) db 0x00
dw 0xaa55
