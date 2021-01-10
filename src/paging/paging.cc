#include <paging/paging.hh>

void PageDirectoryEntry::SetFlag(PT_FLAG flag, bool enabled)
{
	u64 bitSelector = (u64)1 << (u64)flag;
	value &= ~bitSelector;
	if (enabled)
		value |= bitSelector;
}
bool PageDirectoryEntry::GetFlag(PT_FLAG flag)
{
	u64 bitSelector = (u64)1 << (u64)flag;
	return value & bitSelector > 0;
}
void PageDirectoryEntry::SetAddress(u64 addr)
{
	u64 address = (u64)addr & 0x000000ffffffffff;
	value &= 0xfff0000000000fff;
	value |= (address << 12);
}
u64 PageDirectoryEntry::GetAddress()
{
	return ((value & 0x000ffffffffff000) >> 12);
}