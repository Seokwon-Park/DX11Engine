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
	using InputEventCallback = std::function<void()>;

	UEngineInputEvent();
	~UEngineInputEvent();

	void EventCheck(KeyCode _Key);

	std::vector<InputEventCallback> PressEvents;
	std::vector<InputEventCallback> DownEvents;
	std::vector<InputEventCallback> UpEvents;
	std::vector<InputEventCallback> FreeEvents;
private:

};



