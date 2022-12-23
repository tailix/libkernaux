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
may only change when major version number is increased (or minor while major is
zero). Work-in-progress APIs can change at any time.

* Basic features
  * [Feature macros](/include/kernaux/version.h.in) (*work in progress*)
  * [Runtime environment](/include/kernaux/runtime.h) (*non-breaking since* **0.7.0**)
  * [Macros](/include/kernaux/macro.h) (*non-breaking since* **0.6.0**)
    * [Example: packing](/examples/macro_packing.c)
    * [Example: BITS](/examples/macro_bits.c)
    * [Example: CAST\_\*](/examples/macro_cast.c);
    * [Example: CONTAINER\_OF](/examples/macro_container_of.c)
    * [Example: STATIC\_TEST\*](/examples/macro_static_test.c)
  * Stack trace *(planned)*
* Generic types
  * [Display](/include/kernaux/generic/display.h) (*non-breaking since* **0.7.0**)
    * [Example](/examples/generic_display.c)
  * [Memory allocator](/include/kernaux/generic/malloc.h) (*non-breaking since* **0.5.0**)
    * [Example](/examples/generic_malloc.c)
  * [Mutex](/include/kernaux/generic/mutex.h) (*non-breaking since* **0.5.0**)
    * [Example](/examples/generic_mutex.c)
* Algorithms
  * [Free list memory allocator](/include/kernaux/free_list.h) (*non-breaking since* **0.5.0**)
  * [Simple command line parser](/include/kernaux/cmdline.h) (*non-breaking since* **0.2.0**)
    * [Example](/examples/cmdline.c)
  * [Page Frame Allocator](/include/kernaux/pfa.h) (*work in progress*)
    * [Example](/examples/pfa.c)
* Data formats
  * [ELF](/include/kernaux/elf.h) (*work in progress*)
  * [MBR](/include/kernaux/mbr.h) (*work in progress*)
  * [Multiboot 2 (GRUB 2)](/include/kernaux/multiboot2.h.in) (*non-breaking since* **0.7.0**)
    * [Example: header macros](/examples/multiboot2_header_macro.c)
* Utilities
  * [Measurement units utils](/include/kernaux/units.h) (*work in progress*)
    * [Example: To human](/examples/units_human.c)
  * [Memory map](/include/kernaux/memmap.h) (*non-breaking since* **0.7.0**)
    * [Example](/examples/memmap.c)
  * [printf format parser](/include/kernaux/printf_fmt.h) (*non-breaking since* **0.6.0**)
    * [Example](/examples/printf_fmt.c)
* Usual functions
  * [itoa/ftoa replacement](/include/kernaux/ntoa.h) (*non-breaking since* **0.4.0**)
    * [Example](/examples/ntoa.c)
  * [printf replacement](/include/kernaux/printf.h) (*non-breaking since* **0.5.0**)
    * [Example: fprintf](/examples/printf_file.c)
    * [Example: vfprintf](/examples/printf_file_va.c)
    * [Example: snprintf](/examples/printf_str.c)
    * [Example: vsnprintf](/examples/printf_str_va.c)
* libc replacement (*work in progress*)
  * [ctype.h](/libc/include/ctype.h)
  * [errno.h](/libc/include/errno.h)
  * [inttypes.h](/libc/include/inttypes.h)
  * [setjmp.h](/libc/include/setjmp.h)
  * [stdlib.h](/libc/include/stdlib.h)
  * [string.h](/libc/include/string.h)
  * [sys/types.h](/libc/include/sys/types.h)
* Architecture-specific code (*work in progress*)
  * [Declarations](/include/kernaux/arch/)
  * [Functions](/include/kernaux/asm/)

### Definitions

`#define` the following C preprocessor macros before including `<kernaux.h>` and
`<kernaux/*.h>` files. They have effect on your code, not the library code.

* `KERNAUX_ACCESS_PRIVATE` - disable access modifier "private". Don't do this!
* `KERNAUX_ACCESS_PROTECTED` - disable access modifier "protected". Only do this
  in a file where you implement an inherited type.
* `KERNAUX_BITFIELDS` - enable bitfields in packed structs. It doesn't follow
  the C standard and may be incompatible with some compilers.

### Global variables

```c
// in <kernaux/runtime.h>
void (*kernaux_assert_cb)(const char *file, int line, const char *msg)
```

Assertion callback. It's better to always set it to some function which always
interrupts the execution, even when assertions are disabled. It may for example
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

* `--enable-checks` - enable usual tests and examples
* `--enable-checks-all` - enable all checks
* `--enable-checks-cppcheck` - enable cppcheck
* `--enable-checks-pthreads` - enable tests that require pthreads
* `--enable-checks-python` - enable tests that require Python 3 with YAML and
  Jinja2
* `--enable-fixtures` - enable fixtures for tests and bindings
* `--enable-pkg-config[=PATH]` - install pkg-config files
  [PATH='${libdir}/pkgconfig']

#### Packages

* `--with-libc` - provides the replacement for some standard C functions.
  Useful in freestanding environment, where no libc is present.

### Default options

#### Features

* `--(enable|disable)-assert` - assertions
* `--(enable|disable)-float` - floating-point arithmetic
* `--(enable|disable)-werror` - fail on warning (`CFLAGS+='-Werror'`)

#### Packages

All packages are included by default. To exclude all packages except those
explicitly included, use `--without-all`.

* `--with[out]-arch-all` - all architectures
* `--with[out]-arch-i386` - architecture i386
* `--with[out]-arch-riscv64` - architecture riscv64
* `--with[out]-arch-x86-64` - architecture x86-64
* `--with[out]-asm` - kernel assembler helpers
* `--with[out]-cmdline` - command line parser
* `--with[out]-free-list` - free list memory allocator
* `--with[out]-memmap` - memory map
* `--with[out]-multiboot2` - Multiboot 2 utils
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
sudo ldconfig # on GNU/Linux
```

This is just a usual library. You can use most of it's APIs in hosted
environment.

### Development

```
./autogen.sh # if present
./configure --enable-fixtures --enable-checks # or --enable-checks-all, but see prerequisites
make
```

You can test with `make check`.

#### See also

* [GitHub Actions](/.github/) for **GNU/Linux** build environment
* [Cirrus CI](/.cirrus.yml) for **FreeBSD** build environment
* [sourcehut CI](/.openbsd.yml) for **OpenBSD** build environment

### Cross

Create configuration script with `./autogen.sh` (if present).

Let's assume that your target triplet is `i386-elf`. Configure with
[cross-compiler](https://wiki.osdev.org/GCC_Cross-Compiler) in `$PATH` to make
without it in `$PATH`:

```
./configure \
  --host='i386-elf' \
  --disable-shared \
  --enable-freestanding \
  --with-libc \
  CC="$(which i386-elf-gcc)"
```

The variables include `AR`, `AS`, `CC`, `CCAS`, `LD`, `NM`, `OBJDUMP`, `RANLIB`,
`STRIP`. See the generated `config.log` for more information.

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
