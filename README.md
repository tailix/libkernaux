libkernaux
==========

[![Build status](https://github.com/tailix/libkernaux/actions/workflows/main.yml/badge.svg)](https://github.com/tailix/libkernaux/actions/workflows/main.yml)
[![Build status (FreeBSD)](https://api.cirrus-ci.com/github/tailix/libkernaux.svg?task=Main%20(FreeBSD))](https://cirrus-ci.com/github/tailix/libkernaux)

Auxiliary library for kernel development.

[Topic on OSDev.org forum](https://forum.osdev.org/viewtopic.php?f=1&t=37958).



Table of contents
-----------------

* [Overview](#libkernaux)
* [Table of contents](#table-of-contents)
* [API](#api)
  * [Headers](#headers)
  * [Definitions](#definitions)
  * [Global variables](#global-variables)
* [Configuration](#configuration)
  * [Non-default options](#non-default-options)
  * [Default options](#default-options)
* [Tips](#tips)
  * [Installation](#installation)
  * [Development](#development)
  * [Cross](#cross)



API
---

### Headers

We use [semantic versioning](https://semver.org) for stable APIs. Stable APIs
can only change when major version number is increased (or minor while major is
zero). Work-in-progress APIs can change at any time.

* Runtime environment
  * [Feature macros](/include/kernaux/version.h.in) (*work in progress*)
  * [Assertions](/include/kernaux/assert.h) (*non-breaking since* **?.?.?**)
    * [Assert](/examples/assert.c)
    * [Panic](/examples/panic.c)
  * Stack trace *(planned)*
  * [Input/output](/include/kernaux/io.h) (*work in progress*)
  * Architecture-specific code (*work in progress*)
    * [Declarations](/include/kernaux/arch/)
    * [Functions](/include/kernaux/asm/)
* Device drivers (for debugging only)
  * [Serial console](/include/kernaux/console.h) (*work in progress*)
  * [Framebuffer](/include/kernaux/framebuffer.h) (*planned*)
  * USB (*planned*)
* Algorithms
  * [Simple command line parser](/include/kernaux/cmdline.h) (*non-breaking since* **0.2.0**)
    * [Example](/examples/cmdline.c)
  * [Page Frame Allocator](/include/kernaux/pfa.h) (*work in progress*)
    * [Example](/examples/pfa.c)
* Data formats
  * [ELF](/include/kernaux/elf.h) (*work in progress*)
  * [Master Boot Record](/include/kernaux/mbr.h) (*work in progress*)
  * [Multiboot 2 (GRUB 2)](/include/kernaux/multiboot2.h) (*work in progress*)
  * Stivale 2 (Limine) (*planned*)
* Utilities
  * [Measurement units utils](/include/kernaux/units.h) (*work in progress*)
    * [To human](/examples/units_human.c)
  * [Memory map](/include/kernaux/memmap.h.in) (*non-breaking since* **?.?.?**)
    * [Example](/examples/memmap.c)
  * [printf format parser](/include/kernaux/printf_fmt.h) (*work in progress*)
    * Code from [https://github.com/mpaland/printf](https://github.com/mpaland/printf). Thank you!
    * [Example](/examples/printf_fmt.c)
* Usual functions
  * [itoa/ftoa replacement](/include/kernaux/ntoa.h) (*non-breaking since* **?.?.?**)
    * [Example](/examples/ntoa.c)
  * [printf replacement](/include/kernaux/printf.h.in) (*non-breaking since* **?.?.?**)
    * Code from [https://github.com/mpaland/printf](https://github.com/mpaland/printf). Thank you!
    * [fprintf](/examples/fprintf.c)
    * [vfprintf](/examples/fprintf_va.c)
    * [snprintf](/examples/snprintf.c)
    * [vsnprintf](/examples/snprintf_va.c)
* libc replacement (*work in progress*)
  * [ctype.h](/libc/include/ctype.h)
  * [inttypes.h](/libc/include/inttypes.h)
  * [setjmp.h](/libc/include/setjmp.h)
  * [stdlib.h](/libc/include/stdlib.h)
  * [string.h](/libc/include/string.h)
  * [sys/types.h](/libc/include/sys/types.h)

### Definitions

Define the following C preprocessor macros before including `<kernaux.h>` and
`<kernaux/*.h>` files. They have effect on your code, not the library code.

* `KERNAUX_DEBUG` - enable assertions

### Global variables

```c
// in <kernaux/assert.h>
void (*kernaux_assert_cb)(const char *file, int line, const char *msg)
```

Assertion callback. It's better to always set it to some function which always
interrupts the execution, even when debugging is disabled. It may for example
call `abort()` in hosted environment, raise an exception in Ruby, panic in Rust
or power off the machine in freestanding environment. It may also log the error
location and message.




Configuration
-------------

Because this library has no external dependencies, we use **autoconf** features
to control behavior of the library, and packages to choose it's components.
Configuration options also follow the [semantic versioning](https://semver.org)
scheme and are split into stable and work-in-progress ones. Here we cover only
stable options.

### Non-default options

#### Features

* `--enable-freestanding` - build for freestanding environment
* `--enable-split-libc` - split off libc
* `--enable-tests` - enable usual tests and examples
* `--enable-tests-all` - enable all tests
* `--enable-tests-python` - enable tests that require Python 3 with YAML and
  Jinja2

#### Packages

* `--with-libc` - provides the replacement for some standard C functions.
  Useful in freestanding environment, where no libc is present.

### Default options

#### Features

* `--(enable|disable)-debug` - debugging
* `--(enable|disable)-float` - floating-point arithmetic
* `--(enable|disable)-werror` - fail on warning (`CFLAGS+='-Werror'`)

#### Packages

All packages are included by default. To exclude all packages except those
explicitly included, use `--without-all`.

* `--with[out]-cmdline` - command line parser
* `--with[out]-file` - file simulator
* `--with[out]-memmap` - memory map
* `--with[out]-ntoa` - itoa/ftoa
* `--with[out]-printf` - printf



Tips
----

### Installation

```
./autogen.sh # if present
./configure
make
sudo make install
```

This is just a usual library. You can use most of it's APIs in hosted
environment.

### Development

```
./autogen.sh # if present
./configure --enable-tests # or --enable-tests-all, but see prerequisites
make
```

You can test with `make check`.

### Cross

Create configuration script with `./autogen.sh` (if present).

Let's assume that your target triplet is `i386-elf`. Configure with
[cross-compiler](https://wiki.osdev.org/GCC_Cross-Compiler) in `$PATH` to make
without it in `$PATH`:

```
./configure \
  --host='i386-elf' \
  --enable-freestanding \
  --with-libc \
  AR="$(which i386-elf-ar)" \
  CC="$(which i386-elf-gcc)" \
  RANLIB="$(which i386-elf-ranlib)"
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
