#pragma once
#include <EFIMemory.hh>
#include <types/ints.hh>
#include <Bitmap.hh>
#include <Memory.hh>

class PageFrameAllocator
{
public:
	void ReadEFIMemoryMap(EFI_MEMORY_DESCRIPTOR *mMap, size_t mMapSize, size_t mMapDescSize);
	Bitmap PageBitmap;
	void FreePage(void *address);
	void LockPage(void *address);
	void *requestPage();

	void FreePages(void *address, u64 pageCount);
	void LockPages(void *address, u64 pageCount);

	inline u64 GetFreeRAM() { return freeMemory; };
	inline u64 GetUsedRAM() { return usedMemory; };
	inline u64 GetReservedRAM() { return reservedMemory; };

private:
	void InitBitmap(size_t bitmapSize, void *bufferAddress);
	void ReservePage(void *address);
	void UnreservePage(void *address);
	void ReservePages(void *address, u64 pageCount);
	void UnreservePages(void *address, u64 pageCount);

	u64 freeMemory = 0;
	u64 reservedMemory = 0;
	u64 usedMemory = 0;
	bool Initialized = false;
};

extern PageFrameAllocator globalAllocator;