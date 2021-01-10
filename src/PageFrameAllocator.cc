#include <PageFrameAllocator.hh>

u64 freeMemory;
u64 reservedMemory;
u64 usedMemory;
bool Initialized = false;

void PageFrameAllocator::ReadEFIMemoryMap(EFI_MEMORY_DESCRIPTOR *mMap, size_t mMapSize, size_t mMapDescSize)
{
	if (Initialized)
		return;

	Initialized = true;

	u64 mMapEntries = mMapSize / mMapDescSize;

	void *largestFreeMemSeg = 0;
	size_t largestFreeMemSegSize = 0;

	for (int i = 0; i < mMapEntries; i++)
	{
		EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)((u64)mMap + (i * mMapDescSize));
		if (desc->type == 7)
		{
			//	type 7 is conventional
			if (desc->numPages << 12 > largestFreeMemSegSize)
			{
				largestFreeMemSeg = desc->physAddr;
				largestFreeMemSegSize = desc->numPages << 12;
			}
		}
	}

	u64 memorySize = GetMemorySize(mMap, mMapEntries, mMapDescSize);
	freeMemory = memorySize;

	u64 bitmapSize = memorySize / 4096 / 8 + 1;

	//	Initialize Bitmap
	InitBitmap(bitmapSize, largestFreeMemSeg);

	//	lock bitmap pages
	//	reserve unusable pages
}

void PageFrameAllocator::InitBitmap(size_t bitmapSize, void *bufferAddress)
{
	PageBitmap.Size = bitmapSize;
	PageBitmap.Buffer = (u8 *)bufferAddress;
	for (int i = 0; i < bitmapSize; i += 4)
	{
		*(u64 *)(PageBitmap.Buffer + i) = 0;
	}
}