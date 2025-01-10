#include "EnginePCH.h"
#include "EngineWindow.h"
#include <EngineBase/EngineDebug.h>

HINSTANCE UEngineWindow::HInstance = nullptr;
std::map<std::string, WNDCLASSEXA> UEngineWindow::WindowClasses;
int WindowCount = 0;
bool UEngineWindow::IsLoopActive = true;
UEngineWindow::UserWndProc UEngineWindow::UserProc;

LRESULT CALLBACK UEngineWindow::WndProc(HWND _HWnd, UINT _Message, WPARAM _WParam, LPARAM _LParam)
{
	if (nullptr != UserProc)
	{
		if (UserProc(_HWnd, _Message, _WParam, _LParam))
			return true;
	}

	switch (_Message)
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
			IsLoopActive = false;
		}
		break;
	default:
		return DefWindowProc(_HWnd, _Message, _WParam, _LParam);
	}
	return 0;
}


void UEngineWindow::EngineWindowInit(HINSTANCE _HInstance)
{
	HInstance = _HInstance;

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

int UEngineWindow::WindowMessageLoop(std::function<void()> _InitFn, std::function<void()> _UpdateFn, std::function<void()> _ShutdownFn)
{
	MSG Message = MSG();
	if (nullptr != _InitFn)
	{
		_InitFn();
	}

	if (nullptr == _UpdateFn)
	{
		MSGASSERT("업데이트 펑션이 바인드 되어 있지 않습니다.");
		return 0;
	}

	while (true == IsLoopActive)
	{
		if (0 != PeekMessage(&Message, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		_UpdateFn();
	}

	if (nullptr != _ShutdownFn)
	{
		_ShutdownFn();
	}

	return (int)Message.wParam;
}

void UEngineWindow::CreateWindowClass(const WNDCLASSEXA& _WNDClass)
{
	if (WindowClasses.contains(std::string(_WNDClass.lpszClassName)))
	{
		MSGASSERT(std::string(_WNDClass.lpszClassName) + " 같은 이름의 윈도우 클래스를 2번 등록했습니다");
		return;
	}

	RegisterClassExA(&_WNDClass);

	WindowClasses.insert(std::pair{ _WNDClass.lpszClassName, _WNDClass });
}

UEngineWindow::UEngineWindow()
{

}

UEngineWindow::~UEngineWindow()
{
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

	HDC WindowMainDC = GetDC(WindowHandle);
}

void UEngineWindow::Open(std::string_view _TitleName /*= "Window"*/)
{
	if (0 == WindowHandle)
	{
		Create(_TitleName);
	}

	if (0 == WindowHandle)
	{
		return;
	}

	ShowWindow(WindowHandle, SW_SHOW);
	UpdateWindow(WindowHandle);
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
	ScreenToClient(WindowHandle, &MouseCoord);

	return FIntPoint(MouseCoord.x, MouseCoord.y);
}