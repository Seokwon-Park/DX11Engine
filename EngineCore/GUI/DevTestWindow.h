#pragma once
#include <EngineCore/GUI/EngineImGuiWindow.h>

// Ό³Έν :
class UDevTestWindow : public UEngineImGuiWindow
{
public:
	// constrcuter destructer
	UDevTestWindow();
	~UDevTestWindow();

	// delete Function
	UDevTestWindow(const UDevTestWindow& _Other) = delete;
	UDevTestWindow(UDevTestWindow&& _Other) noexcept = delete;
	UDevTestWindow& operator=(const UDevTestWindow& _Other) = delete;
	UDevTestWindow& operator=(UDevTestWindow&& _Other) noexcept = delete;

	virtual void OnImGuiRender() override;

protected:

private:

};

