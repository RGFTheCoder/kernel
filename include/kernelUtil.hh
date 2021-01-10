#pragma once
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
#include <gdt/gdt.hh>

struct BootInfo
{
	Framebuffer *framebuffer;
	PSF1_FONT *font;
	EFI_MEMORY_DESCRIPTOR *mMap;
	ul mMapSize;
	ul mMapDescSize;
};

extern u64 _KernelStart;
extern u64 _KernelEnd;

struct KernelInfo
{
	PageTableManager *pageTableManager;
};

KernelInfo InitializeKernel(BootInfo *bootinfo);