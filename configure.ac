AC_PREREQ([2.68])
AC_INIT([libkernaux],
  [0.0.0],
  [https://github.com/kernelmq/libkernaux/issues],
  [libkernaux],
  [https://github.com/kernelmq/libkernaux])

AC_CONFIG_SRCDIR([src/pfa.c])
AC_CONFIG_HEADERS([src/config.h])

AC_CANONICAL_HOST

AC_ARG_ENABLE([cmdline],    AS_HELP_STRING([--disable-cmdline],    [disable command line parser]))
AC_ARG_ENABLE([console],    AS_HELP_STRING([--disable-console],    [disable serial console]))
AC_ARG_ENABLE([multiboot2], AS_HELP_STRING([--disable-multiboot2], [disable Multiboot 2 information parser]))
AC_ARG_ENABLE([pfa],        AS_HELP_STRING([--disable-pfa],        [disable Page Frame Allocator]))

AM_CONDITIONAL([ARCH_X86],          [test x"$host_cpu" = x"x86"])
AM_CONDITIONAL([ENABLE_CMDLINE],    [test x"$enable_cmdline"    != x"no"])
AM_CONDITIONAL([ENABLE_CONSOLE],    [test x"$enable_console"    != x"no"])
AM_CONDITIONAL([ENABLE_MULTIBOOT2], [test x"$enable_multiboot2" != x"no"])
AM_CONDITIONAL([ENABLE_PFA],        [test x"$enable_pfa"        != x"no"])

AS_IF([test x"$host_cpu" = x"x86"],          [AC_DEFINE([ARCH_X86],          [1], [architecture is x86])])
AS_IF([test x"$enable_cmdline"    != x"no"], [AC_DEFINE([ENABLE_CMDLINE],    [1], [enabled command line parser])])
AS_IF([test x"$enable_console"    != x"no"], [AC_DEFINE([ENABLE_CONSOLE],    [1], [enabled serial console])])
AS_IF([test x"$enable_multiboot2" != x"no"], [AC_DEFINE([ENABLE_MULTIBOOT2], [1], [enabled Multiboot 2 information parser])])
AS_IF([test x"$enable_pfa"        != x"no"], [AC_DEFINE([ENABLE_PFA],        [1], [enabled Page Frame Allocator])])

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

AC_OUTPUT
