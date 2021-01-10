#include <cstr.hh>

const char *decimalCharset = "0123456789";
const char *hexCharset = "0123456789ABCDEF";

char leftPadLastOutput[255];
const char *padLeft(const char *str, u8 targetLength, char padding)
{
	auto currLength = strLen(str);
	auto lengthNeeded = targetLength - currLength;

	auto outPtr = leftPadLastOutput;
	auto inPtr = str;

	for (auto i = 0; i < lengthNeeded; i++)
	{
		*outPtr = padding;
		outPtr++;
	}

	while (*inPtr != 0)
	{
		*outPtr = *inPtr;
		inPtr++;
		outPtr++;
	}
	*outPtr = 0;

	return leftPadLastOutput;
}

size_t strLen(const char *str)
{
	size_t out = 0;
	while (*str != 0)
	{
		out++;
		str++;
	}
	return out;
}

char intToStringLastOutput[66]; // 64 for 64-bit with 2-dictionary + null terminator + negation sign
const char *toString(u64 value, const char *dict)
{
	u8 size;
	u64 sizeTest = value;
	uint base = strLen(dict);
	while (sizeTest / base > 0)
	{
		sizeTest /= base;
		size++;
	}

	u8 index = 0;
	while (index <= size)
	{
		u8 remainder = value % base;
		value /= base;
		intToStringLastOutput[size - index] = dict[remainder];
		index++;
	}
	intToStringLastOutput[size + 1] = 0;

	return intToStringLastOutput;
}

const char *toString(i64 value, const char *dict)
{
	u8 isNegative = value < 0 ? 1 : 0;

	if (value < 0)
	{
		value = -value;
		intToStringLastOutput[0] = '-';
	}

	u8 size;
	u64 sizeTest = value;
	uint base = strLen(dict);
	while (sizeTest / base > 0)
	{
		sizeTest /= base;
		size++;
	}

	u8 index = 0;
	while (index <= size)
	{
		u8 remainder = value % base;
		value /= base;
		intToStringLastOutput[size - index + isNegative] = dict[remainder];
		index++;
	}
	intToStringLastOutput[size + 1 + isNegative] = 0;

	return intToStringLastOutput;
}

char doubleToStringLastOutput[64 + 1 + 255]; // 64 binary int + 1 decimal point + 255 decimals
const char *toString(double value, u8 decimalPlaces, const char *dict)
{
	uint base = strLen(dict);

	char *intPtr = (char *)toString((i64)value);
	char *doublePtr = doubleToStringLastOutput;

	if (value < 0)
	{
		value *= -1;
	}

	while (*intPtr != 0)
	{
		*doublePtr = *intPtr;
		intPtr++;
		doublePtr++;
	}

	*doublePtr = '.';
	doublePtr++;

	double newValue = value - (i64)value;

	for (u8 i = 0; i < decimalPlaces; ++i)
	{
		newValue *= base;
		*doublePtr = dict[(int)newValue];
		newValue -= (int)newValue;
		doublePtr++;
	}

	*doublePtr = 0;

	return doubleToStringLastOutput;
}