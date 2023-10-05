
#include <HellfireControl/Core/Memory.hpp>

#include <HellfireControl/Core/Memory/BlockAllocator.hpp>
#include <HellfireControl/Core/Memory/StackAllocator.hpp>
#include <HellfireControl/Core/Memory/PoolAllocator.hpp>
#include <HellfireControl/Core/Memory/HeapAllocator.hpp>

void MemorySubsystem::Init() {

}

void MemorySubsystem::Shutdown() {

}

void* operator new(size_t _sSize) {
	
}

void* operator new[](size_t _sSize){
	
}

void operator delete(void* _ptrDelete) {

}

void operator delete[](void* _ptrDeleteArr) {

}
