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
	using EventCallback = std::function<void()>;

	UEngineInputEvent();
	~UEngineInputEvent();

	void EventCheck(KeyCode _Key);

	std::vector<EventCallback> PressEvents;
	std::vector<EventCallback> DownEvents;
	std::vector<EventCallback> UpEvents;
	std::vector<EventCallback> FreeEvents;
private:

};



