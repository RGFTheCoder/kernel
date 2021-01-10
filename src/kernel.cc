#include <types/ints.hh>
#include <lowlevel/Framebuffer.hh>
#include <lowlevel/PSF1.hh>
#include <BasicRenderer.hh>
#include <EFIMemory.hh>
#include <cstr.hh>
#include <Memory.hh>
#include <Bitmap.hh>
#include <paging/PageFrameAllocator.hh>
#include <paging/PageMapIndexer.hh>
#include <paging/paging.hh>
#include <paging/PageTableManager.hh>

struct BootInfo
{
	Framebuffer *framebuffer;
	PSF1_FONT *font;
	EFI_MEMORY_DESCRIPTOR *mMap;
	ul mMapSize;
	ul mMapDescSize;
};

u8 testbuffer[20];

extern u64 _KernelStart;
extern u64 _KernelEnd;

extern "C" void _start(BootInfo *bootinfo)
{
	BasicRenderer out{bootinfo->framebuffer, bootinfo->font};

	u64 mMapEntries = bootinfo->mMapSize / bootinfo->mMapDescSize;

	globalAllocator.ReadEFIMemoryMap(bootinfo->mMap, bootinfo->mMapSize, bootinfo->mMapDescSize);

	u64 kernelSize = (u64)&_KernelEnd - (u64)&_KernelStart;
	u64 kernelPages = kernelSize >> 12 + 1;

	out.print("Test\n\r");
	globalAllocator.LockPages(&_KernelStart, kernelPages);
	out.print("Test\n\r");

	PageTable *PML4 = (PageTable *)globalAllocator.requestPage();
	// memset(PML4, 0, 0x1000);
	out.print("Test\n\r");

	PageTableManager pageTableManager{PML4};

	for (u64 t = 0; t < GetMemorySize(bootinfo->mMap, mMapEntries, bootinfo->mMapDescSize); t += 0x1000)
	{
		pageTableManager.MapMemory((void *)t, (void *)t);
	}

	u64 fbBase = (u64)bootinfo->framebuffer->BaseAddress;
	u64 fbSize = (u64)bootinfo->framebuffer->BufferSize;
	for (u64 t = fbBase; t < fbBase + fbSize; t += 0x1000)
	{
		pageTableManager.MapMemory((void *)t, (void *)t);
	}

	asm("mov %0, %%cr3"
			:
			: "r"(PML4));

	out.print("Test\n\r");
}
