#pragma once

#include <vector>
#include <string>
#include <map>
#include <functional>
#include "context/dab_context.h"

#ifndef DAB_NOT_IMPLEMENT
#define DAB_NOT_IMPLEMENT(context) \
      context.serverFail("this function is not implement")
#endif

class DABHandler {
public:
    static void init();
    static void destroy();
	static void startTelemetry();
	static void stopTelemetry();
public:
    static void discover(DABContext& context);
    static void version(DABContext& context);
    static void health_check(DABContext& context);
    static void operations(DABContext& context);
public:
    static void getAppList(DABContext& context);
    static void launch(DABContext& context);
    static void launchByContent(DABContext& context);
    static void exitApp(DABContext& context);
    static void getAppStatus(DABContext& context);
public:
    static void getKeyList(DABContext& context);
    static void keyPress(DABContext& context);
    static void keyPressByLongTime(DABContext& context);
    static void capture(DABContext& context);
public:
    static void getVoiceList(DABContext& context);
    static void setVoiceStatus(DABContext& context);
    static void sendAudio2voice(DABContext& context);
    static void sendText2voice(DABContext& context);
public:
    static void getDeviceInfo(DABContext& context);
    static void listSystemSetting(DABContext& context);
    static void getSystemSetting(DABContext& context);
    static void setSystemSetting(DABContext& context);
    static void reboot(DABContext& context);
public:
    static void startDeviceTelemetry(DABContext& context);
    static void stopDeviceTelemetry(DABContext& context);
    static void startAppTelemetry(DABContext& context);
    static void stopAppTelemetry(DABContext& context);
    static void reportDeviceTelemetryMetrics(DABContext& context);
    static void reportAppTelemetryMetrics(DABContext& context);
public:
    static void reportMessage(DABContext& context);
public:
    static void getTopicHandles(std::map<std::string, std::function<void(DABContext&)>>& handles);
    static void getTopics(std::vector<std::string>& topics);
    static std::string getTelemetryTopic(const char* appId);
private:
	DABHandler() = delete;
};