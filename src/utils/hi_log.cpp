#include "utils/hi_log.h"
#include <stdarg.h>
#include <cstdio>
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <ratio>
#include <iostream>

using namespace std;

const static int MAX_BUF_SIZE = 2048;

static string getFile(const char* file);
static string getTime();

static void default_log(DABLogLevel level, const char* file, const char* func, 
    int line, const char* msg) {
    printf("%s [%s:%s:%d]%s\n", getTime().c_str(), getFile(file).c_str(), func, line, msg);
}

static function<void(DABLogLevel, const char*, 
    const char*, int, const char*)> log_func = default_log;

namespace dab {
void set_log_callback(const 
    std::function<void
        (DABLogLevel, const char*, const char*, int, const char*)>& 
    callback) {
    log_func = callback;
}

void writeLog(DABLogLevel level, 
            const char* file, 
            const char* function, 
            int line, 
            const char* fmt, ...) {

    char chArr[MAX_BUF_SIZE] = {0};
    va_list arguments;
    va_start(arguments, fmt);
    vsnprintf(chArr, MAX_BUF_SIZE, fmt, arguments);
    va_end(arguments);

    log_func(level, file, function, line, chArr);
}


FunctionLog::FunctionLog(const char* file, const char* function,  int line) {
	name_ = function;
	file_ = file;
	writeLog(DABLogLevel::INFO, file, function, line, "enter");
}
FunctionLog::~FunctionLog() {
	writeLog(DABLogLevel::INFO, file_.c_str(), name_.c_str(), 0, "leave");
}

// When using it, replace the implementation of the function according to the actual situation.
static bool allowAssert() {
#ifdef NDEBUG
	return false;
#endif
	return true;
}

void on_assert_fail(const char* file, const char* function,  int line) {
    std::cerr << "Assertion failed!\n"
              << "File: " << file << "\n"
              << "Function: " << function << "\n"
              << "Line: " << line << std::endl;
	if (allowAssert()) {
		std::abort();
	}
}
}

static string getFile(const char* path) {
    string file = path;
    std::string::size_type pos = file.find_last_of("/");
    if (pos > 0) {
        return file.substr(pos + 1);
    }
    return file;
}

static string getTime() {
    auto now = std::chrono::system_clock::now(); 
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000; 
    stringstream oss;
    oss<<std::put_time(std::localtime(&now_time), "H:%M:%S")<<
        "." << std::setfill('0') << std::setw(3) << ms.count();
    return oss.str();        
}