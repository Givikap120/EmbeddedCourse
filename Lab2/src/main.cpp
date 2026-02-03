#include "stm32f103x6.h"

#include "Lab1Stuff/IncludeAll.h"

#include "Adc.h"
#include "Usart.h"

int main()
{
    setSystemClockRate();
    
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    configureDelay();
    configureLights();
    configureTimer();
    configurePWM();

    configureADC();
    configureUsart();

    while (true)
    {
        delay(500);
        usart1SendMessage("Current ADC value = " + std::to_string(ADC1->DR) + "\r\n");
    }
    
    return 0;
}