#include "dab/dab_api_voice.h"
#include "utils/hi_log.h"

using namespace std;

bool dab_api_listVoices(std::map<std::string, bool>& voices) {
	voices["vidaa_voice"] = true;
	voices["alixsa_voice"] = false;
    return true;
}
bool dab_api_setVoice(const char* voice, bool enabled) {
    FUN_LOG();
    return true;
}
bool dab_api_sendAudio2voice(const char* voice, const char* audioUrl) {
    FUN_LOG();
    return true;
}
bool dab_api_sendText2voice(const char* voice, const char* text) {
    FUN_LOG();
    return true;
}