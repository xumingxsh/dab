#include "context/dab_response.h"

using namespace std;

void DABResponse::append(const char* key, const string value) {
    payload[key]=  value;
}

void DABResponse::append(const char* key, int value) {
    payload[key]=  value;
}

void DABResponse::append(const char* key, float value) {
    payload[key]=  value;
}

void DABResponse::append(const char* key, bool value) {
    payload[key]=  value;
}

void DABResponse::append(const char* key, long long value) {
    payload[key]=  value;
}

void DABResponse::append(const char* key, Json::Value& value) {
    payload[key]=  value;
}

void DABResponse::append(const char* key, const vector<string>& list) {
    if (list.size() < 1) {
        return;
    }
    Json::Value jsonArray;
    for (int i = 0; i < list.size(); i++) {
        jsonArray.append(list[i]);
    }  
    payload[key]=  jsonArray;
}