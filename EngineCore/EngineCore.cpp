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
		MSGASSERT("�̹� �����ϴ� ���� �̸��Դϴ�." + std::string(_Name));
		return;
	}

	Levels.insert({ _Name.data(), _Level });
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

	// ���� ��Ȳ�� ���� ��� ����
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
		MSGASSERT("������ ����� �ε��Ҽ��� �����ϴ�.");
		return;
	}

	INT_PTR(__stdcall * Ptr)(std::shared_ptr<IContentsCore>&) = (INT_PTR(__stdcall*)(std::shared_ptr<IContentsCore>&))GetProcAddress(ContentsDLL, "CreateContentsCore");

	if (nullptr == Ptr)
	{
		MSGASSERT("������ �ھ� ���ο� CreateContentsCoreDefine�� �������� �ʾҽ��ϴ�.");
		return;
	}

	Ptr(ContentsCore);

	if (nullptr == ContentsCore)
	{
		MSGASSERT("������ �ھ� ������ �����߽��ϴ�.");
		return;
	}
}


void UEngineCore::EngineStart(HINSTANCE _Instance, std::string_view _DllName)
{

	//�޸� ���� Check
	UEngineDebug::LeakCheck();
	//_CrtSetBreakAlloc(178);

	//������ �ʱ�ȭ 
	WindowInit(_Instance);

	//Contents DLL �ε�
	LoadContentsDll(_DllName);

	GraphicsDeviceContext = new UEngineDeviceContext();
	//���� ���� ����
	UEngineWindow::WindowMessageLoop(
		[]()
		{
			EngineLogger::StartLogger();
			UEngineInputSystem::InitKeys();
			GraphicsDeviceContext->Init(MainWindow);
			//Default States�� �ݵ�� ���� �����Ǿ�� ��.
			UStateManager::CreateDefaultStates();
			UResourceManager::CreateDefaultResources();
			ContentsCore->EngineStart(Data);
			MainWindow.SetWindowPosAndScale(Data.WindowPos, Data.WindowSize);
			//GraphicsDevice->SetRendererAPI(ERendererAPI::DirectX11);
			GraphicsDeviceContext->CreateBackBuffer(MainWindow);
			GraphicsDeviceContext->SetClearColor(FColor::WHITE);
			HWND ConsoleWindow = GetConsoleWindow(); // �ܼ� â �ڵ� ��������
			if (ConsoleWindow)
			{
				// �ܼ� â�� ��� â�� �ڷ� ����
				SetWindowPos(ConsoleWindow, MainWindow.GetHandle(), 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
			}

			ImGuiLayer::Init();
			// �����Ҷ� �ϰ� ������
		},
		[]()
		{
			// ������ ���ư� �� �ϰ� ������
			EngineUpdate();
		},
		[]()
		{
			// ������ ������ �� �ϰ� ������.
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
