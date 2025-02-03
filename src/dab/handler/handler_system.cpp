#include "dab/dab_handler.h"

#include <algorithm>
#include <jsoncpp/json.h>

#include "dab/dab_api_system.h"
#include <jsoncpp/json.h>
#include "utils/dabEnums.h"

using namespace std;

namespace {	
	Json::Value getOutputResolution(DABOutputResolution it) {
		Json::Value item;
		item["width"] = it.width;
		item["height"] = it.height;
		item["frequency"] = it.frequency;
		return item;
	}
	bool getOutputResolutionOptions(Json::Value& arr) {
		vector<DABOutputResolution> list;
		if (!dab_api_listOutputResolutionOptions(list)) {
			return false;
		}
		for (const auto& it: list) {
			arr.append(getOutputResolution(it));
		}
		return true;
	}
	template<typename T>
	vector<string> getOptions(const function<bool(vector<T>&)>& func) {
		vector<T> list;
		vector<string> arr;
		if (func(list)) {
			for (const auto& it: list) {
				arr.push_back(convert(it));
			}
		}
		return arr;
	}
	vector<string> getLanguages() {
		vector<string> languages;
		dab_api_listLanguageOptions(languages);
		return languages;
	}
	vector<string> getMatchContentFrameRateOptions() {
		return getOptions<DABMatchContentFrameRate>(dab_api_listMatchContentFrameRateOptions);
	}
	vector<string> getHdrOutputModesOptions() {
		return getOptions<DABHdrOutputMode>(dab_api_listHdrOutputModeOptions);
	}
	vector<string> getPictureModeOptions() {
		return getOptions<DABPictureMode>(dab_api_listPictureModeOptions);
	}	
	vector<string> getAudioOutputModeOptions() {
		return getOptions<DABAudioOutputMode>(dab_api_listAudioOutputModeOptions);
	}
	vector<string> getAudioOutputSourceOptions() {
		return getOptions<DABAudioOutputSource>(dab_api_listAudioOutputSourceOptions);
	}
	vector<string> getVideoInputSourceOptions() {
		return getOptions<DABVideoInputSource>(dab_api_listVideoInputSourceOptions);
	}
}

#define LIST_SYSTEM_PROPERT(key, func) \
	do {\
		vector<string> list  = func(); \
		if (list.size() < 1) { \
			context.serverFail("get %s options failed in server", key); \
			return; \
		} \
		context.response.append(key, list); \
	} while (false)

void DABHandler::listSystemSetting(DABContext& context) {
	vector<string> languages = getLanguages();
	if (languages.size() < 1) {
        context.serverFail("get languages failed in server");
		return;
	}
	context.response.append("language", languages);
	Json::Value  outputResolutions;
	if (!getOutputResolutionOptions(outputResolutions)) {
        context.serverFail("get outputResolutions failed in server");
		return;
	}
	context.response.append("outputResolution", outputResolutions);

	LIST_SYSTEM_PROPERT("matchContentFrameRate", getMatchContentFrameRateOptions);
	LIST_SYSTEM_PROPERT("hdrOutputMode", getHdrOutputModesOptions);
	LIST_SYSTEM_PROPERT("pictureMode", getHdrOutputModesOptions);
	LIST_SYSTEM_PROPERT("audioOutputMode", getAudioOutputModeOptions);
	LIST_SYSTEM_PROPERT("audioOutputSource", getAudioOutputSourceOptions);
	LIST_SYSTEM_PROPERT("videoInputSource", getVideoInputSourceOptions);
	
	int minVolume = 0;
	int maxVolume = 100;
	if (!dab_api_getVolumnRange(minVolume, maxVolume)) {
        context.serverFail("get volume range failed in server");
		return;
	}
	Json::Value audioVolume;
	audioVolume["min"] = minVolume;
	audioVolume["max"] = maxVolume;
	context.response.append("audioVolume", audioVolume);

	context.response.append("memc", dab_api_spuuportMemc());
	context.response.append("cec", dab_api_supportCec());
	context.response.append("lowLatencyMode", dab_api_supportLowLatencyMode());
	context.response.append("mute", dab_api_supportMute());
	context.response.append("textToSpeech", dab_api_supportTextToSpeech());
	context.success();
}

