############################
# Specify program versions #
############################

AC_PREREQ([2.68])
LT_PREREQ([2.4.6])



#######################
# Initialize Autoconf #
#######################

AC_INIT([libkernaux],
  m4_normalize(m4_include([VERSION])),
  [https://github.com/tailix/libkernaux/issues],
  [libkernaux],
  [https://github.com/tailix/libkernaux])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST

AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([src/assert.c])
AC_CONFIG_FILES([
  Makefile
  examples/Makefile
  include/Makefile
  libc/Makefile
  libc/include/Makefile
  include/kernaux.h
  include/kernaux/console.h
  include/kernaux/printf.h
  include/kernaux/version.h
  tests/Makefile
])



###############
# Define args #
###############

dnl Features (enabled by default)
AC_ARG_ENABLE([debug],        AS_HELP_STRING([--disable-debug],       [disable debugging]))
AC_ARG_ENABLE([float],        AS_HELP_STRING([--disable-float],       [disable floating-point arithmetic]))
AC_ARG_ENABLE([werror],       AS_HELP_STRING([--disable-werror],      [disable -Werror]))

dnl Features (disabled by default)
AC_ARG_ENABLE([freestanding], AS_HELP_STRING([--enable-freestanding], [build for freestanding environment]))
AC_ARG_ENABLE([split-libc],   AS_HELP_STRING([--enable-split-libc],   [split off libc]))
AC_ARG_ENABLE([tests],        AS_HELP_STRING([--enable-tests],        [enable usual tests and examples]))
AC_ARG_ENABLE([tests-all],    AS_HELP_STRING([--enable-tests-all],    [enable all tests]))
AC_ARG_ENABLE([tests-python], AS_HELP_STRING([--enable-tests-python], [enable tests that require Python 3 with YAML and Jinja2]))

dnl Packages (enabled by default)
AC_ARG_WITH(  [all],          AS_HELP_STRING([--without-all],         [without all default packages]))
AC_ARG_WITH(  [cmdline],      AS_HELP_STRING([--without-cmdline],     [without command line parser]))
AC_ARG_WITH(  [console],      AS_HELP_STRING([--without-console],     [without serial console]))
AC_ARG_WITH(  [elf],          AS_HELP_STRING([--without-elf],         [without ELF utils]))
AC_ARG_WITH(  [framebuffer],  AS_HELP_STRING([--without-framebuffer], [without framebuffer]))
AC_ARG_WITH(  [io],           AS_HELP_STRING([--without-io],          [without input/output]))
AC_ARG_WITH(  [mbr],          AS_HELP_STRING([--without-mbr],         [without Master Boot Record]))
AC_ARG_WITH(  [memmap],       AS_HELP_STRING([--without-memmap],      [without memory map]))
AC_ARG_WITH(  [multiboot2],   AS_HELP_STRING([--without-multiboot2],  [without Multiboot 2 information parser]))
AC_ARG_WITH(  [ntoa],         AS_HELP_STRING([--without-ntoa],        [without itoa/ftoa]))
AC_ARG_WITH(  [pfa],          AS_HELP_STRING([--without-pfa],         [without Page Frame Allocator]))
AC_ARG_WITH(  [printf],       AS_HELP_STRING([--without-printf],      [without printf]))
AC_ARG_WITH(  [printf-fmt],   AS_HELP_STRING([--without-printf-fmt],  [without printf format parser]))
AC_ARG_WITH(  [units],        AS_HELP_STRING([--without-units],       [without measurement units utils]))

dnl Packages (disabled by default)
AC_ARG_WITH(  [libc],         AS_HELP_STRING([--with-libc],           [with libc replacement]))



################
# Default args #
################

AC_DEFUN([do_enable_tests_all],
[
if test -z "$enable_tests";        then enable_tests=yes;        fi
if test -z "$enable_tests_python"; then enable_tests_python=yes; fi
])
AS_IF([test "$enable_tests_all" = yes], do_enable_tests_all)

AC_DEFUN([do_without_all],
[
if test -z "$with_cmdline";     then with_cmdline=no;     fi
if test -z "$with_console";     then with_console=no;     fi
if test -z "$with_elf";         then with_elf=no;         fi
if test -z "$with_framebuffer"; then with_framebuffer=no; fi
if test -z "$with_io";          then with_io=no;          fi
if test -z "$with_mbr";         then with_mbr=no;         fi
if test -z "$with_memmap";      then with_memmap=no;      fi
if test -z "$with_multiboot2";  then with_multiboot2=no;  fi
if test -z "$with_ntoa";        then with_ntoa=no;        fi
if test -z "$with_pfa";         then with_pfa=no;         fi
if test -z "$with_printf";      then with_printf=no;      fi
if test -z "$with_printf_fmt";  then with_printf_fmt=no;  fi
if test -z "$with_units";       then with_units=no;       fi
])
AS_IF([test "$with_all" = no], do_without_all)



##################
# Normalize args #
##################

dnl Features (enabled by default)
AS_IF([test "$enable_debug"        = no ], [enable_debug=no],         [enable_debug=yes])
AS_IF([test "$enable_float"        = no ], [enable_float=no],         [enable_float=yes])
AS_IF([test "$enable_werror"       = no ], [enable_werror=no],        [enable_werror=yes])

dnl Features (disabled by default)
AS_IF([test "$enable_freestanding" = yes], [enable_freestanding=yes], [enable_freestanding=no])
AS_IF([test "$enable_split_libc"   = yes], [enable_split_libc=yes],   [enable_split_libc=no])
AS_IF([test "$enable_tests"        = yes], [enable_tests=yes],        [enable_tests=no])
AS_IF([test "$enable_tests_all"    = yes], [enable_tests_all=yes],    [enable_tests_all=no])
AS_IF([test "$enable_tests_python" = yes], [enable_tests_python=yes], [enable_tests_python=no])

dnl Packages (enabled by default)
AS_IF([test "$with_all"            = no ], [with_all=no],             [with_all=yes])
AS_IF([test "$with_cmdline"        = no ], [with_cmdline=no],         [with_cmdline=yes])
AS_IF([test "$with_console"        = no ], [with_console=no],         [with_console=yes])
AS_IF([test "$with_elf"            = no ], [with_elf=no],             [with_elf=yes])
AS_IF([test "$with_framebuffer"    = no ], [with_framebuffer=no],     [with_framebuffer=yes])
AS_IF([test "$with_io"             = no ], [with_io=no],              [with_io=yes])
AS_IF([test "$with_mbr"            = no ], [with_mbr=no],             [with_mbr=yes])
AS_IF([test "$with_memmap"         = no ], [with_memmap=no],          [with_memmap=yes])
AS_IF([test "$with_multiboot2"     = no ], [with_multiboot2=no],      [with_multiboot2=yes])
AS_IF([test "$with_ntoa"           = no ], [with_ntoa=no],            [with_ntoa=yes])
AS_IF([test "$with_pfa"            = no ], [with_pfa=no],             [with_pfa=yes])
AS_IF([test "$with_printf"         = no ], [with_printf=no],          [with_printf=yes])
AS_IF([test "$with_printf_fmt"     = no ], [with_printf_fmt=no],      [with_printf_fmt=yes])
AS_IF([test "$with_units"          = no ], [with_units=no],           [with_units=yes])

dnl Packages (disabled by default)
AS_IF([test "$with_libc"           = yes], [with_libc=yes],           [with_libc=no])



#############
# Test args #
#############

AS_IF([test "$enable_tests"        = yes -a "$host_cpu" != "$build_cpu" ], AC_MSG_ERROR([can not build cross-platform tests]))
AS_IF([test "$enable_tests_python" = yes -a "$host_cpu" != "$build_cpu" ], AC_MSG_ERROR([can not build cross-platform tests]))
AS_IF([test "$enable_tests"        = yes -a "$enable_freestanding" = yes], AC_MSG_ERROR([can not build freestanding tests]))
AS_IF([test "$enable_tests_python" = yes -a "$enable_freestanding" = yes], AC_MSG_ERROR([can not build freestanding tests]))
AS_IF([test "$enable_tests"        = yes -a "$with_libc"           = yes], AC_MSG_ERROR([can not use package `libc' with tests]))
AS_IF([test "$enable_tests_python" = yes -a "$with_libc"           = yes], AC_MSG_ERROR([can not use package `libc' with tests]))

AS_IF([test "$with_printf" = yes -a "$with_ntoa"       = no], AC_MSG_ERROR([package `printf' requires package `ntoa']))
AS_IF([test "$with_printf" = yes -a "$with_printf_fmt" = no], AC_MSG_ERROR([package `printf' requires package `printf-fmt']))
AS_IF([test "$with_units"  = yes -a "$with_ntoa"       = no], AC_MSG_ERROR([package `units' requires package `ntoa']))



#########################
# Automake conditionals #
#########################

dnl Architecture
AM_CONDITIONAL([ASM_I386],            [test "$host_cpu" = i386])
AM_CONDITIONAL([ASM_RISCV64],         [test "$host_cpu" = riscv64])
AM_CONDITIONAL([ASM_X86_64],          [test "$host_cpu" = x86_64])

dnl Features (enabled by default)
AM_CONDITIONAL([ENABLE_DEBUG],        [test "$enable_debug"        = yes])
AM_CONDITIONAL([ENABLE_FLOAT],        [test "$enable_float"        = yes])
AM_CONDITIONAL([ENABLE_WERROR],       [test "$enable_werror"       = yes])

dnl Features (disabled by default)
AM_CONDITIONAL([ENABLE_FREESTANDING], [test "$enable_freestanding" = yes])
AM_CONDITIONAL([ENABLE_SPLIT_LIBC],   [test "$enable_split_libc"   = yes])
AM_CONDITIONAL([ENABLE_TESTS],        [test "$enable_tests"        = yes])
AM_CONDITIONAL([ENABLE_TESTS_PYTHON], [test "$enable_tests_python" = yes])

dnl Packages (enabled by default)
AM_CONDITIONAL([WITH_CMDLINE],        [test "$with_cmdline"        = yes])
AM_CONDITIONAL([WITH_CONSOLE],        [test "$with_console"        = yes])
AM_CONDITIONAL([WITH_ELF],            [test "$with_elf"            = yes])
AM_CONDITIONAL([WITH_FRAMEBUFFER],    [test "$with_framebuffer"    = yes])
AM_CONDITIONAL([WITH_IO],             [test "$with_io"             = yes])
AM_CONDITIONAL([WITH_MBR],            [test "$with_mbr"            = yes])
AM_CONDITIONAL([WITH_MEMMAP],         [test "$with_memmap"         = yes])
AM_CONDITIONAL([WITH_MULTIBOOT2],     [test "$with_multiboot2"     = yes])
AM_CONDITIONAL([WITH_NTOA],           [test "$with_ntoa"           = yes])
AM_CONDITIONAL([WITH_PFA],            [test "$with_pfa"            = yes])
AM_CONDITIONAL([WITH_PRINTF],         [test "$with_printf"         = yes])
AM_CONDITIONAL([WITH_PRINTF_FMT],     [test "$with_printf_fmt"     = yes])
AM_CONDITIONAL([WITH_UNITS],          [test "$with_units"          = yes])

dnl Packages (disabled by default)
AM_CONDITIONAL([WITH_LIBC],           [test "$with_libc"           = yes])



####################
# Autoconf defines #
####################

dnl Architecture
AS_IF([test "$host_cpu" = i386],           [AC_DEFINE([ASM_I386],            [1], [architecture is i386])])
AS_IF([test "$host_cpu" = riscv64],        [AC_DEFINE([ASM_RISCV64],         [1], [architecture is RISC-V 64-bit])])
AS_IF([test "$host_cpu" = x86_64],         [AC_DEFINE([ASM_X86_64],          [1], [architecture is x86_64])])

dnl Features (enabled by default)
AS_IF([test "$enable_debug"        = yes], [AC_DEFINE([ENABLE_DEBUG],        [1], [enabled debugging])])
AS_IF([test "$enable_float"        = yes], [AC_DEFINE([ENABLE_FLOAT],        [1], [enabled floating-point arithmetic])])
AS_IF([test "$enable_werror"       = yes], [AC_DEFINE([ENABLE_WERROR],       [1], [enabled -Werror])])

dnl Features (disabled by default)
AS_IF([test "$enable_split_libc"   = yes], [AC_DEFINE([ENABLE_SPLIT_LIBC],   [1], [split off libc])])
AS_IF([test "$enable_freestanding" = yes], [AC_DEFINE([ENABLE_FREESTANDING], [1], [build for freestanding environment])])
AS_IF([test "$enable_tests"        = yes], [AC_DEFINE([ENABLE_TESTS],        [1], [enabled usual tests and examples])])
AS_IF([test "$enable_tests_python" = yes], [AC_DEFINE([ENABLE_TESTS_PYTHON], [1], [enabled tests that require Python 3 with YAML and Jinja2])])

dnl Packages (enabled by default)
AS_IF([test "$with_cmdline"        = yes], [AC_DEFINE([WITH_CMDLINE],        [1], [with command line parser])])
AS_IF([test "$with_console"        = yes], [AC_DEFINE([WITH_CONSOLE],        [1], [with serial console])])
AS_IF([test "$with_elf"            = yes], [AC_DEFINE([WITH_ELF],            [1], [with ELF utils])])
AS_IF([test "$with_framebuffer"    = yes], [AC_DEFINE([WITH_FRAMEBUFFER],    [1], [with framebuffer])])
AS_IF([test "$with_io"             = yes], [AC_DEFINE([WITH_IO],             [1], [with input/output])])
AS_IF([test "$with_mbr"            = yes], [AC_DEFINE([WITH_MBR],            [1], [with Master Boot Record])])
AS_IF([test "$with_memmap"         = yes], [AC_DEFINE([WITH_MEMMAP],         [1], [with memory map])])
AS_IF([test "$with_multiboot2"     = yes], [AC_DEFINE([WITH_MULTIBOOT2],     [1], [with Multiboot 2 information parser])])
AS_IF([test "$with_ntoa"           = yes], [AC_DEFINE([WITH_NTOA],           [1], [with ntoa])])
AS_IF([test "$with_pfa"            = yes], [AC_DEFINE([WITH_PFA],            [1], [with Page Frame Allocator])])
AS_IF([test "$with_printf"         = yes], [AC_DEFINE([WITH_PRINTF],         [1], [with printf])])
AS_IF([test "$with_printf_fmt"     = yes], [AC_DEFINE([WITH_PRINTF_FMT],     [1], [with printf format parser])])
AS_IF([test "$with_units",         = yes], [AC_DEFINE([WITH_UNITS],          [1], [with measurement units utils])])

dnl Packages (disabled by default)
AS_IF([test "$with_libc"           = yes], [AC_DEFINE([WITH_LIBC],           [1], [with libc replacement])])

dnl Additional
AS_IF([test "$enable_debug"        = yes], [AC_DEFINE([KERNAUX_DEBUG],       [1], [enabled debugging])])



##########################
# Autoconf substitutions #
##########################

dnl Packages (enabled by default)
AS_IF([test "$with_cmdline"     = no], [AC_SUBST([comment_line_cmdline],     [//])])
AS_IF([test "$with_console"     = no], [AC_SUBST([comment_line_console],     [//])])
AS_IF([test "$with_elf"         = no], [AC_SUBST([comment_line_elf],         [//])])
AS_IF([test "$with_framebuffer" = no], [AC_SUBST([comment_line_framebuffer], [//])])
AS_IF([test "$with_io"          = no], [AC_SUBST([comment_line_io],          [//])])
AS_IF([test "$with_mbr"         = no], [AC_SUBST([comment_line_mbr],         [//])])
AS_IF([test "$with_memmap"      = no], [AC_SUBST([comment_line_memmap],      [//])])
AS_IF([test "$with_multiboot2"  = no], [AC_SUBST([comment_line_multiboot2],  [//])])
AS_IF([test "$with_ntoa"        = no], [AC_SUBST([comment_line_ntoa],        [//])])
AS_IF([test "$with_pfa"         = no], [AC_SUBST([comment_line_pfa],         [//])])
AS_IF([test "$with_printf"      = no], [AC_SUBST([comment_line_printf],      [//])])
AS_IF([test "$with_printf_fmt"  = no], [AC_SUBST([comment_line_printf_fmt],  [//])])
AS_IF([test "$with_units"       = no], [AC_SUBST([comment_line_units],       [//])])



###################
# Set build flags #
###################

AC_DEFUN([do_enable_freestanding],  [CFLAGS+=' -nostdlib -ffreestanding -fno-pic -fno-stack-protector '])
AC_DEFUN([do_disable_freestanding], [CFLAGS+=' -fpic '])
AS_IF([test "$enable_freestanding" = yes], do_enable_freestanding, do_disable_freestanding)



#######################
# Initialize Automake #
#######################

AM_INIT_AUTOMAKE([1.16 subdir-objects])



##############
# Run checks #
##############

AC_LANG([C])

AM_PROG_AR
AM_PROG_AS
AC_PROG_CC
AC_PROG_CC_C99
AC_C_INLINE
AC_CHECK_HEADER_STDBOOL
AC_CHECK_HEADERS([stdarg.h stddef.h stdint.h])



######################
# Initialize Libtool #
######################

LT_INIT([disable-shared])



##########
# Finish #
##########

AC_OUTPUT
