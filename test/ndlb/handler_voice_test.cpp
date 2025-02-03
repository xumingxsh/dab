#include <gtest/gtest.h>
#include <unistd.h>
#include "dab_common.h"
#include "utils/hi_log.h"

TEST(DABHandler, voice) {
	onTopicTest("voice/list", "{}");
	onTopicTest("voice/set", R"({
		"name":"GoogleAssistant",
		"enabled":true
	})");
	onTopicTest("voice/send-text", R"({
		"voiceSystem":"GoogleAssistant",
		"requestText":"Play Ed Sheeran on YouTube"
	})");
	onTopicTest("voice/send-audio", R"({
		"voiceSystem":"GoogleAssistant",
		"fileLocation":"http://192.168.1.8:80/utterance_1.wav"
	})");
}