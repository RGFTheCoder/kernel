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