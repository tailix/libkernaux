AC_PREREQ([2.68])
AC_INIT([libkernaux],
  [0.0.0],
  [https://github.com/kernelmq/libkernaux/issues],
  [libkernaux],
  [https://github.com/kernelmq/libkernaux])

AC_CONFIG_SRCDIR([src/pfa.c])
AC_CONFIG_HEADERS([src/config.h])

AC_CANONICAL_HOST

AS_IF([test x"${host_cpu}" = x"x86"],
  [AC_DEFINE([ARCH_X86],[1],[architecture is x86])])

AM_CONDITIONAL(ARCH_X86, test x"${host_cpu}" = x"x86")

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

AC_OUTPUT
