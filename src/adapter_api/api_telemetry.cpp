#include "dab/dab_api_telemetry.h"
#include "utils/hi_log.h"

bool dab_api_startDeviceTelemetry() {
    FUN_LOG();
    return true;
}
bool dab_api_stopDeviceTelemetry() {
    FUN_LOG();
    return true;
}
bool dab_api_startAppTelemetry(const char* appId) {
    FUN_LOG();
    return true;
}
bool dab_api_stopAppTelemetry(const char* appId) {
    FUN_LOG();
    return true;
}
bool dab_api_getDeviceMemory(int& val)  {
    FUN_LOG();
	val = 80;
    return true;
}
bool dab_api_getDeviceCPU(float& val)  {
    FUN_LOG();
	val = 3.1415926;
    return true;
}
bool dab_api_getAppCPU(const char* appId, float& val)  {
    FUN_LOG();
	val = 3.1415926;
    return true;
}
bool dab_api_getAppMemory(const char* appId, int& val)  {
    FUN_LOG();
	val = 80;
    return true;
}