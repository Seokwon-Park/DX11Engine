#include "EnginePCH.h"
#include "EngineCore.h"
#include "EngineBuffer.h"
#include "DirectX11/DX11Buffer.h"
#include <EngineBase/EngineMath.h>

VertexBuffer::VertexBuffer()
{
}

VertexBuffer::~VertexBuffer()
{
}

std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32 _DataSize, uint32 _VertexSize)
{
	switch (UEngineCore::GraphicsDevice->GetRendererAPI())
	{
	case ERendererAPI::DirectX11:
		return std::make_shared<DX11VertexBuffer>(_DataSize, _VertexSize);
	case ERendererAPI::None:
		return nullptr;
	default:
		return nullptr;
	}
}

std::shared_ptr<VertexBuffer> VertexBuffer::Create(std::vector<Vertex>& _Vertices, uint32 _DataSize, uint32 _VertexCount)
{
	switch (UEngineCore::GraphicsDevice->GetRendererAPI())
	{
	case ERendererAPI::DirectX11:
		return std::make_shared<DX11VertexBuffer>(_Vertices, _DataSize, _VertexCount);
	case ERendererAPI::None:
		return nullptr;
	default:
		return nullptr;
	}
}

IndexBuffer::IndexBuffer()
{
}

IndexBuffer::~IndexBuffer()
{
}
