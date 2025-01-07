#pragma once
#include "EngineShader.h"
#include <EngineBase/EngineMath.h>
#include <EngineCore/Resources/EngineResource.h>

// 설명 :
class UEngineTexture : public UEngineResource
{
public:
	// constrcuter destructer
	UEngineTexture();
	virtual ~UEngineTexture();

	// delete Function
	UEngineTexture(const UEngineTexture& _Other) = delete;
	UEngineTexture(UEngineTexture&& _Other) noexcept = delete;
	UEngineTexture& operator=(const UEngineTexture& _Other) = delete;
	UEngineTexture& operator=(UEngineTexture&& _Other) noexcept = delete;

	virtual void SetData(void* data, Uint32 size) = 0;

	virtual void BindSRV(EShaderType _ShaderType, Uint32 slot = 0) const = 0;
protected:

private:

};


class UEngineTexture2D : public UEngineTexture
{
public:
	ENGINE_API static std::shared_ptr<UEngineTexture2D> Create(std::string_view _Name, D3D11_TEXTURE2D_DESC _Desc);
	ENGINE_API static std::shared_ptr<UEngineTexture2D> Create(std::string_view _Name, std::string_view _Path);

	virtual void SetData(void* data, Uint32 size);
	virtual void BindSRV(EShaderType _ShaderType, Uint32 _Slot = 0) const override;
	inline FVector2 GetTextureSize() { return TextureSize; }
	void CreateRTV();
	void CreateDSV();
	void CreateSRV();
	void CreateUAV();

	inline ID3D11RenderTargetView* GetRTV() { return RenderTargetView.Get(); }
	inline ID3D11DepthStencilView* GetDSV() { return DepthStencilView.Get(); }
	inline ID3D11ShaderResourceView* GetSRV() { return ShaderResourceView.Get(); }
	inline ID3D11UnorderedAccessView* GetUAV() { return UnorderedAccessView.Get(); }
	inline ComPtr<ID3D11Texture2D>& GetTextureRef() { return Texture; }
	void CreateTexture(D3D11_TEXTURE2D_DESC _Desc);
private:
	//이 텍스쳐는 ShaderResourceView 용으로 생성.
	void LoadTextureFromPath(std::string_view _Path);
	bool IsCreatable(D3D11_BIND_FLAG _BindFlag);

	FVector2 TextureSize;
	ComPtr<ID3D11Texture2D> Texture = nullptr;
	ComPtr<ID3D11RenderTargetView> RenderTargetView = nullptr;
	ComPtr<ID3D11DepthStencilView> DepthStencilView = nullptr;
	ComPtr<ID3D11ShaderResourceView> ShaderResourceView = nullptr;
	ComPtr<ID3D11UnorderedAccessView> UnorderedAccessView = nullptr;
};


