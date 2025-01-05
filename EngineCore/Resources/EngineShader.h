#pragma once
#include "EngineResource.h"
#include <EngineCore/EngineCore.h>
#include <EngineCore/EngineDeviceContext.h>


struct VertexConstant
{
	FMatrix World;
	FMatrix View;
	FMatrix Proj;
};

enum class EShaderType
{
	NONE,
	VS,
	HS,
	DS,
	GS,
	PS,
	CS,
};

// Ό³Έν :
class UEngineShader : public UEngineResource
{
public:
	UEngineShader();
	virtual ~UEngineShader();


	//virtual void SetVertexConstants(VertexConstant _Data) = 0;
	//virtual void SetSpriteConstants(struct FSpriteRect _Data) = 0;

	//ENGINE_API static std::vector<std::shared_ptr<UEngineShader>> CreateShaders(std::string_view _FilePath, std::vector<EShaderType> _ShaderTypes);
	virtual void Bind() const = 0;
	virtual void Compile();
	inline void Init(std::string_view _FilePath, EShaderType _Type) 
	{
		Path = _FilePath; 
		ShaderType = _Type;
	}
	inline ID3DBlob* GetShaderBlob() const { return ShaderBlob.Get(); }
protected:
	ComPtr<ID3DBlob> ShaderBlob;
	ComPtr<ID3DBlob> ShaderCompileErrorBlob;

private:
	EShaderType ShaderType = EShaderType::NONE;
};




