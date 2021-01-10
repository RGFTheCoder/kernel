#include <gdt/gdt.hh>

GDT defaultGDT = {
		{0, 0, 0, 0x00, 0x00, 0}, // kernel null
		{0, 0, 0, 0x9a, 0xa0, 0}, // kernel code
		{0, 0, 0, 0x92, 0xa0, 0}, // kernel data
		{0, 0, 0, 0x00, 0x00, 0}, // user null
		{0, 0, 0, 0x9a, 0xa0, 0}, // user code
		{0, 0, 0, 0x92, 0xa0, 0}, // user data
};