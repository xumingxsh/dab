#include "dab/dab_handler.h"
#include "dab/dab_api_device.h"
#include "dab/dab_api_system.h"

using namespace std;

static string getDisplayType(DABDisplayType type) {
	switch(type) {
		case DABDisplayType::Native:
			return "Native";
		case DABDisplayType::External:
			return "External";
		default:
			return "Native";

	}
}

#define ON_DEVICE_INF_ATTRIBUTE(attr) \
	string attr = dab_api_##attr(); \
	if (attr.empty()) { \
        context.serverFail("get device information failed in server, can't get #attr"); \
		return; \
	} \
	context.response.append("#attr", attr.c_str())

void DABHandler::getDeviceInfo(DABContext& context) {
	DAB_NOT_IMPLEMENT(context);
	ON_DEVICE_INF_ATTRIBUTE(manufacturer);
	ON_DEVICE_INF_ATTRIBUTE(deviceId);
	ON_DEVICE_INF_ATTRIBUTE(model);
	ON_DEVICE_INF_ATTRIBUTE(serialNumber);
	ON_DEVICE_INF_ATTRIBUTE(chipset);
	ON_DEVICE_INF_ATTRIBUTE(firmwareVersion);
	ON_DEVICE_INF_ATTRIBUTE(firmwareBuild);
	int width = 0;
	int height = 0;
	if (!dab_api_getScreenPixels(width, height)) {
        context.serverFail("get device information failed in server, can't get ScreenPixels");
		return;
	}
	context.response.append("screenWidthPixels", width);
	context.response.append("screenHeightPixels", height);
	long long uptimeSince = dab_api_uptimeSince();
	if (uptimeSince < 0) {
        context.serverFail("get device information failed in server, can't uptimeSince");
		return;
	}
	context.response.append("uptimeSince", uptimeSince);
	DABDisplayType type;
	if (!dab_api_getDisplayType(type)) {
        context.serverFail("get device information failed in server, can't displayType");
		return;
	}
	context.response.append("displayType", getDisplayType(type).c_str());
}

void DABHandler::reboot(DABContext& context) {
	DAB_NOT_IMPLEMENT(context);
}