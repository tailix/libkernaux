all: test

CCPREFIX = ../../vendor/cross/bin/i386-elf-

AS = $(CCPREFIX)as
CC = $(CCPREFIX)gcc

CONFIG_LIBKERNAUX = ../../config/i386
DIFF = diff
GRUB_FILE = grub-file
GRUB_MKRESCUE = grub-mkrescue
QEMU = qemu-system-i386

BUILD_LIBKERNAUX = build-libkernaux
EXPECTED = expected.txt
IMAGE = image.iso
LINKERSCR = linker.ld
OUTPUT = output.txt
ROOTFS = rootfs

GRUBCFG = $(ROOTFS)/boot/grub/grub.cfg
KERNEL  = $(ROOTFS)/boot/kernel

CFLAGS = \
	-std=c99             \
	-pedantic            \
	-Wall                \
	-Wextra              \
	-Werror              \
	-ffreestanding       \
	-fno-builtin         \
	-fno-stack-protector \
	-I../../include

OBJS = main.c.o multiboot2.c.o start.S.o

test: run
	$(DIFF) -a -Z $(EXPECTED) $(OUTPUT)

run: $(IMAGE)
	$(QEMU) -cdrom $< -serial stdio -display none | tee $(OUTPUT)

clean:
	make -C $(BUILD_LIBKERNAUX) distclean || true
	rm -f $(OUTPUT) $(IMAGE) $(KERNEL) $(OBJS)

$(IMAGE): $(GRUBCFG) $(KERNEL)
	$(GRUB_MKRESCUE) $(ROOTFS) -o $@

$(KERNEL): $(LINKERSCR) $(OBJS) build-libkernaux.a
	$(CC) -T $(LINKERSCR) -o $@ $(OBJS) -ffreestanding -nostdlib -lgcc -lkernaux -Wl,-L$(BUILD_LIBKERNAUX)
	$(GRUB_FILE) --is-x86-multiboot2 $@

build-libkernaux.a:
	cd $(BUILD_LIBKERNAUX) && ../$(CONFIG_LIBKERNAUX)
	cd $(BUILD_LIBKERNAUX) && make libkernaux.a

%.c.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.S.o: %.S
	$(AS) $< -o $@