#define GET_SYSTEM_PROPERT(key, type, func) \
	do {\
		type t; \
		if (!func(t)) { \
			context.serverFail("get %s failed in server", key); \
			return; \
		} \
		context.response.append(key, convert(t)); \
	} while (false)

#define GET_SYSTEM_PROPERT_VAULE(key, type, func) \
	do {\
		type t; \
		if (!func(t)) { \
			context.serverFail("get %s failed in server", key); \
			return; \
		} \
		context.response.append(key, t); \
	} while (false)

void DABHandler::getSystemSetting(DABContext& context) {
	string language;
	if (!dab_api_getLanguage(language)) {
        context.serverFail("get language failed in server");
		return;
	}
	context.response.append("language", language);
	
	DABOutputResolution outputResolution;
	if (!dab_api_getOutputResolution(outputResolution)) {
        context.serverFail("get outputResolution failed in server");
		return;
	}
	Json::Value resolution =  getOutputResolution(outputResolution);
	context.response.append("outputResolution", resolution);
	GET_SYSTEM_PROPERT_VAULE("memc", bool, dab_api_getMemc);
	GET_SYSTEM_PROPERT_VAULE("cec", bool, dab_api_getCec);
	GET_SYSTEM_PROPERT_VAULE("lowLatencyMode", bool, dab_api_getLowLatencyMode);
	GET_SYSTEM_PROPERT_VAULE("textToSpeech", bool, dab_api_getTextToSpeech);
	GET_SYSTEM_PROPERT_VAULE("audioVolume", int, dab_api_getVolumn);
	
	GET_SYSTEM_PROPERT("matchContentFrameRate", DABMatchContentFrameRate, dab_api_getMatchContentFrameRate);
	GET_SYSTEM_PROPERT("hdrOutputMode", DABHdrOutputMode, dab_api_getHdrOutputMode);
	GET_SYSTEM_PROPERT("pictureMode", DABPictureMode, dab_api_getPictureMode);
	GET_SYSTEM_PROPERT("audioOutputMode", DABAudioOutputMode, dab_api_getAudioOutputMode);
	GET_SYSTEM_PROPERT("audioOutputSource", DABAudioOutputSource, dab_api_getAudioOutputSource);
	GET_SYSTEM_PROPERT("videoInputSource", DABVideoInputSource, dab_api_getVideoInputSource);
	
	context.success();
}

static bool setOutputResolution(DABContext& context, Json::Value& value) {
	DABOutputResolution resolution;
	if (!value.isMember("width")) {
		context.clientFail("outputResolution.width not include");
		return false;
	}
	resolution.width = value["width"].asInt();
	
	if (!value.isMember("height")) {
		context.clientFail("outputResolution.height not include");
		return false;
	}
	resolution.height = value["height"].asInt();
	
	if (!value.isMember("frequency")) {
		context.clientFail("outputResolution.frequency not include");
		return false;
	}
	resolution.frequency = value["frequency"].asInt();
	
	if (!dab_api_setOutputResolution(resolution)) {
        context.serverFail("set outputResolution failed in server");
		return false;
	}
	context.response.append("outputResolution", value);
	return true;
}
#define SET_SYSTEM_PROPERT_VAULE(key, type, supportFunc, setFunc) \
	do {\
		type val; \
		if (context.request.getValue(key, val)) { \
			context.response.append(key, val); \
			if (!supportFunc()) { \
				context.clientFail("set %s unsupport", key); \
				return; \
			} \
			if (!setFunc(val)) { \
				context.serverFail("set %s failed in server", key); \
				return; \
			} \
			context.success(); \
			return; \
		} \
	} while (false)


