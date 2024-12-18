#pragma once

struct EngineVertex
{
	FVector4 Pos;
	FVector4 Color;
};
// 클래스 설명 :
class EngineVertexBuffer 
{
public:
	// Constrcuter Destructer
	EngineVertexBuffer();
	~EngineVertexBuffer();

	// Delete Function
	EngineVertexBuffer(const EngineVertexBuffer& _Other) = delete;
	EngineVertexBuffer(EngineVertexBuffer&& _Other) noexcept = delete;
	EngineVertexBuffer& operator=(const EngineVertexBuffer& _Other) = delete;
	EngineVertexBuffer& operator=(EngineVertexBuffer&& _Other) noexcept = delete;

	void CreateVertexBuffer();
protected:
private:

};
