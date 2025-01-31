#include "telemetriesProxy.h"

#include <mutex>
#include "utils/hi_time.h"
#include <utils/hi_collection.h>

using namespace std;

#define DEVICE_ID "device"

namespace {
	class TelemetryInfo {
	public:
		string dabAppId;
		int duration;
		long long lastReport;
	public:
		bool canReport(long long time) {
			if (time - lastReport >= duration) {
				lastReport = time;
				return true;
			}
			return false;
		}
		bool isDevice() {
			return dabAppId == DEVICE_ID;
		}
	};

	HiCollection<map<string, TelemetryInfo>> telemetries;

	bool startTelemetry(const string& dabAppId, int duration) {
		std::lock_guard<std::mutex> lck(telemetries.mutex_);
		auto it = telemetries.collection.find(dabAppId);
		if (telemetries.collection.end() != it) {
			return false;
		}
		
		TelemetryInfo item;
		item.dabAppId = dabAppId;
		item.duration = duration;
		item.lastReport = 0;
		telemetries.collection[dabAppId] = item;
		return true;
	}

	bool stopTelemetry(const string& dabAppId) {
		std::lock_guard<std::mutex> lck(telemetries.mutex_);
		auto it = telemetries.collection.find(dabAppId);
		if (telemetries.collection.end() == it) {
			return false;
		}
		telemetries.collection.erase(it);
		return true;
	}
}

bool TelemetriesProxy::startAppTelemetry(const string& dabAppId, int duration) {
    return startTelemetry(dabAppId, duration);
}

bool TelemetriesProxy::startDeviceTelemetry(int duration) {
    return startTelemetry(DEVICE_ID, duration);
}

bool TelemetriesProxy::stopAppTelemetry(const string& dabAppId) {
	return stopTelemetry(dabAppId);
}

bool TelemetriesProxy::stopDeviceTelemetry() {
	return stopTelemetry(DEVICE_ID);
}

void TelemetriesProxy::getNeedReportAppOrDevice(vector<string>& apps, long long currentTimeInMS) {
    std::lock_guard<std::mutex> lck(telemetries.mutex_);
    for (auto& it: telemetries.collection) {
        if (it.second.canReport(currentTimeInMS)) {
            apps.push_back(it.second.dabAppId);
        }
    }
}

bool TelemetriesProxy::isDevice(const string& appId) {
	return appId == DEVICE_ID;
}