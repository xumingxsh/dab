#include "dab/dab_handler.h"
#include <functional>
#include <cstring>
#include "app_attributies.h"

using namespace std;

static void setTopicHandle(map<string, function<void(DABContext&)>>& handles, 
            const char* topic, const function<void(DABContext&)>& handle) {
    stringstream oss;
    oss<<"dab/"<<DABProperties::device_id<<"/"<<topic;
    handles[oss.str()] = handle;
}

void DABHandler::getTopicHandles(map<string, function<void(DABContext&)>>& handles) {
    handles["dab/discovery"] = DABHandler::discover;
    setTopicHandle(handles, "operations/list",                  DABHandler::operations);
    setTopicHandle(handles, "applications/list",                DABHandler::getAppList);
    setTopicHandle(handles, "applications/launch",              DABHandler::launch);
    setTopicHandle(handles, "applications/launch-with-content", DABHandler::launchByContent);
    setTopicHandle(handles, "applications/get-state",           DABHandler::getAppStatus);
    setTopicHandle(handles, "applications/exit",                DABHandler::exitApp);
    setTopicHandle(handles, "system/restart",                   DABHandler::reboot);
    setTopicHandle(handles, "system/settings/list",             DABHandler::listSystemSetting);
    setTopicHandle(handles, "system/settings/set",              DABHandler::setSystemSetting);
    setTopicHandle(handles, "system/settings/get",              DABHandler::getSystemSetting);
    setTopicHandle(handles, "output/image",                     DABHandler::capture);
    setTopicHandle(handles, "device-telemetry/start",           DABHandler::startDeviceTelemetry);
    setTopicHandle(handles, "device-telemetry/stop",            DABHandler::stopDeviceTelemetry);
    //setTopicHandle(handles, "device-telemetry/metrics",         DABHandler::reportDeviceTelemetryMetrics);
    setTopicHandle(handles, "app-telemetry/start",              DABHandler::startAppTelemetry);
    setTopicHandle(handles, "app-telemetry/stop",               DABHandler::stopAppTelemetry);
    //setTopicHandle(handles, "app-telemetry/metrics",            DABHandler::reportAppTelemetryMetrics);
    setTopicHandle(handles, "input/key-press",                  DABHandler::keyPress);
    setTopicHandle(handles, "input/key/list",                   DABHandler::getKeyList);
    setTopicHandle(handles, "input/long-key-press",             DABHandler::keyPressByLongTime);
    setTopicHandle(handles, "health-check/get",                 DABHandler::health_check);
    setTopicHandle(handles, "device/info",                      DABHandler::getDeviceInfo);
    setTopicHandle(handles, "version",                          DABHandler::version);
    //setTopicHandle(handles, "messages",                         DABHandler::reportMessage);
    setTopicHandle(handles, "voice/list",                       DABHandler::getVoiceList);
    setTopicHandle(handles, "voice/set",                        DABHandler::setVoiceStatus);
    setTopicHandle(handles, "voice/send-text",                  DABHandler::sendText2voice);
    setTopicHandle(handles, "voice/send-audio",                 DABHandler::sendAudio2voice);
}

static void setTopics(vector<string>& topics, const char* topic) {
    stringstream oss;
    oss<<"dab/"<<DABProperties::device_id<<"/"<<topic;
    topics.push_back(oss.str());
}

void DABHandler::getTopics(vector<string>& topics) {
    setTopics(topics, "operations/list");
    setTopics(topics, "applications/list");
    setTopics(topics, "applications/launch");
    setTopics(topics, "applications/launch-with-content");
    setTopics(topics, "applications/get-state");
    setTopics(topics, "applications/exit");
    setTopics(topics, "system/restart");
    setTopics(topics, "system/settings/list");
    setTopics(topics, "system/settings/set");
    setTopics(topics, "system/settings/get");
    setTopics(topics, "output/image");
    setTopics(topics, "device-telemetry/start");
    setTopics(topics, "device-telemetry/stop");
    //setTopics(topics, "device-telemetry/metrics");
    setTopics(topics, "app-telemetry/start");
    setTopics(topics, "app-telemetry/stop");
    //setTopics(topics, "app-telemetry/metrics");
    setTopics(topics, "input/key-press");
    setTopics(topics, "input/key/list");
    setTopics(topics, "input/long-key-press");
    setTopics(topics, "health-check/get");
    setTopics(topics, "device/info");
    setTopics(topics, "version");
    setTopics(topics, "messages");
    setTopics(topics, "discovery");
    setTopics(topics, "voice/list");
    setTopics(topics, "voice/set");
    setTopics(topics, "voice/send-text");
    setTopics(topics, "voice/send-audio");
}

string DABHandler::getTelemetryTopic(const char* appId) {
    stringstream oss;
    oss<<"dab/"<<DABProperties::device_id<<"/app-telemetry/metrics";
	if (appId != nullptr && strlen(appId) > 0) {
		oss<<"/"<<appId;
	}
	return oss.str();
}
