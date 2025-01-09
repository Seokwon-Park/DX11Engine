#pragma once
#include "EngineImGuiWindow.h"

// Ό³Έν :
class ImGuiLayer
{
public:
	// constrcuter destructer
	ImGuiLayer();
	~ImGuiLayer();

	// delete Function
	ImGuiLayer(const ImGuiLayer& _Other) = delete;
	ImGuiLayer(ImGuiLayer&& _Other) noexcept = delete;
	ImGuiLayer& operator=(const ImGuiLayer& _Other) = delete;
	ImGuiLayer& operator=(ImGuiLayer&& _Other) noexcept = delete;

	static void Init();
	static void SetDarkThemeColors();
	void OnImGuiRender();
	void RenderStart();
	void RenderEnd();
	static void Shutdown();



	inline void AttachWindow(std::shared_ptr<UEngineImGuiWindow> _Window)
	{
		Windows.push_back(_Window);
	}
protected:

private:
	std::list<std::shared_ptr<UEngineImGuiWindow>> Windows;
};

