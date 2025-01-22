#include "dab/dab_api_system.h"
#include "utils/hi_log.h"

using namespace std;

bool dab_api_reboot() {
    FUN_LOG();
    return true;
}

// IVServiceAPI:setVolumeValue, getVolumeValue 
bool dab_api_getVolumnRange(int& min, int& max) {
    FUN_LOG();
	min = 0;
	max = 100;
    return true;
}
bool dab_api_getVolumn(int& val) {
    FUN_LOG();
	val = true;
    return true;
}
bool dab_api_setVolumn(int val) {
    FUN_LOG();
    return true;
}

// IVServiceAPI:getMuteState,setMuteState
bool dab_api_supportMute() {
    FUN_LOG();
    return true;
}
bool dab_api_getMute(bool& val) {
    FUN_LOG();
	val = true;
    return true;
}
bool dab_api_setMute(bool val) {
    FUN_LOG();
    return true;
}

bool dab_api_supportTextToSpeech() {
    FUN_LOG();
    return true;
}
bool dab_api_getTextToSpeech(bool& val) {
    FUN_LOG();
	val = true;
    return true;
}
bool dab_api_setTextToSpeech(bool val) {
    FUN_LOG();
    return true;
}

bool dab_api_spuuportMemc() {
    FUN_LOG();
    return true;
}
bool dab_api_getMemc(bool& val) {
    FUN_LOG();
	val = true;
    return true;
}
bool dab_api_setMemc(bool val) {
    FUN_LOG();
    return true;
}

bool dab_api_supportCec() {
    FUN_LOG();
    return true;
}
bool dab_api_getCec(bool& val) {
    FUN_LOG();
	val = true;
    return true;
}
bool dab_api_setCec(bool val) {
    FUN_LOG();
    return true;
}

bool dab_api_supportLowLatencyMode() {
    FUN_LOG();
    return true;
}
bool dab_api_getLowLatencyMode(bool& val) {
    FUN_LOG();
	val = true;
    return true;
}
bool dab_api_setLowLatencyMode(bool val) {
    FUN_LOG();
    return true;
}


bool dab_api_listLanguageOptions(std::vector<std::string>& list) {
    FUN_LOG();
	list.push_back("eu");
	list.push_back("sp");
    return true;
}
bool dab_api_getLanguage(std::string& language) {
    FUN_LOG();
	language = "eu";
    return true;
}
bool dab_api_setLanguage(const char* language) {
    FUN_LOG();
    return true;
}

bool dab_api_listOutputResolutionOptions(std::vector<DABOutputResolution>& list) {
    FUN_LOG();
	DABOutputResolution item;
	item.width = 1920;
	item.height = 1080;
	item.frequency = 60;
	list.push_back(item);
    return true;
}
bool dab_api_getOutputResolution(DABOutputResolution& val) {
    FUN_LOG();
	val.width = 1920;
	val.height = 1080;
	val.frequency = 60; 
    return true;
}
bool sdab_api_etOutputResolution(const DABOutputResolution val) {
    FUN_LOG();
    return true;
}

bool dab_api_listMatchContentFrameRateOptions(std::vector<DABMatchContentFrameRate>& list) {
    FUN_LOG();
	list.push_back(DABMatchContentFrameRate::EnabledAlways);
	list.push_back(DABMatchContentFrameRate::EnabledSeamlessOnly);
    return true;
}
bool dab_api_getMatchContentFrameRate(DABMatchContentFrameRate& val) {
    FUN_LOG();
	val = DABMatchContentFrameRate::EnabledAlways;
    return true;
}
bool dab_api_setMatchContentFrameRate(const DABMatchContentFrameRate& val) {
    FUN_LOG();
    return true;
}

bool dab_api_listHdrOutputModeOptions(std::vector<DABHdrOutputMode>& list) {
    FUN_LOG();
    return true;
}
bool dab_api_getHdrOutputMode(DABHdrOutputMode& val) {
    FUN_LOG();
    return true;
}
bool dab_api_stHdrOutputMode(const DABHdrOutputMode val) {
    FUN_LOG();
    return true;
}

bool dab_api_listPictureModeOptions(std::vector<DABPictureMode>& list) {
    FUN_LOG();
	list.push_back(DABPictureMode::Standard);
	list.push_back(DABPictureMode::Dynamic);
    return true;
}
bool dab_api_getPictureMode(DABPictureMode& val) {
    FUN_LOG();
	val = DABPictureMode::Standard;
    return true;
}
bool dab_api_setPictureMode(const DABPictureMode val) {
    FUN_LOG();
    return true;
}

bool dab_api_listAudioOutputModeOptions(std::vector<DABAudioOutputMode>& list) {
    FUN_LOG();
	list.push_back(DABAudioOutputMode::Stereo);
	list.push_back(DABAudioOutputMode::MultichannelPcm);
    return true;
}
bool dab_api_getAudioOutputMode(DABAudioOutputMode& val) {
    FUN_LOG();
	val = DABAudioOutputMode::Stereo;
    return true;
}
bool dab_api_setAudioOutputMode(const DABAudioOutputMode val) {
    FUN_LOG();
    return true;
}
bool dab_api_listAudioOutputSourceOptions(std::vector<DABAudioOutputSource>& list) {
    FUN_LOG();
	list.push_back(DABAudioOutputSource::NativeSpeaker);
	list.push_back(DABAudioOutputSource::Arc);
    return true;
}
bool dab_api_getAudioOutputSource(DABAudioOutputSource& val) {
    FUN_LOG();
	val = DABAudioOutputSource::NativeSpeaker;
    return true;
}
bool dab_api_setAudioOutputSource(const DABAudioOutputSource val) {
    FUN_LOG();
    return true;
}

bool dab_api_listVideoInputSourceOptions(std::vector<DABVideoInputSource>& list) {
    FUN_LOG();
	list.push_back(DABVideoInputSource::HDMI1);
	list.push_back(DABVideoInputSource::HDMI2);
	list.push_back(DABVideoInputSource::Tuner);
    return true;
}
bool dab_api_getVideoInputSource(DABVideoInputSource& val) {
    FUN_LOG();
	val = DABVideoInputSource::HDMI1;
    return true;
}
bool dab_api_setVideoInputSource(const DABVideoInputSource val) {
    FUN_LOG();
    return true;
}