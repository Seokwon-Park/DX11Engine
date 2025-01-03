#include "EnginePCH.h"
#include "Level.h"
#include "Components/SpriteRendererComponent.h"
#include "EngineCore.h"
#include "EngineDeviceContext.h"

ULevel::ULevel()
{
}

ULevel::~ULevel()
{
}

void ULevel::Tick(float _DeltaTime)
{
	std::list<std::shared_ptr<class AActor>>::iterator StartIter = BeginPlayList.begin();
	std::list<std::shared_ptr<class AActor>>::iterator EndIter = BeginPlayList.end();
	for (; StartIter != EndIter; )
	{
		std::shared_ptr<AActor> CurActor = *StartIter;

		/*if (false == CurActor->IsActive())
		{
			++StartIter;
			continue;
		}*/

		StartIter = BeginPlayList.erase(StartIter);

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
	UEngineCore::GraphicsDeviceContext->ClearRenderTarget();

	for (std::pair<const std::pair<int,int>, std::list<std::shared_ptr<USpriteRendererComponent>>>& RenderGroup : SpriteRenderers)
	{
		std::list<std::shared_ptr<USpriteRendererComponent>>& RenderList = RenderGroup.second;

		for (std::shared_ptr<URendererComponent> Renderer : RenderList)
		{
			Renderer->Render(_DeltaTime);
		}
	}
	UEngineCore::GraphicsDeviceContext->SwapBuffers();
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
