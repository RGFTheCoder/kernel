#include <Bitmap.hh>

bool Bitmap::operator[](size_t i) const
{
	size_t byteIndex = i >> 3;
	u8 bitIndex = i & 0b111;
	u8 bitIndexer = 0b10000000 >> bitIndex;
	if ((buffer[byteIndex] & bitIndexer) > 0)
	{
		return true;
	}
	return false;
}
void Bitmap::set(size_t i, bool value)
{
	size_t byteIndex = i >> 3;
	u8 bitIndex = i & 0b111;
	u8 bitIndexer = 0b10000000 >> bitIndex;
	buffer[byteIndex] &= ~bitIndexer;
	if (value)
	{
		buffer[byteIndex] |= bitIndexer;
	}
}