#include "dab/dab_handler.h"

#include "app_attributies.h"
#include "dab/dab_api_voice.h"
#include <jsoncpp/json.h>

using namespace std;

void DABHandler::getVoiceList(DABContext& context) {
	std::map<std::string, bool> voices;
	if (!dab_api_listVoices(voices)) {
        context.serverFail("get getVoiceList failed in server");
        return;
	}
    Json::Value jsonArray;
	for (auto it = voices.begin(); it != voices.end(); ++it) {
		Json::Value element;
		element["name"] = it->first;
		element["enabled"] = it->second;
		jsonArray.append(element);
	}
	context.response.append("voiceSystems", jsonArray);
	context.success();
}

void DABHandler::setVoiceStatus(DABContext& context) {
	Json::Value voiceSystem;
	if (!context.request.getValue("voiceSystem", voiceSystem)) {
        context.clientFail("setVoiceStatus request not include voiceSystem");
        return;
	}
	if (!voiceSystem.isMember("name")) {
        context.clientFail("setVoiceStatus request, voiceSystem notinclude name");
        return;
	}
	string name = voiceSystem["name"].asString();
	if (!voiceSystem.isMember("enabled")) {
        context.clientFail("setVoiceStatus request, voiceSystem notinclude enabled");
        return;
	}
	bool enabled = voiceSystem["enabled"].asBool();
	context.response.append("voiceSystem", voiceSystem);
	if (!dab_api_setVoice(name.c_str(), enabled)) {
        context.serverFail("setVoiceStatus request failed in server");
        return;
	}
	context.success();
}

void DABHandler::sendAudio2voice(DABContext& context) {
	string fileLocation = context.request.getStringValue("fileLocation");
	if (fileLocation.empty()) {
        context.clientFail("sendAudio2voice request not include fileLocation");
        return;
	}
	string voiceSystem = context.request.getStringValue("voiceSystem");

	if (!dab_api_sendAudio2voice(voiceSystem.c_str(), fileLocation.c_str())) {
        context.serverFail("sendAudio2voice request failed in server");
        return;
	}
	context.success();
}

void DABHandler::sendText2voice(DABContext& context) {
	string requestText = context.request.getStringValue("requestText");
	if (requestText.empty()) {
        context.clientFail("sendText2voice request not include requestText");
        return;
	}
	string voiceSystem = context.request.getStringValue("voiceSystem");
	if (voiceSystem.empty()) {
        context.clientFail("sendText2voice request not include voiceSystem");
        return;
	}

	if (!dab_api_sendAudio2voice(voiceSystem.c_str(), requestText.c_str())) {
        context.serverFail("sendText2voice request failed in server");
        return;
	}
	context.success();
}