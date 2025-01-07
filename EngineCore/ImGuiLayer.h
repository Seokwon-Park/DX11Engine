#pragma once

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
	static void RenderStart();
	static void RenderEnd();
	static void Shutdown();
protected:

private:

};

