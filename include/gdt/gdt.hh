#pragma once
#include <types/ints.hh>

struct GDTDescriptor
{
	u16 size;
	u64 offset;
} __attribute__((packed));

struct GDTEntry
{
	u16 limit0;
	u16 base0;
	u8 base1;
	u8 accessByte;
	u8 limit1Flags;
	u8 base2;
} __attribute__((packed));

struct GDT
{
	GDTEntry kernelNull;
	GDTEntry kernelCode;
	GDTEntry kernelData;
	GDTEntry userNull;
	GDTEntry userCode;
	GDTEntry userData;
} __attribute__((packed)) __attribute__((aligned(0x1000)));

extern GDT defaultGDT;

extern "C" void LoadGDT(GDTDescriptor *gdtDescriptor);