#include "telemetryTask.h"
#include <unistd.h>
#include <future>
#include <cstring>
#include <string>

#include "context/dab_context.h"
#include "dab/dab_handler.h"
#include "telemetriesProxy.h"
#include "utils/hi_log.h"
#include "utils/hi_time.h"

using namespace std;

namespace {
	bool isExit = false;
	TelemetryTask::OnTelemetry onTelemetryFunc = [](const string& appId){};
	void onTelemetry_Impl() {
		vector<string> list;
		TelemetriesProxy::getNeedReportAppOrDevice(list, dab::currentMs());
		if (list.size() < 1) {
			return;
		}
		if (isExit) {
			return;
		}
		for (const auto& it: list) {
			onTelemetryFunc(it);
		}
	}

	void onTelemetry_func() {
		FUN_LOG();
		static const int MILL_SECONDS_100 = 100000;
		isExit = false;
		while (!isExit) {
			onTelemetry_Impl();
			if (isExit) {
				break;
			}
			usleep(MILL_SECONDS_100);
		}
	}
}

static future<void> telemetryThread;

bool TelemetryTask::start(const OnTelemetry& func) {
    FUN_LOG();
	onTelemetryFunc = func;
    telemetryThread = std::async([&]{
        DABLOG_ALWAYS("onTelemetry begin");
        onTelemetry_func();
        DABLOG_ALWAYS("onTelemetry finish");
    });
    telemetryThread.valid();
	return true;
}

bool TelemetryTask::stop() {
    FUN_LOG();
    isExit = true;
    telemetryThread.wait();
	return true;
}