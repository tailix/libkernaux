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
* [Summary](#summary)
  * [Pure code size](#pure-code-size)
  * [Used header files](#used-header-files)
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
* Device drivers (for debugging only)
  * [Serial console](/include/kernaux/console.h)
  * [Framebuffer](/include/kernaux/framebuffer.h) *(work in progress)*
* Algorithms
  * [Simple command line parser](/include/kernaux/cmdline.h)
    * [Example](/examples/cmdline.c)
  * [Page Frame Allocator](/include/kernaux/pfa.h)
    * [Example](/examples/pfa.c)
* Data formats
  * [Multiboot 2 (GRUB 2) information parser](/include/kernaux/multiboot2.h)
  * [ELF utils](/include/kernaux/elf.h) *(work in progress)*
* Utilities
  * [Measurement units utils](/include/kernaux/units.h) *(work in progress)*
    * [To human](/examples/units_human.c)
* Usual functions
  * [libc replacement](/include/kernaux/libc.h)
    * `memset`
    * `strcpy`
    * `strlen`
  * [itoa replacement](/include/kernaux/itoa.h) *(work in progress)*
  * [printf replacement](/include/kernaux/printf.h) *(work in progress)*
    * [printf](/examples/printf.c)
    * [printf_va](/examples/printf_va.c)



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
  undefined behabior in other cases. You can also separately enable or disable
  guards:
  * `--(enable|disable)-guard-cond`
  * `--(enable|disable)-guard-null`
* `--with-libc` - provides the replacement for some standard C functions. Useful
  in freestanding environment, where no libc is present. You can also separately
  include or exclude components:
  * `--with[out]-libc-memset`
  * `--with[out]-libc-strcpy`
  * `--with[out]-libc-strlen`

### Default options

* `--with[out]-cmdline`
* `--with[out]-console`
* `--with[out]-elf`
* `--with[out]-framebuffer`
* `--with[out]-multiboot2`
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
./configure --enable-assert --enable-guard
make
```

You can test with `make check`.

### Cross

The library depends on `stdint.h` header. According to the standards it must be
present in freestanding environment. However when you build GCC cross-compiler
using [instructions from OSDev Wiki](https://wiki.osdev.org/GCC_Cross-Compiler)
the header is missing. To fix this issue you may add `use_gcc_stdint=provide` to
the end of `gcc/config.gcc` in your GCC source code extracted from tarball:

```
echo 'use_gcc_stdint=provide' >> gcc-11.2.0/gcc/config.gcc
```

---

Create configuration script with `./autogen.sh`.

Let's assume that your target triplet is `i386-elf`. Configure with
cross-compiler in `$PATH` to make without it in `$PATH`:

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

When configured with cross-compiler, library can't be build and installed with
just `make && sudo make install`. Instead use the following commands:

* `make libkernaux.a`
* `sudo make install-exec install-data`

To install into specific directory use full path:
`DESTDIR="$(pwd)/dest" sudo make install-exec install-data` instead of
`DESTDIR=dest sudo make install-exec install-data`.

Check if compilation targets i386: `objdump -d src/asm/i386.o`. It should output
something like this:

```
src/asm/i386.o:     file format elf32-i386


Disassembly of section .text:

00000000 <kernaux_asm_i386_hang>:
   0:   fa                    cli
   1:   f4                    hlt
   2:   eb fc                 jmp    0 <kernaux_asm_i386_hang>

00000004 <kernaux_asm_i386_read_cr0>:
   4:   0f 20 c0              mov    %cr0,%eax
   7:   c3                    ret

00000008 <kernaux_asm_i386_read_cr4>:
   8:   0f 20 e0              mov    %cr4,%eax
   b:   c3                    ret

0000000c <kernaux_asm_i386_write_cr0>:
   c:   8b 44 24 04           mov    0x4(%esp),%eax
  10:   0f 22 c0              mov    %eax,%cr0
  13:   c3                    ret

00000014 <kernaux_asm_i386_write_cr3>:
  14:   8b 44 24 04           mov    0x4(%esp),%eax
  18:   0f 22 d8              mov    %eax,%cr3
  1b:   c3                    ret

0000001c <kernaux_asm_i386_write_cr4>:
  1c:   8b 44 24 04           mov    0x4(%esp),%eax
  20:   0f 22 e0              mov    %eax,%cr4
  23:   c3                    ret
```



Summary
-------

This information is updated from time to time.

### Pure code size

`cloc --vcs=git include/ src/`

```
-------------------------------------------------------------------------------
Language                     files          blank        comment           code
-------------------------------------------------------------------------------
C                               12            236             19           1548
C/C++ Header                    14            179             64            597
Assembly                         2              7              6             28
make                             1              0              0             13
-------------------------------------------------------------------------------
SUM:                            29            422             89           2186
-------------------------------------------------------------------------------
```

### Used header files

`git grep '#include <' -- include/ src/ | grep -v '#include <kernaux' | awk '{ print $2; }' | sort | uniq`

* `stdarg.h`
* `stdbool.h`
* `stddef.h`
* `stdint.h`



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
