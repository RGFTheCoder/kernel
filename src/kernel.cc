#include <types/ints.hh>
#include <lowlevel/Framebuffer.hh>
#include <lowlevel/PSF1.hh>
#include <BasicRenderer.hh>
#include <EFIMemory.hh>
#include <cstr.hh>

struct BootInfo
{
	Framebuffer *framebuffer;
	PSF1_FONT *font;
	EFI_MEMORY_DESCRIPTOR *mMap;
	ul mMapSize;
	ul mMapDescriptorSize;
};

extern "C" void _start(BootInfo *p_bootinfo)
{
	BasicRenderer out{p_bootinfo->framebuffer, p_bootinfo->font};

	out.cursorPosition.y = 16;

	u64 mMapEntries = p_bootinfo->mMapSize / p_bootinfo->mMapDescriptorSize;

	for (int i = 0; i < mMapEntries; ++i)
	{
		EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)((u64)p_bootinfo->mMap + (i * p_bootinfo->mMapDescriptorSize));
		out.color.g = 0xff;
		out.print(EFI_MEMORY_TYPE_STRINGS[desc->type]);
		out.color.g = 0;
		out.print(" ");
		out.print(toString(desc->numPages * (4096 / 1024)));
		out.color.g = 0xff;
		out.print(" KB");
		out.print("\n\r");
	}
}
