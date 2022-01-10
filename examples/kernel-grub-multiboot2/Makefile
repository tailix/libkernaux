all: run

CCPREFIX = i386-elftailix-

AS = $(CCPREFIX)as
CC = $(CCPREFIX)gcc

IMAGE = image.iso
LINKERSCR = linker.ld
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

OBJS = main.c.o start.S.o

run: $(IMAGE)
	qemu-system-i386 -cdrom $< -serial stdio -display none

clean:
	rm -f $(IMAGE) $(KERNEL) $(OBJS)

$(IMAGE): $(GRUBCFG) $(KERNEL)
	grub-mkrescue $(ROOTFS) -o $@

$(KERNEL): $(LINKERSCR) $(OBJS)
	$(CC) -T $(LINKERSCR) -o $@ $(OBJS) -ffreestanding -nostdlib -lgcc -lkernaux -Wl,-L../..
	grub-file --is-x86-multiboot2 $@

%.c.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.S.o: %.S
	$(AS) $< -o $@
