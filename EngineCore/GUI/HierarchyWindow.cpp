#include "EnginePCH.h"
#include "HierarchyWindow.h"
#include <EngineCore/Level.h>
#include <EngineCore/Components/AnimatorComponent.h>
#include <EngineCore/Components/SceneComponent.h>

UHierarchyWindow::UHierarchyWindow(ULevel* _Level)
	:Level(_Level)
{
	SetName("HierarchyPanel");
}


UHierarchyWindow::~UHierarchyWindow()
{
}

void UHierarchyWindow::OnImGuiRender()
{
	ImGui::Begin(GetName().c_str());
	for (auto Actor : Level->AllActorList)
	{
		DrawActor(Actor);
	}

	if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
	{
		SelectedActor = nullptr;
	}
	ImGui::End();

	ImGui::Begin("Components");
	if (nullptr != SelectedActor)
	{
		DrawComponents(SelectedActor);
	}
	ImGui::End();

}

void UHierarchyWindow::DrawActor(std::shared_ptr<AActor>& _Actor)
{
	ImGuiTreeNodeFlags Flags = ImGuiTreeNodeFlags_Leaf;
	//ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;

	Flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
	bool opened = ImGui::TreeNodeEx((void*)_Actor.get(), Flags, _Actor->GetName().c_str());
	if (ImGui::IsItemClicked())
	{
		SelectedActor = _Actor;
	}

	ImGui::TreePop();
}

void UHierarchyWindow::DrawVec3Control(const std::string& _Label, FVector4& _Values, float _ResetValue = 0.0f, float _ColumnWidth = 100.0f)
{
	ImGuiIO& io = ImGui::GetIO();
	auto boldFont = io.Fonts->Fonts[0];

	ImGui::PushID(_Label.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, _ColumnWidth);
	ImGui::Text(_Label.c_str());
	ImGui::NextColumn();

	ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0,0 });

	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	ImVec2 buttonSize = { lineHeight + 2.0f , lineHeight };

	//ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.4f, 0.4f, 0.4f, 1.0f });
	//ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.3f, 0.3f, 1.0f });
	//ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.2f, 0.2f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.1f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.8f, 0.3f, 0.3f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.5f, 0.1f, 0.1f, 1.0f });
	ImGui::PushFont(boldFont);
	if (ImGui::Button("X", buttonSize))
		_Values.X = _ResetValue;
	ImGui::PopFont();
	ImGui::PopStyleColor(3);


	ImGui::SameLine();
	ImGui::DragFloat("##X", &_Values.X, 0.1f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.8f, 0.1f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.9f, 0.2f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.5f, 0.1f, 1.0f });
	ImGui::PushFont(boldFont);
	if (ImGui::Button("Y", buttonSize))
		_Values.Y = _ResetValue;
	ImGui::PopFont();
	ImGui::PopStyleColor(3);


	ImGui::SameLine();
	ImGui::DragFloat("##Y", &_Values.Y, 0.1f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.1f, 0.8f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.2f, 0.9f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.1f, 0.5f, 1.0f });
	ImGui::PushFont(boldFont);
	if (ImGui::Button("Z", buttonSize))
		_Values.Z = _ResetValue;
	ImGui::PopFont();
	ImGui::PopStyleColor(3);


	ImGui::SameLine();
	ImGui::DragFloat("##Z", &_Values.Z, 0.1f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();

	ImGui::PopStyleVar();

	ImGui::Columns(1);

	ImGui::PopID();
}

void UHierarchyWindow::GetAllSceneComponent(std::shared_ptr<USceneComponent> _Parent, std::vector<std::shared_ptr<USceneComponent>>& _Result)
{
	std::list<std::shared_ptr<USceneComponent>> Childs = _Parent->GetChilds();
	for (std::shared_ptr<USceneComponent> Child : Childs)
	{
		_Result.push_back(Child);
	}
}

void UHierarchyWindow::DrawComponents(std::shared_ptr<class AActor>& _Actor)
{
	std::shared_ptr<USceneComponent>& RootComponent = _Actor->RootComponent;
	const ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen
		| ImGuiTreeNodeFlags_Framed
		| ImGuiTreeNodeFlags_SpanAvailWidth
		| ImGuiTreeNodeFlags_AllowItemOverlap;
	std::vector<std::shared_ptr<USceneComponent>> SceneComponentList;
	SceneComponentList.push_back(RootComponent);

	GetAllSceneComponent(RootComponent, SceneComponentList);
	for (auto Component : SceneComponentList)
	{
		if (Component->GetName() == "SceneComponent")
		{
			DrawComponent<USceneComponent>(Component, [=](auto& _Component)
				{
					DrawVec3Control("Translation", _Component->GetTransformRef().Location);
					FVector4 Rotation = FMath::RadianToDegree(_Component->GetTransformRef().Rotation);
					DrawVec3Control("Rotation", Rotation);
					_Component->GetTransformRef().Rotation = FMath::DegreeToRadian(Rotation);
					DrawVec3Control("Scale", _Component->GetTransformRef().Scale, 1.0f);
					_Component->UpdateTransform();
				});
		}

		if (Component->GetName() == "CameraComponent")
		{
			DrawComponent<UCameraComponent>(std::static_pointer_cast<UCameraComponent>(Component), [=](auto& _Component)
				{
					DrawVec3Control("Translation", _Component->GetTransformRef().Location);
					FVector4 Rotation = FMath::RadianToDegree(_Component->GetTransformRef().Rotation);
					DrawVec3Control("Rotation", Rotation);
					_Component->GetTransformRef().Rotation = FMath::DegreeToRadian(Rotation);
					DrawVec3Control("Scale", _Component->GetTransformRef().Scale, 1.0f);
					_Component->UpdateTransform();
					ImGui::RadioButton("IsPerspective", false);
				});
		}
		if (Component->GetName() == "SpriteRendererComponent")
		{
			DrawComponent<UCameraComponent>(std::static_pointer_cast<UCameraComponent>(Component), [=](auto& _Component)
				{
					DrawVec3Control("Translation", _Component->GetTransformRef().Location);
					FVector4 Rotation = FMath::RadianToDegree(_Component->GetTransformRef().Rotation);
					DrawVec3Control("Rotation", Rotation);
					_Component->GetTransformRef().Rotation = FMath::DegreeToRadian(Rotation);
					DrawVec3Control("Scale", _Component->GetTransformRef().Scale, 1.0f);
					_Component->UpdateTransform();
				});
		}
	}

	for (auto Component : _Actor->ActorComponentList)
	{
		if (Component->GetName() == "AnimatorComponent")
		{
			DrawComponent<UAnimatorComponent>(std::static_pointer_cast<UAnimatorComponent>(Component), [=](auto& _Component) 
				{

				});
		}
	}

}

