#include "dab/dab_handler.h"

#include "app_attributies.h"
#include "dab/dab_api_io.h"

#include <vector>

using namespace std;

void DABHandler::getKeyList(DABContext& context) {
    vector<string>  keys;
    if (!dab_api_getKeyList(keys)) {
        context.serverFail("get key list failed in server");
        return;
    }
    context.response.append("keyCodes", keys);
    context.success();
}

void DABHandler::keyPress(DABContext& context) {
    string keyCode = context.request.getStringValue("keyCode");
    if (keyCode.empty()) {
        context.clientFail("keyPress request not include keyCode");
        return;
    }
    if (!dab_api_pressKey(keyCode.c_str(), 0)) {
        context.serverFail("keyPress failed in server");
        return;
    }
    context.success();
}

void DABHandler::keyPressByLongTime(DABContext& context) {
    string keyCode = context.request.getStringValue("keyCode");
    if (keyCode.empty()) {
        context.clientFail("long keyPress request not include keyCode");
        return;
    }
    int durationMs = context.request.getIntValue("durationMs");
    if (durationMs < 0) {
        context.clientFail("long press request not include durationMs element");
        return;
    }
    if (!dab_api_pressKey(keyCode.c_str(), durationMs)) {
        context.serverFail("long press failed in server");
        return;
    }
    context.success();
}

void DABHandler::capture(DABContext& context) {
	string base64;;
	if (!dab_api_catpureImage2png(base64)) {
        context.serverFail("capture failed in server");
        return;
	}
	stringstream oss;
	oss<<"data:image/png;base64,"<<base64;
	context.response.append("outputImage", oss.str().c_str());
	context.success();
}