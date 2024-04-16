#pragma once

#include <dolphin/os.h>

#define MOD_ARRAYSIZE(x) \
	(sizeof((x)) / sizeof((x)[0]))

#define MOD_CONCAT_IMPL(s1, s2) s1##s2
#define MOD_CONCAT(s1, s2) MOD_CONCAT_IMPL(s1, s2)
#define MOD_ANONYMOUS(str) MOD_CONCAT(str, __LINE__)

#define MOD_ASSERT(x) \
	do \
	{ \
		if (!(x)) \
		{ \
			OSPanic(__FILE__, __LINE__, "Mod assertion failed: %s\n", #x); \
		} \
	} \
	while(false)

namespace mod {
namespace util {

inline s64 GetTbRate()
{
	return *(s32 *)0x800000f8 / 4;
}

}
}
