#include "ConsoleCommandHandler.h"

#include "stm32f103x6.h"
#include "Lab1Stuff/Lights.h"
#include "Lab1Stuff/GpioHandler.h"
#include "Lab1Stuff/Utils.h"

constexpr const char timerdelay_str[] = "timerdelay";
constexpr size_t timerdelay_length = sizeof(timerdelay_str) - 1;

constexpr const char pwmdelay_str[] = "pwmdelay";
constexpr size_t pwmdelay_length = sizeof(pwmdelay_str) - 1;

int parseArgument(const std::string& command, size_t offset)
{
    const char* valueStr = command.c_str() + offset + 1;
    char* endPtr;
    long delay = strtol(valueStr, &endPtr, 10);

    if (*endPtr != '\0' && *endPtr != '\r' && *endPtr != '\n')  
        return -1;

    return delay;
}

std::string executeCommand(std::string command)
{
    if (command == "enable")
    {
        enableLight();
        return "\r\nLight succesfully enabled\r\n";
    }
    if (command == "disable")
    {
        disableLight();
        return "\r\nLight succesfully disabled\r\n";
    }
    if (command.substr(0, timerdelay_length) == timerdelay_str)
    {
        int delay = parseArgument(command, timerdelay_length);
        if (delay == -1) return "\r\nInvalid delay value\r\n";

        setTimerDelay(delay);
        return "\r\nTimer delay was set to " + std::to_string(delay) + "\r\n";
    }
    if (command.substr(0, pwmdelay_length) == pwmdelay_str)
    {
        int delay = parseArgument(command, pwmdelay_length);
        if (delay == -1) return "\r\nInvalid delay value\r\n";

        setPWMDelay(delay);
        return "\r\nPWM delay was set to " + std::to_string(delay) + "\r\n";
    }

    return "\r\nUnknown command: " + command + "\r\n";
}

void enableLight()
{
    GPIO_SetOutputValue(control_light_pin, true);
}

void disableLight()
{
    GPIO_SetOutputValue(control_light_pin, false);
}

void setTimerDelay(int delay)
{
    TIM2->PSC = getPscFromDelay(delay) - 1;
    TIM2->CR1 |= TIM_CR1_CEN;
}

void setPWMDelay(int delay)
{
    TIM1->PSC = getPscFromDelay(delay * 2) - 1;
    TIM1->CR1 |= TIM_CR1_CEN;
}