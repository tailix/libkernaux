#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "assert.h"

#include <kernaux/generic/display.h>
#include <kernaux/generic/malloc.h>
#include <kernaux/macro.h>
#include <kernaux/memmap.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

static void free_node(KernAux_Malloc malloc, struct KernAux_Memmap_Node *node);
static KernAux_Memmap_Node node_by_addr(
    KernAux_Memmap_Node parent_node,
    uint64_t addr
);
static void print_nodes(
    KernAux_Memmap_Node node,
    KernAux_Display display,
    unsigned indentation
);

KernAux_Memmap_Builder
KernAux_Memmap_Builder_new(const KernAux_Malloc malloc)
{
    KERNAUX_NOTNULL(malloc);

    struct KernAux_Memmap_Builder *const builder =
        KernAux_Malloc_malloc(malloc, sizeof(*builder));
    if (!builder) {
        return NULL;
    }

    struct KernAux_Memmap *const memmap =
        KernAux_Malloc_malloc(malloc, sizeof(*memmap));
    if (!memmap) {
        KernAux_Malloc_free(malloc, builder);
        return NULL;
    }

    struct KernAux_Memmap_Node *const root_node =
        KernAux_Malloc_malloc(malloc, sizeof(*root_node));
    if (!root_node) {
        KernAux_Malloc_free(malloc, memmap);
        KernAux_Malloc_free(malloc, builder);
        return NULL;
    }

    *root_node = (struct KernAux_Memmap_Node){
        .parent_node = NULL,
        .level = 0,
        .mem_start = 0x0,
        .mem_end   = 0xffffffffffffffff, // 2**64 - 1
        .mem_size  = 0xffffffffffffffff, // 2**64 - 1
        .is_available = false,
        .tag = NULL,
        .next = NULL,
        .children = NULL,
    };
    *memmap = (struct KernAux_Memmap){
        .malloc = malloc,
        .root_node = root_node,
    };
    *builder = (struct KernAux_Memmap_Builder){
        .memmap = memmap,
    };

    return builder;
}

KernAux_Memmap_Node KernAux_Memmap_Builder_add(
    const KernAux_Memmap_Builder builder,
    const uint64_t mem_start,
    const uint64_t mem_size,
    const bool is_available,
    const char *tag
) {
    KERNAUX_NOTNULL(builder);
    KERNAUX_ASSERT(builder->memmap);
    KERNAUX_ASSERT(builder->memmap->root_node);
    KERNAUX_ASSERT(builder->memmap->malloc);

    if (mem_size == 0) goto fail;

    char *tag_copy = NULL;
    if (tag) {
        tag_copy =
            KernAux_Malloc_malloc(builder->memmap->malloc, strlen(tag) + 1);
        if (!tag_copy) goto fail;
        strcpy(tag_copy, tag);
    }

    struct KernAux_Memmap_Node *const new_node =
        KernAux_Malloc_malloc(builder->memmap->malloc, sizeof(*new_node));
    if (!new_node) goto fail_after_tag;

    new_node->mem_start = mem_start;
    new_node->mem_size = mem_size;
    new_node->mem_end = mem_start + mem_size - 1;
    new_node->is_available = is_available;
    new_node->tag = tag_copy;

    new_node->parent_node =
        KernAux_Memmap_node_by_addr(builder->memmap, new_node->mem_start);
    KERNAUX_ASSERT(new_node->parent_node);

    if (new_node->mem_start < new_node->parent_node->mem_start ||
        new_node->mem_end > new_node->parent_node->mem_end)
    {
        goto fail_after_new_node;
    }

    new_node->level = new_node->parent_node->level + 1;
    KERNAUX_ASSERT(new_node->level > 0);

    if (new_node->parent_node->children) {
        for (
            struct KernAux_Memmap_Node *curr_node =
                (struct KernAux_Memmap_Node*)new_node->parent_node->children;
            curr_node;
            curr_node = (struct KernAux_Memmap_Node*)curr_node->next
        ) {
            if (!curr_node->next ||
                curr_node->next->mem_start > new_node->mem_start)
            {
                if (new_node->next &&
                    new_node->mem_end >= new_node->next->mem_start)
                {
                    goto fail_after_new_node;
                }
                new_node->next = curr_node->next;
                curr_node->next = new_node;
                break;
            }
        }
    } else {
        new_node->next = NULL;
        ((struct KernAux_Memmap_Node*)new_node->parent_node)->children =
            new_node;
    }

    return new_node;

fail_after_new_node:
    KernAux_Malloc_free(builder->memmap->malloc, new_node);
fail_after_tag:
    if (tag_copy) KernAux_Malloc_free(builder->memmap->malloc, tag_copy);
fail:
    return NULL;
}

