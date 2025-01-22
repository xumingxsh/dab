#pragma once
#include <string>
#include <vector>
#include "dab/dab_api.h"

struct DABOutputResolution {
   int width;
   int height;
   int frequency;
};

enum class DABHdrOutputMode {
    // Always output HDMI signal in HDR Format
    AlwaysHdr,
    // Output HDMI signal in HDR Format Only when playing HDR content
    HdrOnPlayback,
    // Never Output HDMI Signal in HDR Mode
    DisableHdr,
};

enum class DABMatchContentFrameRate {
    // Match Content Frame Rate is Always Allowed even if the transition is not Seamless
    EnabledAlways,
    // Match Content Frame Rate is Only Allowed when the transition is Seamless
    EnabledSeamlessOnly,
    // Match Content Frame Rate is Disabled
    Disabled,
};

enum class DABPictureMode {
    // Standard Mode or Normal Mode
    Standard,
    // Dynamic or Vivid Mode
    Dynamic,
    // Movie or Cinema Mode
    Movie,
    // Sports Mode
    Sports,
    // Filmmaker Mode
    FilmMaker,
    // Game Mode, Lowest Latency Option
    Game,
    // Automatically adjust the picture mode to the best option for current content
    Auto,
};

enum class DABAudioOutputMode {
    // 2 Channel PCM
    Stereo,
    // Multichannel PCM e.g. 5.1 PCM
    MultichannelPcm,
    // Bitstreams sent in passthrough mode
    PassThrough,
    // Audio Output Mode Recommended by the device partner in current setup
    Auto,
};

enum class DABAudioOutputSource {
    // Audio Output on Native Speakers of the device
    NativeSpeaker,
    // Audio Output on ARC Port
    Arc,
    // Audio Output on E-ARC Port
    EArc,
    // Audio Output on Optical Port
    Optical,
    // Audio Output on Auxilliary Port
    Aux,
    // Audio Output on connected Bluetooth Speaker
    Bluetooth,
    // Audio Output in the default mode recommended by the device partner in current setup
    Auto,
    // HDMI, This is only applicable for Source devices
    HDMI,
};

enum class DABVideoInputSource {
    // TV Tuner / Antenna
    Tuner,
    // First HDMI Input Port
    HDMI1,
    // Second HDMI Input Port
    HDMI2,
    // Third HDMI Input Port
    HDMI3,
    // Fourth HDMI Input Port
    HDMI4,
    // Composite input port
    Composite,
    // Component input port
    Component,
    // TV Home Screen
    Home,
    // Wireless Casting
    Cast,
};

extern "C" {
    bool dab_api_reboot();

    // IVServiceAPI:setVolumeValue, getVolumeValue 
    bool dab_api_getVolumnRange(int& min, int& max);
    bool dab_api_getVolumn(int& val);
    bool dab_api_setVolumn(int val);

    // IVServiceAPI:getMuteState,setMuteState
    bool dab_api_supportMute();
    bool dab_api_getMute(bool& val);
    bool dab_api_setMute(bool val);

    bool dab_api_supportTextToSpeech();
    bool dab_api_getTextToSpeech(bool& val);
    bool dab_api_setTextToSpeech(bool val);

    bool dab_api_spuuportMemc();
    bool dab_api_getMemc(bool& val);
    bool dab_api_setMemc(bool val);

    bool dab_api_supportCec();
    bool dab_api_getCec(bool& val);
    bool dab_api_setCec(bool val);

    bool dab_api_supportLowLatencyMode();
    bool dab_api_getLowLatencyMode(bool& val);
    bool dab_api_setLowLatencyMode(bool val);


    bool dab_api_listLanguageOptions(std::vector<std::string>& list);
    bool dab_api_getLanguage(std::string& language);
    bool dab_api_setLanguage(const char* language);
    
    bool dab_api_listOutputResolutionOptions(std::vector<DABOutputResolution>& list);
    bool dab_api_getOutputResolution(DABOutputResolution& val);
    bool dab_api_setOutputResolution(const DABOutputResolution val);

    bool dab_api_listMatchContentFrameRateOptions(std::vector<DABMatchContentFrameRate>& list);
    bool dab_api_getMatchContentFrameRate(DABMatchContentFrameRate& val);
    bool dab_api_setMatchContentFrameRate(const DABMatchContentFrameRate& val);


    bool dab_api_listHdrOutputModeOptions(std::vector<DABHdrOutputMode>& list);
    bool dab_api_getHdrOutputMode(DABHdrOutputMode& val);
    bool dab_api_stHdrOutputMode(const DABHdrOutputMode val);


    bool dab_api_listPictureModeOptions(std::vector<DABPictureMode>& list);
    bool dab_api_getPictureMode(DABPictureMode& val);
    bool dab_api_setPictureMode(const DABPictureMode val);


    bool dab_api_listAudioOutputModeOptions(std::vector<DABAudioOutputMode>& list);
    bool dab_api_getAudioOutputMode(DABAudioOutputMode& val);
    bool dab_api_setAudioOutputMode(const DABAudioOutputMode val);

    bool dab_api_listAudioOutputSourceOptions(std::vector<DABAudioOutputSource>& list);
    bool dab_api_getAudioOutputSource(DABAudioOutputSource& val);
    bool dab_api_setAudioOutputSource(const DABAudioOutputSource val);


    bool dab_api_listVideoInputSourceOptions(std::vector<DABVideoInputSource>& list);
    bool dab_api_getVideoInputSource(DABVideoInputSource& val);
    bool dab_api_setVideoInputSource(const DABVideoInputSource val);
}