all: run

REPO = ../../..

CCPREFIX = $(REPO)/vendor/cross/root/bin/riscv64-elf-

AS = $(CCPREFIX)as
CC = $(CCPREFIX)gcc

LIBKERNAUX_BUILD = $(REPO)/build/dev-cross-riscv64
LIBKERNAUX_DEST  = $(REPO)/dest/dev-cross-riscv64

QEMU = qemu-system-riscv64 -serial stdio -display none

KERNEL = kernel.elf
LINKERSCR = linker.ld

CFLAGS = \
	-std=c99                     \
	-pedantic                    \
	-Wall                        \
	-Wextra                      \
	-Werror                      \
	-ffreestanding               \
	-mcmodel=medany              \
	-I$(LIBKERNAUX_DEST)/include

OBJS = main.c.o start.S.o

run: $(KERNEL)
	$(QEMU) -machine virt -bios $<

clean:
	rm -f $(KERNEL) $(OBJS)

$(KERNEL): $(LINKERSCR) build-libkernaux.a $(OBJS)
	$(CC) -T $(LINKERSCR) -o $@ $(OBJS) -nostdlib -lkernaux -lgcc -Wl,-L$(LIBKERNAUX_DEST)/lib

build-libkernaux.a:
	cd $(LIBKERNAUX_BUILD) && ./config && make install

%.c.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.S.o: %.S
	$(AS) $< -o $@
