#pragma once

#include <iostream>
#include <EngineBase/EngineMath.h>

//#include "Application.h"

//#pragma comment(lib,"EngineBase.lib")

extern Application* CreateApplication();

int main()
{
	std::unique_ptr<Application> app(CreateApplication());
	app->Run();
	//delete app;

	return 0;
}
