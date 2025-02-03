#include <gtest/gtest.h>
#include "dab_common.h"
#include <unistd.h>

TEST(DABHandler, telemetry) {
	onTopicTest("device-telemetry/start", R"({"duration":100})");
	usleep(210*1000);
	onTopicTest("device-telemetry/stop", "{}");
}
TEST(DABHandler, telemetry_youtube) {
	onTopicTest("app-telemetry/start", R"({"appId":"YouTube","duration":100})");
	usleep(210*1000);
	onTopicTest("app-telemetry/stop",  R"({"appId":"YouTube"})");
}