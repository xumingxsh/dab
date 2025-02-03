#include "context/dab_context.h"

#include <string>
#include <cassert>
#include <stdarg.h>
#include "utils/hi_log.h"

using namespace std;
const static int MAX_BUF_SIZE = 2048;

static function<void(const char*, const char*)> publish_func;

void DABContext::setPublishFunc(const std::function<void(const char*, const char*)>& func) {
    publish_func = func;
}

void DABContext::publish(DABContext& context) {
    assert(!context.request.response_topic.empty());
	DABContext::publish(context.request.response_topic.c_str(), context.toJson().c_str());
}

void DABContext::publish(const char* topic, const char* body) {
    if (nullptr == topic || nullptr == body) {
        return;
    }
    DABLOG_INFO("topic:%s, body:%s", topic, body);
	publish_func(topic, body);
}

 DABContext::DABContext(const char* topic, const char* requestBody, const char* reponse_topic, const char* correlation_data) {
    request.setDABStatus(&status);
    request.init(requestBody);
    request.topic = topic;
	request.response_topic = reponse_topic;
	request.correlationData = correlation_data;
 }

bool DABContext::is_ok() const {
    return status.is_ok();
}

void DABContext::success() {
}

void DABContext::clientFail(const char* fmt, ...) {
    char chArr[MAX_BUF_SIZE] = {0};
    va_list arguments;
    va_start(arguments, fmt);
    vsnprintf(chArr, MAX_BUF_SIZE, fmt, arguments);
    va_end(arguments);
    status.clientFail(chArr);
    DABLOG_ERROR(chArr);
}
void DABContext::serverFail(const char* fmt, ...) {
    char chArr[MAX_BUF_SIZE] = {0};
    va_list arguments;
    va_start(arguments, fmt);
    vsnprintf(chArr, MAX_BUF_SIZE, fmt, arguments);
    va_end(arguments);

    status.serverFail(chArr);
    DABLOG_ERROR(chArr);
}

string DABContext::toJson() {
    response.append("status", status.getStatus());
    if (!is_ok()) {
        if (!status.out_log.empty()) {
            response.append("error", status.out_log);
        }
    }
    Json::FastWriter fastWriter;
	return fastWriter.write(response.payload);
}