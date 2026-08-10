#include "ongaku.h"

#include <rtaudio/RtAudio.h>
#include <SFML/Audio.hpp>
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
}

namespace OngakuNotes {

namespace Static {

    // *First Octive

void C1(float VolumeC1, float DurationC1){
    Ongaku::AudioStream(32.70, VolumeC1, DurationC1);
}
void CS1(float VolumeCS1, float DurationCS1){
    Ongaku::AudioStream(34.65, VolumeCS1, DurationCS1);
}
void D1(float VolumeD1, float DurationD1){
    Ongaku::AudioStream(36.71, VolumeD1, DurationD1);
}
void DS1(float VolumeDS1, float DurationDS1){
    Ongaku::AudioStream(38.89, VolumeDS1, DurationDS1);
}
void E1(float VolumeE1, float DurationE1){
    Ongaku::AudioStream(41.20, VolumeE1, DurationE1);
}
void F1(float VolumeF1, float DurationF1){
    Ongaku::AudioStream(43.65, VolumeF1, DurationF1);
}
void FS1(float VolumeFS1, float DurationFS1){
    Ongaku::AudioStream(46.25, VolumeFS1, DurationFS1);
}
void G1(float VolumeG1, float DurationG1){
    Ongaku::AudioStream(49.00, VolumeG1, DurationG1);
}
void GS1(float VolumeGS1, float DurationGS1){
    Ongaku::AudioStream(51.91, VolumeGS1, DurationGS1);
}
void A1(float VolumeA1, float DurationA1){
    Ongaku::AudioStream(55.00, VolumeA1, DurationA1);
}
void AS1(float VolumeAS1, float DurationAS1){
    Ongaku::AudioStream(58.27, VolumeAS1, DurationAS1);
}
void B1(float VolumeB1, float DurationB1){
    Ongaku::AudioStream(61.74, VolumeB1, DurationB1);
}

    // *Second Octive

void C2(float VolumeC2, float DurationC2){
    Ongaku::AudioStream(32.70*2, VolumeC2, DurationC2);
}
void CS2(float VolumeCS2, float DurationCS2){
    Ongaku::AudioStream(34.65*2, VolumeCS2, DurationCS2);
}
void D2(float VolumeD2, float DurationD2){
    Ongaku::AudioStream(36.71*2, VolumeD2, DurationD2);
}
void DS2(float VolumeDS2, float DurationDS2){
    Ongaku::AudioStream(38.89*2, VolumeDS2, DurationDS2);
}
void E2(float VolumeE2, float DurationE2){
    Ongaku::AudioStream(41.20*2, VolumeE2, DurationE2);
}
void F2(float VolumeF2, float DurationF2){
    Ongaku::AudioStream(43.65*2, VolumeF2, DurationF2);
}
void FS2(float VolumeFS2, float DurationFS2){
    Ongaku::AudioStream(46.25*2, VolumeFS2, DurationFS2);
}
void G2(float VolumeG2, float DurationG2){
    Ongaku::AudioStream(49.00*2, VolumeG2, DurationG2);
}
void GS2(float VolumeGS2, float DurationGS2){
    Ongaku::AudioStream(51.91*2, VolumeGS2, DurationGS2);
}
void A2(float VolumeA2, float DurationA2){
    Ongaku::AudioStream(55.00*2, VolumeA2, DurationA2);
}
void AS2(float VolumeAS2, float DurationAS2){
    Ongaku::AudioStream(58.27*2, VolumeAS2, DurationAS2);
}
void B2(float VolumeB2, float DurationB2){
    Ongaku::AudioStream(61.74*2, VolumeB2, DurationB2);
}

