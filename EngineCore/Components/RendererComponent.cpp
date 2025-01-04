#include "EnginePCH.h"
#include "RendererComponent.h"
#include "Actor.h"
#include "ResourceManager.h"
#include <EngineCore/Resources/EngineBuffer.h>
#include <EngineCore/Resources/EngineTexture.h>
#include <EngineShaderFactory.h>
#include "EngineDeviceContext.h"

URendererComponent::URendererComponent()
{
}

URendererComponent::~URendererComponent()
{
}

void URendererComponent::BeginPlay()
{

	std::vector<Vertex> Vertices;
	std::vector<Uint32> Indices = { 0,1,2, 1,3,2 };

	Vertices.resize(4);

	Vertices[0] = Vertex{ FVector4(-0.5f, 0.5f, 1.0f, 1.0f), {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f} };
	Vertices[1] = Vertex{ FVector4(0.5f, 0.5f, 1.0f,1.0f), {0.0f, 1.0f, 0.0f, 1.0f}	,{1.0f, 0.0f} };
	Vertices[2] = Vertex{ FVector4(-0.5f, -0.5f, 1.0f,1.0f), {0.0f, 0.0f, 1.0f, 1.0f},{0.0f, 1.0f} };
	Vertices[3] = Vertex{ FVector4(0.5f, -0.5f, 1.0f,1.0f), {1.0f, 1.0f, 1.0f, 1.0f},{1.0f, 1.0f} };

	VB = UResourceManager::Find<UEngineVertexBuffer>("Quad");
	VB->Bind();
	IB = UResourceManager::Find<UEngineIndexBuffer>("Quad");
	IB->Bind();

	UEngineDirectory Dir;
	Dir.MoveParentToDirectory("EngineCore");
	Dir.AppendDirectory("Shaders");

	VS = UResourceManager::Find<UEngineShader>("QuadVS");
	PS = UResourceManager::Find<UEngineShader>("QuadPS");
	VS->Bind();
	PS->Bind();
	std::shared_ptr<UEngineInputLayout> IL = UResourceManager::Find<UEngineInputLayout>("Quad");
	IL->Bind();
}

void URendererComponent::Render(float _DeltaTime)
{
	VertexConstant VC;
	FMatrix WorldMatrix = GetTransformRef().WorldMatrix;
	WorldMatrix.MatrixTranspose();
	VC.World = WorldMatrix;
	VC.View.MatrixView(FVector4::BACK, FVector4::FORWARD, FVector4::UP);
	VC.View.MatrixTranspose();

	//Data.Proj.MatrixOrthoFovLH(1.22, 1280.0f / 720.0f, 0.01f, 100.0f);
	VC.Proj.MatrixOrthoLH(1280.f, 720.0f, 0.01f, 100.0f);
	VC.Proj.MatrixTranspose();
	//Test2->Bind();
	//Test3->Bind();
	//Shader->SetVertexConstants(Data);

	ComPtr<ID3D11Buffer> VertexCBuffer;

	auto DeviceContext = UEngineCore::GraphicsDeviceContext;

	VertexCBuffer.Reset();
	D3D11_BUFFER_DESC BufferInfo = { 0 };
	BufferInfo.ByteWidth = sizeof(VertexConstant);
	BufferInfo.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	BufferInfo.Usage = D3D11_USAGE_DYNAMIC;

	if (S_OK != DeviceContext->GetDevice()->CreateBuffer(&BufferInfo, nullptr, VertexCBuffer.GetAddressOf()))
	{
		MSGASSERT("상수버퍼 생성에 실패했습니다..");
		return;
	}

	D3D11_MAPPED_SUBRESOURCE Data = {};
	DeviceContext->GetContext()->Map(VertexCBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);

	// Data.pData 그래픽카드와 연결된 주소값.
	if (nullptr == Data.pData)
	{
		MSGASSERT("그래픽카드가 수정을 거부했습니다.");
	}

	memcpy_s(Data.pData, sizeof(VertexConstant), &VC, sizeof(VertexConstant));
	DeviceContext->GetContext()->Unmap(VertexCBuffer.Get(), 0);

	// 같은 상수버퍼를 
	ID3D11Buffer* ArrPtr[16] = { VertexCBuffer.Get() };
	DeviceContext->GetContext()->VSSetConstantBuffers(0, 1, ArrPtr);


	UEngineCore::GraphicsDeviceContext->DrawCall();
}
