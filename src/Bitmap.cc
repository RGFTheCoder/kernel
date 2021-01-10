#include <Bitmap.hh>

bool Bitmap::operator[](size_t i) const
{
	if (i > size * 8)
		return false;
	size_t byteIndex = i >> 3;
	u8 bitIndex = i & 0b111;
	u8 bitIndexer = 0b10000000 >> bitIndex;
	if ((buffer[byteIndex] & bitIndexer) > 0)
	{
		return true;
	}
	return false;
}
bool Bitmap::set(size_t i, bool value)
{
	if (i > size * 8)
		return false;
	size_t byteIndex = i >> 3;
	u8 bitIndex = i & 0b111;
	u8 bitIndexer = 0b10000000 >> bitIndex;
	buffer[byteIndex] &= ~bitIndexer;
	if (value)
	{
		buffer[byteIndex] |= bitIndexer;
	}
	return true;
}