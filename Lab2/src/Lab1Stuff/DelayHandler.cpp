#include "DelayHandler.h"

#include "stm32f103x6.h"
#include "Utils.h"

volatile int time = 0;
extern "C" void SysTick_Handler()
{
    ++time;
}

void delay(int delay) 
{
    int target = time + delay;
    while (time < target) {}
}

void configureDelay()
{
    SysTick->LOAD  = clock / 3 / 1000 - 1;
    SysTick->VAL   = 0;
    SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | 
                     SysTick_CTRL_TICKINT_Msk   | 
                     SysTick_CTRL_ENABLE_Msk;
}