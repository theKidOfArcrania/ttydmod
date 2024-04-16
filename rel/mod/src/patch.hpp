#pragma once

#include <cstdint>
#include <dolphin/os.h>


namespace mod {

namespace patch {

void writeBranch(void *ptr, void *destination);

template<typename Func, typename Dest>
Func hookFunction(Func function, Dest destination)
{
	uint32_t *instructions = reinterpret_cast<uint32_t *>(function);

	uint32_t *trampoline = new uint32_t[2];
	// Original instruction
	trampoline[0] = instructions[0];
	// Branch to original function past hook
	writeBranch(&trampoline[1], &instructions[1]);

	// Write actual hook
	writeBranch(&instructions[0], reinterpret_cast<void *>(static_cast<Func>(destination)));

	// Make relocated instruction visible
	DCFlushRange(trampoline, sizeof(uint32_t));
	ICInvalidateRange(trampoline, sizeof(uint32_t));

	return reinterpret_cast<Func>(trampoline);
}

typedef void (*InstructionHookHandler)(OSContext *context, void *user);
void hookInstruction(void *location, InstructionHookHandler handler, void *user = nullptr);

}
}
