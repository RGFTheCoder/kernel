#pragma once

#include <types/ints.hh>
#include <EFIMemory.hh>

u64 GetMemorySize(EFI_MEMORY_DESCRIPTOR *mMap, u64 mMapEntries, u64 mMapDescSize);

void memset(void *start, u8 value, size_t size);