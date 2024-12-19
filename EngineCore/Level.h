#pragma once

#include "EngineBase/Object.h"
#include "Actor.h"

// ���� :
class  ULevel : public UObject
{
public:
	// constrcuter destructer
	ENGINE_API ULevel();
	ENGINE_API ~ULevel();

	// delete Function
	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	//void LevelChangeStart();
	//// ���� ��ü ��������
	//void LevelChangeEnd();

	void Tick(float _DeltaTime);
	void Render(float _DeltaTime);

	void PushRenderer(std::shared_ptr<class URendererComponent> _Renderer);

	template<typename ActorType>
	std::shared_ptr<ActorType> SpawnActor()
	{
		static_assert(std::is_base_of_v<AActor, ActorType>, "���͸� ��ӹ��� ���� Ŭ������ SpawnActor�Ϸ��� �߽��ϴ�.");

		if (false == std::is_base_of_v<AActor, ActorType>)
		{
			MSGASSERT("���͸� ��ӹ��� ���� Ŭ������ SpawnActor�Ϸ��� �߽��ϴ�.");
			return nullptr;
		}

		ActorType* ActorMemory = new ActorType();
		AActor* ActorPtr = reinterpret_cast<ActorType*>(ActorMemory);
		ActorPtr->Level = this;
		std::shared_ptr<ActorType> NewActor(ActorMemory);

		BeginPlayList.push_back(NewActor);

		return NewActor;
	}
protected:

private:
	std::list<std::shared_ptr<class AActor>> BeginPlayList;
	std::list<std::shared_ptr<class AActor>> AllActorList;

	std::map<int, std::list<std::shared_ptr<class URendererComponent>>> Renderers;

};

