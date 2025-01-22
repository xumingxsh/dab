#include "context/dab_request.h"
#include <cassert>

using namespace std;
void DABRequest::setDABStatus(DABStatus* status) {
    dab_status = status;
}

void DABRequest::init(const char* request) {
    assert(dab_status);
    Json::Reader requestReader;
    Json::Value requestRoot;
    if (!requestReader.parse(request, requestRoot)) {
        dab_status->clientFail("The request information is not a valid JSON string.");
        return;
    }
    request_payload = requestRoot;
}

string DABRequest::getStringValue(const char* key, const char* defaultVal) {  
    if (!request_payload.isMember(key)) {
        return defaultVal;
    }
    return request_payload[key].asString();
}

int DABRequest::getIntValue(const char* key,  int defaultVal) {
    if (!request_payload.isMember(key)) {
        return defaultVal;
    }
    return request_payload[key].asInt();
}

bool DABRequest::getValue(const char* path, bool& val) {
    if (!request_payload.isMember(path)) {
        return false;
    }
    val = request_payload[path].asBool();
    return true;
}

bool DABRequest::getValue(const char* path, std::vector<std::string>& list) {
    if (!request_payload.isMember(path)) {
        return false;
    }
    
    Json::Value  root = request_payload[path];
    for (unsigned int i = 0; i < root.size(); i++) {
        list.push_back(root[i].asString());
    }
    return true;
}

bool DABRequest::getValue(const char* path, Json::Value& value) {
    if (!request_payload.isMember(path)) {
        return false;
    }
    value = request_payload[path];
    return true;
}