#include "dab/dab_handler.h"
#include "app_attributies.h"

using namespace std;

void DABHandler::discover(DABContext& context) {
    context.response.append("ip",        DABProperties::device_ip.c_str());
    context.response.append("deviceId",  DABProperties::device_id.c_str());
    context.success();
}

void DABHandler::version(DABContext& context) {
    vector<string> versions;
    versions.push_back("2.0");
    context.response.append("versions", versions);
    context.success();
}

void DABHandler::health_check(DABContext& context) {
    context.response.append("healthy", true);
    context.success();
}

void DABHandler::operations(DABContext& context) {
    printf("DABHandler::operations called\n");
    vector<string> list;
    DABHandler::getTopics(list);
    
    context.response.append("operations", list);
    context.success();
}

void DABHandler::reportMessage(DABContext& context) {
	DAB_NOT_IMPLEMENT(context);
}
