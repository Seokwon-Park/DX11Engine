#pragma once
#include "EngineBuffer.h"

// 클래스 설명 :
class UEngineMesh : public UEngineResource
{
public:
	// Constrcuter Destructer
	UEngineMesh();
	~UEngineMesh();

	// Delete Function
	UEngineMesh(const UEngineMesh& _Other) = delete;
	UEngineMesh(UEngineMesh&& _Other) noexcept = delete;
	UEngineMesh& operator=(const UEngineMesh& _Other) = delete;
	UEngineMesh& operator=(UEngineMesh&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineMesh> Create(std::string_view _Name)
	{
		return Create(_Name, _Name, _Name);
	}
	static std::shared_ptr<UEngineMesh> Create(std::string_view _Name, std::string_view _VBName, std::string_view _IBName);

protected:
private:
	std::shared_ptr<UEngineVertexBuffer> VertexBuffer;
	std::shared_ptr<UEngineIndexBuffer> IndexBuffer;
};
