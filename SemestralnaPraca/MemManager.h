#pragma once
#include <iostream>
#include <cstring>

class MemoryManager {
public:
    MemoryManager(size_t size) {
        memory = new char[size];
        size = size;
        next = memory;
    }

    ~MemoryManager() {
        delete[] memory;
    }

    void* allocate(size_t size) {
        void* ptr = nullptr;

        if (next + size <= memory + size) {
            ptr = next;
            next += size;
        }

        return ptr;
    }

    void deallocate(void* ptr, size_t size) {
        if (ptr >= memory && ptr < memory + size) {
            std::memset(ptr, 0, size);

            if (ptr == next - size) {
                next -= size;
            }
        }
    }

private:
    char* memory;
    char* next;
    size_t size;
};

