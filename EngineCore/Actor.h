#pragma once

#include <EngineBase/Object.h>
#include <EngineBase/EngineDebug.h>

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
	inline std::shared_ptr<ComponentType> CreateDefaultSubObject()
	{
		static_assert(std::is_base_of_v<UActorComponent, ComponentType>,
			"액터 컴포넌트를 상속받지 않은 클래스를 CreateDefaultSubObject하려고 했습니다.");

		if (false == std::is_base_of_v<UActorComponent, ComponentType>)
		{
			MSGASSERT("액터 컴포넌트를 상속받지 않은 클래스를 CreateDefaultSubObject하려고 했습니다.");
			return nullptr;
		}

		ComponentType* ComponentPtr = new ComponentType();
		UActorComponent* Temp = reinterpret_cast<UActorComponent*>(ComponentPtr);
		Temp->Owner = this;

		std::shared_ptr<ComponentType> NewComponent(ComponentPtr);

		ActorComponentList.push_back(NewComponent);

		return NewComponent;
	}

	ENGINE_API void SetActorLocation(const FVector4& _Value);
	ENGINE_API void AddActorLocation(const FVector4& _Value);
	ENGINE_API void SetActorRelativeScale3D(const FVector4& _Scale);

	inline ULevel* GetLevel() const { return Level; }
	inline void SetLevel(class ULevel* _Level) { Level = _Level; }
	ENGINE_API virtual void Tick(float _DeltaTime);

protected:
	ENGINE_API virtual void BeginPlay();

	std::shared_ptr<class USceneComponent> RootComponent;
private:
	class ULevel* Level = nullptr;

	std::list<std::shared_ptr<class UActorComponent>> ActorComponentList;
};

