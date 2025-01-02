#include "EnginePCH.h"
#include "DX11Buffer.h"
#include "EngineCore.h"
#include "DX11DeviceContext.h"


DX11VertexBuffer::DX11VertexBuffer(Uint32 _DataSize, Uint32 _VertexSize)
{
	Stride = _VertexSize;
	D3D11_BUFFER_DESC Desc;
	ZeroMemory(&Desc, sizeof(D3D11_BUFFER_DESC));
	Desc.ByteWidth = _DataSize;
	Desc.Usage = D3D11_USAGE_DYNAMIC;
	Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//Desc.MiscFlags = 0;
	Desc.StructureByteStride = sizeof(Vertex); // ������ ���ۿ����� �ʿ���.

	DX11DeviceContext* DeviceContext = static_cast<DX11DeviceContext*>(UEngineCore::GraphicsDevice);
	DeviceContext->GetDevice()->CreateBuffer(&Desc, nullptr, Buffer.GetAddressOf());
}
 
DX11VertexBuffer::DX11VertexBuffer(const void* _Data, Uint32 _DataSize, Uint32 _VertexCount)
{
	Stride = _DataSize / _VertexCount;
	D3D11_BUFFER_DESC Desc;
	ZeroMemory(&Desc, sizeof(D3D11_BUFFER_DESC));
	Desc.ByteWidth = _DataSize;
	Desc.Usage = D3D11_USAGE_IMMUTABLE;
	Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	Desc.CPUAccessFlags = 0;
	//Desc.MiscFlags = 0;
	Desc.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA VerticesData = { 0 };
	 // MS �������� �ʱ�ȭ�ϴ� ���
	VerticesData.pSysMem = _Data;
	VerticesData.SysMemPitch = 0;
	VerticesData.SysMemSlicePitch = 0;

	DX11DeviceContext* DeviceContext = static_cast<DX11DeviceContext*>(UEngineCore::GraphicsDevice);
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

DX11IndexBuffer::DX11IndexBuffer(Uint32* _Indices, Uint32 _IndexCount)
{
	D3D11_BUFFER_DESC Desc = {};
	ZeroMemory(&Desc, sizeof(D3D11_BUFFER_DESC));
	Desc.ByteWidth = sizeof(uint32_t) * _IndexCount;
	Desc.Usage = D3D11_USAGE_IMMUTABLE; // �ʱ�ȭ �� ����X
	Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	Desc.CPUAccessFlags = 0; // 0 if no CPU access is necessary.
	Desc.MiscFlags = 0;
	Desc.StructureByteStride = 4;

	D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
	indexBufferData.pSysMem = _Indices;
	indexBufferData.SysMemPitch = 0;
	indexBufferData.SysMemSlicePitch = 0;

	DX11DeviceContext* DeviceContext = static_cast<DX11DeviceContext*>(UEngineCore::GraphicsDevice);

	DeviceContext->GetDevice()->CreateBuffer(&Desc, &indexBufferData, Buffer.GetAddressOf());
}

DX11IndexBuffer::~DX11IndexBuffer()
{
}

void DX11IndexBuffer::Bind() const
{
	DX11DeviceContext* DeviceContext = static_cast<DX11DeviceContext*>(UEngineCore::GraphicsDevice);
	DeviceContext->GetContext()->IASetIndexBuffer(Buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}
