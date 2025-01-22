#ifndef __NT_DAB_CONTEXT_H__
#define __NT_DAB_CONTEXT_H__

#include <string>
#include <vector>
#include <functional>
#include <jsoncpp/json.h>
#include "context/dab_status.h"
#include "context/dab_request.h"
#include "context/dab_response.h"
 
class DABContext {
public:
    DABContext(const char* topic, const char* request, const char* reponse_topic, const char* correlation_data);
    DABContext(DABContext&&) = delete;
public:
    bool is_ok() const;
    void success();
    void clientFail(const char* out_log, const char* inner_log = nullptr);
    void serverFail(const char* fmt, ...);
public:
	std::string toJson();
	static void setPublishFunc(const std::function<void(const char*, const char*)>& func);
    static void publish(DABContext& context);
    static void publish(const char* topic, const char* body);
public:
    DABStatus status;
    DABRequest request;
    DABResponse response;
};

#endif // __NT_DAB_CONTEXT_H__
