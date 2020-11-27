libkernaux
==========

Auxiliary library for kernel development.



Tips
----

Configure with cross-compiler in `$PATH` to make without it in `$PATH`:

```
./configure \
  --host=i686-elf \
  AR="$(which i686-elf-ar)" \
  CC="$(which i686-elf-gcc)" \
  RANLIB="$(which i686-elf-ranlib)" \
  CFLAGS='-ffreestanding -nostdinc -nostdlib -fno-builtin -fno-stack-protector -Wall -Wextra'
```

Check if compilation targets i386: `objdump -d src/arch/i386.o`.

It should output something like this:

```
src/arch/i386.o:     file format elf32-i386


Disassembly of section .text:

00000000 <kernaux_arch_i386_read_cr0>:
   0:   0f 20 c0              mov    %cr0,%eax
   3:   c3                    ret

00000004 <kernaux_arch_i386_read_cr4>:
   4:   0f 20 e0              mov    %cr4,%eax
   7:   c3                    ret

00000008 <kernaux_arch_i386_write_cr0>:
   8:   8b 44 24 04           mov    0x4(%esp),%eax
   c:   0f 22 c0              mov    %eax,%cr0
   f:   c3                    ret

00000010 <kernaux_arch_i386_write_cr3>:
  10:   8b 44 24 04           mov    0x4(%esp),%eax
  14:   0f 22 d8              mov    %eax,%cr3
  17:   c3                    ret

00000018 <kernaux_arch_i386_write_cr4>:
  18:   8b 44 24 04           mov    0x4(%esp),%eax
  1c:   0f 22 e0              mov    %eax,%cr4
  1f:   c3                    ret
```
