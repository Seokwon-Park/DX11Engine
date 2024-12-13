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


	// ������ʹ� �����մϴ�.
	UEngineWindow::WindowMessageLoop(
		[]()
		{
			//UEngineInitData Data;
			//Core->EngineStart(Data);

			MainWindow.SetWindowPosAndScale(Data.WindowPos, Data.WindowSize);
		},
		[]()
		{
			// ������ ���ư��� �ϰ� ������
		},
		[]()
		{
			// ������ �������� �ϰ� ������.
		});


	//// ���� ������ ���۵Ǿ���.
	//// ������â�� ������ �˾Ƽ� ������ �ϰ�.

	//// Window ������ �Ѵ�.


}