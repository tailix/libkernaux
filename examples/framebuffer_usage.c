#include <kernaux/framebuffer.h>


/*important params*/
framebuffer_t myframe = framebuffer(0/*framewidth*/,0/*frameheight*/,0/*framepitch*/,0/*framedepth*/,0/*frameaddr*/);

/*optional params*/
framebuffer_t myframe = framebuffer(0/*framewidth*/,0/*frameheight*/,0/*framepitch*/,0/*framedepth*/,0/*frameaddr*/, 0/*red mask size*/, 0/*red mask shift*/, 0/*green mask size*/, 0/*green mask shift*/, 0/*blue mask size*/, 0/*blue mask shift*/);

putpixel(myframe, 20, 20, 0xFFFF0000);

fillarea(myframe, 0, 0, 300, 400, 0xFF0066FF);