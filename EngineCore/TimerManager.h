#pragma once



// Ό³Έν :
class FTimerManager
{
public:
	using EventFn = std::function<void()>;
	
	struct FTimeEvent
	{
		EventFn Function;
		float CurTime;
		float DelayTime;
		bool IsLoop;
	};
	// constrcuter destructer
	FTimerManager();
	~FTimerManager();

	// delete Function
	FTimerManager(const FTimerManager& _Other) = delete;
	FTimerManager(FTimerManager&& _Other) noexcept = delete;
	FTimerManager& operator=(const FTimerManager& _Other) = delete;
	FTimerManager& operator=(FTimerManager&& _Other) noexcept = delete;

	ENGINE_API void SetTimer(EventFn _Function, float _DelayTime, bool _IsLoop);
	void Tick(float _DeltaTime);
protected:

private:
	std::list<FTimeEvent> TimeEvents;
};

