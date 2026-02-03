#pragma once

#include <string>

void configureCommandExecutors();
std::string executeCommand(std::string command);

void enableLight();
void disableLight();
void setTimerDelay(int delay);
void setPWMDelay(int delay);