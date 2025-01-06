#include "EnginePCH.h"
#include "RenderUnit.h"
#include "EngineCore.h"
#include "EngineDeviceContext.h"
#include <EngineCore/Components/CameraComponent.h>
#include "ResourceManager.h"

URenderUnit::URenderUnit()
{
}

URenderUnit::~URenderUnit()
{
}

void URenderUnit::Render(UCameraComponent* _Camera, float _DeltaTime)
{
	if (Mesh == nullptr)
	{
		MSGASSERT("메쉬가 설정되지 않았습니다.")
	}
	if (Material == nullptr)
	{
		MSGASSERT("머테리얼이 설정되지 않았습니다.")
	}
	Mesh->Bind();
	Material->Bind();

	UEngineCore::GetGraphicsDeviceContext()->GetContext()->DrawIndexed(Mesh->GetIndexCount(), 0, 0);
}

void URenderUnit::SetMesh(std::string_view _Name)
{
	SetMesh(UResourceManager::Find<UEngineMesh>(_Name));
}

void URenderUnit::SetMaterial(std::string_view _Name)
{
	SetMaterial(UResourceManager::Find<UEngineMaterial>(_Name));
}

