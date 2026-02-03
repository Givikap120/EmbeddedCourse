#include "PWMHandler.h"

#include "stm32f103x6.h"
#include "Utils.h"

void configurePWM()
{
    GPIOA->CRL = GPIOA->CRL & ~(GPIO_CRL_MODE7 | GPIO_CRL_CNF7);
    GPIOA->CRL = GPIOA->CRL | (GPIO_CRL_MODE7_0 | GPIO_CRL_CNF7_1);
    GPIOA->CRH = GPIOA->CRH & ~(GPIO_CRH_MODE8 | GPIO_CRH_CNF8);
    GPIOA->CRH = GPIOA->CRH | (GPIO_CRH_MODE8_0 | GPIO_CRH_CNF8_1);
    AFIO->MAPR |= AFIO_MAPR_TIM1_REMAP_PARTIALREMAP; // Remap to have pins 7 and 8

    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    TIM1->PSC = getPscFromFrequency(0.5) - 1;
    TIM1->ARR = ARR - 1;
    TIM1->CCMR1 |= (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2); // This enables mode 1 to have value alternating 0->CCR1->ARR
    TIM1->CCR1 = ARR / 2;
    TIM1->BDTR |= TIM_BDTR_MOE; // Enable PWM output
    TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC1NE | TIM_CCER_CC1NP; // Set normal output, complementary output, invert complementary output
    TIM1->CR1 |= TIM_CR1_CEN; // Enable timer
}