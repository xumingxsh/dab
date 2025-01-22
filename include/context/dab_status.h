#ifndef __NT_APP_DAB_STATUS_H__
#define __NT_APP_DAB_STATUS_H__

#include <string>
 
class DABStatus {
public:
    DABStatus();
    bool is_ok() const;
    void clientFail(const char* out_log, const char* inner_log = nullptr);
    void serverFail(const char* out_log, const char* inner_log = nullptr);
    int getStatus() const;
public:
    bool is_exception;
    bool is_server_exception;
    std::string inner_log;
    std::string out_log;
};
#endif // __NT_APP_DAB_STATUS_H__