    // *Third Octive

void C3(float VolumeC3, float DurationC3){
    Ongaku::AudioStream(32.70*4, VolumeC3, DurationC3);    
}
void CS3(float VolumeCS3, float DurationCS3){
    Ongaku::AudioStream(34.65*4, VolumeCS3, DurationCS3);
}
void D3(float VolumeD3, float DurationD3){
    Ongaku::AudioStream(36.71*4, VolumeD3, DurationD3);
}
void DS3(float VolumeDS3, float DurationDS3){
    Ongaku::AudioStream(38.89*4, VolumeDS3, DurationDS3);
}
void E3(float VolumeE3, float DurationE3){
    Ongaku::AudioStream(41.20*4, VolumeE3, DurationE3);
}
void F3(float VolumeF3, float DurationF3){
    Ongaku::AudioStream(43.65*4, VolumeF3, DurationF3);
}
void FS3(float VolumeFS3, float DurationFS3){
    Ongaku::AudioStream(46.25*4, VolumeFS3, DurationFS3);
}
void G3(float VolumeG3, float DurationG3){
    Ongaku::AudioStream(49.00*4, VolumeG3, DurationG3);
}
void GS3(float VolumeGS3, float DurationGS3){
    Ongaku::AudioStream(51.91*4, VolumeGS3, DurationGS3);
}
void A3(float VolumeA3, float DurationA3){
    Ongaku::AudioStream(55.00*4, VolumeA3, DurationA3);
}
void AS3(float VolumeAS3, float DurationAS3){
    Ongaku::AudioStream(58.27*4, VolumeAS3, DurationAS3);
}
void B3(float VolumeB3, float DurationB3){
    Ongaku::AudioStream(61.74*4, VolumeB3, DurationB3);
}


    // *Fourth Octive

void C4(float VolumeC4, float DurationC4){
    Ongaku::AudioStream(32.70*8, VolumeC4, DurationC4);    
}
void CS4(float VolumeCS4, float DurationCS4){
    Ongaku::AudioStream(34.65*8, VolumeCS4, DurationCS4);
}
void D4(float VolumeD4, float DurationD4){
    Ongaku::AudioStream(36.71*8, VolumeD4, DurationD4);
}
void DS4(float VolumeDS4, float DurationDS4){
    Ongaku::AudioStream(38.89*8, VolumeDS4, DurationDS4);
}
void E4(float VolumeE4, float DurationE4){
    Ongaku::AudioStream(41.20*8, VolumeE4, DurationE4);
}
void F4(float VolumeF4, float DurationF4){
    Ongaku::AudioStream(43.65*8, VolumeF4, DurationF4);
}
void FS4(float VolumeFS4, float DurationFS4){
    Ongaku::AudioStream(46.25*8, VolumeFS4, DurationFS4);
}
void G4(float VolumeG4, float DurationG4){
    Ongaku::AudioStream(49.00*8, VolumeG4, DurationG4);
}
void GS4(float VolumeGS4, float DurationGS4){
    Ongaku::AudioStream(51.91*8, VolumeGS4, DurationGS4);
}
void A4(float VolumeA4, float DurationA4){
    Ongaku::AudioStream(55.00*8, VolumeA4, DurationA4);
}
void AS4(float VolumeAS4, float DurationAS4){
    Ongaku::AudioStream(58.27*8, VolumeAS4, DurationAS4);
}
void B4(float VolumeB4, float DurationB4){
    Ongaku::AudioStream(61.74*8, VolumeB4, DurationB4);
}


    // *Fith Octive

void C5(float VolumeC5, float DurationC5){
    Ongaku::AudioStream(32.70*16, VolumeC5, DurationC5);    
}
void CS5(float VolumeCS5, float DurationCS5){
    Ongaku::AudioStream(34.65*16, VolumeCS5, DurationCS5);
}
void D5(float VolumeD5, float DurationD5){
    Ongaku::AudioStream(36.71*16, VolumeD5, DurationD5);
}
void DS5(float VolumeDS5, float DurationDS5){
    Ongaku::AudioStream(38.89*16, VolumeDS5, DurationDS5);
}
void E5(float VolumeE5, float DurationE5){
    Ongaku::AudioStream(41.20*16, VolumeE5, DurationE5);
}
void F5(float VolumeF5, float DurationF5){
    Ongaku::AudioStream(43.65*16, VolumeF5, DurationF5);
}
void FS5(float VolumeFS5, float DurationFS5){
    Ongaku::AudioStream(46.25*16, VolumeFS5, DurationFS5);
}
void G5(float VolumeG5, float DurationG5){
    Ongaku::AudioStream(49.00*16, VolumeG5, DurationG5);
}
void GS5(float VolumeGS5, float DurationGS5){
    Ongaku::AudioStream(51.91*16, VolumeGS5, DurationGS5);
}
void A5(float VolumeA5, float DurationA5){
    Ongaku::AudioStream(55.00*16, VolumeA5, DurationA5);
}
void AS5(float VolumeAS5, float DurationAS5){
    Ongaku::AudioStream(58.27*16, VolumeAS5, DurationAS5);
}
void B5(float VolumeB5, float DurationB5){
    Ongaku::AudioStream(61.74*16, VolumeB5, DurationB5);
}


