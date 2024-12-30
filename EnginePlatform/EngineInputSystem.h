#pragma once
#include "KeyCode.h"
#include <EngineBase/EngineDebug.h>

// 설명 :
class UEngineInputSystem
{
public:

	ENGINE_API UEngineInputSystem();
	// constrcuter destructer
	ENGINE_API ~UEngineInputSystem();

	// delete Function
	UEngineInputSystem(const UEngineInputSystem& _Other) = delete;
	UEngineInputSystem(UEngineInputSystem&& _Other) noexcept = delete;
	UEngineInputSystem& operator=(const UEngineInputSystem& _Other) = delete;
	UEngineInputSystem& operator=(UEngineInputSystem&& _Other) noexcept = delete;

	ENGINE_API static UEngineInputSystem& GetInstance()
	{
		// 플랫폼
		static UEngineInputSystem Inst = UEngineInputSystem();
		return Inst;
	}

	ENGINE_API static void KeyCheck(float _DeltaTime);
	static bool GetKeyDown(int _KeyIndex)
	{
		if (false == GetInstance().Keys.contains(_KeyIndex))
		{
			MSGASSERT("아직도 등록되지 않은 키가 존재합니다.");
			return false;
		}

		return GetInstance().Keys[_KeyIndex].IsDown;
	}

	static bool GetKeyUp(int _KeyIndex)
	{
		if (false == GetInstance().Keys.contains(_KeyIndex))
		{
			MSGASSERT("아직도 등록되지 않은 키가 존재합니다.");
			return false;
		}

		return GetInstance().Keys[_KeyIndex].IsUp;
	}

	static bool GetKey(int _KeyIndex)
	{
		if (false == GetInstance().Keys.contains(_KeyIndex))
		{
			MSGASSERT("아직도 등록되지 않은 키가 존재합니다.");
			return false;
		}

		return GetInstance().Keys[_KeyIndex].IsPress;
	}

	static float GetKeyPressTime(int _KeyIndex)
	{
		if (false == GetInstance().Keys.contains(_KeyIndex))
		{
			MSGASSERT("아직도 등록되지 않은 키가 존재합니다.");
			return false;
		}

		return GetInstance().Keys[_KeyIndex].PressTime;
	}


	static bool GetKeyFree(int _KeyIndex)
	{
		if (false == GetInstance().Keys.contains(_KeyIndex))
		{
			MSGASSERT("아직도 등록되지 않은 키가 존재합니다.");
			return false;
		}

		return GetInstance().Keys[_KeyIndex].IsFree;
	}


protected:

private:
	class UEngineKey
	{
	public:
		int Key = -1;
		bool IsDown = false;
		bool IsPress = false;
		bool IsUp = false;
		bool IsFree = true;

		float PressTime = 0.0f;

	UEngineKey() {}
		UEngineKey(int _Key)
			:Key(_Key) {}

		void KeyCheck(float _DeltaTime);
	};

	std::map<int, UEngineKey> Keys;
};

