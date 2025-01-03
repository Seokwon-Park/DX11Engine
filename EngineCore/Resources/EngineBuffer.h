#pragma once
#include "EngineResource.h"

struct Vertex
{
	FVector4 Pos;
	FVector4 Color;
	float UV[2];
};

enum class EInputLayoutDataType
{
	None = 0,
	Float,
	Float2,
	Float3,
	Float4,
	Mat3,
	Mat4,
	Int,
	Int2,
	Int3,
	Int4,
	Bool
};

struct FInputLayoutElement
{
	std::string Name;
	EInputLayoutDataType Type;
	Uint32 Size;
	Uint32 Offset;
	bool Normalized;

	FInputLayoutElement() {}
	FInputLayoutElement(EInputLayoutDataType _Type, const std::string& _Name)
		:Name(_Name), Type(_Type), Size(InputLayoutDataTypeToSize(_Type)), Offset(0)
	{

	}

	static Uint32 InputLayoutDataTypeToSize(EInputLayoutDataType type)
	{
		switch (type)
		{
		case EInputLayoutDataType::Float: return 4;
		case EInputLayoutDataType::Float2:return 4 * 2;
		case EInputLayoutDataType::Float3:return 4 * 3;
		case EInputLayoutDataType::Float4:return 4 * 4;
		case EInputLayoutDataType::Mat3:	 return 4 * 3 * 3;
		case EInputLayoutDataType::Mat4:	 return 4 * 4 * 4;
		case EInputLayoutDataType::Int:	 return 4;
		case EInputLayoutDataType::Int2:	 return 4 * 2;
		case EInputLayoutDataType::Int3:	 return 4 * 3;
		case EInputLayoutDataType::Int4:	 return 4 * 4;
		case EInputLayoutDataType::Bool:	 return 1;
		}
		return 0;
	}
};

class UEngineInputLayout : public UEngineResource
{
public:
	// Constrcuter Destructer
	UEngineInputLayout();
	//UEngineInputLayout(const std::initializer_list<FInputLayoutData> elements)
	~UEngineInputLayout();

	// Delete Function
	UEngineInputLayout(const UEngineInputLayout& _Other) = delete;
	UEngineInputLayout(UEngineInputLayout&& _Other) noexcept = delete;
	UEngineInputLayout& operator=(const UEngineInputLayout& _Other) = delete;
	UEngineInputLayout& operator=(UEngineInputLayout&& _Other) noexcept = delete;

	ENGINE_API static std::shared_ptr<UEngineInputLayout> Create(std::shared_ptr<class UEngineShader> _VertexShader, std::vector<FInputLayoutElement>& _Elements);
	
	DXGI_FORMAT ConvertToDXGI(EInputLayoutDataType _Type);
	void Bind() const;
	void CreateLayout(std::shared_ptr<class UEngineShader> _VertexShader, std::vector<FInputLayoutElement>& _Elements);
	//ENGINE_API static std::shared_ptr<UEngineInputLayout> Create(Uint32* _Indices, Uint32 _IndexCount);
protected:
private:
	Uint32 Stride = 0;
	ComPtr<ID3D11InputLayout> InputLayout;
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

	void Bind() const;

	inline Uint32 GetVertexSize() { return VertexSize; }
	inline Uint32 GetVertexCount() { return VertexCount; }

	void CreateVertexBuffer(Uint32 _Size, Uint32 _VertexSize);
	void CreateVertexBuffer(const void* _Data, Uint32 _DataSize, Uint32 _VertexCount);

	//정점 데이터가 없는 상태로 정점 버퍼만 생성합니다.
	ENGINE_API static std::shared_ptr<UEngineVertexBuffer> Create(Uint32 _Size, Uint32 _VertexSize);

	//정점 데이터로 정점 버퍼를 생성합니다.
	ENGINE_API static std::shared_ptr<UEngineVertexBuffer> Create(const void* _Data, Uint32 _DataSize, Uint32 _VertexCount);
private:
	Uint32 Stride = 0;
	Uint32 Offset = 0;
	Uint32 VertexSize = 0;
	Uint32 VertexCount = 0;
	ComPtr<ID3D11Buffer> Buffer = nullptr; // DirectX 11 버퍼 객체
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

	void CreateIndexBuffer(Uint32* _Indices, Uint32 _IndexCount);

	void Bind() const;

	ENGINE_API static std::shared_ptr<UEngineIndexBuffer> Create(Uint32* _Indices, Uint32 _IndexCount);
protected:
private:
	Uint32 IndexCount = 0;
	ComPtr<ID3D11Buffer> Buffer = nullptr; // DirectX 11 버퍼 객체

};
