#pragma once

// Ό³Έν :
class UStateManager
{
public:
	// constrcuter destructer
	UStateManager();
	~UStateManager();

	// delete Function
	UStateManager(const UStateManager& _Other) = delete;
	UStateManager(UStateManager&& _Other) noexcept = delete;
	UStateManager& operator=(const UStateManager& _Other) = delete;
	UStateManager& operator=(UStateManager&& _Other) noexcept = delete;


};

