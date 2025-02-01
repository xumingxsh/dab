#include "dab/dab_api_network.h"

using namespace std;

bool dab_api_getNetworks(map<DABNetworkType, DABNetworkInfo>& nets) {
	DABNetworkInfo info;
	info.connected = true;
	info.macAddress = "00-11-22-33-44-55";
	info.ipAddress = "127.0.0.1";
	info.dns.push_back("8.8.8.8");
	info.dns.push_back("114.114.114.114");
	nets[DABNetworkType::Ethernet] = info;
	DABNetworkInfo info2;
	info2.connected = true;
	info2.macAddress = "55-11-22-33-44-55";
	info.ipAddress = "127.0.0.1";
	nets[DABNetworkType::Wifi] = info2;
	return true;
}