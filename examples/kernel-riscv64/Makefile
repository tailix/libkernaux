all: run

CCPREFIX = ../../vendor/cross/bin/riscv64-elf-

AS = $(CCPREFIX)as
CC = $(CCPREFIX)gcc

QEMU = qemu-system-riscv64

run:
	$(QEMU) -machine virt -serial stdio
