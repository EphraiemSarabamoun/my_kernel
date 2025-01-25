# Specify the tools
CC = x86_64-elf-gcc
AS = nasm
LD = x86_64-elf-ld

# Compiler and assembler flags
CFLAGS = -ffreestanding -m32 -O2 -Wall -Wextra -fno-pie -no-pie
ASFLAGS = -f elf32

# File names
KERNEL = kernel.bin

# Linker flags
LDFLAGS = -m elf_i386 -nostdlib -T linker.ld

# Build the kernel

$(KERNEL): boot.o kernel.o
	$(LD) -m elf_i386 -T linker.ld -o $(KERNEL) boot.o kernel.o

boot.o: boot.s
	$(AS) $(ASFLAGS) boot.s -o boot.o

kernel.o: kernel.c
	$(CC) $(CFLAGS) -c kernel.c -o kernel.o

# Clean up build artifacts
clean:
	rm -rf *.o $(KERNEL) $(ISO) isodir