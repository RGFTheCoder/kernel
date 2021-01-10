#pragma once

#include <types/ints.hh>
#include <EFIMemory.hh>

u64 GetMemorySize(EFI_MEMORY_DESCRIPTOR *mMap, u64 mMapEntries, u64 mMapDescSize);