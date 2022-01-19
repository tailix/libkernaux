libkernaux
==========

[![Test](https://github.com/tailix/libkernaux/actions/workflows/test.yml/badge.svg)](https://github.com/tailix/libkernaux/actions/workflows/test.yml)

Auxiliary library for kernel development.



Table of contents
-----------------

* [Overview](#libkernaux)
* [Table of contents](#table-of-contents)
* [API](#api)
* [Tips](#tips)
  * [Non-default options](#non-default-options)
  * [Default options](#default-options)
  * [Installation](#installation)
  * [Development](#development)
  * [Cross](#cross)
* [Architectures](#architectures)
* [Portability](#portability)
* [Discussion](#discussion)



API
---

* Runtime environment
  * Architecture-specific code
    * [Declarations](/include/kernaux/arch/)
    * [Functions](/include/kernaux/asm/)
  * [Assertions](/include/kernaux/assert.h)
    * [Simple](/examples/assert_simple.c)
    * [Guards](/examples/assert_guards.c)
  * Stack trace *(planned)*
* Device drivers (for debugging only)
  * [Serial console](/include/kernaux/console.h) *(work in progress)*
  * [Framebuffer](/include/kernaux/framebuffer.h) *(planned)*
  * USB *(planned)*
* Algorithms
  * [Simple command line parser](/include/kernaux/cmdline.h)
    * [Example](/examples/cmdline.c)
  * [Page Frame Allocator](/include/kernaux/pfa.h) *(work in progress)*
    * [Example](/examples/pfa.c)
* Data formats
  * [ELF](/include/kernaux/elf.h) *(work in progress)*
  * [Master Boot Record](/include/kernaux/mbr.h) *(work in progress)*
  * [Multiboot 2 (GRUB 2)](/include/kernaux/multiboot2.h) *(work in progress)*
  * Stivale 2 (Limine) *(planned)*
* Utilities
  * [Measurement units utils](/include/kernaux/units.h) *(work in progress)*
    * [To human](/examples/units_human.c)
* Usual functions
  * [libc replacement](/include/kernaux/libc.h)
  * [itoa/ftoa replacement](/include/kernaux/ntoa.h) *(work in progress)*
  * [printf replacement](/include/kernaux/printf.h) *(work in progress)*
    * [printf](/examples/printf.c)
    * [vprintf](/examples/printf_va.c)
    * `snprintf`
    * `vsnprintf`
    * `sprintf`



Tips
----

### Non-default options

Because this library has no external dependencies, we use **autoconf** features
to control behavior of the library, and packages to choose it's components. Here
are some non-default options:

* `--enable-assert` - use value of extern variable `kernaux_assert_cb` as a
  callback function for internal assertions. You still can use assertions in
  your own application (kernel) even if this option was not enabled.
* `--enable-guard` - safely return from functions even when assertions are
  disabled. This option doesn't have effect if your assetion function was set
  and ends execution of application (kernel). However it prevents crashes and
  undefined behavior in other cases. You can also separately enable or disable
  guards:
  * `--(enable|disable)-guard-cond`
  * `--(enable|disable)-guard-null`
* `--with-libc` - provides the replacement for some standard C functions. Useful
  in freestanding environment, where no libc is present. You can also separately
  include or exclude components:
  * `--with[out]-libc-memset`
  * `--with[out]-libc-strcpy`
  * `--with[out]-libc-strlen`
  * `--with[out]-libc-strnlen`

### Default options

* `--enable-float`, disable with `--disable-float`

* `--with[out]-cmdline`
* `--with[out]-console`
* `--with[out]-elf`
* `--with[out]-framebuffer`
* `--with[out]-mbr`
* `--with[out]-multiboot2`
* `--with[out]-ntoa`
* `--with[out]-printf`
* `--with[out]-pfa`
* `--with[out]-units`

### Installation

```
./autogen.sh
./configure
make
sudo make install
```

This is just a usual library. You can use most of it's APIs in hosted
environment.

### Development

```
./autogen.sh
./configure --enable-tests --enable-assert --enable-guard
make
```

You can test with `make check`.

### Cross

Create configuration script with `./autogen.sh`.

Let's assume that your target triplet is `i386-elf`. Configure with
[cross-compiler](https://wiki.osdev.org/GCC_Cross-Compiler) in `$PATH` to make
without it in `$PATH`:

```
./configure \
  --host='i386-elf' \
  --enable-assert \
  --enable-guard \
  --with-libc \
  AR="$(which i386-elf-ar)" \
  CC="$(which i386-elf-gcc)" \
  RANLIB="$(which i386-elf-ranlib)" \
  CFLAGS='-ffreestanding -nostdlib -fno-builtin -fno-stack-protector'
```

You can see the following messages. It's
[a bug](https://savannah.gnu.org/support/index.php?110393) in **autoconf**, just
ignore it.

```
checking for _Bool... no
checking stdarg.h usability... no
checking stdarg.h presence... yes
configure: WARNING: stdarg.h: present but cannot be compiled
configure: WARNING: stdarg.h:     check for missing prerequisite headers?
configure: WARNING: stdarg.h: see the Autoconf documentation
configure: WARNING: stdarg.h:     section "Present But Cannot Be Compiled"
configure: WARNING: stdarg.h: proceeding with the compiler's result
configure: WARNING:     ## ---------------------------------------------------------- ##
configure: WARNING:     ## Report this to https://github.com/tailix/libkernaux/issues ##
configure: WARNING:     ## ---------------------------------------------------------- ##
checking for stdarg.h... no
checking stddef.h usability... no
checking stddef.h presence... yes
configure: WARNING: stddef.h: present but cannot be compiled
configure: WARNING: stddef.h:     check for missing prerequisite headers?
configure: WARNING: stddef.h: see the Autoconf documentation
configure: WARNING: stddef.h:     section "Present But Cannot Be Compiled"
configure: WARNING: stddef.h: proceeding with the compiler's result
configure: WARNING:     ## ---------------------------------------------------------- ##
configure: WARNING:     ## Report this to https://github.com/tailix/libkernaux/issues ##
configure: WARNING:     ## ---------------------------------------------------------- ##
checking for stddef.h... no
```

To install into specific directory use full path: `DESTDIR="$(pwd)/dest" make
install` instead of `DESTDIR=dest make install`.

Check if compilation targets i386: `objdump -d src/asm/i386.o`. It should output
something like this:

```
src/asm/i386.o:     file format elf32-i386


Disassembly of section .text:

00000000 <kernaux_asm_i386_read_cr0>:
   0:   0f 20 c0              mov    %cr0,%eax
   3:   c3                    ret

00000004 <kernaux_asm_i386_read_cr4>:
   4:   0f 20 e0              mov    %cr4,%eax
   7:   c3                    ret

00000008 <kernaux_asm_i386_write_cr0>:
   8:   8b 44 24 04           mov    0x4(%esp),%eax
   c:   0f 22 c0              mov    %eax,%cr0
   f:   c3                    ret

00000010 <kernaux_asm_i386_write_cr3>:
  10:   8b 44 24 04           mov    0x4(%esp),%eax
  14:   0f 22 d8              mov    %eax,%cr3
  17:   c3                    ret

00000018 <kernaux_asm_i386_write_cr4>:
  18:   8b 44 24 04           mov    0x4(%esp),%eax
  1c:   0f 22 e0              mov    %eax,%cr4
  1f:   c3                    ret
```



Architectures
-------------

Architectures should be properly identified. We use the following scheme, but it
may change in future:

* `x86`
  * `i386`
  * `x86_64`
* `riscv`
  * `riscv64`



Portability
-----------

Except GNU/Linux, the library is periodically successfully built (starting with
`./autogen.sh`) and tested with **autoconf**, **automake**, **binutils** and
**gcc**/**clang** (depending on what is present) on the following operating
systems:

* FreeBSD 13.0
* Minix 3.3.0
* NetBSD 9.2
* OpenBSD 7.0



Discussion
----------

* [Topic on OSDev.org forum](https://forum.osdev.org/viewtopic.php?f=1&t=37958)
* [Thread on r/osdev](https://www.reddit.com/r/osdev/comments/k3ueeu/libkernaux_auxiliary_library_for_kernel/)
