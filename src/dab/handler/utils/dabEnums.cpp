#include "dabEnums.h"
#include <map>

using namespace std;

namespace {
	map<DABMatchContentFrameRate, string> matchContentFrameRates = {
		{DABMatchContentFrameRate::EnabledAlways, "EnabledAlways"},
		{DABMatchContentFrameRate::EnabledSeamlessOnly, "EnabledSeamlessOnly"},
		{DABMatchContentFrameRate::Disabled, "Disabled"}
	};
	map<DABHdrOutputMode, string> hdrOutputModes = {
		{DABHdrOutputMode::AlwaysHdr, "AlwaysHdr"},
		{DABHdrOutputMode::HdrOnPlayback, "HdrOnPlayback"},
		{DABHdrOutputMode::DisableHdr, "DisableHdr"}
	};
	map<DABPictureMode, string> pictureModes = {
		{DABPictureMode::Standard, "Standard"},
		{DABPictureMode::Dynamic, "Dynamic"},
		{DABPictureMode::Movie, "Movie"},
		{DABPictureMode::Sports, "Sports"},
		{DABPictureMode::FilmMaker, "FilmMaker"},
		{DABPictureMode::Game, "Game"},
		{DABPictureMode::Auto, "Auto"}
	};
	map<DABAudioOutputMode, string> audioOutputModes = {
		{DABAudioOutputMode::Stereo, "Stereo"},
		{DABAudioOutputMode::MultichannelPcm, "MultichannelPcm"},
		{DABAudioOutputMode::PassThrough, "PassThrough"},
		{DABAudioOutputMode::Auto, "Auto"}
	};
	map<DABAudioOutputSource, string> audioOutputSources = {
		{DABAudioOutputSource::NativeSpeaker, "NativeSpeaker"},
		{DABAudioOutputSource::Arc, "Arc"},
		{DABAudioOutputSource::EArc, "EArc"},
		{DABAudioOutputSource::Optical, "Optical"},
		{DABAudioOutputSource::Aux, "Aux"},
		{DABAudioOutputSource::Bluetooth, "Bluetooth"},
		{DABAudioOutputSource::Auto, "Auto"},
		{DABAudioOutputSource::HDMI, "HDMI"},
	};
	map<DABVideoInputSource, string> videoInputSources = {
		{DABVideoInputSource::Tuner, "Tuner"},
		{DABVideoInputSource::HDMI1, "HDMI1"},
		{DABVideoInputSource::HDMI2, "HDMI2"},
		{DABVideoInputSource::HDMI3, "HDMI3"},
		{DABVideoInputSource::HDMI4, "HDMI4"},
		{DABVideoInputSource::Composite, "Composite"},
		{DABVideoInputSource::Component, "Component"},
		{DABVideoInputSource::Home, "Home"},
		{DABVideoInputSource::Cast, "Cast"},
	};

	template<typename T>
	string convert2string(const map<T, string>& map_, T val, const string& defaultValue) {
		const auto& it = map_.find(val);
		if (map_.end() == it) {
			return defaultValue;
		}
		return it->second;
	}

	template<typename T>
	bool convert2enum(const map<T, string>& map_, const string& val, T& dst) {
		for (const auto& it: map_) {
			if (it.second == val) {
				dst = it.first;
				return true;
			}
		}
		return false;
	}
}
string convert(DABMatchContentFrameRate val) {
	return convert2string(matchContentFrameRates, val, "Disabled");
}
bool convert2MatchContentFrameRate(const string& val, DABMatchContentFrameRate& dst) {
	return convert2enum(matchContentFrameRates, val, dst);
}	
string convert(DABHdrOutputMode val) {
	return convert2string(hdrOutputModes, val, "DisableHdr");
}
bool convert2HdrOutputMode(const string& val, DABHdrOutputMode& dst) {
	return convert2enum(hdrOutputModes, val, dst);
}
string convert(DABPictureMode val) {
	return convert2string(pictureModes, val, "Auto");
}
bool convert2PictureMode(const string& val, DABPictureMode& dst) {
	return convert2enum(pictureModes, val, dst);
}
string convert(DABAudioOutputMode val) {
	return convert2string(audioOutputModes, val, "Auto");
}
bool convert2AudioOutputMode(const string& val, DABAudioOutputMode& dst) {
	return convert2enum(audioOutputModes, val, dst);
}
string convert(DABAudioOutputSource val) {
	return convert2string(audioOutputSources, val, "Auto");
}
bool convert2AudioOutputSource(const string& val, DABAudioOutputSource& dst) {
	return convert2enum(audioOutputSources, val, dst);
}
string convert(DABVideoInputSource val) {
	return convert2string(videoInputSources, val, "Home");
}
bool convert2VideoInputSource(const string& val, DABVideoInputSource& dst) {
	return convert2enum(videoInputSources, val, dst);
}