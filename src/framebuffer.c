/***
 * @ashusharmasigdev [ashusharma.sigmadev@gmail.com] [github.com/ashusharmasigdev] [caitraos.github.io]
 * date : 12 jan 2022
 * file : framebuffer.c
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/framebuffer.h>

framebuffer_t framebuffer(uint32_t width, uint32_t height, uint32_t pitch, uint32_t depth, uintptr_t buf_addr)
{
    return (framebuffer_t){
        .frame_width=width,
        .frame_height=height,
        .frame_pitch=pitch,
        .frame_depth=depth,
        .buffer_addr=buf_addr,
        .redmask_size=0,
        .redmask_shift=0,
        .greenmask_size=0,
        .greenmask_shift=0,
        .bluemask_size=0,
        .bluemask_shift=0
    };
}

framebuffer_t framebuffer(uint32_t width, uint32_t height, uint32_t pitch, uint32_t depth, uintptr_t buf_addr, uint8_t redmask_sz, uint8_t redmask_shift, uint8_t greenmask_sz, uint8_t greenmask_shift, uint8_t bluemask_sz, uint8_t bluemask_shift)
{
    return (framebuffer_t){
        .frame_width=width,
        .frame_height=height,
        .frame_pitch=pitch,
        .frame_depth=depth,
        .buffer_addr=buf_addr,
        .redmask_size=redmask_sz,
        .redmask_shift=redmask_shift,
        .greenmask_size=greenmask_sz,
        .greenmask_shift=greenmask_shift,
        .bluemask_size=bluemask_sz,
        .bluemask_shift=bluemask_shift
    };
}


void putpixel(framebuffer_t* _framebuffer, int x, int y, uint32_t hex)
{
    switch (_framebuffer->frame_depth)
    {
        case 32:
        {
            uint32_t *spix = (uint32_t*)_framebuffer->buffer_addr;
            size_t vr = (y * _framebuffer->frame_pitch) / 4;
            spix[vr+x] = hex;
            break;
        }
        case 16:
        {
            uint16_t *spix = (uint16_t*)_framebuffer->buffer_addr;
            size_t vr = (y * _framebuffer->frame_pitch) / 2;
            spix[vr+x] = hex;
            break;
        }
        default:
        {
            /* 8 Bit */
            uint8_t *spix = (uint8_t*)_framebuffer->buffer_addr;
            size_t vr = (y * _framebuffer->frame_pitch);
            spix[vr+x] = hex;
            break;
        }
    }
}


void fillarea(framebuffer_t* _framebuffer, int x0, int y0, int x1, int y1, uint32_t hex)
{
    if(y1 > _framebuffer->height)   return;
    if(x1 > _framebuffer->width)   return;
    
    for (int y = y0; y < y1; y++)
    {
        for (int x = x0; x < x1; x++)
        {
            putpixel(_framebuffer, x, y, hex);
        }
        
    }
    
}