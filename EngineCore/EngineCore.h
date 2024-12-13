#pragma once

#include <EngineBase/EngineBase.h>

// Ό³Έν :
class UEngineCore
{
public:
	// constrcuter destructer
	UEngineCore();
	ENGINE_API virtual ~UEngineCore() = 0;

	// delete Function
	UEngineCore(const UEngineCore& _Other) = delete;
	UEngineCore(UEngineCore&& _Other) noexcept = delete;
	UEngineCore& operator=(const UEngineCore& _Other) = delete;
	UEngineCore& operator=(UEngineCore&& _Other) noexcept = delete;
protected:
	bool EngineInit();
	

private:

};

