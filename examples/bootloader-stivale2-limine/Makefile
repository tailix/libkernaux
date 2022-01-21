all: test

CCPREFIX = ../../vendor/cross/root/bin/x86_64-elf-

AS = $(CCPREFIX)as
CC = $(CCPREFIX)gcc

LIBKERNAUX_BUILD = ../../build/dev-cross-x86_64
LIBKERNAUX_DEST  = ../../dest/dev-cross-x86_64

DIFF = diff
LIMINE = ../../vendor/limine/build/bin
QEMU = qemu-system-x86_64 -serial stdio -display none
XORRISO = xorriso

EXPECTED = expected.txt
IMAGE = image.iso
LINKERSCR = linker.ld
OUTPUT = output.txt
ROOTFS = rootfs

LIMINE_CD       = $(LIMINE)/limine-cd.bin
LIMINE_ELTORITO = $(LIMINE)/limine-eltorito-efi.bin
LIMINE_INSTALL  = $(LIMINE)/limine-install
LIMINE_SYS      = $(LIMINE)/limine.sys

REL_KERNEL          = boot/kernel
REL_LIMINE_CD       = boot/limine-cd.bin
REL_LIMINE_CFG      = boot/limine.cfg
REL_LIMINE_ELTORITO = boot/limine-eltorito-efi.bin
REL_LIMINE_SYS      = boot/limine.sys

FULL_KERNEL          = $(ROOTFS)/$(REL_KERNEL)
FULL_LIMINE_CD       = $(ROOTFS)/$(REL_LIMINE_CD)
FULL_LIMINE_CFG      = $(ROOTFS)/$(REL_LIMINE_CFG)
FULL_LIMINE_ELTORITO = $(ROOTFS)/$(REL_LIMINE_ELTORITO)
FULL_LIMINE_SYS      = $(ROOTFS)/$(REL_LIMINE_SYS)

CFLAGS = \
	-std=c99             \
	-Wall                \
	-Wextra              \
	-Werror              \
	-ffreestanding       \
	-fno-builtin         \
	-fno-stack-protector \
	-fno-pic             \
	-I../../include      \
	-mabi=sysv           \
	-mno-80387           \
	-mno-mmx             \
	-mno-3dnow           \
	-mno-sse             \
	-mno-sse2            \
	-mno-red-zone        \
	-mcmodel=kernel      \
	-MMD
	# -pedantic            \

OBJS = main.c.o stivale2.c.o

test: run
	$(DIFF) -a -Z $(EXPECTED) $(OUTPUT)

run: $(IMAGE)
	$(QEMU) -cdrom $< | tee $(OUTPUT)

clean:
	rm -f $(OUTPUT) $(IMAGE) $(FULL_KERNEL) $(FULL_LIMINE_CD) $(FULL_LIMINE_ELTORITO) $(FULL_LIMINE_SYS) $(OBJS)

$(IMAGE): $(FULL_KERNEL) $(FULL_LIMINE_CD) $(FULL_LIMINE_ELTORITO) $(FULL_LIMINE_SYS)
	$(XORRISO) -as mkisofs -b $(REL_LIMINE_CD) -no-emul-boot -boot-load-size 4 -boot-info-table --efi-boot $(REL_LIMINE_ELTORITO) -efi-boot-part --efi-boot-image --protective-msdos-label $(ROOTFS) -o $@
	$(LIMINE_INSTALL) $@

$(FULL_KERNEL): $(LINKERSCR) $(OBJS) build-libkernaux.a
	$(CC) -T $(LINKERSCR) -o $@ $(OBJS) -ffreestanding -nostdlib -zmax-page-size=0x1000 -static -lkernaux -lgcc -Wl,-L$(LIBKERNAUX_DEST)/lib

$(FULL_LIMINE_CD):
	cp -f $(LIMINE_CD) $(FULL_LIMINE_CD)

$(FULL_LIMINE_ELTORITO):
	cp -f $(LIMINE_ELTORITO) $(FULL_LIMINE_ELTORITO)

$(FULL_LIMINE_SYS):
	cp -f $(LIMINE_SYS) $(FULL_LIMINE_SYS)

build-libkernaux.a:
	cd $(LIBKERNAUX_BUILD) && ./config
	cd $(LIBKERNAUX_BUILD) && make libkernaux.a
	cd $(LIBKERNAUX_BUILD) && make install-data install-exec

%.c.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.S.o: %.S
	$(AS) $< -o $@
