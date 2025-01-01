#pragma once

// 클래스 설명 :
class UEngineDelegate
{
public:
	using EventCallback = std::function<void()>;
	// Constrcuter Destructer
	BASE_API UEngineDelegate();
	BASE_API UEngineDelegate(EventCallback _Function);
	BASE_API ~UEngineDelegate();

	// Delete Function
	BASE_API UEngineDelegate(const UEngineDelegate& _Other);
	UEngineDelegate(UEngineDelegate&& _Other) noexcept = delete;
	UEngineDelegate& operator=(const UEngineDelegate& _Other) = delete;
	UEngineDelegate& operator=(UEngineDelegate&& _Other) noexcept = delete;

	BASE_API inline bool IsEmpty() { return Events.empty(); }
	BASE_API inline void operator+=(EventCallback _Function) { Events.push_back(_Function); }
	BASE_API inline void Clear() { Events.clear(); }
	BASE_API inline void operator()()
	{
		for (EventCallback Event : Events)
		{
			Event();
		}
	}
protected:

private:
	std::list<EventCallback> Events;
};
