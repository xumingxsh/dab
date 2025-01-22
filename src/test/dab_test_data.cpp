#include <string>
#include <sstream>
#include "app_attributies.h"

using namespace std;
static string getTopic(const char* topic) {
    stringstream oss;
    oss<<"dab/"<<DABProperties::device_id<<topic;
    return oss.str();
}

void discover_request(string& topic, string& body) {
    topic = "dab/discovery";
    stringstream oss;
    oss<<
        "{\"topic\":\""<<topic<<"\", "
        "\"correlationData\": \"abc\","
        "\"responseTopic\": \"dab/userClient-1/responses\","
        "\"payload\":{}}";
    body = oss.str();
}

void version_request(string& topic, string& body) {
    topic = getTopic("/version");
    stringstream oss;
    oss<<
        "{\"topic\":\""<<topic<<"\", "
        "\"correlationData\": \"abc\","
        "\"responseTopic\": \"dab/userClient-1/responses\","
        "\"payload\":{}}";
    body = oss.str();
}

void getOperations_request(string& topic, string& body) {
    topic = getTopic("/operations/list");
    stringstream oss;
    oss<<
        "{\"topic\":\""<<topic<<"\", "
        "\"correlationData\": \"abc\","
        "\"responseTopic\": \"dab/userClient-1/responses\","
        "\"payload\":{}}";
    body = oss.str();
}

void onAppLaunch_request(string& topic, string& body) {
    topic = getTopic("/applications/launch");
    stringstream oss;
    oss<<
        "{\"topic\":\""<<topic<<"\", "
        "\"correlationData\": \"abc\","
        "\"responseTopic\": \"dab/userClient-1/responses\","
        "\"payload\":{\"appId\":\"YouTube\"}}";
    body = oss.str();
}