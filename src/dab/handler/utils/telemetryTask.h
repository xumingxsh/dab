#pragma once

#include <string>
#include <functional>

class TelemetryTask {
public:
	using OnTelemetry = std::function<void(const std::string&)>;
public:
    static bool start(const OnTelemetry& onAppTelemetry);
	static bool stop();
};