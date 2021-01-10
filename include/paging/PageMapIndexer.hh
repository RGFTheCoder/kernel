#pragma once
#include <types/ints.hh>

class PageMapIndexer
{
public:
	PageMapIndexer(u64 virtualAddress);
	u64 PDP_i;
	u64 PD_i;
	u64 PT_i;
	u64 P_i;
};