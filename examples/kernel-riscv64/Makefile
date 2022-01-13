all: run

CCPREFIX = ../../vendor/cross/bin/riscv64-elf-

AS = $(CCPREFIX)as
CC = $(CCPREFIX)gcc

QEMU = qemu-system-riscv64

KERNEL = kernel.elf
LINKERSCR = linker.ld

CFLAGS = \
	-std=c99        \
	-pedantic       \
	-Wall           \
	-Wextra         \
	-Werror         \
	-ffreestanding  \
	-mcmodel=medany

OBJS = main.c.o start.S.o

run: $(KERNEL)
	$(QEMU) -machine virt -bios $< -serial stdio -display none

clean:
	rm -f $(KERNEL) $(OBJS)

$(KERNEL): $(LINKERSCR) $(OBJS)
	$(CC) -T $(LINKERSCR) -o $@ $(OBJS) -nostdlib -lgcc

%.c.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.S.o: %.S
	$(AS) $< -o $@
