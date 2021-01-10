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

private:
	void InitBitmap(size_t bitmapSize, void *bufferAddress);
};