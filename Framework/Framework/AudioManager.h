#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fmod_studio.hpp>
#include <fmod.hpp>

class AudioManager
{
public:
	AudioManager() {}
	~AudioManager() {}

	void Init(); // premable for setting up the system
	void Play(const char*); // read in the file and set it to the channel
	void Stop(); // close the low level system

private:
	FMOD::System* lowLevelSystem = NULL; //create an FMOD system pointer(lowLevelSystem)
	FMOD::Studio::System* system = NULL; //initialising a pointer to a Studio::System,
	FMOD::Sound* music = NULL; // init a sound pointer 
	FMOD::Channel* playerChannel = NULL; //channel pointer for the sound we're going to play. FMOD binds sounds to channels on playback
};

