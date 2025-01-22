#ifndef __NT_APP_DAB_REQUEST_H__
#define __NT_APP_DAB_REQUEST_H__

#include <string>
#include <jsoncpp/json.h>
#include "context/dab_status.h"
 
class DABRequest {
public:
    std::string topic;
    std::string request_topic;
    std::string response_topic;
    std::string correlationData;
    Json::Value request_payload;
public:
    void setDABStatus(DABStatus* dabStatus);
    void init(const char* request);
    bool getValue(const char* path, std::vector<std::string>& list);
    bool getValue(const char* path, bool& val);
    bool getValue(const char* path, Json::Value& value);
    int getIntValue(const char* key,  int defaultVal = -1);
    std::string getStringValue(const char* key, const char* defaultVal = "");
private:
    DABStatus* dab_status;
};
#endif // __NT_APP_DAB_REQUEST_H__
