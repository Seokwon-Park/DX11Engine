#pragma once
#include "EngineBase.h"
#include <format>

// Ό³Έν :
class BASE_API EngineLogger
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

	template <typename T>
	static void Test()
	{
	}
protected:

private:

};



