#include "dab/dab_handler.h"
#include "dab/dab_api_device.h"
#include "dab/dab_api_system.h"
#include "dab/dab_api_network.h"

using namespace std;

namespace {
	string getDisplayType(DABDisplayType type) {
		switch(type) {
			case DABDisplayType::Native:
				return "Native";
			case DABDisplayType::External:
				return "External";
			default:
				return "Native";

		}
	}

	string getNetType(DABNetworkType type) {
		switch(type) {
		case DABNetworkType::Ethernet: return "Ethernet";
		case DABNetworkType::Wifi: return "Wifi";
		case DABNetworkType::Bluetooth: return "Bluetooth";
		case DABNetworkType::Coax: return "Coax";
		default: return "Other";
		}
	}

	Json::Value getNetworks(const map<DABNetworkType, DABNetworkInfo>& nets) {
		Json::Value array;
		for (const auto& it: nets) {
			Json::Value val;
			val["connected"] = it.second.connected;
			val["macAddress"] = it.second.macAddress;
			val["ipAddress"] = it.second.ipAddress;
			Json::Value dns;
			for (const auto& item: it.second.dns) {
				dns.append(item);
			}
			val["dns"] = dns;
			val["type"] = getNetType(it.first);
			array.append(val);
		}
		return array;
	}
}

#define ON_DEVICE_INF_ATTRIBUTE(attr) \
    do { \
        std::string attr_value = dab_api_##attr(); \
        if (attr_value.empty()) { \
            context.serverFail("get device information failed in server, can't get " #attr); \
            return; \
        } \
        context.response.append(#attr, attr_value.c_str()); \
    } while (0)

void DABHandler::getDeviceInfo(DABContext& context) {
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
	
	map<DABNetworkType, DABNetworkInfo> nets;
	if (!dab_api_getNetworks(nets)) {
        context.serverFail("get device information failed in server, can't get network information");
		return;
	} 
	Json::Value arr = getNetworks(nets);
	context.response.append("networkInterfaces", arr);
	context.success();
}

void DABHandler::reboot(DABContext& context) {
	if (!dab_api_reboot()) {
        context.serverFail("reboot device failed in server");
		return;
	}
	context.success();
}