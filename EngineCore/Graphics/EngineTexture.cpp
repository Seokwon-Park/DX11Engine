#include "EnginePCH.h"
#include "EngineTexture.h"
#include "EngineCore.h"
#include "Graphics/DirectX11/DX11Texture.h"

UEngineTexture::UEngineTexture()
{
}

UEngineTexture::~UEngineTexture()
{
}

std::shared_ptr<UEngineTexture2D> UEngineTexture2D::Create(uint32 width, uint32 height)
{
	switch (UEngineCore::GraphicsDevice->GetRendererAPI())
	{
	case ERendererAPI::DirectX11:
		return std::make_shared<DX11Texture2D>(1, 2);
	case ERendererAPI::None:
		return nullptr;
	default:
		return nullptr;
	}
}

std::shared_ptr<UEngineTexture2D> UEngineTexture2D::Create(const std::string& path)
{
    return std::shared_ptr<UEngineTexture2D>();
}
