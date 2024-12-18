#pragma once

// Ό³Έν :
class UActorComponent : public UObject
{
	friend class AActor;
public:
	// constrcuter destructer
	UActorComponent();
	~UActorComponent();

	// delete Function
	UActorComponent(const UActorComponent& _Other) = delete;
	UActorComponent(UActorComponent&& _Other) noexcept = delete;
	UActorComponent& operator=(const UActorComponent& _Other) = delete;
	UActorComponent& operator=(UActorComponent&& _Other) noexcept = delete;

	std::shared_ptr<class AActor> GetOwner();
	virtual void InitializeComponent() {}
	virtual void BeginPlay() {}

protected:

private:
	std::shared_ptr<AActor> Owner;

};

