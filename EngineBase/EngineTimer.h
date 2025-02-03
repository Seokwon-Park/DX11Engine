#pragma once
#include <chrono>
#include <thread>



// 설명 :
class UEngineTimer
{
public:
	using Clock = std::chrono::steady_clock;
	using TimePoint = std::chrono::time_point<Clock>;
	using Duration = std::chrono::duration<float>;

	// constrcuter destructer
	BASE_API UEngineTimer();
	BASE_API ~UEngineTimer();

	// delete Function
	UEngineTimer(const UEngineTimer& _Other) = delete;
	UEngineTimer(UEngineTimer&& _Other) noexcept = delete;
	UEngineTimer& operator=(const UEngineTimer& _Other) = delete;
	UEngineTimer& operator=(UEngineTimer&& _Other) noexcept = delete;

	BASE_API void TimeCheck();

	BASE_API inline float GetDeltaTime() const { return DeltaTime; }

	BASE_API inline float GetCurTime()  { return std::chrono::duration<float>(Clock::now().time_since_epoch()).count(); }

	BASE_API void TimeReset();

	//float End();

	//double DEnd();

	//void SetTimeScale(float _Scale)
	//{
	//	TimeScale = _Scale;
	//}

protected:

private:
	TimePoint PrevTime;
	// LONGLONG QuadPart => 10000 / 1 기준으로 부터 10000초 지났어요

	TimePoint CurrentTime;
	// LONGLONG QuadPart => 10002 

	float DeltaTime = 0.0f;

	float TimeScale = 1.0f;
};
