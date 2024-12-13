#pragma once

#include <iostream>
#include <EngineBase/EngineMath.h>

//#include "Application.h"

//#pragma comment(lib,"EngineBase.lib")

extern Application* CreateApplication();

int main()
{
	auto app = CreateApplication();
	app->Run();
	delete app;

	return 0;
}
