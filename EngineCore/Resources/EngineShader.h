#pragma once
#include <EngineCore/EngineCore.h>
#include "EngineResource.h"


struct VertexConstant
{
	FMatrix World;
	FMatrix View;
	FMatrix Proj;
};

enum class EShaderType
{
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

	virtual void Bind() const = 0;

	//virtual void SetVertexConstants(VertexConstant _Data) = 0;
	//virtual void SetSpriteConstants(struct FSpriteRect _Data) = 0;

	ENGINE_API static std::vector<std::shared_ptr<UEngineShader>> CreateShaders(std::string_view _FilePath, std::vector<EShaderType> _ShaderTypes);
	ENGINE_API static std::shared_ptr<UEngineShader> Create(std::string_view _FilePath, EShaderType _ShaderType);
	//ENGINE_API static std::shared_ptr<UEngineVertexShader> Create(std::string_view& _Name, std::string_view _ShaderSrc);

	ID3DBlob* GetShaderBlob() const { return ShaderBlob.Get(); }
protected:
	ComPtr<ID3DBlob> ShaderBlob;
	ComPtr<ID3DBlob> ShaderCompileErrorBlob;

private:
	static std::shared_ptr<UEngineShader> DX11CreateShader(std::string_view _FilePath, EShaderType _ShaderType);
	EShaderType ShaderType;

	
};


