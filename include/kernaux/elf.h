#ifndef KERNAUX_INCLUDED_ELF
#define KERNAUX_INCLUDED_ELF

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/macro.h>

#include <stdint.h>

#include <kernaux/macro/packing_start.run>

struct KernAux_ELF_Ident {
    uint8_t magic_0x7f;
    uint8_t magic_E;
    uint8_t magic_L;
    uint8_t magic_F;
    uint8_t class_;
    uint8_t data;
    uint8_t version;
    uint8_t unused[9];
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_ELF_Ident, 16);

// KernAux_ELF_Ident.class_
#define KERNAUX_ELF_CLASS_NONE 0 // Invalid class
#define KERNAUX_ELF_CLASS_32   1 // 32-bit objects
#define KERNAUX_ELF_CLASS_64   2 // 64-bit objects

// KernAux_ELF_Ident.data
#define KERNAUX_ELF_DATA_NONE 0 // Invalid data encoding
#define KERNAUX_ELF_DATA_2LSB 1 // 0x01020304 == [0x04, 0x03, 0x02, 0x01]
#define KERNAUX_ELF_DATA_2MSB 2 // 0x01020304 == [0x01, 0x02, 0x03, 0x04]

struct KernAux_ELF_Header {
    struct KernAux_ELF_Ident ident;
    uint16_t type;
    uint16_t machine;
    uint32_t version;
    uint32_t entry;
    uint32_t phoff;
    uint32_t shoff;
    uint32_t flags;
    uint16_t ehsize;
    uint16_t phentsize;
    uint16_t phnum;
    uint16_t shentsize;
    uint16_t shnum;
    uint16_t shstrndx;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_ELF_Header, 52);

// KernAux_ELF_Header.type
#define KERNAUX_ELF_TYPE_NONE   0      // No file type
#define KERNAUX_ELF_TYPE_REL    1      // Relocatable file
#define KERNAUX_ELF_TYPE_EXEC   2      // Executable file
#define KERNAUX_ELF_TYPE_DYN    3      // Shared object file
#define KERNAUX_ELF_TYPE_CORE   4      // Core file
#define KERNAUX_ELF_TYPE_LOPROC 0xff00 // Processor-specific
#define KERNAUX_ELF_TYPE_HIPROC 0xffff // Processor-specific

// KernAux_ELF_Header.machine
#define KERNAUX_ELF_MACHINE_NONE  0 // No machine
#define KERNAUX_ELF_MACHINE_M32   1 // AT&T WE 32100
#define KERNAUX_ELF_MACHINE_SPARC 2 // SPARC
#define KERNAUX_ELF_MACHINE_386   3 // Intel 80386
#define KERNAUX_ELF_MACHINE_68K   4 // Motorola 68000
#define KERNAUX_ELF_MACHINE_88K   5 // Motorola 88000
#define KERNAUX_ELF_MACHINE_860   7 // Intel 80860
#define KERNAUX_ELF_MACHINE_MIPS  8 // MIPS RS3000

// KernAux_ELF_Header.version
#define KERNAUX_ELF_VERSION_NONE    0 // Invalid version
#define KERNAUX_ELF_VERSION_CURRENT 1 // Current version

struct KernAux_ELF_Section {
    uint32_t name;
    uint32_t type;
    uint32_t flags;
    uint32_t addr;
    uint32_t offset;
    uint32_t size;
    uint32_t link;
    uint32_t info;
    uint32_t addralign;
    uint32_t entsize;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_ELF_Section, 40);

#define KERNAUX_ELF_SECT_TYPE_NULL     0
#define KERNAUX_ELF_SECT_TYPE_PROGBITS 1
#define KERNAUX_ELF_SECT_TYPE_SYMTAB   2
#define KERNAUX_ELF_SECT_TYPE_STRTAB   3
#define KERNAUX_ELF_SECT_TYPE_RELA     4
#define KERNAUX_ELF_SECT_TYPE_HASH     5
#define KERNAUX_ELF_SECT_TYPE_DYNAMIC  6
#define KERNAUX_ELF_SECT_TYPE_NOTE     7
#define KERNAUX_ELF_SECT_TYPE_NOBITS   8
#define KERNAUX_ELF_SECT_TYPE_REL      9
#define KERNAUX_ELF_SECT_TYPE_SHLIB    10
#define KERNAUX_ELF_SECT_TYPE_DYNSYM   11
#define KERNAUX_ELF_SECT_TYPE_LOPROC   0x70000000
#define KERNAUX_ELF_SECT_TYPE_HIPROC   0x7fffffff
#define KERNAUX_ELF_SECT_TYPE_LOUSER   0x80000000
#define KERNAUX_ELF_SECT_TYPE_HIUSER   0xffffffff

#define KERNAUX_ELF_SECT_FLAGS_WRITE     0x1
#define KERNAUX_ELF_SECT_FLAGS_ALLOC     0x2
#define KERNAUX_ELF_SECT_FLAGS_EXECINSTR 0x4
#define KERNAUX_ELF_SECT_FLAGS_MASKPROC  0xf0000000

const char *KernAux_ELF_Section_Type_to_str(uint32_t type);

struct KernAux_ELF_Symbol {
    uint32_t name;
    uint32_t value;
    uint32_t size;
    uint8_t info;
    uint8_t other;
    uint16_t shndx;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_ELF_Symbol, 16);

#define KERNAUX_ELF_SYM_INFO(bind, type) (((bind) << 4) + ((type) & 0xf))
#define KERNAUX_ELF_SYM_BIND(info) ((info) >> 4)
#define KERNAUX_ELF_SYM_TYPE(info) ((into) & 0xf)

#define KERNAUX_ELF_SYM_BIND_LOCAL  0
#define KERNAUX_ELF_SYM_BIND_GLOBAL 1
#define KERNAUX_ELF_SYM_BIND_WEAK   2
#define KERNAUX_ELF_SYM_BIND_LOPROC 13
#define KERNAUX_ELF_SYM_BIND_HIPROC 15

#define KERNAUX_ELF_SYM_TYPE_NOTYPE  0
#define KERNAUX_ELF_SYM_TYPE_OBJECT  1
#define KERNAUX_ELF_SYM_TYPE_FUNC    2
#define KERNAUX_ELF_SYM_TYPE_SECTION 3
#define KERNAUX_ELF_SYM_TYPE_FILE    4
#define KERNAUX_ELF_SYM_TYPE_LOPROC  13
#define KERNAUX_ELF_SYM_TYPE_HIPROC  15

struct KernAux_ELF_Program {
    uint32_t type;
    uint32_t offset;
    uint32_t vaddr;
    uint32_t paddr;
    uint32_t filesz;
    uint32_t memsz;
    uint32_t flags;
    uint32_t align;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_ELF_Program, 32);

#define KERNAUX_ELF_PROG_TYPE_NULL    0
#define KERNAUX_ELF_PROG_TYPE_LOAD    1
#define KERNAUX_ELF_PROG_TYPE_DYNAMIC 2
#define KERNAUX_ELF_PROG_TYPE_INTERP  3
#define KERNAUX_ELF_PROG_TYPE_NOTE    4
#define KERNAUX_ELF_PROG_TYPE_SHLIB   5
#define KERNAUX_ELF_PROG_TYPE_PHDR    6
#define KERNAUX_ELF_PROG_TYPE_LOPROC  0x70000000
#define KERNAUX_ELF_PROG_TYPE_HIPROC  0x7fffffff

#include <kernaux/macro/packing_end.run>

#ifdef __cplusplus
}
#endif

#endif
