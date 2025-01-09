#pragma once
#include "EngineImGuiWindow.h"
#include <EngineBase/EngineMath.h>
#include <EngineCore/ThirdParty/IMGUI/imgui.h>
#include <EngineCore/Components/ActorComponent.h>
#include <EngineCore/Components/AnimatorComponent.h>

// Ό³Έν :
class HierarchyWindow : public UEngineImGuiWindow
{
public:
	// constrcuter destructer
	HierarchyWindow(class ULevel* _Level);
	~HierarchyWindow();

	// delete Function
	HierarchyWindow(const HierarchyWindow& _Other) = delete;
	HierarchyWindow(HierarchyWindow&& _Other) noexcept = delete;
	HierarchyWindow& operator=(const HierarchyWindow& _Other) = delete;
	HierarchyWindow& operator=(HierarchyWindow&& _Other) noexcept = delete;

	virtual void OnImGuiRender() override;
	void DrawActor(std::shared_ptr<class AActor>& _Actor);
	void DrawComponents(std::shared_ptr<class AActor>& _Actor);
	template <typename ComponentType, typename UIFunction>
	void DrawComponent(std::shared_ptr<ComponentType> _Component, UIFunction _Function)
	{
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen
			| ImGuiTreeNodeFlags_Framed
			| ImGuiTreeNodeFlags_SpanAvailWidth
			| ImGuiTreeNodeFlags_AllowItemOverlap;

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
			ImGui::Separator();
			bool open = ImGui::TreeNodeEx((void*)_Component.get(), treeNodeFlags, _Component->GetName().c_str());
			ImGui::PopStyleVar();

			if (open)
			{
				_Function(_Component);
				ImGui::TreePop();
			}
	}

	void DrawVec3Control(const std::string& _Label, FVector4& _Values, float _ResetValue, float _ColumnWidth);

	void GetAllSceneComponent(std::shared_ptr<class USceneComponent> _Parent, std::vector<std::shared_ptr<class USceneComponent>>& _Result);
protected:

private:
	std::shared_ptr<class AActor> SelectedActor = nullptr;
	class ULevel* Level = nullptr;
};

