#pragma once

#include <string>
#include <map>
#include <vector>
#include "dab/dab_api.h"

enum class DABNetworkType {
   Ethernet,
   Wifi,
   Bluetooth,
   Coax,
   Other,
};

struct DABNetworkInfo {
    // IVServiceAPI:isConnected 
   bool connected;
    // IVServiceAPI:getEthernetMacAddress,getWifiMacAddress 
   std::string macAddress;
    // IVServiceAPI:getIPAddress 
   std::string ipAddress;
   std::vector<std::string> dns;
};

extern "C" {
    bool dab_api_getNetworks(std::map<DABNetworkType, DABNetworkInfo>& list);
}