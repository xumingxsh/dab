#pragma once

#include <vector>
#include <string>

struct DABAppInfo {
	std::string appId;
	std::string friendlyName;
	std::string version;
};
enum class DABAppStatus {
	STOPPED,
	FOREGROUND,
	BACKGROUND,
};

extern "C" {
	bool dab_api_getApplications(std::vector<DABAppInfo>& list);	
	bool dab_api_launch(const char* appId, const std::vector<std::string>& params, const char* contentId);
	bool dab_api_exitApp(const char* appId, bool background);
	bool dab_api_getAppStatus(const char* appId, DABAppStatus& status);

	std::string dab_api_converDABApp2DeviceApp(const char* dabApp);
}