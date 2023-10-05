#pragma once

void* operator new (size_t _sSize);

void* operator new[](size_t _sSize);

void operator delete(void* _ptrDelete);

void operator delete[](void* _ptrDeleteArr);

class MemorySubsystem {
private:
	friend void* operator new(size_t _sSize);

	friend void* operator new[](size_t _sSize);

	friend void operator delete(void* _ptrDelete);

	friend void operator delete[](void* _ptrDeleteArr);

public:
	MemorySubsystem() {}

	~MemorySubsystem() {}

	void Init();

	void Shutdown();
};