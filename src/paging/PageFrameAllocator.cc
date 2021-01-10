#include <paging/PageFrameAllocator.hh>

PageFrameAllocator globalAllocator;

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
		{ // type = EfiConventionalMemory
			if (desc->numPages * 4096 > largestFreeMemSegSize)
			{
				largestFreeMemSeg = desc->physAddr;
				largestFreeMemSegSize = desc->numPages * 4096;
			}
		}
	}

	u64 memorySize = GetMemorySize(mMap, mMapEntries, mMapDescSize);
	freeMemory = memorySize;
	u64 bitmapSize = memorySize / 4096 / 8 + 1;

	InitBitmap(bitmapSize, largestFreeMemSeg);

	LockPages(&PageBitmap, PageBitmap.size / 4096 + 1);

	for (int i = 0; i < mMapEntries; i++)
	{
		EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)((u64)mMap + (i * mMapDescSize));
		if (desc->type != 7)
		{ // not efiConventionalMemory
			ReservePages(desc->physAddr, desc->numPages);
		}
	}
}

void PageFrameAllocator::InitBitmap(size_t bitmapSize, void *bufferAddress)
{
	PageBitmap.size = bitmapSize;
	PageBitmap.buffer = (u8 *)bufferAddress;
	for (int i = 0; i < bitmapSize; i += 4)
	{
		*(u64 *)(PageBitmap.buffer + i) = 0;
	}
}

void PageFrameAllocator::FreePage(void *address)
{
	u64 index = (u64)address >> 12;
	if (!PageBitmap[index])
		return;
	PageBitmap.set(index, false);
	freeMemory += 1 << 12;
	usedMemory -= 1 << 12;
}
void PageFrameAllocator::LockPage(void *address)
{
	u64 index = (u64)address >> 12;
	if (PageBitmap[index])
		return;
	PageBitmap.set(index, true);
	freeMemory -= 1 << 12;
	usedMemory += 1 << 12;
}
void PageFrameAllocator::ReservePage(void *address)
{
	u64 index = (u64)address >> 12;
	if (!PageBitmap[index])
		return;
	PageBitmap.set(index, true);
	freeMemory -= 1 << 12;
	reservedMemory += 1 << 12;
}
void PageFrameAllocator::UnreservePage(void *address)
{
	u64 index = (u64)address >> 12;
	if (PageBitmap[index])
		return;
	PageBitmap.set(index, false);
	freeMemory += 1 << 12;
	reservedMemory -= 1 << 12;
}

void PageFrameAllocator::FreePages(void *address, u64 pageCount)
{
	for (int t = 0; t < pageCount; t++)
	{
		FreePage((void *)((u64)address + (t << 12)));
	}
}
void PageFrameAllocator::LockPages(void *address, u64 pageCount)
{
	for (int t = 0; t < pageCount; t++)
	{
		LockPage((void *)((u64)address + (t << 12)));
	}
}
void PageFrameAllocator::ReservePages(void *address, u64 pageCount)
{
	for (int t = 0; t < pageCount; t++)
	{
		ReservePage((void *)((u64)address + (t << 12)));
	}
}
void PageFrameAllocator::UnreservePages(void *address, u64 pageCount)
{
	for (int t = 0; t < pageCount; t++)
	{
		UnreservePage((void *)((u64)address + (t << 12)));
	}
}

void *PageFrameAllocator::requestPage()
{
	for (u64 i = 0; i < PageBitmap.size * 8; i++)
	{
		if (!PageBitmap[i])
		{
			LockPage((void *)(i * 4096));
			return (void *)(i * 4096);
		}
	}

	return 0; // TODO: PageFrame swap to file
}