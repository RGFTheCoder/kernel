#pragma once
#include <types/ints.hh>

enum class PT_FLAG
{
	present = 0,
	readWrite,
	userSuper,
	writeThrough,
	cacheDisabled,
	accessed,
	largerPages = 7,
	custom0 = 9,
	custom1,
	custom2,
	NX = 63
};

struct PageDirectoryEntry
{
	u64 value;
	void SetFlag(PT_FLAG flag, bool enabled);
	bool GetFlag(PT_FLAG flag);
	void SetAddress(u64 address);
	u64 GetAddress();
};

struct PageTable
{
	PageDirectoryEntry entries[512];
} __attribute__((aligned(0x1000)));