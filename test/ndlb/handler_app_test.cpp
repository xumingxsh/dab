#include <gtest/gtest.h>
#include "dab_common.h"
#include <unistd.h>

TEST(DABHandler, applications) {
	onTopicTest("applications/list", "{}");
	onTopicTest("applications/launch", "{\"appId\":\"YouTube\"}");
	onTopicTest("applications/launch-with-content", "{\"appId\":\"YouTube\",\"contentId\":\"XqZsoesa55w\"}");
	onTopicTest("applications/launch", "{\"appId\": \"Netflix\",\"parameters\": [ \"-KEY\", \"https%3A%2F%2Fwww.example-value.com%2F\", \"-STANDALONE_PARAM\", \"%22param-with-quotes%22\"]}");
	onTopicTest("applications/get-state", "{\"appId\":\"YouTube\"}");
	onTopicTest("applications/exit", "{\"appId\":\"YouTube\"}");
	onTopicTest("applications/exit", "{\"appId\":\"YouTube\",\"background\":true}");
}