#include "EnginePCH.h"
#include "EngineCore.h"
#include "EngineBuffer.h"
#include "EngineShader.h"
#include "EngineDeviceContext.h"
#include <EngineBase/EngineMath.h>

UEngineVertexBuffer::UEngineVertexBuffer()
{
}

UEngineVertexBuffer::~UEngineVertexBuffer()
{
}

void UEngineVertexBuffer::Bind() const
{
	UEngineCore::GetGraphicsDeviceContext()->GetContext()->IASetVertexBuffers(0, 1, Buffer.GetAddressOf(), &Stride, &Offset);
}

void UEngineVertexBuffer::CreateVertexBuffer(Uint32 _Size, Uint32 _VertexSize)
{
	//Stride = _VertexSize;
	//D3D11_BUFFER_DESC Desc;
	//ZeroMemory(&Desc, sizeof(D3D11_BUFFER_DESC));
	//Desc.ByteWidth = _DataSize;
	//Desc.Usage = D3D11_USAGE_DYNAMIC;
	//Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	////Desc.MiscFlags = 0;
	//Desc.StructureByteStride = sizeof(Vertex); // 구조적 버퍼에서만 필요함.
	
	//UEngineCore::GraphicsDeviceContext->GetDevice()->CreateBuffer(&Desc, nullptr, Buffer.GetAddressOf());
}

void UEngineVertexBuffer::CreateVertexBuffer(const void* _Data, Uint32 _DataSize, Uint32 _VertexCount)
{
	Stride = _DataSize / _VertexCount;
	D3D11_BUFFER_DESC Desc;
	ZeroMemory(&Desc, sizeof(D3D11_BUFFER_DESC));
	Desc.ByteWidth = _DataSize;
	Desc.Usage = D3D11_USAGE_IMMUTABLE;
	Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	Desc.CPUAccessFlags = 0;
	Desc.MiscFlags = 0;
	Desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA VerticesData = { 0 };
	// MS 예제에서 초기화하는 방식
	VerticesData.pSysMem = _Data;
	VerticesData.SysMemPitch = 0;
	VerticesData.SysMemSlicePitch = 0;

	UEngineCore::GetGraphicsDeviceContext()->GetDevice()->CreateBuffer(&Desc, &VerticesData, Buffer.GetAddressOf());
}

std::shared_ptr<UEngineVertexBuffer> UEngineVertexBuffer::Create(Uint32 _DataSize, Uint32 _VertexSize)
{
	return nullptr;
}

std::shared_ptr<UEngineVertexBuffer> UEngineVertexBuffer::Create(const void* _Data, Uint32 _DataSize, Uint32 _VertexCount)
{
	std::shared_ptr<UEngineVertexBuffer> NewVertexBuffer = std::make_shared<UEngineVertexBuffer>();
	NewVertexBuffer->CreateVertexBuffer(_Data, _DataSize, _VertexCount);
	return NewVertexBuffer;
}
// Vertex Buffer ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


UEngineIndexBuffer::UEngineIndexBuffer()
{

}

UEngineIndexBuffer::~UEngineIndexBuffer()
{
}

void UEngineIndexBuffer::CreateIndexBuffer(Uint32* _Indices, Uint32 _IndexCount)
{
	D3D11_BUFFER_DESC Desc = {};
	ZeroMemory(&Desc, sizeof(D3D11_BUFFER_DESC));
	Desc.ByteWidth = sizeof(uint32_t) * _IndexCount;
	Desc.Usage = D3D11_USAGE_IMMUTABLE;
	Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	Desc.CPUAccessFlags = 0;
	Desc.MiscFlags = 0;
	Desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
	indexBufferData.pSysMem = _Indices;
	indexBufferData.SysMemPitch = 0;
	indexBufferData.SysMemSlicePitch = 0;

	UEngineCore::GraphicsDeviceContext->GetDevice()->CreateBuffer(&Desc, &indexBufferData, Buffer.GetAddressOf());
}

