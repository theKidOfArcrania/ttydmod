#include <platform.h>
#include <memory.h>

void *operator new(size_t size)
{
	return __memAlloc(HEAP_TYPE::HEAP_DEFAULT, (u32)size);
}
void *operator new[](size_t size)
{
	return __memAlloc(HEAP_TYPE::HEAP_DEFAULT, (u32)size);
}
void operator delete(void *ptr)
{
	return __memFree(HEAP_TYPE::HEAP_DEFAULT, ptr);
}
void operator delete[](void *ptr)
{
	return __memFree(HEAP_TYPE::HEAP_DEFAULT, ptr);
}
