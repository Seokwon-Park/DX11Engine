#pragma once
#include <EngineBase/EngineMath.h>

// Ό³Έν :
class Texture
{
public:
	// constrcuter destructer
	Texture();
	~Texture();

	// delete Function
	Texture(const Texture& _Other) = delete;
	Texture(Texture&& _Other) noexcept = delete;
	Texture& operator=(const Texture& _Other) = delete;
	Texture& operator=(Texture&& _Other) noexcept = delete;

	virtual uint32 GetWidth() const = 0;
	virtual uint32 GetHeight() const = 0;

	virtual void SetData(void* data, uint32 size) = 0;

	virtual void Bind(uint32 slot = 0) const = 0;
protected:

private:

};


class Texture2D : public Texture
{
public:
	static std::shared_ptr<Texture2D> Create(uint32 width, uint32 height);
	static std::shared_ptr<Texture2D> Create(const std::string& path);
};


