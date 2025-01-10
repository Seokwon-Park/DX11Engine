#pragma once

#include <EngineBase/Object.h>
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineMath.h>

// 설명 :
class AActor : public UObject
{
	friend class ULevel;
	friend class UHierarchyWindow;
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
	inline std::shared_ptr<ComponentType> CreateDefaultSubobject()
	{
		static_assert(std::is_base_of_v<UActorComponent, ComponentType>,
			"액터 컴포넌트를 상속받지 않은 클래스를 CreateDefaultSubObject하려고 했습니다.");

		if (false == std::is_base_of_v<UActorComponent, ComponentType>)
		{
			MSGASSERT("액터 컴포넌트를 상속받지 않은 클래스를 CreateDefaultSubObject하려고 했습니다.");
			return nullptr;
		}

		//이게 괜찮은지 모르겠네 ㅋ.
		std::string TypeName = typeid(ComponentType).name();
		size_t ix = 0;
		while (TypeName[ix] != ' ')
		{
			ix++;
		}
		//공백의 위치 + U도 안붙게? (어차피 무조건 U 접두사가 붙어버리기 때문에)
		TypeName = TypeName.substr(ix + 2);
		ComponentType* ComponentPtr = new ComponentType();
		UActorComponent* ActorPtr = reinterpret_cast<UActorComponent*>(ComponentPtr);
		ActorPtr->Owner = this;
		ActorPtr->SetName(TypeName);
		std::shared_ptr<ComponentType> NewComponent(ComponentPtr);

		//Scene Component는 SetupAttachment를 호출하지 않으면 생성해도 적용되지 않도록 한다.
		if (false == std::is_base_of_v<USceneComponent, ComponentType>)
		{
			ActorComponentList.push_back(NewComponent);
		}

		return NewComponent;
	}

	ENGINE_API void SetActorLocation(const FVector4& _Value);
	ENGINE_API void AddActorLocation(const FVector4& _Value);
	ENGINE_API void SetActorRotation(const FVector4& _Rotation);
	ENGINE_API void AddActorRotation(const FVector4& _Rotation);
	ENGINE_API void SetActorRelativeScale3D(const FVector4& _Scale);

	inline class ULevel* GetLevel() const { return Level; }
	inline void SetLevel(class ULevel* _Level) { Level = _Level; }
	ENGINE_API virtual void Tick(float _DeltaTime);

protected:
	ENGINE_API virtual void BeginPlay();

	std::shared_ptr<class USceneComponent> RootComponent;
private:
	class ULevel* Level = nullptr;

	std::list<std::shared_ptr<class UActorComponent>> ActorComponentList;
	//std::map<int, std::shared_ptr<class ACameraActor>> CameraActors;

};

