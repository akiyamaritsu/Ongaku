/*ongaku.h*/
#ifndef ONGAKU_HPP
#define ONGAKU_HPP
#pragma once

#include <string>

namespace Ongaku {
    void AudioStream(float hertz, float volume, float duration);
    void PlayAudioFile(float AudioVolume, bool AudioLoop, float AudioPitch, const std::string& AudioFilePath, float AudioOffset);
}
namespace OngakuNotes {

    namespace Static {

    void C1(float VolumeC1, float DurationC1);
    void CS1(float VolumeCS1, float DurationCS1);
    void D1(float VolumeD1, float DurationD1);
    void DS1(float VolumeDS1, float DurationDS1);
    void E1(float VolumeE1, float DurationE1);
    void F1(float VolumeF1, float DurationF1);
    void FS1(float VolumeFS1, float DurationFS1);
    void G1(float VolumeG1, float DurationG1);
    void GS1(float VolumeGS1, float DurationGS1);
    void A1(float VolumeA1, float DurationA1);
    void AS1(float VolumeAS1, float DurationAS1);
    void B1(float VolumeB1, float DurationB1);

    void C2(float VolumeC2, float DurationC2);
    void CS2(float VolumeCS2, float DurationCS2);
    void D2(float VolumeD2, float DurationD2);
    void DS2(float VolumeDS2, float DurationDS2);
    void E2(float VolumeE2, float DurationE2);
    void F2(float VolumeF2, float DurationF2);
    void FS2(float VolumeFS2, float DurationFS2);
    void G2(float VolumeG2, float DurationG2);
    void GS2(float VolumeGS2, float DurationGS2);
    void A2(float VolumeA2, float DurationA2);
    void AS2(float VolumeAS2, float DurationAS2);
    void B2(float VolumeB2, float DurationB2);

    void C3(float VolumeC3, float DurationC3);
    void CS3(float VolumeCS3, float DurationCS3);
    void D3(float VolumeD3, float DurationD3);
    void DS3(float VolumeDS3, float DurationDS3);
    void E3(float VolumeE3, float DurationE3);
    void F3(float VolumeF3, float DurationF3);
    void FS3(float VolumeFS3, float DurationFS3);
    void G3(float VolumeG3, float DurationG3);
    void GS3(float VolumeGS3, float DurationGS3);
    void A3(float VolumeA3, float DurationA3);
    void AS3(float VolumeAS3, float DurationAS3);
    void B3(float VolumeB3, float DurationB3);

    void C4(float VolumeC4, float DurationC4);
    void CS4(float VolumeCS4, float DurationCS4);
    void D4(float VolumeD4, float DurationD4);
    void DS4(float VolumeDS4, float DurationDS4);
    void E4(float VolumeE4, float DurationE4);
    void F4(float VolumeF4, float DurationF4);
    void FS4(float VolumeFS4, float DurationFS4);
    void G4(float VolumeG4, float DurationG4);
    void GS4(float VolumeGS4, float DurationGS4);
    void A4(float VolumeA4, float DurationA4);
    void AS4(float VolumeAS4, float DurationAS4);
    void B4(float VolumeB4, float DurationB4);

    void C5(float VolumeC5, float DurationC5);
    void CS5(float VolumeS5, float DurationCS5);
    void D5(float VolumeD5, float DurationD5);
    void DS5(float VolumeDS5, float DurationDS5);
    void E5(float VolumeE5, float DurationE5);
    void F5(float VolumeF5, float DurationF5);
    void FS5(float VolumeFS5, float DurationFS5);
    void G5(float VolumeG5, float DurationG5);
    void GS5(float VolumeGS5, float DurationGS5);
    void A5(float VolumeA5, float DurationA5);
    void AS5(float VolumeAS5, float DurationAS5);
    void B5(float VolumeB2, float DurationB5);
    
    void C6(float VolumeC6, float DurationC6);
    void CS6(float VolumeS6, float DurationCS6);
    void D6(float VolumeD6, float DurationD6);
    void DS6(float VolumeDS6, float DurationDS6);
    void E6(float VolumeE6, float DurationE6);
    void F6(float VolumeF6, float DurationF6);
    void FS6(float VolumeFS6, float DurationFS6);
    void G6(float VolumeG6, float DurationG6);
    void GS6(float VolumeGS6, float DurationGS6);
    void A6(float VolumeA6, float DurationA6);
    void AS6(float VolumeAS6, float DurationAS6);
    void B6(float VolumeB6, float DurationB6);

    void C7(float VolumeC7, float DurationC7);
    }

    namespace Instrument {

            void C1(float NoteVolume);
            void CS1(float NoteVolume);
            void D1(float NoteVolume);
            void DS1(float NoteVolume);
            void E1(float NoteVolume);
            void F1(float NoteVolume);
            void FS1(float NoteVolume);
            void G1(float NoteVolume);
            void GS1(float NoteVolume);
            void A1(float NoteVolume);
            void AS1(float NoteVolume);
            void B1(float NoteVolume);

            void C2(float NoteVolume);
            void CS2(float NoteVolume);
            void D2(float NoteVolume);
            void DS2(float NoteVolume);
            void E2(float NoteVolume);
            void F2(float NoteVolume);
            void FS2(float NoteVolume);
            void G2(float NoteVolume);
            void GS2(float NoteVolume);
            void A2(float NoteVolume);
            void AS2(float NoteVolume);
            void B2(float NoteVolume);

            void C3(float NoteVolume);
            void CS3(float NoteVolume);
            void D3(float NoteVolume);
            void DS3(float NoteVolume);
            void E3(float NoteVolume);
            void F3(float NoteVolume);
            void FS3(float NoteVolume);
            void G3(float NoteVolume);
            void GS3(float NoteVolume);
            void A3(float NoteVolume);
            void AS3(float NoteVolume);
            void B3(float NoteVolume);

            void C4(float NoteVolume);
            void CS4(float NoteVolume);
            void D4(float NoteVolume);
            void DS4(float NoteVolume);
            void E4(float NoteVolume);
            void F4(float NoteVolume);
            void FS4(float NoteVolume);
            void G4(float NoteVolume);
            void GS4(float NoteVolume);
            void A4(float NoteVolume);
            void AS4(float NoteVolume);
            void B4(float NoteVolume);

            void C5(float NoteVolume);
            void CS5(float NoteVolume);
            void D5(float NoteVolume);
            void DS5(float NoteVolume);
            void E5(float NoteVolume);
            void F5(float NoteVolume);
            void FS5(float NoteVolume);
            void G5(float NoteVolume);
            void GS5(float NoteVolume);
            void A5(float NoteVolume);
            void AS5(float NoteVolume);
            void B5(float NoteVolume);

            void C6(float NoteVolume);
            void CS6(float NoteVolume);
            void D6(float NoteVolume);
            void DS6(float NoteVolume);
            void E6(float NoteVolume);
            void F6(float NoteVolume);
            void FS6(float NoteVolume);
            void G6(float NoteVolume);
            void GS6(float NoteVolume);
            void A6(float NoteVolume);
            void AS6(float NoteVolume);
            void B6(float NoteVolume);
            
            void C7(float NoteVolume);
        }

    }
#endif