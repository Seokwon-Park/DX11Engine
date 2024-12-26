#include "EnginePCH.h"
#include "EngineTexture.h"

Texture::Texture()
{
}

Texture::~Texture()
{
}

std::shared_ptr<Texture2D> Texture2D::Create(uint32 width, uint32 height)
{
    return std::shared_ptr<Texture2D>();
}

std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path)
{
    return std::shared_ptr<Texture2D>();
}
