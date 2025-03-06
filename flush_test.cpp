#include <iostream>
#include <x86intrin.h>

int main() {
    volatile int data = 42;
    // Test CLFLUSH
    _mm_clflush((void*)&data);
    // Test MFENCE
    _mm_mfence();
    // Test LFENCE
    _mm_lfence();
    // Test SFENCE
    _mm_sfence();
    std::cout << "Flush/Fence test completed!" << std::endl;
    return 0;
}
