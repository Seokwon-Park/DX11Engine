#pragma once
#include "EngineBase.h"
#include <format>

// ���� :
class ENGINE_API EngineLogger
{
public:
	// constrcuter destructer
	EngineLogger();
	~EngineLogger();

	// delete Function
	EngineLogger(const EngineLogger& _Other) = delete;
	EngineLogger(EngineLogger&& _Other) noexcept = delete;
	EngineLogger& operator=(const EngineLogger& _Other) = delete;
	EngineLogger& operator=(EngineLogger&& _Other) noexcept = delete;


	static void StartLogger();
	static void EndLogger();
protected:

private:

};


