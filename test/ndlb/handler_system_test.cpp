#include <gtest/gtest.h>
#include <unistd.h>
#include "dab_common.h"
#include "utils/hi_log.h"

TEST(DABHandler, system) {
	onTopicTest("system/settings/list", "{}");
	onTopicTest("system/settings/get", "{}");
	onTopicTest("system/settings/set", R"({
	   "outputResolution": {
		  "width": 3840,
		  "height": 2160,
		  "frequency": 60
	   }})");
	onTopicTest("system/settings/set", R"({"language": "eu"})");
	onTopicTest("system/settings/set", R"({"language": "not_exist"})");
	onTopicTest("system/settings/set", R"({"matchContentFrameRate": "EnabledSeamlessOnly"})");
	onTopicTest("system/settings/set", R"({"matchContentFrameRate": "not_exist"})");
	onTopicTest("system/settings/set", R"({"hdrOutputMode": "AlwaysHdr"})");
	onTopicTest("system/settings/set", R"({"hdrOutputMode": "not_exist"})");
	onTopicTest("system/settings/set", R"({"pictureMode": "Standard"})");
	onTopicTest("system/settings/set", R"({"pictureMode": "not_exist"})");
	onTopicTest("system/settings/set", R"({"audioOutputMode": "Auto"})");
	onTopicTest("system/settings/set", R"({"audioOutputMode": "not_exist"})");
	onTopicTest("system/settings/set", R"({"audioOutputSource": "HDMI"})");
	onTopicTest("system/settings/set", R"({"audioOutputSource": "not_exist"})");
	onTopicTest("system/settings/set", R"({"videoInputSource": "Home"})");
	onTopicTest("system/settings/set", R"({"videoInputSource": "not_exist"})");
	
	
	onTopicTest("system/settings/set", R"({"memc": true})");
	onTopicTest("system/settings/set", R"({"cec": true})");
	onTopicTest("system/settings/set", R"({"mute": true})");
	onTopicTest("system/settings/set", R"({"textToSpeech": true})");
	onTopicTest("system/settings/set", R"({"lowLatencyMode": true})");
	
	onTopicTest("system/settings/set", R"({"audioVolume": 20})");
	
	onTopicTest("system/settings/set", R"({})");
}