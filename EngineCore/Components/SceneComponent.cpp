#include "EnginePCH.h"
#include "SceneComponent.h"

USceneComponent::USceneComponent()
{
}

USceneComponent::~USceneComponent()
{
}


void USceneComponent::GetParentTransform()
{
	if (nullptr != Parent)
	{
		Transform = Parent->Transform;
	}
}

ENGINE_API void USceneComponent::SetupAttachment(std::shared_ptr<USceneComponent> _Parent)
{
	SetupAttachment(_Parent.get());
}

void USceneComponent::SetupAttachment(USceneComponent* _Parent)
{
	Parent = _Parent;
	Parent->Childs.push_back(GetThis<USceneComponent>());

	UpdateTransform();
}

ENGINE_API void USceneComponent::UpdateTransform()
{
	GetParentTransform();
	// ���� Ʈ������ ������Ʈ�� �ϴ� �Ѵ�.
	Transform.UpdateTransform();//(IsAbsolute);

	for (std::shared_ptr<USceneComponent> Child : Childs)
	{
		Child->UpdateTransform();
	}

	//IsAbsolute = false;
}
