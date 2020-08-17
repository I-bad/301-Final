#include "AudioManager.h"

void AudioManager::Init()
{
	FMOD::Studio::System::create(&system); //calling a create function for the studio system
	if (system) {
		std::cout << "High-level (fmod studio) audio system created." << std::endl;
	}
	system->getLowLevelSystem(&lowLevelSystem); //	bind the fmod system pointer to the studio system
	/*calling 'getLowLevelSystem' generates a point of access to the low level system*/
	if (lowLevelSystem){
		std::cout << "Low-level (fmod) audio system created." << std::endl;
	}
	lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_STEREO, 0); //setting up vairables for the low level system
	system->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, NULL); // init  both systems
}

void AudioManager::Play(const char* fileName/*channels*/ )
{
	lowLevelSystem->createSound(fileName, FMOD_LOOP_OFF, NULL, &music);// createSound function to read in a.wav file and bind it to the pointer
	music->setDefaults(16400, 0); // target frequency, making it play faster or slower, and altering its pitch.
	lowLevelSystem->playSound(music, NULL, false, &playerChannel);
}

void AudioManager::Stop()
{
	lowLevelSystem->close();
}
