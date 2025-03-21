#include <iostream>
#include <cmath>
#include <stdint.h>

unsigned int CountBits(uint8_t n)
{
    // count bits of each 2-bit chunk
    n = n - ((n >> 1) & 0x55);
    // count bits of each 4-bit chunk
    n = (n & 0x33) + ((n >> 2) & 0x33);
    // count bits of each 8-bit chunk
    n = n + (n >> 4);
    // mask out junk
    n &= 0x0F;
    return n;
}

int main(int argc, char *argv[])
{
    std::cout << CountBits(173) << std::endl;
    return 0;
}
