#ifndef __NT_APP_DAB_RESPONSE_H__
#define __NT_APP_DAB_RESPONSE_H__

#include <string>
#include <vector>
#include <functional>
#include <jsoncpp/json.h>
 

class DABResponse {
public:
    void append(const char* key, const char* value);
    void append(const char* key, int value);
    void append(const char* key, float value);
    void append(const char* key, long long value);
    void append(const char* key, bool value);
    void append(const char* key, const std::vector<std::string>& list);
    void append(const char* key, Json::Value& value);
public:
    Json::Value payload;
};

#endif // __NT_APP_DAB_RESPONSE_H__
