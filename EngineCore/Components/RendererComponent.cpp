#include "EnginePCH.h"
#include "RendererComponent.h"
#include "Actor.h"
#include "ResourceManager.h"
#include <EngineCore/Resources/EngineBuffer.h>
#include <EngineCore/Resources/EngineShader.h>
#include <EngineCore/Resources/EngineTexture.h>
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

	VB = UEngineVertexBuffer::Create((void*)&Vertices[0], sizeof(Vertex) * Vertices.size(), Vertices.size());
	VB->Bind();
	IB = UEngineIndexBuffer::Create(Indices.data(), 6);
	IB->Bind();

	UEngineDirectory Dir;
	Dir.MoveParentToDirectory("EngineCore");
	Dir.AppendDirectory("Shaders");

	VS = UEngineShader::Create(Dir.GetFile("SpriteShader.hlsl").ToString(), EShaderType::VS);
	PS = UEngineShader::Create(Dir.GetFile("SpriteShader.hlsl").ToString(), EShaderType::PS);
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
		MSGASSERT("������� ������ �����߽��ϴ�..");
		return;
	}

	D3D11_MAPPED_SUBRESOURCE Data = {};
	DeviceContext->GetContext()->Map(VertexCBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);

	// Data.pData �׷���ī��� ����� �ּҰ�.
	if (nullptr == Data.pData)
	{
		MSGASSERT("�׷���ī�尡 ������ �ź��߽��ϴ�.");
	}

	memcpy_s(Data.pData, sizeof(VertexConstant), &VC, sizeof(VertexConstant));
	DeviceContext->GetContext()->Unmap(VertexCBuffer.Get(), 0);

	// ���� ������۸� 
	ID3D11Buffer* ArrPtr[16] = { VertexCBuffer.Get() };
	DeviceContext->GetContext()->VSSetConstantBuffers(0, 1, ArrPtr);


	UEngineCore::GraphicsDeviceContext->DrawCall();
}
