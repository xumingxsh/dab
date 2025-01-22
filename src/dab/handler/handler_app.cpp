#include "dab/dab_handler.h"

#include "dab/dab_api_app.h"
#include <jsoncpp/json.h>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

namespace {
string convert(DABAppStatus status) {
	switch(status) {
		case DABAppStatus::STOPPED:
			return "STOPPED";
		case DABAppStatus::FOREGROUND:
			return "FOREGROUND";
		case DABAppStatus::BACKGROUND:
			return "BACKGROUND";
		default:
			return "STOPPED";
	}
}

string getStatus(const char* appId) {
	DABAppStatus status;
	bool ret = dab_api_getAppStatus(appId, status);
	if (!ret) {
		return "";
	}
	return convert(status);
}
} // namespace

void DABHandler::getAppList(DABContext& context) {
	vector<DABAppInfo> list;
	if (!dab_api_getApplications(list)) {
        context.serverFail("get applications list failed in server");
        return;
	}
	
    Json::Value jsonArray;
	for (auto it = list.begin(); it != list.end(); ++it) {
		Json::Value item;
		item["appId"] = it->appId;
		if (!it->friendlyName.empty()) {
			item["friendlyName"] = it->friendlyName;
		}
		if (!it->version.empty()) {
			item["version"] = it->version;
		}
		jsonArray.append(item);
	}
	context.response.append("applications", jsonArray);
	context.success();
}

void DABHandler::launch(DABContext& context) {
	string appId = context.request.getStringValue("appId");
	if (appId.empty()) {
        context.clientFail("application launch request not include appId");
        return;
	}

	vector<string>  parameters;
	context.request.getValue("parameters", parameters);
	bool ret = dab_api_launch(appId.c_str(), parameters, nullptr);
	if (!ret) {
        context.serverFail("launch applications failed in server");
		return;
	}
	context.success();
}

void DABHandler::launchByContent(DABContext& context) {	
	string appId = context.request.getStringValue("appId");
	if (appId.empty()) {
        context.clientFail("application launchByContent request not include appId");
        return;
	}

	vector<string>  parameters;
	context.request.getValue("parameters", parameters);
	string contentId  = context.request.getStringValue("contentId");
	if (contentId.empty()) {
        context.clientFail("application launchByContent with content request not include contentId");
        return;
	}
	bool ret = dab_api_launch(appId.c_str(), parameters, contentId.c_str());
	if (!ret) {
        context.serverFail("launch applications failed in server");
		return;
	}
	context.success();
}

void DABHandler::exitApp(DABContext& context) {
	string appId = context.request.getStringValue("appId");
	if (appId.empty()) {
        context.clientFail("exit application request not include appId");
        return;
	}

	bool backgrond = false;
	context.request.getValue("background", backgrond);
	bool ret = dab_api_exitApp(appId.c_str(), backgrond);
	if (!ret) {
        context.serverFail("exit applications failed in server");
		return;
	}
    string status = getStatus(appId.c_str());
	if (status.empty()) {
        context.serverFail("get applications status failed in server");
		return;
	}
	context.response.append("state", status.c_str());
	context.success();
}

void DABHandler::getAppStatus(DABContext& context) {
	string appId = context.request.getStringValue("appId");
	if (appId.empty()) {
        context.clientFail("get application status request not include appId");
        return;
	}
    string status = getStatus(appId.c_str());
	if (status.empty()) {
        context.serverFail("get applications status failed in server");
		return;
	}
	context.response.append("state", status.c_str());
	context.success();
}