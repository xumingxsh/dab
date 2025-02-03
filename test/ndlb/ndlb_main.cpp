#include <gtest/gtest.h>
#include "utils/hi_log.h"
#include "dab/dab_handler.h"
#include "dab/dab_api.h"
#include "hi_topic_handler.h"
#include "app_attributies.h"

using namespace std;

namespace {	
	void publish(const char* topic, const char* body) {
		DABLOG_ALWAYS("topic:%s,body:%s", topic, body);
	}
    void dabInit() {
		FUN_LOG();
		DABProperties::device_id = "this_is_a_test";
		TopicHandler::init(5);
		DABHandler::init();				
		DABContext::setPublishFunc(publish);
		map<string, function<void(DABContext&)>> handles;    
		DABHandler::getTopicHandles(handles);
		TopicHandler::registerHandler(handles);
		dab_api_init();
    }
    void dabDestory() {
		FUN_LOG();
		TopicHandler::destroy();
		DABHandler::destroy();
		dab_api_destroy();
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);    
    dabInit();
    int ret = RUN_ALL_TESTS();
    dabDestory();
    return ret;
}