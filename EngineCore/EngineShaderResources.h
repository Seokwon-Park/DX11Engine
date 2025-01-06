#pragma once
#include <EngineBase/EngineString.h>
#include <EngineCore/Resources/EngineShader.h>
#include <EngineCore/Resources/EngineBuffer.h>
#include <EngineCore/Resources/EngineTexture.h>
#include <EngineCore/States/EngineSamplerState.h>

// ���� :
class UEngineShaderResources
{
public:
	// constrcuter destructer
	UEngineShaderResources();
	~UEngineShaderResources();

	// delete Function
	UEngineShaderResources(const UEngineShaderResources& _Other) = delete;
	UEngineShaderResources(UEngineShaderResources&& _Other) noexcept = delete;
	UEngineShaderResources& operator=(const UEngineShaderResources& _Other) = delete;
	UEngineShaderResources& operator=(UEngineShaderResources&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineShaderResources> Create(std::shared_ptr<UEngineShader> _Shader);
	
	void Bind() const;
	//�̰� Shader�ܰ迡�� ȣ��
	void CreateShaderResources(std::shared_ptr<UEngineShader> _Shader);
	inline void SetTexture(std::string_view _Name, std::shared_ptr<UEngineTexture2D> _Texture)
	{ 
		Textures[UEngineString::ToUpper(_Name)].second = _Texture; 
	}
	inline void SetSamplerState(std::string_view _Name, std::shared_ptr<UEngineSamplerState> _Sampler) 
	{ 
		SamplerStates[UEngineString::ToUpper(_Name)].second = _Sampler;
	}
	template <typename DataType>
	inline void SetConstantBuffer(std::string_view _Name, const DataType& Data)
	{
		ConstantBuffers[UEngineString::ToUpper(_Name)].second->SetData(Data);
	}
protected:

private:
	EShaderType ShaderType = EShaderType::NONE;
	// Shader���� �̸�, ���Թ�ȣ, �Ҵ� ���ҽ�
	std::map<std::string, std::pair<int,std::shared_ptr<UEngineTexture2D>>> Textures;
	std::map<std::string, std::pair<int,std::shared_ptr<UEngineSamplerState>>> SamplerStates;
	std::map<std::string, std::pair<int,std::shared_ptr<UEngineConstantBuffer>>> ConstantBuffers;

};

