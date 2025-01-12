#include "EnginePCH.h"
#include "Level.h"
#include "Components/Collider2DComponent.h"
#include "Components/SpriteRendererComponent.h"
#include "Components/TilemapRendererComponent.h"
#include "EngineCore.h"
#include "EngineDeviceContext.h"
#include "GUI/ImGuiLayer.h"
#include "GUI/HierarchyWindow.h"
#include "GUI/DevTestWindow.h"
#include <EngineCore/Components/CameraComponent.h>

ULevel::ULevel()
{
	CurrentCamera = SpawnCamera("MainCamera").get();
	CurrentCamera->SetActorLocation({ 0.0f, 0.0f, -500.0f, 1.0f });

	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = b2Vec2(0.0f, -9.8f); 
	WorldId = b2CreateWorld(&worldDef);

	GuiLayer = std::make_shared<ImGuiLayer>();
	GuiLayer->AttachWindow(std::make_shared<UHierarchyWindow>(this));
	GuiLayer->AttachWindow(std::make_shared<UDevTestWindow>());
}

ULevel::~ULevel()
{
	b2DestroyWorld(WorldId);
}

void ULevel::Tick(float _DeltaTime)
{
	b2World_Step(WorldId, 1.0f / 60.0f, 4);
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

	for (std::pair<const std::pair<int,int>, std::list<std::shared_ptr<URendererComponent>>>& RenderGroup : SpriteRenderers)
	{
		std::list<std::shared_ptr<URendererComponent>>& RenderList = RenderGroup.second;

		for (std::shared_ptr<URendererComponent> Renderer : RenderList)
		{
			Renderer->Render(CurrentCamera->GetCameraComponent().get(), _DeltaTime);
		}
	}

	for (auto Collider2D : Colliders2D)
	{
		Collider2D->DebugRender(CurrentCamera->GetCameraComponent().get(), _DeltaTime);
	}
	GuiLayer->OnImGuiRender();
	UEngineCore::GetGraphicsDeviceContext()->SwapBuffers();
}

void ULevel::PushCollider2D(std::shared_ptr<class UCollider2DComponent> _Renderer)
{
	Colliders2D.push_back(_Renderer);
}

void ULevel::PushRenderer(std::shared_ptr<class USpriteRendererComponent> _Renderer)
{
	SpriteRenderers[_Renderer->GetOrder()].push_back(_Renderer);
}

void ULevel::PushTilemapRenderer(std::shared_ptr< UTilemapRendererComponent> _Renderer)
{
	std::pair<int, int> Tempkey = { 0,0 };
	SpriteRenderers[Tempkey].push_back(_Renderer);
}

void ULevel::ChangeRenderOrder(std::pair<int,int> _PrevRenderOrder, std::shared_ptr<USpriteRendererComponent> _Renderer)
{
	SpriteRenderers[_PrevRenderOrder].remove(_Renderer);
	SpriteRenderers[_Renderer->GetOrder()].push_back(_Renderer);
}

std::shared_ptr<ACameraActor> ULevel::SpawnCamera(std::string_view _Name)
{
	std::shared_ptr<ACameraActor> CameraActor = SpawnActor<ACameraActor>(_Name);
	CameraComponents.insert(std::make_pair(_Name, CameraActor));

	return CameraActor;
}

void ULevel::AddGuiWindow(std::shared_ptr<class UEngineImGuiWindow> _Window)
{
	GuiLayer->AttachWindow(_Window);
}
