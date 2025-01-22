
#include <unistd.h>
#include "app_attributies.h"
#include <functional>
 
using namespace std;
extern "C" int runDabService();

extern "C" void setAppAttributes(const function<void()>& func);

static void init_attributies() {
    static const int MAX_THREADS_COUNT = 5;
    DABProperties::max_handle_threads   = MAX_THREADS_COUNT;
    DABProperties::device_id            = "thisisatest";
    DABProperties::device_ip            = "127.0.0.1";
    DABProperties::mqtt_ip              = "localhost";
    DABProperties::mqtt_port            = 1883;
    DABProperties::mqtt_user            = "";
    DABProperties::mqtt_password        = "";
    DABProperties::mqtt_client_id       = DABProperties::device_id;
}

int WinMain() {
    setAppAttributes([]{
        init_attributies();
    });
    if (runDabService() == 0) {
        sleep(40000000);
    }
    return 0;
}