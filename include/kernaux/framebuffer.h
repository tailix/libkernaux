/***
 * @ashusharmasigdev [ashusharma.sigmadev@gmail.com] [github.com/ashusharmasigdev] [caitraos.github.io]
 * date : 12 jan 2022
 * file : framebuffer.h
*/

#ifndef KERNAUX_INCLUDED_FRAMEBUFFER
#define KERNAUX_INCLUDED_FRAMEBUFFER

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    
    uint32_t    frame_width;
    uint32_t    frame_height;
    uint32_t    frame_pitch;
    uint32_t    frame_depth;
    uintptr_t   buffer_addr;
    uint8_t     redmask_size;
    uint8_t     redmask_shift;
    uint8_t     greenmask_size;
    uint8_t     greenmask_shift;
    uint8_t     bluemask_size;
    uint8_t     bluemask_shift;
} framebuffer_t;


framebuffer_t framebuffer(uint32_t width, uint32_t height, uint32_t pitch, uint32_t depth, uintptr_t buf_addr);
framebuffer_t framebuffer(uint32_t width, uint32_t height, uint32_t pitch, uint32_t depth, uintptr_t buf_addr, uint8_t redmask_sz, uint8_t redmask_shift, uint8_t greenmask_sz, uint8_t greenmask_shift, uint8_t bluemask_sz, uint8_t bluemask_shift);

void putpixel(framebuffer_t _framebuffer, int x, int y, uint32_t hex);

void fillarea(framebuffer_t _framebuffer, int x0, int y0, int x1, int y1, uint32_t hex);

#ifdef __cplusplus
}
#endif

#endif
