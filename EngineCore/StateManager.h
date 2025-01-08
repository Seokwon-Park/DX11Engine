#pragma once
#include <EngineBase/EngineIO.h>

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

	ENGINE_API static void CreateDefaultStates();
	static void CreateDefaultRasterizerState();
	static void CreateDefaultBlendState();
	static void CreateDefaultDepthStencilState();


	template<typename StateType>
	static std::shared_ptr<StateType> Find(std::string_view _Name)
	{
		const type_info& Info = typeid(StateType);
		return std::dynamic_pointer_cast<StateType>(Find(Info.name(), _Name.data()));
	}
	template<typename StateType>
	inline static void AddState(std::shared_ptr<class UEngineState> _Resource, std::string_view _Name)
	{
		const type_info& Info = typeid(StateType);
		AddState(_Resource, Info.name(), _Name);
	}

	inline static bool IsExist(std::string_view _Name) { return StateMap.contains(_Name.data()); }
	inline static void Release() { StateMap.clear(); }

	ENGINE_API static std::shared_ptr<class UEngineState> Find(std::string_view _StateType, std::string_view _StateName);
	ENGINE_API static void AddState(std::shared_ptr<class UEngineState> _State, const std::string_view _Info, std::string_view _Name);
private:
	ENGINE_API static std::map<std::string, std::map<std::string, std::shared_ptr<class UEngineState>>> StateMap;
};

