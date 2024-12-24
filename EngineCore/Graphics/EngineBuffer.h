#pragma once

struct Vertex
{
	FVector4 Pos;
	FVector4 Color;
};

// 클래스 설명 :
class VertexBuffer 
{
public:
	// Constrcuter Destructer
	VertexBuffer();
	virtual ~VertexBuffer();

	// Delete Function
	VertexBuffer(const VertexBuffer& _Other) = delete;
	VertexBuffer(VertexBuffer&& _Other) noexcept = delete;
	VertexBuffer& operator=(const VertexBuffer& _Other) = delete;
	VertexBuffer& operator=(VertexBuffer&& _Other) noexcept = delete;

	virtual void Bind() const = 0;

	ENGINE_API static std::shared_ptr<VertexBuffer> Create(uint32 _Size, uint32 _VertexSize);
	ENGINE_API static std::shared_ptr<VertexBuffer> Create(std::vector<Vertex>& _Vertices, uint32 _DataSize, uint32 _VertexCount);
private:

};

// 클래스 설명 :
class IndexBuffer
{
public:
	// Constrcuter Destructer
	IndexBuffer();
	~IndexBuffer();

	// Delete Function
	IndexBuffer(const IndexBuffer& _Other) = delete;
	IndexBuffer(IndexBuffer&& _Other) noexcept = delete;
	IndexBuffer& operator=(const IndexBuffer& _Other) = delete;
	IndexBuffer& operator=(IndexBuffer&& _Other) noexcept = delete;

	virtual void Bind() const = 0;

	ENGINE_API static std::shared_ptr<IndexBuffer> Create(std::vector<uint32> _Indices, uint32 _IndexCount);
protected:
private:

};
