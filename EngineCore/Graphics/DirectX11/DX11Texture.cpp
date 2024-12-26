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

DX11Texture2D::DX11Texture2D(UEngineFile _Path)
{
	
	DX11DeviceContext* DeviceContext = static_cast<DX11DeviceContext*>(UEngineCore::GraphicsDevice);
	m_TextureResourceView.Reset();
	m_Texture.Reset();

	std::string Str = _Path.ToString();
	std::string Ext = _Path.GetFileExtension();
	std::wstring wLoadPath = UEngineString::ToWString(Str.c_str());
	std::string UpperExt = UEngineString::ToUpper(Ext.c_str());

	DirectX::TexMetadata Metadata;
	DirectX::ScratchImage ImageData;

	if (UpperExt == ".DDS")
	{
		if (S_OK != DirectX::LoadFromDDSFile(wLoadPath.c_str(), DirectX::DDS_FLAGS_NONE, &Metadata, ImageData))
		{
			MSGASSERT("DDS 파일 로드에 실패했습니다.");
			return;
		}
	}
	else if (UpperExt == ".TGA")
	{
		if (S_OK != DirectX::LoadFromTGAFile(wLoadPath.c_str(), DirectX::TGA_FLAGS_NONE, &Metadata, ImageData))
		{
			MSGASSERT("TGA 파일 로드에 실패했습니다.");
			return;
		}
	}
	else
	{
		if (S_OK != DirectX::LoadFromWICFile(wLoadPath.c_str(), DirectX::WIC_FLAGS_NONE, &Metadata, ImageData))
		{
			MSGASSERT(UpperExt + "파일 로드에 실패했습니다.");
			return;
		}
	}

	D3D11_TEXTURE2D_DESC txtDesc = {};
	txtDesc.Width = m_Width;
	txtDesc.Height = m_Height;
	txtDesc.MipLevels = 1;
	txtDesc.ArraySize = 1;
	txtDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	txtDesc.SampleDesc.Count = 1;
	txtDesc.Usage = D3D11_USAGE_IMMUTABLE;
	txtDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	ID3D11Resource** Res;
	m_Texture->QueryInterface(__uuidof(ID3D11Resource), (void**)&Res);
	DirectX::CreateTexture(DeviceContext->GetDevice(), ImageData.GetImages(), ImageData.GetImageCount(), ImageData.GetMetadata(), Res);
	

	//DeviceContext->GetDevice()->CreateTexture2D(&txtDesc, &InitData, m_Texture.GetAddressOf());
	DeviceContext->GetDevice()->CreateShaderResourceView(m_Texture.Get(), nullptr, m_TextureResourceView.GetAddressOf());
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
}
