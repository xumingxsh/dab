#include "dab/dab_handler.h"

#include <unistd.h>
#include <future>
#include <cstring>

#include "utils/telemetriesProxy.h"
#include "utils/telemetryTask.h"
#include "utils/hi_log.h"
#include "utils/hi_time.h"
#include "dab/dab_api_telemetry.h"

using namespace std;

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
    
    bool ret = TelemetriesProxy::startDeviceTelemetry(duration);
    if (!ret) {
        context.clientFail(" device telemetry is started, could not start again");
        return;
    }
	context.response.append("duration", duration);
	context.success();
}

void DABHandler::stopDeviceTelemetry(DABContext& context) {
    FUN_LOG();
	bool ret = TelemetriesProxy::stopDeviceTelemetry();
    if (!ret) {
        context.clientFail("device telemetry is not started, could not stop");
        return;
    }
	context.success();
}

void DABHandler::startAppTelemetry(DABContext& context) {
    FUN_LOG();
	int duration = context.request.getIntValue("duration");
	if (duration < 0) {
		context.clientFail("start app telemetry request not include duration");
		return;
	}
	
	if (duration < 100) {
		context.clientFail("in start app telemetry request, duration must > 100ms");
		return;
	}

	string appId = context.request.getStringValue("appId");
	if (appId.empty()) {
        context.clientFail("not include appId");
        return;
	}
    
    bool ret = TelemetriesProxy::startAppTelemetry(appId, duration);
    if (!ret) {
        context.clientFail(" device telemetry is started, could not start again");
        return;
    }
	context.response.append("duration", duration);
	context.success();
}

void DABHandler::stopAppTelemetry(DABContext& context) {
	string appId = context.request.getStringValue("appId");
	if (appId.empty()) {
        context.clientFail("not include appId");
        return;
	}
	bool ret = TelemetriesProxy::stopAppTelemetry(appId);
    if (!ret) {
        context.clientFail(" app telemetry is not started, could not stop");
        return;
    }
	context.success();
}

void DABHandler::stopTelemetry() {
    FUN_LOG();
    TelemetryTask::stop();
}

namespace {
	void publishCPU(const string& topic, float cpu) {
		Json::Value root;
		root["metric"] = "cpu";
		root["value"] = cpu;
		root["timestamp"] = dab::currentMs();

		Json::FastWriter fastWriter;
		string body = fastWriter.write(root);
		DABContext::publish(topic.c_str(), body.c_str());
	}

	void publishMemory(const string& topic, int memory) {
		Json::Value root;
		root["metric"] = "memory";
		root["value"] = memory;
		root["timestamp"] = dab::currentMs();

		Json::FastWriter fastWriter;
		string body = fastWriter.write(root);
		DABContext::publish(topic.c_str(), body.c_str());
	}
	void publishAppTelemetry(const string& appId) {
		string topic = DABHandler::getTelemetryTopic(appId.c_str());
		float cpu = 0.0;
		if (dab_api_getAppCPU(appId.c_str(), cpu)) {
			publishCPU(topic, cpu);
		} else {
			DABLOG_ERROR("get app [%s] cpu failed", appId.c_str());
		}
		int memory = 0;
		if (dab_api_getAppMemory(appId.c_str(), memory)) {
			publishMemory(topic, memory);
		} else {
			DABLOG_ERROR("get app [%s] memory failed", appId.c_str());
		}
	}
	void publishDeviceTelemetry() {
		string topic = DABHandler::getTelemetryTopic(nullptr);
		float cpu = 0.0;
		if (dab_api_getDeviceCPU(cpu)) {
			publishCPU(topic, cpu);
		} else {
			DABLOG_ERROR("get device cpu failed");
		}
		int memory = 0;
		if (dab_api_getDeviceMemory(memory)) {
			publishMemory(topic, memory);
		} else {
			DABLOG_ERROR("get device memory failed");
		}
	}
}

void DABHandler::startTelemetry() {
    FUN_LOG();
    TelemetryTask::start([](const string& appId){		
		if (TelemetriesProxy::isDevice(appId)) {
			publishDeviceTelemetry();
		} else {
			publishAppTelemetry(appId);
		}
	});
}