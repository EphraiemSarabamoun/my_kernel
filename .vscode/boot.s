; This is boot.s - the entry point of our kernel
; It sets up the initial environment and jumps to our C code

; Multiboot header magic numbers - these help GRUB recognize our kernel
MBALIGN     equ 1<<0             ; Align loaded modules on page boundaries
MEMINFO     equ 1<<1             ; Provide memory map
FLAGS       equ MBALIGN | MEMINFO
MAGIC       equ 0x1BADB002       ; Magic number lets bootloader find the header
CHECKSUM    equ -(MAGIC + FLAGS) ; Checksum to prove we are multiboot

; Declare the multiboot header that marks the program as a kernel
section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

; Create a small stack for our kernel to use
section .bootstrap_stack, nobits
align 4
stack_bottom:
    resb 16384 ; 16 KiB
stack_top:

; The kernel entry point function
section .text
global _start
_start:
    ; Set up the stack - essential for C code to work
    mov esp, stack_top

    ; Call the kernel's main function
    extern kernel_main
    call kernel_main

    ; Enter an infinite loop if kernel_main returns
    cli      ; Disable interrupts
.hang:
    hlt      ; Halt the CPU
    jmp .hang ; Jump back to .hang if we ever wake up