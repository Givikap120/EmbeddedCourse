#include "Usart.h"

#include "stm32f103x6.h"
#include "Lab1Stuff/GpioHandler.h"
#include "Lab1Stuff/DelayHandler.h"
#include "Lab1Stuff/Utils.h"
#include "ConsoleCommandHandler.h"

extern "C" void USART2_IRQHandler() 
{
    static std::string cmd;
    
    if (USART2->SR & USART_SR_RXNE)
    {
        char received = USART2->DR;

        if (received == '\n') 
        {
            std::string result = executeCommand(cmd);
            usart2SendMessage(result);
            cmd.clear();
        } 
        else 
        {
            cmd.push_back(received);
        }
    }

    USART2->SR &= ~USART_SR_RXNE;
}

void configureUsart()
{
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    
    USART1->BRR = clock / 10000;
    USART1->CR1 |= (USART_CR1_UE | USART_CR1_TE);

    USART2->BRR = clock / 20000;
    USART2->CR1 |= (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE);
    
    NVIC_EnableIRQ(USART2_IRQn);

    usart2SendMessage("Console initialized\r\n");
    usart1SendMessage("Logger initialized\r\n");
}

void usart1SendMessage(const std::string& message)
{
    for (auto byte : message)
    {
        while ((USART1->SR & USART_SR_TC) == 0)
        {}

        USART1->DR = byte;
    }
}

void usart2SendMessage(const std::string& message)
{
    for (auto byte : message)
    {
        while ((USART2->SR & USART_SR_TC) == 0)
        {}

        USART2->DR = byte;
    }
}