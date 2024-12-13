#include "EnginePCH.h"
#include "EngineWindow.h"
#include <EngineBase/Debug/EngineDebug.h>

// 멀티플랫폼으로 짜려면
//#ifdef _WINDOWS
//#include <Windows.h>
//#elseif _리눅스
//
//#elseif 안드로이드
//#endif 

HINSTANCE UEngineWindow::HInstance = nullptr;
std::map<std::string, WNDCLASSEXA> UEngineWindow::WindowClasses;
int WindowCount = 0;
bool UEngineWindow::LoopActive = true;

LRESULT CALLBACK UEngineWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		++WindowCount;
		break;

	case WM_PAINT:
		break;
	case WM_DESTROY:
		--WindowCount;
		if (0 >= WindowCount)
		{
			UEngineWindow::LoopActive = false;
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


void UEngineWindow::EngineWindowInit(HINSTANCE _Instance)
{
	HInstance = _Instance;

	// 어차피 무조건 해줘야 한다면 여기서 하려고 한것.
	// 디폴트 윈도우 클래스 등록
	WNDCLASSEXA wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = HInstance;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = "Default";
	wcex.hIconSm = nullptr;
	CreateWindowClass(wcex);
}

int UEngineWindow::WindowMessageLoop(std::function<void()> _StartFunction, std::function<void()> _FrameFunction, std::function<void()> _EndFunction)
{
	MSG msg = MSG();

	if (nullptr != _StartFunction)
	{
		_StartFunction();
	}

	if (nullptr == _FrameFunction)
	{
		MSGASSERT("업데이트 펑션이 바인드 되어 있지 않습니다.");
		return 0;
	}

	while (true == LoopActive)
	{
		if (0 != PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		_FrameFunction();
	}

	if (nullptr != _EndFunction)
	{
		_EndFunction();
	}

	return (int)msg.wParam;
}

void UEngineWindow::CreateWindowClass(const WNDCLASSEXA& _Class)
{
	// 일반적인 맵의 사용법

	std::map<std::string, WNDCLASSEXA>::iterator EndIter = WindowClasses.end();
	std::map<std::string, WNDCLASSEXA>::iterator FindIter = WindowClasses.find(std::string(_Class.lpszClassName));

	// ckw
	if (EndIter != FindIter)
	{
		// std::string ErrorText = "같은 이름의 윈도우 클래스를 2번 등록했습니다" + std::string(_Class.lpszClassName);

		// std::string 내부에 들고 있는 맴버변수 => std::string => std::vector<char>
		// std::vector<char> char* = new char[100];
		// ErrorText const char* 리턴해주는 함수가 c_str()
		// const char* Text = ErrorText.c_str();
		MSGASSERT(std::string(_Class.lpszClassName) + " 같은 이름의 윈도우 클래스를 2번 등록했습니다");
		return;
	}

	RegisterClassExA(&_Class);

	WindowClasses.insert(std::pair{ _Class.lpszClassName, _Class });
}

UEngineWindow::UEngineWindow()
{

}

UEngineWindow::~UEngineWindow()
{
	// 릴리즈하는 순서는 왠만하면 만들어진 순서의 역순이 좋다.
	if (nullptr != WindowHandle)
	{
		DestroyWindow(WindowHandle);
		WindowHandle = nullptr;
	}
}

void UEngineWindow::Create(std::string_view _TitleName, std::string_view _ClassName)
{
	if (nullptr != WindowHandle)
	{
		return;
	}

	if (false == WindowClasses.contains(_ClassName.data()))
	{
		MSGASSERT(std::string(_ClassName) + " 등록하지 않은 클래스로 윈도우창을 만들려고 했습니다");
		return;
	}

	WindowHandle = CreateWindowA(_ClassName.data(), _TitleName.data(), WS_OVERLAPPEDWINDOW,
		0, 0, CW_USEDEFAULT, 0, nullptr, nullptr, HInstance, nullptr);

	if (nullptr == WindowHandle)
	{
		MSGASSERT(std::string(_TitleName) + " 윈도우 생성에 실패했습니다.");
		return;
	}

	// 윈도우가 만들어지면 hdc를 여기서 얻어올 겁니다.
	HDC WindowMainDC = GetDC(WindowHandle);
}

void UEngineWindow::Open(std::string_view _TitleName /*= "Window"*/)
{
	// 어 window 안만들고 띄우려고 하네?
	if (0 == WindowHandle)
	{
		// 만들어
		Create(_TitleName);
	}

	if (0 == WindowHandle)
	{
		return;
	}

	// 단순히 윈도창을 보여주는 것만이 아니라
	ShowWindow(WindowHandle, SW_SHOW);
	UpdateWindow(WindowHandle);
	// ShowWindow(WindowHandle, SW_HIDE);
}

void UEngineWindow::SetWindowPosAndScale(FIntPoint _Pos, FIntPoint _Scale)
{
	WindowSize = _Scale;
	RECT Rc = { 0, 0, _Scale.X, _Scale.Y };

	AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);
	::SetWindowPos(WindowHandle, nullptr, _Pos.X, _Pos.Y, Rc.right - Rc.left, Rc.bottom - Rc.top, SWP_NOZORDER);
}

FIntPoint UEngineWindow::GetMousePos()
{
	POINT MouseCoord;

	GetCursorPos(&MouseCoord);
	// 윈도우창 위치기준으로 마우스 포지션을 
	ScreenToClient(WindowHandle, &MouseCoord);

	return FIntPoint(MouseCoord.x, MouseCoord.y);
}