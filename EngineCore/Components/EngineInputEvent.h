#pragma once

enum class KeyEvent
{
	Down,
	Press,
	Free,
	Up,
};

class UEngineInputEvent
{
public:
	using EventCallBack = std::function<void()>;

	UEngineInputEvent();
	~UEngineInputEvent();

	void EventCheck(KeyCode _Key);

	std::vector<EventCallBack> PressEvents;
	std::vector<EventCallBack> DownEvents;
	std::vector<EventCallBack> UpEvents;
	std::vector<EventCallBack> FreeEvents;
private:

};



