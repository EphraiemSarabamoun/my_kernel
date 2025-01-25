/* Linker script - tells the linker how to put our kernel together */
ENTRY(_start)

SECTIONS {
    /* Start at 1MB - standard practice for kernels */
    . = 1M;

    /* First put the multiboot header, as it needs to be within the first 8KB */
    .text BLOCK(4K) : ALIGN(4K) {
        *(.multiboot)
        *(.text)
    }

    /* Read-only data */
    .rodata BLOCK(4K) : ALIGN(4K) {
        *(.rodata)
    }

    /* Read-write data (initialized) */
    .data BLOCK(4K) : ALIGN(4K) {
        *(.data)
    }

    /* Read-write data (uninitialized) and stack */
    .bss BLOCK(4K) : ALIGN(4K) {
        *(COMMON)
        *(.bss)
        *(.bootstrap_stack)
    }
}