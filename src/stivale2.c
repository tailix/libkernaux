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
        tag = reinterpret_cast<KernAux_stivale2_tag *>(tags->next);
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

        tag = reinterpret_cast<KernAux_stivale2_tag *>(tags->next);

    }

    /* Not Found */
    return 0;
}
