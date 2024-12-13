#pragma once

#include <string>
#include <memory>
#include <EnginePlatform/EngineWindow.h>

#include "EngineCore.h"

class ENGINE_API Application
{
public:
	Application(const std::string& name = "Engine App");
	virtual ~Application();
	inline static Application& Get() { return *Instance; }
protected:

private:
	void Run();

	static Application* Instance;
	friend int main();

	HINSTANCE HInstance = nullptr;
};

// To be defined in client
Application* CreateApplication();

