#include <gtest/gtest.h>
#include <unistd.h>
#include "dab_common.h"
#include "utils/hi_log.h"

TEST(DABHandler, device) {
	onTopicTest("device/info", "{}");
	onTopicTest("system/restart", "{}");
}