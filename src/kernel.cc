#include <kernelUtil.hh>

extern "C" void _start(BootInfo *bootinfo)
{

	KernelInfo kernelInfo = InitializeKernel(bootinfo);
	PageTableManager *pageTableManager = kernelInfo.pageTableManager;

	globalRenderer->print("Kernel Initialized Successfully\n\r");

	// Previous line won't print if next included
	asm("int $0x0e");

	while (true)
		;
}
