#include "dab/dab_api_device.h"

using namespace std;

string dab_api_deviceId() {
    return "abcdefghikjh234234234";
}
string dab_api_manufacturer() {
    return "DEVICE";
}
string dab_api_model() {
    return "72690";
}
string dab_api_serialNumber() {
    return "abcdefghikjh234234234";
}
string dab_api_chipset() {
    return "chipsetNo.";
}
string dab_api_firmwareVersion() {
    return "V0.0.0.6";
}
string dab_api_firmwareBuild() {
    return "20240313";
}
bool dab_api_getScreenPixels(int& width, int height) {
	width = 1920;
	height = 1080;
    return true;
}
long long dab_api_uptimeSince() {
    return 12345678;
}

bool dab_api_getDisplayType(DABDisplayType& type) {
	type = DABDisplayType::Native;
    return true;
}