#include <Bitmap.hh>

bool Bitmap::operator[](size_t i) const
{
	size_t byte = i >> 3;
	u8 bitIndex = i & 0b111;
	return (buffer[byte] >> bitIndex) & 1;
}
void Bitmap::set(size_t i, bool value)
{

	size_t byte = i >> 3;
	u8 bitIndex = i & 0b111;
	u8 bitIndexer = 1 << bitIndex;
	buffer[byte] &= ~bitIndexer;
	if (value)
		buffer[byte] |= bitIndexer;
}