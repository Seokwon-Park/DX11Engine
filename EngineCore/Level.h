#pragma once

#include "Actor.h"
#include "GameMode.h"
#include "CameraActor.h"
#include <EngineCore/ThirdParty/Box2D/include/box2d.h>

// 설명 :
class  ULevel : public UObject
{
public:
	friend class UHierarchyWindow;
	// constrcuter destructer
	ENGINE_API ULevel();
	ENGINE_API ~ULevel();

	// delete Function
	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	//void LevelChangeStart();
	//// 내가 교체 당했을때
	//void LevelChangeEnd();

	void Tick(float _DeltaTime);
	void Render(float _DeltaTime);
	
	void PushCollider2D(std::shared_ptr<class UCollider2DComponent> _Renderer);

	void PushRenderer(std::shared_ptr<class URenderer2DComponent> _Renderer);
	void PushRenderer2D(std::shared_ptr<class URendererComponent> _Renderer);
	void ChangeRenderOrder(std::pair<int, int> _PrevRenderOrder, std::shared_ptr<class URenderer2DComponent> _Renderer);



	std::shared_ptr<class ACameraActor> SpawnCamera(std::string_view _Name);

	template<typename ActorType>
	std::shared_ptr<ActorType> SpawnActor(std::string_view _Name = "")
	{
		static_assert(std::is_base_of_v<AActor, ActorType>, "액터를 상속받지 않은 클래스를 SpawnActor하려고 했습니다.");

		if (false == std::is_base_of_v<AActor, ActorType>)
		{
			MSGASSERT("액터를 상속받지 않은 클래스를 SpawnActor하려고 했습니다.");
			return nullptr;
		}

		ActorType* ActorMemory = new ActorType();
		AActor* ActorPtr = reinterpret_cast<ActorType*>(ActorMemory);
		ActorPtr->Level = this;
		ActorPtr->SetName(_Name);
		std::shared_ptr<ActorType> NewActor(ActorMemory);

		BeginPlayList.push_back(NewActor);

		return NewActor;
	}
	template<typename GameModeType>
	std::shared_ptr<GameModeType> GetGameMode()
	{
		return dynamic_pointer_cast<GameModeType>(GameMode);
	}

	template<typename ActorType>
	std::shared_ptr<ActorType> GetMainPawn()
	{
		return dynamic_pointer_cast<ActorType>(MainPawn);
	}

	class ACameraActor* GetCurrentCamera()
	{
		return CurrentCamera;
	}


	template <typename GameModeType, typename MainPawnType>
	void Create()
	{
		GameMode = SpawnActor<GameModeType>("GameMode");
		MainPawn = SpawnActor<MainPawnType>("MainPawn");
	}

	inline b2WorldId GetPhysicsWorld() const { return WorldId; }
	ENGINE_API void AddGuiWindow(std::shared_ptr<class UEngineImGuiWindow> _Window);

protected:

private:
	b2WorldId WorldId;
	std::shared_ptr<class ImGuiLayer> GuiLayer;

	std::shared_ptr<AGameMode> GameMode;
	std::shared_ptr<AActor> MainPawn;

	std::list<std::shared_ptr<class AActor>> BeginPlayList;
	std::list<std::shared_ptr<class AActor>> AllActorList;

	std::map<std::pair<int,int>, std::list<std::shared_ptr<class URenderer2DComponent>>> SpriteRenderers;
	std::list<std::shared_ptr<class UCollider2DComponent>> Colliders2D;
	std::map<std::string,std::shared_ptr<class ACameraActor>> CameraComponents;
	class ACameraActor* CurrentCamera;
};

