#include "dab/dab_api_app.h"

#include <cstring>
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
	return true;
}

bool dab_api_exitApp(const char* appId, bool background) {
    FUN_LOG();
	return true;
}
bool dab_api_getAppStatus(const char* appId, DABAppStatus& status) {
    FUN_LOG();
	status = DABAppStatus::FOREGROUND;
	return true;
}