#define SET_SYSTEM_PROPERT(key, type, optionsFunc, convertFunc, setFunc) \
	do {\
		string val = context.request.getStringValue(key); \
		if (!val.empty()) { \
			context.response.append(key, val); \
			vector<string> options = optionsFunc();\
			if (options.size() < 1) { \
				context.serverFail("get %s options failed in server", key); \
				return; \
			} \
			if (std::count(options.begin(), options.end(), val) < 1) { \
				context.clientFail("set %s value [%s] not valid", key, val.c_str()); \
				return; \
			} \
			type dst;\
			if (!convertFunc(val, dst)) { \
				context.clientFail("set %s value [%s] not support", key, val.c_str()); \
				return;\
			} \
			if (!setFunc(dst)) { \
				context.serverFail("set %s failed in server", key); \
				return; \
			} \
			context.success(); \
			return; \
		} \
	} while (false)

static bool convert2language(const string& language, string& dst) {
	dst = language;
	return true;
}

void DABHandler::setSystemSetting(DABContext& context) {
	SET_SYSTEM_PROPERT("language", 
		string, getLanguages, 
		convert2language, dab_api_setLanguage);

	SET_SYSTEM_PROPERT("matchContentFrameRate", 
		DABMatchContentFrameRate, getMatchContentFrameRateOptions, 
		convert2MatchContentFrameRate, dab_api_setMatchContentFrameRate);

	SET_SYSTEM_PROPERT("hdrOutputMode", 
		DABHdrOutputMode, getHdrOutputModesOptions, 
		convert2HdrOutputMode, dab_api_stHdrOutputMode);

	SET_SYSTEM_PROPERT("pictureMode", 
		DABPictureMode, getPictureModeOptions, 
		convert2PictureMode, dab_api_setPictureMode);

	SET_SYSTEM_PROPERT("audioOutputMode", 
		DABAudioOutputMode, getAudioOutputModeOptions, 
		convert2AudioOutputMode, dab_api_setAudioOutputMode);

	SET_SYSTEM_PROPERT("audioOutputSource",
		DABAudioOutputSource, getAudioOutputSourceOptions, 
		convert2AudioOutputSource, dab_api_setAudioOutputSource);

	SET_SYSTEM_PROPERT("videoInputSource",
		DABVideoInputSource, getVideoInputSourceOptions, 
		convert2VideoInputSource, dab_api_setVideoInputSource);
	
	SET_SYSTEM_PROPERT_VAULE("memc", bool, dab_api_spuuportMemc, dab_api_setMemc);
	SET_SYSTEM_PROPERT_VAULE("cec", bool, dab_api_supportCec, dab_api_setCec);
	SET_SYSTEM_PROPERT_VAULE("lowLatencyMode", bool, dab_api_supportLowLatencyMode, dab_api_setLowLatencyMode);
	SET_SYSTEM_PROPERT_VAULE("mute", bool, dab_api_supportTextToSpeech, dab_api_setMute);
	SET_SYSTEM_PROPERT_VAULE("textToSpeech", bool, dab_api_supportMute, dab_api_setTextToSpeech);
	
	int volume = context.request.getIntValue("audioVolume", -1);
	if (volume != -1) {
		context.response.append("audioVolume", volume);
		int min = 0;
		int max = 100;
		if (!dab_api_getVolumnRange(min, max)) {
			context.serverFail("get audioVolume min, max failed in server");
			return;
		}
		if (volume < min || volume >  max) {
			context.clientFail("audioVolume value valid, min:%d, max:%d, set value:%d", min, max, volume);
			return;
		}
		
		if (!dab_api_setVolumn(volume)) {
			context.serverFail("set audioVolume failed in server");
			return;
		}
		context.success();
		return;
	}
	
	Json::Value value;
	if (context.request.getValue("outputResolution", value)) {
		if (!setOutputResolution(context, value)) {
			return;
		}
		context.success();
		return;
	}
	context.clientFail("set system by not include valid information");
}