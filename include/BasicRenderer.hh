#pragma once
#include <types/ints.hh>
#include <math/Point.hh>
#include <math/RGBA.hh>
#include <lowlevel/PSF1.hh>
#include <lowlevel/Framebuffer.hh>

class BasicRenderer
{

	Framebuffer *framebuffer;
	PSF1_FONT *font;

public:
	uint maxWidth;
	RGBA color{0xff, 0xff, 0xff, 0xff};
	constexpr inline BasicRenderer(Framebuffer *framebuffer, PSF1_FONT *font)
			: framebuffer(framebuffer), font(font), maxWidth(framebuffer->PixelsPerScanline){};

	Point cursorPosition;

	void putchar(char chr, uint xOff, uint yOff);
	void print(const char *str);
};

extern BasicRenderer *globalRenderer;
