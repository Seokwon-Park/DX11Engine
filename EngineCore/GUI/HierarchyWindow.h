#pragma once
#include "EngineImGuiWindow.h"

// ���� :
class HierarchyWindow : public UEngineImGuiWindow
{
public:
	// constrcuter destructer
	HierarchyWindow();
	~HierarchyWindow();

	// delete Function
	HierarchyWindow(const HierarchyWindow& _Other) = delete;
	HierarchyWindow(HierarchyWindow&& _Other) noexcept = delete;
	HierarchyWindow& operator=(const HierarchyWindow& _Other) = delete;
	HierarchyWindow& operator=(HierarchyWindow&& _Other) noexcept = delete;

	virtual void Update() override;
	//void Init(ULevel* _Level);
protected:

private:

};

