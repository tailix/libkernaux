all: test

TESTER = ../../kernaux-tester-stivale2

DIFF = diff
LIMINE = ../../vendor/limine/build/bin
QEMU = qemu-system-x86_64 -serial stdio -display none
XORRISO = xorriso

EXPECTED = expected.txt
IMAGE = image.iso
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

test: run
	$(DIFF) -a -Z $(EXPECTED) $(OUTPUT)

run: $(IMAGE)
	$(QEMU) -cdrom $< | tee $(OUTPUT)

clean:
	rm -f $(OUTPUT) $(IMAGE) $(FULL_KERNEL) $(FULL_LIMINE_CD) $(FULL_LIMINE_ELTORITO) $(FULL_LIMINE_SYS)

$(IMAGE): $(FULL_KERNEL) $(FULL_LIMINE_CD) $(FULL_LIMINE_ELTORITO) $(FULL_LIMINE_SYS)
	$(XORRISO) -as mkisofs -b $(REL_LIMINE_CD) -no-emul-boot -boot-load-size 4 -boot-info-table --efi-boot $(REL_LIMINE_ELTORITO) -efi-boot-part --efi-boot-image --protective-msdos-label $(ROOTFS) -o $@
	$(LIMINE_INSTALL) $@

$(FULL_KERNEL):
	cp $(TESTER) $@

$(FULL_LIMINE_CD):
	cp -f $(LIMINE_CD) $(FULL_LIMINE_CD)

$(FULL_LIMINE_ELTORITO):
	cp -f $(LIMINE_ELTORITO) $(FULL_LIMINE_ELTORITO)

$(FULL_LIMINE_SYS):
	cp -f $(LIMINE_SYS) $(FULL_LIMINE_SYS)
