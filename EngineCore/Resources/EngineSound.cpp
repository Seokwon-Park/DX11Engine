#include "EnginePCH.h"
#include "EngineSound.h"
#include <EngineBase/EngineString.h>
#include <EngineCore/Core/EngineAudioSystem.h>

UEngineSound::UEngineSound()
{
}

UEngineSound::~UEngineSound()
{
	if (nullptr != FMODSound)
	{
		FMODSound->release();
		FMODSound = nullptr;
	}
}
void UEngineSound::Load(std::string_view _Path, bool _IsLoop)
{
	FMOD_MODE LoopMode = _IsLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;

	FMOD_RESULT Result = UEngineAudioSystem::GetSystem()->createSound(_Path.data(), LoopMode, nullptr, &FMODSound);

	if (FMOD_RESULT::FMOD_OK != Result)
	{
		MSGASSERT("파일로드에 실패함");
	}

	if (nullptr == FMODSound)
	{
		MSGASSERT("사운드 로딩에 실패했습니다" + std::string(_Path));
	}
}

void UEngineSound::Play()
{
	UEngineAudioSystem::GetSystem()->playSound(FMODSound, nullptr, false, &FMODChannel);
}
void UEngineSound::Stop()
{
	FMODChannel->stop();
}
void UEngineSound::SetVolume(float _Volume)
{
	FMODChannel->setVolume(_Volume);
}