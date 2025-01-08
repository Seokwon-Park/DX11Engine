#pragma once

// Ό³Έν :
class UEngineImGuiWindow : public UObject
{
public:
	// constrcuter destructer
	UEngineImGuiWindow();
	~UEngineImGuiWindow();

	// delete Function
	UEngineImGuiWindow(const UEngineImGuiWindow& _Other) = delete;
	UEngineImGuiWindow(UEngineImGuiWindow&& _Other) noexcept = delete;
	UEngineImGuiWindow& operator=(const UEngineImGuiWindow& _Other) = delete;
	UEngineImGuiWindow& operator=(UEngineImGuiWindow&& _Other) noexcept = delete;

	virtual void Update() = 0;
protected:

private:

};

