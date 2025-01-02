#pragma once
#include "KeyCode.h"
#include "EngineKey.h"
#include <EngineBase/EngineDebug.h>

// ���� :
class UEngineInputSystem
{
public:

	PLATFORM_API UEngineInputSystem();
	PLATFORM_API ~UEngineInputSystem();

	// delete Function
	UEngineInputSystem(const UEngineInputSystem& _Other) = delete;
	UEngineInputSystem(UEngineInputSystem&& _Other) noexcept = delete;
	UEngineInputSystem& operator=(const UEngineInputSystem& _Other) = delete;
	UEngineInputSystem& operator=(UEngineInputSystem&& _Other) noexcept = delete;

	PLATFORM_API static void InitKeys();
	PLATFORM_API static void KeyCheck(float _DeltaTime);
	PLATFORM_API static bool GetKeyDown(int _KeyIndex);
	PLATFORM_API static bool GetKeyUp(int _KeyIndex);
	PLATFORM_API static bool GetKey(int _KeyIndex);


	inline static float GetKeyPressTime(int _KeyIndex)
	{
		if (false == Keys.contains(_KeyIndex))
		{
			MSGASSERT("������ ��ϵ��� ���� Ű�� �����մϴ�.");
			return false;
		}

		return Keys[_KeyIndex].PressTime;
	}

	static bool GetKeyFree(int _KeyIndex)
	{
		if (false == Keys.contains(_KeyIndex))
		{
			MSGASSERT("������ ��ϵ��� ���� Ű�� �����մϴ�.");
			return false;
		}

		return Keys[_KeyIndex].IsFree;
	}

protected:

private:
	PLATFORM_API static std::map<int, UEngineKey> Keys;
	
};

