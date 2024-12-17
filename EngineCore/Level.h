#pragma once

#include "EngineBase/Object.h"

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

<<<<<<< HEAD
	//void LevelChangeStart();
	//// ���� ��ü ��������
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

		static_assert(std::is_base_of_v<AActor, ActorType>, "���͸� ��ӹ��� ���� Ŭ������ SpawnActor�Ϸ��� �߽��ϴ�.");

		if (false == std::is_base_of_v<AActor, ActorType>)
		{
			MSGASSERT("���͸� ��ӹ��� ���� Ŭ������ SpawnActor�Ϸ��� �߽��ϴ�.");
			return nullptr;
			// static_assert
		}

		char* ActorMemory = new char[sizeof(ActorType)];


		AActor* ActorPtr = reinterpret_cast<ActorType*>(ActorMemory);
		ActorPtr->World = this;

		ActorType* NewPtr = reinterpret_cast<ActorType*>(ActorMemory);
		// �������� �����ϰ�
		// �÷��̽���Ʈ new 
		std::shared_ptr<ActorType> NewActor(NewPtr = new(ActorMemory) ActorType());


		//�����Ϸ��� �װ� �𸥴�.
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

