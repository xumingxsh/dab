#include "dab/dab_api_app.h"

#include <cstring>
#include <numeric> 

#include "utils/hi_log.h"

using namespace std;

bool dab_api_getApplications(vector<DABAppInfo>& list) {
    FUN_LOG();
	DABAppInfo app;
	app.appId = "YouTube";
	app.friendlyName = "YouTube";
	list.push_back(app);
	app.appId = "Netflix";
	app.friendlyName = "Netflix";
	list.push_back(app);
	app.appId = "PrimeVideo";
	app.friendlyName = "PrimeVideo";
	list.push_back(app);
	return true;
}

bool dab_api_launch(const char* appId, const vector<string>& params, const char* contentId) {
    FUN_LOG();
	string paramStr = std::accumulate(params.begin(), params.end(), std::string());
	DABLOG_INFO("appId:%s,params:%s,contentId:%s", appId, paramStr.c_str(), contentId);
	return true;
}

bool dab_api_exitApp(const char* appId, bool background) {
    FUN_LOG();
	DABLOG_INFO("appId:%s,background:%d", appId, background);
	return true;
}
bool dab_api_getAppStatus(const char* appId, DABAppStatus& status) {
    FUN_LOG();
	status = DABAppStatus::FOREGROUND;
	DABLOG_INFO("appId:%s,background:%d", appId, status);
	return true;
}