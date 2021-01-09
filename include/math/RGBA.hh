#pragma once
#include <types/ints.hh>

class RGBA
{
public:
	u8 r;
	u8 g;
	u8 b;
	u8 a;

	inline u64 getData()
	{
		return (((((a << 8) | r) << 8) | g) << 8) | b;
	}
};