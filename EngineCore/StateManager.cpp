#include "EnginePCH.h"
#include "StateManager.h"
#include <EngineBase/EngineString.h>
#include <EngineCore/States/EngineState.h>
#include <EngineCore/States/EngineRasterizerState.h>
#include <EngineCore/States/EngineBlendState.h>
#include <EngineCore/States/EngineDepthStencilState.h>

std::map<std::string, std::map<std::string, std::shared_ptr<UEngineState>>> UStateManager::StateMap;

UStateManager::UStateManager()
{
}

UStateManager::~UStateManager()
{
}

std::shared_ptr<UEngineState> UStateManager::Find(std::string_view _StateType, std::string_view _StateName)
{
	std::string UpperName = UEngineString::ToUpper(_StateName);

	if (false == StateMap[_StateType.data()].contains(UpperName))
	{
		return nullptr;
	}

	return StateMap[_StateType.data()][UpperName];
}

void UStateManager::AddState(std::shared_ptr<UEngineState> _State, const std::string_view _Info, std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);
	if (true == StateMap[_Info.data()].contains(UpperName))
	{
		MSGASSERT("이미 추가한 리소스를 또 추가하려고 했습니다" + std::string(_Info.data()) + "  " + _Name.data());
		return;
	}

	_State->SetName(UpperName);
	StateMap[_Info.data()].insert(std::make_pair(UpperName, _State));
}

void UStateManager::CreateDefaultStates()
{
	CreateDefaultRasterizerState();
	CreateDefaultBlendState();
	CreateDefaultDepthStencilState();
}

void UStateManager::CreateDefaultRasterizerState()
{
	UEngineRasterizerState::Create("Default");
	D3D11_RASTERIZER_DESC Desc;
	ZeroMemory(&Desc, sizeof(D3D11_RASTERIZER_DESC));
	Desc.CullMode = D3D11_CULL_NONE;
	Desc.FillMode = D3D11_FILL_WIREFRAME;
	UEngineRasterizerState::Create("Wired", Desc);
}

void UStateManager::CreateDefaultBlendState()
{
	UEngineBlendState::Create("Default");
}

void UStateManager::CreateDefaultDepthStencilState()
{
	UEngineDepthStencilState::Create("Default");
}
