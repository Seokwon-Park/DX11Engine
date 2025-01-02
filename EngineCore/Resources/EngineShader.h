#pragma once

struct VertexConstant
{
	FMatrix World;
	FMatrix View;
	FMatrix Proj;
};

// Ό³Έν :
class UEngineShader
{
public:
	// constrcuter destructer
	UEngineShader();
	~UEngineShader();

	// delete Function
	UEngineShader(const UEngineShader& _Other) = delete;
	UEngineShader(UEngineShader&& _Other) noexcept = delete;
	UEngineShader& operator=(const UEngineShader& _Other) = delete;
	UEngineShader& operator=(UEngineShader&& _Other) noexcept = delete;

	virtual void Bind() const = 0;

	virtual void SetVertexConstants(VertexConstant _Data) = 0;
	virtual void SetSpriteConstants(struct FSpriteRect _Data) = 0;

	ENGINE_API static std::shared_ptr<UEngineShader> Create(const std::string& filepath);
	ENGINE_API static std::shared_ptr<UEngineShader> Create(const std::string& _Name, const std::string& vertexSrc, const std::string& fragmentSrc);
protected:

private:

};

