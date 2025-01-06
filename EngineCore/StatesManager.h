#pragma once

// Ό³Έν :
class UStatesManager
{
public:
	// constrcuter destructer
	UStatesManager();
	~UStatesManager();

	// delete Function
	UStatesManager(const UStatesManager& _Other) = delete;
	UStatesManager(UStatesManager&& _Other) noexcept = delete;
	UStatesManager& operator=(const UStatesManager& _Other) = delete;
	UStatesManager& operator=(UStatesManager&& _Other) noexcept = delete;

protected:

private:

};

