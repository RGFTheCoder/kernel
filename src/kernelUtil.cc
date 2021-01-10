#include <kernelUtil.hh>
KernelInfo kernelInfo;
PageTableManager pageTableManager = 0;
void PrepareMemory(BootInfo *bootinfo)
{
	u64 mMapEntries = bootinfo->mMapSize / bootinfo->mMapDescSize;

	globalAllocator.ReadEFIMemoryMap(bootinfo->mMap, bootinfo->mMapSize, bootinfo->mMapDescSize);

	u64 kernelSize = (u64)&_KernelEnd - (u64)&_KernelStart;
	u64 kernelPages = (kernelSize >> 12) + 1;

	globalAllocator.LockPages(&_KernelStart, kernelPages);

	PageTable *PML4 = (PageTable *)globalAllocator.requestPage();
	memset(PML4, 0, 0x1000);

	pageTableManager = PageTableManager{PML4};

	for (u64 t = 0; t < GetMemorySize(bootinfo->mMap, mMapEntries, bootinfo->mMapDescSize); t += 0x1000)
	{
		pageTableManager.MapMemory((void *)t, (void *)t);
	}

	u64 fbBase = (u64)bootinfo->framebuffer->BaseAddress;
	u64 fbSize = (u64)bootinfo->framebuffer->BufferSize;
	globalAllocator.LockPages((void *)fbBase, fbSize / 4096 + 1);
	for (u64 t = fbBase; t < fbBase + fbSize; t += 0x1000)
	{
		pageTableManager.MapMemory((void *)t, (void *)t);
	}

	asm("mov %0, %%cr3"
			:
			: "r"(PML4));

	kernelInfo.pageTableManager = &pageTableManager;
}

KernelInfo InitializeKernel(BootInfo *bootinfo)
{
	PrepareMemory(bootinfo);
	memset(bootinfo->framebuffer->BaseAddress, 0, bootinfo->framebuffer->BufferSize);

		return kernelInfo;
}