#pragma once
#include "ActorComponent.h"
#include <EngineCore/EngineInputEvent.h>

// Ό³Έν :
class UInputComponent : public UActorComponent
{
public:
	using EventCallback = std::function<void()>;

	// constrcuter destructer
	ENGINE_API UInputComponent();
	ENGINE_API ~UInputComponent();

	// delete Function
	UInputComponent(const UInputComponent& _Other) = delete;
	UInputComponent(UInputComponent&& _Other) noexcept = delete;
	UInputComponent& operator=(const UInputComponent& _Other) = delete;
	UInputComponent& operator=(UInputComponent&& _Other) noexcept = delete;

	virtual void TickComponent(float _DeltaTime) override;
	ENGINE_API void BindAction(KeyCode _KeyCode, KeyEvent _EventType, EventCallback _Function);
protected:
	virtual void BeginPlay() override;
private:
	std::map<KeyCode, UEngineInputEvent> KeyEvents;
};

