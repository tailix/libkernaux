#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/extras/font.h>
#include <kernaux/drivers/framebuffer.h>

void KernAux_Framebuffer_init_default(KernAux_Framebuffer framebuffer, uint32_t width, uint32_t height, uint32_t pitch, uint32_t depth, uintptr_t buf_addr, uint8_t frame_type)
{
    KERNAUX_NOTNULL_RETURN(framebuffer);
    KERNAUX_ASSERT_RETURN(width > 0);
    KERNAUX_ASSERT_RETURN(height > 0);
    KERNAUX_ASSERT_RETURN(pitch > 0);
    KERNAUX_ASSERT_RETURN(depth > 0);
    KERNAUX_NOTNULL_RETURN(buf_addr);

    framebuffer->frame_width = width;
    framebuffer->frame_height = height;
    framebuffer->frame_pitch = pitch;
    framebuffer->frame_depth = depth;
    framebuffer->buffer_addr = buf_addr;
    framebuffer->frame_type = frame_type;
    framebuffer->redmask_size = 0;
    framebuffer->redmask_shift = 0;
    framebuffer->greenmask_size = 0;
    framebuffer->greenmask_shift = 0;
    framebuffer->bluemask_size = 0;
    framebuffer->bluemask_shift = 0;
}

void KernAux_Framebuffer_init(KernAux_Framebuffer framebuffer, uint32_t width, uint32_t height, uint32_t pitch, uint32_t depth, uintptr_t buf_addr, uint8_t frame_type, uint8_t redmask_sz, uint8_t redmask_shift, uint8_t greenmask_sz, uint8_t greenmask_shift, uint8_t bluemask_sz, uint8_t bluemask_shift)
{
    KERNAUX_NOTNULL_RETURN(framebuffer);
    KERNAUX_ASSERT_RETURN(width > 0);
    KERNAUX_ASSERT_RETURN(height > 0);
    KERNAUX_ASSERT_RETURN(pitch > 0);
    KERNAUX_ASSERT_RETURN(depth > 0);
    KERNAUX_NOTNULL_RETURN(buf_addr);

    framebuffer->frame_width = width;
    framebuffer->frame_height = height;
    framebuffer->frame_pitch = pitch;
    framebuffer->frame_depth = depth;
    framebuffer->buffer_addr = buf_addr;
    framebuffer->frame_type = frame_type;
    framebuffer->redmask_size = redmask_sz;
    framebuffer->redmask_shift = redmask_shift;
    framebuffer->greenmask_size = greenmask_sz;
    framebuffer->greenmask_shift = greenmask_shift;
    framebuffer->bluemask_size = bluemask_sz;
    framebuffer->bluemask_shift = bluemask_shift;
}

void KernAux_Framebuffer_putpixel_rgb(KernAux_Framebuffer framebuffer, int x, int y, uint32_t hex)
{
    KERNAUX_NOTNULL_RETURN(framebuffer);
    KERNAUX_ASSERT_RETURN(framebuffer->frame_type == FRAME_TYPE_RGB);
    KERNAUX_ASSERT_RETURN(x <= framebuffer->frame_width);
    KERNAUX_ASSERT_RETURN(y <= framebuffer->frame_height);
    KERNAUX_ASSERT_RETURN(32 >= framebuffer->frame_depth);

    switch (framebuffer->frame_depth)
    {
        case 32:
        {
            uint32_t *spix = (uint32_t*)framebuffer->buffer_addr;
            size_t vr = (y * framebuffer->frame_pitch) / 4;
            spix[vr + x] = hex;
            break;
        }
        case 16:
        {
            uint16_t *spix = (uint16_t*)framebuffer->buffer_addr;
            size_t vr = (y * framebuffer->frame_pitch) / 2;
            spix[vr + x] = hex;
            break;
        }
        default:
        {
            /* 8 Bit */
            uint8_t *spix = (uint8_t*)framebuffer->buffer_addr;
            size_t vr = (y * framebuffer->frame_pitch);
            spix[vr + x] = hex;
            break;
        }
    }
}

