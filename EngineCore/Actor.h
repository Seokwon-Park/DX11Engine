#pragma once

#include <EngineBase/EngineDebug.h>
#include "Level.h"

// ���� :
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
	inline std::shared_ptr<ComponentType> CreateDefaultSubObject()
	{
		static_assert(std::is_base_of_v<UActorComponent, ComponentType>,
			"���� ������Ʈ�� ��ӹ��� ���� Ŭ������ CreateDefaultSubObject�Ϸ��� �߽��ϴ�.");

		if (false == std::is_base_of_v<UActorComponent, ComponentType>)
		{
			MSGASSERT("���� ������Ʈ�� ��ӹ��� ���� Ŭ������ CreateDefaultSubObject�Ϸ��� �߽��ϴ�.");
			return nullptr;
		}

		ComponentType* ComponentPtr = new ComponentType();
		UActorComponent* Temp = reinterpret_cast<UActorComponent*>(ComponentPtr);
		Temp->Owner = this;

		std::shared_ptr<ComponentType> NewComponent(ComponentPtr);

		if (std::is_base_of_v<USceneComponent, ComponentType>)
		{
			if (nullptr != RootComponent)
			{
				MSGASSERT("���� ���ϱ����� ������ �ʾҽ��ϴ�.");
			}

			RootComponent = NewComponent;
		}
		else if (std::is_base_of_v<UActorComponent, ComponentType>)
		{
			ActorComponentList.push_back(NewComponent);
		}
		else
		{
			MSGASSERT("���� �ȵ�");
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

