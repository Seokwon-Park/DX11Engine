#include "EnginePCH.h"
#include "Level.h"
#include "Actor.h"
#include "RendererComponent.h"
#include "EngineCore.h"

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
	UEngineCore::Device->ClearRenderTarget();

	for (std::pair<const int, std::list<std::shared_ptr<URendererComponent>>>& RenderGroup : Renderers)
	{
		std::list<std::shared_ptr<URendererComponent>>& RenderList = RenderGroup.second;

		for (std::shared_ptr<URendererComponent> Renderer : RenderList)
		{
			Renderer->Render(_DeltaTime);
		}
	}
	UEngineCore::Device->SwapBuffers();
}