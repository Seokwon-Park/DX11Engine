#include "EnginePCH.h"
#include "EngineTexture.h"
#include "EngineCore.h"
#include "EngineDeviceContext.h"
#include <EngineBase/EngineIO.h>
#include <EngineBase/EngineString.h>
#include <ThirdParty/DirectXTex/Include/DirectXTex.h>


UEngineTexture::UEngineTexture()
{
}

UEngineTexture::~UEngineTexture()
{
}

std::shared_ptr<UEngineTexture2D> UEngineTexture2D::Create(Uint32 width, Uint32 height)
{
	return nullptr;
}

std::shared_ptr<UEngineTexture2D> UEngineTexture2D::Create(std::string_view _Path)
{
	std::shared_ptr<UEngineTexture2D> NewTexture = std::make_shared<UEngineTexture2D>();
	NewTexture->LoadTextureFromPath(_Path);
	return NewTexture;
}

void UEngineTexture2D::LoadTextureFromPath(std::string_view _Path)
{
	UEngineDeviceContext* DeviceContext = UEngineCore::GetGraphicsDeviceContext();
	ShaderResourceView.Reset();
	Texture.Reset();

	UEnginePath Path = UEnginePath(std::string_view(_Path));

	std::string Str = _Path.data();
	std::string Ext = Path.GetFileExtension();
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

	TextureSize.X = static_cast<float>(Metadata.width);
	TextureSize.Y = static_cast<float>(Metadata.height);

	D3D11_TEXTURE2D_DESC TextureDesc = {};
	TextureDesc.Width = static_cast<UINT>(TextureSize.X);
	TextureDesc.Height = static_cast<UINT>(TextureSize.Y);
	TextureDesc.MipLevels = 1;
	TextureDesc.ArraySize = 1;
	TextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	TextureDesc.SampleDesc.Count = 1;
	TextureDesc.Usage = D3D11_USAGE_IMMUTABLE;
	TextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	DirectX::CreateTexture(DeviceContext->GetDevice(), ImageData.GetImages(), ImageData.GetImageCount(), ImageData.GetMetadata(), reinterpret_cast<ID3D11Resource**>(Texture.GetAddressOf()));

	DeviceContext->GetDevice()->CreateShaderResourceView(Texture.Get(), nullptr, ShaderResourceView.GetAddressOf());
}

void UEngineTexture2D::SetData(void* data, Uint32 size)
{
}

void UEngineTexture2D::Bind(EShaderType _ShaderType, Uint32 _Slot) const
{
	switch (_ShaderType)
	{
	case EShaderType::VS:
		UEngineCore::GetGraphicsDeviceContext()->GetContext()->VSSetShaderResources(_Slot, 1, ShaderResourceView.GetAddressOf());
		break;
	case EShaderType::HS:
		UEngineCore::GetGraphicsDeviceContext()->GetContext()->HSSetShaderResources(_Slot, 1, ShaderResourceView.GetAddressOf());
		break;
	case EShaderType::DS:
		UEngineCore::GetGraphicsDeviceContext()->GetContext()->DSSetShaderResources(_Slot, 1, ShaderResourceView.GetAddressOf());
		break;
	case EShaderType::GS:
		UEngineCore::GetGraphicsDeviceContext()->GetContext()->GSSetShaderResources(_Slot, 1, ShaderResourceView.GetAddressOf());
		break;
	case EShaderType::PS:
		UEngineCore::GetGraphicsDeviceContext()->GetContext()->PSSetShaderResources(_Slot, 1, ShaderResourceView.GetAddressOf());
		break;
	case EShaderType::CS:
		UEngineCore::GetGraphicsDeviceContext()->GetContext()->CSSetShaderResources(_Slot, 1, ShaderResourceView.GetAddressOf());
		break;
	default:
		break;
	}

}