#pragma once
#include "EngineResource.h"
#include <EngineCore/EngineDeviceContext.h>
#include <EngineCore/EngineCore.h>
#include "EngineShader.h"

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

class UEngineBuffer : public UEngineResource
{
public:
	// Constrcuter Destructer
	UEngineBuffer() {};
	virtual ~UEngineBuffer() {};

	// Delete Function
	UEngineBuffer(const UEngineBuffer& _Other) = delete;
	UEngineBuffer(UEngineBuffer&& _Other) noexcept = delete;
	UEngineBuffer& operator=(const UEngineBuffer& _Other) = delete;
	UEngineBuffer& operator=(UEngineBuffer&& _Other) noexcept = delete;
protected:
	ComPtr<ID3D11Buffer> Buffer = nullptr; 
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
class UEngineVertexBuffer : public UEngineBuffer
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
};

// 클래스 설명 :
class UEngineIndexBuffer : public UEngineBuffer
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
	inline Uint32 GetIndexCount() const { return IndexCount; }

	ENGINE_API static std::shared_ptr<UEngineIndexBuffer> Create(Uint32* _Indices, Uint32 _IndexCount);
protected:
private:
	Uint32 IndexCount = 0;
};

class UEngineConstantBuffer : public UEngineBuffer
{
public:
	UEngineConstantBuffer();
	~UEngineConstantBuffer();

	// Delete Function
	UEngineConstantBuffer(const UEngineConstantBuffer& _Other) = delete;
	UEngineConstantBuffer(UEngineConstantBuffer&& _Other) noexcept = delete;
	UEngineConstantBuffer& operator=(const UEngineConstantBuffer& _Other) = delete;
	UEngineConstantBuffer& operator=(UEngineConstantBuffer&& _Other) noexcept = delete;

	template <typename DataType>
	static std::shared_ptr<UEngineConstantBuffer> Create(DataType& _Data)
	{
		std::shared_ptr<UEngineConstantBuffer> NewConstantBuffer = std::make_shared<UEngineConstantBuffer>();

		NewConstantBuffer->BufferSize = sizeof(DataType);
		NewConstantBuffer->CreateConstantBuffer();
		NewConstantBuffer->SetData(_Data, sizeof(DataType));

		return NewConstantBuffer;
	}

	void CreateConstantBuffer();

	template <typename DataType>
	void SetData(const DataType& _Data, size_t _DataSize)
	{
		if (_DataSize != BufferSize)
		{
			MSGASSERT("버퍼와 데이터의 크기가 다름");
		}

		UEngineDeviceContext* DeviceContext = UEngineCore::GetGraphicsDeviceContext();

		D3D11_MAPPED_SUBRESOURCE Data;
		DeviceContext->GetContext()->Map(Buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);
		if (nullptr == Data.pData)
		{
			MSGASSERT("그래픽카드가 수정을 거부했습니다.");
		}

		memcpy_s(Data.pData, sizeof(_Data), &_Data, sizeof(_Data));
		DeviceContext->GetContext()->Unmap(Buffer.Get(), 0);
	}
	
	void Bind(EShaderType _Type, Uint32 _Slot = 0) const;
private:
	void* BufferData = nullptr;
	size_t BufferSize = 0;
	ComPtr<ID3D11Buffer> Buffer = nullptr;
};
