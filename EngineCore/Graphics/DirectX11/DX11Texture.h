#pragma once
#include "Graphics/EngineTexture.h"

//#ifdef _DEBUG
//#pragma comment(lib, "DirectXTex_Debug.lib")
//#else
//#pragma comment(lib, "DirectXTex_Release.lib")
//#endif

// Ό³Έν :
class DX11Texture2D : public UEngineTexture2D
{
public:
	// constrcuter destructer
	DX11Texture2D(uint32 _Width, uint32 _Height);
	DX11Texture2D(const std::string& _Path);
	virtual ~DX11Texture2D();
	// delete Function
	DX11Texture2D(const DX11Texture2D& _Other) = delete;
	DX11Texture2D(DX11Texture2D&& _Other) noexcept = delete;
	DX11Texture2D& operator=(const DX11Texture2D& _Other) = delete;
	DX11Texture2D& operator=(DX11Texture2D&& _Other) noexcept = delete;

	virtual uint32 GetWidth() const override { return m_Width; }
	virtual uint32 GetHeight() const override { return m_Height; }

	virtual void SetData(void* data, uint32 size) override;

	virtual void Bind(uint32 slot = 0) const override;
protected:

private:
	ComPtr<ID3D11Texture2D> Texture;
	ComPtr<ID3D11ShaderResourceView> ShaderResourceView;
	std::string _Path;
	uint32 m_Width, m_Height;
};

