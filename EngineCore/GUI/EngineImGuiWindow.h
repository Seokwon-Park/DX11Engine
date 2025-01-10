#pragma once

#include <EngineCore/ThirdParty/IMGUI/imgui.h>
#include <EngineCore/ThirdParty/IMGUI/imgui_internal.h>

// Ό³Έν :
class UEngineImGuiWindow : public UObject
{
public:
	// constrcuter destructer
	ENGINE_API UEngineImGuiWindow();
	ENGINE_API ~UEngineImGuiWindow();

	// delete Function
	UEngineImGuiWindow(const UEngineImGuiWindow& _Other) = delete;
	UEngineImGuiWindow(UEngineImGuiWindow&& _Other) noexcept = delete;
	UEngineImGuiWindow& operator=(const UEngineImGuiWindow& _Other) = delete;
	UEngineImGuiWindow& operator=(UEngineImGuiWindow&& _Other) noexcept = delete;

	virtual void OnImGuiRender() = 0;
protected:

private:

};