    // *Sixth Octive / C7

void C6(float VolumeC6, float DurationC6){
    Ongaku::AudioStream(32.70*32, VolumeC6, DurationC6);    
}
void CS6(float VolumeCS6, float DurationCS6){
    Ongaku::AudioStream(34.65*32, VolumeCS6, DurationCS6);
}
void D6(float VolumeD6, float DurationD6){
    Ongaku::AudioStream(36.71*32, VolumeD6, DurationD6);
}
void DS6(float VolumeDS6, float DurationDS6){
    Ongaku::AudioStream(38.89*32, VolumeDS6, DurationDS6);
}
void E6(float VolumeE6, float DurationE6){
    Ongaku::AudioStream(41.20*32, VolumeE6, DurationE6);
}
void F6(float VolumeF6, float DurationF6){
    Ongaku::AudioStream(43.65*32, VolumeF6, DurationF6);
}
void FS6(float VolumeFS6, float DurationFS6){
    Ongaku::AudioStream(46.25*32, VolumeFS6, DurationFS6);
}
void G6(float VolumeG6, float DurationG6){
    Ongaku::AudioStream(49.00*32, VolumeG6, DurationG6);
}
void GS6(float VolumeGS6, float DurationGS6){
    Ongaku::AudioStream(51.91*32, VolumeGS6, DurationGS6);
}
void A6(float VolumeA6, float DurationA6){
    Ongaku::AudioStream(55.00*32, VolumeA6, DurationA6);
}
void AS6(float VolumeAS6, float DurationAS6){
    Ongaku::AudioStream(58.27*32, VolumeAS6, DurationAS6);
}
void B6(float VolumeB6, float DurationB6){
    Ongaku::AudioStream(61.74*32, VolumeB6, DurationB6);
}
void C7(float VolumeC7, float DurationC7){
    Ongaku::AudioStream(32.70*64, VolumeC7, DurationC7);    
}
}

namespace Instrument {

    // * First Octive

