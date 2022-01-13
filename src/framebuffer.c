#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/framebuffer.h>

void KernAux_Framebuffer_init_default(KernAux_Framebuffer* _framebuffer, uint32_t width, uint32_t height, uint32_t pitch, uint32_t depth, uintptr_t buf_addr, uint8_t frame_type)
{
    KERNAUX_NOTNULL_RETURN(_framebuffer);
    KERNAUX_ASSERT_RETURN(width > 0);
    KERNAUX_ASSERT_RETURN(height > 0);
    KERNAUX_ASSERT_RETURN(pitch > 0);
    KERNAUX_ASSERT_RETURN(depth > 0);
    KERNAUX_NOTNULL_RETURN(buf_addr);

    _framebuffer->frame_width = width;
    _framebuffer->frame_height = height;
    _framebuffer->frame_pitch = pitch;
    _framebuffer->frame_depth = depth;
    _framebuffer->buffer_addr = buf_addr;
    _framebuffer->frame_type = frame_type;
    _framebuffer->redmask_size = 0;
    _framebuffer->redmask_shift = 0;
    _framebuffer->greenmask_size = 0;
    _framebuffer->greenmask_shift = 0;
    _framebuffer->bluemask_size = 0;
    _framebuffer->bluemask_shift = 0;
}

void KernAux_Framebuffer_init(KernAux_Framebuffer* _framebuffer, uint32_t width, uint32_t height, uint32_t pitch, uint32_t depth, uintptr_t buf_addr, uint8_t frame_type, uint8_t redmask_sz, uint8_t redmask_shift, uint8_t greenmask_sz, uint8_t greenmask_shift, uint8_t bluemask_sz, uint8_t bluemask_shift)
{
    KERNAUX_NOTNULL_RETURN(_framebuffer);
    KERNAUX_ASSERT_RETURN(width > 0);
    KERNAUX_ASSERT_RETURN(height > 0);
    KERNAUX_ASSERT_RETURN(pitch > 0);
    KERNAUX_ASSERT_RETURN(depth > 0);
    KERNAUX_NOTNULL_RETURN(buf_addr);

    _framebuffer->frame_width = width;
    _framebuffer->frame_height = height;
    _framebuffer->frame_pitch = pitch;
    _framebuffer->frame_depth = depth;
    _framebuffer->buffer_addr = buf_addr;
    _framebuffer->frame_type = frame_type;
    _framebuffer->redmask_size = redmask_sz;
    _framebuffer->redmask_shift = redmask_shift;
    _framebuffer->greenmask_size = greenmask_sz;
    _framebuffer->greenmask_shift = greenmask_shift;
    _framebuffer->bluemask_size = bluemask_sz;
    _framebuffer->bluemask_shift = bluemask_shift;
}

void KernAux_Framebuffer_putpixel_rgb(KernAux_Framebuffer *_framebuffer, int x, int y, uint32_t hex)
{
    KERNAUX_NOTNULL_RETURN(_framebuffer);
    KERNAUX_ASSERT_RETURN(_framebuffer->frame_type == FRAME_TYPE_RGB);
    KERNAUX_ASSERT_RETURN(x <= _framebuffer->frame_width);
    KERNAUX_ASSERT_RETURN(y <= _framebuffer->frame_height);
    KERNAUX_ASSERT_RETURN(32 >= _framebuffer->frame_depth);

    switch (_framebuffer->frame_depth)
    {
        case 32:
        {
            uint32_t *spix = (uint32_t *)_framebuffer->buffer_addr;
            size_t vr = (y * _framebuffer->frame_pitch) / 4;
            spix[vr + x] = hex;
            break;
        }
        case 16:
        {
            uint16_t *spix = (uint16_t *)_framebuffer->buffer_addr;
            size_t vr = (y * _framebuffer->frame_pitch) / 2;
            spix[vr + x] = hex;
            break;
        }
        default:
        {
            /* 8 Bit */
            uint8_t *spix = (uint8_t *)_framebuffer->buffer_addr;
            size_t vr = (y * _framebuffer->frame_pitch);
            spix[vr + x] = hex;
            break;
        }
    }
}

void KernAux_Framebuffer_putpixel_ega(KernAux_Framebuffer* _framebuffer, int x, int y, enum kernAux_vga_color_palatte color)
{
    KERNAUX_NOTNULL_RETURN(_framebuffer);
    KERNAUX_ASSERT_RETURN(_framebuffer->frame_type == FRAME_TYPE_EGA);
    KERNAUX_ASSERT_RETURN(x <= _framebuffer->frame_width);
    KERNAUX_ASSERT_RETURN(y <= _framebuffer->frame_height);

    switch (_framebuffer->frame_depth)
    {
        case 16:
        {
            uint16_t *spix = (uint16_t *)_framebuffer->buffer_addr;
            size_t vr = (y * _framebuffer->frame_pitch) / 2;
            spix[vr + x] = color;
            break;
        }
        default:
        {
            uint8_t *spix = (uint8_t *)_framebuffer->buffer_addr;
            size_t vr = (y * _framebuffer->frame_pitch);
            spix[vr + x] = color;
            break;
        }
    }
}

void KernAux_Framebuffer_fillarea_rgb(KernAux_Framebuffer *_framebuffer, int x0, int y0, int x1, int y1, uint32_t hex)
{
    KERNAUX_NOTNULL_RETURN(_framebuffer);
    KERNAUX_ASSERT_RETURN(_framebuffer->frame_type == FRAME_TYPE_RGB);
    KERNAUX_ASSERT_RETURN((y0+y1) <= _framebuffer->frame_height);
    KERNAUX_ASSERT_RETURN((x0+x1) <= _framebuffer->frame_width);

    for (int y = y0; y < y1; y++)
    {
        for (int x = x0; x < x1; x++)
        {
            KernAux_Framebuffer_putpixel_rgb(_framebuffer, x, y, hex);
        }
    }
}

void KernAux_Framebuffer_fillarea_ega(KernAux_Framebuffer* _framebuffer, int x0, int y0, int x1, int y1, enum kernAux_vga_color_palatte color)
{
    KERNAUX_NOTNULL_RETURN(_framebuffer);
    KERNAUX_ASSERT_RETURN(_framebuffer->frame_type == FRAME_TYPE_EGA);
    KERNAUX_ASSERT_RETURN((y0+y1) <= _framebuffer->frame_height);
    KERNAUX_ASSERT_RETURN((x0+x1) <= _framebuffer->frame_width);

    for (int y = y0; y < y1; y++)
    {
        for (int x = x0; x < x1; x++)
        {
            KernAux_Framebuffer_putpixel_ega(_framebuffer, x, y, color);
        }
    }
}
