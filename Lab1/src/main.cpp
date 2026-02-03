#include "stm32f103x6.h"

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

void setSystemClockRate()
{
    // Enable HSI
    RCC->CR |= RCC_CR_HSION;  
    while (!(RCC->CR & RCC_CR_HSIRDY));  

    // Set multiplier of PLL as 6, so wer're getting SYSCLK = 8 (HSI) / 2 (HSI->PLL) * 6 (multiplier) = 24 MHz here
    RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL);
    RCC->CFGR |= RCC_CFGR_PLLMULL6; 

    // Enable PLL
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));

    // Set HPRE prescaler to DIV4 to get HCLK = 6 MHz
    RCC->CFGR &= ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2);
    RCC->CFGR |= RCC_CFGR_HPRE_DIV4 | RCC_CFGR_PPRE1_DIV2;

    // Set PLL as system clock source
    RCC->CFGR |= RCC_CFGR_SW_PLL; 
    while (!(RCC->CFGR & RCC_CFGR_SWS_PLL));

    // Set Latency 0 mode to memory
    FLASH->ACR &= ~FLASH_ACR_LATENCY;
    FLASH->ACR |= FLASH_ACR_LATENCY_0;
}

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

const int starting_pin = 3;
const int total_pins = 10;

bool areLightsActive = false;

void setBit(volatile uint32_t& number, uint32_t bit, bool value)
{
    if (value) number |= bit;
    else number &= ~bit;
}

int getPin(int i)
{
    int result = i + starting_pin;
    if (result >= 7) result += 2;
    return result;
}

void updateLightsState()
{
    constexpr int mid_point = total_pins / 2;

    bool isButtonPressed = !(GPIOA->IDR & GPIO_IDR_IDR1);
    bool value = isButtonPressed && areLightsActive;

    for (int i = 0; i < total_pins; i++) {
        if (i == mid_point && areLightsActive) value = !value;
        int pin = getPin(i);
        setBit(GPIOA->ODR, GPIO_ODR_ODRpin(pin), value);
    }
}

extern "C" void EXTI1_IRQHandler() 
{
    if (EXTI->PR & EXTI_PR_PR1) {
        updateLightsState();
        EXTI->PR |= EXTI_PR_PR1;
    }
}

extern "C" void TIM2_IRQHandler() 
{
    areLightsActive = !areLightsActive;
    updateLightsState();
    TIM2->SR &= ~TIM_SR_UIF;
}

constexpr int N = 6;
constexpr int N1 = N - 1;
constexpr double T1 = (double)N / 10;

// T1 = clock / (PSC * ARR)
// ARR = 1000
// PSC = clock / (T1 * ARR)

constexpr int clock = N * 1000000;
constexpr int ARR = 1000;

constexpr int getPsc(double frequency) 
{
    return clock / (frequency * ARR);
}

int main()
{
    setSystemClockRate();

    SysTick->LOAD  = SystemCoreClock / 1000 - 1;
    SysTick->VAL   = 0;
    SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | 
                     SysTick_CTRL_TICKINT_Msk   | 
                     SysTick_CTRL_ENABLE_Msk;

    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    for (int i = 0; i < total_pins; i++) {
        int pin = getPin(i);
        GPIOA_CRX(pin) |= GPIO_CRX_MODEpin_0(pin);
        GPIOA_CRX(pin) &= ~GPIO_CRX_CNFpin_0(pin);
    }

    updateLightsState();

    // Button
    GPIOA->CRL &= ~GPIO_CRL_CNF1;
    GPIOA->CRL |= GPIO_CRL_CNF1_1;
    GPIOA->ODR |= GPIO_ODR_ODR1;

    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI1_PA;
    EXTI->IMR |= EXTI_IMR_IM1; // Enable callback
    EXTI->FTSR |= EXTI_FTSR_FT1; // Callback on press
    EXTI->RTSR |= EXTI_RTSR_RT1; // Callback on release
    NVIC_EnableIRQ(EXTI1_IRQn);

    // Timer
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    TIM2->PSC = getPsc(T1) - 1;
    TIM2->ARR = ARR - 1;
    TIM2->DIER |= TIM_DIER_UIE; // Enable callback
    TIM2->CR1 |= TIM_CR1_CEN;
    NVIC_EnableIRQ(TIM2_IRQn);

    // PWM
    GPIOA->CRL = GPIOA->CRL & ~(GPIO_CRL_MODE7 | GPIO_CRL_CNF7);
    GPIOA->CRL = GPIOA->CRL | (GPIO_CRL_MODE7_0 | GPIO_CRL_CNF7_1);
    GPIOA->CRH = GPIOA->CRH & ~(GPIO_CRH_MODE8 | GPIO_CRH_CNF8);
    GPIOA->CRH = GPIOA->CRH | (GPIO_CRH_MODE8_0 | GPIO_CRH_CNF8_1);
    AFIO->MAPR |= AFIO_MAPR_TIM1_REMAP_PARTIALREMAP; // Remap to have pins 7 and 8

    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    TIM1->PSC = getPsc(0.5) - 1;
    TIM1->ARR = ARR - 1;
    TIM1->CCMR1 |= (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2); // This enables mode 1 to have value alternating 0->CCR1->ARR
    TIM1->CCR1 = ARR / 2;
    TIM1->BDTR |= TIM_BDTR_MOE; // Enable PWM output
    TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC1NE | TIM_CCER_CC1NP; // Set normal output, complementary output, invert complementary output
    TIM1->CR1 |= TIM_CR1_CEN; // Enable timer

    while (true)
    {
    }
    
    return 0;
}