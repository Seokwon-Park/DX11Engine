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
	// constrcuter destructer
	ENGINE_API UEngineWindow();
	ENGINE_API ~UEngineWindow();

	// delete Function
	UEngineWindow(const UEngineWindow& _Other) = delete;
	UEngineWindow(UEngineWindow&& _Other) noexcept = delete;
	UEngineWindow& operator=(const UEngineWindow& _Other) = delete;
	UEngineWindow& operator=(UEngineWindow&& _Other) noexcept = delete;

	ENGINE_API static void EngineWindowInit(HINSTANCE _Instance);
	ENGINE_API static void CreateWindowClass(const WNDCLASSEXA& _Class);
	ENGINE_API static int WindowMessageLoop(std::function<void()> _StartFunction, std::function<void()> _FrameFunction, std::function<void()> _EndFunction = nullptr);

	ENGINE_API void Create(std::string_view _TitleName, std::string_view _ClassName = "Default");
	ENGINE_API void Open(std::string_view _TitleName = "Window");

	inline FIntPoint GetWindowSize() const
	{
		return WindowSize;
	}

	inline void SetWindowTitle(std::string_view Text)
	{
		SetWindowTextA(WindowHandle, Text.data());
	}

	ENGINE_API void SetWindowPosAndScale(FIntPoint _Pos, FIntPoint _Scale);
	ENGINE_API FIntPoint GetMousePos();

	void ApplicationOff()
	{
		LoopActive = false;
	}

protected:

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static HINSTANCE HInstance;
	static bool LoopActive;
	static std::map<std::string, WNDCLASSEXA> WindowClasses;

	FIntPoint WindowSize;
	HWND WindowHandle = nullptr;
};


