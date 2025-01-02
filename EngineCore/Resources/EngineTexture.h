#pragma once
#include <EngineBase/EngineMath.h>
#include <EngineCore/Resources/EngineResource.h>

// Ό³Έν :
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

	virtual void Bind(Uint32 slot = 0) const = 0;
protected:

private:

};


class UEngineTexture2D : public UEngineTexture
{
public:
	ENGINE_API static std::shared_ptr<UEngineTexture2D> Create(Uint32 width, Uint32 height);
	ENGINE_API static std::shared_ptr<UEngineTexture2D> Create(const std::string& path);

	inline FVector2 GetTextureSize() { return TextureSize; }
protected:
	FVector2 TextureSize;
};


