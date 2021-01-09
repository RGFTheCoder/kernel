#pragma once
#include <types/ints.hh>

struct PSF1_HEADER
{
	u8 magic[2];
	u8 mode;
	u8 charsize;
};

struct PSF1_FONT
{
	PSF1_HEADER *psf1_Header;
	i8 *glyphBuffer;
};