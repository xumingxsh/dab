#include "telemetriesProxy.h"

#include "utils/hi_time.h"

using namespace std;

static long long getCurrentTime();

bool TelemetriesProxy::start(const char* dabAppId, const char* tvAppId, int duration) {
    std::lock_guard<std::mutex> lck(telemetries.mutex_);
    auto it = telemetries.collection.find(dabAppId);
    if (telemetries.collection.end() != it) {
        return false;
    }
    
    TelemetryInfo item;
    item.dabAppId = dabAppId;
    item.tvAppId = tvAppId;
    item.duration = duration;
    item.startTime = dab::currentMs();
    item.lastReport = 0;
    telemetries.collection[dabAppId] = item;
    return true;
}
bool TelemetriesProxy::stop(const char* dabAppId) {
    std::lock_guard<std::mutex> lck(telemetries.mutex_);
    auto it = telemetries.collection.find(dabAppId);
    if (telemetries.collection.end() != it) {
        return false;
    }
    telemetries.collection.erase(it);
    return true;
}

void TelemetriesProxy::onTime(vector<TelemetryInfo>& apps) {
    long long time = dab::currentMs();
    std::lock_guard<std::mutex> lck(telemetries.mutex_);
    for (auto it = telemetries.collection.begin(); it != telemetries.collection.end(); ++it) {
        if (it->second.canReport(time)) {
            apps.push_back(it->second);
        }
    }
}

bool TelemetryInfo::canReport(long long time) {
    if (time - lastReport >= duration) {
        lastReport = time;
        return true;
    }
    return false;
}

bool TelemetryInfo::isDevice() {
    return dabAppId == DEVICE_ID;
}