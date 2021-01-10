#include <types/ints.hh>
#include <lowlevel/Framebuffer.hh>
#include <lowlevel/PSF1.hh>
#include <BasicRenderer.hh>
#include <cstr.hh>

extern "C" void _start(Framebuffer *p_framebuffer, PSF1_FONT *p_font)
{
	BasicRenderer out{p_framebuffer, p_font};

	out.color.g = 0;
	out.print(toHString(0xdeadbeef));
	out.print("test");
}
