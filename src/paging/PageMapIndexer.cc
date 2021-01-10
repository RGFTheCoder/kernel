#include <paging/PageMapIndexer.hh>

PageMapIndexer::PageMapIndexer(u64 virtualAddress)
{
	virtualAddress >>= 12;
	P_i = virtualAddress & 0x1ff;
	virtualAddress >>= 9;
	PT_i = virtualAddress & 0x1ff;
	virtualAddress >>= 9;
	PD_i = virtualAddress & 0x1ff;
	virtualAddress >>= 9;
	PDP_i = virtualAddress & 0x1ff;
}