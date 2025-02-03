#pragma once

#include <string>
#include "dab/dab_api_system.h"

std::string convert(DABMatchContentFrameRate val);
bool convert2MatchContentFrameRate(const std::string& val, DABMatchContentFrameRate& dst);
std::string convert(DABHdrOutputMode val);
bool convert2HdrOutputMode(const std::string& val, DABHdrOutputMode& dst);
std::string convert(DABPictureMode val);
bool convert2PictureMode(const std::string& val, DABPictureMode& dst);
std::string convert(DABAudioOutputMode val);
bool convert2AudioOutputMode(const std::string& val, DABAudioOutputMode& dst);
std::string convert(DABAudioOutputSource val);
bool convert2AudioOutputSource(const std::string& val, DABAudioOutputSource& dst);
std::string convert(DABVideoInputSource val);
bool convert2VideoInputSource(const std::string& val, DABVideoInputSource& dst);