#pragma once

#include <EngineBase/EngineBase.h>
#include <EnginePlatform/EngineWindow.h>

class ENGINE_API UEngineCore
{
public:
	// constrcuter destructer
	UEngineCore();
	virtual ~UEngineCore() = 0;

	static void EngineStart(HINSTANCE _Instance);

protected:

private:
	static UEngineWindow MainWindow;

	static void WindowInit(HINSTANCE _Instance);
};


