#ifndef TELEMETRIES_PROXY_H_
#define TELEMETRIES_PROXY_H_

#include <map>
#include <vector>
#include <utils/hi_collection.h>

#define DEVICE_ID "device"


class TelemetryInfo {
public:
    std::string dabAppId;
    std::string tvAppId;
    long long startTime;
    int duration;
    long long lastReport;
public:
    bool canReport(long long time);
    bool isDevice();
};

class TelemetriesProxy {
public:
    bool start(const char* dabAppId, const char* tvAppId, int duration);
    bool stop(const char* dabAppId);
    void onTime(std::vector<TelemetryInfo>& apps);
private:
    HiCollection<std::map<std::string, TelemetryInfo>> telemetries;
};

#endif // TELEMETRIES_PROXY_H_