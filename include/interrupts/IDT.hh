#pragma once
#include <types/ints.hh>

enum class IDT_TA : u8
{
	InterruptGate = 0b10001110,
	CallGate = 0b10001100,
	TrapGate = 0b10001111
};

struct IDTDescEntry
{
	u16 offset0;
	u16 selector;
	u8 ist;
	u8 typeAttr;
	u16 offset1;
	u32 offset2;
	u32 ignore;
	void SetOffset(u64 offset);
	u64 GetOffset();
};

struct IDTR
{
	u16 limit;
	u64 offset;
} __attribute__((packed));