#include "EnginePCH.h"
#include "EngineInputSystem.h"

std::map<int, UEngineKey> UEngineInputSystem::Keys;

UEngineInputSystem::UEngineInputSystem()
{

}

UEngineInputSystem::~UEngineInputSystem()
{

}

void UEngineInputSystem::InitKeys()
{
	for (int i = 0; i < 255; i++)
	{
		Keys.insert(std::make_pair(i, UEngineKey(i)));
	}
}

void UEngineInputSystem::KeyCheck(float _DeltaTime)
{
	for (std::pair<const int,UEngineKey>& Itr : Keys)
	{
		UEngineKey& CurKey = Itr.second;
		CurKey.KeyCheck(_DeltaTime);
	}
}

bool UEngineInputSystem::GetKeyDown(int _KeyIndex)
{
	if (false == Keys.contains(_KeyIndex))
	{
		MSGASSERT("아직도 등록되지 않은 키가 존재합니다.");
		return false;
	}

	return Keys[_KeyIndex].IsDown;
}

bool UEngineInputSystem::GetKeyUp(int _KeyIndex)
{
	if (false == Keys.contains(_KeyIndex))
	{
		MSGASSERT("아직도 등록되지 않은 키가 존재합니다.");
		return false;
	}

	return Keys[_KeyIndex].IsUp;
}

bool UEngineInputSystem::GetKey(int _KeyIndex)
{
	if (false == Keys.contains(_KeyIndex))
	{
		MSGASSERT("아직도 등록되지 않은 키가 존재합니다.");
		return false;
	}

	return Keys[_KeyIndex].IsPress;
}



