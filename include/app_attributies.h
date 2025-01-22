#ifndef __NT_APP_ATTRIBUTES_H__
#define __NT_APP_ATTRIBUTES_H__

#include <string>

class DABProperties {
public:
    static int max_handle_threads;
    static std::string device_id;
    static std::string device_ip;
    
    static std::string mqtt_ip;
    static int mqtt_port;
    static std::string mqtt_user;
    static std::string mqtt_password;
    static std::string mqtt_client_id;
public:
    static void check_init();
    static void set_mqtt_attributes(int port, const char* user, const char* password, const char* clientId);
private:
    DABProperties() = delete;
};

#endif // __NT_APP_ATTRIBUTES_H__
