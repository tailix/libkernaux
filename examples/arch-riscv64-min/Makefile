all: run

CCPREFIX = ../../vendor/cross/bin/riscv64-elf-

AS = $(CCPREFIX)as
CC = $(CCPREFIX)gcc

LIBKERNAUX_BUILD = ../../build/dev-cross-riscv64
LIBKERNAUX_DEST  = ../../dest/dev-cross-riscv64

QEMU = qemu-system-riscv64 -serial stdio -display none

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
	$(QEMU) -machine virt -bios $<

clean:
	rm -f $(KERNEL) $(OBJS)

$(KERNEL): $(LINKERSCR) $(OBJS) build-libkernaux.a
	$(CC) -T $(LINKERSCR) -o $@ $(OBJS) -nostdlib -lgcc -lkernaux -Wl,-L$(LIBKERNAUX_DEST)/lib

build-libkernaux.a:
	cd $(LIBKERNAUX_BUILD) && ./config
	cd $(LIBKERNAUX_BUILD) && make libkernaux.a
	cd $(LIBKERNAUX_BUILD) && make install-data install-exec

%.c.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.S.o: %.S
	$(AS) $< -o $@
