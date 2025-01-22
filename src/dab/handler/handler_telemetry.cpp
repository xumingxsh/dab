#include "dab/dab_handler.h"
#include "dab/dab_api_app.h"
#include "dab/dab_api_telemetry.h"

#include "utils/telemetriesProxy.h"
#include "utils/hi_log.h"
#include "utils/hi_time.h"

#include <unistd.h>
#include <future>
#include <cstring>

using namespace std;

static TelemetriesProxy telemetries;

void DABHandler::startDeviceTelemetry(DABContext& context) {
    FUN_LOG();
	int duration = context.request.getIntValue("duration");
    if (duration < 0) {
        context.clientFail("start device telemetry request not include duration");
        return;
    }
    
    if (duration < 100) {
        context.clientFail("in start device telemetry request, duration must > 100ms");
        return;
    }
    
    bool ret = telemetries.start(DEVICE_ID, DEVICE_ID, duration);
    if (!ret) {
        context.clientFail(" device telemetry is started, could not start again");
        return;
    }
	context.success();
}

void DABHandler::stopDeviceTelemetry(DABContext& context) {
	 bool ret = telemetries.stop(DEVICE_ID);
    if (!ret) {
        context.clientFail(" device telemetry is not started, could not stop");
        return;
    }
	context.success();
}

void DABHandler::startAppTelemetry(DABContext& context) {
    FUN_LOG();
	int duration = context.request.getIntValue("duration");
    if (duration < 0) {
        context.clientFail("start device telemetry request not include duration");
        return;
    }
    
    if (duration < 100) {
        context.clientFail("in start device telemetry request, duration must > 100ms");
        return;
    }

	string appId = context.request.getStringValue("appId");
	if (appId.empty()) {
        context.clientFail("not include appId");
        return;
	}
    
    bool ret = telemetries.start(appId.c_str(), appId.c_str(), duration);
    if (!ret) {
        context.clientFail(" device telemetry is started, could not start again");
        return;
    }
	context.success();
}

void DABHandler::stopAppTelemetry(DABContext& context) {
	string appId = context.request.getStringValue("appId");
	if (appId.empty()) {
        context.clientFail("not include appId");
        return;
	}
	bool ret = telemetries.stop(appId.c_str());
    if (!ret) {
        context.clientFail(" app telemetry is not started, could not stop");
        return;
    }
	context.success();
}

void DABHandler::reportDeviceTelemetryMetrics(DABContext& context) {
	DAB_NOT_IMPLEMENT(context);
}

void DABHandler::reportAppTelemetryMetrics(DABContext& context) {
	DAB_NOT_IMPLEMENT(context);
}

static future<void> telemetryThread;
static bool isExit = false;

static void onTelemetry();

void DABHandler::stopTelemetry() {
    FUN_LOG();
    isExit = true;
    telemetryThread.wait();
}

static void onTelemetry_func();

void DABHandler::startTelemetry() {
    FUN_LOG();
    telemetryThread = std::async([&]{
        DABLOG_INFO("onTelemetry begin");
        onTelemetry_func();
        DABLOG_INFO("onTelemetry finish");
    });
    telemetryThread.valid();
}


static void onTelemetry_Impl();
static void onTelemetry_func() {
    FUN_LOG();
    static const int MILL_SECONDS_100 = 100000;
    isExit = false;
    while (!isExit) {
        onTelemetry_Impl();
        if (isExit) {
            break;
        }
        usleep(MILL_SECONDS_100);
    }
}

static void publishTelemetry(TelemetryInfo& telemetry);
static void onTelemetry_Impl() {
    vector<TelemetryInfo> list;
    telemetries.onTime(list);
    if (list.size() < 1) {
        return;
    }
    if (isExit) {
        return;
    }
    for (auto it = list.begin(); it != list.end(); ++it) {
        publishTelemetry(*it);
    }
}

static float getCPU(const char* appId);
static int getMemory(const char* appId);
static void publishCPU(const char* topic, float cpu);
static void publishMemory(const char* topic, int memory);
static void publishTelemetry(TelemetryInfo& telemetry) {
    FUN_LOG();
    string topic = DABHandler::getTelemetryTopic(telemetry.isDevice() ? nullptr : telemetry.dabAppId.c_str());
    float cpu = getCPU(telemetry.dabAppId.c_str());
    if (cpu >= 0) {
        publishCPU(topic.c_str(), cpu);
    }
    int memory = getMemory(telemetry.dabAppId.c_str());
    if (memory >= 0) {
        publishMemory(topic.c_str(), memory);
    }
}

static void publishCPU(const char* topic, float cpu) {
    Json::Value root;
    root["metric"] = "cpu";
    root["value"] = cpu;
    root["timestamp"] = dab::currentMs();

    Json::FastWriter fastWriter;
	string body = fastWriter.write(root);
    DABContext::publish(topic, body.c_str());
}

static void publishMemory(const char* topic, int memory) {
    Json::Value root;
    root["metric"] = "memory";
    root["value"] = memory;
    root["timestamp"] = dab::currentMs();

    Json::FastWriter fastWriter;
	string body = fastWriter.write(root);
    DABContext::publish(topic, body.c_str());
}

static float getCPU(const char* appId) {
    float cpu = -1.0;
    if (nullptr == appId || strcmp(appId, DEVICE_ID) == 0) {
        bool ret = dab_api_getDeviceCPU(cpu);
        if (!ret) {
            return -1.0;
        }
        return cpu;
    } else {
        bool ret = dab_api_getAppCPU(appId, cpu);
        if (!ret) {
            return -1.0;
        }
        return cpu;
    }
}

static int getMemory(const char* appId) {
    int memory = -1;
    if (nullptr == appId || strcmp(appId, DEVICE_ID) == 0) {
        bool ret = dab_api_getDeviceMemory(memory);
        if (!ret) {
            return -1;
        }
        return memory;
    } else {
        bool ret = dab_api_getAppMemory(appId, memory);
        if (!ret) {
            return -1;
        }
        return memory;
    }
}