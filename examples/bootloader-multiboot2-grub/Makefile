all: test

TESTER = ../../kernaux-tester-multiboot2

DIFF = diff
GRUB_FILE = grub-file
GRUB_MKRESCUE = grub-mkrescue
QEMU = qemu-system-i386 -serial stdio -display none

EXPECTED = expected.txt
IMAGE = image.iso
OUTPUT = output.txt
ROOTFS = rootfs

GRUBCFG = $(ROOTFS)/boot/grub/grub.cfg
KERNEL  = $(ROOTFS)/boot/kernel

test: run
	$(DIFF) -a -Z $(EXPECTED) $(OUTPUT)

run: $(IMAGE)
	$(QEMU) -cdrom $< | tee $(OUTPUT)

clean:
	rm -f $(OUTPUT) $(IMAGE) $(KERNEL)

$(IMAGE): $(GRUBCFG) $(KERNEL)
	$(GRUB_MKRESCUE) $(ROOTFS) -o $@

$(KERNEL):
	cp $(TESTER) $@
	$(GRUB_FILE) --is-x86-multiboot2 $@
