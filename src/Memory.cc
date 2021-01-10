#include <Memory.hh>

u64 GetMemorySize(EFI_MEMORY_DESCRIPTOR *mMap, u64 mMapEntries, u64 mMapDescSize)
{
	static u64 memorySizeBytes = 0;
	if (memorySizeBytes > 0)
		return memorySizeBytes;

	for (int i = 0; i < mMapEntries; i++)
	{
		EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)((u64)mMap + (i * mMapDescSize));
		memorySizeBytes += desc->numPages * 4096;
	}

	return memorySizeBytes;
}

// void memset(void *start, u8 value, size_t size)
// {
// 	auto dvalue = ((((((value << 8) | value) << 8) | value) << 8) | value);
// 	for (u64 i = 0; i < size; i += 4)
// 	{
// 		*(u64 *)((u64)start + i) = dvalue;
// 	}

// 	for (u64 i = (size >> 2) << 2; i < size; i++)
// 	{
// 		*(u8 *)((u64)start + i) = value;
// 	}
// }

void memset(void *start, u8 value, size_t size)
{
	for (u64 i = 0; i < size; i++)
	{
		*(u8 *)((u64)start + i) = value;
	}
}
