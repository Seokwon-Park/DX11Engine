#include "EnginePCH.h"
#include "DX11Texture.h"
#include "EngineCore.h"
#include "DX11DeviceContext.h"
#include <EngineBase/EngineIO.h>
#include <EngineBase/EngineString.h>
#include <ThirdParty/DirectXTex/Include/DirectXTex.h>

DX11Texture2D::DX11Texture2D(uint32 _Width, uint32 _Height)
{
}

DX11Texture2D::DX11Texture2D(const std::string& _Path)
{
	DX11DeviceContext* DeviceContext = static_cast<DX11DeviceContext*>(UEngineCore::GraphicsDevice);
	ShaderResourceView.Reset();
	Texture.Reset();

	UEnginePath Path = UEnginePath(std::string_view(_Path));

	std::string Str = _Path;
	std::string Ext = Path.GetFileExtension();
	std::wstring wLoadPath = UEngineString::ToWString(Str.c_str());
	std::string UpperExt = UEngineString::ToUpper(Ext.c_str());

	DirectX::TexMetadata Metadata;
	DirectX::ScratchImage ImageData;

	if (UpperExt == ".DDS")
	{
		if (S_OK != DirectX::LoadFromDDSFile(wLoadPath.c_str(), DirectX::DDS_FLAGS_NONE, &Metadata, ImageData))
		{
			MSGASSERT("DDS ���� �ε忡 �����߽��ϴ�.");
			return;
		}
	}
	else if (UpperExt == ".TGA")
	{
		if (S_OK != DirectX::LoadFromTGAFile(wLoadPath.c_str(), DirectX::TGA_FLAGS_NONE, &Metadata, ImageData))
		{
			MSGASSERT("TGA ���� �ε忡 �����߽��ϴ�.");
			return;
		}
	}
	else
	{
		if (S_OK != DirectX::LoadFromWICFile(wLoadPath.c_str(), DirectX::WIC_FLAGS_NONE, &Metadata, ImageData))
		{
			MSGASSERT(UpperExt + "���� �ε忡 �����߽��ϴ�.");
			return;
		}
	}

	TextureSize.X = static_cast<float>(Metadata.width);
	TextureSize.Y = static_cast<float>(Metadata.height);

	D3D11_TEXTURE2D_DESC txtDesc = {};
	txtDesc.Width = static_cast<UINT>(TextureSize.X);
	txtDesc.Height = static_cast<UINT>(TextureSize.Y);
	txtDesc.MipLevels = 1;
	txtDesc.ArraySize = 1;
	txtDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	txtDesc.SampleDesc.Count = 1;
	txtDesc.Usage = D3D11_USAGE_IMMUTABLE;
	txtDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	DirectX::CreateTexture(DeviceContext->GetDevice(), ImageData.GetImages(), ImageData.GetImageCount(), ImageData.GetMetadata(), (ID3D11Resource**)Texture.GetAddressOf());

	//DeviceContext->GetDevice()->CreateTexture2D(&txtDesc, &InitData, m_Texture.GetAddressOf());
	DeviceContext->GetDevice()->CreateShaderResourceView(Texture.Get(), nullptr, ShaderResourceView.GetAddressOf());
	//m_Context->GetD3DContext()->PSSetShaderResources(0, 1, m_TextureResourceView.GetAddressOf());
}

DX11Texture2D::~DX11Texture2D()
{
}

void DX11Texture2D::SetData(void* data, uint32 size)
{
}

void DX11Texture2D::Bind(uint32 slot) const
{
	DX11DeviceContext* DeviceContext = static_cast<DX11DeviceContext*>(UEngineCore::GraphicsDevice);

	DeviceContext->GetContext()->PSSetShaderResources(0, 1, ShaderResourceView.GetAddressOf());
}