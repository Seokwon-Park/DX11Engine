#pragma once

class UEngineKey
{
public:
	int Key = -1;
	bool IsDown = false;
	bool IsPress = false;
	bool IsUp = false;
	bool IsFree = true;

	float PressTime = 0.0f;

	UEngineKey() {}
	UEngineKey(int _Key)
		:Key(_Key) {}

	void KeyCheck(float _DeltaTime);
};