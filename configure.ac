AC_PREREQ([2.68])
AC_INIT([libkernaux],
  [0.3.0],
  [https://github.com/tailix/libkernaux/issues],
  [libkernaux],
  [https://github.com/tailix/libkernaux])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([src/assert.c])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST



###############
# Define args #
###############

dnl Features (enabled by default)
AC_ARG_ENABLE([bloat],             AS_HELP_STRING([--disable-bloat],          [disable unnecessary heavy binary data]))
AC_ARG_ENABLE([float],             AS_HELP_STRING([--disable-float],          [disable floating-point arithmetic]))
AC_ARG_ENABLE([werror],            AS_HELP_STRING([--disable-werror],         [disable -Werror]))

dnl Features (disabled by default)
AC_ARG_ENABLE([freestanding],      AS_HELP_STRING([--enable-freestanding],    [build for freestanding environment]))
AC_ARG_ENABLE([tests],             AS_HELP_STRING([--enable-tests],           [enable usual tests and examples]))
AC_ARG_ENABLE([tests-all],         AS_HELP_STRING([--enable-tests-all],       [enable all tests]))
AC_ARG_ENABLE([tests-python],      AS_HELP_STRING([--enable-tests-python],    [enable tests that require Python 3 with YAML and Jinja2]))

dnl Packages (enabled by default)
AC_ARG_WITH(  [all],               AS_HELP_STRING([--without-all],            [without all default packages]))
AC_ARG_WITH(  [cmdline],           AS_HELP_STRING([--without-cmdline],        [without command line parser]))
AC_ARG_WITH(  [console],           AS_HELP_STRING([--without-console],        [without serial console]))
AC_ARG_WITH(  [elf],               AS_HELP_STRING([--without-elf],            [without ELF utils]))
AC_ARG_WITH(  [framebuffer],       AS_HELP_STRING([--without-framebuffer],    [without framebuffer]))
AC_ARG_WITH(  [mbr],               AS_HELP_STRING([--without-mbr],            [without Master Boot Record]))
AC_ARG_WITH(  [multiboot2],        AS_HELP_STRING([--without-multiboot2],     [without Multiboot 2 information parser]))
AC_ARG_WITH(  [ntoa],              AS_HELP_STRING([--without-ntoa],           [without itoa/ftoa]))
AC_ARG_WITH(  [pfa],               AS_HELP_STRING([--without-pfa],            [without Page Frame Allocator]))
AC_ARG_WITH(  [printf],            AS_HELP_STRING([--without-printf],         [without printf]))
AC_ARG_WITH(  [printf-fmt],        AS_HELP_STRING([--without-printf-fmt],     [without printf format parser]))
AC_ARG_WITH(  [units],             AS_HELP_STRING([--without-units],          [without measurement units utils]))

dnl Packages (disabled by default)
AC_ARG_WITH(  [libc-all],          AS_HELP_STRING([--with-libc-all],          [with libc replacement]))
AC_ARG_WITH(  [libc-atoi],         AS_HELP_STRING([--with-libc-atoi],         [with atoi replacement]))
AC_ARG_WITH(  [libc-isdigit],      AS_HELP_STRING([--with-libc-isdigit],      [with isdigit replacement]))
AC_ARG_WITH(  [libc-isspace],      AS_HELP_STRING([--with-libc-isspace],      [with isspace replacement]))
AC_ARG_WITH(  [libc-memset],       AS_HELP_STRING([--with-libc-memset],       [with memset replacement]))
AC_ARG_WITH(  [libc-strcpy],       AS_HELP_STRING([--with-libc-strcpy],       [with strcpy replacement]))
AC_ARG_WITH(  [libc-strlen],       AS_HELP_STRING([--with-libc-strlen],       [with strlen replacement]))
AC_ARG_WITH(  [libc-strnlen],      AS_HELP_STRING([--with-libc-strnlen],      [with strnlen replacement]))
AC_ARG_WITH(  [tester-multiboot2], AS_HELP_STRING([--with-tester-multiboot2], [with Multiboot 2 tester]))
AC_ARG_WITH(  [tester-stivale2],   AS_HELP_STRING([--with-tester-stivale2],   [with Stivale 2 tester]))



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
if test -z "$with_mbr";         then with_mbr=no;         fi
if test -z "$with_multiboot2";  then with_multiboot2=no;  fi
if test -z "$with_ntoa";        then with_ntoa=no;        fi
if test -z "$with_pfa";         then with_pfa=no;         fi
if test -z "$with_printf";      then with_printf=no;      fi
if test -z "$with_printf_fmt";  then with_printf_fmt=no;  fi
if test -z "$with_units";       then with_units=no;       fi
])
AS_IF([test "$with_all" = no], do_without_all)

AC_DEFUN([do_with_libc_all],
[
if test -z "$with_libc_atoi";    then with_libc_atoi=yes;    fi
if test -z "$with_libc_isdigit"; then with_libc_isdigit=yes; fi
if test -z "$with_libc_isspace"; then with_libc_isspace=yes; fi
if test -z "$with_libc_memset";  then with_libc_memset=yes;  fi
if test -z "$with_libc_strcpy";  then with_libc_strcpy=yes;  fi
if test -z "$with_libc_strlen";  then with_libc_strlen=yes;  fi
if test -z "$with_libc_strnlen"; then with_libc_strnlen=yes; fi
])
AS_IF([test "$with_libc_all" = yes], do_with_libc_all)



##################
# Normalize args #
##################

dnl Features (enabled by default)
AS_IF([test "$enable_bloat"           = no ], [enable_bloat=no],            [enable_bloat=yes])
AS_IF([test "$enable_float"           = no ], [enable_float=no],            [enable_float=yes])
AS_IF([test "$enable_werror"          = no ], [enable_werror=no],           [enable_werror=yes])

dnl Features (disabled by default)
AS_IF([test "$enable_freestanding"    = yes], [enable_freestanding=yes],    [enable_freestanding=no])
AS_IF([test "$enable_tests"           = yes], [enable_tests=yes],           [enable_tests=no])
AS_IF([test "$enable_tests_all"       = yes], [enable_tests_all=yes],       [enable_tests_all=no])
AS_IF([test "$enable_tests_python"    = yes], [enable_tests_python=yes],    [enable_tests_python=no])

dnl Packages (enabled by default)
AS_IF([test "$with_all"               = no ], [with_all=no],                [with_all=yes])
AS_IF([test "$with_cmdline"           = no ], [with_cmdline=no],            [with_cmdline=yes])
AS_IF([test "$with_console"           = no ], [with_console=no],            [with_console=yes])
AS_IF([test "$with_elf"               = no ], [with_elf=no],                [with_elf=yes])
AS_IF([test "$with_framebuffer"       = no ], [with_framebuffer=no],        [with_framebuffer=yes])
AS_IF([test "$with_mbr"               = no ], [with_mbr=no],                [with_mbr=yes])
AS_IF([test "$with_multiboot2"        = no ], [with_multiboot2=no],         [with_multiboot2=yes])
AS_IF([test "$with_ntoa"              = no ], [with_ntoa=no],               [with_ntoa=yes])
AS_IF([test "$with_pfa"               = no ], [with_pfa=no],                [with_pfa=yes])
AS_IF([test "$with_printf"            = no ], [with_printf=no],             [with_printf=yes])
AS_IF([test "$with_printf_fmt"        = no ], [with_printf_fmt=no],         [with_printf_fmt=yes])
AS_IF([test "$with_units"             = no ], [with_units=no],              [with_units=yes])

dnl Packages (disabled by default)
AS_IF([test "$with_libc_all"          = yes], [with_libc_all=yes],          [with_libc_all=no])
AS_IF([test "$with_libc_atoi"         = yes], [with_libc_atoi=yes],         [with_libc_atoi=no])
AS_IF([test "$with_libc_isdigit"      = yes], [with_libc_isdigit=yes],      [with_libc_isdigit=no])
AS_IF([test "$with_libc_isspace"      = yes], [with_libc_isspace=yes],      [with_libc_isspace=no])
AS_IF([test "$with_libc_memset"       = yes], [with_libc_memset=yes],       [with_libc_memset=no])
AS_IF([test "$with_libc_strcpy"       = yes], [with_libc_strcpy=yes],       [with_libc_strcpy=no])
AS_IF([test "$with_libc_strlen"       = yes], [with_libc_strlen=yes],       [with_libc_strlen=no])
AS_IF([test "$with_libc_strnlen"      = yes], [with_libc_strnlen=yes],      [with_libc_strnlen=no])
AS_IF([test "$with_tester_multiboot2" = yes], [with_tester_multiboot2=yes], [with_tester_multiboot2=no])
AS_IF([test "$with_tester_stivale2"   = yes], [with_tester_stivale2=yes],   [with_tester_stivale2=no])



#############
# Test args #
#############

AS_IF([test "$enable_tests"        = yes -a "$host_cpu" != "$build_cpu" ], AC_MSG_ERROR([can not build cross-platform tests]))
AS_IF([test "$enable_tests"        = yes -a "$enable_freestanding" = yes], AC_MSG_ERROR([can not build freestanding tests]))
AS_IF([test "$enable_tests_python" = yes -a "$host_cpu" != "$build_cpu" ], AC_MSG_ERROR([can not build cross-platform tests]))
AS_IF([test "$enable_tests_python" = yes -a "$enable_freestanding" = yes], AC_MSG_ERROR([can not build freestanding tests]))

AS_IF([test "$with_printf"            = yes -a "$with_ntoa"       = no], AC_MSG_ERROR([package `printf' requires package `ntoa']))
AS_IF([test "$with_printf"            = yes -a "$with_printf_fmt" = no], AC_MSG_ERROR([package `printf' requires package `printf-fmt']))
AS_IF([test "$with_units"             = yes -a "$with_ntoa"       = no], AC_MSG_ERROR([package `units' requires package `ntoa']))
AS_IF([test "$with_tester_multiboot2" = yes -a "$with_console"    = no], AC_MSG_ERROR([package `tester-multiboot2' requires package `console']))
AS_IF([test "$with_tester_multiboot2" = yes -a "$with_multiboot2" = no], AC_MSG_ERROR([package `tester-multiboot2' requires package `multiboot2']))
AS_IF([test "$with_tester_multiboot2" = yes -a "$with_printf"     = no], AC_MSG_ERROR([package `tester-multiboot2' requires package `printf']))
AS_IF([test "$with_tester_stivale2"   = yes -a "$with_console"    = no], AC_MSG_ERROR([package `tester-stivale2' requires package `console']))
AS_IF([test "$with_tester_stivale2"   = yes -a "$with_printf"     = no], AC_MSG_ERROR([package `tester-stivale2' requires package `printf']))



#########################
# Automake conditionals #
#########################

dnl Architecture
AM_CONDITIONAL([ASM_I386],    [test "$host_cpu" = i386])
AM_CONDITIONAL([ASM_RISCV64], [test "$host_cpu" = riscv64])
AM_CONDITIONAL([ASM_X86_64],  [test "$host_cpu" = x86_64])

dnl Features (enabled by default)
AM_CONDITIONAL([ENABLE_BLOAT],           [test "$enable_bloat"           = yes])
AM_CONDITIONAL([ENABLE_FLOAT],           [test "$enable_float"           = yes])
AM_CONDITIONAL([ENABLE_WERROR],          [test "$enable_werror"          = yes])

dnl Features (disabled by default)
AM_CONDITIONAL([ENABLE_FREESTANDING],    [test "$enable_freestanding"    = yes])
AM_CONDITIONAL([ENABLE_TESTS],           [test "$enable_tests"           = yes])
AM_CONDITIONAL([ENABLE_TESTS_PYTHON],    [test "$enable_tests_python"    = yes])

dnl Packages (enabled by default)
AM_CONDITIONAL([WITH_CMDLINE],           [test "$with_cmdline"           = yes])
AM_CONDITIONAL([WITH_CONSOLE],           [test "$with_console"           = yes])
AM_CONDITIONAL([WITH_ELF],               [test "$with_elf"               = yes])
AM_CONDITIONAL([WITH_FRAMEBUFFER],       [test "$with_framebuffer"       = yes])
AM_CONDITIONAL([WITH_MBR],               [test "$with_mbr"               = yes])
AM_CONDITIONAL([WITH_MULTIBOOT2],        [test "$with_multiboot2"        = yes])
AM_CONDITIONAL([WITH_NTOA],              [test "$with_ntoa"              = yes])
AM_CONDITIONAL([WITH_PFA],               [test "$with_pfa"               = yes])
AM_CONDITIONAL([WITH_PRINTF],            [test "$with_printf"            = yes])
AM_CONDITIONAL([WITH_PRINTF_FMT],        [test "$with_printf_fmt"        = yes])
AM_CONDITIONAL([WITH_UNITS],             [test "$with_units"             = yes])

dnl Packages (disabled by default)
AM_CONDITIONAL([WITH_LIBC_ATOI],         [test "$with_libc_atoi"         = yes])
AM_CONDITIONAL([WITH_LIBC_ISDIGIT],      [test "$with_libc_isdigit"      = yes])
AM_CONDITIONAL([WITH_LIBC_ISSPACE],      [test "$with_libc_isspace"      = yes])
AM_CONDITIONAL([WITH_LIBC_MEMSET],       [test "$with_libc_memset"       = yes])
AM_CONDITIONAL([WITH_LIBC_STRCPY],       [test "$with_libc_strcpy"       = yes])
AM_CONDITIONAL([WITH_LIBC_STRLEN],       [test "$with_libc_strlen"       = yes])
AM_CONDITIONAL([WITH_LIBC_STRNLEN],      [test "$with_libc_strnlen"      = yes])
AM_CONDITIONAL([WITH_TESTER_MULTIBOOT2], [test "$with_tester_multiboot2" = yes])
AM_CONDITIONAL([WITH_TESTER_STIVALE2],   [test "$with_tester_stivale2"   = yes])



####################
# Autoconf defines #
####################

dnl Architecture
AS_IF([test "$host_cpu" = i386],              [AC_DEFINE([ASM_I386],               [1], [architecture is i386])])
AS_IF([test "$host_cpu" = riscv64],           [AC_DEFINE([ASM_RISCV64],            [1], [architecture is RISC-V 64-bit])])
AS_IF([test "$host_cpu" = x86_64],            [AC_DEFINE([ASM_X86_64],             [1], [architecture is x86_64])])

dnl Features (enabled by default)
AS_IF([test "$enable_bloat"           = yes], [AC_DEFINE([ENABLE_BLOAT],           [1], [enabled unnecessary heavy binary data])])
AS_IF([test "$enable_float"           = yes], [AC_DEFINE([ENABLE_FLOAT],           [1], [enabled floating-point arithmetic])])
AS_IF([test "$enable_werror"          = yes], [AC_DEFINE([ENABLE_WERROR],          [1], [enabled -Werror])])

dnl Features (disabled by default)
AS_IF([test "$enable_freestanding"    = yes], [AC_DEFINE([ENABLE_FREESTANDING],    [1], [build for freestanding environment])])
AS_IF([test "$enable_tests"           = yes], [AC_DEFINE([ENABLE_TESTS],           [1], [enabled usual tests and examples])])
AS_IF([test "$enable_tests_python"    = yes], [AC_DEFINE([ENABLE_TESTS_PYTHON],    [1], [enabled tests that require Python 3 with YAML and Jinja2])])

dnl Packages (enabled by default)
AS_IF([test "$with_cmdline"           = yes], [AC_DEFINE([WITH_CMDLINE],           [1], [with command line parser])])
AS_IF([test "$with_console"           = yes], [AC_DEFINE([WITH_CONSOLE],           [1], [with serial console])])
AS_IF([test "$with_elf"               = yes], [AC_DEFINE([WITH_ELF],               [1], [with ELF utils])])
AS_IF([test "$with_framebuffer"       = yes], [AC_DEFINE([WITH_FRAMEBUFFER],       [1], [with framebuffer])])
AS_IF([test "$with_mbr"               = yes], [AC_DEFINE([WITH_MBR],               [1], [with Master Boot Record])])
AS_IF([test "$with_multiboot2"        = yes], [AC_DEFINE([WITH_MULTIBOOT2],        [1], [with Multiboot 2 information parser])])
AS_IF([test "$with_ntoa"              = yes], [AC_DEFINE([WITH_NTOA],              [1], [with ntoa])])
AS_IF([test "$with_pfa"               = yes], [AC_DEFINE([WITH_PFA],               [1], [with Page Frame Allocator])])
AS_IF([test "$with_printf"            = yes], [AC_DEFINE([WITH_PRINTF],            [1], [with printf])])
AS_IF([test "$with_printf_fmt"        = yes], [AC_DEFINE([WITH_PRINTF_FMT],        [1], [with printf format parser])])
AS_IF([test "$with_units",            = yes], [AC_DEFINE([WITH_UNITS],             [1], [with measurement units utils])])

dnl Packages (disabled by default)
AS_IF([test "$with_libc_atoi"         = yes], [AC_DEFINE([WITH_LIBC_ATOI],         [1], [with atoi replacement])])
AS_IF([test "$with_libc_isdigit"      = yes], [AC_DEFINE([WITH_LIBC_ISDIGIT],      [1], [with isdigit replacement])])
AS_IF([test "$with_libc_isspace"      = yes], [AC_DEFINE([WITH_LIBC_ISSPACE],      [1], [with isspace replacement])])
AS_IF([test "$with_libc_memset"       = yes], [AC_DEFINE([WITH_LIBC_MEMSET],       [1], [with memset replacement])])
AS_IF([test "$with_libc_strcpy"       = yes], [AC_DEFINE([WITH_LIBC_STRCPY],       [1], [with strcpy replacement])])
AS_IF([test "$with_libc_strlen"       = yes], [AC_DEFINE([WITH_LIBC_STRLEN],       [1], [with strlen replacement])])
AS_IF([test "$with_libc_strnlen"      = yes], [AC_DEFINE([WITH_LIBC_STRNLEN],      [1], [with strnlen replacement])])
AS_IF([test "$with_tester_multiboot2" = yes], [AC_DEFINE([WITH_TESTER_MULTIBOOT2], [1], [with Multiboot 2 tester])])
AS_IF([test "$with_tester_stivale2"   = yes], [AC_DEFINE([WITH_TESTER_STIVALE2],   [1], [with Stivale 2 tester])])



##########################
# Autoconf substitutions #
##########################

dnl Architecture
AS_IF([test "$host_cpu" != i386],            [AC_SUBST([comment_line_asm_i386],          [//])])
AS_IF([test "$host_cpu" != riscv64],         [AC_SUBST([comment_line_asm_riscv64],       [//])])
AS_IF([test "$host_cpu" != x86_64],          [AC_SUBST([comment_line_asm_x86_64],        [//])])

dnl Packages (enabled by default)
AS_IF([test "$with_cmdline"           = no], [AC_SUBST([comment_line_cmdline],           [//])])
AS_IF([test "$with_console"           = no], [AC_SUBST([comment_line_console],           [//])])
AS_IF([test "$with_elf"               = no], [AC_SUBST([comment_line_elf],               [//])])
AS_IF([test "$with_framebuffer"       = no], [AC_SUBST([comment_line_framebuffer],       [//])])
AS_IF([test "$with_mbr"               = no], [AC_SUBST([comment_line_mbr],               [//])])
AS_IF([test "$with_multiboot2"        = no], [AC_SUBST([comment_line_multiboot2],        [//])])
AS_IF([test "$with_ntoa"              = no], [AC_SUBST([comment_line_ntoa],              [//])])
AS_IF([test "$with_pfa"               = no], [AC_SUBST([comment_line_pfa],               [//])])
AS_IF([test "$with_printf"            = no], [AC_SUBST([comment_line_printf],            [//])])
AS_IF([test "$with_printf_fmt"        = no], [AC_SUBST([comment_line_printf_fmt],        [//])])
AS_IF([test "$with_units"             = no], [AC_SUBST([comment_line_units],             [//])])

dnl Packages (disabled by default)
AS_IF([test "$with_libc_atoi"         = no], [AC_SUBST([comment_line_libc_atoi],         [//])])
AS_IF([test "$with_libc_isdigit"      = no], [AC_SUBST([comment_line_libc_isdigit],      [//])])
AS_IF([test "$with_libc_isspace"      = no], [AC_SUBST([comment_line_libc_isspace],      [//])])
AS_IF([test "$with_libc_memset"       = no], [AC_SUBST([comment_line_libc_memset],       [//])])
AS_IF([test "$with_libc_strcpy"       = no], [AC_SUBST([comment_line_libc_strcpy],       [//])])
AS_IF([test "$with_libc_strlen"       = no], [AC_SUBST([comment_line_libc_strlen],       [//])])
AS_IF([test "$with_libc_strnlen"      = no], [AC_SUBST([comment_line_libc_strnlen],      [//])])
AS_IF([test "$with_tester_multiboot2" = no], [AC_SUBST([comment_line_tester_multiboot2], [//])])
AS_IF([test "$with_tester_stivale2"   = no], [AC_SUBST([comment_line_tester_stivale2],   [//])])



AC_DEFUN([do_enable_freestanding],  [CFLAGS+=' -nostdlib -ffreestanding -fno-pic -fno-stack-protector '])
AC_DEFUN([do_disable_freestanding], [CFLAGS+=' -fpic '])
AS_IF([test "$enable_freestanding" = yes], do_enable_freestanding, do_disable_freestanding)



AM_INIT_AUTOMAKE([1.9 subdir-objects])

AC_CONFIG_FILES([
  Makefile
  include/Makefile
  include/kernaux.h
  include/kernaux/console.h
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
