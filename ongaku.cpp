#include "ongaku.h"

#include <rtaudio/RtAudio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <thread>
#include <chrono>
#include <cmath>

struct AudioSettings {
    float frequency         = 440.0f; 
    float volume            = 0.2f;   
    double phase[2]         = {0.0, 0.0};
    float duration          = 1.0f;
    unsigned int sampleRate = 44100;
    unsigned long currentFrame = 0;
};

int sawCallback( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                 double streamTime, RtAudioStreamStatus status, void *userData )
{
  double *buffer = (double *) outputBuffer;
  AudioSettings *settings = (AudioSettings *) userData;
 
  if ( status )
    std::cout << "Stream underflow detected!" << std::endl;
 
  double phaseIncrement = (settings->frequency * 2.0) / static_cast<double>(settings->sampleRate);
  unsigned long totalFramesNeeded = static_cast<unsigned long>(settings->duration * settings->sampleRate);

  for ( unsigned int i = 0; i < nBufferFrames; i++ ) {
    if ( settings->currentFrame >= totalFramesNeeded ) {
      for ( unsigned int j = 0; j < 2; j++ ) {
        *buffer++ = 0.0;
      }
      continue;
    }

    for ( unsigned int j = 0; j < 2; j++ ) {
      *buffer++ = settings->phase[j] * settings->volume;
 
      settings->phase[j] += phaseIncrement * (j + 1 + (j * 0.1));
      
      if ( settings->phase[j] >= 1.0 ) {
          settings->phase[j] -= 2.0;
      }
    }

    settings->currentFrame++;
  }
  if ( settings->currentFrame >= totalFramesNeeded ) {
    return 1; 
  }

  return 0;
}

namespace Ongaku {

void AudioStream(float hertz, float volume, float duration) {
  RtAudio dac;

  if ( dac.getDeviceCount() < 1 ) {
    std::cout << "\nNo audio devices found!\n";
    return;
  }
 
  RtAudio::StreamParameters parameters;
  parameters.deviceId = dac.getDefaultOutputDevice();
  parameters.nChannels = 2;
  parameters.firstChannel = 0;
  
  unsigned int sampleRate = 44100;
  unsigned int bufferFrames = 256;

  AudioSettings settings;
  settings.frequency  = hertz;
  settings.volume     = volume;
  settings.duration   = duration;
  settings.sampleRate = sampleRate;
  settings.currentFrame = 0;
 
  if ( dac.openStream( &parameters, NULL, RTAUDIO_FLOAT64, sampleRate,
                       &bufferFrames, &sawCallback, (void *)&settings ) ) {
    std::cout << '\n' << dac.getErrorText() << '\n' << std::endl;
    return;
  }
 
  if ( dac.startStream() ) {
    std::cout << dac.getErrorText() << std::endl;
    if ( dac.isStreamOpen() ) dac.closeStream();
    return;
  }

  std::this_thread::sleep_for(std::chrono::duration<float>(duration));
  while ( dac.isStreamRunning() ) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  if ( dac.isStreamOpen() ) dac.closeStream();
}

void PlayAudioFile(float AudioVolume, bool AudioLoop, float AudioPitch, const std::string& AudioFilePath){
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(AudioFilePath)) {
        std::cerr << "Failed to load audio file: " << AudioFilePath << std::endl;
        return;
    }

    sf::Sound sound(buffer);
    sound.setVolume(AudioVolume);
    sound.setLooping(AudioLoop);
    sound.setPitch(AudioPitch);

    sound.play();

    while (sound.getStatus() == sf::Sound::Status::Playing) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

struct KeyInfo {
    sf::Keyboard::Scan scancode;
    float semitone;
    bool isBlack;
    int whiteIndex;
};

void SynthGUI() {

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("Sound/C.wav")) {
        std::cerr << "Error: Could not load Sound/C.wav" << std::endl;
        return;
    }

