#include "mqtt_util.h"
#include <algorithm>
#include <mutex>
#include "utils/hi_log.h"
#include "mosquitto/mqtt_protocol.h"

using namespace std;

namespace {
    MqttUtil::TopicHandlerFunc handleTopic = [](const char*, const char*, const char*, const char*) {
        DAB_ASSERT(false, "not set mqtt handleTopic");
    };
    mutex handler_mutex;

    string getMqttPropertyString(const mosquitto_property* props, int property_id) {
        char* value = nullptr;
        const mosquitto_property* prop = mosquitto_property_read_string(props, property_id, &value, false);
        if (!prop) {
            return "";
        }
        return value;
    }
	
	void handleMqttMessage (const struct mosquitto_message* msg, const mosquitto_property* props) {
        string resp_topic = getMqttPropertyString(props, MQTT_PROP_RESPONSE_TOPIC);
        string correlation_data = getMqttPropertyString(props, MQTT_PROP_CORRELATION_DATA);

        {
            lock_guard<mutex> lock(handler_mutex);
            handleTopic(msg->topic, static_cast<const char*>(msg->payload), resp_topic.c_str(), correlation_data.c_str());
        }
	}
}

namespace {
    vector<string> mqtt_topics;
	mutex topics_mutex; 

    void connectCb(struct mosquitto* mosq, void* data, int ret) {
        ON_MQTT_RET(ret);
        if (!MqttUtil::success(ret)) {
            return;
        }

        DABLOG_ALWAYS("mqtt connect success");
        MqttUtil::subscribe(mosq);
    }

    void messageCb(struct mosquitto* mosq, void* data, const struct mosquitto_message* msg, const mosquitto_property* props) {
        FUN_LOG();
        if (!msg || !msg->topic) {
            return;
        }

        DABLOG_ERROR("topic:%s", msg->topic);
        if (!props) {
            DABLOG_ERROR("props is null");
            return;
        }
		handleMqttMessage (msg, props);
    }

    void subscribeCb(struct mosquitto* mosq, void* data, int mid, int qos_count, const int* granted_qos) {
        //DABLOG_ALWAYS("call, mid:%d", mid);
    }

    void logCb(struct mosquitto* mosq, void* data, int level, const char* str) {
        if (level == MOSQ_LOG_ERR) {
            DABLOG_ERROR("mosquitto log:%s", str);
        } else {
            //DABLOG_INFO("mosquitto log:%s", str);
        }
    }
} // namespace

static void setCallback(struct mosquitto* mqtt) {
    mosquitto_connect_callback_set(mqtt, connectCb);
    mosquitto_message_v5_callback_set(mqtt, messageCb);
    mosquitto_subscribe_callback_set(mqtt, subscribeCb);
    mosquitto_log_callback_set(mqtt, logCb);
}

void MqttUtil::setMqttCallBack(struct mosquitto* mqtt) {
    DAB_ASSERT(mqtt, "mqtt parameter is nullptr");
    if (!mqtt) {
        return;
    }

    int ver = MQTT_PROTOCOL_V5;
    mosquitto_opts_set(mqtt, MOSQ_OPT_PROTOCOL_VERSION, &ver);
    setCallback(mqtt);

    DABLOG_INFO("mosquitto set connect, message, subscribe, log callback success");
}

void MqttUtil::setTopics(const vector<string>& topics) {
    lock_guard<mutex> lock(topics_mutex);
    mqtt_topics.insert(mqtt_topics.end(), topics.begin(), topics.end());
    sort(mqtt_topics.begin(), mqtt_topics.end());
    mqtt_topics.erase(unique(mqtt_topics.begin(), mqtt_topics.end()), mqtt_topics.end());
}

void MqttUtil::subscribe(struct mosquitto* mqtt) {
    if (!mqtt) {
        return;
    }

    lock_guard<mutex> lock(topics_mutex);
    for (const string& topic : mqtt_topics) {
        int ret = mosquitto_subscribe_v5(mqtt, nullptr, topic.c_str(), 1, 0, nullptr);
        ON_MQTT_RET(ret);
        if (!success(ret)) {
            DABLOG_WARNING("subscribe topic %s failed", topic.c_str());
        } else {
            DABLOG_INFO("subscribe topic %s success", topic.c_str());
        }
    }
}

bool MqttUtil::hasTopics() {
    lock_guard<mutex> lock(topics_mutex);
    return !mqtt_topics.empty();
}

void MqttUtil::setTopicHandler(const MqttUtil::TopicHandlerFunc& handler) {
    lock_guard<mutex> lock(handler_mutex);
    handleTopic = handler;
}