libkernaux
==========

[![Build Status](https://travis-ci.org/kernelmq/libkernaux.svg?branch=master)](https://travis-ci.org/kernelmq/libkernaux)

Auxiliary library for kernel development.



Table of contents
-----------------

* [Overview](#libkernaux)
* [Table of contents](#table-of-contents)
* [API](#api)
* [Tips](#tips)
* [Discussion](#discussion)



API
---

* [Simple command line parser](/include/kernaux/cmdline.h) *(work in progress)*
* [Multiboot 2 (GRUB 2) information parser](/include/kernaux/multiboot2.h)
* [Serial console](/include/kernaux/console.h) *(work in progress)*
* [Page Frame Allocator](/include/kernaux/pfa.h) *(work in progress)*
* ELF utils *(planned)*
* [Architecture-specific helpers](/include/kernaux/arch/)
* [stdlib replacement](/include/kernaux/stdlib.h) (with prefix):
  * `memset`
  * `strlen`
  * `strncpy`
  * `itoa` *(incomplete)*



Tips
----

Create configuration script with `./autogen.sh`.

Configure with cross-compiler in `$PATH` to make without it in `$PATH`:

```
./configure \
  --host=x86-elf \
  AR="$(which x86-elf-ar)" \
  CC="$(which x86-elf-gcc)" \
  RANLIB="$(which x86-elf-ranlib)" \
  CFLAGS='-ffreestanding -nostdlib -fno-builtin -fno-stack-protector'
```

To install into specific directory use full path:
`DESTDIR="$(pwd)/dest" make install` instead of `DESTDIR=dest make install`.

When configured with cross-compiler, library can't be build and installed with
just `make && sudo make install`. Instead use the following commands:

* `make libkernaux.a`
* `sudo make install-exec`
* `sudo make install-data`

Check if compilation targets x86: `objdump -d src/arch/x86.o`. It should
output something like this:

```
src/arch/x86.o:     file format elf32-i386


Disassembly of section .text:

00000000 <kernaux_arch_x86_hang>:
   0:   fa                    cli
   1:   f4                    hlt
   2:   eb fc                 jmp    0 <kernaux_arch_x86_hang>

00000004 <kernaux_arch_x86_read_cr0>:
   4:   0f 20 c0              mov    %cr0,%eax
   7:   c3                    ret

00000008 <kernaux_arch_x86_read_cr4>:
   8:   0f 20 e0              mov    %cr4,%eax
   b:   c3                    ret

0000000c <kernaux_arch_x86_write_cr0>:
   c:   8b 44 24 04           mov    0x4(%esp),%eax
  10:   0f 22 c0              mov    %eax,%cr0
  13:   c3                    ret

00000014 <kernaux_arch_x86_write_cr3>:
  14:   8b 44 24 04           mov    0x4(%esp),%eax
  18:   0f 22 d8              mov    %eax,%cr3
  1b:   c3                    ret

0000001c <kernaux_arch_x86_write_cr4>:
  1c:   8b 44 24 04           mov    0x4(%esp),%eax
  20:   0f 22 e0              mov    %eax,%cr4
  23:   c3                    ret
```



Discussion
----------

* [Topic on OSDev.org forum](https://forum.osdev.org/viewtopic.php?f=1&t=37958)
* [Thread on r/osdev](https://www.reddit.com/r/osdev/comments/k3ueeu/libkernaux_auxiliary_library_for_kernel/)
