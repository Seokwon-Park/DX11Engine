#pragma once
#include "EngineBase.h"

// 설명 :
class  UObject : public std::enable_shared_from_this<UObject>
{
public:
	// constrcuter destructer
	ENGINE_API UObject();
	ENGINE_API ~UObject();

	// delete Function
	UObject(const UObject& _Other) = delete;
	UObject(UObject&& _Other) noexcept = delete;
	UObject& operator=(const UObject& _Other) = delete;
	UObject& operator=(UObject&& _Other) noexcept = delete;

	inline std::string GetName() const { return Name; }
	inline std::string_view GetNameView() const { return Name.c_str(); }
	inline virtual void SetName(std::string_view _Name) { Name = _Name.data(); }

	//virtual bool IsActive()
	//{
	//	return IsActiveValue && false == IsDestroyValue;
	//}

	//virtual bool IsDestroy()
	//{
	//	return IsDestroyValue;
	//}

	// 바로 죽겠죠?
	// _Time 시간후에 죽어라.
	//void Destroy(float _Time = 0.0f)
	//{
	//	DeathTime = _Time;

	//	if (0.0f < _Time)
	//	{
	//		IsDeathTimeCheck = true;
	//		return;
	//	}

	//	IsDestroyValue = true;
	//}

	//virtual void ReleaseTimeCheck(float _DeltaTime)
	//{
	//	if (false == IsDeathTimeCheck)
	//	{
	//		return;
	//	}

	//	CurDeathTime += _DeltaTime;

	//	if (DeathTime <= CurDeathTime)
	//	{
	//		IsDestroyValue = true;
	//	}
	//}

	//virtual void ReleaseCheck(float _DeltaTime)
	//{

	//}

	//// 모든 기능 정지.
	//// 얼음 외부에서 다른 객체가 풀어줘야 한다.
	//void SetActive(bool _IsActive)
	//{
	//	IsActiveValue = _IsActive;
	//}

	//void SetActiveSwitch()
	//{
	//	IsActiveValue = !IsActiveValue;
	//}

	//bool IsDebug()
	//{
	//	return IsDebugValue;
	//}

	//void DebugOn()
	//{
	//	IsDebugValue = true;
	//}

	//void DebugOff()
	//{
	//	IsDebugValue = false;
	//}

	//void DebugSwitch()
	//{
	//	IsDebugValue = !IsDebugValue;
	//}

protected:

private:
	//bool IsDestroyValue = false;
	//bool IsActiveValue = true;

	//bool IsDeathTimeCheck = false;
	//float DeathTime = 0.0f;
	//float CurDeathTime = 0.0f;

	std::string Name;

	//bool IsDebugValue = false;
};

