all: run

CCPREFIX = ../../vendor/cross/bin/riscv64-elf-

AS = $(CCPREFIX)as
CC = $(CCPREFIX)gcc

CONFIG_LIBKERNAUX = ../../config/riscv64
QEMU = qemu-system-riscv64 -serial stdio -display none

BUILD_LIBKERNAUX = build-libkernaux
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
	make -C $(BUILD_LIBKERNAUX) distclean || true
	rm -f $(KERNEL) $(OBJS)

$(KERNEL): $(LINKERSCR) $(OBJS) build-libkernaux.a
	$(CC) -T $(LINKERSCR) -o $@ $(OBJS) -nostdlib -lgcc -lkernaux -Wl,-L$(BUILD_LIBKERNAUX)

build-libkernaux.a:
	cd $(BUILD_LIBKERNAUX) && ../$(CONFIG_LIBKERNAUX)
	cd $(BUILD_LIBKERNAUX) && make libkernaux.a

%.c.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.S.o: %.S
	$(AS) $< -o $@
