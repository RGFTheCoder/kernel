#include <interrupts/interrupts.hh>

__attribute__((interrupt)) void PageFault_handler(struct interrupt_frame *frame)
{
	globalRenderer->print("Page Fault Detected");
	while (true)
		;
}