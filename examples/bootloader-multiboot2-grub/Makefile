all: test

CCPREFIX = ../../vendor/cross/root/bin/i386-elf-

AS = $(CCPREFIX)as
CC = $(CCPREFIX)gcc

LIBKERNAUX_SRC   = ../..
LIBKERNAUX_BUILD = ../../build/dev-cross-i386
LIBKERNAUX_DEST  = ../../dest/dev-cross-i386

DIFF = diff
GRUB_FILE = grub-file
GRUB_MKRESCUE = grub-mkrescue
QEMU = qemu-system-i386 -serial stdio -display none

EXPECTED = expected.txt
IMAGE = image.iso
LINKERSCR = linker.ld
OUTPUT = output.txt
ROOTFS = rootfs

GRUBCFG = $(ROOTFS)/boot/grub/grub.cfg
KERNEL  = $(ROOTFS)/boot/kernel

CFLAGS = \
	-std=c99                      \
	-pedantic                     \
	-Wall                         \
	-Wextra                       \
	-Werror                       \
	-ffreestanding                \
	-fno-stack-protector          \
	-I$(LIBKERNAUX_SRC)/include   \
	-I$(LIBKERNAUX_BUILD)/include

OBJS = main.c.o multiboot2.c.o start.S.o

test: run
	$(DIFF) -a -Z $(EXPECTED) $(OUTPUT)

run: $(IMAGE)
	$(QEMU) -cdrom $< | tee $(OUTPUT)

clean:
	rm -f $(OUTPUT) $(IMAGE) $(KERNEL) $(OBJS)

$(IMAGE): $(GRUBCFG) $(KERNEL)
	$(GRUB_MKRESCUE) $(ROOTFS) -o $@

$(KERNEL): $(LINKERSCR) build-libkernaux.a $(OBJS)
	$(CC) -T $(LINKERSCR) -o $@ $(OBJS) -ffreestanding -nostdlib -lkernaux -lgcc -Wl,-L$(LIBKERNAUX_DEST)/lib
	$(GRUB_FILE) --is-x86-multiboot2 $@

build-libkernaux.a:
	cd $(LIBKERNAUX_BUILD) && ./config && make install

%.c.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.S.o: %.S
	$(AS) $< -o $@
