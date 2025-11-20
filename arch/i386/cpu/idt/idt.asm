extern idt_handlers

%macro PUSH_NO_ERROR_CODE 1
  global idt_isr%1
  idt_isr%1:
    push eax
    push ecx
    push edx
    push ebx
    push esp
    push ebp
    push esi
    push edi

    push 0x00
    push %1

    call [idt_handlers + 4 * %1]

    add esp, 40
    iret
%endmacro

%macro PUSH_ERROR_CODE 1
  global idt_isr%1
  idt_isr%1:
    push eax
    push ecx
    push edx
    push ebx
    push esp
    push ebp
    push esi
    push edi

    mov eax, esp
    add eax, 28
    push eax
    push %1

    call [idt_handlers + 4 * %1]

    add esp, 44
    iret
%endmacro

section .text

PUSH_NO_ERROR_CODE 0
PUSH_NO_ERROR_CODE 1
PUSH_NO_ERROR_CODE 2
PUSH_NO_ERROR_CODE 3
PUSH_NO_ERROR_CODE 4
PUSH_NO_ERROR_CODE 5
PUSH_NO_ERROR_CODE 6
PUSH_NO_ERROR_CODE 7
PUSH_ERROR_CODE 8
PUSH_NO_ERROR_CODE 9
PUSH_ERROR_CODE 10
PUSH_ERROR_CODE 11
PUSH_ERROR_CODE 12
PUSH_ERROR_CODE 13
PUSH_ERROR_CODE 14
PUSH_NO_ERROR_CODE 16
PUSH_ERROR_CODE 17
PUSH_NO_ERROR_CODE 18
PUSH_NO_ERROR_CODE 19
PUSH_NO_ERROR_CODE 20
PUSH_ERROR_CODE 21
