#include "EnginePCH.h"
#include "EngineCore.h"
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineIO.h>
#include <EnginePlatform/EngineWindow.h>
#include "IContentsCore.h"

UEngineWindow UEngineCore::MainWindow;
HMODULE UEngineCore::ContentsDLL = nullptr;
std::shared_ptr<IContentsCore> UEngineCore::Core;

std::shared_ptr<class ULevel> UEngineCore::NextLevel;
std::shared_ptr<class ULevel> UEngineCore::CurLevel = nullptr;
std::map<std::string, std::shared_ptr<class ULevel>> UEngineCore::Levels;


UEngineCore::UEngineCore()
{
}

UEngineCore::~UEngineCore()
{
}

std::shared_ptr<ULevel> UEngineCore::NewLevelCreate(std::string_view _Name)
{
	// 만들기만 하고 보관을 안하면 앤 그냥 지워집니다. <= 

	// 만들면 맵에 넣어서 레퍼런스 카운트를 증가시킵니다.
	// UObject의 기능이었습니다.
	std::shared_ptr<ULevel> Ptr = std::make_shared<ULevel>();
	Ptr->SetName(_Name);

	Levels.insert({ _Name.data(), Ptr });

	std::cout << "NewLevelCreate" << std::endl;

	return Ptr;
}

void UEngineCore::OpenLevel(std::string_view _Name)
{
	if (false == Levels.contains(_Name.data()))
	{
		MSGASSERT("만들지 않은 레벨로 변경하려고 했습니다." + std::string(_Name));
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

	// 빌드 상황에 따라서 경로 변경
#ifdef _DEBUG
	Dir.Move("Debug");
#else
	Dir.Move("Release");
#endif

	UEngineFile File = Dir.GetFile(_DllName);

	std::string FullPath = File.ToString();
	// 규칙이 생길수밖에 없다.
	ContentsDLL = LoadLibraryA(FullPath.c_str());

	if (nullptr == ContentsDLL)
	{
		MSGASSERT("컨텐츠 기능을 로드할수가 없습니다.");
		return;
	}

	INT_PTR(__stdcall * Ptr)(std::shared_ptr<IContentsCore>&) = (INT_PTR(__stdcall*)(std::shared_ptr<IContentsCore>&))GetProcAddress(ContentsDLL, "CreateContentsCore");

	if (nullptr == Ptr)
	{
		MSGASSERT("컨텐츠 코어 내부에 CreateContentsCoreDefine을 정의하지 않았습니다.");
		return;
	}

	Ptr(Core);

	if (nullptr == Core)
	{
		MSGASSERT("컨텐츠 코어 생성에 실패했습니다.");
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
	//메모리 누수 Check
	UEngineDebug::LeakCheck();

	//윈도우 초기화 
	WindowInit(_Instance);

	//Contents DLL 로딩
	LoadContents(_DllName);

	//게임 루프 시작
	UEngineWindow::WindowMessageLoop(
		[]()
		{
			UEngineInitData Data;
			Core->EngineStart(Data);
			MainWindow.SetWindowPosAndScale(Data.WindowPos, Data.WindowSize);
			EngineLogger::StartLogger();
			HWND ConsoleWindow = GetConsoleWindow(); // 콘솔 창 핸들 가져오기
			if (ConsoleWindow)
			{
				// 콘솔 창을 모든 창의 뒤로 보냄
				SetWindowPos(ConsoleWindow, MainWindow.GetHandle(), 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
			}

			// 시작할때 하고 싶은것
			// 1. 윈도우창 크기 바꾸고 싶다.
			//    문제 : 컨텐츠만이 할수 있다.
		},
		[]()
		{
			// 엔진이 돌아갈 때 하고 싶은것
		},
		[]()
		{
			// 엔진이 끝났을 때 하고 싶은것.
			Shutdown();
		});
}