#include <iostream>
#include <x86intrin.h>

int main() {
    volatile int data = 42;
    // Test CLFLUSH
    _mm_clflush((void*)&data); // CLFLUSH instruction
    // Test MFENCE
    _mm_mfence();       // MFENCE instruction
    // Test LFENCE
    _mm_lfence();       // LFENCE instruction
    // Test SFENCE
    _mm_sfence();       // SFENCE instruction
    std::cout << "Flush/Fence test completed!" << std::endl;
    return 0;
}
