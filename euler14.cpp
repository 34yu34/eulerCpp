/*
The following iterative sequence is defined for the set of positive integers:

n → n/2 (n is even)
n → 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:

13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one million.
*/

#include <iostream>
#include <stdint.h>
#include "array.h"

using namespace std;
uint32_t find_collatz(uint32_t num, Array<uint32_t> & data)
{
    //cout << num << endl;
    uint32_t new_num = num % 2 != 0 ? 3 * num + 1 : num / 2;
    if (data[new_num] != 0)
    {
        data[num] = data[new_num] + 1;
    } 
    else
    {
        data[num] = find_collatz(new_num, data) + 1;
    }
    return data[num];
}

int main(int argc, const char** argv) {
    Array<uint32_t> seq((uint64_t)100000000000, (uint32_t)0);
    seq[0] = 1;
    seq[1] = 1;
    for (uint32_t i = 1000000; i > 0; --i)
    {
        find_collatz(i, seq);
    }
    cout << seq << endl;
    return 0;
}