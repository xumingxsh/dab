#pragma once

#include <string>

enum class DABDisplayType {
   // Device has native display capability
   Native,
   // Device cannot display natively and needs an external display connected
   External,
};

extern "C" {
    std::string dab_api_deviceId();
    std::string dab_api_manufacturer();
    std::string dab_api_model();
    std::string dab_api_serialNumber();
    std::string dab_api_chipset();
    std::string dab_api_firmwareVersion();
    std::string dab_api_firmwareBuild();
    bool dab_api_getScreenPixels(int& width, int height);
    long long dab_api_uptimeSince();
    bool dab_api_getDisplayType(DABDisplayType& type);
}