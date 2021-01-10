#pragma once
#include <BasicRenderer.hh>

struct interrupt_frame;
__attribute__((interrupt)) void PageFault_handler(struct interrupt_frame *frame);