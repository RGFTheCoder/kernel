#pragma once
#include <paging/paging.hh>

class PageTableManager
{
public:
	PageTableManager(PageTable *PML4Address) : PML4(PML4Address){};
	PageTable *PML4;
	void MapMemory(void *virtualMemory, void *physicalMemory);
};