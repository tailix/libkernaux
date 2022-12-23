Releases
========



0.7.0 (2022-12-23)
------------------

169 files changed, 6332 insertions(+), 3858 deletions(-)

### Breaking changes

* `./configure` - feature `--(enable|disable)-debug` has been removed.
* `<kernaux/*>` - definition `KERNAUX_DEBUG` has been removed.
* `<kernaux/assert.h>` - it has been removed.
* `<kernaux/memmap.h>` - it has been completely rewritten.

### New features

* `./configure` - feature `--(enable|disable)-fixtures` has been added.
* `./configure` - feature `--(enable|disable)-pkg-config[=PATH` has been added.
  It allows you to specify where to install **pkg-config** files.
* `./configure` - package `--with[out]-multiboot2` has been added.
* `<kernaux/*>` - definition `KERNAUX_BITFIELDS` has been added.
* `<kernaux/generic/display.h>` - new header.
* `<kernaux/macro.h>` - macro `KERNAUX_STATIC_TEST` has been added.
* `<kernaux/macro.h>` - macros `KERNAUX_CAST_(VAR|CONST)` have been added.
* `<kernaux/multiboot2.h>` - new header.
* `<kernaux/runtime.h>` - new header. Now it contains the variable
  `kernaux_assert_cb`.

### Other changes

* `./configure` - a shared library is built by default.
* `<kernaux/*>` - the headers are the same regardless of the selection
  of features and packages (except `<kernaux/version.h>`).
* `examples/Makefile` - the test suite can be built now without **pthreads**.
* `tests/Makefile` - the ability to run tests from with any working directory
  has been added.
* `tests/Makefile` - the test suite has been fixed to run on FreeBSD.



0.6.1 (2022-12-05)
------------------

12 files changed, 111 insertions(+), 110 deletions(-)

### Other changes

* `./configure` - fix a bug with building for a freestanding environment
* `Makefile` - fix cppcheck in out-of-root builds
* `Makefile` - fix Python tests if out-of-root builds



0.6.0 (2022-12-04)
------------------

121 files changed, 1444 insertions(+), 1806 deletions(-)

### Breaking changes

* `./configure` - features `--enable-tests*` have been renamed
  to `--enable-checks*`.
* `<kernaux/macro.h>` - macro `KERNAUX_PACKING_ATTR` has been renamed
  to `KERNAUX_PACKED`.

### New features

* `./configure` - feature `--enable-checks-cppcheck` has been added.
* `Makefile` - task `check-cppcheck` has been added.
* `<kernaux/macro.h>` - macros `KERNAUX_ALIGNED`, `KERNAUX_ASM`,
  `KERNAUX_NORETURN`, `KERNAUX_PRINTF`, `KERNAUX_RETURNS_TWICE`,
  `KERNAUX_SECTION`, `KERNAUX_UNUSED`, `KERNAUX_USED` have been added.
* `<kernaux/printf_fmt.h>` - new header. It's printf format parser.

### Other changes

* `<kernaux/free_list.h>` - fix a bug that was making the allocator unusable.
* `<kernaux/printf.h>` - fix displaying floating-point numbers with big
  precision.



0.5.0 (2022-11-26)
------------------

138 files changed, 2962 insertions(+), 1741 deletions(-)

### Breaking changes

* `./configure` - package `--with[out]-io` has been removed.
* `<kernaux/io.h>` - the header has been removed.
* `<kernaux/printf.h>` - the API of the functions functions `[v]fprintf` has
  been changed.

### New features

* `./configure` - package `--with[out]-asm` has been added.
* `./configure` - packages `--with[out]-arch-(all|i386|riscv64|x86-64)` have
  been added.
* `./configure` - package `--with[out]-drivers` has been added.
* `./configure` - package `--with[out]-free-list` has been added.
* `<kernaux/free_list.h>` - new header. It's a free list memory allocator.
* `<kernaux/macro.h>` - new header. It's a set of macros.
* `<kernaux/macro.h>` - macro `KERNAUX_PRIVATE_FIELD` has been added.
* `<kernaux/macro.h>` - macro `KERNAUX_PROTECTED_FIELD` has been added.
* `<kernaux/macro.h>` - macros `KERNAUX_BITS[8|16|32|64]` have been added.
* `<kernaux/macro.h>` - macros `KERNAUX_CONTAINER_OF` have been added.
* `<kernaux/generic/malloc.h>` - new header. It's a generic memory allocator
  interface.
* `<kernaux/generic/mutex.h>` - new header. It's a generic mutex interface.
* Definition `KERNAUX_ACCESS_PRIVATE` has been added.
* Definition `KERNAUX_ACCESS_PROTECTED` has been added.



0.4.0 (2022-06-16)
------------------

225 files changed, 8625 insertions(+), 3744 deletions(-)

### Breaking changes

* `./configure` - feature `--(enable|disable)-bloat` has been removed.
* `./configure` - feature `--(enable|disable)-pic` has been removed.
* `<kernaux/assert.h>` - API has been completely changed.
* `<kernaux/libc.h>` - header has been removed.
* `<kernaux/ntoa.h>` - API has been completely changed.
* `<kernaux/printf.h>` - Easter egg has been removed.
* `<kernaux/printf.h>` - functions `[v]printf` have been renamed to `[v]fprintf`,
  API has been changed.

### New features

* `./configure` - new feature `--(enable|disable)-debug`.
* `./configure` - new package `--with[out]-io`.
* `./configure` - new package `--with[out]-memmap`.
* `<kernaux/memmap.h>` - new header. It's a memory map.



0.3.0 (2022-05-28)
------------------

134 files changed, 6149 insertions(+), 1770 deletions(-)

### Breaking changes

* `<kernaux/assert.h>` - a semicolon is required after macros.
* `<kernaux/assert.h>` - the constant `KERNAUX_ITOA_BUFFER_SIZE` is renamed to
  `KERNAUX_ITOA10_BUFFER_SIZE`.

### New features

* `./configure` - testing may be enabled with `--enable-tests`,
  `--enable-tests-all`, `--enable-tests-python`.
* `./configure` - the heavy binary data may be disabled with `--disable-bloat`.
* `./configure` - position-independent code is generated by default, disable
  with `--disable-pic`.
* `./configure` - compiler warnings turn into errors by default, disable with
  `--disable-werror`.
* `<kernaux/libc.h>` - added functions `atoi`, `isdigit`, `isspace`.
* `<kernaux/ntoa.h>` - added functions `kernaux_[u|i]toa`, `kernaux_[u|i]toa16`
  and related constants.

### Other changes

* Assertions are used more broadly.
* `<kernaux.h>` - the header is now generated from template depending on
  configuration options, so you may safely include it when some packages are
  missing, it won't cause compilation error.
* `<kernaux/printf.h>` - a potential buffer overflow is fixed.



0.2.0 (2022-01-22)
------------------

51 files changed, 1647 insertions(+), 501 deletions(-)

### Breaking changes

* `./configure` - removed options to disable panic calls and returns in
  `<kernaux/assert.h>`.
* `<kernaux/assert.h>` - removed preprocessor directives that can disable panic
  calls and returns.

### New features

* `<kernaux/cmdline.h>` is stable now. It's a simple command line parser.

### Other changes

* Now `./configure` options also follow semantic versioning.
* Bug fixes in `<kernaux/printf.h>`.



0.1.0 (2022-01-20)
------------------

Initial release.
