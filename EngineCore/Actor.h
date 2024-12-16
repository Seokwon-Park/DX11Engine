#pragma once

// Ό³Έν :
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

	void CreateDefaultSubobject()
	{

	}
	virtual void Tick(float _DeltaTime) = 0;
protected:
	virtual void BeginPlay() = 0;
private:
	std::shared_ptr<class USceneComponent> RootComponent;
	std::list<std::shared_ptr<class UActorComponent>> ActorComponentList;

};

