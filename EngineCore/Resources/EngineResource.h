#pragma once
#include <EngineBase/EngineIO.h>
#include <EngineBase/Object.h>

// Ό³Έν :
class UEngineResource : public UObject
{
public:
	// constrcuter destructer
	UEngineResource();
	virtual ~UEngineResource();

	// delete Function
	UEngineResource(const UEngineResource& _Other) = delete;
	UEngineResource(UEngineResource&& _Other) noexcept = delete;
	UEngineResource& operator=(const UEngineResource& _Other) = delete;
	UEngineResource& operator=(UEngineResource&& _Other) noexcept = delete;

	inline void SetPath(std::string_view _Path) { Path = UEnginePath(_Path); }

protected:
	UEnginePath Path;
private:
};

