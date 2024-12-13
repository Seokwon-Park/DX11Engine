#include "EnginePCH.h"
#include "EngineCore.h"
#include <EngineBase/Debug/EngineDebug.h>
#include <EnginePlatform/EngineWindow.h>

UEngineWindow UEngineCore::MainWindow;

UEngineCore::UEngineCore()
{
}

UEngineCore::~UEngineCore()
{
}

void UEngineCore::WindowInit(HINSTANCE _Instance)
{
	UEngineWindow::EngineWindowInit(_Instance);
	MainWindow.Open("MainWindow");
}

void UEngineCore::EngineStart(HINSTANCE _Instance)
{
	UEngineDebug::LeakCheck();

	WindowInit(_Instance);

	//LoadContents(_DllName);


	// 윈도우와는 무관합니다.
	UEngineWindow::WindowMessageLoop(
		[]()
		{
			//UEngineInitData Data;
			//Core->EngineStart(Data);

			MainWindow.SetWindowPosAndScale(Data.WindowPos, Data.WindowSize);
		},
		[]()
		{
			// 엔진이 돌아갈때 하고 싶은것
		},
		[]()
		{
			// 엔진이 끝났을때 하고 싶은것.
		});


	//// 게임 엔진이 시작되었다.
	//// 윈도우창은 엔진이 알아서 띄워줘야 하고.

	//// Window 띄워줘야 한다.


}