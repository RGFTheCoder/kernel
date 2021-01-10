#pragma once
#include <types/ints.hh>

struct EFI_MEMORY_DESCRIPTOR
{
	u32 type;
	void *physAddr;
	void *virtAddr;
	u64 numPages;
	u64 attribs;
};

extern const char *EFI_MEMORY_TYPE_STRINGS[];