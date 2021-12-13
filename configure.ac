AC_PREREQ([2.68])
AC_INIT([libkernaux],
  [0.0.0],
  [https://github.com/tailix/libkernaux/issues],
  [libkernaux],
  [https://github.com/tailix/libkernaux])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([src/pfa.c])

AC_CANONICAL_HOST

AC_ARG_ENABLE([cmdline],    AS_HELP_STRING([--disable-cmdline],    [disable command line parser]))
AC_ARG_ENABLE([console],    AS_HELP_STRING([--disable-console],    [disable serial console]))
AC_ARG_ENABLE([multiboot2], AS_HELP_STRING([--disable-multiboot2], [disable Multiboot 2 information parser]))
AC_ARG_ENABLE([pfa],        AS_HELP_STRING([--disable-pfa],        [disable Page Frame Allocator]))
AC_ARG_ENABLE([units],      AS_HELP_STRING([--disable-units],      [disable measurement units utils]))

AM_CONDITIONAL([ARCH_I386],         [test "$host_cpu" = i386])
AM_CONDITIONAL([ARCH_X86_64],       [test "$host_cpu" = x86_64])
AM_CONDITIONAL([ENABLE_CMDLINE],    [test "$enable_cmdline"    != no])
AM_CONDITIONAL([ENABLE_CONSOLE],    [test "$enable_console"    != no])
AM_CONDITIONAL([ENABLE_MULTIBOOT2], [test "$enable_multiboot2" != no])
AM_CONDITIONAL([ENABLE_PFA],        [test "$enable_pfa"        != no])
AM_CONDITIONAL([ENABLE_UNITS],      [test "$enable_units"      != no])

AS_IF([test "$host_cpu" = i386],         [AC_DEFINE([ARCH_I386],         [1], [architecture is i386])])
AS_IF([test "$host_cpu" = x86_64],       [AC_DEFINE([ARCH_X86_64],       [1], [architecture is x86_64])])
AS_IF([test "$enable_cmdline"    != no], [AC_DEFINE([ENABLE_CMDLINE],    [1], [enabled command line parser])])
AS_IF([test "$enable_console"    != no], [AC_DEFINE([ENABLE_CONSOLE],    [1], [enabled serial console])])
AS_IF([test "$enable_multiboot2" != no], [AC_DEFINE([ENABLE_MULTIBOOT2], [1], [enabled Multiboot 2 information parser])])
AS_IF([test "$enable_pfa"        != no], [AC_DEFINE([ENABLE_PFA],        [1], [enabled Page Frame Allocator])])
AS_IF([test "$enable_units",     != no], [AC_DEFINE([ENABLE_UNITS],      [1], [enable measurement units utils])])

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
AC_CHECK_HEADERS([stdarg.h stddef.h])

AC_OUTPUT
