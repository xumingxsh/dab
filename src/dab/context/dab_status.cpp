#include "context/dab_status.h"
DABStatus::DABStatus(): is_exception(false), is_server_exception(false) {
}
bool DABStatus::is_ok() const {
    return !is_exception;
}

int DABStatus::getStatus() const {
    if (is_ok()) {
        return 200;
    } else if(is_server_exception) {
        return 500;
    } else {
        return 400;
    }
}
void DABStatus::clientFail(const char* outLog, const char* innerLog) {
    is_exception = true;
    is_server_exception = false;
    if (innerLog) {
        inner_log = innerLog;
    }
    if (outLog) {
        out_log = outLog;
    }
}
void DABStatus::serverFail(const char* outLog, const char* innerLog) {    
    is_exception = true;
    is_server_exception = true;
    if (innerLog) {
        inner_log = innerLog;
    }
    if (outLog) {
        out_log = outLog;
    }
}
