#include "EnginePCH.h"
#include "ImGuiLayer.h"
#include "EngineCore.h"
#include "EngineDeviceContext.h"
#include "HierarchyWindow.h"
#include <EngineCore/ThirdParty/IMGUI/imgui.h>
#include <EngineCore/ThirdParty/IMGUI/imgui_impl_dx11.h>
#include <EngineCore/ThirdParty/IMGUI/imgui_impl_win32.h>
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

std::list<std::shared_ptr<UEngineImGuiWindow>> ImGuiLayer::Windows;

ImGuiLayer::ImGuiLayer()
{
}

ImGuiLayer::~ImGuiLayer()
{
}

void ImGuiLayer::Init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	float fontSize = 18.0f;
	/*io.Fonts->AddFontFromFileTTF("assets/fonts/Naver/NanumBarun/NanumBarunGothicBold.ttf", fontSize);
	io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/Naver/NanumBarun/NanumBarunGothic.ttf", fontSize);*/


	ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	//SetDarkThemeColors();

	auto Device = UEngineCore::GetGraphicsDeviceContext()->GetDevice();
	auto Context = UEngineCore::GetGraphicsDeviceContext()->GetContext();
	ImGui_ImplWin32_Init(UEngineCore::GetMainWindow().GetHandle());
	ImGui_ImplDX11_Init(Device, Context);
	//Device->Release();
	//Context->Release();
	std::function<bool(HWND, UINT, WPARAM, LPARAM)> WndProc = ImGui_ImplWin32_WndProcHandler;
	UEngineCore::GetMainWindow().SetUserWndProc(WndProc);


	//std::shared_ptr<UEngineImGuiWindow> Hierarchy = std::make_shared<HierarchyWindow>();
	Windows.push_back(std::make_shared<HierarchyWindow>());
}

void ImGuiLayer::OnImGuiRender()
{
	if (false == UEngineCore::GetMainWindow().GetIsLoopActive())
	{
		return;
	}
	RenderStart();
	//ImGui::ShowDemoWindow(); // Show demo window! :)
	for (std::shared_ptr<UEngineImGuiWindow> Window : Windows)
	{
		ImGui::Begin(Window->GetName().c_str());
		Window->Update();
		ImGui::End();
	}
	RenderEnd();
}

void ImGuiLayer::RenderStart()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGuiLayer::RenderEnd()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}

void ImGuiLayer::Shutdown()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
