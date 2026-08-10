# Ongaku
A very Siomple C++ IO Audio Libary with RtAudio and SFML.

# Installation

You need a few Packages. GCC/G++. RtAudio and SFML. Install them over your Command.

Debian/Unbuntu:
sudo apt install libsfml-dev librtaudio-dev

Fedora:
sudo dnf install SFML-devel rtaudio-devel

Arch:
sudo pacman -S sfml rtaudio

OpenSUSE:
sudo zypper install sfml3-devel rtaudio-devel.

After Installing the Package and Git just include ongaku.h in your C++ File.

# Functions

## Ongaku::AudioStream()
Do a simple Static Sound with the Three Parameters: Hertz, Volume and Duration.

## Ongaku::PlayAudioFile()
Play a Audio File with the Four Parameters: Volume, Loop (Boolean), Pitch and Path to the File (String).

## OngakuNotes::Static::C1()
Play the Notes from C1 to C7 with the Static Computer Sound

## OngakuNotes::Instrument::C1()
Play the Notes from C1 to C7 with a Piano Sound
