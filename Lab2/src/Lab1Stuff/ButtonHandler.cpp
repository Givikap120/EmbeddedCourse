#include "ButtonHandler.h"

#include "stm32f103x6.h"
#include "Lights.h"

extern "C" void EXTI1_IRQHandler() 
{
    if (EXTI->PR & EXTI_PR_PR1) {
        updateLightsState();
        EXTI->PR |= EXTI_PR_PR1;
    }
}

void configureButton()
{
    GPIOA->CRL &= ~GPIO_CRL_CNF1;
    GPIOA->CRL |= GPIO_CRL_CNF1_1;
    GPIOA->ODR |= GPIO_ODR_ODR1;

    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI1_PA;
    EXTI->IMR |= EXTI_IMR_IM1; // Enable callback
    EXTI->FTSR |= EXTI_FTSR_FT1; // Callback on press
    EXTI->RTSR |= EXTI_RTSR_RT1; // Callback on release
    NVIC_EnableIRQ(EXTI1_IRQn);
}