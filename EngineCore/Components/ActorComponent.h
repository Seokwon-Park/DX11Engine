#pragma once

// Ό³Έν :
class UActorComponent : public UObject
{
	friend class AActor;
public:
	// constrcuter destructer
	ENGINE_API UActorComponent();
	ENGINE_API virtual ~UActorComponent();

	// delete Function
	UActorComponent(const UActorComponent& _Other) = delete;
	UActorComponent(UActorComponent&& _Other) noexcept = delete;
	UActorComponent& operator=(const UActorComponent& _Other) = delete;
	UActorComponent& operator=(UActorComponent&& _Other) noexcept = delete;

	class AActor* GetOwner();
protected:
	virtual void BeginPlay() {}
	virtual void TickComponent(float _DeltaTime) {};

private:
	AActor* Owner;

};