void KernAux_Framebuffer_putpixel_ega(KernAux_Framebuffer framebuffer, int x, int y, enum KernAux_Framebuffer_VGAColorPalette color)
{
    KERNAUX_NOTNULL_RETURN(framebuffer);
    KERNAUX_ASSERT_RETURN(framebuffer->frame_type == FRAME_TYPE_EGA);
    KERNAUX_ASSERT_RETURN(x <= framebuffer->frame_width);
    KERNAUX_ASSERT_RETURN(y <= framebuffer->frame_height);

    KernAux_Framebuffer_putchar_ega(framebuffer, x, y, ' ', color);
}


void KernAux_Framebuffer_putchar_ega(KernAux_Framebuffer framebuffer, int x, int y, unsigned char c, enum KernAux_Framebuffer_VGAColorPalette color)
{
    KERNAUX_NOTNULL_RETURN(framebuffer);
    KERNAUX_ASSERT_RETURN(framebuffer->frame_type == FRAME_TYPE_EGA);
    KERNAUX_ASSERT_RETURN(x <= framebuffer->frame_width);
    KERNAUX_ASSERT_RETURN(y <= framebuffer->frame_height);

    if(framebuffer->frame_depth == 16)
    {
        uint16_t *spix = (uint16_t*)framebuffer->buffer_addr;
        const size_t index = y * framebuffer->frame_width + x;
        spix[index] = (uint16_t)c | (uint16_t)color << 8;
    }
    else
    {
        uint8_t *spix = (uint8_t*)framebuffer->buffer_addr;
        const size_t index = y * framebuffer->frame_width + x;
        spix[index] = (uint8_t)c | (uint8_t)color << 8;
    }
}

void KernAux_Framebuffer_putchar8x16_rgb(KernAux_Framebuffer framebuffer, int x, int y, unsigned char c, uint32_t fg, uint32_t bg)
{

#ifdef KERNAUX_INCLUDED_EXTRAS_FONT8X16
    const KernAux_FontCharMap charBitmap = KernAux_get_font8x16_unicode(c);

    for (size_t y = 0; y < 16; y++)
    {
        for (size_t x = 0; x < 8; x++)
        {
            if(charBitmap->data[y] & (1 << x))
            {
                KernAux_Framebuffer_putpixel_rgb(framebuffer, x, y, fg);
            }
            else
            {
                if(bg != RGB_COLOR_TRANSPARENT)
                    KernAux_Framebuffer_putpixel_rgb(framebuffer, x, y, bg);
            }
        }
    }
#endif
}



void KernAux_Framebuffer_fillarea_rgb(KernAux_Framebuffer framebuffer, int x0, int y0, int x1, int y1, uint32_t hex)
{
    KERNAUX_NOTNULL_RETURN(framebuffer);
    KERNAUX_ASSERT_RETURN(framebuffer->frame_type == FRAME_TYPE_RGB);
    KERNAUX_ASSERT_RETURN((y0+y1) <= framebuffer->frame_height);
    KERNAUX_ASSERT_RETURN((x0+x1) <= framebuffer->frame_width);

    for (int y = y0; y < y1; y++)
    {
        for (int x = x0; x < x1; x++)
        {
            KernAux_Framebuffer_putpixel_rgb(framebuffer, x, y, hex);
        }
    }
}

void KernAux_Framebuffer_fillarea_ega(KernAux_Framebuffer framebuffer, int x0, int y0, int x1, int y1, enum KernAux_Framebuffer_VGAColorPalette color)
{
    KERNAUX_NOTNULL_RETURN(framebuffer);
    KERNAUX_ASSERT_RETURN(framebuffer->frame_type == FRAME_TYPE_EGA);
    KERNAUX_ASSERT_RETURN((y0+y1) <= framebuffer->frame_height);
    KERNAUX_ASSERT_RETURN((x0+x1) <= framebuffer->frame_width);

    for (int y = y0; y < y1; y++)
    {
        for (int x = x0; x < x1; x++)
        {
            KernAux_Framebuffer_putpixel_ega(framebuffer, x, y, color);
        }
    }
}
