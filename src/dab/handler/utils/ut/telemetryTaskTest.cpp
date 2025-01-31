#include <gtest/gtest.h>

#include <unistd.h>
#include "utils/hi_log.h"
#include "../telemetryTask.h"
#include "../telemetriesProxy.h"

using namespace std;

TEST(TelemetryTask, start_stop) {
	TelemetryTask::start([](const string& appId){
		DABLOG_ALWAYS("appId:%s is in telemetry", appId.c_str());
	});
	TelemetriesProxy::startDeviceTelemetry(100);
	TelemetriesProxy::startAppTelemetry("YouTube", 100);
	
	sleep(2);
	TelemetriesProxy::stopDeviceTelemetry();
	TelemetriesProxy::stopAppTelemetry("YouTube");
	TelemetryTask::stop();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}