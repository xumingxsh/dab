#include "dab_service.h"

#include <string>
#include <vector>
#include <map>
#include "dab/dab_handler.h"
#include "app_attributies.h"
#include "hi_mqtt_client.h"
#include "hi_topic_handler.h"
#include "utils/hi_log.h"

using namespace std;

namespace {
static bool appAttributeFuncSetted = false;
static function<void()> appAttributesFunc;

void publish(const char* topic, const char* body) {
    HiMqttClient::publish(topic, body);     
}

static void init_attributies() {
    if (appAttributeFuncSetted) {
        appAttributesFunc();
        return;
    }
    static const int MAX_THREADS_COUNT = 5;
    DABProperties::max_handle_threads   = MAX_THREADS_COUNT;
    DABProperties::device_id            = "thisisatest";
    DABProperties::device_ip            = "127.0.0.1";
    DABProperties::mqtt_ip              = "127.0.0.1";
    DABProperties::mqtt_port            = 1883;
    DABProperties::mqtt_user            = "";
    DABProperties::mqtt_password        = "";
    DABProperties::mqtt_client_id       = DABProperties::device_id;
}
}

extern "C" void setAppAttributes(const function<void()>& func) {
    appAttributesFunc = func;
    appAttributeFuncSetted = true;
}

extern "C" int runDabService() {
    FUN_LOG();
    init_attributies();
    
    DABProperties::check_init();
    
    TopicHandler::init(DABProperties::max_handle_threads);
	DABHandler::init();
    
    HiMqttClient::onTopic(TopicHandler::onTopic);
    
    DABContext::setPublishFunc(publish);

    vector<string> topics;
    DABHandler::getTopics(topics);
    HiMqttClient::subscribe(topics);

    map<string, function<void(DABContext&)>> handles;    
    DABHandler::getTopicHandles(handles);
    TopicHandler::registerHandler(handles);
    
    try {
        HiMqttClient::start(DABProperties::mqtt_ip.c_str(), 
                DABProperties::mqtt_port, 
                DABProperties::mqtt_user.c_str(), 
                DABProperties::mqtt_password.c_str(), 
                DABProperties::mqtt_client_id.c_str());
    } catch (const char* error) {
        DABLOG_ERROR("MqttClientRun failed:%s", error);
        HiMqttClient::stop();
        TopicHandler::destroy();
        return -1;
    }
    return 0;
}

extern "C" int stopDabService() {
    FUN_LOG();
    HiMqttClient::stop();
    TopicHandler::destroy();
	DABHandler::destroy();
    return 0;
}