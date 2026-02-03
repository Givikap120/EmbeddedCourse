#include "TimerHandler.h"

#include "stm32f103x6.h"
#include "Lights.h"
#include "Utils.h"

extern "C" void TIM2_IRQHandler() 
{
    toggleLights();
    updateLightsState();
    TIM2->SR &= ~TIM_SR_UIF;
}

void configureTimer()
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    TIM2->PSC = getPscFromFrequency(T1) - 1;
    TIM2->ARR = ARR - 1;
    TIM2->DIER |= TIM_DIER_UIE; // Enable callback
    TIM2->CR1 |= TIM_CR1_CEN;
    NVIC_EnableIRQ(TIM2_IRQn);
}