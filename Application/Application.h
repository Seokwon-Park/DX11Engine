#pragma once

#include <string>
#include <memory>
#include <EnginePlatform/EngineWindow.h>

class Application
{
public:
	Application(const std::string& name = "Engine App");
	virtual ~Application();

//	inline UEngineWindow& GetWindow() { return *m_Window; }
//	void Close();
//
//	inline static Application& Get() { return *Instance; }
//private:
//	void Run();
//
//	std::unique_ptr<UEngineWindow> m_Window;
//	bool m_Running = true;
//	bool m_Minimized = false;
//	bool m_TitleBarHovered;
//	float m_LastFrameTime = 0.0f;
//private:
//	static Application* Instance;
	//friend int ::main();
};

// To be defined in client
Application* CreateApplication();

