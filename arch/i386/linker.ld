OUTPUT_FORMAT(binary)

SECTIONS {
  . = 0x7c00;

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
