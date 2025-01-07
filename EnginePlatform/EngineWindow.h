#pragma once
// Os Header
#include <Windows.h>

// std Header
#include <map>
#include <string>
#include <functional>

// user header
#include <EngineBase/EngineMath.h>

// Ό³Έν :
class UEngineWindow
{
public:
	using UserWndProc = std::function<bool(HWND, UINT, WPARAM, LPARAM)>;
	// constrcuter destructer
	PLATFORM_API UEngineWindow();
	PLATFORM_API ~UEngineWindow();

	// delete Function
	UEngineWindow(const UEngineWindow& _Other) = delete;
	UEngineWindow(UEngineWindow&& _Other) noexcept = delete;
	UEngineWindow& operator=(const UEngineWindow& _Other) = delete;
	UEngineWindow& operator=(UEngineWindow&& _Other) noexcept = delete;

	PLATFORM_API static void EngineWindowInit(HINSTANCE _Instance);
	PLATFORM_API static void CreateWindowClass(const WNDCLASSEXA& _Class);
	PLATFORM_API static int WindowMessageLoop(std::function<void()> _StartFunction, std::function<void()> _FrameFunction, std::function<void()> _EndFunction = nullptr);

	PLATFORM_API void Open(std::string_view _TitleName = "Window");
	PLATFORM_API void Create(std::string_view _TitleName, std::string_view _ClassName = "Default");
	PLATFORM_API void SetWindowPosAndScale(FIntPoint _Pos, FIntPoint _Scale);
	PLATFORM_API FIntPoint GetMousePos();

	PLATFORM_API inline HWND GetHandle()const { return WindowHandle; }
	PLATFORM_API inline FIntPoint GetWindowSize() const { return WindowSize; }
	inline void SetWindowTitle(std::string_view Text) { SetWindowTextA(WindowHandle, Text.data()); }

	inline void ApplicationOff()
	{
		LoopActive = false;
	}

	inline void SetUserWndProc(UserWndProc _Proc) { UserProc = _Proc; }

protected:

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static HINSTANCE HInstance;
	static bool LoopActive;
	static std::map<std::string, WNDCLASSEXA> WindowClasses;

	FIntPoint WindowSize;
	HWND WindowHandle = nullptr;
	std::function<bool(HWND, UINT, WPARAM, LPARAM)> UserProc;
};


