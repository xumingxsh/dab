#pragma once

#include <string>
#include <functional>

enum class DABLogLevel {
    INFO,
    WARNING,
    ERROR,
    FATAL,
    ALWAYS 
};

namespace dab {
void set_log_callback(const 
    std::function<void(DABLogLevel, 
        const char*, 
        const char*, 
        int, 
        const char*)>& callback);

void writeLog(DABLogLevel level, 
            const char* file, 
            const char* function, 
            int line, 
            const char* fmt, 
            ...);

class FunctionLog {
public:
    FunctionLog(const char* file, const char* function,  int line);
    ~FunctionLog();
private:
    std::string file_;
    std::string name_;
};
void on_assert_fail(const char* file, const char* function,  int line);
}

#define DABLOG_INFO(format, ...) dab::writeLog(DABLogLevel::INFO, __FILE__,__FUNCTION__, __LINE__, format, ##__VA_ARGS__)
#define DABLOG_WARNING(format, ...) dab::writeLog(DABLogLevel::WARNING, __FILE__,__FUNCTION__, __LINE__, format, ##__VA_ARGS__)
#define DABLOG_ERROR(format, ...) dab::writeLog(DABLogLevel::ERROR, __FILE__,__FUNCTION__, __LINE__, format, ##__VA_ARGS__)
#define DABLOG_ALWAYS(format, ...) dab::writeLog(DABLogLevel::ALWAYS, __FILE__,__FUNCTION__, __LINE__, format, ##__VA_ARGS__)
#define DABLOG_FATAL(format, ...) dab::writeLog(DABLogLevel::ALWAYS, __FILE__,__FUNCTION__, __LINE__, format, ##__VA_ARGS__)

#define FUN_LOG() dab::FunctionLog fun_log_##__LINE__(__FILE__, __FUNCTION__, __LINE__)

#define DAB_ASSERT(expr, desc) \
    do { \
        if (!(expr)) { \
			DABLOG_FATAL(desc);\
			dab::on_assert_fail(__FILE__, __FUNCTION__, __LINE__); \
        } \
    } while (0)
	

#define UN_RE_ENTER() \
    static bool isEntered = false; \
	if (isEntered) { \
		return; \
    } \
	isEntered = true
