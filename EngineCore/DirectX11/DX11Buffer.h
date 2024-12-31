#pragma once
#include <EngineCore/Resources/EngineBuffer.h>

// 설명 :
class DX11VertexBuffer: public VertexBuffer
{
public:
	// constrcuter destructer
	DX11VertexBuffer(uint32 _DataSize, uint32 _VertexSize);
	DX11VertexBuffer(std::vector<Vertex>& _Vertices, uint32 _DataSize, uint32 _VertexCount);
	~DX11VertexBuffer();

	// delete Function
	DX11VertexBuffer(const DX11VertexBuffer& _Other) = delete;
	DX11VertexBuffer(DX11VertexBuffer&& _Other) noexcept = delete;
	DX11VertexBuffer& operator=(const DX11VertexBuffer& _Other) = delete;
	DX11VertexBuffer& operator=(DX11VertexBuffer&& _Other) noexcept = delete;

	virtual void Bind() const override;

protected:

private:
	ComPtr<ID3D11Buffer> Buffer; // DirectX 11 버퍼 객체
	uint32 Stride;
	uint32 Offset = 0;
};

// 설명 :
class DX11IndexBuffer : public IndexBuffer
{
public:
	// constrcuter destructer
	DX11IndexBuffer(std::vector<uint32>& _Indices, uint32 _IndexCount);
	~DX11IndexBuffer();

	// delete Function
	DX11IndexBuffer(const DX11IndexBuffer& _Other) = delete;
	DX11IndexBuffer(DX11IndexBuffer&& _Other) noexcept = delete;
	DX11IndexBuffer& operator=(const DX11IndexBuffer& _Other) = delete;
	DX11IndexBuffer& operator=(DX11IndexBuffer&& _Other) noexcept = delete;

	virtual void Bind() const override;
protected:

private:
	ComPtr<ID3D11Buffer> Buffer; // DirectX 11 버퍼 객체
	//size_t VertexSize;
	//size_t VertexCount;
};
