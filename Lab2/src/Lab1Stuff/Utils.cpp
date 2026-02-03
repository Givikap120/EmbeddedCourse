#include "Utils.h"

void setBit(volatile uint32_t& number, uint32_t bit, bool value)
{
    if (value) number |= bit;
    else number &= ~bit;
}