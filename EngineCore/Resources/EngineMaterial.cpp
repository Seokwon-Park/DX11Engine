#include "EnginePCH.h"
#include "EngineMaterial.h"
#include "EngineVertexShader.h"
#include "EnginePixelShader.h"
#include <EngineCore/ResourceManager.h>

UEngineMaterial::UEngineMaterial()
{
}

UEngineMaterial::~UEngineMaterial()
{
}

void UEngineMaterial::SetVS(std::string_view _VSName)
{
	SetVS(UResourceManager::Find<UEngineVertexShader>(_VSName));
}

void UEngineMaterial::SetVS(std::shared_ptr<class UEngineVertexShader> _VS)
{
	if (_VS == nullptr)
	{
		MSGASSERT("���̴��� nullptr�̾����ϴ�.")
	}
	VertexShader = _VS;
}

void UEngineMaterial::SetPS(std::string_view _PSName)
{
	SetPS(UResourceManager::Find<UEnginePixelShader>(_PSName));
}

void UEngineMaterial::SetPS(std::shared_ptr<class UEnginePixelShader> _PS)
{
	if (_PS == nullptr)
	{
		MSGASSERT("���̴��� nullptr�̾����ϴ�.")
	}
	PixelShader = _PS;
}

void UEngineMaterial::Bind() const
{
	if (VertexShader == nullptr || PixelShader == nullptr)
	{
		MSGASSERT("�������̴��� �ȼ����̴��� �ݵ�� �����Ǿ�� �մϴ�.")
	}
	VertexShader->Bind();
	PixelShader->Bind();
}

std::shared_ptr<UEngineMaterial> UEngineMaterial::Create(std::string_view _Name)
{
	return std::shared_ptr<UEngineMaterial>();
}

