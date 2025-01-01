#pragma once

struct Vertex
{
	FVector4 Pos;
	FVector4 Color;
	float UV[2];
};

// 클래스 설명 :
class UEngineVertexBuffer 
{
public:
	// Constrcuter Destructer
	UEngineVertexBuffer();
	virtual ~UEngineVertexBuffer();

	// Delete Function
	UEngineVertexBuffer(const UEngineVertexBuffer& _Other) = delete;
	UEngineVertexBuffer(UEngineVertexBuffer&& _Other) noexcept = delete;
	UEngineVertexBuffer& operator=(const UEngineVertexBuffer& _Other) = delete;
	UEngineVertexBuffer& operator=(UEngineVertexBuffer&& _Other) noexcept = delete;

	virtual void Bind() const = 0;

	ENGINE_API static std::shared_ptr<UEngineVertexBuffer> Create(uint32 _Size, uint32 _VertexSize);
	ENGINE_API static std::shared_ptr<UEngineVertexBuffer> Create(std::vector<Vertex>& _Vertices, uint32 _DataSize, uint32 _VertexCount);
private:

};

// 클래스 설명 :
class UEngineIndexBuffer
{
public:
	// Constrcuter Destructer
	UEngineIndexBuffer();
	~UEngineIndexBuffer();

	// Delete Function
	UEngineIndexBuffer(const UEngineIndexBuffer& _Other) = delete;
	UEngineIndexBuffer(UEngineIndexBuffer&& _Other) noexcept = delete;
	UEngineIndexBuffer& operator=(const UEngineIndexBuffer& _Other) = delete;
	UEngineIndexBuffer& operator=(UEngineIndexBuffer&& _Other) noexcept = delete;

	virtual void Bind() const = 0;

	ENGINE_API static std::shared_ptr<UEngineIndexBuffer> Create(std::vector<uint32> _Indices, uint32 _IndexCount);
protected:
private:

};
