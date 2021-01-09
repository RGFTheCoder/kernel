#include <types/ints.hh>
#include <lowlevel/Framebuffer.hh>
#include <lowlevel/PSF1.hh>
#include <BasicRenderer.hh>

extern "C" void _start(Framebuffer *p_framebuffer, PSF1_FONT *p_font)
{
	BasicRenderer out{p_framebuffer, p_font};

	for (int i = 0; i < 50; i++)
	{
		out.color.g = 0;
		out.print("Hello world.");
	}
}
