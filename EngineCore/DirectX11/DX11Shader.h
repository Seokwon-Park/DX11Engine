#pragma once
#include <EngineCore/Resources/EngineShader.h>

// 설명 :
class DX11Shader : public UEngineShader
{
public:
	// constrcuter destructer
	DX11Shader(std::string_view _FilePath, EShaderType _ShaderType);
	~DX11Shader();

	// delete Function
	DX11Shader(const DX11Shader& _Other) = delete;
	DX11Shader(DX11Shader&& _Other) noexcept = delete;
	DX11Shader& operator=(const DX11Shader& _Other) = delete;
	DX11Shader& operator=(DX11Shader&& _Other) noexcept = delete;
protected:

	ComPtr<ID3D11SamplerState> SamplerState;


private:
	ComPtr<ID3D11InputLayout> InputLayout;
};

class DX11VertexShader : public DX11Shader
{
public:
	// constrcuter destructer
	DX11VertexShader(std::string_view _FilePath, EShaderType _ShaderType);
	~DX11VertexShader();

	// delete Function
	DX11VertexShader(const DX11VertexShader& _Other) = delete;
	DX11VertexShader(DX11VertexShader&& _Other) noexcept = delete;
	DX11VertexShader& operator=(const DX11VertexShader& _Other) = delete;
	DX11VertexShader& operator=(DX11VertexShader&& _Other) noexcept = delete;

	//void SetVertexConstants(VertexConstant _Data) override;
	//void SetSpriteConstants(FSpriteRect _Data) override;

	virtual void Bind() const override;
protected:

private:

	ComPtr<ID3D11Buffer> VertexCBuffer;
	ComPtr<ID3D11Buffer> UVBuffer;
	ComPtr<ID3D11SamplerState> SamplerState;
};


class DX11PixelShader : public DX11Shader
{
public:
	// constrcuter destructer
	DX11PixelShader(std::string_view _FilePath, EShaderType _ShaderType);
	~DX11PixelShader();

	// delete Function
	DX11PixelShader(const DX11PixelShader& _Other) = delete;
	DX11PixelShader(DX11PixelShader&& _Other) noexcept = delete;
	DX11PixelShader& operator=(const DX11PixelShader& _Other) = delete;
	DX11PixelShader& operator=(DX11PixelShader&& _Other) noexcept = delete;

	virtual void Bind() const override;
protected:

private:
	ComPtr<ID3D11PixelShader> PixelShader;

	ComPtr<ID3D11Buffer> VertexCBuffer;
	ComPtr<ID3D11Buffer> UVBuffer;
	ComPtr<ID3D11SamplerState> SamplerState;

	// EngineShader을(를) 통해 상속됨
};

