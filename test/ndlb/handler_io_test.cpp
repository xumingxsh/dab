#include <gtest/gtest.h>
#include <unistd.h>
#include "dab_common.h"
#include "utils/hi_log.h"

TEST(DABHandler, io) {
	onTopicTest("input/key/list", "{}");
	onTopicTest("input/key-press", R"({"keyCode":"KEY_HOME"})");
	onTopicTest("input/long-key-press", R"({
            "keyCode": "KEY_RIGHT",
            "durationMs": 10000
        })");
	onTopicTest("output/image", "{}");
}