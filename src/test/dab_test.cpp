using namespace std;
#include "dab/dab_handler.h"
#include "app_attributies.h"
#include "hi_mqtt_client.h"
#include "hi_topic_handler.h"

extern void discover_request(string& topic, string& body);
extern void version_request(string& topic, string& body);
extern void getOperations_request(string& topic, string& body);
extern void onAppLaunch_request(string& topic, string& body);


static void init_attributies() {
    static const int MAX_THREADS_COUNT = 5;
    DABProperties::service_name         = "DAB Process";
    DABProperties::max_handle_threads   = MAX_THREADS_COUNT;
    DABProperties::device_id            = "thisisatest";
    DABProperties::device_ip            = "127.0.0.1";
    DABProperties::mqtt_ip              = "127.0.0.1";
    DABProperties::mqtt_port            = 36668;
    DABProperties::mqtt_user            = "hisenseservice";
    DABProperties::mqtt_password        = "multimqttservice";
    DABProperties::mqtt_client_id       = DABProperties::device_id;
}

static int MqttClientRun() {
    // 获取或这是DAB服务相关的属性和配置
    init_attributies();
    
    DABProperties::check_init();
    
    TopicHandler::init(DABProperties::max_handle_threads);
    
    // 3. 建立topic与DABHandler处理函数的关联关系， 并告知TopicHandler
    //   TopicHandler在接收到topic后，会自动分发到DABHandler的对应函数处理
    map<string, function<void(DABContext&)>> handles;    
    DABHandler::getTopicHandles(handles);
    TopicHandler::resistHandler(handles);
    
    // 4. 向MQTT订阅DAB的topic， 需要订阅哪些topic由DABHandler决定
    vector<string> topics;
    DABHandler::getTopics(topics);
    return 0;
}

int WinMain() {
    MqttClientRun();
    DABContext::setPublishFunc([](const char* topic, const char* body){
        printf("\n\n--------\n");
        printf("publish topic:%s, body:%s\n", topic, body);
        printf("--------\n\n");
    });
    string topic;
    string body;
    discover_request(topic, body);
    TopicHandler::onTopic(topic.c_str(), body.c_str(), "", "");

    getOperations_request(topic, body);
    TopicHandler::onTopic(topic.c_str(), body.c_str(), "", "");

    onAppLaunch_request(topic, body);
    TopicHandler::onTopic(topic.c_str(), body.c_str(), "", "");

    return 0;
}