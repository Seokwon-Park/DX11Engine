#pragma once
#include "Graphics/EngineShader.h"



// 설명 :
class DX11Shader : public UEngineShader
{
public:
	// constrcuter destructer
	DX11Shader(const std::string& filepath);
	~DX11Shader();

	// delete Function
	DX11Shader(const DX11Shader& _Other) = delete;
	DX11Shader(DX11Shader&& _Other) noexcept = delete;
	DX11Shader& operator=(const DX11Shader& _Other) = delete;
	DX11Shader& operator=(DX11Shader&& _Other) noexcept = delete;

	void SetVertexConstants(VertexConstant _Data) override;

	virtual void Bind() const override;
protected:

private:
	ComPtr<ID3D11VertexShader> VertexShader;
	ComPtr<ID3D11PixelShader> PixelShader;
	ComPtr<ID3D11InputLayout> InputLayout;

	ComPtr<ID3D11Buffer> VertexCBuffer;

	// EngineShader을(를) 통해 상속됨
};

