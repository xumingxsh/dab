#include "dab/dab_api_io.h"

using namespace std;

bool dab_api_getKeyList(vector<string>& list) {
	list.push_back("KEY_POWER");
    list.push_back("KEY_HOME");
    list.push_back("KEY_MENU");
    list.push_back("KEY_EXIT");
    list.push_back("KEY_INFO");
    list.push_back("KEY_UP");
    list.push_back("KEY_RIGHT");
    list.push_back("KEY_DOWN");
    list.push_back("KEY_LEFT");
    list.push_back("KEY_ENTER");
    list.push_back("KEY_BACK");
	return true;
}

bool dab_api_pressKey(const char* key, int durationMs) {
	return true;
}

bool dab_api_catpureImage2png(const char* file) {
	return true;
}