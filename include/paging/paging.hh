#pragma once
#include <types/ints.hh>

struct PageDirectoryEntry
{
	bool present : 1;
	bool readWrite : 1;
	bool userSuper : 1;
	bool writeThrough : 1;
	bool cacheDisabled : 1;
	bool accessed : 1;
	bool ignore0 : 1;
	bool largerPages : 1;
	bool ignore1 : 1;
	u8 available : 3;
	u64 address : 52;
};

struct PageTable
{
	PageDirectoryEntry entries[512];
} __attribute__((aligned(0x1000)));