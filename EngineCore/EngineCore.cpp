#include "EnginePCH.h"
#include "EngineCore.h"
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineIO.h>
#include <EnginePlatform/EngineWindow.h>
#include "IContentsCore.h"
#include "Graphics/DirectX11/DX11DeviceContext.h"


UEngineDeviceContext* UEngineCore::GraphicsDevice;
UEngineWindow UEngineCore::MainWindow;
HMODULE UEngineCore::ContentsDLL = nullptr;
std::shared_ptr<IContentsCore> UEngineCore::Core;

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

	INT_PTR(__stdcall *Ptr)(std::shared_ptr<IContentsCore>&) = (INT_PTR(__stdcall*)(std::shared_ptr<IContentsCore>&))GetProcAddress(ContentsDLL, "CreateContentsCore");

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


void UEngineCore::EngineStart(HINSTANCE _Instance, std::string_view _DllName)
{
	//_CrtSetBreakAlloc(265);
	//�޸� ���� Check
	UEngineDebug::LeakCheck();

	//������ �ʱ�ȭ 
	WindowInit(_Instance);

	//Contents DLL �ε�
	LoadContentsDll(_DllName);

	GraphicsDevice = new DX11DeviceContext();

	//���� ���� ����
	UEngineWindow::WindowMessageLoop(
		[]()
		{
			EngineLogger::StartLogger();
			UEngineInitData Data;
			Core->EngineStart(Data);
			MainWindow.SetWindowPosAndScale(Data.WindowPos, Data.WindowSize);

			GraphicsDevice->Init(MainWindow);
			GraphicsDevice->SetClearColor(FColor::BLACK);
			GraphicsDevice->SetRendererAPI(ERendererAPI::DirectX11);

			HWND ConsoleWindow = GetConsoleWindow(); // �ܼ� â �ڵ� ��������
			if (ConsoleWindow)
			{
				// �ܼ� â�� ��� â�� �ڷ� ����
				SetWindowPos(ConsoleWindow, MainWindow.GetHandle(), 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
			}

			// �����Ҷ� �ϰ� ������
		},
		[]()
		{
			// ������ ���ư� �� �ϰ� ������
			EngineUpdate();
		},
		[]()
		{
			Core = nullptr;
			// ������ ������ �� �ϰ� ������.
			EngineShutdown();
			delete GraphicsDevice;
		});
}

void UEngineCore::EngineUpdate()
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
	}

	CurLevel->Tick(0.0f);
	CurLevel->Render(0.0f);
}

void UEngineCore::EngineShutdown()
{
	CurLevel = nullptr;
	NextLevel = nullptr;
	Levels.clear();
	EngineLogger::EndLogger();
}
