#pragma once

// ���� :
class ENGINE_API ULevel
{
public:
	// constrcuter destructer
	ULevel();
	~ULevel();

	// delete Function
	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	//void LevelChangeStart();
	//// ���� ��ü ��������
	//void LevelChangeEnd();


	void Tick(float _DeltaTime);

	template<typename ActorType>
	std::shared_ptr<ActorType> SpawnActor()
	{
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
		BeginPlayList.push_back(NewActor);

		return NewActor;
	}
protected:

private:
	std::list<std::shared_ptr<class AActor>> BeginPlayList;
	std::list<std::shared_ptr<class AActor>> AllActorList;

};