void UEngineIndexBuffer::Bind() const
{
	UEngineCore::GetGraphicsDeviceContext()->GetContext()->IASetIndexBuffer(Buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}

ENGINE_API std::shared_ptr<UEngineIndexBuffer> UEngineIndexBuffer::Create(Uint32* _Indices, Uint32 _IndexCount)
{
	std::shared_ptr<UEngineIndexBuffer> NewIndexBuffer = std::make_shared<UEngineIndexBuffer>();
	NewIndexBuffer->CreateIndexBuffer(_Indices, _IndexCount);
	return NewIndexBuffer;
}

// Index Buffer ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

UEngineInputLayout::UEngineInputLayout()
{
}

UEngineInputLayout::~UEngineInputLayout()
{
}

ENGINE_API std::shared_ptr<UEngineInputLayout> UEngineInputLayout::Create(std::shared_ptr<UEngineShader> _VertexShader, std::vector<FInputLayoutElement>& _Elements)
{
	Uint32 Offset = 0;
	for (FInputLayoutElement& Element : _Elements)
	{
		Element.Offset = Offset;
		Offset += Element.Size;
	}

	std::shared_ptr<UEngineInputLayout> NewInputLayout;
	NewInputLayout->Stride = Offset;

	return NewInputLayout;
}

void UEngineInputLayout::Bind() const
{
	UEngineCore::GetGraphicsDeviceContext()->GetContext()->IASetInputLayout(InputLayout.Get());
}


void UEngineInputLayout::CreateLayout(std::shared_ptr<UEngineShader> _VertexShader, std::vector<FInputLayoutElement>& _Elements)
{
	auto DeviceContext = UEngineCore::GraphicsDeviceContext;

	std::map<std::string, UINT> SemanticIndexMap;

	Uint32 index = 0;
	std::vector<D3D11_INPUT_ELEMENT_DESC> InputElements;
	for (const auto& Element : _Elements)
	{
		//For Semantic Index
		if (SemanticIndexMap.contains(Element.Name.c_str())) {
			// Key가 이미 존재하는 경우, SemanticIndex 증가
			SemanticIndexMap[Element.Name]++;
		}
		else {
			// Key가 없는 경우, SemanticIndex 값을 0으로 초기화
			SemanticIndexMap[Element.Name] = 0;
		}
		D3D11_INPUT_ELEMENT_DESC DXLayout = { Element.Name.c_str(), SemanticIndexMap[Element.Name], ConvertToDXGI(Element.Type), 0, Element.Offset, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		InputElements.push_back(DXLayout);
	}

	HRESULT Result = DeviceContext->GetDevice()->CreateInputLayout(
		InputElements.data(),
		static_cast<Uint32>(InputElements.size()),
		_VertexShader->GetShaderBlob()->GetBufferPointer(),
		_VertexShader->GetShaderBlob()->GetBufferSize(),
		InputLayout.GetAddressOf());

	if (S_OK != Result)
	{
		//std::cerr << "CreateInputLayout failed with HRESULT: " << std::hex << Result << std::endl;
		MSGASSERT("인풋 레이아웃 생성에 실패했습니다");
	}
}

DXGI_FORMAT UEngineInputLayout::ConvertToDXGI(EInputLayoutDataType _Type)
{
	switch (_Type)
	{
	case EInputLayoutDataType::Float:  return DXGI_FORMAT_R32_FLOAT;
	case EInputLayoutDataType::Float2: return DXGI_FORMAT_R32G32_FLOAT;
	case EInputLayoutDataType::Float3: return DXGI_FORMAT_R32G32B32_FLOAT;
	case EInputLayoutDataType::Float4: return DXGI_FORMAT_R32G32B32A32_FLOAT;
	case EInputLayoutDataType::Mat3:   return DXGI_FORMAT_UNKNOWN;
	case EInputLayoutDataType::Mat4:   return DXGI_FORMAT_UNKNOWN;
	case EInputLayoutDataType::Int:	   return DXGI_FORMAT_R32_SINT;
	case EInputLayoutDataType::Int2:   return DXGI_FORMAT_R32G32_SINT;
	case EInputLayoutDataType::Int3:   return DXGI_FORMAT_R32G32B32_SINT;
	case EInputLayoutDataType::Int4:   return DXGI_FORMAT_R32G32B32A32_SINT;
	case EInputLayoutDataType::Bool:   return DXGI_FORMAT_UNKNOWN;
	default:
		break;
	}

	return DXGI_FORMAT_UNKNOWN;
}


