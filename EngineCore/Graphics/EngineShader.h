#pragma once

struct VertexConstant
{
	FMatrix World;
	FMatrix View;
	FMatrix Proj;
};

// Ό³Έν :
class EngineShader
{
public:
	// constrcuter destructer
	EngineShader();
	~EngineShader();

	// delete Function
	EngineShader(const EngineShader& _Other) = delete;
	EngineShader(EngineShader&& _Other) noexcept = delete;
	EngineShader& operator=(const EngineShader& _Other) = delete;
	EngineShader& operator=(EngineShader&& _Other) noexcept = delete;

	virtual void Bind() const = 0;

	virtual void SetVertexConstants(VertexConstant _Data) = 0;

	ENGINE_API static std::shared_ptr<EngineShader> Create(const std::string& filepath);
	ENGINE_API static std::shared_ptr<EngineShader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
protected:

private:

};

