/*ongaku.h*/
#ifndef ONGAKU_HPP
#define ONGAKU_HPP
#pragma once

#include <string>

namespace Ongaku {
    void AudioStream(float hertz, float volume, float duration);
    void PlayAudioFile(float AudioVolume, bool AudioLoop, float AudioPitch, const std::string& AudioFilePath);
    void SynthGUI();
}
#endif