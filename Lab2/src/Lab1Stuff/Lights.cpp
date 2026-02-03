#include "Lights.h"

#include "stm32f103x6.h"
#include "Utils.h"
#include "GpioHandler.h"

constexpr int starting_pin = 15;
constexpr int total_pins = 1;

bool areLightsActive = false;

void toggleLights()
{
    areLightsActive = !areLightsActive;
}

int getPin(int i)
{
    // int result = i + starting_pin;
    // if (result >= 7) result += 2;
    // return result;
    return starting_pin;
}

void updateLightsState()
{
    // constexpr int mid_point = total_pins / 2;

    // bool isButtonPressed = !(GPIOA->IDR & GPIO_IDR_IDR1);
    // bool value = isButtonPressed && areLightsActive;

    bool value = areLightsActive;

    for (int i = 0; i < total_pins; i++) {
        //if (i == mid_point && areLightsActive) value = !value;
        int pin = getPin(i);
        GPIO_SetOutputValue(pin, value);
    }
}

void configureLights()
{
    GPIO_SetMode(control_light_pin, MODE::Output_2MHz);

    for (int i = 0; i < total_pins; i++) {
        int pin = getPin(i);
        GPIO_SetMode(pin, MODE::Output_2MHz);
        GPIO_SetConfiguration(pin, CONFIGURATION::OutputPushPull);
    }

    updateLightsState();
}
