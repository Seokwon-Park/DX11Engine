#pragma once

// Ό³Έν :
class UEngineThreadPool
{
public:
	// constrcuter destructer
	UEngineThreadPool();
	~UEngineThreadPool();

	// delete Function
	UEngineThreadPool(const UEngineThreadPool& _Other) = delete;
	UEngineThreadPool(UEngineThreadPool&& _Other) noexcept = delete;
	UEngineThreadPool& operator=(const UEngineThreadPool& _Other) = delete;
	UEngineThreadPool& operator=(UEngineThreadPool&& _Other) noexcept = delete;

	PLATFORM_API void Initialize(std::string_view ThreadName = "WorkThread", int Count = 0);
	PLATFORM_API void AddWork(std::function<void()> _Work);

protected:

private:

};