    void C1(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.125, "Sound/Piano_C4.wav");
    }
    void CS1(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.1324, "Sound/Piano_C4.wav");
    }
    void D1(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.1403, "Sound/Piano_C4.wav");
    }
    void DS1(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.1487, "Sound/Piano_C4.wav");
    }
    void E1(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.1575, "Sound/Piano_C4.wav");
    }
    void F1(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.1668, "Sound/Piano_C4.wav");
    }
    void FS1(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.1768, "Sound/Piano_C4.wav");
    }
    void G1(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.1873, "Sound/Piano_C4.wav");
    }
    void GS1(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.1984, "Sound/Piano_C4.wav");
    }
    void A1(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.2102, "Sound/Piano_C4.wav");
    }
    void AS1(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.2227, "Sound/Piano_C4.wav");
    }
    void B1(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.2360, "Sound/Piano_C4.wav");
    }

    // * Second Octive

    void C2(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.125*2, "Sound/Piano_C4.wav");
    }
    void CS2(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.1324*2, "Sound/Piano_C4.wav");
    }
    void D2(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.1403*2, "Sound/Piano_C4.wav");
    }
    void DS2(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.1487*2, "Sound/Piano_C4.wav");
    }
    void E2(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.1575*2, "Sound/Piano_C4.wav");
    }
    void F2(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.1668*2, "Sound/Piano_C4.wav");
    }
    void FS2(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.1768*2, "Sound/Piano_C4.wav");
    }
    void G2(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.1873*2, "Sound/Piano_C4.wav");
    }
    void GS2(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.1984*2, "Sound/Piano_C4.wav");
    }
    void A2(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.2102*2, "Sound/Piano_C4.wav");
    }
    void AS2(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.2227*2, "Sound/Piano_C4.wav");
    }
    void B2(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.2360*2, "Sound/Piano_C4.wav");
    }

    // * Third Octive

    void C3(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.125*4, "Sound/Piano_C4.wav");
    }
    void CS3(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.1324*4, "Sound/Piano_C4.wav");
    }
    void D3(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.1403*4, "Sound/Piano_C4.wav");
    }
    void DS3(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.1487*4, "Sound/Piano_C4.wav");
    }
    void E3(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.1575*4, "Sound/Piano_C4.wav");
    }
    void F3(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.1668*4, "Sound/Piano_C4.wav");
    }
    void FS3(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.1768*4, "Sound/Piano_C4.wav");
    }
    void G3(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.1873*4, "Sound/Piano_C4.wav");
    }
    void GS3(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.1984*4, "Sound/Piano_C4.wav");
    }
    void A3(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.2102*4, "Sound/Piano_C4.wav");
    }
    void AS3(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.2227*4, "Sound/Piano_C4.wav");
    }
    void B3(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 0.2360*4, "Sound/Piano_C4.wav");
    }

        // * Fourth Octive

    void C4(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1, "Sound/Piano_C4.wav");
    }
    void CS4(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.0595, "Sound/Piano_C4.wav");
    }
    void D4(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.1225, "Sound/Piano_C4.wav");
    }
    void DS4(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.1892, "Sound/Piano_C4.wav");
    }
    void E4(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.2599, "Sound/Piano_C4.wav");
    }
    void F4(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.3348, "Sound/Piano_C4.wav");
    }
    void FS4(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.4142, "Sound/Piano_C4.wav");
    }
    void G4(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.4983, "Sound/Piano_C4.wav");
    }
    void GS4(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.5874, "Sound/Piano_C4.wav");
    }
    void A4(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.6818, "Sound/Piano_C4.wav");
    }
    void AS4(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.7818, "Sound/Piano_C4.wav");
    }
    void B4(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.8877, "Sound/Piano_C4.wav");
    }

        // * Fith Octive

    void C5(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 2, "Sound/Piano_C4.wav");
    }
    void CS5(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.0595*2, "Sound/Piano_C4.wav");
    }
    void D5(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.1225*2, "Sound/Piano_C4.wav");
    }
    void DS5(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.1892*2, "Sound/Piano_C4.wav");
    }
    void E5(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.2599*2, "Sound/Piano_C4.wav");
    }
    void F5(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.3348*2, "Sound/Piano_C4.wav");
    }
    void FS5(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.4142*2, "Sound/Piano_C4.wav");
    }
    void G5(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.4983*2, "Sound/Piano_C4.wav");
    }
    void GS5(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.5874*2, "Sound/Piano_C4.wav");
    }
    void A5(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.6818*2, "Sound/Piano_C4.wav");
    }
    void AS5(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.7818*2, "Sound/Piano_C4.wav");
    }
    void B5(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.8877*2, "Sound/Piano_C4.wav");
    }

        // * Sixth Octive / C7

    void C6(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 4, "Sound/Piano_C4.wav");
    }
    void CS6(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.0595*4, "Sound/Piano_C4.wav");
    }
    void D6(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.1225*4, "Sound/Piano_C4.wav");
    }
    void DS6(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.1892*4, "Sound/Piano_C4.wav");
    }
    void E6(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.2599*4, "Sound/Piano_C4.wav");
    }
    void F6(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.3348*4, "Sound/Piano_C4.wav");
    }
    void FS6(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.4142*4, "Sound/Piano_C4.wav");
    }
    void G6(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.4983*4, "Sound/Piano_C4.wav");
    }
    void GS6(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.5874*4, "Sound/Piano_C4.wav");
    }
    void A6(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.6818*4, "Sound/Piano_C4.wav");
    }
    void AS6(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.7818*4, "Sound/Piano_C4.wav");
    }
    void B6(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 1.8877*4, "Sound/Piano_C4.wav");
    }
    void C7(float NoteVolume){
        Ongaku::PlayAudioFile(NoteVolume, false, 8, "Sound/Piano_C4.wav");
    }
}

}