#pragma once

#include <functional>

extern "C" void setAppAttributes(const std::function<void()>& func);
extern "C" int runDabService();
extern "C" int stopDabService();