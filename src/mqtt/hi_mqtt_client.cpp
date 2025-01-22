#include "hi_mqtt_client.h"

#include <cstring>
#include <cassert>
#include <algorithm>
#include <unistd.h>
#include <chrono>
#include <mutex>
#include "mosquitto/mosquitto.h"
#include "utils/hi_log.h"
#include "mqtt_util.h"
#include "utils/hiScopeGuard.h"

using namespace std;

namespace {
    // 全局变量封装
    struct MqttState {
        bool connected = false;
        struct mosquitto* mqtt = nullptr;
        int connectMaxTryTimes = 10;
        int connectFailSleepSecond = 5;
        int mqttAliveMsgTime = 60;
    };

    static MqttState mqttState;
    static mutex mqttMutex;

    // 初始化 MQTT 库
    void initMqtt() {
        UN_RE_ENTER();
        DABLOG_ALWAYS("mosquitto_lib_init called");
        int ret = mosquitto_lib_init();
        ON_MQTT_RET(ret);
        assert(MqttUtil::success(ret));
    }

    // 销毁 MQTT 库
    void destroyMqtt() {
        UN_RE_ENTER();
        DABLOG_ALWAYS("mosquitto_lib_cleanup called");
        int ret = mosquitto_lib_cleanup();
        ON_MQTT_RET(ret);
        assert(MqttUtil::success(ret));
    }

    // 连接 MQTT 代理
    bool connectBroker(const char* ip, int port) {
        int ret = mosquitto_connect_async(mqttState.mqtt, ip, port, mqttState.mqttAliveMsgTime);
        if (!MqttUtil::success(ret)) {
            DABLOG_ERROR("connect mqtt failed, ip:%s, port:%d", ip, port);
            return false;
        }
        DABLOG_INFO("connect mqtt success, ip:%s, port:%d", ip, port);

        ret = mosquitto_loop_start(mqttState.mqtt);
        ON_MQTT_RET(ret);
        if (!MqttUtil::success(ret)) {
            DABLOG_ERROR("mosquitto_loop_start failed");
            mosquitto_disconnect(mqttState.mqtt);
            return false;
        }
        DABLOG_ALWAYS("mosquitto_loop_start success");
        mqttState.connected = true;
        return true;
    }

    // Windows 平台连接逻辑
    void connectInWindows(const char* ip, int port) {
        int ret = mosquitto_connect(mqttState.mqtt, ip, port, mqttState.mqttAliveMsgTime);
        ON_MQTT_RET(ret);
        if (!MqttUtil::success(ret)) {
            DABLOG_ERROR("connect mqtt failed, ip:%s, port:%d", ip, port);
            throw "mqtt start failed, can't connect";
        }
        DABLOG_INFO("connect mqtt success, ip:%s, port:%d", ip, port);

        ret = mosquitto_loop_forever(mqttState.mqtt, -1, 1);
        ON_MQTT_RET(ret);
        if (!MqttUtil::success(ret)) {
            DABLOG_ERROR("mosquitto_loop_forever failed");
            mosquitto_disconnect(mqttState.mqtt);
            throw "mqtt start failed, mosquitto_loop failed";
        }
        DABLOG_ALWAYS("mosquitto_loop success");
        mqttState.connected = true;
        MqttUtil::subscribe(mqttState.mqtt);
    }

    // 连接 MQTT 代理（通用逻辑）
    void connect(const char* ip, int port) {
#ifdef _WIN32
        connectInWindows(ip, port);
#else
        for (int i = 0; i < mqttState.connectMaxTryTimes; i++) {
            if (connectBroker(ip, port)) {
                DABLOG_INFO("mqtt connect success");
                return;
            }
            DABLOG_INFO("mqtt connect failed, try times:%d, will try after %d seconds", i + 1, mqttState.connectFailSleepSecond);
            sleep(mqttState.connectFailSleepSecond);
        }
        throw "mqtt start failed, can't connect";
#endif
    }
} // namespace

void HiMqttClient::start(const char* ip, int port, const char* user, const char* password, const char* clientId) {
    FUN_LOG();
    if (!MqttUtil::hasTopics()) {
        throw "mqtt start failed, topics is null, please call subscribe first";
    }

    initMqtt();
    DAB_ASSERT(!mqttState.mqtt, "mqtt is nullptr");
    mqttState.connected = false;

    mqttState.mqtt = mosquitto_new(clientId, true, nullptr);
    if (!mqttState.mqtt) {
        throw "mqtt start failed, can't create mosquitto, maybe low memory";
    }

    dab::HiScopeGuard mqttGuard([&]() {
        mosquitto_destroy(mqttState.mqtt);
        mqttState.mqtt = nullptr;
    });

    if (user != nullptr && password != nullptr && strlen(user) > 0 && strlen(password) > 0) {
        int ret = mosquitto_username_pw_set(mqttState.mqtt, user, password);
        ON_MQTT_RET(ret);
        if (!MqttUtil::success(ret)) {
            throw "mqtt start failed in set username and password";
        }
        DABLOG_INFO("set mqtt user and password success");
    }

    MqttUtil::setMqttCallBack(mqttState.mqtt);
    connect(ip, port);
    mqttGuard.dismissed();
    DABLOG_ALWAYS("start mqtt success");
}

void HiMqttClient::stop() {
    FUN_LOG();
    if (!mqttState.mqtt) {
        return;
    }

    if (mqttState.connected) {
        mosquitto_disconnect(mqttState.mqtt);
        DABLOG_INFO("mqtt disconnect");
    }

    mosquitto_destroy(mqttState.mqtt);
    DABLOG_INFO("mqtt destroy");
    mqttState.mqtt = nullptr;
    destroyMqtt();
}

void HiMqttClient::subscribe(const vector<string>& topics) {
    MqttUtil::setTopics(topics);
}

bool HiMqttClient::publish(const char* topic, const char* body) {
    FUN_LOG();
    if (!mqttState.mqtt || !topic || !body) {
        DABLOG_ERROR("topic or body empty");
        return false;
    }

    DABLOG_INFO("topic:%s, body:%s", topic, body);
    int ret = MOSQ_ERR_SUCCESS;
    {
        static mutex publishMutex;
        lock_guard<mutex> lock(publishMutex);
        ret = mosquitto_publish(mqttState.mqtt, nullptr, topic, strlen(body), body, 1, false);
    }
    ON_MQTT_RET(ret);
    return MqttUtil::success(ret);
}

void HiMqttClient::onTopic(const MqttUtil::TopicHandlerFunc& func) {
    MqttUtil::setTopicHandler(func);
}