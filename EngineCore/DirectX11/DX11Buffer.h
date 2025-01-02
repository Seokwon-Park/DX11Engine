#pragma once
#include <EngineCore/Resources/EngineBuffer.h>

// 설명 :
class DX11VertexBuffer: public UEngineVertexBuffer
{
public:
	// constrcuter destructer
	DX11VertexBuffer(Uint32 _DataSize, Uint32 _VertexSize);
	DX11VertexBuffer(const void* _Data, Uint32 _DataSize, Uint32 _VertexCount);
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
	Uint32 Stride;
	Uint32 Offset = 0;
};

// 설명 :
class DX11IndexBuffer : public UEngineIndexBuffer
{
public:
	// constrcuter destructer
	DX11IndexBuffer(Uint32* _Indices, Uint32 _IndexCount);
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
