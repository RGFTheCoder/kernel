#pragma once
#include <types/ints.hh>

class Bitmap
{
public:
	size_t Size;
	u8 *Buffer;
	bool operator[](size_t i) const;
	void set(size_t i, bool value);
};