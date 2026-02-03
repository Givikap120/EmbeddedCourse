#include "ClockRateHandler.h"

#include "stm32f103x6.h"

void setSystemClockRate()
{
    // Enable HSI
    RCC->CR |= RCC_CR_HSION;  
    while (!(RCC->CR & RCC_CR_HSIRDY));  

    // Set multiplier of PLL, so wer're getting SYSCLK = 8 (HSI) / 2 (HSI->PLL) * PLL_multiplier = 4 * PLL_multiplier
    RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL);
    RCC->CFGR |= RCC_CFGR_PLLMULL6; // RCC_CFGR_PLLMULL6

    // Enable PLL
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));

    RCC->CFGR &= ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2);
    RCC->CFGR |= RCC_CFGR_HPRE_DIV4 | RCC_CFGR_PPRE1_DIV2;

    // Set PLL as system clock source
    RCC->CFGR |= RCC_CFGR_SW_PLL; 
    while (!(RCC->CFGR & RCC_CFGR_SWS_PLL));

    // Set Latency 0 mode to memory
    FLASH->ACR &= ~FLASH_ACR_LATENCY;
    FLASH->ACR |= FLASH_ACR_LATENCY_0;
}