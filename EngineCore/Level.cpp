#include "EnginePCH.h"
#include "Level.h"
#include "Components/SpriteRendererComponent.h"
#include "EngineCore.h"
#include "EngineDeviceContext.h"
#include "GUI/ImGuiLayer.h"
#include <EngineCore/Components/CameraComponent.h>

ULevel::ULevel()
{
	CurrentCamera = SpawnCamera("MainCamera")->GetCameraComponent().get();
	CurrentCamera->SetLocation({ 0.0f, 0.0f, -500.0f, 1.0f });

	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = b2Vec2(0.0f, -100.0f);
	WorldId = b2CreateWorld(&worldDef);
}

ULevel::~ULevel()
{
	b2DestroyWorld(WorldId);
}

void ULevel::Tick(float _DeltaTime)
{
	
	std::list<std::shared_ptr<class AActor>>::iterator Iterator = BeginPlayList.begin();
	while(Iterator != BeginPlayList.end())
	{
		std::shared_ptr<AActor> CurActor = *Iterator;

		/*if (false == CurActor->IsActive())
		{
			++StartIter;
			continue;
		}*/

		Iterator = BeginPlayList.erase(Iterator);

		CurActor->BeginPlay();
		AllActorList.push_back(CurActor);
	}

	for (std::shared_ptr<AActor> CurActor : AllActorList)
	{
		CurActor->Tick(_DeltaTime);
	}
}

void ULevel::Render(float _DeltaTime)
{
	UEngineCore::GetGraphicsDeviceContext()->ClearRenderTarget();

	for (std::pair<const std::pair<int,int>, std::list<std::shared_ptr<USpriteRendererComponent>>>& RenderGroup : SpriteRenderers)
	{
		std::list<std::shared_ptr<USpriteRendererComponent>>& RenderList = RenderGroup.second;

		for (std::shared_ptr<URendererComponent> Renderer : RenderList)
		{
			Renderer->Render(CurrentCamera, _DeltaTime);
		}
	}

	ImGuiLayer::OnImGuiRender();
	UEngineCore::GetGraphicsDeviceContext()->SwapBuffers();
}

void ULevel::PushRenderer(std::shared_ptr<class USpriteRendererComponent> _Renderer)
{
	SpriteRenderers[_Renderer->GetOrder()].push_back(_Renderer);
}

void ULevel::ChangeRenderOrder(std::pair<int,int> _PrevRenderOrder, std::shared_ptr<USpriteRendererComponent> _Renderer)
{
	SpriteRenderers[_PrevRenderOrder].remove(_Renderer);
	SpriteRenderers[_Renderer->GetOrder()].push_back(_Renderer);
}

std::shared_ptr<ACameraActor> ULevel::SpawnCamera(std::string_view _Name)
{
	std::shared_ptr<ACameraActor> CameraActor = SpawnActor<ACameraActor>();
	CameraComponents.insert(std::make_pair(_Name, CameraActor->GetCameraComponent()));

	return CameraActor;
}
