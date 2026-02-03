#pragma once
#include <cstdint>

constexpr int N = 6;
constexpr int N1 = N - 1;
constexpr double T1 = (double)N / 10;

// T1 = clock / (PSC * ARR)
// ARR = 1000
// PSC = clock / (T1 * ARR)

constexpr int clock = 6 * 1000000;
constexpr int ARR = 1000;

constexpr int getPscFromFrequency(double frequency) 
{
    return clock / (frequency * ARR);
}

constexpr int getPscFromDelay(int delay) 
{
    return delay * clock / (1000 * ARR);
}

void setBit(volatile uint32_t& number, uint32_t bit, bool value);
