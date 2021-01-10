#pragma once
#include <types/ints.hh>

class Bitmap
{
public:
	size_t size;
	u8 *buffer;
	bool operator[](size_t i) const;
	bool set(size_t i, bool value);
};