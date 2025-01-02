#pragma once
#include "EngineResource.h"

struct Vertex
{
	FVector4 Pos;
	FVector4 Color;
	float UV[2];
};

// 클래스 설명 :
class UEngineVertexBuffer : public UEngineResource
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

	inline Uint32 GetVertexSize() { return VertexSize; }
	inline Uint32 GetVertexCount() { return VertexCount; }

	ENGINE_API static std::shared_ptr<UEngineVertexBuffer> Create(Uint32 _Size, Uint32 _VertexSize);
	ENGINE_API static std::shared_ptr<UEngineVertexBuffer> Create(const void* _Data, Uint32 _DataSize, Uint32 _VertexCount);
private:
	Uint32 VertexSize;
	Uint32 VertexCount;
};

// 클래스 설명 :
class UEngineIndexBuffer : public UEngineResource
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

	ENGINE_API static std::shared_ptr<UEngineIndexBuffer> Create(Uint32* _Indices, Uint32 _IndexCount);
protected:
private:

};
