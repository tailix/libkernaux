#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/stivale2.h>

int KernAux_get_stivale2_tag_count(KernAux_stivale2_struct* stivale2_params)
{
    int count = 0;

    auto tag = reinterpret_cast<KernAux_stivale2_tag *>(stivale2_params->tags);

    while (tag != NULL)
    {
        count += 1;
        tag = reinterpret_cast<KernAux_stivale2_tag *>(tag->next);
    }

    return count;
}

bool KernAux_get_stivale2_framebuffer(KernAux_stivale2_struct* stivale2_params, KernAux_stivale2_struct_tag_framebuffer* framebuffer)
{
    auto tag = reinterpret_cast<KernAux_stivale2_tag *>(stivale2_params->tags);

    while (tag != NULL)
    {
        if(tag->identifier == KernAux_STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID)
        {
            auto fbtag = reinterpret_cast<KernAux_stivale2_struct_tag_framebuffer *>(tag);
            framebuffer = fbtag;
            return 1;
            break;
        }

        tag = reinterpret_cast<KernAux_stivale2_tag *>(tag->next);

    }

    /* Not Found */
    return 0;
}


bool KernAux_get_stivale2_memmap(KernAux_stivale2_struct* stivale2_params, KernAux_get_stivale2_memmap* memmap)
{
    auto tag = reinterpret_cast<KernAux_stivale2_tag *>(stivale2_params->tags);

    while (tag != NULL)
    {
        if(tag->identifier == KernAux_STIVALE2_STRUCT_TAG_MEMMAP_ID)
        {
            auto memmaptag = reinterpret_cast<KernAux_get_stivale2_memmap *>(tag);
            memmap = memmaptag;
            return 1;
            break;
        }

        tag = reinterpret_cast<KernAux_stivale2_tag *>(tag->next);

    }

    /* Not Found */
    return 0;
}

bool KernAux_get_stivale2_edid(KernAux_stivale2_struct* stivale2_params, KernAux_stivale2_struct_tag_edid* edid)
{
    auto tag = reinterpret_cast<KernAux_stivale2_tag *>(stivale2_params->tags);

    while (tag != NULL)
    {
        if(tag->identifier == KernAux_STIVALE2_STRUCT_TAG_EDID_ID)
        {
            auto edidtag = reinterpret_cast<KernAux_stivale2_struct_tag_edid *>(tag);
            edid = edidtag;
            return 1;
            break;
        }

        tag = reinterpret_cast<KernAux_stivale2_tag *>(tag->next);

    }

    /* Not Found */
    return 0;
}

bool KernAux_get_stivale2_modules(KernAux_stivale2_struct* stivale2_params, KernAux_stivale2_struct_tag_modules* modules)
{
    auto tag = reinterpret_cast<KernAux_stivale2_tag *>(stivale2_params->tags);

    while (tag != NULL)
    {
        if(tag->identifier == KernAux_STIVALE2_STRUCT_TAG_MODULES_ID)
        {
            auto modtag = reinterpret_cast<KernAux_stivale2_struct_tag_modules *>(tag);
            modules = modtag;
            return 1;
            break;
        }
        tag = reinterpret_cast<KernAux_stivale2_tag *>(tag->next);
    }
    /* Not Found */
    return 0;
}

bool KernAux_get_stivale2_kernel_file_v2(KernAux_stivale2_struct* stivale2_params, KernAux_stivale2_struct_tag_kernel_file_v2* kfile)
{
    auto tag = reinterpret_cast<KernAux_stivale2_tag *>(stivale2_params->tags);

    while (tag != NULL)
    {
        if(tag->identifier == KernAux_STIVALE2_STRUCT_TAG_KERNEL_FILE_V2_ID)
        {
            auto kv2tag = reinterpret_cast<KernAux_stivale2_struct_tag_kernel_file_v2 *>(tag);
            kfile = kv2tag;
            return 1;
            break;
        }
        tag = reinterpret_cast<KernAux_stivale2_tag *>(tag->next);
    }
    /* Not Found */
    return 0;
}

bool KernAux_get_stivale2_smp(KernAux_stivale2_struct* stivale2_params, KernAux_stivale2_struct_tag_smp* smp)
{
    auto tag = reinterpret_cast<KernAux_stivale2_tag *>(stivale2_params->tags);

    while (tag != NULL)
    {
        if(tag->identifier == KernAux_STIVALE2_STRUCT_TAG_SMP_ID)
        {
            auto smptag = reinterpret_cast<KernAux_stivale2_struct_tag_smp *>(tag);
            smp = smptag;
            return 1;
            break;
        }
        tag = reinterpret_cast<KernAux_stivale2_tag *>(tag->next);
    }
    /* Not Found */
    return 0;
}
