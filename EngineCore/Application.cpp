#include "EnginePCH.h"
#include <EngineBase/EngineBase.h>
#include "Application.h"

//Application::Application()
//{
//}

Application* Application::Instance = nullptr;

Application::Application(const std::string& name)
	:HInstance(GetModuleHandle(NULL))
{
}

Application::~Application()
{
}

void Application::Run()
{
	UEngineCore::EngineStart(HInstance, "");
}
