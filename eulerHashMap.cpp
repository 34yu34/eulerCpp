#include "hash_map.h"
#include <iostream>
#include <stdint.h>

using namespace std;

int main(int argc, char const *argv[])
{
    Hash_Map<uint64_t, uint64_t> map(100);

    map.push(345, 1).push(234, 456);
    map[12] = 9;
    cout << map;
    return 0;
}
