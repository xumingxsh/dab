#pragma once

#include <map>
#include <string>
#include <vector>

#define DEVICE_ID "device"

class TelemetriesProxy {
public:
    static bool startDeviceTelemetry(int duration);
    static bool startAppTelemetry(const std::string& dabAppId, int duration);
	static bool stopDeviceTelemetry();
    static bool stopAppTelemetry(const std::string& dabAppId);
    static void getNeedReportAppOrDevice(std::vector<std::string>& reportApps, long long currentTimeInMS);
	static bool isDevice(const std::string& app);
};