#include "EnginePCH.h"
#include "EngineShaderResources.h"

UEngineShaderResources::UEngineShaderResources()
{
}

UEngineShaderResources::~UEngineShaderResources()
{
}

std::shared_ptr<UEngineShaderResources> UEngineShaderResources::Create(std::shared_ptr<UEngineShader> _Shader)
{
	std::shared_ptr<UEngineShaderResources> Result = std::make_shared<UEngineShaderResources>();
	Result->CreateShaderResources(_Shader);
	return Result;
}


void UEngineShaderResources::CreateShaderResources(std::shared_ptr<UEngineShader> _Shader)
{
	ShaderType = _Shader->GetShaderType();
	ID3D11ShaderReflection* ShaderReflection = _Shader->GetShaderReflection();

	D3D11_SHADER_DESC Desc;
	ShaderReflection->GetDesc(&Desc);

	D3D11_SHADER_INPUT_BIND_DESC ResourceDesc;

	// 쉐이더에 있는 리소스 개수 = D3D11_SHADER_DESC BoundResources
	for (UINT i = 0; i < Desc.BoundResources; i++)
	{
		ShaderReflection->GetResourceBindingDesc(i, &ResourceDesc);

		std::string Name = ResourceDesc.Name;
		std::string UpperName = UEngineString::ToUpper(Name);

		D3D_SHADER_INPUT_TYPE Type = ResourceDesc.Type;

		switch (Type)
		{
		case D3D_SIT_CBUFFER:
		{
			// 구체화된 정보를 얻어옵니다.
			ID3D11ShaderReflectionConstantBuffer* ConstantBufferReflection = ShaderReflection->GetConstantBufferByName(ResourceDesc.Name);
			D3D11_SHADER_BUFFER_DESC BufferDesc = { 0 };
			ConstantBufferReflection->GetDesc(&BufferDesc);

			std::shared_ptr<UEngineConstantBuffer> Buffer = UEngineConstantBuffer::CreateEmpty(BufferDesc.Size);

			ConstantBuffers[UpperName] = std::make_pair(ResourceDesc.BindPoint, Buffer);
			break;
		}
		case D3D_SIT_TEXTURE:
		{
			Textures[UpperName] = std::make_pair(ResourceDesc.BindPoint, nullptr);
			break;
		}
		case D3D_SIT_SAMPLER:
		{
			SamplerStates[UpperName] = std::make_pair(ResourceDesc.BindPoint, nullptr);
			break;
		}
		default:
			break;
		}
	}
}

void UEngineShaderResources::Bind() const
{
	for (auto& [Key, Value] : ConstantBuffers)
	{
		Uint32 Slot = Value.first;
		std::shared_ptr<UEngineConstantBuffer> ConstantBuffer = Value.second;
		ConstantBuffer->Bind(ShaderType, Slot);
	}
	for (auto& [Key, Value] : Textures)
	{
		Uint32 Slot = Value.first;
		std::shared_ptr<UEngineTexture2D> Texture = Value.second;
		Texture->BindSRV(ShaderType, Slot);
	}
	for (auto& [Key, Value] : SamplerStates)
	{
		Uint32 Slot = Value.first;
		std::shared_ptr<UEngineSamplerState> SamplerState = Value.second;
		SamplerState->Bind(ShaderType, Slot);
	}
}
