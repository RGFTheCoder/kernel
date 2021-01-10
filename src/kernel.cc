#include <kernelUtil.hh>

extern "C" void _start(BootInfo *bootinfo)
{
	BasicRenderer out{bootinfo->framebuffer, bootinfo->font};
	out.print("Kernel Initializing\n\r");

	KernelInfo kernelInfo = InitializeKernel(bootinfo);
	PageTableManager *pageTableManager = kernelInfo.pageTableManager;

	out.print("Kernel Initialized Successfully\n\r");

	while (true)
	{
	}
}
