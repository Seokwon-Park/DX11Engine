#include "EnginePCH.h"
#include "EngineCore.h"
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineIO.h>
#include <EnginePlatform/EngineWindow.h>
#include "IContentsCore.h"
#include "ResourceManager.h"
#include "StateManager.h"
#include "EngineDeviceContext.h"
#include "GUI/ImGuiLayer.h"

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DBG_NEW
#endif // DBG_NEW
#endif // _DEBUG


UEngineDeviceContext* UEngineCore::GraphicsDeviceContext;

HMODULE UEngineCore::ContentsDLL = nullptr;
std::shared_ptr<IContentsCore> UEngineCore::ContentsCore;

UEngineTimer UEngineCore::Timer;
UEngineInitData UEngineCore::Data;
UEngineWindow UEngineCore::MainWindow;
FTimerManager UEngineCore::TimerManager;

std::shared_ptr<class ULevel> UEngineCore::NextLevel;
std::shared_ptr<class ULevel> UEngineCore::CurLevel = nullptr;

UEngineCore::UEngineCore()
{
}

UEngineCore::~UEngineCore()
{
}

void UEngineCore::AddLevel(std::string_view _Name, std::shared_ptr<ULevel> _Level)
{
	if (true == Levels.contains(_Name.data()))
	{
		MSGASSERT("이미 존재하는 레벨 이름입니다." + std::string(_Name));
		return;
	}

	Levels.insert({ _Name.data(), _Level });
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

UEngineDeviceContext* UEngineCore::GetGraphicsDeviceContext()
{
	return GraphicsDeviceContext;
}

FTimerManager& UEngineCore::GetTimerManager()
{
	return TimerManager;
}

void UEngineCore::WindowInit(HINSTANCE _Instance)
{
	UEngineWindow::EngineWindowInit(_Instance);
	MainWindow.Open("MainWindow");
}

void UEngineCore::LoadContentsDll(std::string_view _DllName)
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

	Ptr(ContentsCore);

	if (nullptr == ContentsCore)
	{
		MSGASSERT("컨텐츠 코어 생성에 실패했습니다.");
		return;
	}
}


void UEngineCore::EngineStart(HINSTANCE _Instance, std::string_view _DllName)
{

	//메모리 누수 Check
	UEngineDebug::LeakCheck();
	//_CrtSetBreakAlloc(178);

	//윈도우 초기화 
	WindowInit(_Instance);

	//Contents DLL 로딩
	LoadContentsDll(_DllName);

	GraphicsDeviceContext = new UEngineDeviceContext();
	//게임 루프 시작
	UEngineWindow::WindowMessageLoop(
		[]()
		{
			EngineLogger::StartLogger();
			UEngineInputSystem::InitKeys();
			GraphicsDeviceContext->Init(MainWindow);
			//Default States가 반드시 먼저 생성되어야 함.
			UStateManager::CreateDefaultStates();
			UResourceManager::CreateDefaultResources();
			ContentsCore->EngineStart(Data);
			MainWindow.SetWindowPosAndScale(Data.WindowPos, Data.WindowSize);
			//GraphicsDevice->SetRendererAPI(ERendererAPI::DirectX11);
			GraphicsDeviceContext->CreateBackBuffer(MainWindow);
			GraphicsDeviceContext->SetClearColor(FColor::WHITE);
			HWND ConsoleWindow = GetConsoleWindow(); // 콘솔 창 핸들 가져오기
			if (ConsoleWindow)
			{
				// 콘솔 창을 모든 창의 뒤로 보냄
				SetWindowPos(ConsoleWindow, MainWindow.GetHandle(), 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
			}

			ImGuiLayer::Init();
			// 시작할때 하고 싶은것
		},
		[]()
		{
			// 엔진이 돌아갈 때 하고 싶은것
			EngineUpdate();
		},
		[]()
		{
			// 엔진이 끝났을 때 하고 싶은것.
			ContentsCore = nullptr;
			EngineShutdown();
		});
}

void UEngineCore::EngineUpdate()
{
	Timer.TimeCheck();
	float DeltaTime = Timer.GetDeltaTime();
	
	//std::cout << "DeltaTime - " << 1.0f / DeltaTime << '\n';

	CheckLevelChange();
	UEngineInputSystem::KeyCheck(DeltaTime);

	TimerManager.Tick(DeltaTime);
	CurLevel->Tick(DeltaTime);
	CurLevel->Render(DeltaTime);
	CurLevel->Release(DeltaTime);
}

void UEngineCore::CheckLevelChange()
{
	if (nullptr != NextLevel)
	{
		if (nullptr != CurLevel)
		{
			//CurLevel->LevelChangeEnd();
		}

		CurLevel = NextLevel;

		//CurLevel->LevelChangeStart();
		NextLevel = nullptr;
		Timer.TimeReset();
	}
}

void UEngineCore::EngineShutdown()
{
	ImGuiLayer::Shutdown();
	CurLevel = nullptr;
	NextLevel = nullptr;
	Levels.clear();
	UResourceManager::Release();
	UStateManager::Release();
	delete GraphicsDeviceContext;
	EngineLogger::EndLogger();
}