KernAux_Memmap
KernAux_Memmap_Builder_finish_and_free(const KernAux_Memmap_Builder builder)
{
    KERNAUX_NOTNULL(builder);
    KERNAUX_ASSERT(builder->memmap);
    KERNAUX_ASSERT(builder->memmap->root_node);
    KERNAUX_ASSERT(builder->memmap->malloc);

    KernAux_Memmap memmap = builder->memmap;
    builder->memmap = NULL;
    KernAux_Malloc_free(memmap->malloc, builder);
    return memmap;
}

void KernAux_Memmap_free(const KernAux_Memmap memmap)
{
    KERNAUX_NOTNULL(memmap);
    KERNAUX_ASSERT(memmap->root_node);
    KERNAUX_ASSERT(memmap->malloc);
    KERNAUX_ASSERT(memmap->root_node->next == NULL);

    free_node(memmap->malloc, (struct KernAux_Memmap_Node*)memmap->root_node);

    KernAux_Malloc malloc = memmap->malloc;

    ((struct KernAux_Memmap*)memmap)->root_node = NULL;
    ((struct KernAux_Memmap*)memmap)->malloc = NULL;

    KernAux_Malloc_free(malloc, (void*)memmap);
}

void KernAux_Memmap_print(
    const KernAux_Memmap memmap,
    const KernAux_Display display
) {
    KERNAUX_NOTNULL(memmap);
    KERNAUX_ASSERT(memmap->root_node);
    KERNAUX_ASSERT(memmap->malloc);
    KERNAUX_ASSERT(memmap->root_node->next == NULL);

    print_nodes(memmap->root_node, display, 0);
}

KernAux_Memmap_Node
KernAux_Memmap_node_by_addr(const KernAux_Memmap memmap, const uint64_t addr)
{
    return node_by_addr(memmap->root_node, addr);
}

void free_node(
    const KernAux_Malloc malloc,
    struct KernAux_Memmap_Node *const node
) {
    KERNAUX_NOTNULL(malloc);
    KERNAUX_NOTNULL(node);

    for (
        struct KernAux_Memmap_Node *child_node =
            (struct KernAux_Memmap_Node*)node->children;
        child_node;
        child_node = (struct KernAux_Memmap_Node*)child_node->next
    ) {
        free_node(malloc, child_node);
    }

    if (node->tag) KernAux_Malloc_free(malloc, (void*)node->tag);
    KernAux_Malloc_free(malloc, node);
}

KernAux_Memmap_Node node_by_addr(
    const KernAux_Memmap_Node parent_node,
    const uint64_t addr
) {
    KERNAUX_NOTNULL(parent_node);

    if (parent_node->mem_start > addr || parent_node->mem_end < addr) {
        return NULL;
    }

    for (
        KernAux_Memmap_Node child_node = parent_node->children;
        child_node;
        child_node = child_node->next
    ) {
        const KernAux_Memmap_Node node = node_by_addr(child_node, addr);
        if (node) return node;
    }

    return parent_node;
}

#define PRINT(s)   do { KernAux_Display_print  (display, s); } while (0)
#define PRINTLN(s) do { KernAux_Display_println(display, s); } while (0)

#define PRINTLNF(format, ...) \
    do { KernAux_Display_printlnf(display, format, __VA_ARGS__); } while (0)

#define INDENT do { \
    for (unsigned index = 0; index < indentation; ++index) PRINT("  "); \
} while (0)

void print_nodes(
    KernAux_Memmap_Node node,
    const KernAux_Display display,
    const unsigned indentation
) {
    for (; node; node = node->next) {
        INDENT;
        PRINTLN("{");

        KERNAUX_CAST_CONST(unsigned long long, mem_start, node->mem_start);
        KERNAUX_CAST_CONST(unsigned long long, mem_size,  node->mem_size);
        KERNAUX_CAST_CONST(unsigned long long, mem_end,   node->mem_end);
        const bool is_available = node->is_available;

        INDENT;
        PRINTLNF("  unsigned char level: %hhu", node->level);
        INDENT;
        PRINTLNF("  u64 mem_start: 0x%llx", mem_start);
        INDENT;
        PRINTLNF("  u64 mem_size:  %llu",   mem_size);
        INDENT;
        PRINTLNF("  u64 mem_end:   0x%llx", mem_end);
        INDENT;
        PRINTLNF("  bool is_available: %s", is_available ? "TRUE" : "FALSE");
        INDENT;
        if (node->tag) {
            PRINTLNF("  char* tag: \"%s\"", node->tag);
        } else {
            PRINTLN("  char* tag: NULL");
        }

        if (node->children) {
            INDENT;
            PRINTLN("  struct* children: [");
            print_nodes(node->children, display, indentation + 2);
            INDENT;
            PRINTLN("  ]");
        } else {
            INDENT;
            PRINTLN("  struct* children: []");
        }

        INDENT;
        PRINTLN("}");
    }
}
