#include "EnginePCH.h"
#include "EngineTexture.h"
#include "EngineCore.h"
#include "EngineDeviceContext.h"
#include "ResourceManager.h"
#include <EngineBase/EngineIO.h>
#include <EngineBase/EngineString.h>
#include <ThirdParty/DirectXTex/Include/DirectXTex.h>


UEngineTexture::UEngineTexture()
{
}

UEngineTexture::~UEngineTexture()
{
}

std::shared_ptr<UEngineTexture2D> UEngineTexture2D::Create(std::string_view _Name, D3D11_TEXTURE2D_DESC _Desc)
{
	std::shared_ptr<UEngineTexture2D> NewTexture = std::make_shared<UEngineTexture2D>();
	NewTexture->CreateTexture(_Desc);
	UResourceManager::AddResource<UEngineTexture2D>(NewTexture, _Name, "");
	return NewTexture;
}

std::shared_ptr<UEngineTexture2D> UEngineTexture2D::Load(std::string_view _Name, std::string_view _Path)
{
	std::shared_ptr<UEngineTexture2D> NewTexture = std::make_shared<UEngineTexture2D>();
	NewTexture->LoadTextureFromPath(_Path);
	UEnginePath Path = _Path;
	std::string Name = Path.GetFileNameWithoutExtension();
	UResourceManager::AddResource<UEngineTexture2D>(NewTexture, Name, _Path);
	return NewTexture;
}

std::shared_ptr<UEngineTexture2D> UEngineTexture2D::Create(std::string_view _Name, UINT _Width, UINT _Height)
{
	D3D11_TEXTURE2D_DESC Desc;
	ZeroMemory(&Desc, sizeof(D3D11_TEXTURE2D_DESC));
	Desc.Width = _Width;
	Desc.Height = _Height;
	Desc.MipLevels = 1;
	Desc.ArraySize = 1;
	Desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	Desc.SampleDesc.Count = 1;
	Desc.Usage = D3D11_USAGE_DYNAMIC;
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	return Create(_Name, Desc);
}

void UEngineTexture2D::CreateTexture(D3D11_TEXTURE2D_DESC _Desc)
{
	TextureSize.X = static_cast<float>(_Desc.Width);
	TextureSize.Y = static_cast<float>(_Desc.Height);
	UEngineCore::GetGraphicsDeviceContext()->GetDevice()->CreateTexture2D(&_Desc, nullptr, Texture.GetAddressOf());
	CreateRTV();
	CreateSRV();
	CreateDSV();
	CreateUAV();
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

	D3D11_TEXTURE2D_DESC Desc;
	ZeroMemory(&Desc, sizeof(D3D11_TEXTURE2D_DESC));
	Desc.Width = static_cast<UINT>(TextureSize.X);
	Desc.Height = static_cast<UINT>(TextureSize.Y);
	Desc.MipLevels = 1;
	Desc.ArraySize = 1;
	Desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	Desc.SampleDesc.Count = 1;
	Desc.Usage = D3D11_USAGE_IMMUTABLE;
	Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	DirectX::CreateTexture(UEngineCore::GetGraphicsDeviceContext()->GetDevice(), ImageData.GetImages(), ImageData.GetImageCount(), ImageData.GetMetadata(), reinterpret_cast<ID3D11Resource**>(Texture.GetAddressOf()));

	DeviceContext->GetDevice()->CreateShaderResourceView(Texture.Get(), nullptr, ShaderResourceView.GetAddressOf());

}

bool UEngineTexture2D::IsCreatable(D3D11_BIND_FLAG _BindFlag)
{
	D3D11_TEXTURE2D_DESC Desc;
	Texture->GetDesc(&Desc);
	if ((Desc.BindFlags & _BindFlag) != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void UEngineTexture2D::SetData(void* data, Uint32 size)
{
	// 데이터 업데이트
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	UEngineDeviceContext* DeviceContext = UEngineCore::GetGraphicsDeviceContext();
	DeviceContext->GetContext()->Map(Texture.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	// 데이터 복사
	memcpy(mappedResource.pData, data, size);
	DeviceContext->GetContext()->Unmap(Texture.Get(), 0);
}

void UEngineTexture2D::BindSRV(EShaderType _ShaderType, Uint32 _Slot) const
{
	if (nullptr == ShaderResourceView)
	{
		MSGASSERT("텍스쳐가 셰이더 리소스 뷰로 생성되지 않았습니다.")
	}
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


void UEngineTexture2D::CreateRTV()
{
	if (false == IsCreatable(D3D11_BIND_RENDER_TARGET))
	{
		return;
	}
	RenderTargetView = nullptr;
	HRESULT Result = UEngineCore::GetGraphicsDeviceContext()->GetDevice()->CreateRenderTargetView(Texture.Get(), nullptr, RenderTargetView.GetAddressOf());
	if (FAILED(Result))
	{
		MSGASSERT("렌더타겟뷰 생성에 실패했습니다.")
	}
}

void UEngineTexture2D::CreateDSV()
{
	if (false == IsCreatable(D3D11_BIND_DEPTH_STENCIL))
	{
		return;
	}
	DepthStencilView = nullptr;
	HRESULT Result = UEngineCore::GetGraphicsDeviceContext()->GetDevice()->CreateDepthStencilView(Texture.Get(), nullptr, DepthStencilView.GetAddressOf());
	if (FAILED(Result))
	{
		MSGASSERT("뎁스 스텐실 뷰 생성에 실패했습니다.")
	}
}

void UEngineTexture2D::CreateSRV()
{
	if (false == IsCreatable(D3D11_BIND_SHADER_RESOURCE))
	{
		return;
	}
	ShaderResourceView = nullptr;
	HRESULT Result = UEngineCore::GetGraphicsDeviceContext()->GetDevice()->CreateShaderResourceView(Texture.Get(), nullptr, ShaderResourceView.GetAddressOf());
	if (FAILED(Result))
	{
		MSGASSERT("셰이더 리소스 뷰 생성에 실패했습니다.")
	}
}

void UEngineTexture2D::CreateUAV()
{
	if (false == IsCreatable(D3D11_BIND_UNORDERED_ACCESS))
	{
		return;
	}
	UnorderedAccessView = nullptr;
	HRESULT Result = UEngineCore::GetGraphicsDeviceContext()->GetDevice()->CreateUnorderedAccessView(Texture.Get(), nullptr, UnorderedAccessView.GetAddressOf());
	if (FAILED(Result))
	{
		MSGASSERT("컴퓨트 셰이더 리소스 생성에 실패했습니다.")
	}
}
