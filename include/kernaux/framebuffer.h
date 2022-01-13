#ifndef KERNAUX_INCLUDED_FRAMEBUFFER
#define KERNAUX_INCLUDED_FRAMEBUFFER

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

enum KernAux_Framebuffer_FrameType {
    FRAME_TYPE_RGB = 1,
    FRAME_TYPE_EGA = 2
};

enum KernAux_Framebuffer_VGAColorPalette {
    VGA_BLACK = 0x00,
    VGA_BLUE = 0x01,
    VGA_GREEN = 0x02,
    VGA_CYAN = 0x03,
    VGA_RED = 0x04,
    VGA_MAGENTA = 0x05,
    VGA_BROWN = 0x06,
    VGA_WHITE = 0x07,
    VGA_GRAY = 0x08,
    VGA_LIGHT_BLUE = 0x09,
    VGA_LIGHT_GREEN = 0x0A,
    VGA_LIGHT_CYAN = 0x0B,
    VGA_LIGHT_RED = 0x0C,
    VGA_LIGHT_MAGENTA = 0x0D,
    VGA_YELLOW = 0x0E,
    VGA_BRIGHT_WHITE = 0x0F
};

typedef struct KernAux_Framebuffer {
    uint32_t  frame_width;
    uint32_t  frame_height;
    uint32_t  frame_pitch;
    uint32_t  frame_depth;
    uintptr_t buffer_addr;
    uint8_t   frame_type;
    uint8_t   redmask_size;
    uint8_t   redmask_shift;
    uint8_t   greenmask_size;
    uint8_t   greenmask_shift;
    uint8_t   bluemask_size;
    uint8_t   bluemask_shift;
} *KernAux_Framebuffer;


void KernAux_Framebuffer_init_default(KernAux_Framebuffer framebuffer, uint32_t width, uint32_t height, uint32_t pitch, uint32_t depth, uintptr_t buf_addr, uint8_t frame_type);
void KernAux_Framebuffer_init(KernAux_Framebuffer _framebuffer, uint32_t width, uint32_t height, uint32_t pitch, uint32_t depth, uintptr_t buf_addr, uint8_t frame_type, uint8_t redmask_sz, uint8_t redmask_shift, uint8_t greenmask_sz, uint8_t greenmask_shift, uint8_t bluemask_sz, uint8_t bluemask_shift);

void KernAux_Framebuffer_putpixel_rgb(KernAux_Framebuffer framebuffer, int x, int y, uint32_t hex);
void KernAux_Framebuffer_putpixel_ega(KernAux_Framebuffer framebuffer, int x, int y, enum KernAux_Framebuffer_VGAColorPalette color);
void KernAux_Framebuffer_putchar_ega(KernAux_Framebuffer framebuffer, int x, int y, unsigned char c, enum KernAux_Framebuffer_VGAColorPalette color);

void KernAux_Framebuffer_fillarea_rgb(KernAux_Framebuffer framebuffer, int x0, int y0, int x1, int y1, uint32_t hex);
void KernAux_Framebuffer_fillarea_ega(KernAux_Framebuffer framebuffer, int x0, int y0, int x1, int y1, enum KernAux_Framebuffer_VGAColorPalette color);

#ifdef __cplusplus
}
#endif

#endif
