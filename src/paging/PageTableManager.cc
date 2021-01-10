#include <paging/PageTableManager.hh>
#include <paging/PageMapIndexer.hh>
#include <paging/PageFrameAllocator.hh>
#include <types/ints.hh>
#include <Memory.hh>

void PageTableManager::MapMemory(void *virtualMemory, void *physicalMemory)
{
	PageMapIndexer indexer{(u64)virtualMemory};
	PageDirectoryEntry PDE;

	PDE = PML4->entries[indexer.PDP_i];
	PageTable *PDP;
	if (!PDE.present)
	{
		PDP = (PageTable *)globalAllocator.requestPage();
		memset(PDP, 0, 0x1000);
		PDE.address = (u64)PDP >> 12;
		PDE.present = true;
		PDE.readWrite = true;
		PML4->entries[indexer.PDP_i] = PDE;
	}
	else
	{
		PDP = (PageTable *)((u64)PDE.address << 12);
	}

	PDE = PDP->entries[indexer.PD_i];
	PageTable *PD;
	if (!PDE.present)
	{
		PD = (PageTable *)globalAllocator.requestPage();
		memset(PD, 0, 0x1000);
		PDE.address = (u64)PD >> 12;
		PDE.present = true;
		PDE.readWrite = true;
		PDP->entries[indexer.PD_i] = PDE;
	}
	else
	{
		PD = (PageTable *)((u64)PDE.address << 12);
	}

	PDE = PD->entries[indexer.PT_i];
	PageTable *PT;
	if (!PDE.present)
	{
		PT = (PageTable *)globalAllocator.requestPage();
		memset(PT, 0, 0x1000);
		PDE.address = (u64)PT >> 12;
		PDE.present = true;
		PDE.readWrite = true;
		PD->entries[indexer.PT_i] = PDE;
	}
	else
	{
		PT = (PageTable *)((u64)PDE.address << 12);
	}

	PDE = PT->entries[indexer.P_i];
	PDE.address = (u64)physicalMemory >> 12;
	PDE.present = true;
	PDE.readWrite = true;
	PT->entries[indexer.P_i] = PDE;
}