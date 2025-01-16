#pragma once
#include "EngineBase.h"

// ���� :
class  UObject : public std::enable_shared_from_this<UObject>
{
public:
	// constrcuter destructer
	BASE_API UObject();
	BASE_API ~UObject();

	// delete Function
	UObject(const UObject& _Other) = delete;
	UObject(UObject&& _Other) noexcept = delete;
	UObject& operator=(const UObject& _Other) = delete;
	UObject& operator=(UObject&& _Other) noexcept = delete;

	inline std::string GetName() const { return Name; }
	inline std::string_view GetNameView() const { return Name.c_str(); }
	inline virtual void SetName(std::string_view _Name) { Name = _Name.data(); }
	inline virtual bool GetIsActive() const { return IsActive; }
	inline void SetActive(bool _Value) { IsActive = _Value; }

	template<typename ChildPtrType>
	std::shared_ptr<ChildPtrType> GetThis()
	{
		return std::static_pointer_cast<ChildPtrType>(shared_from_this());
	}
	
	inline bool GetIsDestroy()
	{
		return IsDestroy;
	}

	// �ٷ� �װ���?
	// _Time �ð��Ŀ� �׾��.
	inline virtual void Destroy(){IsDestroy = true;}

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
	bool IsDestroy = false;
	bool IsActive = true;

	float DestroyDelay = 0.0f;

	//bool IsDeathTimeCheck = false;
	//float DeathTime = 0.0f;
	//float CurDeathTime = 0.0f;

	std::string Name;

	//bool IsDebugValue = false;
};

