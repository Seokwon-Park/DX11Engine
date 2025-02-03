#pragma once
#include "ThirdParty/FMOD/include/fmod.hpp"

// Ό³Έν :
class UEngineAudioSystem
{
public:
	// constrcuter destructer
	~UEngineAudioSystem();

	// delete Function
	UEngineAudioSystem(const UEngineAudioSystem& _Other) = delete;
	UEngineAudioSystem(UEngineAudioSystem&& _Other) noexcept = delete;
	UEngineAudioSystem& operator=(const UEngineAudioSystem& _Other) = delete;
	UEngineAudioSystem& operator=(UEngineAudioSystem&& _Other) noexcept = delete;

	inline static void Init()
	{
		if (Instance == nullptr)
		{
			Instance = new UEngineAudioSystem();
		}
	}

	inline static UEngineAudioSystem* GetInstance()
	{
		return Instance;
	}


	inline static FMOD::System* GetSystem()
	{
		return Instance->FMODSystem;
	}

	inline static void Release()
	{
		Instance->FMODSystem->close();
		Instance->FMODSystem->release();
		Instance->FMODSystem = nullptr;
		delete Instance;
	}
	static void AudioUpdate() { Instance->Update(); }

	static void StopAllSounds() { Instance->FMODChannelGroup->stop();}

protected:

private:
	UEngineAudioSystem();
	void Update();

	static UEngineAudioSystem* Instance;
	FMOD::System* FMODSystem = nullptr;
	FMOD::ChannelGroup* FMODChannelGroup = nullptr;
};

