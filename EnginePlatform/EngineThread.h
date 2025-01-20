#pragma once
#include <thread>

// Ό³Έν :
class UEngineThread
{
public:
	// constrcuter destructer
	PLATFORM_API UEngineThread();
	PLATFORM_API ~UEngineThread();

	// delete Function
	UEngineThread(const UEngineThread& _Other) = delete;
	UEngineThread(UEngineThread&& _Other) noexcept = delete;
	UEngineThread& operator=(const UEngineThread& _Other) = delete;
	UEngineThread& operator=(UEngineThread&& _Other) noexcept = delete;

	PLATFORM_API bool Start(std::string _Name, std::function<void()> _Function);
	PLATFORM_API void Join();
protected:

private:
	std::string Name;
	std::thread ThreadInst;
	std::function<void()> ThreadFunction;

	static void ThreadBaseFunction(UEngineThread* _Thread);

};

