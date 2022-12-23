############################
# Specify program versions #
############################

AC_PREREQ([2.70])
LT_PREREQ([2.4.6])



##################################
# Initialize Autoconf & Automake #
##################################

AC_INIT([libkernaux],
  m4_normalize(m4_include([VERSION])),
  [https://github.com/tailix/libkernaux/issues],
  [libkernaux],
  [https://github.com/tailix/libkernaux])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST

AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([src/runtime.c])
AC_CONFIG_FILES([
  Makefile
  libkernaux.pc
  examples/Makefile
  fixtures/Makefile
  fixtures/multiboot2_bin_examples_gen.c
  include/Makefile
  libc/Makefile
  libc/include/Makefile
  include/kernaux/version.h
  tests/Makefile
  tests/test_multiboot2_header_print.c
  tests/test_multiboot2_info_print.c
])

AM_INIT_AUTOMAKE([1.16 subdir-objects])

AC_SUBST([PACKAGE_DESCR], ['Auxiliary library for kernel development'])
AC_SUBST([PACKAGE_VERSION_SO], m4_normalize(m4_include([VERSION_SO])))



###############
# Define args #
###############

dnl Features (enabled by default)
AC_ARG_ENABLE([assert],          AS_HELP_STRING([--disable-assert],         [disable assertions]))
AC_ARG_ENABLE([float],           AS_HELP_STRING([--disable-float],          [disable floating-point arithmetic]))
AC_ARG_ENABLE([werror],          AS_HELP_STRING([--disable-werror],         [disable -Werror]))
 
dnl Features (disabled by default)
AC_ARG_ENABLE([fixtures],        AS_HELP_STRING([--enable-fixtures],        [enable fixtures for tests and bindings]))
AC_ARG_ENABLE([freestanding],    AS_HELP_STRING([--enable-freestanding],    [build for freestanding environment]))
AC_ARG_ENABLE([checks],          AS_HELP_STRING([--enable-checks],          [enable usual tests and examples]))
AC_ARG_ENABLE([checks-all],      AS_HELP_STRING([--enable-checks-all],      [enable all checks]))
AC_ARG_ENABLE([checks-cppcheck], AS_HELP_STRING([--enable-checks-cppcheck], [enable cppcheck]))
AC_ARG_ENABLE([checks-pthreads], AS_HELP_STRING([--enable-checks-pthreads], [enable tests that require pthreads]))
AC_ARG_ENABLE([checks-python],   AS_HELP_STRING([--enable-checks-python],   [enable tests that require Python 3 with YAML and Jinja2]))
AC_ARG_ENABLE([split-libc],      AS_HELP_STRING([--enable-split-libc],      [split off libc]))

dnl Features (with parameter)
AC_ARG_ENABLE([pkg-config],      AS_HELP_STRING([--enable-pkg-config@<:@=PATH@:>@], [install pkg-config files @<:@PATH='${libdir}/pkgconfig'@:>@]))

dnl Packages (enabled by default)
AC_ARG_WITH(  [all],             AS_HELP_STRING([--without-all],            [without all default packages]))
AC_ARG_WITH(  [arch-all],        AS_HELP_STRING([--without-arch-all],       [without all architectures]))
AC_ARG_WITH(  [arch-i386],       AS_HELP_STRING([--without-arch-i386],      [without architecture i386]))
AC_ARG_WITH(  [arch-riscv64],    AS_HELP_STRING([--without-arch-riscv64],   [without architecture riscv64]))
AC_ARG_WITH(  [arch-x86-64],     AS_HELP_STRING([--without-arch-x86-64],    [without architecture x86-64]))
AC_ARG_WITH(  [asm],             AS_HELP_STRING([--without-asm],            [without kernel assembler helpers]))
AC_ARG_WITH(  [cmdline],         AS_HELP_STRING([--without-cmdline],        [without command line parser]))
AC_ARG_WITH(  [elf],             AS_HELP_STRING([--without-elf],            [without ELF utils]))
AC_ARG_WITH(  [free-list],       AS_HELP_STRING([--without-free-list],      [without free list memory allocator]))
AC_ARG_WITH(  [mbr],             AS_HELP_STRING([--without-mbr],            [without MBR utils]))
AC_ARG_WITH(  [memmap],          AS_HELP_STRING([--without-memmap],         [without memory map]))
AC_ARG_WITH(  [multiboot2],      AS_HELP_STRING([--without-multiboot2],     [without Multiboot 2 utils]))
AC_ARG_WITH(  [ntoa],            AS_HELP_STRING([--without-ntoa],           [without itoa/ftoa]))
AC_ARG_WITH(  [pfa],             AS_HELP_STRING([--without-pfa],            [without Page Frame Allocator]))
AC_ARG_WITH(  [printf],          AS_HELP_STRING([--without-printf],         [without printf]))
AC_ARG_WITH(  [printf-fmt],      AS_HELP_STRING([--without-printf-fmt],     [without printf format parser]))
AC_ARG_WITH(  [units],           AS_HELP_STRING([--without-units],          [without measurement units utils]))

dnl Packages (disabled by default)
AC_ARG_WITH(  [libc],            AS_HELP_STRING([--with-libc],              [with libc replacement]))



################
# Default args #
################

AC_DEFUN([do_enable_checks_all],
[
if test -z "$enable_checks";          then enable_checks=yes;          fi
if test -z "$enable_checks_cppcheck"; then enable_checks_cppcheck=yes; fi
if test -z "$enable_checks_pthreads"; then enable_checks_pthreads=yes; fi
if test -z "$enable_checks_python";   then enable_checks_python=yes;   fi
])
AS_IF([test "$enable_checks_all" = yes], do_enable_checks_all)

AC_DEFUN([do_without_arch_all],
[
if test -z "$with_arch_i386";    then with_arch_i386=no;    fi
if test -z "$with_arch_riscv64"; then with_arch_riscv64=no; fi
if test -z "$with_arch_x86_64";  then with_arch_x86_64=no;  fi
])
AS_IF([test "$with_arch_all" = no], do_without_arch_all)

AC_DEFUN([do_without_all],
[
if test -z "$with_arch_i386";    then with_arch_i386=no;    fi
if test -z "$with_arch_riscv64"; then with_arch_riscv64=no; fi
if test -z "$with_arch_x86_64";  then with_arch_x86_64=no;  fi
if test -z "$with_asm";          then with_asm=no;          fi
if test -z "$with_cmdline";      then with_cmdline=no;      fi
if test -z "$with_elf";          then with_elf=no;          fi
if test -z "$with_free_list";    then with_free_list=no;    fi
if test -z "$with_mbr";          then with_mbr=no;          fi
if test -z "$with_memmap";       then with_memmap=no;       fi
if test -z "$with_multiboot2";   then with_multiboot2=no;   fi
if test -z "$with_ntoa";         then with_ntoa=no;         fi
if test -z "$with_pfa";          then with_pfa=no;          fi
if test -z "$with_printf";       then with_printf=no;       fi
if test -z "$with_printf_fmt";   then with_printf_fmt=no;   fi
if test -z "$with_units";        then with_units=no;        fi
])
AS_IF([test "$with_all" = no], do_without_all)



##################
# Normalize args #
##################

dnl Features (enabled by default)
AS_IF([test "$enable_assert"          = no ], [enable_assert=no],           [enable_assert=yes])
AS_IF([test "$enable_float"           = no ], [enable_float=no],            [enable_float=yes])
AS_IF([test "$enable_werror"          = no ], [enable_werror=no],           [enable_werror=yes])

dnl Features (disabled by default)
AS_IF([test "$enable_fixtures"        = yes], [enable_fixtures=yes],        [enable_fixtures=no])
AS_IF([test "$enable_freestanding"    = yes], [enable_freestanding=yes],    [enable_freestanding=no])
AS_IF([test "$enable_checks"          = yes], [enable_checks=yes],          [enable_checks=no])
AS_IF([test "$enable_checks_all"      = yes], [enable_checks_all=yes],      [enable_checks_all=no])
AS_IF([test "$enable_checks_cppcheck" = yes], [enable_checks_cppcheck=yes], [enable_checks_cppcheck=no])
AS_IF([test "$enable_checks_pthreads" = yes], [enable_checks_pthreads=yes], [enable_checks_pthreads=no])
AS_IF([test "$enable_checks_python"   = yes], [enable_checks_python=yes],   [enable_checks_python=no])
AS_IF([test "$enable_split_libc"      = yes], [enable_split_libc=yes],      [enable_split_libc=no])

dnl Features (with parameter)
AS_IF([test "$enable_pkg_config"      = yes], [enable_pkg_config='${libdir}/pkgconfig'])
AS_IF([test "$enable_pkg_config"      = no ], [enable_pkg_config=''])

dnl Packages (enabled by default)
AS_IF([test "$with_all"               = no ], [with_all=no],                [with_all=yes])
AS_IF([test "$with_arch_all"          = no ], [with_arch_all=no],           [with_arch_all=yes])
AS_IF([test "$with_arch_i386"         = no ], [with_arch_i386=no],          [with_arch_i386=yes])
AS_IF([test "$with_arch_riscv64"      = no ], [with_arch_riscv64=no],       [with_arch_riscv64=yes])
AS_IF([test "$with_arch_x86_64"       = no ], [with_arch_x86_64=no],        [with_arch_x86_64=yes])
AS_IF([test "$with_asm"               = no ], [with_asm=no],                [with_asm=yes])
AS_IF([test "$with_cmdline"           = no ], [with_cmdline=no],            [with_cmdline=yes])
AS_IF([test "$with_elf"               = no ], [with_elf=no],                [with_elf=yes])
AS_IF([test "$with_free_list"         = no ], [with_free_list=no],          [with_free_list=yes])
AS_IF([test "$with_mbr"               = no ], [with_mbr=no],                [with_mbr=yes])
AS_IF([test "$with_memmap"            = no ], [with_memmap=no],             [with_memmap=yes])
AS_IF([test "$with_multiboot2"        = no ], [with_multiboot2=no],         [with_multiboot2=yes])
AS_IF([test "$with_ntoa"              = no ], [with_ntoa=no],               [with_ntoa=yes])
AS_IF([test "$with_pfa"               = no ], [with_pfa=no],                [with_pfa=yes])
AS_IF([test "$with_printf"            = no ], [with_printf=no],             [with_printf=yes])
AS_IF([test "$with_printf_fmt"        = no ], [with_printf_fmt=no],         [with_printf_fmt=yes])
AS_IF([test "$with_units"             = no ], [with_units=no],              [with_units=yes])

dnl Packages (disabled by default)
AS_IF([test "$with_libc"              = yes], [with_libc=yes],              [with_libc=no])



#############
# Test args #
#############

AS_IF([test "$enable_checks"   = yes -a "$enable_freestanding" = yes], AC_MSG_ERROR([can not build freestanding tests]))
AS_IF([test "$enable_fixtures" = yes -a "$enable_freestanding" = yes], AC_MSG_ERROR([can not build freestanding fixtures]))
AS_IF([test "$enable_checks"   = yes -a "$with_libc"           = yes], AC_MSG_ERROR([can not use package `libc' with tests]))
AS_IF([test "$enable_fixtures" = yes -a "$with_libc"           = yes], AC_MSG_ERROR([can not use package `libc' with fixtures]))

AS_IF([test "$with_printf" = yes -a "$with_ntoa"       = no], AC_MSG_ERROR([package `printf' requires package `ntoa']))
AS_IF([test "$with_printf" = yes -a "$with_printf_fmt" = no], AC_MSG_ERROR([package `printf' requires package `printf-fmt']))
AS_IF([test "$with_units"  = yes -a "$with_ntoa"       = no], AC_MSG_ERROR([package `units' requires package `ntoa']))



#########################
# Automake conditionals #
#########################

dnl Architecture
AM_CONDITIONAL([ASM_I386],               [test "$host_cpu" = i386])
AM_CONDITIONAL([ASM_RISCV64],            [test "$host_cpu" = riscv64])
AM_CONDITIONAL([ASM_X86_64],             [test "$host_cpu" = x86_64])

dnl Architecture (additional)
AM_CONDITIONAL([ASM_X86],                [test "$host_cpu" = i386 -o "$host_cpu" = x86_64])

dnl Features (enabled by default)
AM_CONDITIONAL([ENABLE_ASSERT],          [test "$enable_assert"          = yes])
AM_CONDITIONAL([ENABLE_FLOAT],           [test "$enable_float"           = yes])
AM_CONDITIONAL([ENABLE_WERROR],          [test "$enable_werror"          = yes])

dnl Features (disabled by default)
AM_CONDITIONAL([ENABLE_FIXTURES],        [test "$enable_fixtures"        = yes])
AM_CONDITIONAL([ENABLE_FREESTANDING],    [test "$enable_freestanding"    = yes])
AM_CONDITIONAL([ENABLE_CHECKS],          [test "$enable_checks"          = yes])
AM_CONDITIONAL([ENABLE_CHECKS_CPPCHECK], [test "$enable_checks_cppcheck" = yes])
AM_CONDITIONAL([ENABLE_CHECKS_PTHREADS], [test "$enable_checks_pthreads" = yes])
AM_CONDITIONAL([ENABLE_CHECKS_PYTHON],   [test "$enable_checks_python"   = yes])
AM_CONDITIONAL([ENABLE_SPLIT_LIBC],      [test "$enable_split_libc"      = yes])

dnl Features (with parameter)
AM_CONDITIONAL([ENABLE_PKG_CONFIG],      [test ! -z "$enable_pkg_config"])

dnl Packages (enabled by default)
AM_CONDITIONAL([WITH_ARCH_I386],         [test "$with_arch_i386"         = yes])
AM_CONDITIONAL([WITH_ARCH_RISCV64],      [test "$with_arch_riscv64"      = yes])
AM_CONDITIONAL([WITH_ARCH_X86_64],       [test "$with_arch_x86_64"       = yes])
AM_CONDITIONAL([WITH_ASM],               [test "$with_asm"               = yes])
AM_CONDITIONAL([WITH_CMDLINE],           [test "$with_cmdline"           = yes])
AM_CONDITIONAL([WITH_ELF],               [test "$with_elf"               = yes])
AM_CONDITIONAL([WITH_FREE_LIST],         [test "$with_free_list"         = yes])
AM_CONDITIONAL([WITH_MBR],               [test "$with_mbr"               = yes])
AM_CONDITIONAL([WITH_MEMMAP],            [test "$with_memmap"            = yes])
AM_CONDITIONAL([WITH_MULTIBOOT2],        [test "$with_multiboot2"        = yes])
AM_CONDITIONAL([WITH_NTOA],              [test "$with_ntoa"              = yes])
AM_CONDITIONAL([WITH_PFA],               [test "$with_pfa"               = yes])
AM_CONDITIONAL([WITH_PRINTF],            [test "$with_printf"            = yes])
AM_CONDITIONAL([WITH_PRINTF_FMT],        [test "$with_printf_fmt"        = yes])
AM_CONDITIONAL([WITH_UNITS],             [test "$with_units"             = yes])

dnl Packages (disabled by default)
AM_CONDITIONAL([WITH_LIBC],              [test "$with_libc"              = yes])

dnl Packages (virtual)
AM_CONDITIONAL([WITH_ARCH_X86],          [test "$with_arch_i386" = yes -o "$with_arch_x86_64" = yes])



####################
# Autoconf defines #
####################

dnl Architecture
AS_IF([test "$host_cpu" = i386],              [AC_DEFINE([ASM_I386],               [1], [architecture is i386])])
AS_IF([test "$host_cpu" = riscv64],           [AC_DEFINE([ASM_RISCV64],            [1], [architecture is RISC-V 64-bit])])
AS_IF([test "$host_cpu" = x86_64],            [AC_DEFINE([ASM_X86_64],             [1], [architecture is x86_64])])

dnl Architecture (additional)
AS_IF([test "$host_cpu" = i386],              [AC_DEFINE([ASM_X86],                [1], [architecture is x86])])
AS_IF([test "$host_cpu" = x86_64],            [AC_DEFINE([ASM_X86],                [1], [architecture is x86])])

dnl Features (enabled by default)
AS_IF([test "$enable_assert"          = yes], [AC_DEFINE([ENABLE_ASSERT],          [1], [enabled assertions])])
AS_IF([test "$enable_float"           = yes], [AC_DEFINE([ENABLE_FLOAT],           [1], [enabled floating-point arithmetic])])
AS_IF([test "$enable_werror"          = yes], [AC_DEFINE([ENABLE_WERROR],          [1], [enabled -Werror])])

dnl Features (disabled by default)
AS_IF([test "$enable_fixtures"        = yes], [AC_DEFINE([ENABLE_FIXTURES],        [1], [enabled fixtures for tests and bindings])])
AS_IF([test "$enable_freestanding"    = yes], [AC_DEFINE([ENABLE_FREESTANDING],    [1], [build for freestanding environment])])
AS_IF([test "$enable_checks"          = yes], [AC_DEFINE([ENABLE_CHECKS],          [1], [enabled usual tests and examples])])
AS_IF([test "$enable_checks_cppcheck" = yes], [AC_DEFINE([ENABLE_CHECKS_CPPCHECK], [1], [enabled cppcheck])])
AS_IF([test "$enable_checks_pthreads" = yes], [AC_DEFINE([ENABLE_CHECKS_PTHREADS], [1], [enabled tests that require pthreads])])
AS_IF([test "$enable_checks_python"   = yes], [AC_DEFINE([ENABLE_CHECKS_PYTHON],   [1], [enabled tests that require Python 3 with YAML and Jinja2])])
AS_IF([test "$enable_split_libc"      = yes], [AC_DEFINE([ENABLE_SPLIT_LIBC],      [1], [split off libc])])

dnl Packages (enabled by default)
AS_IF([test "$with_arch_i386"         = yes], [AC_DEFINE([WITH_ARCH_I386],         [1], [with architecture i386])])
AS_IF([test "$with_arch_riscv64"      = yes], [AC_DEFINE([WITH_ARCH_RISCV64],      [1], [with architecture riscv64])])
AS_IF([test "$with_arch_x86_64"       = yes], [AC_DEFINE([WITH_ARCH_X86_64],       [1], [with architecture x86_64])])
AS_IF([test "$with_asm"               = yes], [AC_DEFINE([WITH_ASM],               [1], [with kernel assembler helpers])])
AS_IF([test "$with_cmdline"           = yes], [AC_DEFINE([WITH_CMDLINE],           [1], [with command line parser])])
AS_IF([test "$with_elf"               = yes], [AC_DEFINE([WITH_ELF],               [1], [with ELF utils])])
AS_IF([test "$with_free_list"         = yes], [AC_DEFINE([WITH_FREE_LIST],         [1], [with free list memory allocator])])
AS_IF([test "$with_mbr"               = yes], [AC_DEFINE([WITH_MBR],               [1], [with MBR utils])])
AS_IF([test "$with_memmap"            = yes], [AC_DEFINE([WITH_MEMMAP],            [1], [with memory map])])
AS_IF([test "$with_multiboot2"        = yes], [AC_DEFINE([WITH_MULTIBOOT2],        [1], [with Multiboot 2 utils])])
AS_IF([test "$with_ntoa"              = yes], [AC_DEFINE([WITH_NTOA],              [1], [with ntoa])])
AS_IF([test "$with_pfa"               = yes], [AC_DEFINE([WITH_PFA],               [1], [with Page Frame Allocator])])
AS_IF([test "$with_printf"            = yes], [AC_DEFINE([WITH_PRINTF],            [1], [with printf])])
AS_IF([test "$with_printf_fmt"        = yes], [AC_DEFINE([WITH_PRINTF_FMT],        [1], [with printf format parser])])
AS_IF([test "$with_units",            = yes], [AC_DEFINE([WITH_UNITS],             [1], [with measurement units utils])])

dnl Packages (disabled by default)
AS_IF([test "$with_libc"              = yes], [AC_DEFINE([WITH_LIBC],              [1], [with libc replacement])])

dnl Packages (virtual)
AS_IF([test "$with_arch_i386"         = yes], [AC_DEFINE([WITH_ARCH_X86],          [1], [with architecture x86])])
AS_IF([test "$with_arch_x86_64"       = yes], [AC_DEFINE([WITH_ARCH_X86],          [1], [with architecture x86])])



##########################
# Autoconf substitutions #
##########################

dnl Features (with parameter)
AC_SUBST([pkgconfdir], [$enable_pkg_config])

dnl Packages (enabled by default)
AS_IF([test "$with_arch_i386"    = no], [AC_SUBST([comment_line_arch_i386],    [//])])
AS_IF([test "$with_arch_riscv64" = no], [AC_SUBST([comment_line_arch_riscv64], [//])])
AS_IF([test "$with_arch_x86_64"  = no], [AC_SUBST([comment_line_arch_x86_64],  [//])])
AS_IF([test "$with_cmdline"      = no], [AC_SUBST([comment_line_cmdline],      [//])])
AS_IF([test "$with_elf"          = no], [AC_SUBST([comment_line_elf],          [//])])
AS_IF([test "$with_free_list"    = no], [AC_SUBST([comment_line_free_list],    [//])])
AS_IF([test "$with_mbr"          = no], [AC_SUBST([comment_line_mbr],          [//])])
AS_IF([test "$with_memmap"       = no], [AC_SUBST([comment_line_memmap],       [//])])
AS_IF([test "$with_multiboot2"   = no], [AC_SUBST([comment_line_multiboot2],   [//])])
AS_IF([test "$with_ntoa"         = no], [AC_SUBST([comment_line_ntoa],         [//])])
AS_IF([test "$with_pfa"          = no], [AC_SUBST([comment_line_pfa],          [//])])
AS_IF([test "$with_printf"       = no], [AC_SUBST([comment_line_printf],       [//])])
AS_IF([test "$with_printf_fmt"   = no], [AC_SUBST([comment_line_printf_fmt],   [//])])
AS_IF([test "$with_units"        = no], [AC_SUBST([comment_line_units],        [//])])



###################
# Set build flags #
###################

AS_IF([test "$enable_freestanding" = yes],
  [CFLAGS="$CFLAGS -nostdlib -ffreestanding -fno-pic -fno-stack-protector "],
  [CFLAGS="$CFLAGS -fpic "])



##############
# Run checks #
##############

AC_LANG([C])
AM_PROG_AS

AC_C_INLINE

AC_HEADER_STDBOOL
AS_IF([test "$enable_checks" = yes -a "$ac_cv_header_stdbool_h" != yes],
  [AC_MSG_ERROR([the header is required])])

AC_CHECK_HEADERS([limits.h stdarg.h stddef.h stdint.h],,
  [AC_MSG_ERROR([the headers are required])])

AS_IF([test "$enable_checks" = yes],
  [AC_CHECK_HEADERS([assert.h setjmp.h stdio.h stdlib.h string.h],,
    [AC_MSG_ERROR([the headers are required])])])

AS_IF([test "$enable_checks" = yes -a "$enable_checks_pthreads" = yes],
  [AC_CHECK_HEADERS([pthread.h],,
    [AC_MSG_ERROR([the header is required])])])

AM_PATH_PYTHON([3.8],, [:])
AS_IF([test "$enable_checks_python" = yes -a "$enable_checks" = yes -a "$PYTHON" = ':'],
  [AC_MSG_ERROR([Python is required])])

AC_PATH_PROGS([CPPCHECK], [cppcheck], [:])
AS_IF([test "$enable_checks_cppcheck" = yes -a "$CPPCHECK" = ':'],
  [AC_MSG_ERROR([cppcheck is required])])

AC_CACHE_CHECK([for Python YAML],
  [libkernaux_cv_shell_pythonyaml_exists],
  [libkernaux_cv_shell_pythonyaml_exists=no
   PYTHON_YAML=no
   if test "$PYTHON" != ':'; then
     if test "$($PYTHON -c 'import yaml; print(yaml.__package__)')" = 'yaml'; then
       libkernaux_cv_shell_pythonyaml_exists=yes
       PYTHON_YAML=yes
     fi
   fi])
AS_IF([test "$enable_checks_python" = yes -a "$enable_checks" = yes -a "$PYTHON_YAML" != 'yes'],
  [AC_MSG_ERROR([Python YAML is required])])

AC_CACHE_CHECK([for Python Jinja 2],
  [libkernaux_cv_shell_pythonjinja2_exists],
  [libkernaux_cv_shell_pythonjinja2_exists=no
   PYTHON_JINJA2=no
   if test "$PYTHON" != ':'; then
     if test "$($PYTHON -c 'import jinja2; print(jinja2.__package__)')" = 'jinja2'; then
       libkernaux_cv_shell_pythonjinja2_exists=yes
       PYTHON_JINJA2=yes
     fi
   fi])
AS_IF([test "$enable_checks_python" = yes -a "$enable_checks" = yes -a "$PYTHON_JINJA2" != 'yes'],
  [AC_MSG_ERROR([Python Jinja 2 is required])])



######################
# Initialize Libtool #
######################

LT_INIT



##########
# Finish #
##########

AC_OUTPUT
