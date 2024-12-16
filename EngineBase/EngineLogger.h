#pragma once

// Ό³Έν :
class EngineLogger
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

protected:

private:

};

