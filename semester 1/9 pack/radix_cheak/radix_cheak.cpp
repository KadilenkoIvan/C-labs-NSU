#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cassert>

#ifdef _WINDOWS
typedef unsigned long uint32_t;
typedef unsigned char uint8_t;
#else
#include <stdint.h>
#endif
using namespace std;

static void radix(int byte, const unsigned N, const uint32_t* source, uint32_t* dest)
{
    unsigned count[256];
    unsigned index[256];
    memset(count, 0, sizeof(count));

    for (unsigned i = 0; i < N; ++i)
        count[((source[i]) >> (byte * 8)) & 0xff]++;

    index[0] = 0;
    for (unsigned i = 1; i < 256; ++i)
        index[i] = index[i - 1] + count[i - 1];

    for (unsigned i = 0; i < N; ++i)
        dest[index[((source[i]) >> (byte * 8)) & 0xff]++] = source[i];
}

void radixsort(uint32_t* source, const unsigned N)
{
    uint32_t* temp = new uint32_t[N];
    radix(0, N, source, temp);
    radix(1, N, temp, source);
    radix(2, N, source, temp);
    radix(3, N, temp, source);
    delete[] temp;
}

static void make_random(uint32_t* data, const unsigned N)
{
    for (unsigned i = 0; i < N; ++i)
    {
        srand((unsigned)time(NULL));
        int r = 1 + rand() % 100 - 1;
        data[i] = r;
    }
}

static void check_order(const uint32_t* data, unsigned N)
{
    for (--N; N > 0; --N, ++data)
        assert(data[0] <= data[1]);
}

int main()
{
    uint32_t data[15] = {7,3,13,789,13,243,56,13,6546,1,0,324,13,989,234};
    for (int i = 0; i < 15; ++i)
    {
        cout << data[i] << " ";
    }
    cout << "\n";
    radixsort(data, 15);
    for (int i = 0; i < 15; ++i)
    {
        cout << data[i] << " ";
    }
    cout << "\n";
    check_order(data, 15);
    return 0;
}