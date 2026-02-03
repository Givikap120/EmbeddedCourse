#pragma once
#include <cstdint>

enum class MODE {
    Input = 0b00,
    Output_10MHz = 0b01,
    Output_2MHz = 0b10,
    Output_50MHz = 0b11
};

enum class CONFIGURATION {
    Analog = 0b00,
    FloatingInput = 0b01,
    InputPullUpDown = 0b10,
    OutputPushPull = 0b00,
    OutputOpenDrain = 0b01,
    AlternateFunctionPushPull = 0b10,
    AlternateFunctionOpenDrain = 0b11
};

void GPIO_SetMode(int pin, MODE mode);
void GPIO_SetConfiguration(int pin, CONFIGURATION cnf);
void GPIO_SetOutputValue(int pin, bool value);

uint32_t GPIO_ODR_ODRpin(int pin);