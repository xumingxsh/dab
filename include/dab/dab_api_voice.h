#pragma once

#include <string>
#include <map>

extern "C" {
    bool dab_api_listVoices(std::map<std::string, bool>& voices);
    bool dab_api_setVoice(const char* voice, bool enabled);
    bool dab_api_sendAudio2voice(const char* voice, const char* audioUrl);
    bool dab_api_sendText2voice(const char* voice, const char* text);
}