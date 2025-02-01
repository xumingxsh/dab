#include "hi_topic_handler.h"
#include <atomic>
#include <future>
#include <sstream>
#include <map>
#include "utils/hi_log.h"

using namespace std;

namespace {
    int max_threads = 1;
    std::atomic<int> running_threads;
    std::map<std::string, std::function<void(DABContext&)>> handleFunctions;

    void processTopic(const char* topic, const char* body, const char* response_topic, const char* correlation_data) {
		FUN_LOG();
        DABLOG_INFO("processTopic, topic:%s, body:%s, response_topic:%s", topic, body, response_topic);
        DABContext context(topic, body, response_topic, correlation_data);

        if (!context.is_ok()) {
            DABContext::publish(context);
            return;
        }

        auto it = handleFunctions.find(topic);
        if (it == handleFunctions.end()) {
            context.serverFail("server not implement");
            DABContext::publish(context);
            return;
        }
        DABLOG_INFO("handle topic:%s", topic);

        it->second(context);
        DABContext::publish(context);
    }
	
    void handleThreadOverload(const char* topic, const char* body, const char* response_topic, const char* correlation_data) {
        DABContext context(topic, body, response_topic, correlation_data);
        context.serverFail("server is busy, threads(%d) is running, max threads is %d", running_threads.load(), max_threads);
        DABContext::publish(context);
    }
	
    void processTopicMessage(const char* topic, const char* body, const char* response_topic, const char* correlation_data) {
        running_threads.fetch_add(1);
        processTopic(topic, body, response_topic, correlation_data);
        running_threads.fetch_sub(1);
    }
} // namespace

void TopicHandler::init(int maxThreads) {
    FUN_LOG();
    max_threads = maxThreads;
}

void TopicHandler::destroy() {
    FUN_LOG();
}

void TopicHandler::registerHandler(const map<string, function<void(DABContext&)>>& handles) {
    handleFunctions = handles;
}

void TopicHandler::onTopic(const char* topic, const char* body, const char* response_topic, const char* correlation_data) {
    FUN_LOG();
    if (running_threads > max_threads) {
        handleThreadOverload(topic, body, response_topic, correlation_data);
        return;
    }
    processTopicMessage(topic, body, response_topic, correlation_data);
}