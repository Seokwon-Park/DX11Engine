#include "EnginePCH.h"
#include "DX11Buffer.h"
#include "EngineCore.h"
#include "DX11DeviceContext.h"


DX11VertexBuffer::DX11VertexBuffer(uint32 _DataSize, uint32 _VertexSize)
{
	Stride = _VertexSize;
	D3D11_BUFFER_DESC Desc;
	ZeroMemory(&Desc, sizeof(D3D11_BUFFER_DESC));
	Desc.ByteWidth = _DataSize;
	Desc.Usage = D3D11_USAGE_DYNAMIC;
	Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	Desc.MiscFlags = 0;
	Desc.StructureByteStride = 0; // 구조적 버퍼에서만 필요함.

	DX11DeviceContext* DeviceContext = static_cast<DX11DeviceContext*>(UEngineCore::GraphicsDevice);
	DeviceContext->GetDevice()->CreateBuffer(&Desc, nullptr, Buffer.GetAddressOf());
}

DX11VertexBuffer::DX11VertexBuffer(std::vector<Vertex>& _Vertices, uint32 _DataSize, uint32 _VertexCount)
{
	Stride = _DataSize/_VertexCount;
	D3D11_BUFFER_DESC Desc;
	ZeroMemory(&Desc, sizeof(D3D11_BUFFER_DESC));
	Desc.ByteWidth = _DataSize;
	Desc.Usage = D3D11_USAGE_IMMUTABLE;
	Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	Desc.CPUAccessFlags = 0;
	Desc.MiscFlags = 0;
	Desc.StructureByteStride = 0;

	DX11DeviceContext* DeviceContext = static_cast<DX11DeviceContext*>(UEngineCore::GraphicsDevice);

	D3D11_SUBRESOURCE_DATA VerticesData = { 0 }; // MS 예제에서 초기화하는 방식
	VerticesData.pSysMem = _Vertices.data();
	VerticesData.SysMemPitch = 0;
	VerticesData.SysMemSlicePitch = 0;

	DeviceContext->GetDevice()->CreateBuffer(&Desc, &VerticesData, Buffer.GetAddressOf());
}

DX11VertexBuffer::~DX11VertexBuffer()
{
}

void DX11VertexBuffer::Bind() const
{
	DX11DeviceContext* DeviceContext = static_cast<DX11DeviceContext*>(UEngineCore::GraphicsDevice);

	DeviceContext->GetContext()->IASetVertexBuffers(0, 1, Buffer.GetAddressOf(), &Stride, &Offset);
}

DX11IndexBuffer::DX11IndexBuffer(uint32 _DataSize, uint32 _VertexSize)
{
}

DX11IndexBuffer::DX11IndexBuffer(float* _Vertices, uint32 _DataSize, uint32 _VertexCount)
{
}

DX11IndexBuffer::~DX11IndexBuffer()
{
}
