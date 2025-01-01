#include "EnginePCH.h"
#include "EngineCore.h"
#include "EngineBuffer.h"
#include "DirectX11/DX11Buffer.h"
#include <EngineBase/EngineMath.h>

UEngineVertexBuffer::UEngineVertexBuffer()
{
}

UEngineVertexBuffer::~UEngineVertexBuffer()
{
}

std::shared_ptr<UEngineVertexBuffer> UEngineVertexBuffer::Create(uint32 _DataSize, uint32 _VertexSize)
{
	switch (UEngineCore::GetRendererAPI())
	{
	case ERendererAPI::DirectX11:
		return std::make_shared<DX11VertexBuffer>(_DataSize, _VertexSize);
	case ERendererAPI::None:
		return nullptr;
	default:
		return nullptr;
	}
}

std::shared_ptr<UEngineVertexBuffer> UEngineVertexBuffer::Create(std::vector<Vertex>& _Vertices, uint32 _DataSize, uint32 _VertexCount)
{
	switch (UEngineCore::GetRendererAPI())
	{
	case ERendererAPI::DirectX11:
		return std::make_shared<DX11VertexBuffer>(_Vertices, _DataSize, _VertexCount);
	case ERendererAPI::None:
		return nullptr;
	default:
		return nullptr;
	}
}

UEngineIndexBuffer::UEngineIndexBuffer()
{
}

UEngineIndexBuffer::~UEngineIndexBuffer()
{
}

ENGINE_API std::shared_ptr<UEngineIndexBuffer> UEngineIndexBuffer::Create(std::vector<uint32> _Indices, uint32 _IndexCount)
{
	switch (UEngineCore::GetRendererAPI())
	{
	case ERendererAPI::DirectX11:
		return std::make_shared<DX11IndexBuffer>(_Indices, _IndexCount);
	case ERendererAPI::None:
		return nullptr;
	default:
		return nullptr;
	}
}
