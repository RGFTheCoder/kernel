#pragma once
#include <types/ints.hh>

struct Framebuffer
{
	u32 *BaseAddress;
	size_t BufferSize;
	uint Width;
	uint Height;
	uint PixelsPerScanline;
};