libkernaux
==========

Auxiliary library for kernel development.

* [Architecture-specific helpers](/include/kernaux/arch/)
* [stdlib replacement](/include/kernaux/stdlib.h)
  * `memset`
  * `strlen`
  * `strncpy`
  * `itoa` (incomplete)
* [Multiboot 2 (GRUB 2) information parser](/include/kernaux/multiboot2.h)
* [Page Frame Allocator](/include/kernaux/pfa.h) (work in progress)



Table of contents
-----------------

* [Overview](#libkernaux)
* [Table of contents](#table-of-contents)
* [Tips](#tips)
* [Discussion](#discussion)



Tips
----

Create configuration script with `./autogen.sh`.

Configure with cross-compiler in `$PATH` to make without it in `$PATH`:

```
./configure \
  --host=i686-elf \
  AR="$(which i686-elf-ar)" \
  CC="$(which i686-elf-gcc)" \
  RANLIB="$(which i686-elf-ranlib)" \
  CFLAGS='-ffreestanding -nostdinc -nostdlib -fno-builtin -fno-stack-protector'
```

To install into specific directory use full path:
`DESTDIR="$(pwd)/dest" make install` instead of `DESTDIR=dest make install`.

When configured with cross-compiler, library can't be build and installed with
just `make && sudo make install`. Instead use the following commands:

* `make libkernaux.a`
* `sudo make install-libLIBRARIES`
* `sudo make install-data`

Check if compilation targets i386: `objdump -d src/arch/i386.o`. It should
output something like this:

```
src/arch/i386.o:     file format elf32-i386


Disassembly of section .text:

00000000 <kernaux_arch_i386_hang>:
   0:   fa                    cli
   1:   f4                    hlt
   2:   eb fc                 jmp    0 <kernaux_arch_i386_hang>

00000004 <kernaux_arch_i386_read_cr0>:
   4:   0f 20 c0              mov    %cr0,%eax
   7:   c3                    ret

00000008 <kernaux_arch_i386_read_cr4>:
   8:   0f 20 e0              mov    %cr4,%eax
   b:   c3                    ret

0000000c <kernaux_arch_i386_write_cr0>:
   c:   8b 44 24 04           mov    0x4(%esp),%eax
  10:   0f 22 c0              mov    %eax,%cr0
  13:   c3                    ret

00000014 <kernaux_arch_i386_write_cr3>:
  14:   8b 44 24 04           mov    0x4(%esp),%eax
  18:   0f 22 d8              mov    %eax,%cr3
  1b:   c3                    ret

0000001c <kernaux_arch_i386_write_cr4>:
  1c:   8b 44 24 04           mov    0x4(%esp),%eax
  20:   0f 22 e0              mov    %eax,%cr4
  23:   c3                    ret
```



Discussion
----------

* [Topic on OSDev.org forum](https://forum.osdev.org/viewtopic.php?f=1&t=37958)
