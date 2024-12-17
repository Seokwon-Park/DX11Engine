#pragma once

#include "EngineBase/Object.h"

// 설명 :
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

<<<<<<< HEAD
	//void LevelChangeStart();
	//// 내가 교체 당했을때
	//void LevelChangeEnd();


=======
>>>>>>> e303e6160b12585f4d905ed7f018109223275f16
	void Tick(float _DeltaTime);

	template<typename ActorType>
	std::shared_ptr<ActorType> SpawnActor()
	{
<<<<<<< HEAD
		// AMonster : public AActor
		// SpawnActor<AMonster>();
		// std::shared_ptr<AMonster>

		static_assert(std::is_base_of_v<AActor, ActorType>, "액터를 상속받지 않은 클래스를 SpawnActor하려고 했습니다.");

		if (false == std::is_base_of_v<AActor, ActorType>)
		{
			MSGASSERT("액터를 상속받지 않은 클래스를 SpawnActor하려고 했습니다.");
			return nullptr;
			// static_assert
		}

		char* ActorMemory = new char[sizeof(ActorType)];


		AActor* ActorPtr = reinterpret_cast<ActorType*>(ActorMemory);
		ActorPtr->World = this;

		ActorType* NewPtr = reinterpret_cast<ActorType*>(ActorMemory);
		// 레벨먼저 세팅하고
		// 플레이스먼트 new 
		std::shared_ptr<ActorType> NewActor(NewPtr = new(ActorMemory) ActorType());


		//컴파일러는 그걸 모른다.
=======
		std::shared_ptr<ActorType> NewActor = std::make_shared<ActorType>();

>>>>>>> e303e6160b12585f4d905ed7f018109223275f16
		BeginPlayList.push_back(NewActor);

		return NewActor;
	}
protected:

private:
	std::list<std::shared_ptr<class AActor>> BeginPlayList;
<<<<<<< HEAD
=======

>>>>>>> e303e6160b12585f4d905ed7f018109223275f16
	std::list<std::shared_ptr<class AActor>> AllActorList;

};

