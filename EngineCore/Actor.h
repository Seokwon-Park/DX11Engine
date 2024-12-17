#pragma once

// 설명 :
class AActor
{
public:
	// constrcuter destructer
	AActor();
	~AActor();

	// delete Function
	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) = 0;

	template<typename ComponentType>
	void CreateDefaultSubObject()
	{
		static_assert(std::is_base_of_v<UActorComponent, ComponentType>, "액터 컴포넌트를 상속받지 않은 클래스를 CreateDefaultSubObject하려고 했습니다.");

		if (false == std::is_base_of_v<UActorComponent, ComponentType>)
		{
			MSGASSERT("액터 컴포넌트를 상속받지 않은 클래스를 CreateDefaultSubObject하려고 했습니다.");
			return nullptr;
			// static_assert
		}

		char* ComMemory = new char[sizeof(ComponentType)];

		UActorComponent* ComPtr = reinterpret_cast<ComponentType*>(ComMemory);
		ComPtr->Actor = this;

		ComponentType* NewPtr = reinterpret_cast<ComponentType*>(ComMemory);
		// 레벨먼저 세팅하고
		// 플레이스먼트 new 
		std::shared_ptr<ComponentType> NewCom(NewPtr = new(ComMemory) ActorType());

		// 내가 그냥 ActorComponent
		// 내가 그냥 SceneComponent



		if (std::is_base_of_v<USceneComponent, ComponentType>)
		{
			// 기하구조에 편입되어야 한다.
			if (nullptr != RootComponent)
			{
				MSGASSERT("아직 기하구조를 만들지 않았습니다.");
			}

			RootComponent = NewCom;
		}
		else if (std::is_base_of_v<UActorComponent, ComponentType>)
		{

		}
		else
		{
			MSGASSERT("말도 안됨");
		}

		return NewActor;
	}
protected:
	virtual void BeginPlay() = 0;
private:
	std::shared_ptr<class USceneComponent> RootComponent;
	std::list<std::shared_ptr<class UActorComponent>> ActorComponentList;

};

