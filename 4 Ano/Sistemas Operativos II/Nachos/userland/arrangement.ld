OUTPUT_FORMAT("ecoff-littlemips")
ENTRY(__start)
SECTIONS
{
    .text 0 : {
        *(.init)
        *(.text)
        *(.fini)
    }
    .data . : {
        /* `coff2noff` cannot output more than one initialized data section,
           so put the contents of all of them inside `.data`. */
        *(.rdata)
        *(.rodata)
        *(.data)
        CONSTRUCTORS
    }
    .sbss . : {
        *(.sbss)
        *(.scommon)
    }
    .bss . : {
        *(.bss)
        *(COMMON)
    }
    /* Sections to be discarded, if present. */
    /DISCARD/ : {
        *(.comment)
        *(.pdr)
        *(.reginfo)
        *(.gnu.att*)
        *(.MIPS.ab*)
    }
}
