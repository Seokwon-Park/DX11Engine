#pragma once

// ���� :
class AActor
{
	friend class ULevel;
public:
	// constrcuter destructer
	ENGINE_API AActor();
	ENGINE_API virtual ~AActor();

	// delete Function
	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

<<<<<<< HEAD
=======
	void CreateDefaultSubobject()
	{

	}

	ULevel* GetLevel()
	{
		return Level;
	}
>>>>>>> e303e6160b12585f4d905ed7f018109223275f16
	virtual void Tick(float _DeltaTime) = 0;

	template<typename ComponentType>
	void CreateDefaultSubObject()
	{
		static_assert(std::is_base_of_v<UActorComponent, ComponentType>, "���� ������Ʈ�� ��ӹ��� ���� Ŭ������ CreateDefaultSubObject�Ϸ��� �߽��ϴ�.");

		if (false == std::is_base_of_v<UActorComponent, ComponentType>)
		{
			MSGASSERT("���� ������Ʈ�� ��ӹ��� ���� Ŭ������ CreateDefaultSubObject�Ϸ��� �߽��ϴ�.");
			return nullptr;
			// static_assert
		}

		char* ComMemory = new char[sizeof(ComponentType)];

		UActorComponent* ComPtr = reinterpret_cast<ComponentType*>(ComMemory);
		ComPtr->Actor = this;

		ComponentType* NewPtr = reinterpret_cast<ComponentType*>(ComMemory);
		// �������� �����ϰ�
		// �÷��̽���Ʈ new 
		std::shared_ptr<ComponentType> NewCom(NewPtr = new(ComMemory) ActorType());

		// ���� �׳� ActorComponent
		// ���� �׳� SceneComponent



		if (std::is_base_of_v<USceneComponent, ComponentType>)
		{
			// ���ϱ����� ���ԵǾ�� �Ѵ�.
			if (nullptr != RootComponent)
			{
				MSGASSERT("���� ���ϱ����� ������ �ʾҽ��ϴ�.");
			}

			RootComponent = NewCom;
		}
		else if (std::is_base_of_v<UActorComponent, ComponentType>)
		{

		}
		else
		{
			MSGASSERT("���� �ȵ�");
		}

		return NewActor;
	}
protected:
	virtual void BeginPlay() = 0;
private:
	ULevel* Level;

	std::shared_ptr<class USceneComponent> RootComponent;
	std::list<std::shared_ptr<class UActorComponent>> ActorComponentList;

};
