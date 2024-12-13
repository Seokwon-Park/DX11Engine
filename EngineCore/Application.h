#pragma once

#include <string>
#include <memory>
#include <EnginePlatform/EngineWindow.h>

class ENGINE_API Application
{
public:
	Application(const std::string& name = "Engine App");
	virtual ~Application();
	inline static Application& Get() { return *Instance; }
private:
	void Run();
	bool m_Running = true;
	bool m_Minimized = false;
	float m_LastFrameTime = 0.0f;
private:
	static Application* Instance;
	friend int main();
};

// To be defined in client
Application* CreateApplication();

