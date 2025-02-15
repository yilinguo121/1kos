ENTRY(boot)

PAGE_SIZE = 4096;

SECTIONS {
    . = 0x80200000;
    __kernel_base = .;

    .text :{
        KEEP(*(.text.boot));
        *(.text .text.*);
    }

    .rodata : ALIGN(4) {
        *(.rodata .rodata.*);
    }

    .data : ALIGN(4) {
        *(.data .data.*);
    }

    .bss : ALIGN(4) {
        __bss = .;
        *(.bss .bss.* .sbss .sbss.*);
        __bss_end = .;
    }

    __free_ram = ALIGN(__bss_end, PAGE_SIZE);
    __free_ram_end = 0x80300000;

    . = ALIGN(4);
    . += 128 * 1024; /* 128KB */
    __stack_top = .;
}

