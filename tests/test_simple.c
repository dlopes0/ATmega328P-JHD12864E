#include <inttypes.h>

#include "jhd12864e.h"

int main()
{
    while (1)
    {
        for (uint8_t i = 0; i < 64; i++)
        {
            write_operation(i);
        }
    }
}