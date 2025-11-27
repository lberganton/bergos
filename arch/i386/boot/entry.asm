%define KERNEL_STACK_SIZE 8192

extern main

section .text

global _start
_start:
  mov ebp, kernel_stack.top
  mov esp, ebp

  call main

  cli
  hlt

section .bss

kernel_stack.bottom: resb KERNEL_STACK_SIZE
kernel_stack.top:
