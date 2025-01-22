#pragma once

#include <vector>
#include <string>
#include <functional>
#include "mosquitto/mosquitto.h"

#define ON_MQTT_RET(ret)  \
    do { \
        if (MOSQ_ERR_SUCCESS != (ret)) { \
            DABLOG_ERROR("mosquitto error: %s", mosquitto_strerror(ret)); \
        } \
    } while (0)

class MqttUtil {
public:
	using TopicHandlerFunc = std::function<void(const char*, const char*, const char*, const char*)>;
public:
    static void setMqttCallBack(struct mosquitto* mqtt);
    static bool success(int ret) {
		return ret == MOSQ_ERR_SUCCESS;
	}
    static void setTopics(const std::vector<std::string>& topics);
	static void subscribe(struct mosquitto* mqtt);
public:
    static bool hasTopics();
    static void setTopicHandler(const TopicHandlerFunc& handler);
public:
    MqttUtil() = delete;
};