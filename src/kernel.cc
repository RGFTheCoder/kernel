#include <types/ints.hh>
#include <lowlevel/Framebuffer.hh>
#include <lowlevel/PSF1.hh>
#include <BasicRenderer.hh>
#include <EFIMemory.hh>
#include <cstr.hh>
#include <Memory.hh>
#include <Bitmap.hh>

struct BootInfo
{
	Framebuffer *framebuffer;
	PSF1_FONT *font;
	EFI_MEMORY_DESCRIPTOR *mMap;
	ul mMapSize;
	ul mMapDescSize;
};

u8 testbuffer[20];

extern "C" void _start(BootInfo *p_bootinfo)
{
	BasicRenderer out{p_bootinfo->framebuffer, p_bootinfo->font};

	out.cursorPosition.y = 16;

	u64 mMapEntries = p_bootinfo->mMapSize / p_bootinfo->mMapDescSize;

	Bitmap testBitmap;
	testBitmap.Buffer = testbuffer;
	testBitmap.set(0, false);
	testBitmap.set(1, true);
	testBitmap.set(2, false);
	testBitmap.set(3, false);
	testBitmap.set(4, true);

	for (int i = 0; i < 20; i++)
	{
		out.print(testBitmap[i] ? "true\n\r" : "false\n\r");
	}
}
