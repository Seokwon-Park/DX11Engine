#pragma once

#include <EngineBase/Object.h>
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineMath.h>

// ���� :
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
			"���� ������Ʈ�� ��ӹ��� ���� Ŭ������ CreateDefaultSubObject�Ϸ��� �߽��ϴ�.");

		if (false == std::is_base_of_v<UActorComponent, ComponentType>)
		{
			MSGASSERT("���� ������Ʈ�� ��ӹ��� ���� Ŭ������ CreateDefaultSubObject�Ϸ��� �߽��ϴ�.");
			return nullptr;
		}

		//�̰� �������� �𸣰ڳ� ��.
		std::string TypeName = typeid(ComponentType).name();
		size_t ix = 0;
		while (TypeName[ix] != ' ')
		{
			ix++;
		}
		//������ ��ġ + U�� �Ⱥٰ�? (������ ������ U ���λ簡 �پ������ ������)
		TypeName = TypeName.substr(ix + 2);
		ComponentType* ComponentPtr = new ComponentType();
		UActorComponent* ActorPtr = reinterpret_cast<UActorComponent*>(ComponentPtr);
		ActorPtr->Owner = this;
		ActorPtr->SetName(TypeName);
		std::shared_ptr<ComponentType> NewComponent(ComponentPtr);

		//Scene Component�� SetupAttachment�� ȣ������ ������ �����ص� ������� �ʵ��� �Ѵ�.
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

