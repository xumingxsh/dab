#include "dab/dab_api_voice.h"
#include "utils/hi_log.h"

using namespace std;

bool dab_api_listVoices(std::map<std::string, bool>& voices) {
	voices["GoogleAssistant"] = true;
	voices["AmazonAlexa"] = false;
    return true;
}
bool dab_api_setVoice(const char* voice, bool enabled) {
    FUN_LOG();
	DABLOG_INFO("voice:%s,enabled:%d", voice, enabled);
    return true;
}
bool dab_api_sendAudio2voice(const char* voice, const char* audioUrl) {
    FUN_LOG();
	DABLOG_INFO("voice:%s,audioUrl:%s", voice, audioUrl);
    return true;
}
bool dab_api_sendText2voice(const char* voice, const char* text) {
    FUN_LOG();
	DABLOG_INFO("voice:%s,text:%s", voice, text);
    return true;
}