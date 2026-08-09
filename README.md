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

## AudioStream()
Do a simple Static Sound with the Three Parameters: Hertz, Volume and Duration.

## PlayAudioFile()
Play a Audio File with the Four Parameters: Volume, Loop (Boolean), Pitch and Path to the File (String).

## SynthGUI()
This is a Simple Piano. when Starting up, you can just Press The Keys from Tab to the Bracket to Play the White Keys and then few Numbers to Play the Black Keys.
You can change the Default Sound by replacing /Sound/C.wav or Changing the File Path in ongaku.cpp
