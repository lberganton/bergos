OUTPUT_FORMAT(binary)

SECTIONS {
  . = 0x7c00;

  .bootloader : {
    *(.bootloader)
    *(.bootloader.*)
  }

  . = 0x7e00;

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
}
