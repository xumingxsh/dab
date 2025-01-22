#pragma once

#include <string>
#include <vector>

extern "C" {
    bool dab_api_getKeyList(std::vector<std::string>& list);
    bool dab_api_pressKey(const char* key, int durationMs);
    bool dab_api_catpureImage2png(const char* file);
}