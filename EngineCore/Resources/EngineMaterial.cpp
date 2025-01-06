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

void UEngineMaterial::SetShader(std::string_view _ShaderName, EShaderType _Type)
{
	std::shared_ptr<UEngineShader> Shader = UResourceManager::Find<UEngineShader>(_ShaderName);
	SetShader(Shader, _Type);
}

void UEngineMaterial::SetShader(std::shared_ptr<UEngineShader> _Shader, EShaderType _Type)
{
	if (_Shader == nullptr)
	{
		MSGASSERT("쉐이더가 nullptr이었습니다.")
	}
	Shaders[_Type] = _Shader;
	ShaderResources[_Type] = _Shader->GetShaderResources();
}

std::shared_ptr<UEngineShader> UEngineMaterial::GetShader(EShaderType _Type)
{
	return Shaders[_Type];
}

void UEngineMaterial::Bind()
{
	InputLayout->Bind();

	if (false == Shaders.contains(EShaderType::VS) || false == Shaders.contains(EShaderType::PS))
	{
		MSGASSERT("정점쉐이더와 픽셀쉐이더는 반드시 설정되어야 합니다.")
	}
	Shaders[EShaderType::VS]->Bind();
	
	if (true == Shaders.contains(EShaderType::HS) && true == Shaders.contains(EShaderType::DS))
	{
		Shaders[EShaderType::HS]->Bind();
		Shaders[EShaderType::DS]->Bind();
	}

	if (true == Shaders.contains(EShaderType::GS))
	{
		Shaders[EShaderType::GS]->Bind();
	}

	Shaders[EShaderType::PS]->Bind();

	if (true == Shaders.contains(EShaderType::CS))
	{
		Shaders[EShaderType::CS]->Bind();
	}

	ShaderResources[EShaderType::VS]->Bind();
	ShaderResources[EShaderType::PS]->Bind();
	/*if (nullptr != ShaderResources)
	{
		ShaderResources->Bind();
	}*/
}

//기본적인 머티리얼 - 사각형(Quad)
std::shared_ptr<UEngineMaterial> UEngineMaterial::Create()
{
	FMaterialDescription Desc;
	Desc.VSName = "QuadVS";
	Desc.PSName = "QuadPS";
	Desc.InputLayoutName = "Quad";
	return Create(Desc);
}

ENGINE_API std::shared_ptr<UEngineMaterial> UEngineMaterial::Create(FMaterialDescription _Desc)
{
	std::shared_ptr<UEngineMaterial> NewMaterial = std::make_shared<UEngineMaterial>();
	NewMaterial->CreateMaterial(_Desc);
	return NewMaterial;
}

void UEngineMaterial::CreateMaterial(FMaterialDescription _Desc)
{
	InputLayout = UResourceManager::Find<UEngineInputLayout>(_Desc.InputLayoutName);

	if (false == _Desc.VSName.empty())
	{
		SetShader(_Desc.VSName, EShaderType::VS);
	}
	if (false == _Desc.HSName.empty())
	{
		SetShader(_Desc.HSName, EShaderType::HS);
	}
	if (false == _Desc.DSName.empty())
	{
		SetShader(_Desc.DSName, EShaderType::DS);
	}
	if (false == _Desc.GSName.empty())
	{
		SetShader(_Desc.GSName, EShaderType::GS);
	}
	if (false == _Desc.PSName.empty())
	{
		SetShader(_Desc.PSName, EShaderType::PS);
	}
	if (false == _Desc.CSName.empty())
	{
		SetShader(_Desc.CSName, EShaderType::CS);
	}
}