    std::vector<KeyInfo> keyMap = {
        {sf::Keyboard::Scan::Tab,       -10.f, false, 0},  // D1
        {sf::Keyboard::Scan::Num1,       -9.f, true,  0},  // D#1
        {sf::Keyboard::Scan::Q,          -8.f, false, 1},  // E1
        {sf::Keyboard::Scan::W,          -7.f, false, 2},  // F1
        {sf::Keyboard::Scan::Num3,       -6.f, true,  2},  // F#1
        {sf::Keyboard::Scan::E,          -5.f, false, 3},  // G1
        {sf::Keyboard::Scan::Num4,       -4.f, true,  3},  // G#1
        {sf::Keyboard::Scan::R,          -3.f, false, 4},  // A1
        {sf::Keyboard::Scan::Num5,       -2.f, true,  4},  // A#1
        {sf::Keyboard::Scan::T,          -1.f, false, 5},  // B1
        {sf::Keyboard::Scan::Y,           0.f, false, 6},  // C2
        {sf::Keyboard::Scan::Num7,        1.f, true,  6},  // C#2
        {sf::Keyboard::Scan::U,           2.f, false, 7},  // D2
        {sf::Keyboard::Scan::Num8,        3.f, true,  7},  // D#2
        {sf::Keyboard::Scan::I,           4.f, false, 8},  // E2
        {sf::Keyboard::Scan::O,           5.f, false, 9},  // F2
        {sf::Keyboard::Scan::Num0,        6.f, true,  9},  // F#2
        {sf::Keyboard::Scan::P,           7.f, false, 10}, // G2
        {sf::Keyboard::Scan::Hyphen,      8.f, true,  10}, // G#2
        {sf::Keyboard::Scan::LBracket,    9.f, false, 11}, // A2
        {sf::Keyboard::Scan::Equal,      10.f, true,  11}, // A#2
        {sf::Keyboard::Scan::RBracket,   11.f, false, 12}, // B2
        {sf::Keyboard::Scan::Backslash,  12.f, false, 13}  // C3
    };

    std::vector<sf::Sound> sounds;
    sounds.reserve(keyMap.size());
    for (const auto& k : keyMap) {
        sf::Sound sound(buffer);
        sound.setPitch(std::pow(2.f, k.semitone / 12.f));
        sounds.push_back(sound);
    }

    sf::RectangleShape shape;
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(-1.f);

    sf::RenderWindow window(sf::VideoMode({1000, 300}), "Synth");
    window.setKeyRepeatEnabled(false);

    while (window.isOpen()) {
        while (std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (event->is<sf::Event::Resized>()) {
                window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize()))));
            }
            else if (auto key = event->getIf<sf::Event::KeyPressed>()) {
                for (size_t i = 0; i < keyMap.size(); ++i) {
                    if (key->scancode == keyMap[i].scancode) {
                        sounds[i].play();
                        break;
                    }
                }
            }
        }

        float window_w = window.getView().getSize().x;
        float window_h = window.getView().getSize().y;

        window.clear(sf::Color::Black);

        const int whiteKeyCount = 14;
        float key_w = window_w / whiteKeyCount;

        for (size_t i = 0; i < keyMap.size(); ++i) {
            if (!keyMap[i].isBlack) {
                shape.setSize({key_w, window_h});
                shape.setPosition({keyMap[i].whiteIndex * key_w, 0.f});

                if (sf::Keyboard::isKeyPressed(keyMap[i].scancode))
                    shape.setFillColor(sf::Color(0, 170, 255));
                else
                    shape.setFillColor(sf::Color::White);

                window.draw(shape);
            }
        }

        for (size_t i = 0; i < keyMap.size(); ++i) {
            if (keyMap[i].isBlack) {
                shape.setSize({key_w * 0.5f, window_h * 0.6f});
                shape.setPosition({(keyMap[i].whiteIndex + 0.75f) * key_w, 0.f});

                if (sf::Keyboard::isKeyPressed(keyMap[i].scancode))
                    shape.setFillColor(sf::Color(0, 170, 255));
                else
                    shape.setFillColor(sf::Color::Black);

                window.draw(shape);
            }
        }

        window.display();
    }
}
}