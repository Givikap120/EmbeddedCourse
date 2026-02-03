#include "GpioHandler.h"

#include "stm32f103x6.h"

uint32_t GPIO_CRX_MODEpin_0(int pin)
{
    if (pin <= 7) {
        return (1 << (pin * 4));  // MODE bits for PA1 - PA7
    } else {
        return (1 << ((pin - 8) * 4));  // MODE bits PA8 - PA10
    }
}

uint32_t GPIO_CRX_CNFpin_0(int pin)
{
    if (pin <= 7) {
        return (1 << ((pin * 4) + 2));  // Clear CNF bits for PA1 - PA7
    } else {
        return (1 << (((pin - 8) * 4) + 2));  // Clear CNF bits for PA8 - PA10
    }
}

volatile uint32_t& GPIOA_CRX(int pin)
{
    if (pin <= 7) {
        return GPIOA->CRL;
    } else {
        return GPIOA->CRH;
    }
}

uint32_t GPIO_ODR_ODRpin(int pin)
{
    return (1 << pin);
}

void GPIO_SetMode(int pin, MODE mode)
{
    volatile uint32_t& CRX = GPIOA_CRX(pin);
    int shift = (pin % 8) * 4; // Determine bit shift position

    CRX &= ~(0b11 << shift); // Clear MODE bits
    CRX |= (static_cast<uint32_t>(mode) << shift); // Set new MODE bits
}

void GPIO_SetConfiguration(int pin, CONFIGURATION cnf)
{
    volatile uint32_t& CRX = GPIOA_CRX(pin);
    int shift = (pin % 8) * 4 + 2; // CNF bits are in bits 2 and 3 of each 4-bit block

    CRX &= ~(0b11 << shift); // Clear CNF bits
    CRX |= (static_cast<uint32_t>(cnf) << shift); // Set new CNF bits
}

void GPIO_SetOutputValue(int pin, bool value)
{
    if (value)
        GPIOA->ODR |= GPIO_ODR_ODRpin(pin);  // Set bit (output HIGH)
    else
        GPIOA->ODR &= ~GPIO_ODR_ODRpin(pin); // Clear bit (output LOW)
}