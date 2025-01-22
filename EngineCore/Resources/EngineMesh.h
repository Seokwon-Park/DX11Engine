#pragma once
#include "EngineBuffer.h"

// 클래스 설명 :
class UEngineMesh : public UEngineResource
{
public:
	// Constrcuter Destructer
	UEngineMesh();
	~UEngineMesh();

	// Delete Function
	UEngineMesh(const UEngineMesh& _Other) = delete;
	UEngineMesh(UEngineMesh&& _Other) noexcept = delete;
	UEngineMesh& operator=(const UEngineMesh& _Other) = delete;
	UEngineMesh& operator=(UEngineMesh&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineMesh> Create(std::string_view _Name)
	{
		return Create(_Name, _Name, _Name, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
	static std::shared_ptr<UEngineMesh> Create(std::string_view _Name, std::string_view _VBName, std::string_view _IBName, D3D_PRIMITIVE_TOPOLOGY _PrimitiveTopology);

	inline void SetVertexBuffer(std::shared_ptr<UEngineVertexBuffer> _VertexBuffer) { VertexBuffer = _VertexBuffer; }
	inline void SetIndexBuffer(std::shared_ptr<UEngineIndexBuffer> _IndexBuffer) { IndexBuffer = _IndexBuffer; }
	inline void SetTopology(D3D_PRIMITIVE_TOPOLOGY _Topology) { PrimitiveTopology = _Topology; }

	inline UINT GetIndexCount() { return IndexBuffer->GetIndexCount(); }
	void Bind() const;

protected:
private:
	std::shared_ptr<UEngineVertexBuffer> VertexBuffer;
	std::shared_ptr<UEngineIndexBuffer> IndexBuffer;
	D3D_PRIMITIVE_TOPOLOGY PrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

};
