#pragma once
#include <EngineCore/ThirdParty/msdfgen/msdfgen.h>
#include <EngineCore/ThirdParty/msdfgen/msdfgen-ext.h>
#include "EngineResource.h"

// Ό³Έν :
class EngineFont : public UEngineResource
{
public:
	// constrcuter destructer
	EngineFont();
	~EngineFont();

	// delete Function
	EngineFont(const EngineFont& _Other) = delete;
	EngineFont(EngineFont&& _Other) noexcept = delete;
	EngineFont& operator=(const EngineFont& _Other) = delete;
	EngineFont& operator=(EngineFont&& _Other) noexcept = delete;

	void Init();
protected:

private:

};

