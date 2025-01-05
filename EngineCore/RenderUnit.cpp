#include "EnginePCH.h"
#include "RenderUnit.h"
#include "EngineCore.h"
#include "EngineDeviceContext.h"
#include <EngineCore/Components/CameraComponent.h>
#include <EngineCore/Resources/EngineMesh.h>
#include <EngineCore/Resources/EngineMaterial.h>

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
		MSGASSERT("�޽��� �������� �ʾҽ��ϴ�.")
	}
	if (Material == nullptr)
	{
		MSGASSERT("���׸����� �������� �ʾҽ��ϴ�.")
	}
	Mesh->Bind();
	Material->Bind();

	UEngineCore::GetGraphicsDeviceContext()->GetContext()->DrawIndexed(Mesh->GetIndexCount(), 0, 0);
}

