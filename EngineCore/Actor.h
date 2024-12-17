#pragma once

#include <EngineBase/EngineDebug.h>
#include "Level.h"

// 설명 :
class AActor : public UObject
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

	template<typename ComponentType>
	void CreateDefaultSubObject()
	{
		static_assert(std::is_base_of_v<UActorComponent, ComponentType>,
			"액터 컴포넌트를 상속받지 않은 클래스를 CreateDefaultSubObject하려고 했습니다.");

		if (false == std::is_base_of_v<UActorComponent, ComponentType>)
		{
			MSGASSERT("액터 컴포넌트를 상속받지 않은 클래스를 CreateDefaultSubObject하려고 했습니다.");
			return nullptr;
		}

		ComponentType* ComponentPtr = new ComponentType();
		UActorComponent* Temp = reinterpret_cast<UActorComponent>(ComponentPtr);
		ComponentPtr->Actor = this;

		std::shared_ptr<ComponentType> NewComponent(ComponentPtr);

		if (std::is_base_of_v<USceneComponent, ComponentType>)
		{
			// 기하구조에 편입되어야 한다.
			if (nullptr != RootComponent)
			{
				MSGASSERT("아직 기하구조를 만들지 않았습니다.");
			}

			RootComponent = NewComponent;
		}
		else if (std::is_base_of_v<UActorComponent, ComponentType>)
		{

		}
		else
		{
			MSGASSERT("말도 안됨");
		}

		return NewComponent;
	}


	inline ULevel* GetLevel() const {return Level;}
	ENGINE_API virtual void Tick(float _DeltaTime);

protected:
	ENGINE_API virtual void BeginPlay();
private:
	ULevel* Level;

	std::shared_ptr<class USceneComponent> RootComponent;
	std::list<std::shared_ptr<class UActorComponent>> ActorComponentList;

};

