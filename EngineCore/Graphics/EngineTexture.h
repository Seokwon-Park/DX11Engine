#pragma once
#include <EngineBase/EngineMath.h>
#include "EngineResource.h"

// Ό³Έν :
class UEngineTexture : public UEngineResource
{
public:
	// constrcuter destructer
	UEngineTexture();
	~UEngineTexture();

	// delete Function
	UEngineTexture(const UEngineTexture& _Other) = delete;
	UEngineTexture(UEngineTexture&& _Other) noexcept = delete;
	UEngineTexture& operator=(const UEngineTexture& _Other) = delete;
	UEngineTexture& operator=(UEngineTexture&& _Other) noexcept = delete;

	virtual uint32 GetWidth() const = 0;
	virtual uint32 GetHeight() const = 0;

	virtual void SetData(void* data, uint32 size) = 0;

	virtual void Bind(uint32 slot = 0) const = 0;
protected:

private:

};


class UEngineTexture2D : public UEngineTexture
{
public:
	static std::shared_ptr<UEngineTexture2D> Create(uint32 width, uint32 height);
	static std::shared_ptr<UEngineTexture2D> Create(const std::string& path);
};


