#pragma once

extern "C" {
    bool dab_api_startDeviceTelemetry();
    bool dab_api_stopDeviceTelemetry();
    bool dab_api_startAppTelemetry(const char* appId);
    bool dab_api_stopAppTelemetry(const char* appId);
    bool dab_api_getDeviceMemory(int& val);
    bool dab_api_getDeviceCPU(float& val);
    bool dab_api_getAppCPU(const char* appId, float& val);
    bool dab_api_getAppMemory(const char* appId, int& val);
}