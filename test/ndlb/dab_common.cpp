#include "dab_common.h"

#include <sstream>
#include "app_attributies.h"
#include "hi_topic_handler.h"

using namespace std;

namespace {
	string getRequestTopic(const string& topic) {
		stringstream oss;
		oss<<"dab/"<<DABProperties::device_id<<"/"<<topic;
		return oss.str();
	}
	string getResponseTopic(const string& topic) {
		stringstream oss;
		oss<<"_response/dab/"<<DABProperties::device_id<<"/"<<topic;
		return oss.str();
	}
}

void onTopicTest(const std::string& topic, const std::string& request) {
	TopicHandler::onTopic(getRequestTopic(topic).c_str(), request.c_str(), getResponseTopic(topic).c_str(), "");
}