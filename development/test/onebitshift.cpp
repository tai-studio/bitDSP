#include <bitset>
#include <string>
#include <iostream>
#include <climits>

typedef std::bitset<32> bit32;


inline bit32 shift(bit32 last, bit32 current, int amount) {
    return ((current >> amount) | (last << (32-amount)));
}


inline uint32_t shiftUInt(uint32_t last, uint32_t current, int amount) {
    return ((current >> amount) | (last << (32-amount)));
}

inline int32_t shiftSInt(int32_t last, int32_t current, int amount) {
    return ((current >> amount) | (last << (32-amount)));
}

int main() 
{
    bit32 allHigh(-1);       // 11111111111111111111111111111111
    
    // std::cout 
    //     << allHigh << '\n' 
    //     << (allHigh << 3) << '\n'
    //     << (allHigh >> 3) << '\n';

    
    // std::cout << "----------------------------------\n\n";
    
    // bit32 
    //     a_0("10110111011110111110111111011111"), 
    //     a_1("01001000100001000001000000100000");

    // std::cout << ((a_1 >> 1) | (a_0 >> 31)) << "\n";

    std::cout << "--------------- bit32 -------------------\n\n";
    
    bit32 
        b32_0("10110111011110111110111111011111"), 
        b32_1("01001000100001000001000000100000");

    for (int i = 0; i < 33; ++i)
    {
        std::cout << shift(b32_0, b32_1, i) << "\n";
    }

    std::cout << "--------------- uint32_t ---(unsigned)------\n\n";

    uint32_t 
        u32_0 = bit32("10110111011110111110111111011111").to_ulong(), 
        u32_1 = bit32("01001000100001000001000000100000").to_ulong();

    std::cout << bit32(u32_0) << "\t(" << u32_0 << ")\n";
    std::cout << bit32(u32_1) << "\t(" << u32_1 << ")\n";

    for (int i = 0; i < 33; ++i)
    {
        uint32_t u32_res = shiftUInt(u32_0, u32_1, i);
        std::cout << bit32(u32_res) << "\t(" << u32_res << ")\n";
    }

    std::cout << "--------------- int32_t ---(signed)---------\n\n";

    // left-shifts do not affect sign-bit (i.e. for negative numbers, it stays 1) 

    int32_t 
        s32_0 = bit32("10110111011110111110111111011111").to_ulong(), 
        s32_1 = bit32("01001000100001000001000000100000").to_ulong();

    std::cout << bit32(s32_0) << "\t(" << s32_0 << ")\n";
    std::cout << bit32(s32_1) << "\t(" << s32_1 << ")\n";
    
    for (int i = 0; i < 33; ++i)
    {
        int32_t s32_res = shiftSInt(s32_0, s32_1, i);
        std::cout << bit32(s32_res) << "\t(" << s32_res << ")\n";
    }
    
}