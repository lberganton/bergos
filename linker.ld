OUTPUT_FORMAT(binary)

SECTIONS {
  . = 0x7c00;

  .bootloader : {
    *(.bootloader)
  }

  .text : {
    *(.text)
    *(.text.*)
  }

  .data : {
    *(.data)
    *(.data.*)
  }

  .bss : {
    *(.bss)
    *(.bss.*)
  }

  .rodata : {
    *(.rodata)
    *(.rodata.*)
  }
}
