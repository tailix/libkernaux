AC_PREREQ([2.68])
AC_INIT([libkernaux],
  [0.0.0],
  [https://github.com/tailix/libkernaux/issues],
  [libkernaux],
  [https://github.com/tailix/libkernaux])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([src/pfa.c])

AC_CANONICAL_HOST

AC_ARG_ENABLE([cmdline],     AS_HELP_STRING([--disable-cmdline],    [disable command line parser]))
AC_ARG_ENABLE([console],     AS_HELP_STRING([--disable-console],    [disable serial console]))
AC_ARG_ENABLE([elf],         AS_HELP_STRING([--disable-elf],        [disable ELF utils]))
AC_ARG_ENABLE([multiboot2],  AS_HELP_STRING([--disable-multiboot2], [disable Multiboot 2 information parser]))
AC_ARG_ENABLE([pfa],         AS_HELP_STRING([--disable-pfa],        [disable Page Frame Allocator]))
AC_ARG_ENABLE([units],       AS_HELP_STRING([--disable-units],      [disable measurement units utils]))

AC_ARG_ENABLE([assert],      AS_HELP_STRING([--enable-assert],      [enable runtime assertions]))
AC_ARG_ENABLE([libc],        AS_HELP_STRING([--enable-libc],        [enable libc replacement]))
AC_ARG_ENABLE([libc-memset], AS_HELP_STRING([--enable-libc-memset], [enable memset replacement]))
AC_ARG_ENABLE([libc-strcpy], AS_HELP_STRING([--enable-libc-strcpy], [enable strcpy replacement]))
AC_ARG_ENABLE([libc-strlen], AS_HELP_STRING([--enable-libc-strlen], [enable strlen replacement]))
AC_ARG_ENABLE([null-guard],  AS_HELP_STRING([--enable-null-guard],  [enable NULL-guard]))

AC_DEFUN([do_enable_libc],
[
if test -z "$enable_libc_memset"; then enable_libc_memset=yes; fi
if test -z "$enable_libc_strcpy"; then enable_libc_strcpy=yes; fi
if test -z "$enable_libc_strlen"; then enable_libc_strlen=yes; fi
])
AS_IF([test "$enable_libc" = yes], do_enable_libc)

AM_CONDITIONAL([ARCH_I386],          [test "$host_cpu" = i386])
AM_CONDITIONAL([ARCH_X86_64],        [test "$host_cpu" = x86_64])

AM_CONDITIONAL([ENABLE_CMDLINE],     [test "$enable_cmdline"     != no])
AM_CONDITIONAL([ENABLE_CONSOLE],     [test "$enable_console"     != no])
AM_CONDITIONAL([ENABLE_ELF],         [test "$enable_elf"         != no])
AM_CONDITIONAL([ENABLE_MULTIBOOT2],  [test "$enable_multiboot2"  != no])
AM_CONDITIONAL([ENABLE_PFA],         [test "$enable_pfa"         != no])
AM_CONDITIONAL([ENABLE_UNITS],       [test "$enable_units"       != no])

AM_CONDITIONAL([ENABLE_ASSERT],      [test "$enable_assert"      = yes])
AM_CONDITIONAL([ENABLE_LIBC],        [test "$enable_libc"        = yes])
AM_CONDITIONAL([ENABLE_LIBC_MEMSET], [test "$enable_libc_memset" = yes])
AM_CONDITIONAL([ENABLE_LIBC_STRCPY], [test "$enable_libc_strcpy" = yes])
AM_CONDITIONAL([ENABLE_LIBC_STRLEN], [test "$enable_libc_strlen" = yes])
AM_CONDITIONAL([ENABLE_NULL_GUARD],  [test "$enable_null_guard"  = yes])

AS_IF([test "$host_cpu" = i386],          [AC_DEFINE([ARCH_I386],                  [1], [architecture is i386])])
AS_IF([test "$host_cpu" = x86_64],        [AC_DEFINE([ARCH_X86_64],                [1], [architecture is x86_64])])

AS_IF([test "$enable_cmdline"     != no], [AC_DEFINE([ENABLE_CMDLINE],             [1], [enabled command line parser])])
AS_IF([test "$enable_console"     != no], [AC_DEFINE([ENABLE_CONSOLE],             [1], [enabled serial console])])
AS_IF([test "$enable_elf"         != no], [AC_DEFINE([ENABLE_ELF],                 [1], [enabled ELF utils])])
AS_IF([test "$enable_multiboot2"  != no], [AC_DEFINE([ENABLE_MULTIBOOT2],          [1], [enabled Multiboot 2 information parser])])
AS_IF([test "$enable_pfa"         != no], [AC_DEFINE([ENABLE_PFA],                 [1], [enabled Page Frame Allocator])])
AS_IF([test "$enable_units",      != no], [AC_DEFINE([ENABLE_UNITS],               [1], [enabled measurement units utils])])

AS_IF([test "$enable_assert"      = yes], [AC_DEFINE([KERNAUX_ENABLE_ASSERT],      [1], [enabled runtime assertions])])
AS_IF([test "$enable_libc"        = yes], [AC_DEFINE([ENABLE_LIBC],                [1], [enabled libc replacement])])
AS_IF([test "$enable_libc_memset" = yes], [AC_DEFINE([ENABLE_LIBC_MEMSET],         [1], [enabled memset replacement])])
AS_IF([test "$enable_libc_strcpy" = yes], [AC_DEFINE([ENABLE_LIBC_STRCPY],         [1], [enabled strcpy replacement])])
AS_IF([test "$enable_libc_strlen" = yes], [AC_DEFINE([ENABLE_LIBC_STRLEN],         [1], [enabled strlen replacement])])
AS_IF([test "$enable_null_guard"  = yes], [AC_DEFINE([KERNAUX_ENABLE_NULL_GUARD],  [1], [enabled NULL-guard])])

AM_INIT_AUTOMAKE([1.9 subdir-objects -Wall -Werror])

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
