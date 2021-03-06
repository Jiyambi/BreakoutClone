// Breakout - Or A Clone Thereof
// Developed for Ninja Kiwi
// Author: Sarah Herzog
//
// SoundClass
//		The SoundClass encapsulates the DirectSound functionality as well as the 
//		.wav audio loading and playing capabilities.
#pragma once

// |----------------------------------------------------------------------------|
// |								 Linking									|
// |----------------------------------------------------------------------------|
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
 
 
// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>
 
 
// |----------------------------------------------------------------------------|
// |						   Class: SoundClass								|
// |----------------------------------------------------------------------------|
class SoundClass
{
private:
	
	//|------------------------------Type Declarations--------------------------|

	struct WaveHeaderType
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};
 
public:

	//|-------------------------------Public Functions--------------------------|

	// Singleton instance requests
	static SoundClass* GetInstance();
	
	// Initializes sound settings
	bool Initialize(HWND);

	// Releases and cleans up object
	void Shutdown();
 
	// Adjust volumes and loops as needed
	bool Frame(float frameTime);
 
	// Play functions
	bool StartMusic();
	bool StopMusic();
	bool PlayBounce();
	bool PlayBreak();
	bool PlayFire();

	// Toggle Mute
	bool Mute();
	bool UnMute();
 
private:

	//|------------------------------Private Functions--------------------------|

	// Constructors and Destructors
	SoundClass();
	SoundClass(const SoundClass&);
	~SoundClass();
	
	// Initializes/shuts down the direct sound portion of the object
	bool InitializeDirectSound(HWND);
	void ShutdownDirectSound();
 
	// Loads/shuts down a wave file
	bool LoadWaveFile(char*, IDirectSoundBuffer8**, HWND);
	void ShutdownWaveFile(IDirectSoundBuffer8**);
 
	// Processes a single sound buffer
	bool ProcessSound(float frameTime, IDirectSoundBuffer8* &buffer, bool &onOffSetting, LONG &volume);
 
private:
	
	//|-----------------------------Private Data Members------------------------|

	// Instance of the singleton
	static SoundClass* s_instance;

	IDirectSound8* m_DirectSound;
	IDirectSoundBuffer* m_primaryBuffer;

	// Hold the sound samples
	IDirectSoundBuffer8* m_music;
	IDirectSoundBuffer8* m_break;
	IDirectSoundBuffer8* m_bounce;
	IDirectSoundBuffer8* m_fire;

	// Mute toggle
	bool m_globalMute;

	// Play booleans
	bool m_playMusic;

	// Volume sliders
	LONG m_volumeMusic;
};