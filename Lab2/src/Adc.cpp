#include "Adc.h"

#include "stm32f103x6.h"
#include "Lab1Stuff/GpioHandler.h"
#include "Lab1Stuff/Utils.h"
#include "Usart.h"

// extern "C" void ADC1_2_IRQHandler() 
// {
//     if (ADC1->SR & ADC_SR_EOS) 
//         ADC1->SR &= ~ADC_SR_EOS;
// }

void configureADC()
{
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    GPIO_SetConfiguration(0, CONFIGURATION::Analog);

    ADC1->SQR3 = 0; // PA0
    uint32_t speed = 0b111;
    ADC1->SMPR2 = (ADC1->SMPR2 & ~ADC_SMPR2_SMP0_Msk) | (speed << ADC_SMPR2_SMP0_Pos);

    ADC1->SR &= ~ADC_SR_EOS; // Clear EOS flag
    // ADC1->CR1 |= ADC_CR1_EOSIE; // Enable EOS interrupt
    ADC1->CR2 |= ADC_CR2_ADON; // Enable ADC
    ADC1->CR2 |= ADC_CR2_CONT;
    ADC1->CR2 |= ADC_CR2_ADON; // Start conversion

    // NVIC_EnableIRQ(ADC1_2_IRQn); // Enable interrupt
}