#include <bitset>
#include <string>
#include <iostream>
#include <climits>

typedef std::bitset<32> bit32;

inline int32_t shiftSInt(int32_t last, int32_t current, int amount) {
    if (amount < 1)
    {
        return current;
    }
    if (amount >= 32)
    {
        return last;
    }

    return ((current >> amount) | (last << (32-amount)));
}

int main() 
{
    std::cout << "--------------- int32_t ---(signed)---------\n\n";

    // left-shifts do not affect sign-bit (i.e. for negative numbers, it stays 1) 

    int32_t 
        s32_0 = bit32("10110111011110111110111111011111").to_ulong(), 
        s32_1 = bit32("01001000100001000001000000100000").to_ulong();


    std::cout << "--------------- s32_0 ---------\n\n";
    std::cout << bit32(s32_0) << "\t(" << s32_0 << ")\n";

    std::cout << "--------------- s32_1 ---------\n\n";
    std::cout << bit32(s32_1) << "\t(" << s32_1 << ")\n";
    
    std::cout << "--------------- delaying by n bits s32_0 s32_1---------\n\n";

    for (int i = 0; i < 33; ++i)
    {
        int32_t s32_res = shiftSInt(s32_0, s32_1, i);
        std::cout << i << "\t" << bit32(s32_res) << "\t(" << s32_res << ")\n";
    }
    
}