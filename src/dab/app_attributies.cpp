#include "app_attributies.h"
#include "utils/hi_log.h"

int DABProperties::max_handle_threads = 5;
std::string DABProperties::device_id;
std::string DABProperties::device_ip;
    
std::string DABProperties::mqtt_ip = "127.0.0.1";
int DABProperties::mqtt_port;
std::string DABProperties::mqtt_user;
std::string DABProperties::mqtt_password;
std::string DABProperties::mqtt_client_id;

void DABProperties::check_init() {
    DAB_ASSERT(!DABProperties::device_id.empty(), "not set deivce id");
    DAB_ASSERT(!DABProperties::device_ip.empty(), "not set mqtt ip");
    //DAB_ASSERT(!DABProperties::mqtt_client_id.empty());
}