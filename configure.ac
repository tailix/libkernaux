AC_PREREQ([2.68])
AC_INIT([libkernaux],
  [0.0.0],
  [https://github.com/tailix/libkernaux/issues],
  [libkernaux],
  [https://github.com/tailix/libkernaux])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([src/pfa.c])

AC_CANONICAL_HOST



dnl Features (disabled by default)
AC_ARG_ENABLE([assert],      AS_HELP_STRING([--enable-assert],       [enable runtime assertions]))
AC_ARG_ENABLE([guard],       AS_HELP_STRING([--enable-guard],        [enable argument guards]))
AC_ARG_ENABLE([guard-cond],  AS_HELP_STRING([--enable-guard-cond],   [enable condition guard]))
AC_ARG_ENABLE([guard-null],  AS_HELP_STRING([--enable-guard-null],   [enable NULL-guard]))

dnl Packages (enabled by default)
AC_ARG_WITH(  [cmdline],     AS_HELP_STRING([--without-cmdline],     [without command line parser]))
AC_ARG_WITH(  [console],     AS_HELP_STRING([--without-console],     [without serial console]))
AC_ARG_WITH(  [elf],         AS_HELP_STRING([--without-elf],         [without ELF utils]))
AC_ARG_WITH(  [framebuffer], AS_HELP_STRING([--without-framebuffer], [without framebuffer]))
AC_ARG_WITH(  [itoa],        AS_HELP_STRING([--without-itoa],        [without itoa]))
AC_ARG_WITH(  [mbr],         AS_HELP_STRING([--without-mbr],         [without Master Boot Record]))
AC_ARG_WITH(  [multiboot2],  AS_HELP_STRING([--without-multiboot2],  [without Multiboot 2 information parser]))
AC_ARG_WITH(  [pfa],         AS_HELP_STRING([--without-pfa],         [without Page Frame Allocator]))
AC_ARG_WITH(  [printf],      AS_HELP_STRING([--without-printf],      [without printf]))
AC_ARG_WITH(  [units],       AS_HELP_STRING([--without-units],       [without measurement units utils]))

dnl Packages (disabled by default)
AC_ARG_WITH(  [libc],        AS_HELP_STRING([--with-libc],           [with libc replacement]))
AC_ARG_WITH(  [libc-memset], AS_HELP_STRING([--with-libc-memset],    [with memset replacement]))
AC_ARG_WITH(  [libc-strcpy], AS_HELP_STRING([--with-libc-strcpy],    [with strcpy replacement]))
AC_ARG_WITH(  [libc-strlen], AS_HELP_STRING([--with-libc-strlen],    [with strlen replacement]))



AC_DEFUN([do_enable_guard],
[
if test -z "$enable_guard_cond"; then enable_guard_cond=yes; fi
if test -z "$enable_guard_null"; then enable_guard_null=yes; fi
])
AS_IF([test "$enable_guard" = yes], do_enable_guard)

AC_DEFUN([do_with_libc],
[
if test -z "$with_libc_memset"; then with_libc_memset=yes; fi
if test -z "$with_libc_strcpy"; then with_libc_strcpy=yes; fi
if test -z "$with_libc_strlen"; then with_libc_strlen=yes; fi
])
AS_IF([test "$with_libc" = yes], do_with_libc)

AS_IF([test "$with_itoa" = no -a "$with_printf" != no], AC_MSG_ERROR([package `printf' requires package `itoa']))
AS_IF([test "$with_itoa" = no -a "$with_units"  != no], AC_MSG_ERROR([package `units' requires package `itoa']))



dnl Architecture
AM_CONDITIONAL([ASM_I386],          [test "$host_cpu" = i386])
AM_CONDITIONAL([ASM_RISCV64],       [test "$host_cpu" = riscv64])
AM_CONDITIONAL([ASM_X86_64],        [test "$host_cpu" = x86_64])

dnl Features (disabled by default)
AM_CONDITIONAL([ENABLE_ASSERT],     [test "$enable_assert"     = yes])
AM_CONDITIONAL([ENABLE_GUARD_COND], [test "$enable_guard_cond" = yes])
AM_CONDITIONAL([ENABLE_GUARD_NULL], [test "$enable_guard_null" = yes])

dnl Packages (enabled by default)
AM_CONDITIONAL([WITH_CMDLINE],      [test "$with_cmdline"      != no])
AM_CONDITIONAL([WITH_CONSOLE],      [test "$with_console"      != no])
AM_CONDITIONAL([WITH_ELF],          [test "$with_elf"          != no])
AM_CONDITIONAL([WITH_FRAMEBUFFER],  [test "$with_framebuffer"  != no])
AM_CONDITIONAL([WITH_ITOA],         [test "$with_itoa"         != no])
AM_CONDITIONAL([WITH_MBR],          [test "$with_mbr"          != no])
AM_CONDITIONAL([WITH_MULTIBOOT2],   [test "$with_multiboot2"   != no])
AM_CONDITIONAL([WITH_PFA],          [test "$with_pfa"          != no])
AM_CONDITIONAL([WITH_PRINTF],       [test "$with_printf"       != no])
AM_CONDITIONAL([WITH_UNITS],        [test "$with_units"        != no])

dnl Packages (disabled by default)
AM_CONDITIONAL([WITH_LIBC_MEMSET],  [test "$with_libc_memset"  = yes])
AM_CONDITIONAL([WITH_LIBC_STRCPY],  [test "$with_libc_strcpy"  = yes])
AM_CONDITIONAL([WITH_LIBC_STRLEN],  [test "$with_libc_strlen"  = yes])



dnl Architecture
AS_IF([test "$host_cpu" = i386],          [AC_DEFINE([ASM_I386],                  [1], [architecture is i386])])
AS_IF([test "$host_cpu" = riscv64],       [AC_DEFINE([ASM_RISCV64],               [1], [architecture is RISC-V 64-bit])])
AS_IF([test "$host_cpu" = x86_64],        [AC_DEFINE([ASM_X86_64],                [1], [architecture is x86_64])])

dnl Features (disabled by default)
AS_IF([test "$enable_assert"      = yes], [AC_DEFINE([KERNAUX_ENABLE_ASSERT],     [1], [enabled runtime assertions])])
AS_IF([test "$enable_guard_cond"  = yes], [AC_DEFINE([KERNAUX_ENABLE_GUARD_COND], [1], [enabled condition guard])])
AS_IF([test "$enable_guard_null"  = yes], [AC_DEFINE([KERNAUX_ENABLE_GUARD_NULL], [1], [enabled NULL-guard])])

dnl Packages (enabled by default)
AS_IF([test "$with_cmdline"       != no], [AC_DEFINE([WITH_CMDLINE],              [1], [with command line parser])])
AS_IF([test "$with_console"       != no], [AC_DEFINE([WITH_CONSOLE],              [1], [with serial console])])
AS_IF([test "$with_elf"           != no], [AC_DEFINE([WITH_ELF],                  [1], [with ELF utils])])
AS_IF([test "$with_framebuffer"   != no], [AC_DEFINE([WITH_FRAMEBUFFER],          [1], [with framebuffer])])
AS_IF([test "$with_itoa"          != no], [AC_DEFINE([WITH_ITOA],                 [1], [with itoa])])
AS_IF([test "$with_mbr"           != no], [AC_DEFINE([WITH_MBR],                  [1], [with Master Boot Record])])
AS_IF([test "$with_multiboot2"    != no], [AC_DEFINE([WITH_MULTIBOOT2],           [1], [with Multiboot 2 information parser])])
AS_IF([test "$with_pfa"           != no], [AC_DEFINE([WITH_PFA],                  [1], [with Page Frame Allocator])])
AS_IF([test "$with_printf"        != no], [AC_DEFINE([WITH_PRINTF],               [1], [with printf])])
AS_IF([test "$with_units",        != no], [AC_DEFINE([WITH_UNITS],                [1], [with measurement units utils])])

dnl Packages (disabled by default)
AS_IF([test "$with_libc_memset"   = yes], [AC_DEFINE([WITH_LIBC_MEMSET],          [1], [with memset replacement])])
AS_IF([test "$with_libc_strcpy"   = yes], [AC_DEFINE([WITH_LIBC_STRCPY],          [1], [with strcpy replacement])])
AS_IF([test "$with_libc_strlen"   = yes], [AC_DEFINE([WITH_LIBC_STRLEN],          [1], [with strlen replacement])])



AM_INIT_AUTOMAKE([1.9 subdir-objects])

AC_CONFIG_FILES([
  Makefile
  include/Makefile
])

AC_LANG([C])

AM_PROG_AR
AM_PROG_AS
AC_PROG_CC
AC_PROG_CC_C99
AC_PROG_RANLIB
AC_C_INLINE
AC_CHECK_HEADER_STDBOOL
AC_CHECK_HEADERS([stdarg.h stddef.h stdint.h])

AC_OUTPUT
