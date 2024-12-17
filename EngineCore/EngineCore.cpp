#include "EnginePCH.h"
#include "EngineCore.h"
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineIO.h>
#include <EnginePlatform/EngineWindow.h>
#include "IContentsCore.h"

UEngineWindow UEngineCore::MainWindow;
HMODULE UEngineCore::ContentsDLL = nullptr;
std::shared_ptr<IContentsCore> UEngineCore::Core;
std::map<std::string, std::shared_ptr<class ULevel>> UEngineCore::Levels;

std::shared_ptr<class ULevel> UEngineCore::NextLevel;
std::shared_ptr<class ULevel> UEngineCore::CurLevel = nullptr;


UEngineCore::UEngineCore()
{
}

UEngineCore::~UEngineCore()
{
}

void UEngineCore::OpenLevel(std::string_view _Name)
{
	if (false == Levels.contains(_Name.data()))
	{
		MSGASSERT("������ ���� ������ �����Ϸ��� �߽��ϴ�." + std::string(_Name));
		return;
	}


	NextLevel = Levels[_Name.data()];
}


void UEngineCore::WindowInit(HINSTANCE _Instance)
{
	UEngineWindow::EngineWindowInit(_Instance);
	MainWindow.Open("MainWindow");
}

void UEngineCore::LoadContents(std::string_view _DllName)
{
	UEngineDirectory Dir;

	Dir.MoveParentToDirectory("Build");
	Dir.Move("Bin");

	// ���� ��Ȳ�� ���� ��� ����
#ifdef _DEBUG
	Dir.Move("Debug");
#else
	Dir.Move("Release");
#endif

	UEngineFile File = Dir.GetFile(_DllName);

	std::string FullPath = File.ToString();
	// ��Ģ�� ������ۿ� ����.
	ContentsDLL = LoadLibraryA(FullPath.c_str());

	if (nullptr == ContentsDLL)
	{
		MSGASSERT("������ ����� �ε��Ҽ��� �����ϴ�.");
		return;
	}

	INT_PTR(__stdcall * Ptr)(std::shared_ptr<IContentsCore>&) = (INT_PTR(__stdcall*)(std::shared_ptr<IContentsCore>&))GetProcAddress(ContentsDLL, "CreateContentsCore");

	if (nullptr == Ptr)
	{
		MSGASSERT("������ �ھ� ���ο� CreateContentsCoreDefine�� �������� �ʾҽ��ϴ�.");
		return;
	}

	Ptr(Core);

	if (nullptr == Core)
	{
		MSGASSERT("������ �ھ� ������ �����߽��ϴ�.");
		return;
	}
}

void UEngineCore::Shutdown()
{
	Levels.clear();
	EngineLogger::EndLogger();

}

void UEngineCore::EngineStart(HINSTANCE _Instance, std::string_view _DllName)
{
	UEngineDebug::LeakCheck();

	WindowInit(_Instance);

	LoadContents(_DllName);

	// ������ʹ� �����մϴ�.
	UEngineWindow::WindowMessageLoop(
		[]()
		{
			UEngineInitData Data;
			Core->EngineStart(Data);
			MainWindow.SetWindowPosAndScale(Data.WindowPos, Data.WindowSize);
			EngineLogger::StartLogger();
			HWND ConsoleWindow = GetConsoleWindow(); // �ܼ� â �ڵ� ��������
			if (ConsoleWindow)
			{
				// �ܼ� â�� ��� â�� �ڷ� ����
				SetWindowPos(ConsoleWindow, MainWindow.GetHandle(), 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
			}

			// �����Ҷ� �ϰ� ������
			// 1. ������â ũ�� �ٲٰ� �ʹ�.
			//    ���� : ���������� �Ҽ� �ִ�.
		},
		[]()
		{
			// ������ ���ư��� �ϰ� ������
		},
		[]()
		{
			// ������ �������� �ϰ� ������.
			Shutdown();
		});
}